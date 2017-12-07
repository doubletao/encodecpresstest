#pragma once
#include "ecCodec.h"
class IecCodecScaler
{
public:
	virtual ~IecCodecScaler() {}

	// 初始化格式转换
	// pSrcVideoInfo: 视频源格式描述
	virtual bool InitScaler(SD_UINT32 nSrcWidth, SD_UINT32 nSrcHeight, SD_COLOR_FORMAT emSrcColorFormat, SD_UINT32 nDesWidth, SD_UINT32 nDesHeight, SD_COLOR_FORMAT emDesColorFormat) = 0;

	// 设置输出视频格式
	// pOutBufInfo:解码输出帧参数
	virtual bool Scale(SD_UINT8 * pInBuf, SD_UINT8 * pOutBuf) = 0;

	virtual bool IsInitialized() = 0;
	virtual SD_UINT32 GetBufferSize() = 0;
	virtual bool Release() = 0;
};

