#include "ecCodecFFmpegResampler.h"
#include "FFmpegFormatConverter.h"
#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "avutil.lib")
#pragma comment(lib, "swresample.lib")


ecCodecFFmpegResampler::ecCodecFFmpegResampler()
	: m_pSwrCtx(nullptr)
	, m_pSwrFrame(nullptr)
	, m_bIsInitialized(false)
{
}


ecCodecFFmpegResampler::~ecCodecFFmpegResampler()
{
	Release();
}

bool ecCodecFFmpegResampler::InitResampler(SD_UINT64 nDesChannelLayout, SD_CHANNELSAMPLE_FORMAT emDesSampleFormat, SD_INT32 nDesSampleRate, SD_UINT64 nSrcChannelLayout, SD_CHANNELSAMPLE_FORMAT emSrcSampleFormat, SD_INT32 nSrcSampleRate, SD_INT32 nChannelCount, SD_INT32 nSamplesPerFrame)
{
	m_nDesChannelLayout = nDesChannelLayout;
	m_emDesSampleFormat = emDesSampleFormat;
	m_nDesSampleRate = nDesSampleRate;
	m_nSrcChannelLayout = nSrcChannelLayout;
	m_emSrcSampleFormat = emSrcSampleFormat;
	m_nSrcSampleRate = nSrcSampleRate;
	m_nChannelCount = nChannelCount;
	m_nSamplesPerFrame = nSamplesPerFrame;
	Release();
	m_pSwrFrame = av_frame_alloc();
	if (m_pSwrFrame)
	{
		m_pSwrFrame->channels = nChannelCount;
		m_pSwrFrame->format = FFmpegFormatCovert::ConvertSamplesFormat(emDesSampleFormat);
		m_pSwrFrame->sample_rate = nDesSampleRate;
		m_pSwrFrame->channel_layout = nDesChannelLayout;
		m_pSwrFrame->nb_samples = nSamplesPerFrame;

		m_pSwrCtx = swr_alloc_set_opts(m_pSwrCtx, m_pSwrFrame->channel_layout, (AVSampleFormat)m_pSwrFrame->format,
			m_pSwrFrame->sample_rate, nSrcChannelLayout, FFmpegFormatCovert::ConvertSamplesFormat(emSrcSampleFormat), nSrcSampleRate, 0, nullptr);
		if (m_pSwrCtx)
		{
			if (swr_is_initialized(m_pSwrCtx) == 0) 
			{
				if (swr_init(m_pSwrCtx) >= 0)
				{
					if (m_pSwrFrame->nb_samples > 0)
					{
						if (av_frame_get_buffer(m_pSwrFrame, 0) < 0)
						{
							av_frame_free(&m_pSwrFrame);
						}
						m_bIsInitialized = true;
					}
					return true;
				}
			}
		}
	}
	return false;
}

bool ecCodecFFmpegResampler::SetSamplesPerFrame(SD_INT32 nSamplesPerFrame)
{
	if (m_pSwrFrame && m_pSwrFrame->nb_samples == 0)
	{
		m_pSwrFrame->nb_samples = nSamplesPerFrame;
		m_nSamplesPerFrame = nSamplesPerFrame;
		if (av_frame_get_buffer(m_pSwrFrame, 0) < 0)
		{
			av_frame_free(&m_pSwrFrame);
			return false;
		}
		return true;
	}
	return false;
}

SD_INT32 ecCodecFFmpegResampler::Resample(uint8_t ** out, int out_count, const uint8_t ** in, int in_count)
{
	if (m_bIsInitialized)
	{
		return swr_convert(m_pSwrCtx, out, out_count, in, in_count);
	}
	return 0;
}

SD_INT32 ecCodecFFmpegResampler::Resample(SD_UINT8 * pInBuf, SD_INT32 nBufSize, SD_UINT8 * pOutBuf)
{
	if (m_pSwrFrame->nb_samples == 0)
	{
		return 0;
	}

	int bufSizeRet = 0;
	AVFrame* pFrame = av_frame_alloc();
	if (pFrame)
	{
		pFrame->channels = m_nChannelCount;
		pFrame->format = FFmpegFormatCovert::ConvertSamplesFormat(m_emSrcSampleFormat);
		pFrame->sample_rate = m_nSrcSampleRate;
		pFrame->channel_layout = m_nSrcChannelLayout;
		pFrame->nb_samples = m_nSamplesPerFrame;
		if (pFrame->nb_samples > 0)
		{
			if (av_frame_get_buffer(pFrame, 0) < 0)
			{
				av_frame_free(&pFrame);
			}
			else
			{
				FFmpegFormatCovert::ConvertBufferToPData(pInBuf, nullptr, pFrame->data, pFrame->linesize, (AVSampleFormat)pFrame->format, m_nChannelCount, m_nSamplesPerFrame);
				Resample(&pOutBuf, AVCODEC_MAX_AUDIO_FRAME_SIZE, (const uint8_t **)pFrame->data, pFrame->nb_samples);
				bufSizeRet = GetBufferSize();
			}
		}
		if (pFrame)
		{
			av_frame_free(&pFrame);
		}
	}

	return bufSizeRet;
}

bool ecCodecFFmpegResampler::IsInitialized()
{
	return m_bIsInitialized;
}

SD_UINT32 ecCodecFFmpegResampler::GetBufferSize()
{
	if (m_pSwrFrame && m_pSwrFrame->nb_samples > 0)
	{
		return av_samples_get_buffer_size(nullptr, m_pSwrFrame->channels, m_pSwrFrame->nb_samples, (AVSampleFormat)m_pSwrFrame->format, 1);
	}
	return 0;
}

bool ecCodecFFmpegResampler::Release()
{
	if (m_pSwrFrame)
	{
		av_frame_free(&m_pSwrFrame);
	}
	if (m_pSwrCtx)
	{
		swr_close(m_pSwrCtx);
		swr_free(&m_pSwrCtx);
	}
	m_bIsInitialized = false;
	return true;
}
