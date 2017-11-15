#include "FFmpegFormatConverter.h"

AVCodecID FFmpegFormatCovert::ConvertCodecId(SD_VIDEO_TYPE emVideoType)
{
	AVCodecID codecId = AV_CODEC_ID_NONE;
	switch (emVideoType)
	{
	case SDVIDEOTYPE_UNKNOW:
		break;
	case SDVIDEOTYPE_MJPEG_FIELD:
		codecId = AV_CODEC_ID_MJPEG;
		break;
	case SDVIDEOTYPE_MJPEG_FRAME:
		codecId = AV_CODEC_ID_MJPEG;
		break;
	case SDVIDEOTYPE_MJPEG_LOSSLESS_FIELD:
		codecId = AV_CODEC_ID_MJPEG;
		break;
	case SDVIDEOTYPE_MJPEG_LOSSLESS_FRAME:
		codecId = AV_CODEC_ID_MJPEG;
		break;
	case SDVIDEOTYPE_MPEG1:
		codecId = AV_CODEC_ID_MPEG1VIDEO;
		break;
	case SDVIDEOTYPE_MPEG2_IFRAME:
		codecId = AV_CODEC_ID_MPEG2VIDEO;
		break;
	case SDVIDEOTYPE_MPEG2_IBP:
		codecId = AV_CODEC_ID_MPEG2VIDEO;
		break;
	case SDVIDEOTYPE_MPEG2_D10:
		codecId = AV_CODEC_ID_MPEG2VIDEO;
		break;
	case SDVIDEOTYPE_MPEG2_HDV:
		codecId = AV_CODEC_ID_MPEG2VIDEO;
		break;
	case SDVIDEOTYPE_MPEG4:
		codecId = AV_CODEC_ID_MPEG4;
		break;
	case SDVIDEOTYPE_DV25:
		codecId = AV_CODEC_ID_DVVIDEO;
		break;
	case SDVIDEOTYPE_DV50:
		codecId = AV_CODEC_ID_DVVIDEO;
		break;
	case SDVIDEOTYPE_DVSD:
		codecId = AV_CODEC_ID_DVVIDEO;
		break;
	case SDVIDEOTYPE_DVHD:
		codecId = AV_CODEC_ID_DVVIDEO;
		break;
	case SDVIDEOTYPE_YUV_UNCOMPRESS:
		break;
	case SDVIDEOTYPE_RGB_UNCOMPRESS:
		codecId = AV_CODEC_ID_BMP;
		break;
	case SDVIDEOTYPE_ZAXEL_LOSSLESS:
		break;
	case SDVIDEOTYPE_REAL_MEDIA:
		break;
	case SDVIDEOTYPE_WINDOWS_MEDIA:
		codecId = AV_CODEC_ID_WMAV1;
		break;
	case SDVIDEOTYPE_QUICKTIME_MOV:
		break;
	case SDVIDEOTYPE_VCM_COMPRESSED:
		break;
	case SDVIDEOTYPE_AVS:
		codecId = AV_CODEC_ID_AVS;
		break;
	case SDVIDEOTYPE_H263:
		codecId = AV_CODEC_ID_H263;
		break;
	case SDVIDEOTYPE_H264:
		codecId = AV_CODEC_ID_H264;
		break;
	case SDVIDEOTYPE_H265:
		codecId = AV_CODEC_ID_H265;
		break;
	case SDVIDEOTYPE_AVCINTRA_HD:
		break;
	case SDVIDEOTYPE_AVID_DNXHD:
		break;
	case SDVIDEOTYPE_MJ2K:
		break;
	case SDVIDEOTYPE_PRORES422:
		break;
	case SDVIDEOTYPE_SWFFLV_TYPE:
		break;
	case SDVIDEOTYPE_DPX:
		codecId = AV_CODEC_ID_DPX;
		break;
	case SDVIDEOTYPE_REDCODE:
		break;
	default:
		codecId = (AVCodecID)emVideoType;
		break;
	}

	return codecId;
}

AVCodecID FFmpegFormatCovert::ConvertCodecId(SD_AUDIO_TYPE emAudioType)
{
	AVCodecID codecId = AV_CODEC_ID_NONE;
	switch (emAudioType)
	{
	case SDAUDIOTYPE_WAVE_PCM:
		codecId = AV_CODEC_ID_PCM_S16LE;
		break;
	case SDAUDIOTYPE_MP1:
		codecId = AV_CODEC_ID_MP1;
		break;
	case SDAUDIOTYPE_MP2:
		codecId = AV_CODEC_ID_MP2;
		break;
	case SDAUDIOTYPE_MP3:
		codecId = AV_CODEC_ID_MP3;
		break;
	case SDAUDIOTYPE_MPEG4:
		codecId = AV_CODEC_ID_MP4ALS;
		break;
	case SDAUDIOTYPE_AAC:
		codecId = AV_CODEC_ID_AAC;
		break;
	case SDAUDIOTYPE_AC3:
		codecId = AV_CODEC_ID_AC3;
		break;
	case SDAUDIOTYPE_DTS:
		codecId = AV_CODEC_ID_DTS;
		break;
	case SDAUDIOTYPE_DRA:
		break;
	case SDAUDIOTYPE_AVS:
		codecId = AV_CODEC_ID_AVS;
		break;
	case SDAUDIOTYPE_DolbyE:
		break;
	case SDAUDIOTYPE_EAC3:
		break;
	case SDAUDIOTYPE_REAL_MEDIA:
		break;
	case SDAUDIOTYPE_WINDOWS_MEDIA:
		codecId = AV_CODEC_ID_WMAV1;
		break;
	case SDAUDIOTYPE_QUICKTIME_MOV:
		break;
	case SDAUDIOTYPE_G711:
		break;
	case SDAUDIOTYPE_AMRNB:
		codecId = AV_CODEC_ID_AMR_NB;
		break;
	case SDAUDIOTYPE_AMRWB:
		codecId = AV_CODEC_ID_AMR_WB;
		break;
	case SDAUDIOTYPE_SWFFLV:
		codecId = AV_CODEC_ID_FLV1;
		break;
	default:
		codecId = (AVCodecID)emAudioType;
		break;
	}

	return codecId;
}

SD_AUDIO_TYPE FFmpegFormatCovert::ConvertAudioType(AVCodecID emCodecID)
{
	SD_AUDIO_TYPE emAudioType = SDAUDIOTYPE_UNKNOW;
	switch (emCodecID)
	{
	case AV_CODEC_ID_PCM_S16LE:
		emAudioType = SDAUDIOTYPE_WAVE_PCM;
		break;
	case AV_CODEC_ID_MP1:
		emAudioType = SDAUDIOTYPE_MP1;
		break;
	case AV_CODEC_ID_MP2:
		emAudioType = SDAUDIOTYPE_MP2;
		break;
	case AV_CODEC_ID_MP3:
		emAudioType = SDAUDIOTYPE_MP3;
		break;
	case AV_CODEC_ID_MP4ALS:
		emAudioType = SDAUDIOTYPE_MPEG4;
		break;
	case AV_CODEC_ID_AAC:
		emAudioType = SDAUDIOTYPE_AAC;
		break;
	case AV_CODEC_ID_AC3:
		emAudioType = SDAUDIOTYPE_AC3;
		break;
	case AV_CODEC_ID_DTS:
		emAudioType = SDAUDIOTYPE_DTS;
		break;
	case AV_CODEC_ID_AVS:
		emAudioType = SDAUDIOTYPE_AVS;
		break;
	case AV_CODEC_ID_WMAV1:
		emAudioType = SDAUDIOTYPE_WINDOWS_MEDIA;
		break;
	case SDAUDIOTYPE_QUICKTIME_MOV:
		break;
	case SDAUDIOTYPE_G711:
		break;
	case AV_CODEC_ID_AMR_NB:
		emAudioType = SDAUDIOTYPE_AMRNB;
		break;
	case AV_CODEC_ID_AMR_WB:
		emAudioType = SDAUDIOTYPE_AMRWB;
		break;
	case AV_CODEC_ID_FLV1:
		emAudioType = SDAUDIOTYPE_SWFFLV;
		break;
	default:
		emAudioType = (SD_AUDIO_TYPE)emCodecID;
		break;
	}

	return emAudioType;
}

AVPixelFormat FFmpegFormatCovert::ConvertPixelFormat(SD_COLOR_FORMAT emColorFormat)
{
	AVPixelFormat pixelFormat = AV_PIX_FMT_NONE;
	switch (emColorFormat)
	{
	case SDCOLORFORMAT_BGRA:
		pixelFormat = AV_PIX_FMT_BGRA;
		break;
	case SDCOLORFORMAT_BGR:
		pixelFormat = AV_PIX_FMT_BGR24;
		break;
	case SDCOLORFORMAT_YUYV:
		pixelFormat = AV_PIX_FMT_YUYV422;
		break;
	case SDCOLORFORMAT_UYVY:
		pixelFormat = AV_PIX_FMT_UYVY422;
		break;
	case SDCOLORFORMAT_YUVP_444:
		pixelFormat = AV_PIX_FMT_YUV444P;
		break;
	case SDCOLORFORMAT_YUVP_422:
		pixelFormat = AV_PIX_FMT_YUV422P;
		break;
	case SDCOLORFORMAT_YUVP_420:
		pixelFormat = AV_PIX_FMT_YUV420P;
		break;
	//case SDCOLORFORMAT_YUVP_NV12:
	//	pixelFormat = AV_PIX_FMT_NV12;
	//	break;
	case SDCOLORFORMAT_YUVP_411:
		pixelFormat = AV_PIX_FMT_YUV411P;
		break;
	}
	return pixelFormat;
}

int FFmpegFormatCovert::ConvertVideoProfile(SD_CODEC_PROFILE emProfile)
{
	int profile = FF_PROFILE_H264_BASELINE;
	switch (emProfile)
	{
	case PROFILE_UNKNOW:
		break;
	case PROFILE_AVC_BASELINE:
		profile = FF_PROFILE_H264_BASELINE;
		break;
	case PROFILE_AVC_MAIN:
		profile = FF_PROFILE_H264_MAIN;
		break;
	case PROFILE_AVC_HIGH:
		profile = FF_PROFILE_H264_HIGH;
		break;
	default:
		break;
	}

	return profile;
}

int FFmpegFormatCovert::ConvertAudioProfile(SD_UINT32 emProfile)
{
	int profile = FF_PROFILE_AAC_LOW;
	switch (emProfile)
	{
	case PROFILE_UNKNOW:
		break;
	case PROFILE_AVC_BASELINE:
		profile = FF_PROFILE_AAC_LOW;
		break;
	case PROFILE_AVC_MAIN:
		profile = FF_PROFILE_AAC_MAIN;
		break;
	case PROFILE_AVC_HIGH:
		profile = FF_PROFILE_AAC_HE;
		break;
	default:
		break;
	}

	return profile;
}

AVSampleFormat FFmpegFormatCovert::ConvertSamplesFormat(SD_CHANNELSAMPLE_FORMAT emSampleFormat)
{
	AVSampleFormat avSampleFmt = AV_SAMPLE_FMT_NONE;
	switch (emSampleFormat)
	{
	case SDCHANNELSAMPLESFORMAT_Progressive:
		avSampleFmt = AV_SAMPLE_FMT_S16;
		break;
	case SDCHANNELSAMPLESFORMAT_Segmented:
		avSampleFmt = AV_SAMPLE_FMT_S16P;
		break;
	default:
		//留个后门，可以直接指定ffmpeg类型
		avSampleFmt = (AVSampleFormat)emSampleFormat;
		break;
	}
	return avSampleFmt;
}

SD_CHANNELSAMPLE_FORMAT FFmpegFormatCovert::ConvertSamplesFormat(AVSampleFormat emSampleFormat)
{
	SD_CHANNELSAMPLE_FORMAT emSampleRet = SDCHANNELSAMPLESFORMAT_Unknow;
	switch (emSampleFormat)
	{
	case AV_SAMPLE_FMT_S16:
		emSampleRet = SDCHANNELSAMPLESFORMAT_Progressive;
		break;
	case AV_SAMPLE_FMT_S16P:
		emSampleRet = SDCHANNELSAMPLESFORMAT_Segmented;
		break;
	default:
		emSampleRet = SD_CHANNELSAMPLE_FORMAT(emSampleFormat);
		break;
	}
	return emSampleRet;
}

SD_UINT64 FFmpegFormatCovert::ConvertChannelLayout(SD_AUDIO_CHANNELCONFIGURATION channelCfg)
{
	SD_UINT64 nChannelLayout = AV_CH_LAYOUT_STEREO;
	switch (channelCfg)
	{
	case SDAUDIOCFG_UNKNOW:
		break;
	case SDAUDIOCFG_INDEPENDENT:
		nChannelLayout = AV_CH_LAYOUT_MONO;
		break;
	case SDAUDIOCFG_STEREO:
		nChannelLayout = AV_CH_LAYOUT_STEREO;
		break;
	case SDAUDIOCFG_5_1:
		nChannelLayout = AV_CH_LAYOUT_5POINT1;
		break;
	case SDAUDIOCFG_7_1:
		nChannelLayout = AV_CH_LAYOUT_7POINT1;
		break;
	case SDAUDIOCFG_2_1:
		nChannelLayout = AV_CH_LAYOUT_2_1;
		break;
	case SDAUDIOCFG_3_0_C:
		nChannelLayout = AV_CH_LAYOUT_3POINT1;
		break;
	case SDAUDIOCFG_3_0_S:
		nChannelLayout = AV_CH_LAYOUT_SURROUND;
		break;
	case SDAUDIOCFG_3_1_C_LFE:
		break;
	case SDAUDIOCFG_3_1_S_LFE:
		break;
	case SDAUDIOCFG_4_0_C_S:
		nChannelLayout = AV_CH_LAYOUT_4POINT0;
		break;
	case SDAUDIOCFG_4_0_LS_RS:
		nChannelLayout = AV_CH_LAYOUT_2_2;
		break;
	case SDAUDIOCFG_4_1_C_S_LFE:
		break;
	case SDAUDIOCFG_4_1_LS_RS_LFE:
		break;
	case SDAUDIOCFG_5_0:
		nChannelLayout = AV_CH_LAYOUT_5POINT0;
		break;
	case SDAUDIOCFG_6_0_LRC_LRSRC:
		break;
	case SDAUDIOCFG_6_0_FLFR_LR_LRS:
		break;
	case SDAUDIOCFG_6_1_LRFC_LRSRC_LFE:
		break;
	case SDAUDIOCFG_6_1_FLR_LRLRS_LFE:
		break;
	case SDAUDIOCFG_7_0:
		nChannelLayout = AV_CH_LAYOUT_7POINT0;
		break;
	default:
		break;
	}

	return nChannelLayout;
}

SD_AUDIO_CHANNELCONFIGURATION FFmpegFormatCovert::ConvertChannelLayout(SD_UINT64 channelCfg)
{
	SD_AUDIO_CHANNELCONFIGURATION nChannelLayout = SDAUDIOCFG_UNKNOW;
	switch (channelCfg)
	{
	case SDAUDIOCFG_UNKNOW:
		break;
	case AV_CH_LAYOUT_MONO:
		nChannelLayout = SDAUDIOCFG_INDEPENDENT;
		break;
	case AV_CH_LAYOUT_STEREO:
		nChannelLayout = SDAUDIOCFG_STEREO;
		break;
	case AV_CH_LAYOUT_5POINT1:
		nChannelLayout = SDAUDIOCFG_5_1;
		break;
	case AV_CH_LAYOUT_7POINT1:
		nChannelLayout = SDAUDIOCFG_7_1;
		break;
	case AV_CH_LAYOUT_2_1:
		nChannelLayout = SDAUDIOCFG_2_1;
		break;
	case AV_CH_LAYOUT_3POINT1:
		nChannelLayout = SDAUDIOCFG_3_0_C;
		break;
	case AV_CH_LAYOUT_SURROUND:
		nChannelLayout = SDAUDIOCFG_3_0_S;
		break;
	case SDAUDIOCFG_3_1_C_LFE:
		break;
	case SDAUDIOCFG_3_1_S_LFE:
		break;
	case AV_CH_LAYOUT_4POINT0:
		nChannelLayout = SDAUDIOCFG_4_0_C_S;
		break;
	case AV_CH_LAYOUT_2_2:
		nChannelLayout = SDAUDIOCFG_4_0_LS_RS;
		break;
	case SDAUDIOCFG_4_1_C_S_LFE:
		break;
	case SDAUDIOCFG_4_1_LS_RS_LFE:
		break;
	case AV_CH_LAYOUT_5POINT0:
		nChannelLayout = SDAUDIOCFG_5_0;
		break;
	//case SDAUDIOCFG_6_0_LRC_LRSRC:
	//	break;
	case SDAUDIOCFG_6_0_FLFR_LR_LRS:
		break;
	case SDAUDIOCFG_6_1_LRFC_LRSRC_LFE:
		break;
	case SDAUDIOCFG_6_1_FLR_LRLRS_LFE:
		break;
	case AV_CH_LAYOUT_7POINT0:
		nChannelLayout = SDAUDIOCFG_7_0;
		break;
	default:
		break;
	}

	return nChannelLayout;
}

SD_VIDEO_TYPE FFmpegFormatCovert::ConvertVideoCodecType(AVCodecID codecID)
{
	SD_VIDEO_TYPE videoType = SDVIDEOTYPE_UNKNOW;
	switch (codecID)
	{
	case AV_CODEC_ID_H264:
		videoType = SDVIDEOTYPE_H264;
		break;
	case AV_CODEC_ID_MPEG2VIDEO:
		videoType = SDVIDEOTYPE_MPEG2_IFRAME;
		break;
	case AV_CODEC_ID_MPEG4:
		videoType = SDVIDEOTYPE_MPEG4;
		break;
	default:
		videoType = (SD_VIDEO_TYPE)codecID;
		break;
	}
	return videoType;
}

SD_UINT32 FFmpegFormatCovert::ConvertVideoCodecSubType(SD_UINT32 codecTag)
{
	return SD_UINT32();
}

SD_VIDEOSCAN_MODE FFmpegFormatCovert::ConvertVideoFieldOrder(AVFieldOrder fieldOrder)
{
	SD_VIDEOSCAN_MODE emRet = SDVIDEOSCANMODE_Invalid;
	switch (fieldOrder)
	{
	case AV_FIELD_UNKNOWN:
		emRet = SDVIDEOSCANMODE_Invalid;
		break;
	case AV_FIELD_PROGRESSIVE:
		emRet = SDVIDEOSCANMODE_Progressive;
		break;
	case AV_FIELD_TT:
		emRet = SDVIDEOSCANMODE_FirstFieldTop;
		break;
	case AV_FIELD_BB:
		emRet = SDVIDEOSCANMODE_SecondFieldTop;
		break;
	case AV_FIELD_TB:
		emRet = SDVIDEOSCANMODE_FirstFieldTopBackToBack;
		break;
	case AV_FIELD_BT:
		emRet = SDVIDEOSCANMODE_SecondFieldTopBackToBack;
		break;
	default:
		break;
	}
	return emRet;
}

AVFieldOrder FFmpegFormatCovert::ConvertVideoFieldOrder(SD_VIDEOSCAN_MODE emScanMode)
{
	AVFieldOrder emRet = AV_FIELD_UNKNOWN;
	switch (emScanMode)
	{
	case SDVIDEOSCANMODE_Invalid:
		emRet = AV_FIELD_UNKNOWN;
		break;
	case SDVIDEOSCANMODE_FirstFieldTop:
		emRet = AV_FIELD_TT;
		break;
	case SDVIDEOSCANMODE_SecondFieldTop:
		emRet = AV_FIELD_BB;
		break;
	case SDVIDEOSCANMODE_Progressive:
		emRet = AV_FIELD_PROGRESSIVE;
		break;
	case SDVIDEOSCANMODE_ProgressiveSegmented:
		emRet = AV_FIELD_PROGRESSIVE;
		break;
	case SDVIDEOSCANMODE_FirstFieldTopBackToBack:
		emRet = AV_FIELD_TB;
		break;
	case SDVIDEOSCANMODE_SecondFieldTopBackToBack:
		emRet = AV_FIELD_BT;
		break;
	default:
		break;
	}
	return emRet;
}

SD_COLOR_FORMAT FFmpegFormatCovert::ConvertColorFormat(AVPixelFormat pixelFormat)
{
	SD_COLOR_FORMAT emColorFormat = SDCOLORFORMAT_UNKNOW;
	switch (pixelFormat)
	{
	case AV_PIX_FMT_BGRA:
		emColorFormat = SDCOLORFORMAT_BGRA;
		break;
	case AV_PIX_FMT_BGR24:
		emColorFormat = SDCOLORFORMAT_BGR;
		break;
	case AV_PIX_FMT_YUYV422:
		emColorFormat = SDCOLORFORMAT_YUYV;
		break;
	case AV_PIX_FMT_UYVY422:
		emColorFormat = SDCOLORFORMAT_UYVY;
		break;
	case AV_PIX_FMT_YUV444P:
		emColorFormat = SDCOLORFORMAT_YUVP_444;
		break;
	case AV_PIX_FMT_YUV422P:
		emColorFormat = SDCOLORFORMAT_YUVP_422;
		break;
	case AV_PIX_FMT_YUV420P:
		emColorFormat = SDCOLORFORMAT_YUVP_420;
		break;
		//case SDCOLORFORMAT_YUVP_NV12:
		//	pixelFormat = AV_PIX_FMT_NV12;
		//	break;
	case AV_PIX_FMT_YUV411P:
		emColorFormat = SDCOLORFORMAT_YUVP_411;
		break;
	}
	return emColorFormat;
}

SD_COLOR_PRIMARIES FFmpegFormatCovert::ConvertColorPrimaries(AVColorPrimaries colorPrimaries)
{
	return SD_COLOR_PRIMARIES();
}

SD_COLOR_TRANSFER FFmpegFormatCovert::ConvertColorTransfer(AVColorTransferCharacteristic colorTrans)
{
	return SD_COLOR_TRANSFER();
}

SD_COLOR_MATRIX FFmpegFormatCovert::ConvertColorSpace(AVColorSpace colorSpace)
{
	return SD_COLOR_MATRIX();
}

FRAME_COMPRESS_TYPE FFmpegFormatCovert::ConvertCompressType(AVPictureType compressType)
{
	return FRAME_COMPRESS_TYPE();
}

bool FFmpegFormatCovert::ConvertPDataToBuffer(unsigned char ** pInData, int * pInLinesize, SD_UINT8 * pFrameBuf, uint32_t nSize,
	enum AVPixelFormat pix_fmt, int width, int height, int align)
{
	if (pFrameBuf && pInData && pInLinesize)
	{
		uint32_t nRet = av_image_copy_to_buffer(pFrameBuf, nSize, pInData, pInLinesize, pix_fmt, width, height, sizeof(SD_UINT8));
		if (nRet > 0)
		{
			return true;
		}
	}
	return false;
}

bool FFmpegFormatCovert::ConvertBufferToPData(SD_UINT8 * pFrameBuf, uint32_t * pSize, unsigned char ** pOutData, int * pOutLinesize,
	enum AVPixelFormat pix_fmt, int width, int height, int align)
{
	if (pFrameBuf && pOutData && pOutLinesize)
	{
		uint32_t nSize = av_image_fill_arrays(pOutData, pOutLinesize, pFrameBuf, pix_fmt, width, height, sizeof(SD_UINT8));
		if (nSize > 0)
		{
			if (pSize)
			{
				*pSize = nSize;
				return true;
			}
		}
	}
	return false;
}

bool FFmpegFormatCovert::ConvertPDataToBuffer(unsigned char ** pInData, int * pInLinesize, SD_UINT8 * pFrameBuf, uint32_t nSize, AVSampleFormat sample_fmt, int channels, int nb_samples)
{
	int data_size = av_get_bytes_per_sample(sample_fmt);
	if (data_size <= 0) 
	{
		return false;
	}
	SD_UINT64 nCursor = 0;
	for (int i = 0; i < nb_samples; i++)
	{ 
		for (int ch = 0; ch < channels; ch++)
		{
			memcpy(pFrameBuf + nCursor, pInData[ch] + data_size * i, data_size);
			nCursor += data_size;
		}
	}
	return true;
}

bool FFmpegFormatCovert::ConvertBufferToPData(SD_UINT8 * pFrameBuf, uint32_t * pSize, unsigned char ** pOutData, int * pOutLinesize, AVSampleFormat sample_fmt, int channels, int nb_samples)
{
	int data_size = av_get_bytes_per_sample(sample_fmt);
	if (data_size <= 0)
	{
		return false;
	}
	SD_UINT64 nCursor = 0;
	for (int i = 0; i < nb_samples; i++)
	{
		for (int ch = 0; ch < channels; ch++)
		{
			memcpy(pOutData[ch] + data_size * i, pFrameBuf + nCursor, data_size);
			nCursor += data_size;
		}
	}
	return true;
}

std::string FFmpegFormatCovert::GetH264EncodePreset(SD_UINT8 nPresetLevel)
{
	std::string cstrRet;
	if (nPresetLevel == 1)
	{
		cstrRet = "placebo";
	}
	else if (nPresetLevel == 2)
	{
		cstrRet = "veryslow";
	}
	else if (nPresetLevel == 3)
	{
		cstrRet = "slower";
	}
	else if (nPresetLevel == 4)
	{
		cstrRet = "medium slow";
	}
	else if (nPresetLevel == 5)
	{
		cstrRet = "fast";
	}
	else if (nPresetLevel == 6)
	{
		cstrRet = "faster";
	}
	else if (nPresetLevel == 7)
	{
		cstrRet = "veryfast";
	}
	else if (nPresetLevel == 8)
	{
		cstrRet = "superfast";
	}
	else if (nPresetLevel == 9)
	{
		cstrRet = "ultrafast";
	}
	else
	{
		cstrRet = "fast";
	}
	return cstrRet;
}
