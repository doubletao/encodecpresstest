#include "ecCodecFFmpegAudioDecoder.h"
#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "avutil.lib")
#pragma comment(lib, "swresample.lib")
#include "FFmpegFormatConverter.h"

ecCodecFFmpegAudioDecoder::ecCodecFFmpegAudioDecoder()
	: m_pCodecCtx(nullptr)
	, m_bIsInitialized(false)
	, m_pSrcFrame(nullptr)
	, m_pSwrFrame(nullptr)
	, m_pSwrCtx(nullptr)
	, m_pAudioFifo(nullptr)
{
}


ecCodecFFmpegAudioDecoder::~ecCodecFFmpegAudioDecoder()
{
	Release();
}

bool ecCodecFFmpegAudioDecoder::InitAudioDecoder(const SDAudioMediaInfo & sAudioInfo)
{
	Release();
	AVCodecID codecId = FFmpegFormatCovert::ConvertCodecId(sAudioInfo.enumAudioType);
	AVCodec* pAudioCodec = avcodec_find_decoder(codecId);
	if (pAudioCodec) 
	{
		m_pCodecCtx = avcodec_alloc_context3(pAudioCodec);
		if (m_pCodecCtx)
		{
			m_pCodecCtx->profile = FFmpegFormatCovert::ConvertAudioProfile(sAudioInfo.dwAudioSubType);			// AV_SAMPLE_FMT_FLTP;
			m_pCodecCtx->sample_fmt = FFmpegFormatCovert::ConvertSamplesFormat(sAudioInfo.enumChannelSamplesFormat);
			m_pCodecCtx->sample_rate = sAudioInfo.dwSamplesPerSec;												// 48000;
			m_pCodecCtx->channels = sAudioInfo.dwChannels;	       												// av_get_channel_layout_nb_channels(m_pCodecCtx->channel_layout);
			m_pCodecCtx->channel_layout = FFmpegFormatCovert::ConvertChannelLayout(sAudioInfo.enumAudioCFG);	// AV_CH_LAYOUT_STEREO;
			m_pCodecCtx->thread_count = 1;
			if (avcodec_open2(m_pCodecCtx, pAudioCodec, nullptr) < 0) 
			{
				m_pSrcFrame = av_frame_alloc();
				if (m_pSrcFrame)
				{
					m_bIsInitialized = true;
				}
				else
				{
					printf("failed create frame\n");
				}
			}
			else
			{
				printf("failed to open codec\n");
			}
		}
		else
		{
			printf("failed to create codecctx\n");
		}
	}
	else
	{
		printf("failed to find codec\n");
	}

	return m_bIsInitialized;
}

bool ecCodecFFmpegAudioDecoder::GetAudioMediaInfo(SDAudioMediaInfo * pAudioInfo)
{
	pAudioInfo->enumAudioType = FFmpegFormatCovert::ConvertAudioType(m_pCodecCtx->codec_id);		// 音频编解码类型。
	pAudioInfo->dwAudioSubType = 0;		// 音频编解码的子类型,子类型定义随enumAudioType不同而不同
	pAudioInfo->dwChannels = m_pCodecCtx->channels;			// 声道数目
	pAudioInfo->dwBitsPerSample = m_pCodecCtx->bits_per_raw_sample;	// 采样位数 
	pAudioInfo->dwSamplesPerSec = m_pCodecCtx->sample_rate;	// 每秒采样数量 
	pAudioInfo->dwAvgBitsPerSec = m_pCodecCtx->bit_rate;	// 音频码率 bits
	pAudioInfo->dwBlockAlign = m_pCodecCtx->block_align;		// 数据块对齐单位(每个采样样本需要的字节数), 声道数*量化数/8, 量化数(16,20?,24,32...										//Below is Version 2 Add.
	pAudioInfo->enumAudioCFG = FFmpegFormatCovert::ConvertChannelLayout(m_pCodecCtx->channel_layout);		//声道属性
	pAudioInfo->enumChannelSamplesFormat = SDCHANNELSAMPLESFORMAT_Unknow;	//音频声道采样数据格式
	pAudioInfo->dwStruSize = sizeof(SDAudioMediaInfo);			// 结构大小
	return false;
}

bool ecCodecFFmpegAudioDecoder::SetAudioMediaInfo(SDAudioMediaInfo * pAudioInfo)
{
	if (!pAudioInfo || !m_pCodecCtx) {
		return false;
	}

	AVSampleFormat format = FFmpegFormatCovert::ConvertSamplesFormat(pAudioInfo->enumChannelSamplesFormat);

	int channels = pAudioInfo->dwChannels;
	int sample_rate = pAudioInfo->dwSamplesPerSec;

	m_pAudioFifo = av_audio_fifo_alloc(format, channels, m_pCodecCtx->frame_size);
	if (!m_pAudioFifo) {
		return false;
	}

	m_pDestBuffer.reset(new SD_UINT8[AVCODEC_MAX_AUDIO_FRAME_SIZE]);

	bool bSwr = (m_pCodecCtx->channels != channels || m_pCodecCtx->sample_fmt != format ||
		m_pCodecCtx->sample_rate != sample_rate);
	if (!bSwr) { // 无需重采样直接返回
		return true;
	}

	SD_UINT64 nChannelLayout = FFmpegFormatCovert::ConvertChannelLayout(pAudioInfo->enumAudioCFG);

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
		m_pCodecCtx->sample_rate, nChannelLayout, format, pAudioInfo->dwSamplesPerSec, 0, 0);

	if (swr_is_initialized(m_pSwrCtx) == 0) {
		swr_init(m_pSwrCtx);
	}

	return true;
}

bool ecCodecFFmpegAudioDecoder::PutFrame(const SD_UINT8 * pData, const SDRFrameInfo * pFrameInfo)
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

int ecCodecFFmpegAudioDecoder::GetSample(SD_UINT8 *& lpBuffer)
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
			(const SD_UINT8**)m_pSrcFrame->data, m_pSrcFrame->nb_samples);
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

SD_UINT32 ecCodecFFmpegAudioDecoder::GetBufferSize()
{
	if (m_pSwrFrame)
	{
		return av_samples_get_buffer_size(nullptr, m_pSwrFrame->channels, m_pSwrFrame->nb_samples, (AVSampleFormat)m_pSwrFrame->format, 1);
	}
	else if (m_pSrcFrame)
	{
		return av_samples_get_buffer_size(nullptr, m_pSrcFrame->channels, m_pSrcFrame->nb_samples, (AVSampleFormat)m_pSrcFrame->format, 1);
	}
	return 0;
}

bool ecCodecFFmpegAudioDecoder::IsInitialized()
{
	return m_bIsInitialized;
}

bool ecCodecFFmpegAudioDecoder::Release()
{
	if (m_pCodecCtx)
	{
		avcodec_close(m_pCodecCtx);
		avcodec_free_context(&m_pCodecCtx);
	}
	if (m_pSrcFrame)
	{
		av_frame_free(&m_pSrcFrame);
	}
	if (m_pSwrFrame)
	{
		av_frame_free(&m_pSwrFrame);
	}
	if (m_pSwrCtx)
	{
		swr_close(m_pSwrCtx);
		swr_free(&m_pSwrCtx);
	}
	if (m_pAudioFifo)
	{
		av_audio_fifo_free(m_pAudioFifo);
		m_pAudioFifo = nullptr;
	}
	m_bIsInitialized = false;
	return true;
}
