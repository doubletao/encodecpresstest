#include "stdafx.h"
#include "FFmpegAudioDecoder.h"
#include "FormatConverter.h"

FFmpegAudioDecoder::FFmpegAudioDecoder()
: m_pSrcFrame(nullptr)
, m_pSwrFrame(nullptr)
, m_pCodecCtx(nullptr)
, m_pSwrCtx(nullptr)
, m_pAudioFifo(nullptr)
, m_pDestBuffer(nullptr)
{

}

FFmpegAudioDecoder::~FFmpegAudioDecoder()
{
	Release();
}

bool FFmpegAudioDecoder::InitAudioDecoder(const SAudioMediaInfo &sAudioInfo)
{
	AVCodecID codecId = FFmpegFormatCovert::ConvertCodecId(sAudioInfo.enumAudioType);
	AVCodec* pAudioCodec = avcodec_find_decoder(codecId);
	if (!pAudioCodec) {
		return false;
	}

	m_pCodecCtx = avcodec_alloc_context3(pAudioCodec);

	m_pCodecCtx->profile = FFmpegFormatCovert::ConvertAudioProfile(sAudioInfo.dwAudioSubType);			// AV_SAMPLE_FMT_FLTP;
	m_pCodecCtx->sample_fmt = FFmpegFormatCovert::ConvertSamplesFormat(sAudioInfo.enumChannelSamplesFormat);
	m_pCodecCtx->sample_rate = sAudioInfo.dwSamplesPerSec;												// 48000;
	m_pCodecCtx->channels = sAudioInfo.dwChannels;	       												// av_get_channel_layout_nb_channels(m_pCodecCtx->channel_layout);
	m_pCodecCtx->channel_layout = FFmpegFormatCovert::ConvertChannelLayout(sAudioInfo.enumAudioCFG);	// AV_CH_LAYOUT_STEREO;
	m_pCodecCtx->thread_count = 1;

	if (avcodec_open2(m_pCodecCtx, pAudioCodec, nullptr) < 0) {
		return false;
	}

	m_pSrcFrame = av_frame_alloc();

	return true;
}

bool FFmpegAudioDecoder::SetAudioSamplesBufInfo(SAudioSamplesBufInfo *pAudioBufInfo)
{
	if (!pAudioBufInfo || !m_pCodecCtx) {
		return false;
	}

	AVSampleFormat format = FFmpegFormatCovert::ConvertSamplesFormat(pAudioBufInfo->enumChannelSamplesFormat);

	int channels = pAudioBufInfo->dwChannels;
	int sample_rate = pAudioBufInfo->dwSamplesPerSec;

	m_pAudioFifo = av_audio_fifo_alloc(format, channels, m_pCodecCtx->frame_size);
	if (!m_pAudioFifo) {
		return false;
	}

	m_pDestBuffer.reset(new SW_UINT8[AVCODEC_MAX_AUDIO_FRAME_SIZE]);

	bool bSwr = (m_pCodecCtx->channels != channels || m_pCodecCtx->sample_fmt != format ||
				 m_pCodecCtx->sample_rate != sample_rate);
	if (!bSwr) { // 无需重采样直接返回
		return true;
	}

	SW_UINT64 nChannelLayout = FFmpegFormatCovert::ConvertChannelLayout(pAudioBufInfo->enumAudioCFG);

	m_pSwrFrame = av_frame_alloc();
	m_pSwrFrame->channels = channels;
	m_pSwrFrame->format = format;
	m_pSwrFrame->sample_rate = sample_rate;
	m_pSwrFrame->channel_layout = nChannelLayout;
	m_pSwrFrame->nb_samples = m_pCodecCtx->frame_size;		// ???

	if (av_frame_get_buffer(m_pSwrFrame, 0) < 0)
	{
		av_frame_free(&m_pSwrFrame);
		return false;
	}

	m_pSwrCtx = swr_alloc_set_opts(nullptr, m_pCodecCtx->channel_layout, m_pCodecCtx->sample_fmt,
		m_pCodecCtx->sample_rate, nChannelLayout, format, pAudioBufInfo->dwSamplesPerSec, 0, 0);

	if (swr_is_initialized(m_pSwrCtx) == 0) {
		swr_init(m_pSwrCtx);
	}

	return true;
}

bool FFmpegAudioDecoder::PutFrame(const SW_UINT8* pData, const SRFrameInfo* pFrameInfo)
{
	if (!m_pCodecCtx) {
		return false;
	}

	AVPacket avpkt = { 0 };
	av_init_packet(&avpkt);
	avpkt.data = const_cast<uint8_t*>(pData);
	avpkt.size = pFrameInfo->iSize;

	int ret = avcodec_send_packet(m_pCodecCtx, &avpkt);
	if (ret < 0) {
		av_packet_unref(&avpkt);
		return false;
	}
	av_packet_unref(&avpkt);

	return true;
}

int FFmpegAudioDecoder::GetSample(SW_UINT8* &lpBuffer)
{
	if (!m_pCodecCtx || !m_pSrcFrame) {
		return 0;
	}

	int ret = avcodec_receive_frame(m_pCodecCtx, m_pSrcFrame);
	if (ret < 0) {
		return false;
	}

	int bufSizeRet = m_pCodecCtx->sample_rate * m_pCodecCtx->channels * av_get_bytes_per_sample(m_pCodecCtx->sample_fmt) / 25;

	if (m_pSwrCtx && m_pSwrFrame)
	{
		int swr_size = swr_convert(m_pSwrCtx, m_pSwrFrame->data, m_pSwrFrame->nb_samples,
			(const SW_UINT8**)m_pSrcFrame->data, m_pSrcFrame->nb_samples);
		av_audio_fifo_write(m_pAudioFifo, (void**)m_pSwrFrame->data, swr_size);
		bufSizeRet = m_pSwrFrame->sample_rate * m_pSwrFrame->channels * av_get_bytes_per_sample((AVSampleFormat)m_pSwrFrame->format) / 25;
	}
	else
	{
		av_audio_fifo_write(m_pAudioFifo, (void**)m_pSrcFrame->data, m_pSrcFrame->nb_samples);
	}

	if (av_audio_fifo_size(m_pAudioFifo) >= bufSizeRet)
	{
		av_audio_fifo_read(m_pAudioFifo, (void **)m_pDestBuffer.get(), bufSizeRet);
		lpBuffer = m_pDestBuffer.get();
		return bufSizeRet;
	}

	return 0;
}

bool FFmpegAudioDecoder::Release()
{
	av_frame_free(&m_pSrcFrame);
	av_frame_free(&m_pSwrFrame);

	avcodec_close(m_pCodecCtx);
	avcodec_free_context(&m_pCodecCtx);

	return true;
}