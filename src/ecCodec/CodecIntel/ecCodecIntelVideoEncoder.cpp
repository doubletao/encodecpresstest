#include "ecCodecIntelVideoEncoder.h"

ecCodecIntelVideoEncoder::ecCodecIntelVideoEncoder()
	: m_pEncoder(nullptr)
{
	m_pEncoder = CreateIntelEncoder();
}

ecCodecIntelVideoEncoder::~ecCodecIntelVideoEncoder()
{
	DeleteIntelEncoder(m_pEncoder);
}

bool ecCodecIntelVideoEncoder::InitVideoEncoder(const SDVideoMediaInfo * pDesVideoInfo)
{
	if (!m_pEncoder || !pDesVideoInfo)
	{
		return false;
	}
	IntelVideoMediaInfo mediaInfo;
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
	return m_pEncoder->InitVideoEncoder(&mediaInfo);
}

bool ecCodecIntelVideoEncoder::SetVideoFrameBufInfo(const SDVideoFrameImageBufInfo * pVideoBufInfo)
{
	if (!m_pEncoder || !pVideoBufInfo)
	{
		return false;
	}
	if (pVideoBufInfo->enumColorFormat != SDCOLORFORMAT_UYVY)
	{
		return false;
	}
	IntelVideoFrameImageBufInfo sBuferInfo;
	sBuferInfo.dwXSize = pVideoBufInfo->dwXSize;
	sBuferInfo.dwYSize = pVideoBufInfo->dwYSize;
	sBuferInfo.dwScanXByteSize = pVideoBufInfo->dwScanXByteSize;
	return m_pEncoder->SetVideoFrameBufInfo(&sBuferInfo);
}

bool ecCodecIntelVideoEncoder::PutFrame(const SD_UINT8 * pFrameBuffer, const SDRFrameInfo * pFrameInfo, bool bForceToKeyFrame)
{
	if (!m_pEncoder || !pFrameInfo)
	{
		return false;
	}
	bool bRet = m_pEncoder->PutFrame(pFrameBuffer, pFrameInfo->iSize, bForceToKeyFrame);
	return bRet;
}

bool ecCodecIntelVideoEncoder::SetEndofInput()
{
	if (!m_pEncoder)
	{
		return false;
	}
	return m_pEncoder->SetEndofInput();
}

int ecCodecIntelVideoEncoder::GetCompressFrame(SD_UINT8 *& pFrameBuffer, SDRFrameInfo * pFrameInfo)
{
	if (!m_pEncoder)
	{
		return -1;
	}
	IntelFrameInfo info;
	if (m_pEncoder->GetCompressFrame(pFrameBuffer, &info))
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

bool ecCodecIntelVideoEncoder::Release()
{
	if (!m_pEncoder)
	{
		return false;
	}
	return m_pEncoder->Release();
}
