//#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "ecCodecFactory.h"
#include "SDVADefine.h"
#include "SDVADefineEx.h"
#include "CodecFFmpeg\ecCodecFFmpegProtocolDecoder.h"
#include "CodecFFmpeg\ecCodecFFmpegProtocolEncoder.h"
#include "CodecFFmpeg\ecCodecFFmpegVideoDecoder.h"
#include "CodecFFmpeg\ecCodecFFmpegVideoEncoder.h"
#include "CodecFFmpeg\ecCodecFFmpegAudioDecoder.h"
#include "CodecFFmpeg\ecCodecFFmpegAudioEncoder.h"
#include "CodecIntel\ecCodecIntelProtocolEncoder.h"
#include "CodecIntel\ecCodecIntelVideoEncoder.h"

void ecCodecFactory::logFF(void *, int level, const char * fmt, va_list ap)
{
	char log[2048];
	vsnprintf_s(log, 512, fmt, ap);
	OutputDebugStringA(log);
	OutputDebugStringA("\n");
}

ecCodecFactory::ecCodecFactory()
{
	InitializeCriticalSection(&m_Log_lock);
	av_log_set_level(AV_LOG_ERROR);
	av_log_set_callback(ecCodecFactory::logFF);
}

ecCodecFactory::~ecCodecFactory()
{
	DeleteCriticalSection(&m_Log_lock);
}

IecCodecProtocolDecoder * ecCodecFactory::GetProtocolDecoder(EmCodecProvider emCodecProvider)
{
	IecCodecProtocolDecoder * pProtocolDecoder = nullptr;
	switch (emCodecProvider)
	{
	case EMCodec_FFmpeg:
	{
		av_register_all();
		pProtocolDecoder = new ecCodecFFmpegProtocolDecoder;
	}
		break;
	case EMCodec_Intel:
		break;
	default:
		break;
	}
	return pProtocolDecoder;
}

IecCodecProtocolEncoder * ecCodecFactory::GetProtocolEncoder(EmCodecProvider emCodecProvider)
{
	IecCodecProtocolEncoder * pProtocolEncoder = nullptr;
	switch (emCodecProvider)
	{
	case EMCodec_FFmpeg:
	{
		av_register_all();
		pProtocolEncoder = new ecCodecFFmpegProtocolEncoder;
	}
	break;
	case EMCodec_Intel:
		pProtocolEncoder = new ecCodecIntelProtocolEncoder;
		break;
	default:
		break;
	}
	return pProtocolEncoder;
}

IecCodecVideoDecoder * ecCodecFactory::GetVideoDecoder(EmCodecProvider emCodecProvider)
{
	IecCodecVideoDecoder * pVideoDecoder = nullptr;
	switch (emCodecProvider)
	{
	case EMCodec_FFmpeg:
	{
		av_register_all();
		pVideoDecoder = new ecCodecFFmpegVideoDecoder;
	}
	break;
	case EMCodec_Intel:
		break;
	default:
		break;
	}
	return pVideoDecoder;
}

IecCodecVideoEncoder * ecCodecFactory::GetVideoEncoder(EmCodecProvider emCodecProvider)
{
	IecCodecVideoEncoder * pVideoEncoder = nullptr;
	switch (emCodecProvider)
	{
	case EMCodec_FFmpeg:
	{
		av_register_all();
		pVideoEncoder = new ecCodecFFmpegVideoEncoder;
	}
	break;
	case EMCodec_Intel:
		pVideoEncoder = new ecCodecIntelVideoEncoder;
		break;
	default:
		break;
	}
	return pVideoEncoder;
}

IecCodecAudioDecoder * ecCodecFactory::GetAudioDecoder(EmCodecProvider emCodecProvider)
{
	IecCodecAudioDecoder * pAudioDecoder = nullptr;
	switch (emCodecProvider)
	{
	case EMCodec_FFmpeg:
	{
		av_register_all();
		pAudioDecoder = new ecCodecFFmpegAudioDecoder;
	}
	break;
	case EMCodec_Intel:
		break;
	default:
		break;
	}
	return pAudioDecoder;
}

IecCodecAudioEncoder * ecCodecFactory::GetAudioEncoder(EmCodecProvider emCodecProvider)
{
	IecCodecAudioEncoder * pAudioEncoder = nullptr;
	switch (emCodecProvider)
	{
	case EMCodec_FFmpeg:
	{
		av_register_all();
		pAudioEncoder = new ecCodecFFmpegAudioEncoder;
	}
	break;
	case EMCodec_Intel:
		break;
	default:
		break;
	}
	return pAudioEncoder;
}

bool ecCodecFactory::DeleteProtocolEncoder(IecCodecProtocolEncoder *& pObj)
{
	pObj->Release();
	delete pObj;
	pObj = nullptr;
	return true;
}

bool ecCodecFactory::DeleteVideoDecoder(IecCodecVideoDecoder *& pObj)
{
	pObj->Release();
	delete pObj;
	pObj = nullptr;
	return true;
}

bool ecCodecFactory::DeleteVideoEncoder(IecCodecVideoEncoder *& pObj)
{
	pObj->Release();
	delete pObj;
	pObj = nullptr;
	return true;
}

bool ecCodecFactory::DeleteAudioDecoder(IecCodecAudioDecoder *& pObj)
{
	pObj->Release();
	delete pObj;
	pObj = nullptr;
	return true;
}

bool ecCodecFactory::DeleteAudioEncoder(IecCodecAudioEncoder *& pObj)
{
	pObj->Release();
	delete pObj;
	pObj = nullptr;
	return true;
}

bool ecCodecFactory::DeleteProtocolDecoder(IecCodecProtocolDecoder *& pObj)
{
	pObj->Release();
	delete pObj;
	pObj = nullptr;
	return true;
}

EASY_CODEC_API_EXPORT	IecCodecFactory * ecCodec_CreateCodecFactory()
{
	IecCodecFactory * pCodecFactory = new ecCodecFactory;
	return pCodecFactory;
}
EASY_CODEC_API_EXPORT bool ecCodec_ReleaseCodecFactory(IecCodecFactory *& pCodecFactory)
{
	delete pCodecFactory;
	pCodecFactory = nullptr;
	return true;
}

LPCTSTR GetPresetMediaInfo(SD_VIDEO_STANDARD emVideoStandard, SD_VIDEO_TYPE emVideoType, SD_COLOR_FORMAT emColorFormat, SD_AUDIO_TYPE emAudioType, DWORD dwSamplePerSec, int nH264Level, OUT SDStreamMediaInfo & streamInfo)
{
	switch (emVideoStandard)
	{
	case SDVIDEOSTANDARD_PAL:
		streamInfo.sVideoMediaInfo.dwWidth = 720;////////////////////////////////////////////////////////////////////////////
		streamInfo.sVideoMediaInfo.dwHeight = 576;////////////////////////////////////////////////////////////////////////////
		streamInfo.sVideoMediaInfo.dwStandardRate = 25;////////////////////////////////////////////////////////////////////////////
		streamInfo.sVideoMediaInfo.dwStandardScale = 1;////////////////////////////////////////////////////////////////////////////
		streamInfo.sVideoMediaInfo.dwDisplayWidth = 4;////////////////////////////////////////////////////////////////////////////
		streamInfo.sVideoMediaInfo.dwDisplayHeight = 3;////////////////////////////////////////////////////////////////////////////
		streamInfo.sVideoMediaInfo.enumColorPrimaries = SDCOLORPRIMARIES_ITU_R470_2BG;			// 源基色的色度坐标(ISO13818-2)
		streamInfo.sVideoMediaInfo.enumColorTransfer = SDCOLORTRANSFER_ITU_R470_2BG;			// 光电转换特性(ISO13818-2)
		streamInfo.sVideoMediaInfo.enumColorMatrix = SDCOLORMATRIX_ITU_R470_2BG;			// 颜色空间变换系数(ISO13818-2)
		streamInfo.sVideoMediaInfo.dwDataRateInBitsPerSec = 50000000;
		break;
	case SDVIDEOSTANDARD_HD1080i_25:
		streamInfo.sVideoMediaInfo.dwWidth = 1920;////////////////////////////////////////////////////////////////////////////
		streamInfo.sVideoMediaInfo.dwHeight = 1080;////////////////////////////////////////////////////////////////////////////
		streamInfo.sVideoMediaInfo.dwStandardRate = 25;////////////////////////////////////////////////////////////////////////////
		streamInfo.sVideoMediaInfo.dwStandardScale = 1;////////////////////////////////////////////////////////////////////////////
		streamInfo.sVideoMediaInfo.dwDisplayWidth = 16;////////////////////////////////////////////////////////////////////////////
		streamInfo.sVideoMediaInfo.dwDisplayHeight = 9;////////////////////////////////////////////////////////////////////////////
		streamInfo.sVideoMediaInfo.enumColorPrimaries = SDCOLORPRIMARIES_ITU_R709;			// 源基色的色度坐标(ISO13818-2)
		streamInfo.sVideoMediaInfo.enumColorTransfer = SDCOLORTRANSFER_ITU_R709;			// 光电转换特性(ISO13818-2)
		streamInfo.sVideoMediaInfo.enumColorMatrix = SDCOLORMATRIX_ITU_R709;			// 颜色空间变换系数(ISO13818-2)
		streamInfo.sVideoMediaInfo.dwDataRateInBitsPerSec = 100000000;
		break;
	default:
		break;
	}

	streamInfo.enumStreamMediaType = SDSTREAMTYPE_OPENDML_AVI;
	streamInfo.dwStreamMediaSubType = 0;
	streamInfo.dwVideoStreamCount = 1;
	streamInfo.dwTotalAverDataRateInBitsPerSec = 0;
	streamInfo.dwTotalMaxDataRateInBitsPerSec = 0;
	streamInfo.dwTotalMinDataRateInBitsPerSec = 0;
	streamInfo.sVideoMediaInfo.enumScanMode = SDVIDEOSCANMODE_FirstFieldTop;
	streamInfo.sVideoMediaInfo.enumColorFormat = emColorFormat;//(SDCOLORFORMAT_YUVP_420)////////////////////////////////////////////////////////////////////////////
	streamInfo.sVideoMediaInfo.enumVideoType = emVideoType; //(SDVIDEOTYPE_H264)////////////////////////////////////////////////////////////////////////////
	streamInfo.sVideoMediaInfo.dwVideoSubType = PROFILE_UNKNOW;
	streamInfo.sVideoMediaInfo.enumDataRateType = SDDATARATE_CONSTANT;
	streamInfo.sVideoMediaInfo.dwGOPSize = 100;////////////////////////////////////////////////////////////////////////////
	streamInfo.sVideoMediaInfo.dwReferencePeriod = 1;
	streamInfo.sVideoMediaInfo.bIsClipped = 1;
	streamInfo.sVideoMediaInfo.dwMaxDataRateInBitsPerSec = 0;
	streamInfo.sVideoMediaInfo.dwMinDataRateInBitsPerSec = 0;
	streamInfo.sVideoMediaInfo.dwH264EncoderLevel = nH264Level;
	streamInfo.sVideoMediaInfo.dwStruSize = sizeof(SDVideoMediaInfo);
	streamInfo.dwAudioStreamCount = 1;
	streamInfo.sAudioMediaInfo.enumAudioType = emAudioType;		// 音频编解码类型。////////////////////////////////////////////////////////////////////////////
	streamInfo.sAudioMediaInfo.dwAudioSubType = 0;		// 音频编解码的子类型,子类型定义随enumAudioType不同而不同
	streamInfo.sAudioMediaInfo.dwChannels = 2;			// 声道数目
	streamInfo.sAudioMediaInfo.dwSamplesPerSec = dwSamplePerSec;	// 每秒采样数量 ////////////////////////////////////////////////////////////////////////////
	streamInfo.sAudioMediaInfo.dwBitsPerSample = 32;	// 采样位数 
	streamInfo.sAudioMediaInfo.dwAvgBitsPerSec = 32 * dwSamplePerSec;	// 音频码率 bits
	streamInfo.sAudioMediaInfo.dwBlockAlign = 1;		// 数据块对齐单位(每个采样样本需要的字节数), 声道数*量化数/8, 量化数(16,20?,24,32...)
	streamInfo.sAudioMediaInfo.enumAudioCFG = SDAUDIOCFG_STEREO;		//声道属性
	streamInfo.sAudioMediaInfo.enumChannelSamplesFormat = SDCHANNELSAMPLESFORMAT_Progressive;	//音频声道采样数据格式(AV_SAMPLE_FMT_S32)
	streamInfo.sAudioMediaInfo.extradata = nullptr;
	streamInfo.sAudioMediaInfo.extradata_size = 0;
	streamInfo.sAudioMediaInfo.dwStruSize = sizeof(SDAudioMediaInfo);			// 结构大小
	streamInfo.dwStruSize = sizeof(SDStreamMediaInfo);

	if (emVideoType == SDVIDEOTYPE_H264 && emAudioType == SDAUDIOTYPE_AAC)
	{
		streamInfo.sVideoMediaInfo.dwDataRateInBitsPerSec = 25000000;
		return _T(".mp4");
	}
	if (emVideoType == SDVIDEOTYPE_H264_INTEL && emAudioType == SDAUDIOTYPE_AAC)
	{
		streamInfo.sVideoMediaInfo.dwDataRateInBitsPerSec = 25000000;
		return _T(".mp4");
	}
	else if (emVideoType == SDVIDEOTYPE_MPEG4 && emAudioType == SDAUDIOTYPE_MP3)
	{
		streamInfo.sVideoMediaInfo.dwDataRateInBitsPerSec = 25000000;
		return _T(".mp4");
	}
	else if (emVideoType == SDVIDEOTYPE_MPEG2_IFRAME && emAudioType == SDAUDIOTYPE_WAVE_PCM)
	{
		return _T(".avi");
	}
	else
	{
		return _T(".avi");
	}
}
