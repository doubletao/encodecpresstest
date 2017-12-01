#include "stdafx.h"
#include "IntelEncoder.h"
#include "IntelCodecAPI.h"
#include "IntelVideoEncoder.h"

CIntelVideoEncoder * GetIntelPointer(void * pEncoder)
{
	return static_cast<CIntelVideoEncoder *>(pEncoder);
}

IntelEncoder::IntelEncoder()
	: m_pEncoder(nullptr)
{
	m_pEncoder = new CIntelVideoEncoder;
}


IntelEncoder::~IntelEncoder()
{
	delete GetIntelPointer(m_pEncoder);
	m_pEncoder = nullptr;
}

bool IntelEncoder::InitVideoEncoder(const IntelVideoMediaInfo * pDesVideoInfo)
{
	if (!m_pEncoder || !pDesVideoInfo)
	{
		return false;
	}
	SVideoMediaInfo mediaInfo;
	mediaInfo.dwStruSize = pDesVideoInfo->dwStruSize;
	mediaInfo.dwWidth = pDesVideoInfo->dwWidth;
	mediaInfo.dwHeight = pDesVideoInfo->dwHeight;
	mediaInfo.dwStandardRate = pDesVideoInfo->dwStandardRate;
	mediaInfo.dwStandardScale = pDesVideoInfo->dwStandardScale;
	mediaInfo.dwDataRateInBitsPerSec = pDesVideoInfo->dwDataRateInBitsPerSec;
	mediaInfo.dwGOPSize = pDesVideoInfo->dwGOPSize;
	mediaInfo.dwReferencePeriod = pDesVideoInfo->dwReferencePeriod;
	mediaInfo.bIsClipped = pDesVideoInfo->bIsClipped;
	mediaInfo.dwDisplayWidth = pDesVideoInfo->dwDisplayWidth;
	mediaInfo.dwDisplayHeight = pDesVideoInfo->dwDisplayHeight;
	mediaInfo.dwMaxDataRateInBitsPerSec = pDesVideoInfo->dwMaxDataRateInBitsPerSec;
	mediaInfo.dwMinDataRateInBitsPerSec = pDesVideoInfo->dwMinDataRateInBitsPerSec;
	return GetIntelPointer(m_pEncoder)->InitVideoEncoder(&mediaInfo);;
}

bool IntelEncoder::SetVideoFrameBufInfo(const IntelVideoFrameImageBufInfo * pVideoBufInfo)
{
	if (!m_pEncoder || !pVideoBufInfo)
	{
		return false;
	}
	SVideoFrameImageBufInfo sBuferInfo;
	sBuferInfo.dwXSize = pVideoBufInfo->dwXSize;
	sBuferInfo.dwYSize = pVideoBufInfo->dwYSize;
	sBuferInfo.dwScanXByteSize = pVideoBufInfo->dwScanXByteSize;
	return GetIntelPointer(m_pEncoder)->SetVideoFrameBufInfo(&sBuferInfo);
}

bool IntelEncoder::PutFrame(const unsigned char * pFrameBuffer, const unsigned int nFramaeSize, bool bForceToKeyFrame)
{
	if (!m_pEncoder)
	{
		return false;
	}
	SRFrameInfo info;
	info.iSize = nFramaeSize;
	return GetIntelPointer(m_pEncoder)->PutFrame(pFrameBuffer, &info);
}

bool IntelEncoder::SetEndofInput()
{
	if (!m_pEncoder)
	{
		return false;
	}
	return GetIntelPointer(m_pEncoder)->SetEndofInput();
}

int IntelEncoder::GetCompressFrame(unsigned char *& pFrameBuffer, unsigned int & nFramaeSize)
{
	if (!m_pEncoder)
	{
		return -1;
	}
	SRFrameInfo info;
	if (GetIntelPointer(m_pEncoder)->GetCompressFrame(pFrameBuffer, &info))
	{
		nFramaeSize = info.iSize;
		return nFramaeSize;
	}
	return 0;
}

bool IntelEncoder::Release()
{
	if (!m_pEncoder)
	{
		return false;
	}
	return GetIntelPointer(m_pEncoder)->Release();
}

INTEL_CODEC_API_EXPORT IntelEncoder * CreateIntelEncoder()
{
	IntelEncoder * pEncoder = new IntelEncoder;
	return pEncoder;
}

INTEL_CODEC_API_EXPORT bool DeleteIntelEncoder(IntelEncoder *& pEncoder)
{
	delete pEncoder;
	pEncoder = nullptr;
	return false;
}
