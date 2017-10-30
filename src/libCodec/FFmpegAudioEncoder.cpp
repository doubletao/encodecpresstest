#include "stdafx.h"
#include "FFmpegAudioEncoder.h"
#include "FormatConverter.h"

FFmpegAudioEncoder::FFmpegAudioEncoder()
	: m_pSwrFrame(nullptr)
	, m_pAudioFrame(nullptr)
	, m_pCodecCtx(nullptr)
	, m_pSwrCtx(nullptr)
	, m_pAudioFifo(nullptr)
	, m_pDestBuffer(nullptr)
{

}

FFmpegAudioEncoder::~FFmpegAudioEncoder()
{
	Release();
}

bool FFmpegAudioEncoder::InitAudioEncoder(const SAudioMediaInfo &sAudioInfo)
{
	AVCodecID codecId = FFmpegFormatCovert::ConvertCodecId(sAudioInfo.enumAudioType);
	AVCodec* pAudioCodec = avcodec_find_encoder(codecId);
	if (!pAudioCodec) {
		return false;
	}

	m_pCodecCtx = avcodec_alloc_context3(pAudioCodec);
	if (!m_pCodecCtx) {
		return false;
	}

	m_pCodecCtx->profile = FFmpegFormatCovert::ConvertAudioProfile(sAudioInfo.dwAudioSubType);			// AV_SAMPLE_FMT_FLTP;
	m_pCodecCtx->sample_fmt = AV_SAMPLE_FMT_FLTP;// FFmpegFormatCovert::ConvertSamplesFormat(sAudioInfo.enumChannelSamplesFormat);
	m_pCodecCtx->sample_rate = sAudioInfo.dwSamplesPerSec;												// 48000;
	m_pCodecCtx->channels = sAudioInfo.dwChannels;	       												// av_get_channel_layout_nb_channels(m_pCodecCtx->channel_layout);
	m_pCodecCtx->channel_layout = FFmpegFormatCovert::ConvertChannelLayout(sAudioInfo.enumAudioCFG);	// AV_CH_LAYOUT_STEREO;
	m_pCodecCtx->bit_rate = sAudioInfo.dwAvgBitsPerSec;
	m_pCodecCtx->time_base.num = 1;
	m_pCodecCtx->time_base.den = m_pCodecCtx->sample_rate;
	m_pCodecCtx->codec_type = AVMEDIA_TYPE_AUDIO;
	m_pCodecCtx->thread_count = 1;
	//m_pCodecCtx->flags |= CODEC_FLAG_GLOBAL_HEADER;

	if (m_pCodecCtx->codec_id == AV_CODEC_ID_AAC) {
		m_pCodecCtx->profile = FF_PROFILE_AAC_LOW;
		m_pCodecCtx->strict_std_compliance = FF_COMPLIANCE_EXPERIMENTAL;
	}

	if (avcodec_open2(m_pCodecCtx, pAudioCodec, nullptr) < 0) {
		return false;
	}
		 
	return true;
}

bool FFmpegAudioEncoder::SetAudioSamplesBufInfo(const SAudioSamplesBufInfo *pAudioBufInfo)
{
	if (!pAudioBufInfo || !m_pCodecCtx) {
		return false;
	}

	int channels = pAudioBufInfo->dwChannels;
	int sample_rate = pAudioBufInfo->dwSamplesPerSec;
	AVSampleFormat format = FFmpegFormatCovert::ConvertSamplesFormat(pAudioBufInfo->enumChannelSamplesFormat);

	m_pAudioFifo = av_audio_fifo_alloc(m_pCodecCtx->sample_fmt, m_pCodecCtx->channels, m_pCodecCtx->frame_size*10);
	if (!m_pAudioFifo) {
		return false;
	}

	m_nBytesPerSrcSample = pAudioBufInfo->dwChannels * av_get_bytes_per_sample(format);
	m_pDestBuffer.reset(new SW_UINT8[AVCODEC_MAX_AUDIO_FRAME_SIZE]);

 	bool bSwr = (channels != m_pCodecCtx->channels || format != m_pCodecCtx->sample_fmt ||
 				 sample_rate != m_pCodecCtx->sample_rate);
 	if (!bSwr) { // 无需重采样直接返回
 		return true;
 	}

	m_pAudioFrame = av_frame_alloc();
	m_pAudioFrame->channels = m_pCodecCtx->channels;
	m_pAudioFrame->format = m_pCodecCtx->sample_fmt;
	m_pAudioFrame->sample_rate = m_pCodecCtx->sample_rate;
	m_pAudioFrame->channel_layout = m_pCodecCtx->channel_layout;
	m_pAudioFrame->nb_samples = m_pCodecCtx->frame_size;
	if (av_frame_get_buffer(m_pAudioFrame, 0) < 0) {
		av_frame_free(&m_pAudioFrame);
		return false;
	}
	
	SW_UINT64 nChannelLayout = FFmpegFormatCovert::ConvertChannelLayout(pAudioBufInfo->enumAudioCFG);
	m_pSwrCtx = swr_alloc_set_opts(nullptr, m_pCodecCtx->channel_layout, m_pCodecCtx->sample_fmt, 
		m_pCodecCtx->sample_rate, nChannelLayout, format, pAudioBufInfo->dwSamplesPerSec, 0, 0);

	if (swr_is_initialized(m_pSwrCtx) == 0) {
		swr_init(m_pSwrCtx);
	}

	return true;
}

bool FFmpegAudioEncoder::WriteSample(const SW_UINT8* pData, SW_UINT32 iSize, bool emInputFlag)
{
	if (!m_pAudioFifo) {
		return false;
	}

	int nSamples = iSize / m_nBytesPerSrcSample;

	if (!m_pSwrFrame || m_pSwrFrame->nb_samples<nSamples)
	{
		av_frame_free(&m_pSwrFrame);
		m_pSwrFrame = av_frame_alloc();
		m_pSwrFrame->channels = m_pCodecCtx->channels;
		m_pSwrFrame->format = m_pCodecCtx->sample_fmt;
		m_pSwrFrame->sample_rate = m_pCodecCtx->sample_rate;
		m_pSwrFrame->channel_layout = m_pCodecCtx->channel_layout;
		m_pSwrFrame->nb_samples = nSamples;
		if (av_frame_get_buffer(m_pSwrFrame, 0) < 0) {
			av_frame_free(&m_pSwrFrame);
			return false;
		}
	}

	if (m_pSwrCtx) {
		swr_convert(m_pSwrCtx, m_pSwrFrame->data, nSamples, &pData, nSamples);
		int fifo = av_audio_fifo_write(m_pAudioFifo, (void**)m_pSwrFrame->data, nSamples);
	}

	return true;
}

bool FFmpegAudioEncoder::SetEndofInput()
{
	return true;
}

bool FFmpegAudioEncoder::GetCompressFrame(SW_UINT8* &pData, SRFrameInfo* pFrameInfo)
{
	if (!m_pCodecCtx || !m_pAudioFrame) {
		return false;
	}

	if (av_audio_fifo_size(m_pAudioFifo) < m_pCodecCtx->frame_size) {
		return false;
	}

	av_audio_fifo_read(m_pAudioFifo, (void**)m_pAudioFrame->data, m_pCodecCtx->frame_size);

	m_pAudioFrame->pts = m_pts++*m_pCodecCtx->frame_size;
	AVRational timebase = { 1, m_pCodecCtx->sample_rate };
	m_pAudioFrame->pts = av_rescale_q(m_pAudioFrame->pts, timebase, m_pCodecCtx->time_base);

	int ret = avcodec_send_frame(m_pCodecCtx, m_pAudioFrame);
	if (ret < 0) {
		return false;
	}

	AVPacket avpkt = { 0 };
	av_init_packet(&avpkt);
	if (avcodec_receive_packet(m_pCodecCtx, &avpkt) < 0) {
		av_packet_unref(&avpkt);
		return false;
	}

	memcpy(m_pDestBuffer.get(), avpkt.data, avpkt.size);
	pData = m_pDestBuffer.get();
	pFrameInfo->iSize = avpkt.size;
	pFrameInfo->qwDTS = avpkt.dts;
	pFrameInfo->qwPTS = avpkt.pts;
	pFrameInfo->qwDuration = avpkt.duration;

	av_packet_unref(&avpkt);

	return true;
}

bool FFmpegAudioEncoder::Release()
{
	avcodec_close(m_pCodecCtx);
	avcodec_free_context(&m_pCodecCtx);		

	av_frame_free(&m_pSwrFrame);
	av_frame_free(&m_pAudioFrame);
	if (m_pSwrCtx)
	{
		swr_close(m_pSwrCtx);
		swr_free(&m_pSwrCtx);
	}

	av_audio_fifo_free(m_pAudioFifo);
	m_pAudioFifo = nullptr;

	return true;
}

AVCodecContext* FFmpegAudioEncoder::GetCodecContext() const
{
	return m_pCodecCtx;
}