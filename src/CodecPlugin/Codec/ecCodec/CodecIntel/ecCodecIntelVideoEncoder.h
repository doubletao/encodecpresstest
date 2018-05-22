#pragma once
#include "IecCodecVideoEncoder.h"

class CEncodingPipeline;
struct sInputParams;

class ecCodecIntelVideoEncoder :
	public IecCodecVideoEncoder
{
private:
	CEncodingPipeline    *m_pVideoEncoder;
	sInputParams		*m_Params;
	bool                 m_IsHeade;
public:
	ecCodecIntelVideoEncoder();
	virtual ~ecCodecIntelVideoEncoder();
protected:
	bool SWMediaInfoIntoParams(const SDVideoMediaInfo *pVideoMediaInfo);
public:
	virtual bool InitVideoEncoder(const SDVideoMediaInfo *pDesVideoInfo);
	virtual bool SetVideoFrameBufInfo(const SDVideoFrameImageBufInfo *pVideoBufInfo);
	virtual bool PutFrame(const SD_UINT8* pFrameBuffer, const SDRFrameInfo* pFrameInfo, bool bForceToKeyFrame = false);
	virtual bool SetEndofInput();
	virtual int  GetCompressFrame(SD_UINT8* &pFrameBuffer, SDRFrameInfo *pFrameInfo);
	virtual bool Release();
};
