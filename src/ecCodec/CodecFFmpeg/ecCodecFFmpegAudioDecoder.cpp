#include "ecCodecFFmpegAudioDecoder.h"
#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "avutil.lib")
#pragma comment(lib, "swresample.lib")
#include "FFmpegFormatConverter.h"

ecCodecFFmpegAudioDecoder::ecCodecFFmpegAudioDecoder()
	: m_pCodecCtx(nullptr)
	, m_bIsInitialized(false)
	, m_pSrcFrame(nullptr)
	, m_pAudioFifo(nullptr)
	, m_nDesChannelLayout(0)
	, m_emDesSampleFormat(AV_SAMPLE_FMT_NONE)
	, m_nDesSampleRate(0)
	, m_nDesChannelCount(0)
	, m_nLastSampleNum(0)
#ifndef DEBUG_USE_RESAMPLER
	, m_pSwrFrame(nullptr)
	, m_pSwrCtx(nullptr)
#endif
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
			m_pCodecCtx->block_align = sAudioInfo.dwBlockAlign;
			m_pCodecCtx->extradata = sAudioInfo.extradata;
			m_pCodecCtx->extradata_size = sAudioInfo.extradata_size;
			int nRet = avcodec_open2(m_pCodecCtx, pAudioCodec, nullptr);
			if (nRet == 0)
			{
				m_pSrcFrame = av_frame_alloc();
				if (m_pSrcFrame)
				{
					m_pSrcFrame->channels = m_pCodecCtx->channels;
					m_pSrcFrame->format = m_pCodecCtx->sample_fmt;
					m_pSrcFrame->sample_rate = m_pCodecCtx->sample_rate;
					m_pSrcFrame->channel_layout = m_pCodecCtx->channel_layout;
					m_pSrcFrame->nb_samples = m_pCodecCtx->frame_size;		// ???

					m_nDesChannelLayout = m_pCodecCtx->channel_layout;
					m_emDesSampleFormat = m_pCodecCtx->sample_fmt;
					m_nDesSampleRate = m_pCodecCtx->sample_rate;
					m_nDesChannelCount = m_pCodecCtx->channels;
					
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

	m_nDesChannelLayout = FFmpegFormatCovert::ConvertChannelLayout(pAudioInfo->enumAudioCFG);
	m_emDesSampleFormat = FFmpegFormatCovert::ConvertSamplesFormat(pAudioInfo->enumChannelSamplesFormat);
	m_nDesSampleRate = pAudioInfo->dwSamplesPerSec;
	m_nDesChannelCount = pAudioInfo->dwChannels;

	AVSampleFormat format = FFmpegFormatCovert::ConvertSamplesFormat(pAudioInfo->enumChannelSamplesFormat);

	int channels = pAudioInfo->dwChannels;
	int sample_rate = pAudioInfo->dwSamplesPerSec;

	bool bSwr = (m_pCodecCtx->channels != channels || m_pCodecCtx->sample_fmt != format ||
		m_pCodecCtx->sample_rate != sample_rate);

	if (!bSwr) 
	{ // 无需重采样直接返回
		return true;
	}

#ifdef DEBUG_USE_RESAMPLER
	m_AudioResampler.InitResampler(FFmpegFormatCovert::ConvertChannelLayout(pAudioInfo->enumAudioCFG), pAudioInfo->enumChannelSamplesFormat, sample_rate,
		m_pCodecCtx->channel_layout, FFmpegFormatCovert::ConvertSamplesFormat(m_pCodecCtx->sample_fmt), m_pCodecCtx->sample_rate, channels, m_pCodecCtx->frame_size);
#else
	SD_UINT64 nChannelLayout = FFmpegFormatCovert::ConvertChannelLayout(pAudioInfo->enumAudioCFG);

	m_pSwrFrame = av_frame_alloc();
	m_pSwrFrame->channels = channels;
	m_pSwrFrame->format = format;
	m_pSwrFrame->sample_rate = sample_rate;
	m_pSwrFrame->channel_layout = nChannelLayout;
	m_pSwrFrame->nb_samples = m_pCodecCtx->frame_size;		// ???

	m_pSwrCtx = swr_alloc_set_opts(m_pSwrCtx, m_pSwrFrame->channel_layout, (AVSampleFormat)m_pSwrFrame->format,
		m_pSwrFrame->sample_rate, m_pCodecCtx->channel_layout, m_pCodecCtx->sample_fmt, m_pCodecCtx->sample_rate, 0, nullptr);

	if (swr_is_initialized(m_pSwrCtx) == 0) {
		swr_init(m_pSwrCtx);
	}
#endif

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
	avpkt.dts = pFrameInfo->qwDTS;
	avpkt.pts = pFrameInfo->qwPTS;
	avpkt.pos = pFrameInfo->dwShowIndex;
	avpkt.duration = pFrameInfo->qwDuration;

	int ret = avcodec_send_packet(m_pCodecCtx, &avpkt);
	if (ret < 0) 
	{
		switch (ret)
		{
		case AVERROR(EAGAIN):
			printf("EAGAIN");
			break;
		case AVERROR_EOF:
			printf("AVERROR_EOF");
			break;
		case AVERROR(EINVAL):
			printf("EINVAL");
			break;
		case AVERROR(ENOMEM):
			printf("ENOMEM");
			break;
		default:
			printf("UNKONWN");
			break;
		}
		av_packet_unref(&avpkt);
		return false;
	}
	av_packet_unref(&avpkt);
	return true;
}

int ecCodecFFmpegAudioDecoder::GetSample(SD_UINT8 *& lpBuffer, SD_UINT32 nSampleNum)
{
	if (!m_pCodecCtx || !m_pSrcFrame) {
		return 0;
	}

	int ret = avcodec_receive_frame(m_pCodecCtx, m_pSrcFrame);
	if (ret < 0) 
	{
		return 0;
	}

	if (nSampleNum != m_nLastSampleNum)
	{
		if (m_pAudioFifo)
		{
			av_audio_fifo_free(m_pAudioFifo);
			m_pAudioFifo = nullptr;
		}
	}

	if (!m_pAudioFifo)
	{
		m_pAudioFifo = av_audio_fifo_alloc(m_emDesSampleFormat, m_nDesChannelCount, nSampleNum);
	}
	if (!m_pAudioFifo)
	{
		//无法获取sample数
		printf("failed to get nb_samples");
		return -1;
	}
	m_nLastSampleNum = nSampleNum;

#ifdef DEBUG_USE_RESAMPLER
	if (m_AudioResampler.IsInitialized())
	{
		if (m_AudioResampler.GetBufferSize() <= 0)
		{
			m_AudioResampler.SetSamplesPerFrame(m_pSrcFrame->nb_samples);
		}
#if 0
		FFmpegFormatCovert::ConvertPDataToBuffer(m_pSrcFrame->data, &m_pSrcFrame->nb_samples, lpBuffer, AVCODEC_MAX_AUDIO_FRAME_SIZE, (AVSampleFormat)m_pSrcFrame->format, 2, m_pSrcFrame->nb_samples);
		if (0)
		{
			FILE * fp_debug = nullptr;
			fopen_s(&fp_debug, "debug.pcm", "ab");
			fwrite(lpBuffer, 1, av_samples_get_buffer_size(nullptr, m_pSrcFrame->channels, m_pSrcFrame->nb_samples, (AVSampleFormat)m_pSrcFrame->format, 1), fp_debug);
			fclose(fp_debug);
		}
		m_AudioResampler.Resample(lpBuffer, m_AudioResampler.GetBufferSize(), lpBuffer);
#else
		int swr_size = m_AudioResampler.Resample(&lpBuffer, AVCODEC_MAX_AUDIO_FRAME_SIZE,
			(const uint8_t **)m_pSrcFrame->data, m_pSrcFrame->nb_samples);
#endif

		av_audio_fifo_write(m_pAudioFifo, (void**)&lpBuffer, swr_size);
	}
#else
	if (m_pSwrCtx && m_pSwrFrame)
	{
		if (m_pSwrFrame->nb_samples == 0)
		{
			m_pSwrFrame->nb_samples = m_pSrcFrame->nb_samples;
			if (av_frame_get_buffer(m_pSwrFrame, 0) < 0)
			{
				av_frame_free(&m_pSwrFrame);
				return 0;
			}
		}
		else
		{
			if (av_frame_get_buffer(m_pSwrFrame, 0) < 0)
			{
				av_frame_free(&m_pSwrFrame);
				return 0;
			}
		}

		int swr_size = swr_convert(m_pSwrCtx, m_pSwrFrame->data, AVCODEC_MAX_AUDIO_FRAME_SIZE,
			(const SD_UINT8**)m_pSrcFrame->data, m_pSrcFrame->nb_samples);

		int bufSizeRet = av_samples_get_buffer_size(NULL, m_pSwrFrame->channels, m_pSwrFrame->nb_samples, (AVSampleFormat)m_pSwrFrame->format, 1);
		memcpy(lpBuffer, m_pSwrFrame->data[0], m_pSwrFrame->linesize[0]);

		return bufSizeRet;
	}
#endif
	else
	{
		av_audio_fifo_write(m_pAudioFifo, (void**)m_pSrcFrame->data, m_pSrcFrame->nb_samples);
	}

	if (av_audio_fifo_size(m_pAudioFifo) >= nSampleNum)
	{
		av_audio_fifo_read(m_pAudioFifo, (void **)&lpBuffer, nSampleNum);
		return nSampleNum;
	}

	return 0;
}

SD_UINT32 ecCodecFFmpegAudioDecoder::GetBufferSize()
{
#ifdef DEBUG_USE_RESAMPLER
	if (m_AudioResampler.IsInitialized())
	{
		return m_AudioResampler.GetBufferSize();
	}
#else
	if (m_pSwrFrame)
	{
		return av_samples_get_buffer_size(nullptr, m_pSwrFrame->channels, m_pSwrFrame->nb_samples, (AVSampleFormat)m_pSwrFrame->format, 1);
	}
#endif
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
		//若打开则在formatctx释放时会崩溃，理论上来说不应该这样，具体原因待查
		//avcodec_free_context(&m_pCodecCtx);
	}
	if (m_pSrcFrame)
	{
		av_frame_free(&m_pSrcFrame);
	}
	if (m_pAudioFifo)
	{
		av_audio_fifo_free(m_pAudioFifo);
		m_pAudioFifo = nullptr;
	}
#ifdef DEBUG_USE_RESAMPLER
	m_AudioResampler.Release();
#else
	if (m_pSwrFrame)
	{
		av_frame_free(&m_pSwrFrame);
	}
	if (m_pSwrCtx)
	{
		swr_close(m_pSwrCtx);
		swr_free(&m_pSwrCtx);
	}
#endif
	m_bIsInitialized = false;
	return true;
}
