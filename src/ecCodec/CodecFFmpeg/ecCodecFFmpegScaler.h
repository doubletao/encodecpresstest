#pragma once
#include "IecCodecScaler.h"

extern "C"
{
#include "libswscale\swscale.h"
#include "libavutil\imgutils.h"
#include "libavformat\avformat.h"
}

class ecCodecFFmpegScaler :
	public IecCodecScaler
{
private:
	bool m_bInitialized;
	SD_UINT32 m_nSrcWidth;
	SD_UINT32 m_nSrcHeight;
	AVPixelFormat m_emSrcPixFmt;
	SD_UINT32 m_nDesWidth;
	SD_UINT32 m_nDesHeight;
	AVPixelFormat m_emDesPixFmt;
	SwsContext* m_pScaleCtx;
	AVFrame	* m_pScaleFrame;
public:
	ecCodecFFmpegScaler();
	virtual ~ecCodecFFmpegScaler();
public:
	virtual bool InitScaler(SD_UINT32 nSrcWidth, SD_UINT32 nSrcHeight, SD_COLOR_FORMAT emSrcColorFormat, SD_UINT32 nDesWidth, SD_UINT32 nDesHeight, SD_COLOR_FORMAT emDesColorFormat);
	bool ResetScalerSrcWH(SD_UINT32 nSrcWidth, SD_UINT32 nSrcHeight);
	virtual bool Scale(SD_UINT8 * pInBuf, SD_UINT8 * pOutBuf);
	bool Scale(uint8_t ** pInData, const int srcStride[], uint8_t **& pOutData);
	int * GetDesLineSize();
	virtual bool IsInitialized();
	virtual SD_UINT32 GetBufferSize();
	virtual bool Release();
};

