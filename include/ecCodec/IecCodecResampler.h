#pragma once
#include "ecCodec.h"
class EASY_CODEC_API_EXPORT IecCodecResampler
{
public:
	// 初始化重采样
	virtual bool InitResampler(SD_UINT64 nDesChannelLayout, SD_CHANNELSAMPLE_FORMAT emDesSampleFormat, SD_INT32 nDesSampleRate,
		SD_UINT64 nSrcChannelLayout, SD_CHANNELSAMPLE_FORMAT emSrcSampleFormat, SD_INT32 nSrcSampleRate, SD_INT32 nChannelCount = 2, SD_INT32 nSamplesPerFrame = 0) = 0;
	
	virtual bool SetSamplesPerFrame(SD_INT32 nSamplesPerFrame) = 0;

	// 设置输出视频格式
	// pOutBufInfo:解码输出帧参数
	virtual SD_INT32 Resample(SD_UINT8 * pInBuf, SD_INT32 nBufSize, SD_UINT8 * pOutBuf) = 0;

	virtual bool IsInitialized() = 0;
	virtual SD_UINT32 GetBufferSize() = 0;
	virtual bool Release() = 0;
};

