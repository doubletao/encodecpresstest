/*****************************************************************************
// 文件名字：CodecDefines.h
// 作者：MY
// 创建日期：2017-07-26
// 版本：1.0
// 内容：定义速编码常用的枚举类型、数据结构
// 修改时间：
// 重要备注：
//enum CODEC_MODEL //编码器类型
//enum CODEC_PROFILE       //编码子类型
//enum TARGET_USAGES       //编码质量
//enum VIDEO_STANDARD	// 视频制式标准
//enum VIDEO_CLASS	//视频制式分类
//enum VIDEO_TYPE		// 视频编码格式类型
//enum AUDIO_TYPE	        // 音频编解码格式类型
//enum COLOR_FORMAT       // 视频颜色格式
//enum STREAM_TYPE        // 视音频流、文件格式类型
//enum VIDEOSCAN_MODE	// 视频扫描帧场数据排列方式
//enum VIDEO_ASPECTRATIO	// 视频幅宽比类型
//enum COLOR_PRIMARIES    // 源基色的色度坐标(ISO13818-2)
//enum COLOR_MATRIX	//	颜色空间变换系数(ISO13818-2)
//enum DATARATE_TYPE	// MPEG视频编解码格式码率类型
//struct SVideoMediaInfo	// 视频基本属性
//struct SVideoFrameImageBufInfo	//视频帧图像数据块属性
//enum AUDIO_CHANNELCONFIGURATION	// 声道属性枚举定义//采样精度
//enum SampleFormat          //采样精度
//enum CHANNELSAMPLE_FORMAT	//音频声道采样数据格式
//struct SAudioMediaInfo		// 音频基本属性
//struct SAudioSamplesBufInfo	//音频采样数据块属性
//enum SUBTITLE_TYPE              //字幕流类型
//struct SStreamMediaInfo		// 视音频流(文件)属性
//struct SStreamMediaInfoEx	// 视音频流(文件)扩展属性
//enum STREAMMEDIA_TYPE	        //流媒体数据信息类型
//enum MEDIADATASTREAM_TYPE	//媒体数据流数据类型
//enum FIELD                      //奇偶场
//enum VIDEO_SCALE_TYPE		//高标清上下变换类型定义
******************************************************************************/

#ifndef _VACOMMONDEFINE_H
#define _VACOMMONDEFINE_H

#include <string>
#include <sstream>
#include <cstdint>
#include "TypeDefine.h"

enum CODEC_MODEL
{
	CodecModel_FFMPEG = 0x00000001,
	CodecModel_INTEL,
	CodecModel_FFMPEG_INTEL
};

enum VIDEO_STANDARD	// 视频制式标准
{
	VIDEOSTANDARD_UNKNOW			= 0x00000000,	// Unknow type.
	VIDEOSTANDARD_PAL				= 0x00000001,	// PAL video type.						
	VIDEOSTANDARD_NTSC2997			= 0x00000002,	// NTSC video type.						
	VIDEOSTANDARD_NTSC30			= 0x00000004,	// 30-frames/second generic type.
	VIDEOSTANDARD_HD1080i_25		= 0x00000010,	// HDTV 1920*1080*25 type.				
	VIDEOSTANDARD_HD1080i_2997		= 0x00000020,	// HDTV 1920*1080*29.97 type.			
	VIDEOSTANDARD_HD1080i_30		= 0x00000040,	// HDTV 1920*1080*30 type.
	VIDEOSTANDARD_HD720p_2398		= 0x00000080,	// HDTV 1280*720*23.98 type.			
	VIDEOSTANDARD_HD720p_24			= 0x00000200,	// HDTV 1280*720*24 type.				
	VIDEOSTANDARD_HD720p_25			= 0x00000100,	// HDTV 1280*720*25 type.				
	VIDEOSTANDARD_HD720p_2997		= 0x00001000,	// HDTV 1280*720*29.97 type.			
	VIDEOSTANDARD_HD720p_30			= 0x00000008,	// HDTV 1280*720*30 type.				
	VIDEOSTANDARD_HD720p_50			= 0x00000400,	// HDTV 1280*720*50 type.				
	VIDEOSTANDARD_HD720p_5994		= 0x00000800,	// HDTV 1280*720*59.94 type.			
	VIDEOSTANDARD_HD720p_60			= 0x00040000,	// HDTV 1280*720*60 type.
	VIDEOSTANDARD_HD1080p_2398		= 0x00002000,	// HDTV 1920*1080*23.98 type.			
	VIDEOSTANDARD_HD1080p_24		= 0x00004000,	// HDTV 1920*1080*24 type.				
	VIDEOSTANDARD_HD1080p_25		= 0x00008000,	// HDTV 1920*1080*25 type.				
	VIDEOSTANDARD_HD1080p_2997		= 0x00010000,	// HDTV 1920*1080*29.97 type.			
	VIDEOSTANDARD_HD1080p_30		= 0x00020000,	// HDTV 1920*1080*30 type.
	VIDEOSTANDARD_HD1080psf_2398	= 0x00080000,	// HDTV 1920*1080*23.98 type.			
	VIDEOSTANDARD_HD1080psf_24		= 0x00100000,	// HDTV 1920*1080*24 type.				
	VIDEOSTANDARD_HD1080psf_25		= 0x00200000,	// HDTV 1920*1080*25 type.				
	VIDEOSTANDARD_HD1080psf_2997	= 0x00400000,	// HDTV 1920*1080*29.97 type.			
	VIDEOSTANDARD_HD1080psf_30		= 0x00800000,	// HDTV 1920*1080*30 type.	
	VIDEOSTANDARD_HD1080P_50		= 0x41000000,	// HDTV 1920*1080*50 type.				
	VIDEOSTANDARD_HD1080P_5994		= 0x42000000,	// HDTV 1920*1080*59.94 type.			
	VIDEOSTANDARD_HD1080P_60		= 0x43000000,	// HDTV 1920*1080*60 type.
	VIDEOSTANDARD_2K1080P_2398		= 0x45000000,	// 2K 2048*1080*23.98 type.				
	VIDEOSTANDARD_2K1080P_24		= 0x46000000,	// 2K 2048*1080*24 type.				
	VIDEOSTANDARD_2K1080P_48		= 0x47000000,	// 2K 2048*1080*48 type.
	VIDEOSTANDARD_2K1080Psf_2398	= 0x81000000,	// 2K 2048*1080*23.98 type.				
	VIDEOSTANDARD_2K1080Psf_24		= 0x82000000,	// 2K 2048*1080*24 type.
	VIDEOSTANDARD_2K1556P_2398		= 0x83000000,	// 2K 2048*1556*23.98 PLAYBACK.			
	VIDEOSTANDARD_2K1556P_24		= 0x84000000,	// 2K 2048*1556*24 PLAYBACK
	VIDEOSTANDARD_2K1556Psf_2398	= 0x85000000,	// 2K 2048*1556*23.98 PLAYBACK.			
	VIDEOSTANDARD_2K1556Psf_24		= 0x86000000,	// 2K 2048*1556*24 PLAYBACK.	
	VIDEOSTANDARD_4K2160P_24		= 0x87000000,	// HDTV 4096*2160*24 type.				

	VIDEOSTANDARD_2398_P			= 0x02000000,	// Unknow Size 23.98 P type.						
	VIDEOSTANDARD_2398_Psf			= 0x03000000,	// Unknow Size 23.98 Psf type.								
	VIDEOSTANDARD_24_P				= 0x04000000,	// Unknow Size 24 P type.									
	VIDEOSTANDARD_24_Psf			= 0x05000000,	// Unknow Size 24 Psf type.									
	VIDEOSTANDARD_25_I				= 0x08000000,	// Unknow Size 25 I type.
	VIDEOSTANDARD_25_P				= 0x06000000,	// Unknow Size 25 P type.									
	VIDEOSTANDARD_25_Psf			= 0x07000000,	// Unknow Size 25 Psf type.									
	VIDEOSTANDARD_2997_I			= 0x10000000,	// Unknow Size 29.97 I type.
	VIDEOSTANDARD_2997_P			= 0xC0000000,	// Unknow Size 29.97 P type.							
	VIDEOSTANDARD_2997_Psf			= 0xC1000000,	// Unknow Size 29.97 Psf type.								
	VIDEOSTANDARD_30_I				= 0x20000000,	// Unknow Size 30 I type.
	VIDEOSTANDARD_30_P				= 0xC2000000,	// Unknow Size 30 P type.									
	VIDEOSTANDARD_30_Psf			= 0xC3000000,	// Unknow Size 30 Psf type.									
	VIDEOSTANDARD_48_P				= 0xC4000000,	// Unknow Size 48 type.										
	VIDEOSTANDARD_50_P				= 0xC5000000,	// Unknow Size 50 type.										
	VIDEOSTANDARD_5994_P			= 0xC6000000,	// Unknow Size 59.94 type.								
	VIDEOSTANDARD_60_P				= 0xC7000000,	// Unknow Size 60 type.				
};

inline void	GetVideoStandardParam(VIDEO_STANDARD enumVideoStandard, std::string &strHint, uint32_t &dwWidth, uint32_t &dwHigh, uint32_t &dwCodecHigh)
{
	strHint = "Unknow";
	dwWidth = dwHigh = dwCodecHigh = 0;

	switch (enumVideoStandard)
	{
	case VIDEOSTANDARD_PAL:
		strHint = "PAL";
		dwWidth = 720;
		dwHigh = 576;
		dwCodecHigh = 576;
		break;
	case VIDEOSTANDARD_NTSC2997:
		strHint = "NTSC";
		dwWidth = 720;
		dwHigh = 486;
		dwCodecHigh = 480;
		break;
	case VIDEOSTANDARD_NTSC30:
		strHint = "480/60i";				//NTSC-30
		dwWidth = 720;
		dwHigh = 486;
		dwCodecHigh = 480;
		break;
	case VIDEOSTANDARD_HD1080i_25:
		strHint = "1080/50i";				//HD1080-25i
		dwWidth = 1920;
		dwHigh = 1080;
		dwCodecHigh = 1088;
		break;
	case VIDEOSTANDARD_HD1080i_2997:
		strHint = "1080/59.94i";			//HD1080-29.97i
		dwWidth = 1920;
		dwHigh = 1080;
		dwCodecHigh = 1088;
		break;
	case VIDEOSTANDARD_HD1080i_30:
		strHint = "1080/60i";				//HD1080-30i
		dwWidth = 1920;
		dwHigh = 1080;
		dwCodecHigh = 1088;
		break;
	case VIDEOSTANDARD_HD720p_2398:
		strHint = "720/23.98P";				//HD720-23.98p
		dwWidth = 1280;
		dwHigh = 720;
		dwCodecHigh = 720;
		break;
	case VIDEOSTANDARD_HD720p_24:
		strHint = "720/24P";				//HD720-24p
		dwWidth = 1280;
		dwHigh = 720;
		dwCodecHigh = 720;
		break;
	case VIDEOSTANDARD_HD720p_25:
		strHint = "720/25P";				//HD720-25p
		dwWidth = 1280;
		dwHigh = 720;
		dwCodecHigh = 720;
		break;
	case VIDEOSTANDARD_HD720p_2997:
		strHint = "720/29.97P";				//HD720-29.97p
		dwWidth = 1280;
		dwHigh = 720;
		dwCodecHigh = 720;
		break;
	case VIDEOSTANDARD_HD720p_30:
		strHint = "720/30P";				//HD720-30p
		dwWidth = 1280;
		dwHigh = 720;
		dwCodecHigh = 720;
		break;
	case VIDEOSTANDARD_HD720p_50:
		strHint = "720/50P";				//HD720-50p
		dwWidth = 1280;
		dwHigh = 720;
		dwCodecHigh = 720;
		break;
	case VIDEOSTANDARD_HD720p_5994:
		strHint = "720/59.94P";				//HD720-59.94p
		dwWidth = 1280;
		dwHigh = 720;
		dwCodecHigh = 720;
		break;
	case VIDEOSTANDARD_HD720p_60:
		strHint = "720/60P";				//HD720-60p
		dwWidth = 1280;
		dwHigh = 720;
		dwCodecHigh = 720;
		break;
	case VIDEOSTANDARD_HD1080p_2398:
		strHint = "1080/23.98P";			//HD1080-23.98p
		dwWidth = 1920;
		dwHigh = 1080;
		dwCodecHigh = 1088;
		break;
	case VIDEOSTANDARD_HD1080p_24:
		strHint = "1080/24P";				//HD1080-24p
		dwWidth = 1920;
		dwHigh = 1080;
		dwCodecHigh = 1088;
		break;
	case VIDEOSTANDARD_HD1080p_25:
		strHint = "1080/25P";				//HD1080-25p
		dwWidth = 1920;
		dwHigh = 1080;
		dwCodecHigh = 1088;
		break;
	case VIDEOSTANDARD_HD1080p_2997:
		strHint = "1080/29.97P";			//HD1080-29.97p
		dwWidth = 1920;
		dwHigh = 1080;
		dwCodecHigh = 1088;
		break;
	case VIDEOSTANDARD_HD1080p_30:
		strHint = "1080/30P";				//HD1080-30p
		dwWidth = 1920;
		dwHigh = 1080;
		dwCodecHigh = 1088;
		break;
	case VIDEOSTANDARD_HD1080psf_2398:
		strHint = "1080/23.98Psf";			//HD1080-23.98Psf
		dwWidth = 1920;
		dwHigh = 1080;
		dwCodecHigh = 1088;
		break;
	case VIDEOSTANDARD_HD1080psf_24:
		strHint = "1080/24Psf";				//HD1080-24Psf
		dwWidth = 1920;
		dwHigh = 1080;
		dwCodecHigh = 1088;
		break;
	case VIDEOSTANDARD_HD1080psf_25:
		strHint = "1080/25Psf";				//HD1080-25Psf
		dwWidth = 1920;
		dwHigh = 1080;
		dwCodecHigh = 1088;
		break;
	case VIDEOSTANDARD_HD1080psf_2997:
		strHint = "1080/29.97Psf";			//HD1080-29.97Psf
		dwWidth = 1920;
		dwHigh = 1080;
		dwCodecHigh = 1088;
		break;
	case VIDEOSTANDARD_HD1080psf_30:
		strHint = "1080/30Psf";				//HD1080-30Psf
		dwWidth = 1920;
		dwHigh = 1080;
		dwCodecHigh = 1088;
		break;
	case VIDEOSTANDARD_HD1080P_50:
		strHint = "1080/50P";				//HD1080-50P
		dwWidth = 1920;
		dwHigh = 1080;
		dwCodecHigh = 1088;
		break;
	case VIDEOSTANDARD_HD1080P_5994:
		strHint = "1080/59.94P";			//HD1080-59.94P
		dwWidth = 1920;
		dwHigh = 1080;
		dwCodecHigh = 1088;
		break;
	case VIDEOSTANDARD_HD1080P_60:
		strHint = "1080/60P";				//HD1080-60P
		dwWidth = 1920;
		dwHigh = 1080;
		dwCodecHigh = 1088;
		break;
	case VIDEOSTANDARD_2K1080P_2398:
		strHint = "2048X1080/23.98P";		//2K1080P_23.98
		dwWidth = 2048;
		dwHigh = 1080;
		dwCodecHigh = 1088;
		break;
	case VIDEOSTANDARD_2K1080P_24:
		strHint = "2048X1080/24P";			//2K1080P_24
		dwWidth = 2048;
		dwHigh = 1080;
		dwCodecHigh = 1088;
		break;
	case VIDEOSTANDARD_2K1080P_48:
		strHint = "2048X1080/48P";			//2K1080P_48
		dwWidth = 2048;
		dwHigh = 1080;
		dwCodecHigh = 1088;
		break;
	case VIDEOSTANDARD_2K1080Psf_2398:
		strHint = "2048X1080/23.98Psf";		//2K1080Psf_23.98
		dwWidth = 2048;
		dwHigh = 1080;
		dwCodecHigh = 1088;
		break;
	case VIDEOSTANDARD_2K1080Psf_24:
		strHint = "2048X1080/24Psf";		//2K1080Psf_24
		dwWidth = 2048;
		dwHigh = 1080;
		dwCodecHigh = 1088;
		break;
	case VIDEOSTANDARD_2K1556P_2398:
		strHint = "2048X1556/23.98P";		//2K1556P_23.98
		dwWidth = 2048;
		dwHigh = 1556;
		dwCodecHigh = 1552;
		break;
	case VIDEOSTANDARD_2K1556P_24:
		strHint = "2048X1556/24P";			//2K1556P_24
		dwWidth = 2048;
		dwHigh = 1556;
		dwCodecHigh = 1552;
		break;
	case VIDEOSTANDARD_2K1556Psf_2398:
		strHint = "2048X1556/23.98Psf";		//2K1556Psf_23.98
		dwWidth = 2048;
		dwHigh = 1556;
		dwCodecHigh = 1552;
		break;
	case VIDEOSTANDARD_2K1556Psf_24:
		strHint = "2048X1556/24Psf";		//2K1556Psf_24
		dwWidth = 2048;
		dwHigh = 1556;
		dwCodecHigh = 1552;
		break;
	case VIDEOSTANDARD_4K2160P_24:
		strHint = "4096X2160/24P";			//4K2160P_24
		dwWidth = 4096;
		dwHigh = 2160;
		dwCodecHigh = 2160;
		break;
	case VIDEOSTANDARD_2398_P:
		strHint = "***/23.98P";				//Unknow-23.98
		break;
	case VIDEOSTANDARD_2398_Psf:
		strHint = "***/23.98Psf";
		break;
	case VIDEOSTANDARD_24_P:
		strHint = "***/24P";				//Unknow-24
		break;
	case VIDEOSTANDARD_24_Psf:
		strHint = "***/24Psf";
		break;
	case VIDEOSTANDARD_25_I:
		strHint = "***/25I";				//Unknow-25
		break;
	case VIDEOSTANDARD_25_P:
		strHint = "***/25P";
		break;
	case VIDEOSTANDARD_25_Psf:
		strHint = "***/25Psf";
		break;
	case VIDEOSTANDARD_2997_I:
		strHint = "***/29.97I";				//Unknow-29.97
		break;
	case VIDEOSTANDARD_2997_P:
		strHint = "***/29.97P";
		break;
	case VIDEOSTANDARD_2997_Psf:
		strHint = "***/29.97Psf";
		break;
	case VIDEOSTANDARD_30_I:
		strHint = "***/30I";				//Unknow-30
		break;
	case VIDEOSTANDARD_30_P:
		strHint = "***/30P";
		break;
	case VIDEOSTANDARD_30_Psf:
		strHint = "***/30Psf";
		break;
	case VIDEOSTANDARD_48_P:
		strHint = "***/48P";				//Unknow-48
		break;
	case VIDEOSTANDARD_50_P:
		strHint = "***/50P";				//Unknow-50
		break;
	case VIDEOSTANDARD_5994_P:
		strHint = "***/59.94P";				//Unknow-59.94
		break;
	case VIDEOSTANDARD_60_P:
		strHint = "***/60P";				//Unknow-60
		break;
	}
};

//	获得视频制式的名称。
inline std::string GetVideoStandardHint(VIDEO_STANDARD enumVideoStandard)
{
	std::string strHint;
	uint32_t dwWidth, dwHigh, dwCodecHigh;
	GetVideoStandardParam(enumVideoStandard, strHint, dwWidth, dwHigh, dwCodecHigh);
	return strHint;
};

//获得视频制式的水平分辨率。
inline uint32_t _GetWidth(VIDEO_STANDARD enumVideoStandard)
{
	std::string strHint;
	uint32_t dwWidth, dwHigh, dwCodecHigh;
	GetVideoStandardParam(enumVideoStandard, strHint, dwWidth, dwHigh, dwCodecHigh);
	return dwWidth;
};

//获得视频制式的垂直分辨率。
inline uint32_t _GetHeight(VIDEO_STANDARD enumVideoStandard)
{
	std::string strHint;
	uint32_t dwWidth, dwHigh, dwCodecHigh;
	GetVideoStandardParam(enumVideoStandard, strHint, dwWidth, dwHigh, dwCodecHigh);
	return dwHigh;
};

//视频图像压缩编码的水平大小,是16的倍数
inline uint32_t _GetCodecWidth(VIDEO_STANDARD enumVideoStandard)
{
	return _GetWidth(enumVideoStandard);
};

//视频图像压缩编码的垂直大小,是16的倍数
inline uint32_t _GetCodecHeight(VIDEO_STANDARD enumVideoStandard)
{
	std::string strHint;
	uint32_t dwWidth, dwHigh, dwCodecHigh;
	GetVideoStandardParam(enumVideoStandard, strHint, dwWidth, dwHigh, dwCodecHigh);
	return dwCodecHigh;
};

enum VIDEO_CLASS		//视频制式分类
{
	VIDEOCLASS_UNKNOW			= 0x00000000,
	VIDEOCLASS_SD				= 0x00000001,
	VIDEOCLASS_HD1080i			= 0x00000002,
	VIDEOCLASS_HD1080p			= 0x00000004,
	VIDEOCLASS_HD1080psf		= 0x00000008,
	VIDEOCLASS_HD720p			= 0x00000010,
	VIDEOCLASS_HD1080P			= 0x00000100,
	VIDEOCLASS_2K1080P			= 0x00000200,
	VIDEOCLASS_2K1080Psf		= 0x00000400,
	VIDEOCLASS_2K1556P			= 0x00000800,
	VIDEOCLASS_2K1556Psf		= 0x00001000,
	VIDEOCLASS_4K2160P			= 0x00008000,
	VIDEOCLASS_I_RateScale		= 0x00000020,
	VIDEOCLASS_P_RateScale		= 0x00000040,
	VIDEOCLASS_Psf_RateScale	= 0x00000080,
};

//得到视频制式分类的名称
inline std::string GetVideoClassHint(VIDEO_CLASS enumVideoClass)
{
	std::string	strVideoClass = "Unknow";
	switch (enumVideoClass)
	{
	case VIDEOCLASS_SD:
		strVideoClass = "SD";
		break;
	case VIDEOCLASS_HD1080i:
		strVideoClass = "HD 1080i";
		break;
	case VIDEOCLASS_HD720p:
		strVideoClass = "HD 720p";
		break;
	case VIDEOCLASS_HD1080p:
		strVideoClass = "HD 1080p";
		break;
	case VIDEOCLASS_HD1080psf:
		strVideoClass = "HD 1080psf";
		break;
	case VIDEOCLASS_HD1080P:
		strVideoClass = "HD 1080P";
		break;
	case VIDEOCLASS_2K1080P:
		strVideoClass = "2K 1080P";
		break;
	case VIDEOCLASS_2K1080Psf:
		strVideoClass = "2K 1080Psf";
		break;
	case VIDEOCLASS_2K1556P:
		strVideoClass = "2K 1556P";
		break;
	case VIDEOCLASS_2K1556Psf:
		strVideoClass = "2K 1556Psf";
		break;
	case VIDEOCLASS_4K2160P:
		strVideoClass = "4K 2160P";
		break;
	case VIDEOCLASS_I_RateScale:
		strVideoClass = "I_RateScale";
		break;
	case VIDEOCLASS_P_RateScale:
		strVideoClass = "P_RateScale";
		break;
	case VIDEOCLASS_Psf_RateScale:
		strVideoClass = "Psf_RateScale";
		break;
	}
	return strVideoClass;
};

//从视频制式标准得到视频制式分类
inline VIDEO_CLASS _GetVideoClass(VIDEO_STANDARD enumVideoStandard)
{
	switch (enumVideoStandard)
	{
	case VIDEOSTANDARD_PAL:
	case VIDEOSTANDARD_NTSC2997:
	case VIDEOSTANDARD_NTSC30:
		return VIDEOCLASS_SD;

	case VIDEOSTANDARD_HD1080i_25:
	case VIDEOSTANDARD_HD1080i_2997:
	case VIDEOSTANDARD_HD1080i_30:
		return VIDEOCLASS_HD1080i;

	case VIDEOSTANDARD_HD720p_2398:
	case VIDEOSTANDARD_HD720p_24:
	case VIDEOSTANDARD_HD720p_25:
	case VIDEOSTANDARD_HD720p_2997:
	case VIDEOSTANDARD_HD720p_30:
	case VIDEOSTANDARD_HD720p_50:
	case VIDEOSTANDARD_HD720p_5994:
	case VIDEOSTANDARD_HD720p_60:
		return VIDEOCLASS_HD720p;

	case VIDEOSTANDARD_HD1080p_2398:
	case VIDEOSTANDARD_HD1080p_24:
	case VIDEOSTANDARD_HD1080p_25:
	case VIDEOSTANDARD_HD1080p_2997:
	case VIDEOSTANDARD_HD1080p_30:
		return VIDEOCLASS_HD1080p;

	case VIDEOSTANDARD_HD1080psf_2398:
	case VIDEOSTANDARD_HD1080psf_24:
	case VIDEOSTANDARD_HD1080psf_25:
	case VIDEOSTANDARD_HD1080psf_2997:
	case VIDEOSTANDARD_HD1080psf_30:
		return VIDEOCLASS_HD1080psf;

	case VIDEOSTANDARD_HD1080P_50:
	case VIDEOSTANDARD_HD1080P_5994:
	case VIDEOSTANDARD_HD1080P_60:
		return VIDEOCLASS_HD1080P;

	case VIDEOSTANDARD_2K1080P_2398:
	case VIDEOSTANDARD_2K1080P_24:
	case VIDEOSTANDARD_2K1080P_48:
		return VIDEOCLASS_2K1080P;

	case VIDEOSTANDARD_2K1080Psf_2398:
	case VIDEOSTANDARD_2K1080Psf_24:
		return VIDEOCLASS_2K1080Psf;

	case VIDEOSTANDARD_2K1556P_2398:
	case VIDEOSTANDARD_2K1556P_24:
		return VIDEOCLASS_2K1556P;

	case VIDEOSTANDARD_2K1556Psf_2398:
	case VIDEOSTANDARD_2K1556Psf_24:
		return VIDEOCLASS_2K1556Psf;

	case VIDEOSTANDARD_4K2160P_24:
		return VIDEOCLASS_4K2160P;

	case VIDEOSTANDARD_25_I:
	case VIDEOSTANDARD_2997_I:
	case VIDEOSTANDARD_30_I:
		return VIDEOCLASS_I_RateScale;

	case VIDEOSTANDARD_2398_P:
	case VIDEOSTANDARD_24_P:
	case VIDEOSTANDARD_25_P:
	case VIDEOSTANDARD_2997_P:
	case VIDEOSTANDARD_30_P:
	case VIDEOSTANDARD_48_P:
	case VIDEOSTANDARD_50_P:
	case VIDEOSTANDARD_5994_P:
	case VIDEOSTANDARD_60_P:
		return VIDEOCLASS_P_RateScale;

	case VIDEOSTANDARD_2398_Psf:
	case VIDEOSTANDARD_24_Psf:
	case VIDEOSTANDARD_25_Psf:
	case VIDEOSTANDARD_2997_Psf:
	case VIDEOSTANDARD_30_Psf:
		return VIDEOCLASS_Psf_RateScale;
	}
	return VIDEOCLASS_UNKNOW;
};

//------------------------------------------------------------------------------------------------------------
#define c2398FRAMES_FIELD_RATE		48000		// the frequency of the 23.98 field.
#define	c2398FRAMES_FRAME_RATE		24000		// the frequency of the 23.98 frame.
#define c2398FRAMES_SCALE			1001

#define c24FRAMES_FIELD_RATE		48			// the frequency of the 24 field.
#define	c24FRAMES_FRAME_RATE		24			// the frequency of the 24 frame.
#define c24FRAMES_SCALE				1

#define c25FRAMES_FIELD_RATE		50			// the frequency of the 25 field.
#define	c25FRAMES_FRAME_RATE		25			// the frequency of the 25 frame.
#define c25FRAMES_SCALE				1

#define c2997FRAME_FIELD_RATE		60000		// the frequency of the 29.97 field.
#define	c2997FRAME_FRAME_RATE		30000		// the frequency of the 29.97 frame.
#define c2997FRAME_SCALE			1001		// 

#define c30FRAMES_FIELD_RATE		60			// the frequency of the 30 field.
#define	c30FRAMES_FRAME_RATE		30			// the frequency of the 30 frame.
#define c30FRAMES_SCALE				1

#define c48FRAMES_FIELD_RATE		96			// the frequency of the 48 field.
#define	c48FRAMES_FRAME_RATE		48			// the frequency of the 48 frame.
#define c48FRAMES_SCALE				1

#define	c50FRAMES_FIELD_RATE		100			// the frequency of the 50 field.
#define	c50FRAMES_FRAME_RATE		50			// the frequency of the 50 frame.
#define c50FRAMES_SCALE				1

#define	c5994FRAMES_FIELD_RATE		120000		// the frequency of the 59.94 field.
#define	c5994FRAMES_FRAME_RATE		60000		// the frequency of the 59.94 frame.
#define c5994FRAMES_SCALE			1001

#define	c60FRAMES_FIELD_RATE		120			// the frequency of the 60 field.
#define	c60FRAMES_FRAME_RATE		60			// the frequency of the 60 frame.
#define c60FRAMES_SCALE				1
#define LONG_M_CAL	2147483648.0
//------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------
// NUM/DENOM = 10000000 * SCALE/RATE
//------------------------------------------------------------------------------------------------------------
#define cNANO2398_NUM				625625
#define cNANO2398_DENOM				3

#define cNANO24_NUM					625000
#define cNANO24_DENOM				3

#define cNANO25_NUM					200000
#define cNANO25_DENOM				1

#define cNANO2997_NUM				1001000			// those is for 100ns unit reference
#define cNANO2997_DENOM				6

#define cNANO30_NUM					1000000
#define cNANO30_DENOM				6

#define cNANO48_NUM					1250000
#define cNANO48_DENOM				3

#define cNANO50_NUM					400000
#define cNANO50_DENOM				1

#define cNANO5994_NUM				1001000			// those is for 100ns unit reference
#define cNANO5994_DENOM				3

#define cNANO60_NUM					1000000
#define cNANO60_DENOM				3
//------------------------------------------------------------------------------------------------------------

//从视频制式标准得到帧率
inline void	GetStandardRateScale(VIDEO_STANDARD enumVideoStandard, uint32_t &dwRate, uint32_t &dwScale)
{
	switch (enumVideoStandard)
	{
	case VIDEOSTANDARD_HD720p_2398:
	case VIDEOSTANDARD_HD1080p_2398:
	case VIDEOSTANDARD_HD1080psf_2398:
	case VIDEOSTANDARD_2K1080P_2398:
	case VIDEOSTANDARD_2K1080Psf_2398:
	case VIDEOSTANDARD_2K1556P_2398:
	case VIDEOSTANDARD_2K1556Psf_2398:
	case VIDEOSTANDARD_2398_P:
	case VIDEOSTANDARD_2398_Psf:
		dwRate = c2398FRAMES_FRAME_RATE;
		dwScale = c2398FRAMES_SCALE;
		break;
	case VIDEOSTANDARD_HD720p_24:
	case VIDEOSTANDARD_HD1080p_24:
	case VIDEOSTANDARD_HD1080psf_24:
	case VIDEOSTANDARD_2K1080P_24:
	case VIDEOSTANDARD_2K1080Psf_24:
	case VIDEOSTANDARD_2K1556P_24:
	case VIDEOSTANDARD_2K1556Psf_24:
	case VIDEOSTANDARD_4K2160P_24:
	case VIDEOSTANDARD_24_P:
	case VIDEOSTANDARD_24_Psf:
		dwRate = c24FRAMES_FRAME_RATE;
		dwScale = c24FRAMES_SCALE;
		break;
	case VIDEOSTANDARD_PAL:
	case VIDEOSTANDARD_HD1080i_25:
	case VIDEOSTANDARD_HD720p_25:
	case VIDEOSTANDARD_HD1080p_25:
	case VIDEOSTANDARD_HD1080psf_25:
	case VIDEOSTANDARD_25_I:
	case VIDEOSTANDARD_25_P:
	case VIDEOSTANDARD_25_Psf:
		dwRate = c25FRAMES_FRAME_RATE;
		dwScale = c25FRAMES_SCALE;
		break;
	case VIDEOSTANDARD_NTSC2997:
	case VIDEOSTANDARD_HD1080i_2997:
	case VIDEOSTANDARD_HD720p_2997:
	case VIDEOSTANDARD_HD1080p_2997:
	case VIDEOSTANDARD_HD1080psf_2997:
	case VIDEOSTANDARD_2997_I:
	case VIDEOSTANDARD_2997_P:
	case VIDEOSTANDARD_2997_Psf:
		dwRate = c2997FRAME_FRAME_RATE;
		dwScale = c2997FRAME_SCALE;
		break;
	case VIDEOSTANDARD_NTSC30:
	case VIDEOSTANDARD_HD1080i_30:
	case VIDEOSTANDARD_HD720p_30:
	case VIDEOSTANDARD_HD1080p_30:
	case VIDEOSTANDARD_HD1080psf_30:
	case VIDEOSTANDARD_30_I:
	case VIDEOSTANDARD_30_P:
	case VIDEOSTANDARD_30_Psf:
		dwRate = c30FRAMES_FRAME_RATE;
		dwScale = c30FRAMES_SCALE;
		break;
	case VIDEOSTANDARD_2K1080P_48:
	case VIDEOSTANDARD_48_P:
		dwRate = c48FRAMES_FRAME_RATE;
		dwScale = c48FRAMES_SCALE;
		break;
	case VIDEOSTANDARD_HD720p_50:
	case VIDEOSTANDARD_HD1080P_50:
	case VIDEOSTANDARD_50_P:
		dwRate = c50FRAMES_FRAME_RATE;
		dwScale = c50FRAMES_SCALE;
		break;
	case VIDEOSTANDARD_HD720p_5994:
	case VIDEOSTANDARD_HD1080P_5994:
	case VIDEOSTANDARD_5994_P:
		dwRate = c5994FRAMES_FRAME_RATE;
		dwScale = c5994FRAMES_SCALE;
		break;
	case VIDEOSTANDARD_HD720p_60:
	case VIDEOSTANDARD_HD1080P_60:
	case VIDEOSTANDARD_60_P:
		dwRate = c60FRAMES_FRAME_RATE;
		dwScale = c60FRAMES_SCALE;
		break;
	default:
		dwRate = 0;
		dwScale = 1;
		break;
	}
};

//从帧率和分类得到视频制式标准
inline VIDEO_STANDARD GetStandardRateScale(uint32_t dwRate, uint32_t dwScale, VIDEO_CLASS enumVideoClass)
{
	if (dwRate*c2398FRAMES_SCALE == dwScale*c2398FRAMES_FRAME_RATE)
	{
		if (enumVideoClass == VIDEOCLASS_HD720p)
			return VIDEOSTANDARD_HD720p_2398;
		else if (enumVideoClass == VIDEOCLASS_HD1080p)
			return VIDEOSTANDARD_HD1080p_2398;
		else if (enumVideoClass == VIDEOCLASS_HD1080psf)
			return VIDEOSTANDARD_HD1080psf_2398;
		else if (enumVideoClass == VIDEOCLASS_2K1080P)
			return VIDEOSTANDARD_2K1080P_2398;
		else if (enumVideoClass == VIDEOCLASS_2K1080Psf)
			return VIDEOSTANDARD_2K1080Psf_2398;
		else if (enumVideoClass == VIDEOCLASS_2K1556P)
			return VIDEOSTANDARD_2K1556P_2398;
		else if (enumVideoClass == VIDEOCLASS_2K1556Psf)
			return VIDEOSTANDARD_2K1556Psf_2398;
		else if (enumVideoClass == VIDEOCLASS_P_RateScale)
			return VIDEOSTANDARD_2398_P;
		else if (enumVideoClass == VIDEOCLASS_Psf_RateScale)
			return VIDEOSTANDARD_2398_Psf;
	}
	else if (dwRate*c24FRAMES_SCALE == dwScale*c24FRAMES_FRAME_RATE)
	{
		if (enumVideoClass == VIDEOCLASS_HD720p)
			return VIDEOSTANDARD_HD720p_24;
		else if (enumVideoClass == VIDEOCLASS_HD1080p)
			return VIDEOSTANDARD_HD1080p_24;
		else if (enumVideoClass == VIDEOCLASS_HD1080psf)
			return VIDEOSTANDARD_HD1080psf_24;
		else if (enumVideoClass == VIDEOCLASS_2K1080P)
			return VIDEOSTANDARD_2K1080P_24;
		else if (enumVideoClass == VIDEOCLASS_2K1080Psf)
			return VIDEOSTANDARD_2K1080Psf_24;
		else if (enumVideoClass == VIDEOCLASS_2K1556P)
			return VIDEOSTANDARD_2K1556P_24;
		else if (enumVideoClass == VIDEOCLASS_2K1556Psf)
			return VIDEOSTANDARD_2K1556Psf_24;
		else if (enumVideoClass == VIDEOCLASS_4K2160P)
			return VIDEOSTANDARD_4K2160P_24;
		else if (enumVideoClass == VIDEOCLASS_P_RateScale)
			return VIDEOSTANDARD_24_P;
		else if (enumVideoClass == VIDEOCLASS_Psf_RateScale)
			return VIDEOSTANDARD_24_Psf;
	}
	else if (dwRate*c25FRAMES_SCALE == dwScale*c25FRAMES_FRAME_RATE)
	{
		if (enumVideoClass == VIDEOCLASS_SD)
			return VIDEOSTANDARD_PAL;
		else if (enumVideoClass == VIDEOCLASS_HD1080i)
			return VIDEOSTANDARD_HD1080i_25;
		else if (enumVideoClass == VIDEOCLASS_HD720p)
			return VIDEOSTANDARD_HD720p_25;
		else if (enumVideoClass == VIDEOCLASS_HD1080p)
			return VIDEOSTANDARD_HD1080p_25;
		else if (enumVideoClass == VIDEOCLASS_HD1080psf)
			return VIDEOSTANDARD_HD1080psf_25;
		else if (enumVideoClass == VIDEOCLASS_I_RateScale)
			return VIDEOSTANDARD_25_I;
		else if (enumVideoClass == VIDEOCLASS_P_RateScale)
			return VIDEOSTANDARD_25_P;
		else if (enumVideoClass == VIDEOCLASS_Psf_RateScale)
			return VIDEOSTANDARD_25_Psf;
	}
	else if (dwRate*c2997FRAME_SCALE == dwScale*c2997FRAME_FRAME_RATE)
	{
		if (enumVideoClass == VIDEOCLASS_SD)
			return VIDEOSTANDARD_NTSC2997;
		else if (enumVideoClass == VIDEOCLASS_HD1080i)
			return VIDEOSTANDARD_HD1080i_2997;
		else if (enumVideoClass == VIDEOCLASS_HD720p)
			return VIDEOSTANDARD_HD720p_2997;
		else if (enumVideoClass == VIDEOCLASS_HD1080p)
			return VIDEOSTANDARD_HD1080p_2997;
		else if (enumVideoClass == VIDEOCLASS_HD1080psf)
			return VIDEOSTANDARD_HD1080psf_2997;
		else if (enumVideoClass == VIDEOCLASS_I_RateScale)
			return VIDEOSTANDARD_2997_I;
		else if (enumVideoClass == VIDEOCLASS_P_RateScale)
			return VIDEOSTANDARD_2997_P;
		else if (enumVideoClass == VIDEOCLASS_Psf_RateScale)
			return VIDEOSTANDARD_2997_Psf;
	}
	else if (dwRate*c30FRAMES_SCALE == dwScale*c30FRAMES_FRAME_RATE)
	{
		if (enumVideoClass == VIDEOCLASS_SD)
			return VIDEOSTANDARD_NTSC30;
		else if (enumVideoClass == VIDEOCLASS_HD1080i)
			return VIDEOSTANDARD_HD1080i_30;
		else if (enumVideoClass == VIDEOCLASS_HD720p)
			return VIDEOSTANDARD_HD720p_30;
		else if (enumVideoClass == VIDEOCLASS_HD1080p)
			return VIDEOSTANDARD_HD1080p_30;
		else if (enumVideoClass == VIDEOCLASS_HD1080psf)
			return VIDEOSTANDARD_HD1080psf_30;
		else if (enumVideoClass == VIDEOCLASS_I_RateScale)
			return VIDEOSTANDARD_30_I;
		else if (enumVideoClass == VIDEOCLASS_P_RateScale)
			return VIDEOSTANDARD_30_P;
		else if (enumVideoClass == VIDEOCLASS_Psf_RateScale)
			return VIDEOSTANDARD_30_Psf;
	}
	else if (dwRate*c48FRAMES_SCALE == dwScale*c48FRAMES_FRAME_RATE)
	{
		if (enumVideoClass == VIDEOCLASS_2K1080P)
			return VIDEOSTANDARD_2K1080P_48;
		else if (enumVideoClass == VIDEOCLASS_P_RateScale)
			return VIDEOSTANDARD_48_P;
	}
	else if (dwRate*c50FRAMES_SCALE == dwScale*c50FRAMES_FRAME_RATE)
	{
		if (enumVideoClass == VIDEOCLASS_HD720p)
			return VIDEOSTANDARD_HD720p_50;
		else if (enumVideoClass == VIDEOCLASS_HD1080P)
			return VIDEOSTANDARD_HD1080P_50;
		else if (enumVideoClass == VIDEOCLASS_P_RateScale)
			return VIDEOSTANDARD_50_P;
	}
	else if (dwRate*c5994FRAMES_SCALE == dwScale*c5994FRAMES_FRAME_RATE)
	{
		if (enumVideoClass == VIDEOCLASS_HD720p)
			return VIDEOSTANDARD_HD720p_5994;
		else if (enumVideoClass == VIDEOCLASS_HD1080P)
			return VIDEOSTANDARD_HD1080P_5994;
		else if (enumVideoClass == VIDEOCLASS_P_RateScale)
			return VIDEOSTANDARD_5994_P;
	}
	else if (dwRate*c60FRAMES_SCALE == dwScale*c60FRAMES_FRAME_RATE)
	{
		if (enumVideoClass == VIDEOCLASS_HD720p)
			return VIDEOSTANDARD_HD720p_60;
		else if (enumVideoClass == VIDEOCLASS_HD1080P)
			return VIDEOSTANDARD_HD1080P_60;
		else if (enumVideoClass == VIDEOCLASS_P_RateScale)
			return VIDEOSTANDARD_60_P;
	}

	return VIDEOSTANDARD_UNKNOW;
};

inline void GetStandardNumDenom(VIDEO_STANDARD enumVideoStandard, uint32_t &dwNUM, uint32_t &dwDENOM)
{
	dwNUM = cNANO25_NUM;
	dwDENOM = cNANO25_DENOM;
	switch (enumVideoStandard)
	{
	case VIDEOSTANDARD_HD720p_2398:
	case VIDEOSTANDARD_HD1080p_2398:
	case VIDEOSTANDARD_HD1080psf_2398:
	case VIDEOSTANDARD_2K1080P_2398:
	case VIDEOSTANDARD_2K1080Psf_2398:
	case VIDEOSTANDARD_2K1556P_2398:
	case VIDEOSTANDARD_2K1556Psf_2398:
	case VIDEOSTANDARD_2398_P:
	case VIDEOSTANDARD_2398_Psf:
		dwNUM = cNANO2398_NUM;
		dwDENOM = cNANO2398_DENOM;
		break;
	case VIDEOSTANDARD_HD720p_24:
	case VIDEOSTANDARD_HD1080p_24:
	case VIDEOSTANDARD_HD1080psf_24:
	case VIDEOSTANDARD_2K1080P_24:
	case VIDEOSTANDARD_2K1080Psf_24:
	case VIDEOSTANDARD_2K1556P_24:
	case VIDEOSTANDARD_2K1556Psf_24:
	case VIDEOSTANDARD_4K2160P_24:
	case VIDEOSTANDARD_24_P:
	case VIDEOSTANDARD_24_Psf:
		dwNUM = cNANO24_NUM;
		dwDENOM = cNANO24_DENOM;
		break;
	case VIDEOSTANDARD_PAL:
	case VIDEOSTANDARD_HD1080i_25:
	case VIDEOSTANDARD_HD720p_25:
	case VIDEOSTANDARD_HD1080p_25:
	case VIDEOSTANDARD_HD1080psf_25:
	case VIDEOSTANDARD_25_I:
	case VIDEOSTANDARD_25_P:
	case VIDEOSTANDARD_25_Psf:
		dwNUM = cNANO25_NUM;
		dwDENOM = cNANO25_DENOM;
		break;
	case VIDEOSTANDARD_NTSC2997:
	case VIDEOSTANDARD_HD1080i_2997:
	case VIDEOSTANDARD_HD720p_2997:
	case VIDEOSTANDARD_HD1080p_2997:
	case VIDEOSTANDARD_HD1080psf_2997:
	case VIDEOSTANDARD_2997_I:
	case VIDEOSTANDARD_2997_P:
	case VIDEOSTANDARD_2997_Psf:
		dwNUM = cNANO2997_NUM;
		dwDENOM = cNANO2997_DENOM;
		break;
	case VIDEOSTANDARD_NTSC30:
	case VIDEOSTANDARD_HD1080i_30:
	case VIDEOSTANDARD_HD720p_30:
	case VIDEOSTANDARD_HD1080p_30:
	case VIDEOSTANDARD_HD1080psf_30:
	case VIDEOSTANDARD_30_I:
	case VIDEOSTANDARD_30_P:
	case VIDEOSTANDARD_30_Psf:
		dwNUM = cNANO30_NUM;
		dwDENOM = cNANO30_DENOM;
		break;
	case VIDEOSTANDARD_2K1080P_48:
	case VIDEOSTANDARD_48_P:
		dwNUM = cNANO48_NUM;
		dwDENOM = cNANO48_DENOM;
		break;
	case VIDEOSTANDARD_HD720p_50:
	case VIDEOSTANDARD_HD1080P_50:
	case VIDEOSTANDARD_50_P:
		dwNUM = cNANO50_NUM;
		dwDENOM = cNANO50_DENOM;
		break;
	case VIDEOSTANDARD_HD720p_5994:
	case VIDEOSTANDARD_HD1080P_5994:
	case VIDEOSTANDARD_5994_P:
		dwNUM = cNANO5994_NUM;
		dwDENOM = cNANO5994_DENOM;
		break;
	case VIDEOSTANDARD_HD720p_60:
	case VIDEOSTANDARD_HD1080P_60:
	case VIDEOSTANDARD_60_P:
		dwNUM = cNANO60_NUM;
		dwDENOM = cNANO60_DENOM;
		break;
	}
};

typedef int64_t REFERENCETIME;			//以100ns为单位的64位整型数,目的是用整数表达帧的时间度量

//依据视频制式转换场数至参考时间度量单位
inline REFERENCETIME _FieldToRT(uint32_t dwFieldCount, VIDEO_STANDARD enumVideoStandard)
{
	uint32_t dwNUM, dwDENOM;
	GetStandardNumDenom(enumVideoStandard, dwNUM, dwDENOM);
	return (((REFERENCETIME)dwFieldCount * (REFERENCETIME)dwNUM) / (REFERENCETIME)dwDENOM);
};

//依据帧率转换场数至参考时间度量单位
inline REFERENCETIME FieldToRT(uint32_t dwFieldCount, uint32_t dwRate, uint32_t dwScale)
{
	return (((REFERENCETIME)dwFieldCount * 10000000 * (REFERENCETIME)dwScale) / (2 * (REFERENCETIME)dwRate));
};

//依据视频制式转换帧数至参考时间度量单位
inline REFERENCETIME FrameToRT(uint32_t dwFrameCount, VIDEO_STANDARD enumVideoStandard)
{
	return _FieldToRT(2 * dwFrameCount, enumVideoStandard);
};

//依据帧率转换帧数至参考时间度量单位
inline REFERENCETIME _FrameToRT(uint32_t dwFrameCount, uint32_t dwRate, uint32_t dwScale)
{
	return FieldToRT(2 * dwFrameCount, dwRate, dwScale);
};

//依据视频制式转换参考时间度量单位至场数
inline uint32_t _RTToField(REFERENCETIME rt, VIDEO_STANDARD enumVideoStandard)
{
	uint32_t dwNUM, dwDENOM;
	GetStandardNumDenom(enumVideoStandard, dwNUM, dwDENOM);
	if (rt < 0)
		return (uint32_t)((rt * (REFERENCETIME)dwDENOM - ((REFERENCETIME)dwNUM / 2)) / (REFERENCETIME)dwNUM);
	else
		return (uint32_t)((rt * (REFERENCETIME)dwDENOM + ((REFERENCETIME)dwNUM / 2)) / (REFERENCETIME)dwNUM);
};

//依据帧率转换参考时间度量单位至场数
inline uint32_t RTToField(REFERENCETIME rt, uint32_t dwRate, uint32_t dwScale)
{
	return (uint32_t)(rt * (2 * (REFERENCETIME)dwRate) / (REFERENCETIME)dwScale / 10000000);
};

//依据帧率转换参考时间度量单位至帧数
inline uint32_t _RTToFrame(REFERENCETIME rt, uint32_t dwRate, uint32_t dwScale)
{
	return RTToField(rt, dwRate, dwScale) / 2;
};


//依据视频制式转换场数至浮点型秒数
inline double FieldToSec(uint32_t dwFieldCount, VIDEO_STANDARD enumVideoStandard)
{
	uint32_t	dwRate, dwScale;
	GetStandardRateScale(enumVideoStandard, dwRate, dwScale);
	return ((double)dwFieldCount * (double)dwScale / (2.0*(double)dwRate));
};

//依据帧率转换场数至浮点型秒数
inline double FieldToSec(uint32_t dwFieldCount, uint32_t dwRate, uint32_t dwScale)
{
	return ((double)dwFieldCount * (double)dwScale / (2.0*(double)dwRate));
};

//依据视频制式转换帧数至浮点型秒数
inline double FrameToSec(uint32_t dwFrameCount, VIDEO_STANDARD enumVideoStandard)
{
	uint32_t	dwRate, dwScale;
	GetStandardRateScale(enumVideoStandard, dwRate, dwScale);
	return ((double)dwFrameCount * (double)dwScale / (double)dwRate);
};

//依据帧率转换帧数至浮点型秒数
inline double FrameToSec(uint32_t dwFrameCount, uint32_t dwRate, uint32_t dwScale)
{
	return ((double)dwFrameCount * (double)dwScale / (double)dwRate);
};

//依据视频制式转换浮点型秒数至场数
inline uint32_t SecToField(double dblSeconds, VIDEO_STANDARD enumVideoStandard)
{
	uint32_t	dwRate, dwScale;
	GetStandardRateScale(enumVideoStandard, dwRate, dwScale);

	// Add the 0.5 to account for any truncation errors
	if (dblSeconds < 0)
		return uint32_t(-0.5 + ((dblSeconds * 2.0 * (double)dwRate) / (double)dwScale));
	else
		return uint32_t(0.5 + ((dblSeconds * 2.0 * (double)dwRate) / (double)dwScale));
};

//依据帧率转换浮点型秒数至场数
inline uint32_t _SecToField(double dblSeconds, uint32_t dwRate, uint32_t dwScale)
{
	if (dblSeconds < 0)
		return uint32_t(-0.5 + ((dblSeconds * 2.0 * (double)dwRate) / (double)dwScale));
	else
		return uint32_t(0.5 + ((dblSeconds * 2.0 * (double)dwRate) / (double)dwScale));
};

//依据视频制式转换浮点型秒数至帧数
inline uint32_t _SecToFrame(double dblSeconds, VIDEO_STANDARD enumVideoStandard)
{
	uint32_t	dwRate, dwScale;
	GetStandardRateScale(enumVideoStandard, dwRate, dwScale);

	// Add the 0.5 to account for any truncation errors
	if (dblSeconds < 0)
		return uint32_t(-0.5 + ((dblSeconds * (double)dwRate) / (double)dwScale));
	else
		return uint32_t(0.5 + ((dblSeconds * (double)dwRate) / (double)dwScale));
};

//依据帧率转换浮点型秒数至帧数
inline uint32_t _SecToFrame(double dblSeconds, uint32_t dwRate, uint32_t dwScale)
{
	if (dblSeconds < 0)
		return uint32_t(-0.5 + ((dblSeconds * (double)dwRate) / (double)dwScale));
	else
		return uint32_t(0.5 + ((dblSeconds * (double)dwRate) / (double)dwScale));
};

//依据视频制式转换音频采样数至帧数
inline uint32_t GetAudioLengthInFrame(uint64_t llAudioSamples, uint32_t dwSamplesPerSec, VIDEO_STANDARD enumVideoStandard)
{
	return _SecToFrame((double)llAudioSamples / (double)dwSamplesPerSec, enumVideoStandard);
};

//依据帧率转换音频采样数至帧数
inline uint32_t GetAudioLengthInFrame(uint64_t llAudioSamples, uint32_t dwSamplesPerSec, uint32_t dwRate, uint32_t dwScale)
{
	return _SecToFrame((double)llAudioSamples / (double)dwSamplesPerSec, dwRate, dwScale);
};

//转换音频采样数至浮点型秒数
inline double GetAudioTimeInSec(uint64_t llAudioSamples, uint32_t dwSamplesPerSec)
{
	return (double)llAudioSamples / (double)dwSamplesPerSec;
};

//依据视频制式转换帧数至音频采样数
inline uint64_t GetAudioSamplesFromFrame(uint32_t dwFrameCount, uint32_t dwSamplesPerSec, VIDEO_STANDARD enumVideoStandard)
{
	return (uint64_t)(FrameToSec(dwFrameCount, enumVideoStandard) * (double)dwSamplesPerSec + 0.5);
};

//依据帧率转换帧数至音频采样数
inline uint64_t GetAudioSamplesFromFrame(uint32_t dwFrameCount, uint32_t dwSamplesPerSec, uint32_t dwRate, uint32_t dwScale)
{
	return (uint64_t)(FrameToSec(dwFrameCount, dwRate, dwScale) * (double)dwSamplesPerSec + 0.5);
};

//转换浮点型秒数至音频采样数
inline uint64_t GetAudioSamplesFromSec(double dblSeconds, uint32_t dwSamplesPerSec)
{
	return (uint64_t)(dblSeconds*(double)dwSamplesPerSec + 0.5);
};

#define FR_HOUR_24				86400L		// frames per hour in 24 frame mode
#define FR_MINUTE_24			1440L		// frames per minute in 24 frame mode 
#define FR_SECOND_24			24L			// frames per second in 24 frame mode 

#define FR_HOUR_PAL				90000L		// frames per hour in PAL
#define FR_MINUTE_PAL			1500L		// frames per minute in PAL
#define FR_SECOND_PAL			25L			// frames per second in PAL

#define FR_HOUR_2997_ND			108000L		// frames per hour in non-drop 29.97 frame mode
#define FR_HOUR_2997_DROP		107892L		// frames per hour in drop 29.97 frame mode
#define FR_TENMIN_2997_DROP		17982L		// frames per ten minutes in drop 29.97 frame mode
#define FR_MINUTE_2997_DROP		1798L		// frame per minute in drop 29.97 frame mode
#define FR_MINUTE_2997_ND		1800L		// frames per minute in non-drop 29.97 frame mode
#define FR_SECOND_2997			30L			// frames per second, both NTSC modes

#define FR_HOUR_48				172800L		// frames per hour in 48 frame mode 
#define FR_MINUTE_48			2880L		// frames per minute in 48 frame mode 
#define FR_SECOND_48			48L			// frames per second in 48 frame mode 

#define FR_HOUR_50				180000L		// frames per hour in 50 frame mode 
#define FR_MINUTE_50			3000L		// frames per minute in 50 frame mode 
#define FR_SECOND_50			50L			// frames per second in 50 frame mode 

#define FR_HOUR_5994_ND			216000L		// frames per hour in non-drop 59.94 frame mode
#define FR_HOUR_5994_DROP		215784L		// frames per hour in drop 59.94 frame mode
#define FR_TENMIN_5994_DROP		35964L		// frames per ten minutes in 59.94 drop frame mode
#define FR_MINUTE_5994_DROP		3596L		// frame per minute in drop 59.94 frame mode
#define FR_MINUTE_5994_ND		3600L		// frames per minute in non-drop 59.94 frame mode
#define FR_SECOND_5994			60L			// frames per second, both modes 59.94/60 frame mode

#define FR_HOUR_60				216000L		// frames per hour in 60 frame mode
#define FR_MINUTE_60			3600L		// frames per minute in 60 frame mode
#define FR_SECOND_60			60L			// frames per second in 60 frame mode

//依据帧率转换帧数至32位整数, 32位整数的格式是0x(hh-mm-ss-ff)
inline uint32_t FrameToIOPoint(uint32_t dwFrameCount, uint32_t dwRate, uint32_t dwScale)
{
	uint32_t dwReste, hour, minute;

	if (dwRate*c2398FRAMES_SCALE == dwScale*c2398FRAMES_FRAME_RATE)
	{
		hour = (dwFrameCount / FR_HOUR_24);
		dwReste = (dwFrameCount%FR_HOUR_24);
		minute = (dwReste / FR_MINUTE_24);
		dwReste = (dwReste%FR_MINUTE_24);
		return (((hour << 24) & 0xff000000) + ((minute << 16) & 0xff0000) + (((dwReste / FR_SECOND_24) << 8) & 0xff00) + ((dwReste%FR_SECOND_24) & 0xff));
	}
	else if (dwRate*c24FRAMES_SCALE == dwScale*c24FRAMES_FRAME_RATE)
	{
		hour = (dwFrameCount / FR_HOUR_24);
		dwReste = (dwFrameCount%FR_HOUR_24);
		minute = (dwReste / FR_MINUTE_24);
		dwReste = (dwReste%FR_MINUTE_24);
		return (((hour << 24) & 0xff000000) + ((minute << 16) & 0xff0000) + (((dwReste / FR_SECOND_24) << 8) & 0xff00) + ((dwReste%FR_SECOND_24) & 0xff));
	}
	else if (dwRate*c25FRAMES_SCALE == dwScale*c25FRAMES_FRAME_RATE)
	{
		hour = (dwFrameCount / FR_HOUR_PAL);
		dwReste = (dwFrameCount%FR_HOUR_PAL);
		minute = (dwReste / FR_MINUTE_PAL);
		dwReste = (dwReste%FR_MINUTE_PAL);
		return (((hour << 24) & 0xff000000) + ((minute << 16) & 0xff0000) + (((dwReste / FR_SECOND_PAL) << 8) & 0xff00) + ((dwReste%FR_SECOND_PAL) & 0xff));
	}
	else if (dwRate*c2997FRAME_SCALE == dwScale*c2997FRAME_FRAME_RATE)
	{
		hour = (dwFrameCount / FR_HOUR_2997_DROP);
		dwReste = (dwFrameCount%FR_HOUR_2997_DROP);
		minute = 10 * (dwReste / FR_TENMIN_2997_DROP);
		dwReste = (dwReste%FR_TENMIN_2997_DROP);
		if (dwReste >= FR_MINUTE_2997_ND)
		{
			dwReste -= FR_MINUTE_2997_ND;
			minute += 1 + (dwReste / FR_MINUTE_2997_DROP);
			dwReste %= FR_MINUTE_2997_DROP;
			dwReste += 2;
		}
		return (((hour << 24) & 0xff000000) + ((minute << 16) & 0xff0000) + (((dwReste / FR_SECOND_2997) << 8) & 0xff00) + ((dwReste%FR_SECOND_2997) & 0xff));
	}
	else if (dwRate*c30FRAMES_SCALE == dwScale*c30FRAMES_FRAME_RATE)
	{
		hour = (dwFrameCount / FR_HOUR_2997_ND);
		dwReste = (dwFrameCount%FR_HOUR_2997_ND);
		minute = (dwReste / FR_MINUTE_2997_ND);
		dwReste = (dwReste%FR_MINUTE_2997_ND);
		return (((hour << 24) & 0xff000000) + ((minute << 16) & 0xff0000) + (((dwReste / FR_SECOND_2997) << 8) & 0xff00) + ((dwReste%FR_SECOND_2997) & 0xff));
	}
	else if (dwRate*c48FRAMES_SCALE == dwScale*c48FRAMES_FRAME_RATE)
	{
		hour = (dwFrameCount / FR_HOUR_48);
		dwReste = (dwFrameCount%FR_HOUR_48);
		minute = (dwReste / FR_MINUTE_48);
		dwReste = (dwReste%FR_MINUTE_48);
		return (((hour << 24) & 0xff000000) + ((minute << 16) & 0xff0000) + (((dwReste / FR_SECOND_48) << 8) & 0xff00) + ((dwReste%FR_SECOND_48) & 0xff));
	}
	else if (dwRate*c50FRAMES_SCALE == dwScale*c50FRAMES_FRAME_RATE)
	{
		hour = (dwFrameCount / FR_HOUR_50);
		dwReste = (dwFrameCount%FR_HOUR_50);
		minute = (dwReste / FR_MINUTE_50);
		dwReste = (dwReste%FR_MINUTE_50);
		return (((hour << 24) & 0xff000000) + ((minute << 16) & 0xff0000) + (((dwReste / FR_SECOND_50) << 8) & 0xff00) + ((dwReste%FR_SECOND_50) & 0xff));
	}
	else if (dwRate*c5994FRAMES_SCALE == dwScale*c5994FRAMES_FRAME_RATE)
	{
		hour = (dwFrameCount / FR_HOUR_5994_DROP);
		dwReste = (dwFrameCount%FR_HOUR_5994_DROP);
		minute = 10 * (dwReste / FR_TENMIN_5994_DROP);
		dwReste = (dwReste%FR_TENMIN_5994_DROP);
		if (dwReste >= FR_MINUTE_5994_ND)
		{
			dwReste -= FR_MINUTE_5994_ND;
			minute += 1 + (dwReste / FR_MINUTE_5994_DROP);
			dwReste %= FR_MINUTE_5994_DROP;
			dwReste += 2;
		}
		return (((hour << 24) & 0xff000000) + ((minute << 16) & 0xff0000) + (((dwReste / FR_SECOND_5994) << 8) & 0xff00) + ((dwReste%FR_SECOND_5994) & 0xff));
	}
	else if (dwRate*c60FRAMES_SCALE == dwScale*c60FRAMES_FRAME_RATE)
	{
		hour = (dwFrameCount / FR_HOUR_60);
		dwReste = (dwFrameCount%FR_HOUR_60);
		minute = (dwReste / FR_MINUTE_60);
		dwReste = (dwReste%FR_MINUTE_60);
		return (((hour << 24) & 0xff000000) + ((minute << 16) & 0xff0000) + (((dwReste / FR_SECOND_60) << 8) & 0xff00) + ((dwReste%FR_SECOND_60) & 0xff));
	}
	else
	{
		uint32_t uSecNum;
		hour = (dwFrameCount * dwScale / dwRate / 3600);
		dwReste = dwFrameCount - (hour * 3600 * dwRate / dwScale);
		minute = (dwReste * dwScale / dwRate / 60);
		dwReste -= (minute * 60 * dwRate / dwScale);
		uSecNum = dwReste * dwScale / dwRate;
		dwReste -= (uSecNum*dwRate / dwScale);
		return (((hour << 24) & 0xff000000) + ((minute << 16) & 0xff0000) + ((uSecNum << 8) & 0xff00) + (dwReste & 0xff));
	}
	return 0;
};

//依据视频制式转换帧数至32位整数, 32位整数的格式是0x(hh-mm-ss-ff)
inline uint32_t	FrameToIOPoint(uint32_t dwFrameCount, VIDEO_STANDARD enumVideoStandard)
{
	uint32_t dwRate, dwScale;
	GetStandardRateScale(enumVideoStandard, dwRate, dwScale);
	return FrameToIOPoint(dwFrameCount, dwRate, dwScale);
};

//依据帧率转换32位整数至帧数, 32位整数的格式是0x(hh-mm-ss-ff)
inline uint32_t	IOPointToFrame(uint32_t ioPoint, uint32_t dwRate, uint32_t dwScale)
{
	int	nhour = ((ioPoint >> 24) & 0xff);
	int	nminute = ((ioPoint >> 16) & 0xff);
	int	nsec = ((ioPoint >> 8) & 0xff);
	int	nframe = (ioPoint & 0xff);

	if (dwRate*c2398FRAMES_SCALE == dwScale*c2398FRAMES_FRAME_RATE)
	{
		return nhour*FR_HOUR_24 + nminute*FR_MINUTE_24 + nsec*FR_SECOND_24 + nframe;
	}
	else if (dwRate*c24FRAMES_SCALE == dwScale*c24FRAMES_FRAME_RATE)
	{
		return nhour*FR_HOUR_24 + nminute*FR_MINUTE_24 + nsec*FR_SECOND_24 + nframe;
	}
	else if (dwRate*c25FRAMES_SCALE == dwScale*c25FRAMES_FRAME_RATE)
	{
		return nhour*FR_HOUR_PAL + nminute*FR_MINUTE_PAL + nsec*FR_SECOND_PAL + nframe;
	}
	else if (dwRate*c2997FRAME_SCALE == dwScale*c2997FRAME_FRAME_RATE)
	{
		if ((nminute % 10) != 0)
		{
			if (nsec == 0 && (nframe == 0 || nframe == 1))
				nframe = 2;
		}
		return nhour*FR_HOUR_2997_DROP + (nminute / 10)*FR_TENMIN_2997_DROP + (nminute % 10)*FR_MINUTE_2997_DROP + nsec*FR_SECOND_2997 + nframe;
	}
	else if (dwRate*c30FRAMES_SCALE == dwScale*c30FRAMES_FRAME_RATE)
	{
		return nhour*FR_HOUR_2997_ND + nminute*FR_MINUTE_2997_ND + nsec*FR_SECOND_2997 + nframe;
	}
	else if (dwRate*c48FRAMES_SCALE == dwScale*c48FRAMES_FRAME_RATE)
	{
		return nhour*FR_HOUR_48 + nminute*FR_MINUTE_48 + nsec*FR_SECOND_48 + nframe;
	}
	else if (dwRate*c50FRAMES_SCALE == dwScale*c50FRAMES_FRAME_RATE)
	{
		return nhour*FR_HOUR_50 + nminute*FR_MINUTE_50 + nsec*FR_SECOND_50 + nframe;
	}
	else if (dwRate*c5994FRAMES_SCALE == dwScale*c5994FRAMES_FRAME_RATE)
	{
		if ((nminute % 10) != 0)
		{
			if (nsec == 0 && (nframe == 0 || nframe == 1))
				nframe = 2;
		}
		return nhour*FR_HOUR_5994_DROP + (nminute / 10)*FR_TENMIN_5994_DROP + (nminute % 10)*FR_MINUTE_5994_DROP + nsec*FR_SECOND_5994 + nframe;
	}
	else if (dwRate*c60FRAMES_SCALE == dwScale*c60FRAMES_FRAME_RATE)
	{
		return nhour*FR_HOUR_60 + nminute*FR_MINUTE_60 + nsec*FR_SECOND_60 + nframe;
	}
	else
	{
		return (nhour * 3600 * dwRate / dwScale) + (nminute * 60 * dwRate / dwScale) + (nsec*dwRate / dwScale) + nframe;
	}

	return 0;
};

//依据视频制式转换32位整数至帧数, 32位整数的格式是0x(hh-mm-ss-ff)
inline uint32_t	IOPointToFrame(uint32_t ioPoint, VIDEO_STANDARD enumVideoStandard)
{
	uint32_t	dwRate, dwScale;
	GetStandardRateScale(enumVideoStandard, dwRate, dwScale);
	return IOPointToFrame(ioPoint, dwRate, dwScale);
};

//依据帧率转换帧数至时分秒帧字符串
inline void	FramesToTimeCodeString(uint32_t dwFrameCount, std::string &strTimeCode, uint32_t dwRate, uint32_t dwScale)
{
	uint32_t dwReste, hour, minute;
	std::ostringstream ss;

	if (dwRate*c2398FRAMES_SCALE == dwScale*c2398FRAMES_FRAME_RATE)
	{
		hour = (dwFrameCount / FR_HOUR_24);
		dwReste = (dwFrameCount%FR_HOUR_24);
		minute = (dwReste / FR_MINUTE_24);
		dwReste = (dwReste%FR_MINUTE_24);
		//strTimeCode.Format(_T("%02d:%02d:%02d:%02d"), hour, minute, (dwReste / FR_SECOND_24), (dwReste % FR_SECOND_24));
		ss << hour << ":" << minute << ":" << (dwReste / FR_SECOND_24) << ":" << (dwReste % FR_SECOND_24);
	}
	else if (dwRate*c24FRAMES_SCALE == dwScale*c24FRAMES_FRAME_RATE)
	{
		hour = (dwFrameCount / FR_HOUR_24);
		dwReste = (dwFrameCount%FR_HOUR_24);
		minute = (dwReste / FR_MINUTE_24);
		dwReste = (dwReste%FR_MINUTE_24);
		//strTimeCode.Format(_T("%02d:%02d:%02d:%02d"), hour, minute, (dwReste / FR_SECOND_24), (dwReste % FR_SECOND_24));
		ss << hour << ":" << minute << ":" << (dwReste / FR_SECOND_24) << ":" << (dwReste % FR_SECOND_24);
	}
	else if (dwRate*c25FRAMES_SCALE == dwScale*c25FRAMES_FRAME_RATE)
	{
		hour = (dwFrameCount / FR_HOUR_PAL);
		dwReste = (dwFrameCount%FR_HOUR_PAL);
		minute = (dwReste / FR_MINUTE_PAL);
		dwReste = (dwReste%FR_MINUTE_PAL);
		//strTimeCode.Format(_T("%02d:%02d:%02d:%02d"), hour, minute, (dwReste / FR_SECOND_PAL), (dwReste % FR_SECOND_PAL));
		ss << hour << ":" << minute << ":" << (dwReste / FR_SECOND_PAL) << ":" << (dwReste % FR_SECOND_PAL);
	}
	else if (dwRate*c2997FRAME_SCALE == dwScale*c2997FRAME_FRAME_RATE)
	{
		hour = (dwFrameCount / FR_HOUR_2997_DROP);
		dwReste = (dwFrameCount%FR_HOUR_2997_DROP);
		minute = 10 * (dwReste / FR_TENMIN_2997_DROP);
		dwReste = (dwReste%FR_TENMIN_2997_DROP);
		if (dwReste >= FR_MINUTE_2997_ND)
		{
			dwReste -= FR_MINUTE_2997_ND;
			minute += 1 + (dwReste / FR_MINUTE_2997_DROP);
			dwReste %= FR_MINUTE_2997_DROP;
			dwReste += 2;
		}
		//strTimeCode.Format(_T("%02d:%02d:%02d;%02d"), hour, minute, (dwReste / FR_SECOND_2997), (dwReste % FR_SECOND_2997));
		ss << hour << ":" << minute << ":" << (dwReste / FR_SECOND_2997) << ":" << (dwReste % FR_SECOND_2997);
	}
	else if (dwRate*c30FRAMES_SCALE == dwScale*c30FRAMES_FRAME_RATE)
	{
		hour = (dwFrameCount / FR_HOUR_2997_ND);
		dwReste = (dwFrameCount%FR_HOUR_2997_ND);
		minute = (dwReste / FR_MINUTE_2997_ND);
		dwReste = (dwReste%FR_MINUTE_2997_ND);
		//strTimeCode.Format(_T("%02d:%02d:%02d:%02d"), hour, minute, (dwReste / FR_SECOND_2997), (dwReste % FR_SECOND_2997));
		ss << hour << ":" << minute << ":" << (dwReste / FR_SECOND_2997) << ":" << (dwReste % FR_SECOND_2997);
	}
	else if (dwRate*c48FRAMES_SCALE == dwScale*c48FRAMES_FRAME_RATE)
	{
		hour = (dwFrameCount / FR_HOUR_48);
		dwReste = (dwFrameCount%FR_HOUR_48);
		minute = (dwReste / FR_MINUTE_48);
		dwReste = (dwReste%FR_MINUTE_48);
		//strTimeCode.Format(_T("%02d:%02d:%02d:%02d"), hour, minute, (dwReste / FR_SECOND_48), (dwReste % FR_SECOND_48));
		ss << hour << ":" << minute << ":" << (dwReste / FR_SECOND_48) << ":" << (dwReste % FR_SECOND_48);
	}
	else if (dwRate*c50FRAMES_SCALE == dwScale*c50FRAMES_FRAME_RATE)
	{
		hour = (dwFrameCount / FR_HOUR_50);
		dwReste = (dwFrameCount%FR_HOUR_50);
		minute = (dwReste / FR_MINUTE_50);
		dwReste = (dwReste%FR_MINUTE_50);
		//strTimeCode.Format(_T("%02d:%02d:%02d:%02d"), hour, minute, (dwReste / FR_SECOND_50), (dwReste % FR_SECOND_50));
		ss << hour << ":" << minute << ":" << (dwReste / FR_SECOND_50) << ":" << (dwReste % FR_SECOND_50);
	}
	else if (dwRate*c5994FRAMES_SCALE == dwScale*c5994FRAMES_FRAME_RATE)
	{
		hour = (dwFrameCount / FR_HOUR_5994_DROP);
		dwReste = (dwFrameCount%FR_HOUR_5994_DROP);
		minute = 10 * (dwReste / FR_TENMIN_5994_DROP);
		dwReste = (dwReste%FR_TENMIN_5994_DROP);
		if (dwReste >= FR_MINUTE_5994_ND)
		{
			dwReste -= FR_MINUTE_5994_ND;
			minute += 1 + (dwReste / FR_MINUTE_5994_DROP);
			dwReste %= FR_MINUTE_5994_DROP;
			dwReste += 2;
		}
		//strTimeCode.Format(_T("%02d:%02d:%02d;%02d"), hour, minute, (dwReste / FR_SECOND_5994), (dwReste % FR_SECOND_5994));
		ss << hour << ":" << minute << ":" << (dwReste / FR_SECOND_5994) << ":" << (dwReste % FR_SECOND_5994);
	}
	else if (dwRate*c60FRAMES_SCALE == dwScale*c60FRAMES_FRAME_RATE)
	{
		hour = (dwFrameCount / FR_HOUR_60);
		dwReste = (dwFrameCount%FR_HOUR_60);
		minute = (dwReste / FR_MINUTE_60);
		dwReste = (dwReste%FR_MINUTE_60);
		//strTimeCode.Format(_T("%02d:%02d:%02d:%02d"), hour, minute, (dwReste / FR_SECOND_60), (dwReste % FR_SECOND_60));
		ss << hour << ":" << minute << ":" << (dwReste / FR_SECOND_60) << ":" << (dwReste % FR_SECOND_60);
	}
	else
	{
		uint32_t	uSecNum;
		hour = (dwFrameCount * dwScale / dwRate / 3600);
		dwReste = dwFrameCount - (hour * 3600 * dwRate / dwScale);
		minute = (dwReste * dwScale / dwRate / 60);
		dwReste -= (minute * 60 * dwRate / dwScale);
		uSecNum = dwReste * dwScale / dwRate;
		dwReste -= (uSecNum*dwRate / dwScale);
		//strTimeCode.Format(_T("%02d:%02d:%02d:%02d"), hour, minute, uSecNum, dwReste);
		ss << hour << ":" << minute << ":" << uSecNum << ":" << dwReste;
	}

	strTimeCode = ss.str();
};

//依据视频制式转换帧数至时分秒帧字符串
inline void	FramesToTimeCodeString(uint32_t dwFrameCount, std::string &strTimeCode, VIDEO_STANDARD enumVideoStandard)
{
	uint32_t dwRate, dwScale;
	GetStandardRateScale(enumVideoStandard, dwRate, dwScale);
	FramesToTimeCodeString(dwFrameCount, strTimeCode, dwRate, dwScale);
};

//依据视频制式转换帧数至时分秒帧字符串
inline std::string FramesToTimeCodeString(uint32_t dwFrameCount, VIDEO_STANDARD enumVideoStandard)
{
	std::string	strTimeCode;
	FramesToTimeCodeString(dwFrameCount, strTimeCode, enumVideoStandard);
	return strTimeCode;
};

//依据帧率转换帧数至时分秒帧字符串
inline std::string FramesToTimeCodeString(uint32_t dwFrameCount, uint32_t dwRate, uint32_t dwScale)
{
	std::string	strTimeCode;
	FramesToTimeCodeString(dwFrameCount, strTimeCode, dwRate, dwScale);
	return strTimeCode;
};

//依据帧率转换时分秒帧字符串至帧数
inline uint32_t TimeCodeStringToFrames(std::string& strTimeCode, uint32_t dwRate, uint32_t dwScale)
{
	if (strTimeCode.size() != 11)
		return 0;

	int	nhour = (strTimeCode[0] - '0') * 10 + (strTimeCode[1] - '0');
	int	nminute = (strTimeCode[3] - '0') * 10 + (strTimeCode[4] - '0');
	int	nsec = (strTimeCode[6] - '0') * 10 + (strTimeCode[7] - '0');
	int	nframe = (strTimeCode[9] - '0') * 10 + (strTimeCode[10] - '0');

	if (dwRate*c2398FRAMES_SCALE == dwScale*c2398FRAMES_FRAME_RATE)
	{
		return nhour*FR_HOUR_24 + nminute*FR_MINUTE_24 + nsec*FR_SECOND_24 + nframe;
	}
	else if (dwRate*c24FRAMES_SCALE == dwScale*c24FRAMES_FRAME_RATE)
	{
		return nhour*FR_HOUR_24 + nminute*FR_MINUTE_24 + nsec*FR_SECOND_24 + nframe;
	}
	else if (dwRate*c25FRAMES_SCALE == dwScale*c25FRAMES_FRAME_RATE)
	{
		return nhour*FR_HOUR_PAL + nminute*FR_MINUTE_PAL + nsec*FR_SECOND_PAL + nframe;
	}
	else if (dwRate*c2997FRAME_SCALE == dwScale*c2997FRAME_FRAME_RATE)
	{
		if ((nminute % 10) != 0)
		{
			if (nsec == 0 && (nframe == 0 || nframe == 1))
				nframe = 2;
		}
		return nhour*FR_HOUR_2997_DROP + (nminute / 10)*FR_TENMIN_2997_DROP + (nminute % 10)*FR_MINUTE_2997_DROP + nsec*FR_SECOND_2997 + nframe;
	}
	else if (dwRate*c30FRAMES_SCALE == dwScale*c30FRAMES_FRAME_RATE)
	{
		return nhour*FR_HOUR_2997_ND + nminute*FR_MINUTE_2997_ND + nsec*FR_SECOND_2997 + nframe;
	}
	else if (dwRate*c48FRAMES_SCALE == dwScale*c48FRAMES_FRAME_RATE)
	{
		return nhour*FR_HOUR_48 + nminute*FR_MINUTE_48 + nsec*FR_SECOND_48 + nframe;
	}
	else if (dwRate*c50FRAMES_SCALE == dwScale*c50FRAMES_FRAME_RATE)
	{
		return nhour*FR_HOUR_50 + nminute*FR_MINUTE_50 + nsec*FR_SECOND_50 + nframe;
	}
	else if (dwRate*c5994FRAMES_SCALE == dwScale*c5994FRAMES_FRAME_RATE)
	{
		if ((nminute % 10) != 0)
		{
			if (nsec == 0 && (nframe == 0 || nframe == 1))
				nframe = 2;
		}
		return nhour*FR_HOUR_5994_DROP + (nminute / 10)*FR_TENMIN_5994_DROP + (nminute % 10)*FR_MINUTE_5994_DROP + nsec*FR_SECOND_5994 + nframe;
	}
	else if (dwRate*c60FRAMES_SCALE == dwScale*c60FRAMES_FRAME_RATE)
	{
		return nhour*FR_HOUR_60 + nminute*FR_MINUTE_60 + nsec*FR_SECOND_60 + nframe;
	}
	else
	{
		return (nhour * 3600 * dwRate / dwScale) + (nminute * 60 * dwRate / dwScale) + (nsec*dwRate / dwScale) + nframe;
	}

	return 0;
};

//依据视频制式转换时分秒帧字符串至帧数
inline uint32_t TimeCodeStringToFrames(std::string& strTimeCode, VIDEO_STANDARD enumVideoStandard)
{
	uint32_t	dwRate, dwScale;
	GetStandardRateScale(enumVideoStandard, dwRate, dwScale);
	return TimeCodeStringToFrames(strTimeCode, dwRate, dwScale);
};

//依据视频制式转换浮点型秒数至时分秒帧字符串
inline std::string SecondToTimeCodeString(double dblSeconds, VIDEO_STANDARD enumVideoStandard)
{
	return FramesToTimeCodeString(_SecToFrame(dblSeconds, enumVideoStandard), enumVideoStandard);
};

//依据帧率转换浮点型秒数至时分秒帧字符串
inline std::string SecondToTimeCodeString(double dblSeconds, uint32_t dwRate, uint32_t dwScale)
{
	return FramesToTimeCodeString(_SecToFrame(dblSeconds, dwRate, dwScale), dwRate, dwScale);
};

//依据视频制式转换时分秒帧字符串至浮点型秒数
inline double TimeCodeStringToSecond(std::string& strTimeCode, VIDEO_STANDARD enumVideoStandard)
{
	return FrameToSec(TimeCodeStringToFrames(strTimeCode, enumVideoStandard), enumVideoStandard);
};

//依据帧率转换时分秒帧字符串至浮点型秒数
inline double TimeCodeStringToSecond(std::string& strTimeCode, uint32_t dwRate, uint32_t dwScale)
{
	return FrameToSec(TimeCodeStringToFrames(strTimeCode, dwRate, dwScale), dwRate, dwScale);
};

//转换浮点型秒数至时分秒毫秒字符串
inline std::string _SecondToTimeString(double dblSeconds, uint32_t dwMilliSecBitNum = 0)
{
	std::string	strTimeString = "";
	std::stringstream strstream;

	double	xx = dblSeconds;
	uint32_t	hh = (uint32_t)xx / 3600;
	xx -= (double)hh * 3600;
	uint32_t	mm = (uint32_t)xx / 60;
	xx -= (double)mm * 60;
	if (dwMilliSecBitNum == 0)
	{
		uint32_t ss = (uint32_t)(xx + 0.5);
		//strTimeString.Format(_T("%02d:%02d:%02d"), hh, mm, ss);
		strstream << hh << mm << ss;
	}
	else
	{
		uint32_t	ss = (uint32_t)xx;
		if (dwMilliSecBitNum == 1)
		{
			//strTimeString.Format(_T("%02d:%02d:%02d.%01d"), hh, mm, ss, (uint32_t)((xx - (double)ss)*10.0));
			strstream << hh << mm << ss << (uint32_t)((xx - (double)ss)*10.0);
		}
		else if (dwMilliSecBitNum == 2)
		{
			//strTimeString.Format(_T("%02d:%02d:%02d.%02d"), hh, mm, ss, (uint32_t)((xx - (double)ss)*100.0));
			strstream << hh << mm << ss << (uint32_t)((xx - (double)ss)*100.0);
		}	
		else
		{
			//strTimeString.Format(_T("%02d:%02d:%02d.%03d"), hh, mm, ss, (uint32_t)((xx - (double)ss)*1000.0));
			strstream << hh << mm << ss << (uint32_t)((xx - (double)ss)*1000.0);
		}		
	}
	return strTimeString;
};


//=======================================================================================
//与视音频压缩编码、文件(流)封装、节目复用等有关的枚举、结构及函数定义
//=======================================================================================
//	定义枚举:
//		VIDEO_TYPE;					// 视频编码格式类型
//		AUDIO_TYPE;					// 音频编码格式类型
//		COLOR_FORMAT					// 视频颜色格式类型
//		STREAM_TYPE					// 视音频流格式类型
//		VIDEOSCAN_MODE				// 视频扫描帧场数据排列方式
//		VIDEO_ASPECTRATIO			// 视频幅宽比类型
//		COLOR_PRIMARIES				// 源基色的色度坐标(ISO13818-2)
//		COLOR_TRANSFER				// 光电转换特性(ISO13818-2)
//		COLOR_MATRIX					// 颜色空间变换系数(ISO13818-2)
//		ACTIVE_FORMAT_DESCRIPTION	// 图像有效区域信息描述，按SMPTE 2016-1定义
//		DATARATE_TYPE				// MPEG视频编解码格式码率类型
//		AUDIO_CHANNELCONFIGURATION	// 声道属性枚举定义
//		CHANNELSAMPLE_FORMAT			// 音频声道采样数据格式
//		STREAMMEDIA_TYPE				// 流媒体数据信息类型
//		MEDIADATASTREAM_TYPE			// 媒体数据流数据类型
//		STREAMCOMPRESSDATA_ACTMODE	// 流压缩数据获取/推送操作模式
//	定义结构:
//		SVideoMediaInfo											//视频基本属性
//		SVideoFrameImageBufInfo									//视频帧图像数据块属性
//		SAudioMediaInfo, ASAudioMediaInfoArray					//音频基本属性
//		SAudioSamplesBufInfo									//音频采样数据块属性
//		SStreamMediaInfo, ASStreamMediaInfoArray				//视音频流(文件)属性
//		SStreamMediaInfoEx, ASStreamMediaInfoExArray			//视音频流(文件)扩展属性
//		SSingleProgramStreamMediaInfo, 							//单节目视音频流(文件)属性
//		SSingleProgramStreamMediaInfoEx,						//单节目视音频流(文件)扩展属性
//		SMultiProgramStreamMediaInfo							//多节目视音频流(文件)属性
//		SMultiProgramStreamMediaInfoEx							//多节目视音频流(文件)扩展属性
//		SGlobalStreamMediaInfo									//全局流媒体数据信息
//		SGlobalStreamMediaInfoEx								//全局流媒体数据扩展信息
//		SStreamCompressDataInfo									//流压缩数据信息
//	定义函数:
//		std::string GetVideoTypeHint( VIDEO_TYPE enumVideoType );	//得到视频编码格式类型的名称
//		std::string GetAudioTypeHint( AUDIO_TYPE enumAudioType );	//得到音频编码格式类型的名称
//		std::string GetColorFormatHint(COLOR_FORMAT enumColorFormat);	//得到视频颜色格式类型的名称
//		uint32_t GetColorFormatBufSizeInByte( COLOR_FORMAT enumColorFormat, uint32_t dwPixelNum );	//依据视频颜色格式和像素点数目得到视频数据块的大小
//		std::string GetStreamTypeHint( STREAM_TYPE enumStreamType );	//得到视音频流格式类型的名称
//		std::string GetVideoScanModeHint( VIDEOSCAN_MODE enumScanMode );	//得到视频扫描帧场数据排列方式的名称
//		std::string GetVideoAspectRatioHint( VIDEO_ASPECTRATIO enumAspectRatio );	//得到视频幅宽比类型的名称
//		std::string GetColorPrimariesHint( COLOR_PRIMARIES emColorPrimaries );	//得到源基色的色度坐标类型的名称
//		std::string GetColorTransferHint( COLOR_TRANSFER emColorTransfer );	//得到光电转换特性类型的名称
//		std::string GetColorMatrixHint( COLOR_MATRIX emColorMatrix );	//得到颜色空间变换系数类型的名称
//		std::string GetActiveFormatDescriptionHint( ACTIVE_FORMAT_DESCRIPTION enumAFD, bool bIs16_9 );	//得到图像有效区域信息描述类型的名称
//		std::string GetDataRateTypeHint( DATARATE_TYPE enumDataRateType );	//得到MPEG视频编解码格式码率类型的名称
//		std::string GeAudioCFGHint( AUDIO_CHANNELCONFIGURATION enumAudioCFG )	////得到声道属性枚举定义的名称
//=======================================================================================
enum  VIDEO_TYPE		// 视频编码格式类型
{
	VIDEOTYPE_UNKNOW			   = 0x00000000,	// 无效类型

	VIDEOTYPE_MJPEG_FIELD		   = 0x00000001,	// MJPEG 场压缩方式
	VIDEOTYPE_MJPEG_FRAME		   = 0x00000002,	// MJPEG 帧压缩方式
	VIDEOTYPE_MJPEG_LOSSLESS_FIELD = 0x00000400,	// MJPEG 无损场压缩方式
	VIDEOTYPE_MJPEG_LOSSLESS_FRAME = 0x00000800,	// MJPEG 无损帧压缩方式

	VIDEOTYPE_MPEG1				   = 0x00000100,	// MPEG1 编码
	VIDEOTYPE_MPEG2_IFRAME		   = 0x00000004,	// MPEG2 I帧压缩方式
	VIDEOTYPE_MPEG2_IBP			   = 0x00000008,	// MPEG2 IBP帧压缩方式。
	VIDEOTYPE_MPEG2_D10			   = 0x00000010,	// Mpeg2 D10 编码格式, Special Mpeg2 I
	VIDEOTYPE_MPEG2_HDV			   = 0x02000000,	// Mpeg2 HDV 编码格式, Special Mpeg2 IBP
	VIDEOTYPE_MPEG4				   = 0x00000200,	// MPEG4 编码

	VIDEOTYPE_DV25				   = 0x00000020,	// DV25编码格式 
	VIDEOTYPE_DV50				   = 0x00000040,	// DV50编码格式
	VIDEOTYPE_DVSD				   = 0x00000080,	// DVSD编码格式
	VIDEOTYPE_DVHD				   = 0x00040000,	// DVC PRO HD 100M 压缩方式

	VIDEOTYPE_YUV_UNCOMPRESS	   = 0x00001000,	// YUV or TYUV 非压缩方式
	VIDEOTYPE_RGB_UNCOMPRESS	   = 0x00002000,	// RGB or ARGB 非压缩方式
	VIDEOTYPE_ZAXEL_LOSSLESS	   = 0x00100000,	// Zaxtar 无损编码压缩方式

	VIDEOTYPE_REAL_MEDIA		   = 0x00004000,	// real media(rm)格式
	VIDEOTYPE_WINDOWS_MEDIA		   = 0x00008000,	// window media(wm)格式
	VIDEOTYPE_QUICKTIME_MOV		   = 0x00010000,	// quicktime 格式
	VIDEOTYPE_VCM_COMPRESSED	   = 0x00020000,	// video compression manager (VCM)压缩格式。

	VIDEOTYPE_AVS				   = 0x00200000,	// AVS压缩格式
	VIDEOTYPE_H263			       = 0x00400000,	// H263压缩格式
	VIDEOTYPE_H264				   = 0x00800000,	// H264压缩格式
	VIDEOTYPE_H265				   = 0x00801000,	// H265压缩格式
	VIDEOTYPE_AVCINTRA_HD		   = 0x04000000,	// P2 AVC Intra的压缩格式
	VIDEOTYPE_AVID_DNXHD		   = 0x08000000,	// AVID DNXHD的压缩格式
	VIDEOTYPE_MJ2K			       = 0x01000000,	// MJPEG2000压缩格式
	VIDEOTYPE_PRORES422			   = 0x10000000,	// Apple ProRes 422 压缩方式

	VIDEOTYPE_SWFFLV_TYPE		   = 0x00080000,	// FLV 文件格式能包括的压缩格式
	VIDEOTYPE_DPX				   = 0x00080001,	// DPX 文件的视频格式
	VIDEOTYPE_REDCODE			   = 0x00080002,	// Red one的REDCODE格式
};
enum CODEC_PROFILE
{
	PROFILE_UNKNOW		 = 0x00000000,	// 无效类型
	PROFILE_AVC_BASELINE = 0x00000042,
	PROFILE_AVC_MAIN	 = 0x0000004d,
	PROFILE_AVC_HIGH	 = 0x00000064
};
//得到视频编码格式类型的名称
inline std::string GetVideoTypeHint(VIDEO_TYPE enumVideoType)
{
	std::string strHint = "Unknow";
	switch (enumVideoType)
	{
	case VIDEOTYPE_MJPEG_FIELD:
		strHint = "MJPEG_Field";
		break;
	case VIDEOTYPE_MJPEG_FRAME:
		strHint = "MJPEG_Frame";
		break;
	case VIDEOTYPE_MJPEG_LOSSLESS_FIELD:
		strHint = "MJPEG_LossLess_Field";
		break;
	case VIDEOTYPE_MJPEG_LOSSLESS_FRAME:
		strHint = "MJPEG_LossLess_Frame";
		break;
	case VIDEOTYPE_MPEG1:
		strHint = "MPEG1";
		break;
	case VIDEOTYPE_MPEG2_IFRAME:
		strHint = "MPEG2_I";
		break;
	case VIDEOTYPE_MPEG2_IBP:
		strHint = "MPEG2_IBP";
		break;
	case VIDEOTYPE_MPEG2_D10:
		strHint = "MPEG2_D10";
		break;
	case VIDEOTYPE_MPEG2_HDV:
		strHint = "MPEG2_HDV";
		break;
	case VIDEOTYPE_MPEG4:
		strHint = "MPEG4";
		break;
	case VIDEOTYPE_DV25:
		strHint = "DV25";
		break;
	case VIDEOTYPE_DV50:
		strHint = "DV50";
		break;
	case VIDEOTYPE_DVSD:
		strHint = "DVSD";
		break;
	case VIDEOTYPE_DVHD:
		strHint = "DVHD";
		break;
	case VIDEOTYPE_YUV_UNCOMPRESS:
		strHint = "YUV_UnCompress";
		break;
	case VIDEOTYPE_RGB_UNCOMPRESS:
		strHint = "RGB_UnCompress";
		break;
	case VIDEOTYPE_ZAXEL_LOSSLESS:
		strHint = "ZAXEL_LossLess";
		break;
	case VIDEOTYPE_REAL_MEDIA:
		strHint = "Real_Media";
		break;
	case VIDEOTYPE_WINDOWS_MEDIA:
		strHint = "Windows_Media";
		break;
	case VIDEOTYPE_QUICKTIME_MOV:
		strHint = "QuickTime_Mov";
		break;
	case VIDEOTYPE_VCM_COMPRESSED:
		strHint = "VCM_Compressed";
		break;
	case VIDEOTYPE_AVS:
		strHint = "AVS";
		break;
	case VIDEOTYPE_H263:
		strHint = "H263";
		break;
	case VIDEOTYPE_H264:
		strHint = "H264";
		break;
	case VIDEOTYPE_MJ2K:
		strHint = "MJ2K";
		break;
	case VIDEOTYPE_AVCINTRA_HD:
		strHint = "AVC_Intra_HD";
		break;
	case VIDEOTYPE_AVID_DNXHD:
		strHint = "Avid_DNxHD";
		break;
	case VIDEOTYPE_PRORES422:
		strHint = "ProRes422";
		break;
	case VIDEOTYPE_SWFFLV_TYPE:
		strHint = "FLV-Video";
		break;
	case VIDEOTYPE_REDCODE:
		strHint = "RedCode";
		break;
	case VIDEOTYPE_DPX:
		strHint = "DPX";
		break;
	}
	return strHint;
};

enum  AUDIO_TYPE	// 音频编解码格式类型
{
	AUDIOTYPE_UNKNOW	= 0x00000000,       // @emem  unknow type.

	AUDIOTYPE_WAVE_PCM	= 0x00000001,		// WAVE PCM 音频压缩方式

	AUDIOTYPE_MP1		= 0x00000004,		// MPEG1 音频 (Layer 1) 压缩方式
	AUDIOTYPE_MP2		= 0x00000008,		// MPEG1 音频 (Layer 2) 压缩方式
	AUDIOTYPE_MP3		= 0x00000010,		// MPEG1 音频 (Layer 3) 压缩方式	
	AUDIOTYPE_MPEG4		= 0x00000002,		// MPEG4 (ACM) 音频压缩WAVE

	AUDIOTYPE_AAC		= 0x00000020,		// AAC 压缩方式。
	AUDIOTYPE_AC3		= 0x00000040,		// Dolby Digital (AC3) 音频压缩方式
	AUDIOTYPE_DTS		= 0x00000080,		// DTS 音频压缩方式
	AUDIOTYPE_DRA		= 0x00080000,		// DRA Audio
	AUDIOTYPE_AVS		= 0x00000800,		// AVS音频压缩方式
	AUDIOTYPE_DolbyE	= 0x00001000,		// Dolby-E 音频压缩方式
	AUDIOTYPE_EAC3		= 0x00002000,		// Dolby Digital Plus (EAC3) 音频压缩方式

	AUDIOTYPE_REAL_MEDIA	= 0x00000100,	// Real media 音频压缩方式
	AUDIOTYPE_WINDOWS_MEDIA = 0x00000200,	// Windows media 音频压缩方式
	AUDIOTYPE_QUICKTIME_MOV = 0x00000400,	// Quicktime 音频压缩方式

	AUDIOTYPE_G711		= 0x00004000,		// ITUT的语音压缩标准,分ALaw和ULaw两种模式
	AUDIOTYPE_AMRNB		= 0x00010000,		// AMR-NB for 3GPP or GSM
	AUDIOTYPE_AMRWB		= 0x00020000,		// AMR-NB for 3GPP only
	AUDIOTYPE_SWFFLV	= 0x00040000,		// Flv Audio
};

//得到音频编码格式类型的名称
inline std::string GetAudioTypeHint(AUDIO_TYPE enumAudioType)
{
	std::string strHint = "Unknow";
	switch (enumAudioType)
	{
	case AUDIOTYPE_WAVE_PCM:
		strHint = "PCM";
		break;
	case AUDIOTYPE_MP1:
		strHint = "MP1";
		break;
	case AUDIOTYPE_MP2:
		strHint = "MP2";
		break;
	case AUDIOTYPE_MP3:
		strHint = "MP3";
		break;
	case AUDIOTYPE_MPEG4:
		strHint = "MPEG4";
		break;
	case AUDIOTYPE_AAC:
		strHint = "AAC";
		break;
	case AUDIOTYPE_AC3:
		strHint = "AC3";
		break;
	case AUDIOTYPE_EAC3:
		strHint = "EAC3";
		break;
	case AUDIOTYPE_DTS:
		strHint = "DTS";
		break;
	case AUDIOTYPE_DRA:
		strHint = "DRA";
		break;
	case AUDIOTYPE_AVS:
		strHint = "AVS";
		break;
	case AUDIOTYPE_DolbyE:
		strHint = "Dolby-E";
		break;
	case AUDIOTYPE_REAL_MEDIA:
		strHint = "Real_Media";
		break;
	case AUDIOTYPE_WINDOWS_MEDIA:
		strHint = "Windows_Media";
		break;
	case AUDIOTYPE_QUICKTIME_MOV:
		strHint = "QuickTime_Mov";
		break;
	case AUDIOTYPE_G711:
		strHint = "G711";
		break;
	case AUDIOTYPE_AMRNB:
		strHint = "AMR-NB";
		break;
	case AUDIOTYPE_AMRWB:
		strHint = "AMR-WB";
		break;
	case AUDIOTYPE_SWFFLV:
		strHint = "FLV-Audio";
		break;
	}
	return strHint;
};

enum  COLOR_FORMAT		// 视频颜色格式
{
	COLORFORMAT_UNKNOW		= 0x00000000,		// invalid color format.

	COLORFORMAT_BGRA		= 0x00000001,		//BGRA4444,	8bit,	0xAARRGGBB...4个字节排列1个α通道分量A、1个R分量、1个G分量、1个B分量
	COLORFORMAT_BGRA_10b	= 0x00002000,		//BGRA4444,	10bit,	3×1个图像像素, 详细定义见专门文档!
	COLORFORMAT_BGRA_16b	= 0x00008000,		//BGRA4444,	16bit,	0xAAAARRRRGGGGBBBB...8个字节排列1个α通道分量A、1个R分量、1个G分量、1个B分量
	COLORFORMAT_BGR			= 0x00000004,		//BGR444,	8bit,	0xRRGGBB...3个字节排列1个R分量、1个G分量、1个B分量
	COLORFORMAT_BGR_10b		= 0x00004000,		//BGR444,	10bit,	4×1个图像像素, 详细定义见专门文档!
	COLORFORMAT_BGR_16b		= 0x00200000,		//BGR444,	16bit,	0xRRRRGGGGBBBB...6个字节排列1个R分量、1个G分量、1个B分量

	COLORFORMAT_VUYT		= 0x00000020,		//VUYT4444,	8bit,	0xTTYYUUVV...4个字节排列1个T分量、1个Y分量、1个U分量和1个V分量
	COLORFORMAT_VUYT_10b	= 0x00400000,		//VUYT4444,	10bit,	3×1个图像像素, 详细定义见专门文档!
	COLORFORMAT_VUYT_16b	= 0x04000000,		//VUYT4444,	16bit,	0xTTTTYYYYUUUUVVVV...8个字节排列1个T分量、1个Y分量、1个U分量和1个V分量
	COLORFORMAT_VUY			= 0x02000000,		//VUY444,	8bit,	0xYYUUVV...3个字节排列1个Y分量、1个U分量和1个V分量
	COLORFORMAT_VUY_10b		= 0x08000000,		//VUY444,	10bit,	4×1个图像像素, 详细定义见专门文档!
	COLORFORMAT_VUY_16b		= 0x10000000,		//VUY444,	16bit,	0xYYYYUUUUVVVV...6个字节排列1个Y分量、1个U分量和1个V分量

	COLORFORMAT_YUYV		= 0x00000040,		//YUYV422,	8bit,	0xVVYYUUYY...4个字节排列排列2个图像像素的Y、U、V分量
	COLORFORMAT_UYVY		= 0x00000080,		//UYVY422,	8bit,	0xYYVVYYUU...4个字节排列排列2个图像像素的Y、U、V分量
	COLORFORMAT_YUYV_V210	= 0x00040000,		//YUYV422,	10bit,	Apple定义的采样格式, 详细定义见专门文档!
	COLORFORMAT_YUYV_V216	= 0x00020000,		//YUYV422,	16bit,	Apple定义的采样格式, 详细定义见专门文档!
	COLORFORMAT_YUYV_M101	= 0x00080000,		//YUYV422,	8bit,	Matrox定义的采样格式, 详细定义见专门文档!
	COLORFORMAT_YUYV_M101_10BIT  = 0x00100000,	//YUYV422,	10bit,	Matrox定义的采样格式, 详细定义见专门文档!
	COLORFORMAT_YUAYVA4224		 = 0x00800000,	//YUAYVA4224,8bit,	Matrox定义的8bit带阿尔法通道的颜色格式, 以YUYV为基础，每8个像素为一个单元，详细定义见专门文档!
	COLORFORMAT_YUYV_DNXHD_10BIT = 0x00001000,	//YUYV422,	10bit,	AVID定义的采样格式, 详细定义见专门文档!

	COLORFORMAT_YUVP_444	= 0x00000100,		//YUVP444,	8bit,	1个图像像素占3个字节,Y、U、V分量分别保存在三块缓存区中, 详细定义见专门文档!
	COLORFORMAT_YUVP_422	= 0x00000200,		//YUVP422,	8bit,	2x1宏像素占4个字节,Y、U、V分量分别保存在三块缓存区中, 详细定义见专门文档!
	COLORFORMAT_YUVP_420	= 0x00000400,		//YUVP420,	8bit,	2x2宏像素占6个字节,Y、U、V分量分别保存在三块缓存区中, 详细定义见专门文档!
	COLORFORMAT_YUVP_NV12	= 0x00000500,
	COLORFORMAT_YUVP_411	= 0x00000800,		//YUVP411,	8bit,	4x1宏像素占6个字节,Y、U、V分量分别保存在三块缓存区中, 详细定义见专门文档!
};

inline double PixelRatioEx(COLOR_FORMAT &crFormat)
{
	switch (crFormat)
	{
	case	COLORFORMAT_UNKNOW:return 4;
	case	COLORFORMAT_BGRA:return 4;
	case	COLORFORMAT_VUYT:return 4;
	case	COLORFORMAT_YUYV:return 2;
	case	COLORFORMAT_UYVY:return 2;
	case	COLORFORMAT_YUVP_422:return 2;
	case	COLORFORMAT_YUVP_444:return 3;
	case	COLORFORMAT_YUVP_420:return 1.5;
	case	COLORFORMAT_YUVP_NV12:return 1.5;	
	};
	return 4;
}

//得到视频颜色格式类型的名称
inline std::string GetColorFormatHint(COLOR_FORMAT enumColorFormat)
{
	std::string strColorFormat = "Unknow";

	switch (enumColorFormat)
	{
	case COLORFORMAT_BGRA:
		strColorFormat = "BGRA";
		break;
	case COLORFORMAT_BGRA_10b:
		strColorFormat = "BGRA_10b";
		break;
	case COLORFORMAT_BGRA_16b:
		strColorFormat = "BGRA_16b";
		break;
	case COLORFORMAT_BGR:
		strColorFormat = "BGR";
		break;
	case COLORFORMAT_BGR_10b:
		strColorFormat = "BGR_10b";
		break;
	case COLORFORMAT_BGR_16b:
		strColorFormat = "BGR_16b";
		break;
	case COLORFORMAT_VUYT:
		strColorFormat = "VUYT";
		break;
	case COLORFORMAT_VUYT_10b:
		strColorFormat = "VUYT_10b";
		break;
	case COLORFORMAT_VUYT_16b:
		strColorFormat = "VUYT_16b";
		break;
	case COLORFORMAT_VUY:
		strColorFormat = "VUY";
		break;
	case COLORFORMAT_VUY_10b:
		strColorFormat = "VUY_10b";
		break;
	case COLORFORMAT_VUY_16b:
		strColorFormat = "VUY_16b";
		break;
	case COLORFORMAT_YUYV:
		strColorFormat = "YUYV";
		break;
	case COLORFORMAT_UYVY:
		strColorFormat = "UYVY";
		break;
	case COLORFORMAT_YUYV_V210:
		strColorFormat = "YUYV_V210";
		break;
	case COLORFORMAT_YUYV_V216:
		strColorFormat = "YUYV_V216";
		break;
	case COLORFORMAT_YUYV_M101:
		strColorFormat = "YUYV_M101";
		break;
	case COLORFORMAT_YUYV_M101_10BIT:
		strColorFormat = "YUYV_M101_10BIT";
		break;
	case COLORFORMAT_YUAYVA4224:
		strColorFormat = "YUAYVA4224";
		break;
	case COLORFORMAT_YUYV_DNXHD_10BIT:
		strColorFormat = "YUYV_DNXHD_10BIT";
		break;
	case COLORFORMAT_YUVP_444:
		strColorFormat = "YUVP_444";
		break;
	case COLORFORMAT_YUVP_422:
		strColorFormat = "YUVP_422";
		break;
	case COLORFORMAT_YUVP_420:
		strColorFormat = "YUVP_420";
		break;
	case COLORFORMAT_YUVP_411:
		strColorFormat = "YUVP_411";
		break;
	}
	return strColorFormat;
};
enum TARGET_USAGES
{
	TARGETUSAGE_BEST_QUALITY = 0x00000001,
	TARGETUSAGE_BALANCED = 0x00000004,
	TARGETUSAGE_BEST_SPEED = 0x00000007
};
//依据视频颜色格式和像素点数目得到视频数据块的大小
inline uint32_t GetColorFormatBufSizeInByte(COLOR_FORMAT enumColorFormat, uint32_t dwWidth, uint32_t dwHeight, uint32_t *pdwXScanByteSize = NULL)
{
	if (pdwXScanByteSize && (*pdwXScanByteSize) != 0)
		return (*pdwXScanByteSize)*dwHeight;

	uint32_t dwBufByteSize = 0;
	uint32_t dwXScanByteSize = 0;

	switch (enumColorFormat)
	{
	case COLORFORMAT_BGRA:
	case COLORFORMAT_VUYT:
		dwXScanByteSize = 4 * dwWidth;
		dwBufByteSize = dwXScanByteSize*dwHeight;
		break;
	case COLORFORMAT_BGR:
	case COLORFORMAT_VUY:
		dwXScanByteSize = 3 * dwWidth;
		dwBufByteSize = dwXScanByteSize*dwHeight;
		break;
	case COLORFORMAT_BGRA_10b:
	case COLORFORMAT_VUYT_10b:
		if ((dwWidth % 3) != 0)				// 其宏像素由3×1个图像像素组成，在缓存中占4个32位little-endian字节序双字（DWord）
			dwWidth = (dwWidth / 3 + 1) * 3;
		if (((dwWidth * 16 / 3) % 128) != 0)
			dwXScanByteSize = ((dwWidth * 16 / 3) / 128 + 1) * 128;
		else
			dwXScanByteSize = dwWidth * 16 / 3;
		dwBufByteSize = dwXScanByteSize*dwHeight;
		break;
	case COLORFORMAT_BGR_10b:
	case COLORFORMAT_VUY_10b:
		if ((dwWidth % 4) != 0)				// 其宏像素由4×1个图像像素组成，在缓存中占4个32位little-endian字节序双字（DWord）
			dwWidth = (dwWidth / 4 + 1) * 3;
		if (((dwWidth * 16 / 4) % 128) != 0)
			dwXScanByteSize = ((dwWidth * 16 / 4) / 128 + 1) * 128;
		else
			dwXScanByteSize = dwWidth * 16 / 4;
		dwBufByteSize = dwXScanByteSize*dwHeight;
		break;
	case COLORFORMAT_BGRA_16b:
	case COLORFORMAT_VUYT_16b:
		dwXScanByteSize = dwWidth * 8;		// 1个像素占8字节
		dwBufByteSize = dwXScanByteSize*dwHeight;
		break;
	case COLORFORMAT_BGR_16b:
	case COLORFORMAT_VUY_16b:
		dwXScanByteSize = dwWidth * 6;		// 1个像素占6字节
		dwBufByteSize = dwXScanByteSize*dwHeight;
		break;

	case COLORFORMAT_YUYV:
	case COLORFORMAT_UYVY:
		dwXScanByteSize = 2 * dwWidth;
		dwBufByteSize = dwXScanByteSize*dwHeight;
		break;
	case COLORFORMAT_YUYV_V210:			// V210最小单位为6像素16字节, 跨距为128字节的整数倍(48像素)
		if ((dwWidth % 6) != 0)				// 其宏像素由6×1个图像像素组成，在缓存中占4个32位little-endian字节序双字（DWord）
			dwWidth = (dwWidth / 6 + 1) * 6;
		if (((dwWidth * 16 / 6) % 128) != 0)
			dwXScanByteSize = ((dwWidth * 16 / 6) / 128 + 1) * 128;
		else
			dwXScanByteSize = dwWidth * 16 / 6;
		dwBufByteSize = dwXScanByteSize*dwHeight;
		break;
	case COLORFORMAT_YUYV_V216:
		dwXScanByteSize = dwWidth * 4;		// 2个像素占8字节
		dwBufByteSize = dwXScanByteSize*dwHeight;
		break;
	case COLORFORMAT_YUYV_M101:			//最小单位为16像素32字节, 跨距为128字节的整数倍(48像素)
		if ((dwWidth % 16) != 0)
			dwWidth = (dwWidth / 16 + 1) * 16;
		if (((dwWidth * 2) % 128) != 0)
			dwXScanByteSize = ((dwWidth * 2 / 128) + 1) * 128;
		else
			dwXScanByteSize = dwWidth * 2;
		dwBufByteSize = dwXScanByteSize*dwHeight;
		break;
	case COLORFORMAT_YUYV_M101_10BIT:		//最小单位为16像素40字节, 跨距为128字节的整数倍(48像素)
		if ((dwWidth % 16) != 0)
			dwWidth = (dwWidth / 16 + 1) * 16;
		if (((dwWidth * 40 / 16) % 128) != 0)
			dwXScanByteSize = ((dwWidth * 40 / 16 / 128) + 1) * 128;
		else
			dwXScanByteSize = dwWidth * 40 / 16;
		dwBufByteSize = dwXScanByteSize*dwHeight;
		break;
	case COLORFORMAT_YUAYVA4224:			//最小单位为8像素,Picth为32字节对齐。在720时为2176字节，1920时为5760字节
		dwXScanByteSize = 3 * dwWidth;		//每像素为3字节
		if ((dwXScanByteSize % 32) != 0)
			dwXScanByteSize = (dwXScanByteSize / 32 + 1) * 32;
		dwBufByteSize = dwXScanByteSize*dwHeight;
		break;
	case COLORFORMAT_YUYV_DNXHD_10BIT:	//缓存排列2部分，前一部分和COLORFORMAT_YUYV完全相同，后一部分是每个分量的低2位依次排列
		dwXScanByteSize = 20 * dwWidth / 8;
		dwBufByteSize = dwXScanByteSize*dwHeight;
		break;

	case COLORFORMAT_YUVP_444:
		dwXScanByteSize = 0;
		dwBufByteSize = 3 * dwWidth*dwHeight;
		break;
	case COLORFORMAT_YUVP_422:
		dwXScanByteSize = 0;
		dwBufByteSize = 2 * dwWidth*dwHeight;
		break;
	case COLORFORMAT_YUVP_420:
	case COLORFORMAT_YUVP_411:
		dwXScanByteSize = 0;
		dwBufByteSize = 3 * dwWidth*dwHeight / 2;
		break;
	}
	if (pdwXScanByteSize)
		(*pdwXScanByteSize) = dwXScanByteSize;
	return dwBufByteSize;
};

enum STREAM_TYPE  // 视音频流格式类型
{
	STREAMTYPE_UNKNOWN = 0x00000000,	//无效格式

	STREAMTYPE_OPENDML_AVI = 0x00000001,	// OPENDML Video 文件
	STREAMTYPE_MSVFW_AVI = 0x00000002,	// MSVFW Video 文件
	STREAMTYPE_MSVFW_WAV = 0x00000004,	// MSVFW Audio 文件

	STREAMTYPE_ES = 0x00000010,	// Element Stream file
	STREAMTYPE_PS = 0x00000020,	// Program Stream file
	STREAMTYPE_VCD = 0x00100000,	// VCD MPG file, --- Special PS	
	STREAMTYPE_DVD = 0x00400000,	// DVD MPG file, --- Special PS
	STREAMTYPE_TS = 0x00000040,	// Transport Stream file
	STREAMTYPE_HDV = 0x00000200,	// HDV file, --- Special TS
	STREAMTYPE_SUBTITLE = 0x00800000,	// TS SubTitle文件

	STREAMTYPE_MXF = 0x00010000,   // MXF File
	STREAMTYPE_3GPP = 0x00000400,   // 3GPP file
	STREAMTYPE_FLV = 0x00000800,	// FLV file
	STREAMTYPE_ISOMP4 = 0x00000080,	// ISO MP4 Stream file

	STREAMTYPE_REAL_MEDIA = 0x01000000,	// REAL MEDIA 文件
	STREAMTYPE_WINDOWS_MEDIA = 0x02000000,	// WINDOWS MEDIA PLAY 文件
	STREAMTYPE_QUICKTIME_MOV = 0x04000000,	// QUICKTIME 文件
	STREAMTYPE_ZAXEL = 0x08000000,	// Zaxel文件
	STREAMTYPE_AIFF = 0x00200000,	// AIFF文件
	STREAMTYPE_MKV = 0x00000008,	// MKV文件

	STREAMTYPE_GXF = 0x00020000,   // GXF File
	STREAMTYPE_OMNEON = 0x00080000,   // OMNEON Video Server File
	STREAMTYPE_LXF = 0x00000100,   // LEITCH Video Server File			.........	/**/
	STREAMTYPE_SAF = 0x00040000,   // SEACHANGE Video Server File		.........	/**/
	STREAMTYPE_MAV70 = 0x00001000,   // SONY MAV70 Video Server File		.........	/**/
	STREAMTYPE_VSR2000 = 0x00002000,   // SONY VSR2000 Video Server File	.........	/**/
	STREAMTYPE_MSS = 0x00004000,   // PINNACLE MediaStream Server File	.........	/**/

	STREAMTYPE_P2CLIP = 0x00008000,   // P2 Card Clip
	STREAMTYPE_DPX = 0x00008001,   // DPX File
	STREAMTYPE_R3D = 0x00008002,   // RED ONE R3D file
	STREAMTYPE_E2CLIP = 0x00008003,   // E2 Card Clip 
	STREAMTYPE_HLS = 0x00008004,   // HTTP Live Streaming 
	STREAMTYPE_RTP = 0x00008005,   // Real-time Transport Protocol  	

	STREAMTYPE_DEF10000000 = 0x10000000,	// 大洋扩展定义---0x10000000
	STREAMTYPE_DEF20000000 = 0x20000000,	// 大洋扩展定义---0x20000000
	STREAMTYPE_DEF40000000 = 0x40000000,	// 大洋扩展定义---0x40000000
	STREAMTYPE_DEF80000000 = 0x80000000,	// 大洋扩展定义---0x80000000
};

//得到视音频流格式类型的名称
inline std::string GetStreamTypeHint(STREAM_TYPE enumStreamType)
{
	std::string strStreamType = "Unknow";

	switch (enumStreamType)
	{
	case STREAMTYPE_OPENDML_AVI:
		strStreamType = "ODML_AVI";
		break;
	case STREAMTYPE_MSVFW_AVI:
		strStreamType = "MSVFW_AVI";
		break;
	case STREAMTYPE_MSVFW_WAV:
		strStreamType = "MSVFW_WAV";
		break;
	case STREAMTYPE_ES:
		strStreamType = "ES";
		break;
	case STREAMTYPE_PS:
		strStreamType = "PS";
		break;
	case STREAMTYPE_VCD:
		strStreamType = "VCD";
		break;
	case STREAMTYPE_DVD:
		strStreamType = "DVD";
		break;
	case STREAMTYPE_TS:
		strStreamType = "TS";
		break;
	case STREAMTYPE_HDV:
		strStreamType = "HDV";
		break;
	case STREAMTYPE_SUBTITLE:
		strStreamType = "SubTitle";
		break;
	case STREAMTYPE_MXF:
		strStreamType = "MXF";
		break;
	case STREAMTYPE_3GPP:
		strStreamType = "3GPP";
		break;
	case STREAMTYPE_FLV:
		strStreamType = "FLV";
		break;
	case STREAMTYPE_ISOMP4:
		strStreamType = "ISO MP4";
		break;
	case STREAMTYPE_REAL_MEDIA:
		strStreamType = "RealMedia";
		break;
	case STREAMTYPE_WINDOWS_MEDIA:
		strStreamType = "WindowsMedia";
		break;
	case STREAMTYPE_QUICKTIME_MOV:
		strStreamType = "QuickTime_Mov";
		break;
	case STREAMTYPE_ZAXEL:
		strStreamType = "Zaxel_AVI";
		break;
	case STREAMTYPE_AIFF:
		strStreamType = "AIFF";
		break;
	case STREAMTYPE_MKV:
		strStreamType = "MKV";
		break;
	case STREAMTYPE_GXF:
		strStreamType = "GXF";
		break;
	case STREAMTYPE_OMNEON:
		strStreamType = "OMNEON";
		break;
	case STREAMTYPE_SAF:
		strStreamType = "SAF";
		break;
	case STREAMTYPE_LXF:
		strStreamType = "LXF";
		break;
	case STREAMTYPE_MAV70:
		strStreamType = "MAV70";
		break;
	case STREAMTYPE_VSR2000:
		strStreamType = "VSR2000";
		break;
	case STREAMTYPE_MSS:
		strStreamType = "MSS";
		break;
	case STREAMTYPE_P2CLIP:
		strStreamType = "P2 Clip";
		break;
	case STREAMTYPE_E2CLIP:
		strStreamType = "E2 Clip";
		break;
	case STREAMTYPE_DPX:
		strStreamType = "DPX";
		break;
	case STREAMTYPE_R3D:
		strStreamType = "R3D";
		break;
	case STREAMTYPE_HLS:
		strStreamType = "HLS";
		break;
	case STREAMTYPE_RTP:
		strStreamType = "RTP";
		break;
	}
	return strStreamType;
}

enum VIDEOSCAN_MODE	// 视频扫描帧场数据排列方式, 有时间和空间两个概念，场序（First，Second）表示时间概念，奇偶场(Top，Bottom)表示空间（image Buffer)概念
{
	VIDEOSCANMODE_Invalid = -1,
	VIDEOSCANMODE_FirstFieldTop = 0,			// 两场数据交织排列, 首(First)场排列在奇(Top)场位置
	VIDEOSCANMODE_SecondFieldTop = 1,			// 两场数据交织排列, 第二(Second)场排列在奇(Top)场位置
	VIDEOSCANMODE_Progressive = 2,			// 帧数据连续排列, 无场序时间概念
	VIDEOSCANMODE_ProgressiveSegmented = 3,			// 帧数据分割排列, 无场序时间概念, 无奇偶场空间概念
	VIDEOSCANMODE_FirstFieldTopBackToBack = 4,			// 两场数据分别排列,首(First)场后是第二(Second)场, 无奇偶场空间概念
	VIDEOSCANMODE_SecondFieldTopBackToBack = 5,			// 两场数据分别排列,第二(Second)场后是首(First)场, 无奇偶场空间概念
};

//得到视频扫描帧场数据排列方式的名称
inline std::string GetVideoScanModeHint(VIDEOSCAN_MODE enumScanMode)
{
	std::string	strScanModeHint = "Unknow";
	switch (enumScanMode)
	{
	case VIDEOSCANMODE_FirstFieldTop:
		strScanModeHint = "FirstFieldTop";
		break;
	case VIDEOSCANMODE_SecondFieldTop:
		strScanModeHint = "SecondFieldTop";
		break;
	case VIDEOSCANMODE_Progressive:
		strScanModeHint = "Progressive";
		break;
	case VIDEOSCANMODE_ProgressiveSegmented:
		strScanModeHint = "ProgressiveSegmented";
		break;
	case VIDEOSCANMODE_FirstFieldTopBackToBack:
		strScanModeHint = "FirstFieldTopBackToBack";
		break;
	case VIDEOSCANMODE_SecondFieldTopBackToBack:
		strScanModeHint = "SecondFieldTopBackToBack";
		break;
	}
	return strScanModeHint;
};

enum VIDEO_ASPECTRATIO	// 视频幅宽比类型
{
	VIDEOASPECTRATIO_Invalid = 0x00000000,
	VIDEOASPECTRATIO_4_3 = 0x00000001,
	VIDEOASPECTRATIO_16_9 = 0x00000002,
	VIDEOASPECTRATIO_14_9 = 0x00000003,				//SMPTE 2016-1
};

//得到视频幅宽比类型的名称
inline std::string GetVideoAspectRatioHint(VIDEO_ASPECTRATIO enumAspectRatio)
{
	std::string	strAspectRatioHint = "Unknow";
	switch (enumAspectRatio)
	{
	case VIDEOASPECTRATIO_4_3:
		strAspectRatioHint = "4:3";
		break;
	case VIDEOASPECTRATIO_16_9:
		strAspectRatioHint = "16:9";
		break;
	case VIDEOASPECTRATIO_14_9:
		strAspectRatioHint = "14:9";
		break;
	}
	return strAspectRatioHint;
};

enum COLOR_PRIMARIES			// 源基色的色度坐标(ISO13818-2)
{
	COLORPRIMARIES_Unknow = -1,
	COLORPRIMARIES_Forbidden = 0,
	COLORPRIMARIES_ITU_R709 = 1,		// SMPTE 274M-1995 and SMPTE 296M-1997
	COLORPRIMARIES_Unspecified = 2,
	COLORPRIMARIES_Reserved = 3,
	COLORPRIMARIES_ITU_R470_2M = 4,
	COLORPRIMARIES_ITU_R470_2BG = 5,	// EBU Tech. 3213 (1981).
	COLORPRIMARIES_SMPTE_170M = 6,		// SMPTE 293M-1996, SMPTE 240M-1995,SMPTE 274M-1995
	COLORPRIMARIES_SMPTE_240M = 7,		// Same as SMPTE 170M
	COLORPRIMARIES_GenericFilm = 8,		// from Mpeg4
};

enum DATARATE_TYPE						// MPEG视频编解码格式码率类型
{
	DATARATE_VBR_QUILTY = 0,			//可变码率编码(VBR),质量固定
	DATARATE_CONSTANT = 1,				//恒定码率编码
	DATARATE_VBR_AVERAGE_SMALL = 2,		//可变码率编码(VBR),平均码率, 小码率变化
	DATARATE_VBR_AVERAGE_LARGE = 3,		//可变码率编码(VBR),平均码率, 大码率变化
};

enum RateControlMethod
{
	RATECONTROL_CBR = 1,
	RATECONTROL_VBR = 2,
	RATECONTROL_CQP = 3,
	RATECONTROL_AVBR = 4,
	RATECONTROL_RESERVED1 = 5,
	RATECONTROL_RESERVED2 = 6,
	RATECONTROL_RESERVED3 = 100,
	RATECONTROL_RESERVED4 = 7,
	RATECONTROL_LA = 8
};

//得到MPEG视频编解码格式码率类型的名称
inline std::string GetDataRateTypeHint(DATARATE_TYPE enumDataRateType)
{
	std::string str = "Unknow";
	switch (enumDataRateType)
	{
	case DATARATE_VBR_QUILTY:
		str = "VBR-Quilty";
		break;
	case DATARATE_CONSTANT:
		str = "ConstantRate";
		break;
	case DATARATE_VBR_AVERAGE_SMALL:
		str = "VBR-Average_Small";
		break;
	case DATARATE_VBR_AVERAGE_LARGE:
		str = "VBR-Average_Large";
		break;
	}
	return str;
};

#define	VIDEOMEDIAINFO_STRUSIZE_VER1		52
#define	VIDEOMEDIAINFO_STRUSIZE_VER2		88

struct SVideoMediaInfo	// 视频基本属性
{
	uint32_t				dwStruSize;					// 结构大小
	uint32_t				dwWidth;					// 图像宽度（水平分辨率）
	uint32_t				dwHeight;					// 图像高度（垂直分辨率）
	uint32_t				dwStandardRate;				// 基本帧频
	uint32_t				dwStandardScale;			// 系数（用于帧序号计算）
	VIDEOSCAN_MODE			enumScanMode;				// 视频扫描帧场数据排列方式
	COLOR_FORMAT			enumColorFormat;		    // 视频颜色格式
	VIDEO_TYPE				enumVideoType;				// 视频编解码类型
	CODEC_PROFILE			enumVideoSubType;			// 视频编解码的子类型,子类型定义随enumVideoType不同而不同
	uint32_t				dwDataRateInBitsPerSec;		// 码率, based on *****bits/S******	// Mpeg专用设置
	DATARATE_TYPE			enumDataRateType;			// 码率类型							// Mpeg专用设置
	uint32_t				dwGOPSize;					// IBP帧压缩类型时的IBP帧组大小		// Mpeg专用设置
	uint32_t				dwReferencePeriod;			// IBP帧压缩类型时IP帧的间隔周期。	// Mpeg专用设置
	bool					bIsClipped;					// true:Y(8bit)[16-235]/(10bit)[64,940]---normal, false:Y[0-255][0-1023]---KEY; maybe Cb/Cr
	RateControlMethod		enumRateControlMethod;      // 码率是固定码率还是可变码率
	//Below is Version 2 Add.
	uint32_t				dwDisplayWidth;				// 视频显示幅宽度值
	uint32_t				dwDisplayHeight;			// 视频显示幅高度值
	uint32_t				dwMaxDataRateInBitsPerSec;	// 最大码率, based on *****bits/S******
	uint32_t				dwMinDataRateInBitsPerSec;	// 最小码率, based on *****bits/S******

	SVideoMediaInfo()
	{
		dwStruSize = sizeof(SVideoMediaInfo);
		dwWidth = 720;
		dwHeight = 576;
		dwStandardRate = 25;
		dwStandardScale = 1;
		enumScanMode = VIDEOSCANMODE_FirstFieldTop;
		enumColorFormat = COLORFORMAT_YUVP_420;
		enumVideoType = VIDEOTYPE_UNKNOW;
		enumVideoSubType = PROFILE_UNKNOW;
		dwDataRateInBitsPerSec = 25000000;
		enumDataRateType = DATARATE_CONSTANT;
		dwGOPSize = 14;
		dwReferencePeriod = 2;
		bIsClipped = true;
		dwDisplayWidth = 4;
		dwDisplayHeight = 3;
		dwMaxDataRateInBitsPerSec = 0;
		dwMinDataRateInBitsPerSec = 0;
		enumRateControlMethod = RATECONTROL_CBR;
	};

	SVideoMediaInfo(const SVideoMediaInfo &other)
	{
		*this = other;
	};

	SVideoMediaInfo& operator = (const SVideoMediaInfo& other)
	{
		dwStruSize = other.dwStruSize;
		dwWidth = other.dwWidth;
		dwHeight = other.dwHeight;
		dwStandardRate = other.dwStandardRate;
		dwStandardScale = other.dwStandardScale;
		enumScanMode = other.enumScanMode;
		enumColorFormat = other.enumColorFormat;
		enumVideoType = other.enumVideoType;
		enumVideoSubType = other.enumVideoSubType;
		dwDataRateInBitsPerSec = other.dwDataRateInBitsPerSec;
		enumDataRateType = other.enumDataRateType;
		dwGOPSize = other.dwGOPSize;
		dwReferencePeriod = other.dwReferencePeriod;
		bIsClipped = other.bIsClipped;
		dwDisplayWidth = other.dwDisplayWidth;
		dwDisplayHeight = other.dwDisplayHeight;
		dwMaxDataRateInBitsPerSec = other.dwMaxDataRateInBitsPerSec;
		dwMinDataRateInBitsPerSec = other.dwMinDataRateInBitsPerSec;
		enumRateControlMethod = other.enumRateControlMethod;
		return *this;
	};

	bool operator == (const SVideoMediaInfo& other)
	{
		if (dwStruSize != other.dwStruSize)
			return false;
		if (dwWidth != other.dwWidth || dwHeight != other.dwHeight)
			return false;
		if (dwStandardRate != other.dwStandardRate)
			return false;
		if (dwStandardScale != other.dwStandardScale)
			return false;
		if (enumScanMode != other.enumScanMode)
			return false;
		if (enumColorFormat != other.enumColorFormat)
			return false;
		if (enumVideoType != other.enumVideoType)
			return false;
		if (enumVideoSubType != other.enumVideoSubType)
			return false;
		if (dwDataRateInBitsPerSec != other.dwDataRateInBitsPerSec)
			return false;
		if (enumDataRateType != other.enumDataRateType)
			return false;
		if (dwGOPSize != other.dwGOPSize)
			return false;
		if (dwReferencePeriod != other.dwReferencePeriod)
			return false;
		if (bIsClipped != other.bIsClipped)
			return false;
		if (dwDisplayWidth != other.dwDisplayWidth || dwDisplayHeight != other.dwDisplayHeight)
			return false;
		if (dwMaxDataRateInBitsPerSec != other.dwMaxDataRateInBitsPerSec || dwMinDataRateInBitsPerSec != other.dwMinDataRateInBitsPerSec)
			return false;
		if (enumRateControlMethod != other.enumRateControlMethod)
			return false;

		return true;
	};

	bool operator != (const SVideoMediaInfo& other)
	{
		if (dwStruSize != other.dwStruSize)
			return true;
		if (dwWidth != other.dwWidth || dwHeight != other.dwHeight)
			return true;
		if (dwStandardRate != other.dwStandardRate)
			return true;
		if (dwStandardScale != other.dwStandardScale)
			return true;
		if (enumScanMode != other.enumScanMode)
			return true;
		if (enumColorFormat != other.enumColorFormat)
			return true;
		if (enumVideoType != other.enumVideoType)
			return true;
		if (enumVideoSubType != other.enumVideoSubType)
			return true;
		if (dwDataRateInBitsPerSec != other.dwDataRateInBitsPerSec)
			return true;
		if (enumDataRateType != other.enumDataRateType)
			return true;
		if (dwGOPSize != other.dwGOPSize)
			return true;
		if (dwReferencePeriod != other.dwReferencePeriod)
			return true;
		if (bIsClipped != other.bIsClipped)
			return true;
		if (dwDisplayWidth != other.dwDisplayWidth || dwDisplayHeight != other.dwDisplayHeight)
			return true;
		if (dwMaxDataRateInBitsPerSec != other.dwMaxDataRateInBitsPerSec || dwMinDataRateInBitsPerSec != other.dwMinDataRateInBitsPerSec)
			return true;
		if (enumRateControlMethod != other.enumRateControlMethod)
			return true;

		return false;
	};
};

struct SVideoFrameImageBufInfo	//视频帧图像数据块属性
{
	uint32_t		dwXSize;								// 图象宽度像素数量
	uint32_t		dwYSize;								// 图象高度像素数量
	uint32_t		dwScanXByteSize;						// 跨距
	COLOR_FORMAT	enumColorFormat;						// 颜色格式
	VIDEOSCAN_MODE	enumScanMode;							// 扫描方式

	SVideoFrameImageBufInfo()
	{
		dwXSize = 0;
		dwYSize = 0;
		dwScanXByteSize = 0;
		enumColorFormat = COLORFORMAT_UNKNOW;
		enumScanMode = VIDEOSCANMODE_FirstFieldTop;
	};

	SVideoFrameImageBufInfo(const SVideoFrameImageBufInfo &other)
	{
		*this = other;
	};

	SVideoFrameImageBufInfo& operator = (const SVideoFrameImageBufInfo& other)
	{
		dwXSize = other.dwXSize;
		dwYSize = other.dwYSize;
		dwScanXByteSize = other.dwScanXByteSize;
		enumColorFormat = other.enumColorFormat;
		enumScanMode = other.enumScanMode;
		return *this;
	};
};

enum AUDIO_CHANNELCONFIGURATION		// 声道属性枚举定义
{
	AUDIOCFG_UNKNOW = 0,      // 声道属性未知
	AUDIOCFG_INDEPENDENT = 1,      // 独立声道
	AUDIOCFG_STEREO = 2,      // 立体声(左 右)
	AUDIOCFG_5_1 = 3,		// 5.1(左 右 中置 左环绕 右环绕 低音)
	AUDIOCFG_7_1 = 4,      // 7.0(前左 前右 中置 左 右 左环绕 右环绕  低音)

	AUDIOCFG_2_1 = 5,      // 2.1(左 右 低音)
	AUDIOCFG_3_0_C = 6,      // 3.0(左 右 中置)
	AUDIOCFG_3_0_S = 7,      // 3.0(左 右 环绕)
	AUDIOCFG_3_1_C_LFE = 8,      // 3.1(左 右 中置 低音)
	AUDIOCFG_3_1_S_LFE = 9,      // 3.1(左 右 环绕 低音)
	AUDIOCFG_4_0_C_S = 10,     // 4.0(左 右 中置 环绕)
	AUDIOCFG_4_0_LS_RS = 11,     // 4.0(左 右 左环绕 右环绕)
	AUDIOCFG_4_1_C_S_LFE = 12,     // 4.1(左 右 中置 环绕 低音)
	AUDIOCFG_4_1_LS_RS_LFE = 13,     // 4.1(左 右 左环绕 右环绕 低音)
	AUDIOCFG_5_0 = 14,     // 5.0(左 右 中置 左环绕 右环绕)
	AUDIOCFG_6_0_LRC_LRSRC = 15,     // 6.0(左 右 前中置 左环绕 右环绕 后中置)
	AUDIOCFG_6_0_FLFR_LR_LRS = 16,     // 6.0(前左 前右 左 右 左环绕 右环绕)
	AUDIOCFG_6_1_LRFC_LRSRC_LFE = 17,     // 6.1(左 右 前中置 左环绕  右环绕 后中置 低音)
	AUDIOCFG_6_1_FLR_LRLRS_LFE = 18,     // 6.1(前左 前右 左 右 左环绕 右环绕 低音)
	AUDIOCFG_7_0 = 19,     // 7.0(前左 前右 中置 左 右 左环绕 右环绕)
};

//得到声道属性枚举定义的名称
inline std::string GeAudioCFGHint(AUDIO_CHANNELCONFIGURATION enumAudioCFG)
{
	std::string str = "Unknow";
	switch (enumAudioCFG)
	{
	case AUDIOCFG_INDEPENDENT:					// 独立声道
		str = "Independent";
		break;
	case AUDIOCFG_STEREO:						// 立体声(左 右)
		str = "Stereo";
		break;
	case AUDIOCFG_5_1:							// 5.1(左 右 中置 左环绕 右环绕 低音)
		str = "5.1";
		break;
	case AUDIOCFG_7_1:							// 7.0(前左 前右 中置 左 右 左环绕 右环绕  低音)
		str = "7.1";
		break;
	case AUDIOCFG_2_1:							// 2.1(左 右 低音)
		str = "2.1(Left_Right_Lfe)";
		break;
	case AUDIOCFG_3_0_C:						// 3.0(左 右 中置)
		str = "3.0(Left_Right_Center)";
		break;
	case AUDIOCFG_3_0_S:						// 3.0(左 右 环绕)
		str = "3.0(Left_Right_Surround)";
		break;
	case AUDIOCFG_3_1_C_LFE:					// 3.1(左 右 中置 低音)
		str = "3.1(Left_Right_Center_Lfe)";
		break;
	case AUDIOCFG_3_1_S_LFE:					// 3.1(左 右 环绕 低音)
		str = "3.1(Left_Right_Surround_Lfe)";
		break;
	case AUDIOCFG_4_0_C_S:						// 4.0(左 右 中置 环绕)
		str = "4.0(Left_Right_Center_Surround)";
		break;
	case AUDIOCFG_4_0_LS_RS:					// 4.0(左 右 左环绕 右环绕)
		str = "4.0(Left_Right_SurroundLeft_SurroundRight)";
		break;
	case AUDIOCFG_4_1_C_S_LFE:					// 4.1(左 右 中置 环绕 低音)
		str = "4.1(Left_Right_Center_Surround_Lfe)";
		break;
	case AUDIOCFG_4_1_LS_RS_LFE:				// 4.1(左 右 左环绕 右环绕 低音)
		str = "4.1(Left_Right_SurroundLeft_SurroundRight_Lfe)";
		break;
	case AUDIOCFG_5_0:							// 5.0(左 右 中置 左环绕 右环绕)
		str = "5.0(Left_Right_Center_SurroundLeft_SurroundRight)";
		break;
	case AUDIOCFG_6_0_LRC_LRSRC:				// 6.0(左 右 前中置 左环绕 右环绕 后中置)
		str = "6.0(Left_Right_FrontCenter_SurroundLeft_SurroundRight_RearCenter)";
		break;
	case AUDIOCFG_6_0_FLFR_LR_LRS:				// 6.0(前左 前右 左 右 左环绕 右环绕)
		str = "6.0(FrontLeft_FrontRight_Left_Right_SurroundLeft_SurroundRight)";
		break;
	case AUDIOCFG_6_1_LRFC_LRSRC_LFE:			// 6.1(左 右 前中置 左环绕  右环绕 后中置 低音)
		str = "6.1(Left_Right_FrontCenter_SurroundLeft_SurroundRight_RearCenter_Lfe)";
		break;
	case AUDIOCFG_6_1_FLR_LRLRS_LFE:			// 6.1(前左 前右 左 右 左环绕 右环绕 低音)
		str = "6.1(FrontLeft_FrontRight_Left_Right_SurroundLeft_SurroundRight_Lfe)";
		break;
	case AUDIOCFG_7_0:							// 7.0(前左 前右 中置 左 右 左环绕 右环绕)
		str = "7.0(FrontLeft_FrontRight_Center_Left_Right_SurroundLeft_SurroundRight)";
		break;
	}
	return str;
};
//音频声道采样数据格式
enum CHANNELSAMPLE_FORMAT	
{
	SAMPLE_FMT_NONE = -1,
	SAMPLE_FMT_U8,          ///< unsigned 8 bits
	SAMPLE_FMT_S16,         ///< signed 16 bits
	SAMPLE_FMT_S32,         ///< signed 32 bits
	SAMPLE_FMT_FLT,         ///< float
	SAMPLE_FMT_DBL,         ///< double
	SAMPLE_FMT_U8P,         ///< unsigned 8 bits, planar
	SAMPLE_FMT_S16P,        ///< signed 16 bits, planar
	SAMPLE_FMT_S32P,        ///< signed 32 bits, planar
	SAMPLE_FMT_FLTP,        ///< float, planar
	SAMPLE_FMT_DBLP,        ///< double, planar
	SAMPLE_FMT_S64,         ///< signed 64 bits
	SAMPLE_FMT_S64P,        ///< signed 64 bits, planar
	SAMPLE_FMT_NB           ///< Number of sample formats. DO NOT USE if linking dynamicall
};

enum ARes		//量化精度
{
	ARUnknown = 0x0000,
	ARI8 = 0x0001,
	ARI16 = 0x0002,
	ARI24 = 0x0003,	// used for 20 bits as well
	ARI32 = 0x0100,
	ARF32 = 0x0200,	// IEEE 754 32 bit float
	ARF64 = 0x0400,	// IEEE 754 64 bit double float

	// 下面的数据格式实为32bit，只是低字节无效
	ARI32_16 = 0x0101,	// 32 bit data with 16 bit alignment
	ARI32_18 = 0x0102,	// 32 bit data with 18 bit alignment
	ARI32_20 = 0x0103,	// 32 bit data with 20 bit alignment
	ARI32_24 = 0x0104,	// 32 bit data with 24 bit alignment
	ARI32_32 = ARI32,
};

//根据量化精度得到单声道一个采样点占用的字节数
inline short sizeofARes(ARes res)
{
	switch (res)
	{
	case ARI8:return 1;
	case ARI16:return 2;
	case ARI24:return 3;
	case ARI32:return 4;
	case ARF32:return 4;
	case ARF64:return 8;
	case ARI32_16:
	case ARI32_18:
	case ARI32_20:
	case ARI32_24:
		return 4;
	default:
		return 0;
	}
}

#define	AUDIOMEDIAINFO_STRUSIZE_VER1		32
#define	AUDIOMEDIAINFO_STRUSIZE_VER2		40

struct SAudioMediaInfo			// 音频基本属性
{
	uint32_t			dwStruSize;			// 结构大小
	AUDIO_TYPE			enumAudioType;		// 音频编解码类型。
	uint32_t			dwAudioSubType;		// 音频编解码的子类型,子类型定义随enumAudioType不同而不同
	uint32_t			dwChannels;			// 声道数目
	uint32_t			dwBitsPerSample;	// 采样位数 
	uint32_t			dwSamplesPerSec;	// 每秒采样数量 
	uint32_t			dwAvgBitsPerSec;	// 音频码率 Bit                     
	uint32_t			dwBlockAlign;		// 数据块对齐单位(每个采样样本需要的字节数), 声道数*量化数/8, 量化数(16,20?,24,32...)

	//Below is Version 2 Add.
	AUDIO_CHANNELCONFIGURATION enumAudioCFG;	//声道属性
	CHANNELSAMPLE_FORMAT enumChannelSamplesFormat;	//音频声道采样数据格式

	SAudioMediaInfo()
	{
		dwStruSize = sizeof(SAudioMediaInfo);
		enumAudioType = AUDIOTYPE_WAVE_PCM;
		dwAudioSubType = 0;
		dwChannels = 2;
		dwBitsPerSample = 16;
		dwSamplesPerSec = 48000;
		dwAvgBitsPerSec = dwSamplesPerSec*dwBitsPerSample*dwChannels;
		dwBlockAlign = 4;
		enumAudioCFG = AUDIOCFG_STEREO;
		enumChannelSamplesFormat = SAMPLE_FMT_S16;
	};

	SAudioMediaInfo(const SAudioMediaInfo &other)
	{
		*this = other;
	};

	SAudioMediaInfo& operator = (const SAudioMediaInfo& other)
	{
		dwStruSize = other.dwStruSize;
		enumAudioType = other.enumAudioType;
		dwAudioSubType = other.dwAudioSubType;
		dwChannels = other.dwChannels;
		dwBitsPerSample = other.dwBitsPerSample;
		dwSamplesPerSec = other.dwSamplesPerSec;
		dwAvgBitsPerSec = other.dwAvgBitsPerSec;
		dwBlockAlign = other.dwBlockAlign;
		enumAudioCFG = other.enumAudioCFG;
		enumChannelSamplesFormat = other.enumChannelSamplesFormat;
		return *this;
	};

	bool operator == (const SAudioMediaInfo& other)
	{
		if (dwStruSize != other.dwStruSize)
			return false;
		if (enumAudioType != other.enumAudioType)
			return false;
		if (dwAudioSubType != other.dwAudioSubType)
			return false;
		if (dwChannels != other.dwChannels)
			return false;
		if (dwBitsPerSample != other.dwBitsPerSample)
			return false;
		if (dwSamplesPerSec != other.dwSamplesPerSec)
			return false;
		if (dwAvgBitsPerSec != other.dwAvgBitsPerSec)
			return false;
		if (dwBlockAlign != other.dwBlockAlign)
			return false;
		if (enumAudioCFG != other.enumAudioCFG)
			return false;
		if (enumChannelSamplesFormat != other.enumChannelSamplesFormat)
			return false;

		return true;
	};

	bool operator != (const SAudioMediaInfo& other)
	{
		if (dwStruSize != other.dwStruSize)
			return true;
		if (enumAudioType != other.enumAudioType)
			return true;
		if (dwAudioSubType != other.dwAudioSubType)
			return true;
		if (dwChannels != other.dwChannels)
			return true;
		if (dwBitsPerSample != other.dwBitsPerSample)
			return true;
		if (dwSamplesPerSec != other.dwSamplesPerSec)
			return true;
		if (dwAvgBitsPerSec != other.dwAvgBitsPerSec)
			return true;
		if (dwBlockAlign != other.dwBlockAlign)
			return true;
		if (enumAudioCFG != other.enumAudioCFG)
			return true;
		if (enumChannelSamplesFormat != other.enumChannelSamplesFormat)
			return true;

		return false;
	};

	bool  CloneBufPtr(void* pStruBuf)
	{
		if (pStruBuf)
		{
			uint8_t*	pbStruBuf = (uint8_t*)pStruBuf;
			uint32_t	dwStruBufSize = (*((uint32_t*)pStruBuf));
			if (dwStruBufSize == AUDIOMEDIAINFO_STRUSIZE_VER1 || dwStruBufSize == AUDIOMEDIAINFO_STRUSIZE_VER2)
			{
				pbStruBuf += sizeof(uint32_t);

				enumAudioType = (AUDIO_TYPE)((*((int32_t*)pbStruBuf)));
				pbStruBuf += sizeof(int32_t);

				dwAudioSubType = (*((uint32_t*)pbStruBuf));
				pbStruBuf += sizeof(uint32_t);

				dwChannels = (*((uint32_t*)pbStruBuf));
				pbStruBuf += sizeof(uint32_t);

				dwBitsPerSample = (*((uint32_t*)pbStruBuf));
				pbStruBuf += sizeof(uint32_t);

				dwSamplesPerSec = (*((uint32_t*)pbStruBuf));
				pbStruBuf += sizeof(uint32_t);

				dwAvgBitsPerSec = (*((uint32_t*)pbStruBuf));
				pbStruBuf += sizeof(uint32_t);

				dwBlockAlign = (*((uint32_t*)pbStruBuf));
				pbStruBuf += sizeof(uint32_t);

				if (dwStruBufSize == AUDIOMEDIAINFO_STRUSIZE_VER2)
				{
					enumAudioCFG = (AUDIO_CHANNELCONFIGURATION)((*((int32_t*)pbStruBuf)));
					pbStruBuf += sizeof(int32_t);
					enumChannelSamplesFormat = (CHANNELSAMPLE_FORMAT)((*((int32_t*)pbStruBuf)));
					pbStruBuf += sizeof(int32_t);
				}
				else
				{
					enumAudioCFG = AUDIOCFG_INDEPENDENT;
					enumChannelSamplesFormat = SAMPLE_FMT_S16;
				}
				return true;
			}
			return false;
		}
	};
};

struct SAudioSamplesBufInfo	//音频采样数据块属性
{
	uint32_t			dwChannels;								// 声道数目
	uint32_t			dwBitsPerSample;						// 采样位数 
	uint32_t			dwSamplesPerSec;						// 每秒采样数量 
	uint32_t			dwAvgBitsPerSec;						// 音频码率
	uint32_t			dwBlockAlign;							// 数据块对齐单位(每个采样样本需要的字节数), 声道数*量化数/8, 量化数(16,20?,24,32...)
	AUDIO_CHANNELCONFIGURATION	enumAudioCFG;					// 声道属性
	CHANNELSAMPLE_FORMAT		enumChannelSamplesFormat;		// 音频声道采样数据格式

	SAudioSamplesBufInfo()
	{
		dwChannels = 2;
		dwBitsPerSample = 16;
		dwSamplesPerSec = 48000;
		dwAvgBitsPerSec = dwSamplesPerSec*dwBitsPerSample*dwChannels;
		dwBlockAlign = 4;
		enumAudioCFG = AUDIOCFG_STEREO;
		enumChannelSamplesFormat = SAMPLE_FMT_S16;
	};

	SAudioSamplesBufInfo(const SAudioSamplesBufInfo &other)
	{
		*this = other;
	};

	SAudioSamplesBufInfo& operator = (const SAudioSamplesBufInfo& other)
	{
		dwChannels = other.dwChannels;
		dwBitsPerSample = other.dwBitsPerSample;
		dwSamplesPerSec = other.dwSamplesPerSec;
		dwAvgBitsPerSec = other.dwAvgBitsPerSec;
		dwBlockAlign = other.dwBlockAlign;
		enumAudioCFG = other.enumAudioCFG;
		enumChannelSamplesFormat = other.enumChannelSamplesFormat;
		return *this;
	};
};

//枚举所有可能的subtitle文件类型
//是否作为dwStreamSubType？MediaType为STREAMTYPE_SUBTITLE
enum SUBTITLE_TYPE//字幕流类型
{
	SUBSTYPE_UNKNOWN = 0,
	SUBSTYPE_SUBRIP = 1,		//srt字幕格式
	SUBSTYPE_DVBSUBTITLE = 2,	//TS 字幕
	SUBSTYPE_DVDSUBTITLE = 3,	//DVD字幕
	SUBSTYPE_SSA1 = 4,
	SUBSTYPE_SSA2_4 = 5,
	SUBSTYPE_ASS = 6,
};

#define	STREAMMEDIAINFO_STRUSIZE_VER1		100		//VIDEOMEDIAINFO_STRUSIZE_VER1(52)+AUDIOMEDIAINFO_STRUSIZE_VER2(32)+16
#define	STREAMMEDIAINFO_STRUSIZE_VER2		160		//VIDEOMEDIAINFO_STRUSIZE_VER2(88)+AUDIOMEDIAINFO_STRUSIZE_VER2(40)+32
#define	STREAMMEDIAINFO_STRUSIZE_VER3		168		//VIDEOMEDIAINFO_STRUSIZE_VER2(88)+AUDIOMEDIAINFO_STRUSIZE_VER2(40)+32+SUBTITLEMEDIAINFO_STRUSIZE_VER1(8)

struct SStreamMediaInfo		// 视音频流(文件)属性
{
	uint32_t				dwStruSize;						// 结构大小
	uint32_t				dwTotalAverDataRateInBitsPerSec;// 总体平均码率, based on *****bits/S******
	uint32_t				dwTotalMaxDataRateInBitsPerSec;	// 总体最大码率, based on *****bits/S******
	uint32_t				dwTotalMinDataRateInBitsPerSec;	// 总体最小码率, based on *****bits/S******

	STREAM_TYPE				enumStreamMediaType;			// stream type
	uint32_t				dwStreamMediaSubType;			// 文件属性的子类型,子类型定义随enumStreamMediaType不同而不同

	uint32_t				dwVideoStreamCount;				// 视音频流(文件)包含视频流的数量
	SVideoMediaInfo			sVideoMediaInfo;				// 视音频流(文件)中第一个视频流的媒体属性.

	uint32_t				dwAudioStreamCount;				// 视音频流(文件)包含音频流的数量
	SAudioMediaInfo			sAudioMediaInfo;				// 视音频流(文件)中第一个音频流的媒体属性.

	SStreamMediaInfo()
	{
		dwStruSize = sizeof(SStreamMediaInfo);
		dwTotalAverDataRateInBitsPerSec = 0;
		dwTotalMaxDataRateInBitsPerSec = 0;
		dwTotalMinDataRateInBitsPerSec = 0;
		enumStreamMediaType = STREAMTYPE_UNKNOWN;
		dwStreamMediaSubType = 0;
		dwVideoStreamCount = 0;
		dwAudioStreamCount = 0;
	};

	SStreamMediaInfo(const SStreamMediaInfo &other)
	{
		*this = other;
	};

	SStreamMediaInfo& operator = (const SStreamMediaInfo& other)
	{
		dwStruSize = other.dwStruSize;
		dwTotalAverDataRateInBitsPerSec = other.dwTotalAverDataRateInBitsPerSec;
		dwTotalMaxDataRateInBitsPerSec = other.dwTotalMaxDataRateInBitsPerSec;
		dwTotalMinDataRateInBitsPerSec = other.dwTotalMinDataRateInBitsPerSec;
		enumStreamMediaType = other.enumStreamMediaType;
		dwStreamMediaSubType = other.dwStreamMediaSubType;
		dwVideoStreamCount = other.dwVideoStreamCount;
		sVideoMediaInfo = other.sVideoMediaInfo;
		dwAudioStreamCount = other.dwAudioStreamCount;
		sAudioMediaInfo = other.sAudioMediaInfo;

		return *this;
	};

	bool operator == (const SStreamMediaInfo& other)
	{
		if (dwStruSize != other.dwStruSize)
			return false;
		if (dwTotalAverDataRateInBitsPerSec != other.dwTotalAverDataRateInBitsPerSec)
			return false;
		if (dwTotalMaxDataRateInBitsPerSec != other.dwTotalMaxDataRateInBitsPerSec)
			return false;
		if (dwTotalMinDataRateInBitsPerSec != other.dwTotalMinDataRateInBitsPerSec)
			return false;
		if (enumStreamMediaType != other.enumStreamMediaType)
			return false;
		if (dwStreamMediaSubType != other.dwStreamMediaSubType)
			return false;

		if ((dwVideoStreamCount == 0 && other.dwVideoStreamCount > 0) ||
			(dwVideoStreamCount > 0 && other.dwVideoStreamCount == 0))
			return false;
		if ((dwAudioStreamCount == 0 && other.dwAudioStreamCount > 0) ||
			(dwAudioStreamCount > 0 && other.dwAudioStreamCount == 0))
			return false;

		if (dwVideoStreamCount > 0)
		{
			if (sVideoMediaInfo != other.sVideoMediaInfo)
				return false;
		}
		if (dwAudioStreamCount > 0)
		{
			if (sAudioMediaInfo != other.sAudioMediaInfo)
				return false;
		}
		return true;
	};
};

struct SStreamMediaInfoEx : public SStreamMediaInfo		// 视音频流(文件)扩展属性
{
	uint64_t	llFileSize;					// 文件大小
	uint32_t	dwVideoFrameNum;			// 视频流数据的长度。(Unit:Frame)
	uint32_t	dwAudioSamplesNum;			// 音频流数据长度	 (Unit:Sample)
	uint32_t	dwSubtitleFrameNum;         // 字幕流数据的长度(Unit:SubtitleFrame)

	SStreamMediaInfoEx()
	{
		dwStruSize = sizeof(SStreamMediaInfoEx);
		llFileSize = 0;
		dwVideoFrameNum = 0;
		dwAudioSamplesNum = 0;
		dwSubtitleFrameNum = 0;
	};

	SStreamMediaInfoEx(const SStreamMediaInfoEx &other)
	{
		*this = other;
	};

	SStreamMediaInfoEx(const SStreamMediaInfo &other)
	{
		*this = other;
	};

	SStreamMediaInfoEx& operator = (const SStreamMediaInfoEx& other)
	{
		dwStruSize = other.dwStruSize;
		dwTotalAverDataRateInBitsPerSec = other.dwTotalAverDataRateInBitsPerSec;
		dwTotalMaxDataRateInBitsPerSec = other.dwTotalMaxDataRateInBitsPerSec;
		dwTotalMinDataRateInBitsPerSec = other.dwTotalMinDataRateInBitsPerSec;
		llFileSize = other.llFileSize;
		enumStreamMediaType = other.enumStreamMediaType;
		dwVideoStreamCount = other.dwVideoStreamCount;
		sVideoMediaInfo = other.sVideoMediaInfo;
		dwVideoFrameNum = other.dwVideoFrameNum;
		dwAudioStreamCount = other.dwAudioStreamCount;
		sAudioMediaInfo = other.sAudioMediaInfo;
		dwAudioSamplesNum = other.dwAudioSamplesNum;
		dwSubtitleFrameNum = other.dwSubtitleFrameNum;
		return *this;
	};

	SStreamMediaInfoEx& operator = (const SStreamMediaInfo& other)
	{
		dwStruSize = sizeof(SStreamMediaInfoEx);
		dwTotalAverDataRateInBitsPerSec = other.dwTotalAverDataRateInBitsPerSec;
		dwTotalMaxDataRateInBitsPerSec = other.dwTotalMaxDataRateInBitsPerSec;
		dwTotalMinDataRateInBitsPerSec = other.dwTotalMinDataRateInBitsPerSec;
		enumStreamMediaType = other.enumStreamMediaType;
		dwStreamMediaSubType = other.dwStreamMediaSubType;
		dwVideoStreamCount = other.dwVideoStreamCount;
		sVideoMediaInfo = other.sVideoMediaInfo;
		dwAudioStreamCount = other.dwAudioStreamCount;
		sAudioMediaInfo = other.sAudioMediaInfo;
		llFileSize = 0;
		dwVideoFrameNum = 0;
		dwAudioSamplesNum = 0;
		dwSubtitleFrameNum = 0;

		return *this;
	};

	bool GetStreamMediaInfo(SStreamMediaInfo *psInfo)
	{
		if (psInfo)
		{
			psInfo->dwStruSize = sizeof(SStreamMediaInfo);
			psInfo->dwTotalAverDataRateInBitsPerSec = dwTotalAverDataRateInBitsPerSec;
			psInfo->dwTotalMaxDataRateInBitsPerSec = dwTotalMaxDataRateInBitsPerSec;
			psInfo->dwTotalMinDataRateInBitsPerSec = dwTotalMinDataRateInBitsPerSec;
			psInfo->enumStreamMediaType = enumStreamMediaType;
			psInfo->dwStreamMediaSubType = dwStreamMediaSubType;
			psInfo->dwVideoStreamCount = dwVideoStreamCount;
			psInfo->sVideoMediaInfo = sVideoMediaInfo;
			psInfo->dwAudioStreamCount = dwAudioStreamCount;
			psInfo->sAudioMediaInfo = sAudioMediaInfo;
			return true;
		}
		else
			return false;
	};
};

enum STREAMMEDIA_TYPE	//流媒体数据信息类型
{
	STREAMMEDIATYPE_Unknow = 0,
	STREAMMEDIATYPE_VIDEOAUDIO = 1,		//视音频格式
	STREAMMEDIATYPE_SINGLEPROGRAM = 2,		//单节目流格式
	STREAMMEDIATYPE_MULTIPROGRAM = 3,		//多节目流格式
};

//得到流媒体数据信息类型的名称
inline std::string GetStreamMediaTypeHint(STREAMMEDIA_TYPE enumStreamMediaType)
{
	std::string strHint = "Unknow";

	switch (enumStreamMediaType)
	{
	case STREAMMEDIATYPE_VIDEOAUDIO:
		strHint = "VideoAudio";
		break;
	case STREAMMEDIATYPE_SINGLEPROGRAM:
		strHint = "Single Program";
		break;
	case STREAMMEDIATYPE_MULTIPROGRAM:
		strHint = "Multi Program";
		break;
	}
	return strHint;
};

enum MEDIADATASTREAM_TYPE	//媒体数据流数据类型
{
	MEDIADATASTREAMTYPE_Unknow = 0,
	MEDIADATASTREAMTYPE_VIDEO1 = 0x00000001,		//视频流1
	MEDIADATASTREAMTYPE_VIDEO2 = 0x00000002,		//视频流2
	MEDIADATASTREAMTYPE_VIDEO3 = 0x00000004,		//视频流3
	MEDIADATASTREAMTYPE_VIDEO4 = 0x00000008,		//视频流4
	MEDIADATASTREAMTYPE_AUDIO1 = 0x00000100,		//音频流1
	MEDIADATASTREAMTYPE_AUDIO2 = 0x00000200,		//音频流2
	MEDIADATASTREAMTYPE_AUDIO3 = 0x00000400,		//音频流3
	MEDIADATASTREAMTYPE_AUDIO4 = 0x00000800,		//音频流4
	MEDIADATASTREAMTYPE_AUDIO5 = 0x00001000,		//音频流5
	MEDIADATASTREAMTYPE_AUDIO6 = 0x00002000,		//音频流6
	MEDIADATASTREAMTYPE_AUDIO7 = 0x00004000,		//音频流7
	MEDIADATASTREAMTYPE_AUDIO8 = 0x00008000,		//音频流8
	MEDIADATASTREAMTYPE_AUDIO9 = 0x00010000,		//音频流9
	MEDIADATASTREAMTYPE_AUDIO10 = 0x00020000,		//音频流10
	MEDIADATASTREAMTYPE_AUDIO11 = 0x00040000,		//音频流11
	MEDIADATASTREAMTYPE_AUDIO12 = 0x00080000,		//音频流12
	MEDIADATASTREAMTYPE_AUDIO13 = 0x00100000,		//音频流13
	MEDIADATASTREAMTYPE_AUDIO14 = 0x00200000,		//音频流14
	MEDIADATASTREAMTYPE_AUDIO15 = 0x00400000,		//音频流15
	MEDIADATASTREAMTYPE_AUDIO16 = 0x00800000,		//音频流16
	MEDIADATASTREAMTYPE_SUBTITLE1 = 0x01000000,		//字幕流1
	MEDIADATASTREAMTYPE_SUBTITLE2 = 0x02000000,		//字幕流2
	MEDIADATASTREAMTYPE_SUBTITLE3 = 0x04000000,		//字幕流3
	MEDIADATASTREAMTYPE_SUBTITLE4 = 0x08000000,		//字幕流4
	MEDIADATASTREAMTYPE_SUBTITLE5 = 0x10000000,		//字幕流5
	MEDIADATASTREAMTYPE_SUBTITLE6 = 0x20000000,		//字幕流6
	MEDIADATASTREAMTYPE_SUBTITLE7 = 0x40000000,		//字幕流7
	MEDIADATASTREAMTYPE_SUBTITLE8 = 0x80000000,		//字幕流8
};

//========================================================================================
typedef	uint32_t DEVICERECTRACKFLAG;
//----------------------------------------------------------------------------------------
#define	DEVICE_RECTRACK_AUDIO_ALL				0x10000000	//	or any of the following OR'd together
#define DEVICE_RECTRACK_AUDIO_1					0x0000001L
#define DEVICE_RECTRACK_AUDIO_2					0x0000002L
#define DEVICE_RECTRACK_AUDIO_3					0x0000004L
#define DEVICE_RECTRACK_AUDIO_4					0x0000008L
#define DEVICE_RECTRACK_AUDIO_5					0x0000010L
#define DEVICE_RECTRACK_AUDIO_6					0x0000020L
#define DEVICE_RECTRACK_AUDIO_7					0x0000040L
#define DEVICE_RECTRACK_AUDIO_8					0x0000080L
#define DEVICE_RECTRACK_AUDIO_9					0x0000100L
#define DEVICE_RECTRACK_AUDIO_10				0x0000200L
#define DEVICE_RECTRACK_AUDIO_11				0x0000400L
#define DEVICE_RECTRACK_AUDIO_12				0x0000800L
#define DEVICE_RECTRACK_AUDIO_13				0x0001000L
#define DEVICE_RECTRACK_AUDIO_14				0x0002000L
#define DEVICE_RECTRACK_AUDIO_15				0x0004000L
#define DEVICE_RECTRACK_AUDIO_16				0x0008000L
#define DEVICE_RECTRACK_AUDIO_17				0x0010000L
#define DEVICE_RECTRACK_AUDIO_18				0x0020000L
#define DEVICE_RECTRACK_AUDIO_19				0x0040000L
#define DEVICE_RECTRACK_AUDIO_20				0x0080000L
#define DEVICE_RECTRACK_AUDIO_21				0x0100000L
#define DEVICE_RECTRACK_AUDIO_22				0x0200000L
#define DEVICE_RECTRACK_AUDIO_23				0x0400000L
#define DEVICE_RECTRACK_AUDIO_24				0x0800000L
#define DEVICE_RECTRACK_VIDEO					0x2000000L	
//========================================================================================

//========================================================================================
#define DEVICE_RECMODE_ASSEMBLE					(0x1000L+660L)
#define DEVICE_RECMODE_INSERT					(0x1000L+661L)
//========================================================================================

enum FIELD
{
	ODD_FIELD = 0,		//奇数场
	EVEN_FIELD = 1,		//偶数场
	BOTH_FIELD = 2,		//奇偶场
};

enum VIDEO_SCALE_TYPE		//高标清上下变换类型定义
{
	VIDEO_SCALE_TYPE_NONE = 0,
	VIDEO_SCALE_TYPE_BOX = 1,	//信箱 
	VIDEO_SCALE_TYPE_ZOOM = 2,	//放大	
	VIDEO_SCALE_TYPE_CUT = 3,	//切边
	VIDEO_SCALE_TYPE_WINDOW = 4,	//窗口
};

// 流数据类型	
enum STREAM_DATATYPE
{
	STREAM_DATATYPE_UNKNOW = 0,	// 未知类型 
	STREAM_DATATYPE_VIDEO = 1,	// 视频
	STREAM_DATATYPE_AUDIO = 2,	// 音频
	STREAM_DATATYPE_SUBTITLE = 3,	// 字幕
};
// 流数据状态
enum STREAMSTATE
{
	STREAMSTATE_BEGIN = 0,	 // 流数据的第1次输入
	STREAMSTATE_CONTINUE = 1,	 // 流数据的中间输入
	STREAMSTATE_END = 2,	 // 流数据的最后输入
	STREAMSTATE_SEQEND = 3	 // 流数据的多段时每段结束
};

// 帧压缩类型
enum FRAME_COMPRESS_TYPE
{
	FRAMETYPE_UNKNOW = 0,		// 未知类型 
	FRAMETYPE_I = 1,			// 帧内压缩
	FRAMETYPE_P = 2,			// 前向压缩
	FRAMETYPE_B = 3,			// 双向压缩
	FRAMETYPE_B_CLOSED = 4,		// 后向压缩的B帧
	FRAMETYPE_UNCOMPRESS = 5,	// 无压缩
	FRAMETYPE_B_REFERENCE = 6,	// 可以做参考帧的B帧(在H264中DYR_FRAMETYPE_B是不能做参考帧的B帧，DYR_FRAMETYPE_B_REFERENCE是可以做参考帧的B帧)
	FRAMETYPE_SI = 7,			// H.264中的SI类型
	FRAMETYPE_SP = 8,			// H.264中的SP类型
	FRAMETYPE_REFI = 9,			// H.264中的用作参考的I帧(H264中的IDR定义为DYR_FRAMETYPE_I)
	FRAMETYPE_NULL = 100,	    // 无效数据
	FRAMETYPE_SKIPFRAME = 101 // VirtualDub Skip Frame, 大小可能为0
};

// 帧数据描述
struct SRFrameInfo
{
	//结构版本
	uint32_t				iVersion;		// 结构版本号。		4---4[序列化占用字节－序列化位置]

	//基本描述
	STREAM_DATATYPE			emDataType;		// 帧数据类型		4---8
	STREAMSTATE			    emStreamFlag;   // 标识是第一帧，还是中间帧，还是末尾帧
	uint32_t				iSize;			// 帧数据大小		4---16
	uint32_t 				dwFrameIndex;	// 帧数据流顺序		4---28
	uint32_t 				dwFrameNum;		// 视频/音频帧数量	4---32

	int32_t 				iSamplesOffset;	// 标识RawAudio音频、视频帧中有效采样的偏移数，大于0表示从开始偏移，小于0表示从尾部开始向前偏移		4---36

	// 时间信息扩展
	uint64_t				qwDTS;			// 解码时间(90Khz单位)	8---44
	uint64_t				qwPTS;			// 展现时间(90Khz单位)	8---52
	uint64_t				qwDuration;		// 持续时间(90Khz单位)	8---6

	// for Video
	uint32_t				dwShowIndex;	// 帧数据显示顺序			4---104
	FRAME_COMPRESS_TYPE		emFrameType;   	// 帧类型 				4---108

	int						extradata_size;

	SRFrameInfo()
	{
		iVersion = 1;
		emDataType = STREAM_DATATYPE_UNKNOW;
		iSize = 0;
		dwFrameNum = 1;
		dwShowIndex = 0; // 表示帧数据显示顺序无效
		emFrameType = FRAMETYPE_I;
		qwDTS = -1;
		qwPTS = -1; // 表示帧数据展现顺序无效
		qwDuration = 0; // 表示帧数据持续时间未知

		iSamplesOffset = 0;
		emStreamFlag = STREAMSTATE_BEGIN;

		extradata_size = 0;
	};

	SRFrameInfo &operator = (const SRFrameInfo &other)
	{
		iVersion = 1;

		emDataType = other.emDataType;
		iSize = other.iSize;

		dwFrameIndex = other.dwFrameIndex;
		dwFrameNum = other.dwFrameNum;

		iSamplesOffset = other.iSamplesOffset;

		qwDTS = other.qwDTS; // 表示帧数据显示顺序无效
		qwPTS = other.qwPTS; // 表示帧数据展现顺序无效
		qwDuration = other.qwDuration; // 表示帧数据持续时间未知

		dwShowIndex = other.dwShowIndex; // 表示帧数据显示顺序无效
		emFrameType = other.emFrameType;
		emStreamFlag = other.emStreamFlag;
		return *this;
	}
};// struct SRFrameInfo
struct SResamplerPara
{

};
#endif

