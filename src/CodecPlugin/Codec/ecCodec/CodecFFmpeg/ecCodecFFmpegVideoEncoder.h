#pragma once
#include "IecCodecVideoEncoder.h"
#include "ecCodecFFmpegScaler.h"
#include <memory>
extern "C"
{
#include "libavutil\pixfmt.h"
#include "libavformat\avformat.h"
#include "libavutil\imgutils.h"
#include "libavutil/opt.h"
}

class ecCodecFFmpegVideoEncoder :
	public IecCodecVideoEncoder
{
public:
	ecCodecFFmpegVideoEncoder();
	virtual ~ecCodecFFmpegVideoEncoder();
private:
	int m_extradataSize;
	AVFrame* m_pSourceFrame;
	AVFrame* m_pScaleFrame;
	SD_INT64 m_pts;
	AVCodecContext* m_pCodecCtx;
	SwsContext* m_pSwsCtx;
	std::unique_ptr<SD_UINT8[]> m_pDestBuffer;
public:
	virtual bool InitVideoEncoder(const SDVideoMediaInfo *pDesVideoInfo);
	virtual bool SetVideoFrameBufInfo(const SDVideoFrameImageBufInfo *pVideoBufInfo);
	virtual bool PutFrame(const SD_UINT8* pFrameBuffer, const SDRFrameInfo* pFrameInfo, bool bForceToKeyFrame = false);
	virtual bool SetEndofInput();
	virtual int  GetCompressFrame(SD_UINT8* &pFrameBuffer, SDRFrameInfo *pFrameInfo);
	virtual bool Release();
	AVCodecContext* GetCodecContext() const;
};

