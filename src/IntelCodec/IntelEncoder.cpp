#include "stdafx.h"
#include "IntelEncoder.h"
#include "IntelCodecAPI.h"
#include "IntelVideoEncoder.h"

CIntelVideoEncoderCPUHW * GetIntelPointer(void * pEncoder)
{
	return static_cast<CIntelVideoEncoderCPUHW *>(pEncoder);
}

IntelEncoder::IntelEncoder()
	: m_pEncoder(nullptr)
{
	m_pEncoder = new CIntelVideoEncoderCPUHW;
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
	mediaInfo.enumVideoType = VIDEOTYPE_H264;
	mediaInfo.enumColorFormat = COLORFORMAT_YUVP_NV12;
	bool bRet = GetIntelPointer(m_pEncoder)->Init(&mediaInfo);
	return bRet;
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
	sBuferInfo.enumColorFormat = COLORFORMAT_UYVY;
	sBuferInfo.enumScanMode = VIDEOSCANMODE_FirstFieldTop;
	return GetIntelPointer(m_pEncoder)->SetInfo(&sBuferInfo);
}

bool IntelEncoder::PutFrame(const unsigned char * pFrameBuffer, const unsigned int nFramaeSize, bool bForceToKeyFrame)
{
	if (!m_pEncoder)
	{
		return false;
	}
	if (true)
	{
		FILE * file;
		fopen_s(&file, "scaled.yuv", "wb");
		if (file)
		{
			fwrite(pFrameBuffer, 1, nFramaeSize, file);  //V
			fclose(file);
		}
	}
	SRFrameInfo info;
	info.iSize = nFramaeSize;
	bool bRet = GetIntelPointer(m_pEncoder)->PutFrame(pFrameBuffer, &info);
	return bRet;
}

bool IntelEncoder::SetEndofInput()
{
	if (!m_pEncoder)
	{
		return false;
	}
	return false;
}

int IntelEncoder::GetCompressFrame(unsigned char *& pFrameBuffer, IntelFrameInfo * pFrameInfo)
{
	if (!m_pEncoder)
	{
		return -1;
	}
	SRFrameInfo info;
	if (GetIntelPointer(m_pEncoder)->GetFrame(pFrameBuffer, &info))
	{
		if (pFrameInfo)
		{
			pFrameInfo->iVersion = info.iVersion;
			pFrameInfo->iSize = info.iSize;
			pFrameInfo->dwFrameIndex = info.dwFrameIndex;
			pFrameInfo->dwFrameNum = info.dwFrameNum;
			pFrameInfo->iSamplesOffset = info.iSamplesOffset;
			pFrameInfo->qwDTS = info.qwDTS;
			pFrameInfo->qwPTS = info.qwPTS;
			pFrameInfo->qwDuration = info.qwDuration;
			pFrameInfo->dwShowIndex = info.dwShowIndex;
			pFrameInfo->extradata_size = info.extradata_size;
		}
		return info.iSize;
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
