#pragma once
#include "IecCodecResampler.h"

extern "C"
{
#include "libavutil\pixfmt.h"
#include "libavformat\avformat.h"
#include "libavutil\imgutils.h"
#include "libswresample\swresample.h"
}

class ecCodecFFmpegResampler :
	public IecCodecResampler
{
private:
	SD_UINT64 m_nDesChannelLayout;
	SD_CHANNELSAMPLE_FORMAT m_emDesSampleFormat;
	SD_INT32 m_nDesSampleRate;
	SD_UINT64 m_nSrcChannelLayout;
	SD_CHANNELSAMPLE_FORMAT m_emSrcSampleFormat;
	SD_INT32 m_nSrcSampleRate;
	SD_INT32 m_nChannelCount;
	SD_INT32 m_nSamplesPerFrame;

	AVFrame*		m_pSwrFrame;
	SwrContext*		m_pSwrCtx;
	bool m_bIsInitialized;
public:
	ecCodecFFmpegResampler();
	virtual ~ecCodecFFmpegResampler();
public:
	virtual bool InitResampler(SD_UINT64 nDesChannelLayout, SD_CHANNELSAMPLE_FORMAT emDesSampleFormat, SD_INT32 nDesSampleRate,
		SD_UINT64 nSrcChannelLayout, SD_CHANNELSAMPLE_FORMAT emSrcSampleFormat, SD_INT32 nSrcSampleRate, SD_INT32 nChannelCount = 2, SD_INT32 nSamplesPerFrame = 0);
	virtual bool SetSamplesPerFrame(SD_INT32 nSamplesPerFrame);
	SD_INT32 Resample(uint8_t **out, int out_count, const uint8_t **in, int in_count);
	virtual SD_INT32 Resample(SD_UINT8 * pInBuf, SD_UINT8 * pOutBuf);
	virtual bool IsInitialized();
	virtual SD_UINT32 GetBufferSize();
	virtual bool Release();
};

