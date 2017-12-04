#pragma once
#include "IecCodecVideoEncoder.h"
#define EDU_INTEL_CODEC
#ifdef EDU_INTEL_CODEC
#include "IntelEncoder.h"
#else
#include "Intel\pipeline_encode.h"
#endif

class ecCodecIntelVideoEncoder :
	public IecCodecVideoEncoder
{
public:
	ecCodecIntelVideoEncoder();
	virtual ~ecCodecIntelVideoEncoder();
private:
#ifdef EDU_INTEL_CODEC
	IntelEncoder * m_pEncoder;
#else
	CEncodingPipeline * m_pEncodingPipeline;
#endif
public:
	virtual bool InitVideoEncoder(const SDVideoMediaInfo *pDesVideoInfo);
	virtual bool SetVideoFrameBufInfo(const SDVideoFrameImageBufInfo *pVideoBufInfo);
	virtual bool PutFrame(const SD_UINT8* pFrameBuffer, const SDRFrameInfo* pFrameInfo, bool bForceToKeyFrame = false);
	virtual bool SetEndofInput();
	virtual int  GetCompressFrame(SD_UINT8* &pFrameBuffer, SDRFrameInfo *pFrameInfo);
	virtual bool Release();
};
