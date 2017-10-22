#include "stdafx.h"
#include "FormatConverter.h"

AVCodecID FFmpegFormatCovert::ConvertCodecId(VIDEO_TYPE emVideoType)
{
	AVCodecID codecId = AV_CODEC_ID_NONE;
	switch (emVideoType)
	{
	case VIDEOTYPE_UNKNOW:
		break;
	case VIDEOTYPE_MJPEG_FIELD:
		codecId = AV_CODEC_ID_MJPEG;
		break;
	case VIDEOTYPE_MJPEG_FRAME:
		codecId = AV_CODEC_ID_MJPEG;
		break;
	case VIDEOTYPE_MJPEG_LOSSLESS_FIELD:
		codecId = AV_CODEC_ID_MJPEG;
		break;
	case VIDEOTYPE_MJPEG_LOSSLESS_FRAME:
		codecId = AV_CODEC_ID_MJPEG;
		break;
	case VIDEOTYPE_MPEG1:
		codecId = AV_CODEC_ID_MPEG1VIDEO;
		break;
	case VIDEOTYPE_MPEG2_IFRAME:
		codecId = AV_CODEC_ID_MPEG2VIDEO;
		break;
	case VIDEOTYPE_MPEG2_IBP:
		codecId = AV_CODEC_ID_MPEG2VIDEO;
		break;
	case VIDEOTYPE_MPEG2_D10:
		codecId = AV_CODEC_ID_MPEG2VIDEO;
		break;
	case VIDEOTYPE_MPEG2_HDV:
		codecId = AV_CODEC_ID_MPEG2VIDEO;
		break;
	case VIDEOTYPE_MPEG4:
		codecId = AV_CODEC_ID_MPEG4;
		break;
	case VIDEOTYPE_DV25:
		codecId = AV_CODEC_ID_DVVIDEO;
		break;
	case VIDEOTYPE_DV50:
		codecId = AV_CODEC_ID_DVVIDEO;
		break;
	case VIDEOTYPE_DVSD:
		codecId = AV_CODEC_ID_DVVIDEO;
		break;
	case VIDEOTYPE_DVHD:
		codecId = AV_CODEC_ID_DVVIDEO;
		break;
	case VIDEOTYPE_YUV_UNCOMPRESS:
		break;
	case VIDEOTYPE_RGB_UNCOMPRESS:
		codecId = AV_CODEC_ID_BMP;
		break;
	case VIDEOTYPE_ZAXEL_LOSSLESS:
		break;
	case VIDEOTYPE_REAL_MEDIA:
		break;
	case VIDEOTYPE_WINDOWS_MEDIA:
		codecId = AV_CODEC_ID_WMAV1;
		break;
	case VIDEOTYPE_QUICKTIME_MOV:
		break;
	case VIDEOTYPE_VCM_COMPRESSED:
		break;
	case VIDEOTYPE_AVS:
		codecId = AV_CODEC_ID_AVS;
		break;
	case VIDEOTYPE_H263:
		codecId = AV_CODEC_ID_H263;
		break;
	case VIDEOTYPE_H264:
		codecId = AV_CODEC_ID_H264;
		break;
	case VIDEOTYPE_H265:
		codecId = AV_CODEC_ID_H265;
		break;
	case VIDEOTYPE_AVCINTRA_HD:
		break;
	case VIDEOTYPE_AVID_DNXHD:
		break;
	case VIDEOTYPE_MJ2K:
		break;
	case VIDEOTYPE_PRORES422:
		break;
	case VIDEOTYPE_SWFFLV_TYPE:
		break;
	case VIDEOTYPE_DPX:
		codecId = AV_CODEC_ID_DPX;
		break;
	case VIDEOTYPE_REDCODE:
		break;
	default:
		break;
	}

	return codecId;
}

AVCodecID FFmpegFormatCovert::ConvertCodecId(AUDIO_TYPE emAudioType)
{
	AVCodecID codecId = AV_CODEC_ID_NONE;
	switch (emAudioType)
	{
	case AUDIOTYPE_WAVE_PCM:
		codecId = AV_CODEC_ID_PCM_DVD;
		break;
	case AUDIOTYPE_MP1:
		codecId = AV_CODEC_ID_MP1;
		break;
	case AUDIOTYPE_MP2:
		codecId = AV_CODEC_ID_MP2;
		break;
	case AUDIOTYPE_MP3:
		codecId = AV_CODEC_ID_MP3;
		break;
	case AUDIOTYPE_MPEG4:
		codecId = AV_CODEC_ID_MP4ALS;
		break;
	case AUDIOTYPE_AAC:
		codecId = AV_CODEC_ID_AAC;
		break;
	case AUDIOTYPE_AC3:
		codecId = AV_CODEC_ID_AC3;
		break;
	case AUDIOTYPE_DTS:
		codecId = AV_CODEC_ID_DTS;
		break;
	case AUDIOTYPE_DRA:
		break;
	case AUDIOTYPE_AVS:
		codecId = AV_CODEC_ID_AVS;
		break;
	case AUDIOTYPE_DolbyE:
		break;
	case AUDIOTYPE_EAC3:
		break;
	case AUDIOTYPE_REAL_MEDIA:
		break;
	case AUDIOTYPE_WINDOWS_MEDIA:
		codecId = AV_CODEC_ID_WMAV1;
		break;
	case AUDIOTYPE_QUICKTIME_MOV:
		break;
	case AUDIOTYPE_G711:
		break;
	case AUDIOTYPE_AMRNB:
		codecId = AV_CODEC_ID_AMR_NB;
		break;
	case AUDIOTYPE_AMRWB:
		codecId = AV_CODEC_ID_AMR_WB;
		break;
	case AUDIOTYPE_SWFFLV:
		codecId = AV_CODEC_ID_FLV1;
		break;
	default:
		break;
	}

	return codecId;
}

AVPixelFormat FFmpegFormatCovert::ConvertPixelFormat(COLOR_FORMAT emColorFormat)
{
	AVPixelFormat pixelFormat = AV_PIX_FMT_NONE;
	switch (emColorFormat)
	{
	case COLORFORMAT_BGRA:
		pixelFormat = AV_PIX_FMT_BGRA;
		break;
	case COLORFORMAT_BGR:
		pixelFormat = AV_PIX_FMT_BGR24;
		break;
	case COLORFORMAT_YUYV:
		pixelFormat = AV_PIX_FMT_YUYV422;
		break;
	case COLORFORMAT_UYVY:
		pixelFormat = AV_PIX_FMT_UYVY422;
		break;
	case COLORFORMAT_YUVP_444:
		pixelFormat = AV_PIX_FMT_YUV444P;
		break;
	case COLORFORMAT_YUVP_422:
		pixelFormat = AV_PIX_FMT_YUV422P;
		break;
	case COLORFORMAT_YUVP_420:
		pixelFormat = AV_PIX_FMT_YUV420P;
		break;
	case COLORFORMAT_YUVP_NV12:
		pixelFormat = AV_PIX_FMT_NV12;
		break;
	case COLORFORMAT_YUVP_411:
		pixelFormat = AV_PIX_FMT_YUV411P;
		break;
	}
	return pixelFormat;
}

int FFmpegFormatCovert::ConvertVideoProfile(CODEC_PROFILE emProfile)
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

int FFmpegFormatCovert::ConvertAudioProfile(SW_UINT32 emProfile)
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

AVSampleFormat FFmpegFormatCovert::ConvertSamplesFormat(CHANNELSAMPLE_FORMAT emSampleFormat)
{
	AVSampleFormat avSampleFmt = AV_SAMPLE_FMT_NONE;
	switch (emSampleFormat)
	{
	case SAMPLE_FMT_U8:
		avSampleFmt = AV_SAMPLE_FMT_U8;
		break;
	case SAMPLE_FMT_S16:
		avSampleFmt = AV_SAMPLE_FMT_S16;
		break;
	case SAMPLE_FMT_S32:
		avSampleFmt = AV_SAMPLE_FMT_S32;
		break;
	case SAMPLE_FMT_FLT:
		avSampleFmt = AV_SAMPLE_FMT_FLT;
		break;
	case SAMPLE_FMT_DBL:
		avSampleFmt = AV_SAMPLE_FMT_DBL;
		break;
	case SAMPLE_FMT_U8P:
		avSampleFmt = AV_SAMPLE_FMT_U8P;
		break;
	case SAMPLE_FMT_S16P:
		avSampleFmt = AV_SAMPLE_FMT_S16P;
		break;
	case SAMPLE_FMT_S32P:
		avSampleFmt = AV_SAMPLE_FMT_S32P;
		break;
	case SAMPLE_FMT_FLTP:
		avSampleFmt = AV_SAMPLE_FMT_FLTP;
		break;
	case SAMPLE_FMT_DBLP:
		avSampleFmt = AV_SAMPLE_FMT_DBLP;
		break;
	case SAMPLE_FMT_S64:
		avSampleFmt = AV_SAMPLE_FMT_S64;
		break;
	case SAMPLE_FMT_S64P:
		avSampleFmt = AV_SAMPLE_FMT_S64P;
		break;
	default:
		break;
	}

	return avSampleFmt;
}

SW_UINT64 FFmpegFormatCovert::ConvertChannelLayout(AUDIO_CHANNELCONFIGURATION channelCfg)
{
	SW_UINT64 nChannelLayout = AV_CH_LAYOUT_STEREO;
	switch (channelCfg)
	{
	case AUDIOCFG_UNKNOW:
		break;
	case AUDIOCFG_INDEPENDENT:
		nChannelLayout = AV_CH_LAYOUT_MONO;
		break;
	case AUDIOCFG_STEREO:
		nChannelLayout = AV_CH_LAYOUT_STEREO;
		break;
	case AUDIOCFG_5_1:
		nChannelLayout = AV_CH_LAYOUT_5POINT1;
		break;
	case AUDIOCFG_7_1:
		nChannelLayout = AV_CH_LAYOUT_7POINT1;
		break;
	case AUDIOCFG_2_1:
		nChannelLayout = AV_CH_LAYOUT_2_1;
		break;
	case AUDIOCFG_3_0_C:
		nChannelLayout = AV_CH_LAYOUT_3POINT1;
		break;
	case AUDIOCFG_3_0_S:
		nChannelLayout = AV_CH_LAYOUT_SURROUND;
		break;
	case AUDIOCFG_3_1_C_LFE:
		break;
	case AUDIOCFG_3_1_S_LFE:
		break;
	case AUDIOCFG_4_0_C_S:
		nChannelLayout = AV_CH_LAYOUT_4POINT0;
		break;
	case AUDIOCFG_4_0_LS_RS:
		nChannelLayout = AV_CH_LAYOUT_2_2;
		break;
	case AUDIOCFG_4_1_C_S_LFE:
		break;
	case AUDIOCFG_4_1_LS_RS_LFE:
		break;
	case AUDIOCFG_5_0:
		nChannelLayout = AV_CH_LAYOUT_5POINT0;
		break;
	case AUDIOCFG_6_0_LRC_LRSRC:
		break;
	case AUDIOCFG_6_0_FLFR_LR_LRS:
		break;
	case AUDIOCFG_6_1_LRFC_LRSRC_LFE:
		break;
	case AUDIOCFG_6_1_FLR_LRLRS_LFE:
		break;
	case AUDIOCFG_7_0:
		nChannelLayout = AV_CH_LAYOUT_7POINT0;
		break;
	default:
		break;
	}

	return nChannelLayout;
}