#pragma once
#include "IecCodecVideoEncoder.h"
#include "ecCodecFFmpegScaler.h"
extern "C"
{
#include "libavutil\pixfmt.h"
#include "libavformat\avformat.h"
#include "libavutil\imgutils.h"
}

class ecCodecFFmpegVideoEncoder :
	public IecCodecVideoEncoder
{
public:
	ecCodecFFmpegVideoEncoder();
	virtual ~ecCodecFFmpegVideoEncoder();
private:
	AVFrame* m_pSourceFrame;
	SD_INT64 m_pts;
	AVCodecContext * m_pCodecCtx;
public:
	virtual bool InitVideoEncoder(const SDVideoMediaInfo *pDesVideoInfo);
	virtual bool SetVideoFrameBufInfo(const SDVideoFrameImageBufInfo *pVideoBufInfo);
	virtual bool PutFrame(const SD_UINT8* pFrameBuffer, const SDRFrameInfo* pFrameInfo, bool bForceToKeyFrame = false);
	virtual bool SetEndofInput();
	virtual bool GetCompressFrame(SD_UINT8* &pFrameBuffer, SDRFrameInfo *pFrameInfo);
	virtual bool Release();
};

