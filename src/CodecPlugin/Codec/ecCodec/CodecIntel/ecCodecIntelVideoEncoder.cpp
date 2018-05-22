#include "ecCodecIntelVideoEncoder.h"
#include "IntelSample/PipelineEncode.h"

ecCodecIntelVideoEncoder::ecCodecIntelVideoEncoder()
	: m_pVideoEncoder(nullptr)
	, m_Params(nullptr)
{
}

ecCodecIntelVideoEncoder::~ecCodecIntelVideoEncoder()
{
	Release();
}

bool ecCodecIntelVideoEncoder::SWMediaInfoIntoParams(const SDVideoMediaInfo * pVideoMediaInfo)
{
	switch (pVideoMediaInfo->enumVideoType)
	{
	case SDVIDEOTYPE_H264_INTEL:
	case SDVIDEOTYPE_H264:
		m_Params->CodecId = MFX_CODEC_AVC;
		if (pVideoMediaInfo->dwVideoSubType == PROFILE_AVC_BASELINE)
		{
			m_Params->nCodecProfile = MFX_PROFILE_AVC_BASELINE;
		}
		else if (pVideoMediaInfo->dwVideoSubType == PROFILE_AVC_MAIN)
		{
			m_Params->nCodecProfile = MFX_PROFILE_AVC_MAIN;
		}
		else
			m_Params->nCodecProfile = MFX_PROFILE_AVC_HIGH;
		break;
	case SDVIDEOTYPE_MPEG2_IFRAME:
	{
		m_Params->CodecId = MFX_CODEC_MPEG2;
		m_Params->nGopRefDist = 1;
	}
	break;
	case SDVIDEOTYPE_MPEG2_IBP:
		m_Params->CodecId = MFX_CODEC_MPEG2;
		break;
	case SDVIDEOTYPE_H265:
		return false;
	default:
		return false;
	}

	switch (pVideoMediaInfo->enumScanMode)
	{
	case SDVIDEOSCANMODE_Progressive:
		m_Params->nPicStruct = MFX_PICSTRUCT_PROGRESSIVE;
		break;
	case SDVIDEOSCANMODE_FirstFieldTop:
		m_Params->nPicStruct = MFX_PICSTRUCT_FIELD_TFF;
		break;
	case SDVIDEOSCANMODE_SecondFieldTop:
		m_Params->nPicStruct = MFX_PICSTRUCT_FIELD_BFF;
	}

	if (pVideoMediaInfo->dwWidth > 0 && pVideoMediaInfo->dwHeight > 0 && pVideoMediaInfo->dwDataRateInBitsPerSec > 0 &&
		pVideoMediaInfo->dwStandardRate > 0 && pVideoMediaInfo->dwGOPSize > 0)
	{
		m_Params->nDstWidth = pVideoMediaInfo->dwWidth;
		m_Params->nDstHeight = pVideoMediaInfo->dwHeight;
		m_Params->nTargetUsage = pVideoMediaInfo->dwH264EncoderLevel;
		if (m_Params->nTargetUsage < 1)
		{
			m_Params->nTargetUsage = 1;
		}
		if (m_Params->nTargetUsage > 7)
		{
			m_Params->nTargetUsage = 7;
		}
		m_Params->nBitRate = pVideoMediaInfo->dwDataRateInBitsPerSec / 1000;
		m_Params->dFrameRate = pVideoMediaInfo->dwStandardRate;
		m_Params->ColorFormat = MFX_FOURCC_NV12;
		m_Params->bd3dAlloc = false;
		m_Params->bUseHWLib = true;
		m_Params->RateControlMethod = pVideoMediaInfo->enumDataRateType;
		m_Params->nGopPicSize = pVideoMediaInfo->dwGOPSize;
	}
	else
		return false;

	return true;
}

bool ecCodecIntelVideoEncoder::InitVideoEncoder(const SDVideoMediaInfo * pDesVideoInfo)
{
	if (m_pVideoEncoder || m_Params)
	{
		return false;
	}
	m_pVideoEncoder = new CEncodingPipeline();
	m_Params = new sInputParams();
	if (m_pVideoEncoder && m_Params)
	{
		return SWMediaInfoIntoParams(pDesVideoInfo);
	}
	else
		return false;
}

bool ecCodecIntelVideoEncoder::SetVideoFrameBufInfo(const SDVideoFrameImageBufInfo * pVideoBufInfo)
{
	m_Params->nWidth = pVideoBufInfo->dwXSize;
	m_Params->nHeight = pVideoBufInfo->dwYSize;
	mfxStatus status = m_pVideoEncoder->Init(m_Params);
	if (status != MFX_ERR_NONE)
	{
		return false;
	}
	else
		return true;
}

bool ecCodecIntelVideoEncoder::PutFrame(const SD_UINT8 * pFrameBuffer, const SDRFrameInfo * pFrameInfo, bool bForceToKeyFrame)
{
	if (pFrameBuffer)
	{
		mfxStatus status = m_pVideoEncoder->PutVideo((uint8_t*)pFrameBuffer);
		if (status != MFX_ERR_NONE)
		{
			return false;
		}
	}
	else
		return false;
	return true;
}

bool ecCodecIntelVideoEncoder::SetEndofInput()
{
	if (m_pVideoEncoder)
	{
		mfxStatus sts = MFX_ERR_NONE;
		sts = m_pVideoEncoder->SynchronizeFirstTask();
		if (MFX_ERR_NONE == sts)
			return true;
		else
			return false;
	}
	return false;
}

int ecCodecIntelVideoEncoder::GetCompressFrame(SD_UINT8 *& pFrameBuffer, SDRFrameInfo * pFrameInfo)
{
	if (pFrameInfo && m_pVideoEncoder->m_pVideoFrameInfo.dwFrameIndex > 0)
	{
		pFrameBuffer = (uint8_t *)m_pVideoEncoder->m_Data;
		pFrameInfo->iSize = m_pVideoEncoder->m_pVideoFrameInfo.iSize;
		pFrameInfo->emDataType = m_pVideoEncoder->m_pVideoFrameInfo.emDataType;
		pFrameInfo->emFrameType = m_pVideoEncoder->m_pVideoFrameInfo.emFrameType;
		pFrameInfo->dwFrameIndex = m_pVideoEncoder->m_pVideoFrameInfo.dwFrameIndex;
		pFrameInfo->dwShowIndex = m_pVideoEncoder->m_pVideoFrameInfo.dwShowIndex;
		pFrameInfo->qwDTS = m_pVideoEncoder->m_pVideoFrameInfo.dwFrameIndex;
		pFrameInfo->qwPTS = m_pVideoEncoder->m_pVideoFrameInfo.dwShowIndex;
		return pFrameInfo->iSize;
	}
	else
		return 0;
}

bool ecCodecIntelVideoEncoder::Release()
{
	if (m_pVideoEncoder)
	{
		m_pVideoEncoder->Close();
		delete m_pVideoEncoder;
		m_pVideoEncoder = NULL;
	}
	if (m_Params)
	{
		delete m_Params;
		m_Params = NULL;
	}

	return true;
}
