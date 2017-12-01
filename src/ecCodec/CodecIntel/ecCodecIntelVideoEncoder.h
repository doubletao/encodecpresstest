#pragma once
#include "IecCodecVideoEncoder.h"
#include "IntelEncoder.h"

class ecCodecIntelVideoEncoder :
	public IecCodecVideoEncoder
{
public:
	ecCodecIntelVideoEncoder();
	virtual ~ecCodecIntelVideoEncoder();
private:
	IntelEncoder * m_pEncoder;
public:
	virtual bool InitVideoEncoder(const SDVideoMediaInfo *pDesVideoInfo);
	virtual bool SetVideoFrameBufInfo(const SDVideoFrameImageBufInfo *pVideoBufInfo);
	virtual bool PutFrame(const SD_UINT8* pFrameBuffer, const SDRFrameInfo* pFrameInfo, bool bForceToKeyFrame = false);
	virtual bool SetEndofInput();
	virtual int  GetCompressFrame(SD_UINT8* &pFrameBuffer, SDRFrameInfo *pFrameInfo);
	virtual bool Release();
};

