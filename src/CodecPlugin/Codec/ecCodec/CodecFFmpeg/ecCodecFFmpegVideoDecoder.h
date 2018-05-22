#pragma once
#include "IecCodecVideoDecoder.h"
#include "ecCodecFFmpegScaler.h"
extern "C"
{
#include "libavutil\pixfmt.h"
#include "libavformat\avformat.h"
#include "libavutil\imgutils.h"
}


class ecCodecFFmpegVideoDecoder :
	public IecCodecVideoDecoder
{
private:
	bool m_bIsInitialized;
	AVCodecContext * m_pCodecCtx;
	ecCodecFFmpegScaler m_VideoScaler;
	AVFrame	* m_pFrame;
	int m_nSrcWidth;
	int m_nSrcHeight;
	int m_nDesWidth;
	int m_nDesHeight;
	SD_COLOR_FORMAT m_emDesColorFormat;
public:
	ecCodecFFmpegVideoDecoder();
	virtual ~ecCodecFFmpegVideoDecoder();
public:
	virtual bool InitVideoDecoder(const SDVideoMediaInfo & pSrcVideoInfo);
	virtual bool InitVideoDecoder(AVCodecContext * pCodecCtx, AVCodec * pVideoCodec);
	virtual bool PutVideoFrame(const SD_UINT8 *pFrameBuffer, const SDRFrameInfo *pFrameInfo);
	virtual bool SetEndofInput();
	virtual int GetUnCompressFrame(SD_UINT8* &lpFrameBuffer, SDRFrameInfo *pFrameInfo);
	virtual bool GetVideoMediaInfo(SDVideoMediaInfo * mediaInfo);
	virtual bool SetVideoFrameBufInfo(const SDVideoFrameImageBufInfo *pOutBufInfo);
	virtual double GetCurrentMilSecTimestamp(int num, int den, uint64_t nStartTm);
	virtual bool IsInitialized();
	virtual SD_UINT32 GetBufferSize();
	virtual bool Release();
};

