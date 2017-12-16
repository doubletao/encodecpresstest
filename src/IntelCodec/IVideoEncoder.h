#ifndef __H__IVIDEOENCODER__H__
#define __H__IVIDEOENCODER__H__

#include "VACommonDefine.h"
//-----------------------------------------------------------------------------------------------//
class IVideoEncoder
{
public:
	IVideoEncoder() {};
	virtual ~IVideoEncoder() {};
	virtual bool Init(const SVideoMediaInfo *pDesVideoInfo) = 0;
	virtual bool SetInfo(const SVideoFrameImageBufInfo *pVideoBufInfo) = 0;
	virtual bool PutFrame(const SW_UINT8* pFrameBuffer, const SRFrameInfo* pFrameInfo, bool bForceToKeyFrame = false) = 0;virtual bool GetEnd() = 0;
	virtual bool GetFrame(SW_UINT8* &pFrameBuffer, SRFrameInfo *pFrameInfo) = 0;
	virtual bool Release() = 0;
};

#endif 