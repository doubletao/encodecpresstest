/***************************************************************************
* SDVADefine.H
*
* 公共头文件之一,EasyCode科技公司版权所有!
*
* 描述:		-作为共用的最底层头文件，定义了与音视频相关的最重要的常量、枚举、结构、类、函数等。
*			 考虑了跨平台的应用和减少编译依赖性。
*
* 目标:		- 1.与视频制式标准相关的幅宽高、帧率定义和相应的相互转换函数 ......
*			  2.与视音频压缩编码、文件(流)封装、节目复用等有关的枚举、结构及函数定义 ......
*             3.与视音频信号、设备、数据块相关的扩展定义 ......
*
* Ver-0.9
*
****************************************************************************/
#ifndef _SD_SDVADEFINE_H
#define _SD_SDVADEFINE_H

#include "SDDefine.h"

#pragma warning(push)
#pragma warning(disable:4100)
#pragma warning(disable:4244)

enum SD_VIDEO_STANDARD	// 视频制式标准
{
	SDVIDEOSTANDARD_UNKNOW			= 0x00000000,	// Unknow type.

	SDVIDEOSTANDARD_PAL				= 0x00000001,	// PAL video type.						//ITU.R-BT656
	SDVIDEOSTANDARD_NTSC2997		= 0x00000002,	// NTSC video type.						//ITU.R-BT656
	SDVIDEOSTANDARD_NTSC30			= 0x00000004,	// 30-frames/second generic type.

	SDVIDEOSTANDARD_HD1080i_25		= 0x00000010,	// HDTV 1920*1080*25 type.				//SMPTE 274M
	SDVIDEOSTANDARD_HD1080i_2997	= 0x00000020,	// HDTV 1920*1080*29.97 type.			//SMPTE 274M
	SDVIDEOSTANDARD_HD1080i_30		= 0x00000040,	// HDTV 1920*1080*30 type.				//SMPTE 274M
	
	SDVIDEOSTANDARD_HD720p_2398		= 0x00000080,	// HDTV 1280*720*23.98 type.			//SMPTE 296M
	SDVIDEOSTANDARD_HD720p_24		= 0x00000200,	// HDTV 1280*720*24 type.				//SMPTE 296M
	SDVIDEOSTANDARD_HD720p_25		= 0x00000100,	// HDTV 1280*720*25 type.				//SMPTE 296M
	SDVIDEOSTANDARD_HD720p_2997		= 0x00001000,	// HDTV 1280*720*29.97 type.			//SMPTE 296M
	SDVIDEOSTANDARD_HD720p_30		= 0x00000008,	// HDTV 1280*720*30 type.				//SMPTE 296M
	SDVIDEOSTANDARD_HD720p_50		= 0x00000400,	// HDTV 1280*720*50 type.				//SMPTE 296M
	SDVIDEOSTANDARD_HD720p_5994		= 0x00000800,	// HDTV 1280*720*59.94 type.			//SMPTE 296M
	SDVIDEOSTANDARD_HD720p_60		= 0x00040000,	// HDTV 1280*720*60 type.				//SMPTE 296M

	SDVIDEOSTANDARD_HD1080p_2398	= 0x00002000,	// HDTV 1920*1080*23.98 type.			//SMPTE 274M
	SDVIDEOSTANDARD_HD1080p_24		= 0x00004000,	// HDTV 1920*1080*24 type.				//SMPTE 274M
	SDVIDEOSTANDARD_HD1080p_25		= 0x00008000,	// HDTV 1920*1080*25 type.				//SMPTE 274M
	SDVIDEOSTANDARD_HD1080p_2997	= 0x00010000,	// HDTV 1920*1080*29.97 type.			//SMPTE 274M
	SDVIDEOSTANDARD_HD1080p_30		= 0x00020000,	// HDTV 1920*1080*30 type.				//SMPTE 274M
	SDVIDEOSTANDARD_HD1080P_4796	= 0x4E000000,	// HDTV 1920*1080*47.96 type.			//
	SDVIDEOSTANDARD_HD1080P_48		= 0x4F000000,	// HDTV 1920*1080*48 type.				//
	SDVIDEOSTANDARD_HD1080P_50		= 0x41000000,	// HDTV 1920*1080*50 type.				//SMPTE 274M
	SDVIDEOSTANDARD_HD1080P_5994	= 0x42000000,	// HDTV 1920*1080*59.94 type.			//SMPTE 274M
	SDVIDEOSTANDARD_HD1080P_60		= 0x43000000,	// HDTV 1920*1080*60 type.				//SMPTE 274M

	SDVIDEOSTANDARD_HD1080psf_2398	= 0x00080000,	// HDTV 1920*1080*23.98 type.			//SMPTE 274M
	SDVIDEOSTANDARD_HD1080psf_24	= 0x00100000,	// HDTV 1920*1080*24 type.				//SMPTE 274M
	SDVIDEOSTANDARD_HD1080psf_25	= 0x00200000,	// HDTV 1920*1080*25 type.				//SMPTE 274M
	SDVIDEOSTANDARD_HD1080psf_2997	= 0x00400000,	// HDTV 1920*1080*29.97 type.			//SMPTE 274M
	SDVIDEOSTANDARD_HD1080psf_30	= 0x00800000,	// HDTV 1920*1080*30 type.				//SMPTE 274M
	
	SDVIDEOSTANDARD_2K1080P_2398	= 0x45000000,	// 2K 2048*1080*23.98 type.				//AJA支持
	SDVIDEOSTANDARD_2K1080P_24		= 0x46000000,	// 2K 2048*1080*24 type.				//SMPTE 428-1
	SDVIDEOSTANDARD_2K1080P_25		= 0x22100000,	// 2K 2048*1080*25 type.				//
	SDVIDEOSTANDARD_2K1080P_2997	= 0x22200000,	// 2K 2048*1080*29.97 type.				//
	SDVIDEOSTANDARD_2K1080P_30		= 0x22300000,	// 2K 2048*1080*30 type.				//
	SDVIDEOSTANDARD_2K1080P_4796	= 0x22700000,	// 2K 2048*1080*47.96 type.				//
	SDVIDEOSTANDARD_2K1080P_48		= 0x47000000,	// 2K 2048*1080*48 type.				//SMPTE 428-1
	SDVIDEOSTANDARD_2K1080P_50		= 0x22400000,	// 2K 2048*1080*50 type.				//
	SDVIDEOSTANDARD_2K1080P_5994	= 0x22500000,	// 2K 2048*1080*59.94 type.				//
	SDVIDEOSTANDARD_2K1080P_60		= 0x22600000,	// 2K 2048*1080*60 type.				//

	SDVIDEOSTANDARD_2K1080Psf_2398	= 0x81000000,	// 2K 2048*1080*23.98 type.				//AJA支持
	SDVIDEOSTANDARD_2K1080Psf_24	= 0x82000000,	// 2K 2048*1080*24 type.				//SMPTE 428-1
	SDVIDEOSTANDARD_2K1080Psf_25	= 0x21100000,	// 2K 2048*1080*25 type.				//
	SDVIDEOSTANDARD_2K1080Psf_2997	= 0x21200000,	// 2K 2048*1080*29.97 type.				//
	SDVIDEOSTANDARD_2K1080Psf_30	= 0x21300000,	// 2K 2048*1080*30 type.				//

	SDVIDEOSTANDARD_2K1556P_2398	= 0x83000000,	// 2K 2048*1556*23.98 PLAYBACK.			//AJA支持
	SDVIDEOSTANDARD_2K1556P_24		= 0x84000000,	// 2K 2048*1556*24 PLAYBACK.			//AJA支持
	SDVIDEOSTANDARD_2K1556Psf_2398	= 0x85000000,	// 2K 2048*1556*23.98 PLAYBACK.			//AJA支持
	SDVIDEOSTANDARD_2K1556Psf_24	= 0x86000000,	// 2K 2048*1556*24 PLAYBACK.			//AJA支持

	SDVIDEOSTANDARD_4K_3840P_2398	= 0xF1100000,	// 4K 3840*2160*23.98 type.				//
	SDVIDEOSTANDARD_4K_3840P_24		= 0xF1200000,	// 4K 3840*2160*24 type.				//
	SDVIDEOSTANDARD_4K_3840P_25		= 0xF1300000,	// 4K 3840*2160*25 type.				//
	SDVIDEOSTANDARD_4K_3840P_2997	= 0xF1400000,	// 4K 3840*2160*29.97 type.				//
	SDVIDEOSTANDARD_4K_3840P_30		= 0xF1500000,	// 4K 3840*2160*30 type.				//
	SDVIDEOSTANDARD_4K_3840P_4796	= 0xF1600000,	// 4K 3840*2160*47.96 type.				//
	SDVIDEOSTANDARD_4K_3840P_48		= 0xF1700000,	// 4K 3840*2160*48 type.				//
	SDVIDEOSTANDARD_4K_3840P_50		= 0xF1800000,	// 4K 3840*2160*50 type.				//
	SDVIDEOSTANDARD_4K_3840P_5994	= 0xF1900000,	// 4K 3840*2160*59.94 type.				//
	SDVIDEOSTANDARD_4K_3840P_60		= 0xF1A00000,	// 4K 3840*2160*60 type.				//

	SDVIDEOSTANDARD_4K_3840Psf_2398	= 0xF2100000,	// 4K 3840*2160*23.98 type.				//
	SDVIDEOSTANDARD_4K_3840Psf_24	= 0xF2200000,	// 4K 3840*2160*24 type.				//
	SDVIDEOSTANDARD_4K_3840Psf_25	= 0xF2300000,	// 4K 3840*2160*25 type.				//
	SDVIDEOSTANDARD_4K_3840Psf_2997	= 0xF2400000,	// 4K 3840*2160*29.97 type.				//
	SDVIDEOSTANDARD_4K_3840Psf_30	= 0xF2500000,	// 4K 3840*2160*30 type.				//

	SDVIDEOSTANDARD_4K_4096P_2398	= 0xF3100000,	// 4K 4096*2160*23.98 type.				//
	SDVIDEOSTANDARD_4K_4096P_24		= 0xF3200000,	// 4K 4096*2160*24 type.				//
	SDVIDEOSTANDARD_4K_4096P_25		= 0xF3300000,	// 4K 4096*2160*25 type.				//
	SDVIDEOSTANDARD_4K_4096P_2997	= 0xF3400000,	// 4K 4096*2160*29.97 type.				//
	SDVIDEOSTANDARD_4K_4096P_30		= 0xF3500000,	// 4K 4096*2160*30 type.				//
	SDVIDEOSTANDARD_4K_4096P_4796	= 0xF3600000,	// 4K 4096*2160*47.96 type.				//
	SDVIDEOSTANDARD_4K_4096P_48		= 0xF3700000,	// 4K 4096*2160*48 type.				//
	SDVIDEOSTANDARD_4K_4096P_50		= 0xF3800000,	// 4K 4096*2160*50 type.				//
	SDVIDEOSTANDARD_4K_4096P_5994	= 0xF3900000,	// 4K 4096*2160*59.94 type.				//
	SDVIDEOSTANDARD_4K_4096P_60		= 0xF3A00000,	// 4K 4096*2160*60 type.				//

	SDVIDEOSTANDARD_4K_4096Psf_2398	= 0xF4100000,	// 4K 4096*2160*23.98 type.				//
	SDVIDEOSTANDARD_4K_4096Psf_24	= 0xF4200000,	// 4K 4096*2160*24 type.				//
	SDVIDEOSTANDARD_4K_4096Psf_25	= 0xF4300000,	// 4K 4096*2160*25 type.				//
	SDVIDEOSTANDARD_4K_4096Psf_2997	= 0xF4400000,	// 4K 4096*2160*29.97 type.				//
	SDVIDEOSTANDARD_4K_4096Psf_30	= 0xF4500000,	// 4K 4096*2160*30 type.				//

	SDVIDEOSTANDARD_2398_P			= 0x02000000,	// Unknow Size 23.98 P type.					
	SDVIDEOSTANDARD_2398_Psf		= 0x03000000,	// Unknow Size 23.98 Psf type.					
	SDVIDEOSTANDARD_24_P			= 0x04000000,	// Unknow Size 24 P type.						
	SDVIDEOSTANDARD_24_Psf			= 0x05000000,	// Unknow Size 24 Psf type.						
	SDVIDEOSTANDARD_25_I			= 0x08000000,	// Unknow Size 25 I type.
	SDVIDEOSTANDARD_25_P			= 0x06000000,	// Unknow Size 25 P type.						
	SDVIDEOSTANDARD_25_Psf			= 0x07000000,	// Unknow Size 25 Psf type.						
	SDVIDEOSTANDARD_2997_I			= 0x10000000,	// Unknow Size 29.97 I type.
	SDVIDEOSTANDARD_2997_P			= 0xC0000000,	// Unknow Size 29.97 P type.					
	SDVIDEOSTANDARD_2997_Psf		= 0xC1000000,	// Unknow Size 29.97 Psf type.					
	SDVIDEOSTANDARD_30_I			= 0x20000000,	// Unknow Size 30 I type.
	SDVIDEOSTANDARD_30_P			= 0xC2000000,	// Unknow Size 30 P type.						
	SDVIDEOSTANDARD_30_Psf			= 0xC3000000,	// Unknow Size 30 Psf type.						
	SDVIDEOSTANDARD_4796_P			= 0xC8000000,	// Unknow Size 48 type.					
	SDVIDEOSTANDARD_48_P			= 0xC4000000,	// Unknow Size 48 type.							
	SDVIDEOSTANDARD_50_P			= 0xC5000000,	// Unknow Size 50 type.							
	SDVIDEOSTANDARD_5994_P			= 0xC6000000,	// Unknow Size 59.94 type.						
	SDVIDEOSTANDARD_60_P			= 0xC7000000,	// Unknow Size 60 type.							

//Extend:0x|0,4,8,(C)|0,1,2,4,(3,5,6,7)|000000;
};

SD_INLINE SD_VOID	GetVideoStandardPara(SD_VIDEO_STANDARD enumVideoStandard, CSDString &strHint, SD_UINT32 &dwWidth, SD_UINT32 &dwHigh, SD_UINT32 &dwCodecHigh)
{
	strHint = _T("Unknow");
	dwWidth = dwHigh = dwCodecHigh = 0;
	
	switch(enumVideoStandard)
	{
		case SDVIDEOSTANDARD_PAL:
			strHint = _T("PAL");
			dwWidth = 720;
			dwHigh = 576;
			dwCodecHigh = 576;
			break;
		case SDVIDEOSTANDARD_NTSC2997:
			strHint = _T("NTSC");
			dwWidth = 720;
			dwHigh = 486;
			dwCodecHigh = 480;
			break;
		case SDVIDEOSTANDARD_NTSC30:
			strHint = _T("480/60i");				//NTSC-30
			dwWidth = 720;
			dwHigh = 486;
			dwCodecHigh = 480;
			break;

		case SDVIDEOSTANDARD_HD1080i_25:
			strHint = _T("1080/50i");				//HD1080-25i
			dwWidth = 1920;
			dwHigh = 1080;
			dwCodecHigh = 1088;
			break;
		case SDVIDEOSTANDARD_HD1080i_2997:
			strHint = _T("1080/59.94i");			//HD1080-29.97i
			dwWidth = 1920;
			dwHigh = 1080;
			dwCodecHigh = 1088;
			break;
		case SDVIDEOSTANDARD_HD1080i_30:
			strHint = _T("1080/60i");				//HD1080-30i
			dwWidth = 1920;
			dwHigh = 1080;
			dwCodecHigh = 1088;
			break;
		
		case SDVIDEOSTANDARD_HD720p_2398:
			strHint = _T("720/23.98P");				//HD720-23.98p
			dwWidth = 1280;
			dwHigh = 720;
			dwCodecHigh = 720;
			break;
		case SDVIDEOSTANDARD_HD720p_24:
			strHint = _T("720/24P");				//HD720-24p
			dwWidth = 1280;
			dwHigh = 720;
			dwCodecHigh = 720;
			break;
		case SDVIDEOSTANDARD_HD720p_25:
			strHint = _T("720/25P");				//HD720-25p
			dwWidth = 1280;
			dwHigh = 720;
			dwCodecHigh = 720;
			break;
		case SDVIDEOSTANDARD_HD720p_2997:
			strHint = _T("720/29.97P");				//HD720-29.97p
			dwWidth = 1280;
			dwHigh = 720;
			dwCodecHigh = 720;
			break;
		case SDVIDEOSTANDARD_HD720p_30:
			strHint = _T("720/30P");				//HD720-30p
			dwWidth = 1280;
			dwHigh = 720;
			dwCodecHigh = 720;
			break;
		case SDVIDEOSTANDARD_HD720p_50:
			strHint = _T("720/50P");				//HD720-50p
			dwWidth = 1280;
			dwHigh = 720;
			dwCodecHigh = 720;
			break;
		case SDVIDEOSTANDARD_HD720p_5994:
			strHint = _T("720/59.94P");				//HD720-59.94p
			dwWidth = 1280;
			dwHigh = 720;
			dwCodecHigh = 720;
			break;
		case SDVIDEOSTANDARD_HD720p_60:
			strHint = _T("720/60P");				//HD720-60p
			dwWidth = 1280;
			dwHigh = 720;
			dwCodecHigh = 720;
			break;

		case SDVIDEOSTANDARD_HD1080p_2398:
			strHint = _T("1080/23.98P");			//HD1080-23.98p
			dwWidth = 1920;
			dwHigh = 1080;
			dwCodecHigh = 1088;
			break;
		case SDVIDEOSTANDARD_HD1080p_24:
			strHint = _T("1080/24P");				//HD1080-24p
			dwWidth = 1920;
			dwHigh = 1080;
			dwCodecHigh = 1088;
			break;
		case SDVIDEOSTANDARD_HD1080p_25:
			strHint = _T("1080/25P");				//HD1080-25p
			dwWidth = 1920;
			dwHigh = 1080;
			dwCodecHigh = 1088;
			break;
		case SDVIDEOSTANDARD_HD1080p_2997:
			strHint = _T("1080/29.97P");			//HD1080-29.97p
			dwWidth = 1920;
			dwHigh = 1080;
			dwCodecHigh = 1088;
			break;
		case SDVIDEOSTANDARD_HD1080p_30:
			strHint = _T("1080/30P");				//HD1080-30p
			dwWidth = 1920;
			dwHigh = 1080;
			dwCodecHigh = 1088;
			break;
		case SDVIDEOSTANDARD_HD1080P_4796:
			strHint = _T("1080/47.96P");				//HD1080-47.96P
			dwWidth = 1920;
			dwHigh = 1080;
			dwCodecHigh = 1088;
			break;
		case SDVIDEOSTANDARD_HD1080P_48:
			strHint = _T("1080/48P");				//HD1080-48P
			dwWidth = 1920;
			dwHigh = 1080;
			dwCodecHigh = 1088;
			break;
		case SDVIDEOSTANDARD_HD1080P_50:
			strHint = _T("1080/50P");				//HD1080-50P
			dwWidth = 1920;
			dwHigh = 1080;
			dwCodecHigh = 1088;
			break;
		case SDVIDEOSTANDARD_HD1080P_5994:
			strHint = _T("1080/59.94P");			//HD1080-59.94P
			dwWidth = 1920;
			dwHigh = 1080;
			dwCodecHigh = 1088;
			break;
		case SDVIDEOSTANDARD_HD1080P_60:
			strHint = _T("1080/60P");				//HD1080-60P
			dwWidth = 1920;
			dwHigh = 1080;
			dwCodecHigh = 1088;
			break;

		case SDVIDEOSTANDARD_HD1080psf_2398:
			strHint = _T("1080/23.98Psf");			//HD1080-23.98Psf
			dwWidth = 1920;
			dwHigh = 1080;
			dwCodecHigh = 1088;
			break;
		case SDVIDEOSTANDARD_HD1080psf_24:
			strHint = _T("1080/24Psf");				//HD1080-24Psf
			dwWidth = 1920;
			dwHigh = 1080;
			dwCodecHigh = 1088;
			break;
		case SDVIDEOSTANDARD_HD1080psf_25:
			strHint = _T("1080/25Psf");				//HD1080-25Psf
			dwWidth = 1920;
			dwHigh = 1080;
			dwCodecHigh = 1088;
			break;
		case SDVIDEOSTANDARD_HD1080psf_2997:
			strHint = _T("1080/29.97Psf");			//HD1080-29.97Psf
			dwWidth = 1920;
			dwHigh = 1080;
			dwCodecHigh = 1088;
			break;
		case SDVIDEOSTANDARD_HD1080psf_30:
			strHint = _T("1080/30Psf");				//HD1080-30Psf
			dwWidth = 1920;
			dwHigh = 1080;
			dwCodecHigh = 1088;
			break;

		case SDVIDEOSTANDARD_2K1080P_2398:
			strHint = _T("2K2048X1080/23.98P");		//2K1080P_23.98
			dwWidth = 2048;
			dwHigh = 1080;
			dwCodecHigh = 1088;
			break;
		case SDVIDEOSTANDARD_2K1080P_24:
			strHint = _T("2K2048X1080/24P");			//2K1080P_24
			dwWidth = 2048;
			dwHigh = 1080;
			dwCodecHigh = 1088;
			break;
		case SDVIDEOSTANDARD_2K1080P_25:
			strHint = _T("2K2048X1080/25P");			//2K1080P_25
			dwWidth = 2048;
			dwHigh = 1080;
			dwCodecHigh = 1088;
			break;
		case SDVIDEOSTANDARD_2K1080P_2997:
			strHint = _T("2K2048X1080/29.97P");			//2K1080P_29.97
			dwWidth = 2048;
			dwHigh = 1080;
			dwCodecHigh = 1088;
			break;
		case SDVIDEOSTANDARD_2K1080P_30:
			strHint = _T("2K2048X1080/30P");			//2K1080P_30
			dwWidth = 2048;
			dwHigh = 1080;
			dwCodecHigh = 1088;
			break;
		case SDVIDEOSTANDARD_2K1080P_4796:
			strHint = _T("2K2048X1080/47.96P");			//2K1080P_47.96
			dwWidth = 2048;
			dwHigh = 1080;
			dwCodecHigh = 1088;
			break;
		case SDVIDEOSTANDARD_2K1080P_48:
			strHint = _T("2K2048X1080/48P");			//2K1080P_48
			dwWidth = 2048;
			dwHigh = 1080;
			dwCodecHigh = 1088;
			break;
		case SDVIDEOSTANDARD_2K1080P_50:
			strHint = _T("2K2048X1080/50P");			//2K1080P_50
			dwWidth = 2048;
			dwHigh = 1080;
			dwCodecHigh = 1088;
			break;
		case SDVIDEOSTANDARD_2K1080P_5994:
			strHint = _T("2K2048X1080/5994P");			//2K1080P_59.94
			dwWidth = 2048;
			dwHigh = 1080;
			dwCodecHigh = 1088;
			break;
		case SDVIDEOSTANDARD_2K1080P_60:
			strHint = _T("2K2048X1080/60P");			//2K1080P_60
			dwWidth = 2048;
			dwHigh = 1080;
			dwCodecHigh = 1088;
			break;

		case SDVIDEOSTANDARD_2K1080Psf_2398:
			strHint = _T("2K2048X1080/23.98Psf");		//2K1080Psf_23.98
			dwWidth = 2048;
			dwHigh = 1080;
			dwCodecHigh = 1088;
			break;
		case SDVIDEOSTANDARD_2K1080Psf_24:
			strHint = _T("2048X1080/24Psf");		//2K1080Psf_24
			dwWidth = 2048;
			dwHigh = 1080;
			dwCodecHigh = 1088;
			break;
		case SDVIDEOSTANDARD_2K1080Psf_25:
			strHint = _T("2048X1080/25Psf");		//2K1080Psf_25
			dwWidth = 2048;
			dwHigh = 1080;
			dwCodecHigh = 1088;
			break;
		case SDVIDEOSTANDARD_2K1080Psf_2997:
			strHint = _T("2048X1080/29.97Psf");		//2K1080Psf_29.97
			dwWidth = 2048;
			dwHigh = 1080;
			dwCodecHigh = 1088;
			break;
		case SDVIDEOSTANDARD_2K1080Psf_30:
			strHint = _T("2048X1080/30Psf");		//2K1080Psf_30
			dwWidth = 2048;
			dwHigh = 1080;
			dwCodecHigh = 1088;
			break;

		case SDVIDEOSTANDARD_2K1556P_2398:
			strHint = _T("2048X1556/23.98P");		//2K1556P_23.98
			dwWidth = 2048;
			dwHigh = 1556;
			dwCodecHigh = 1552;
			break;
		case SDVIDEOSTANDARD_2K1556P_24:
			strHint = _T("2048X1556/24P");			//2K1556P_24
			dwWidth = 2048;
			dwHigh = 1556;
			dwCodecHigh = 1552;
			break;
		case SDVIDEOSTANDARD_2K1556Psf_2398:
			strHint = _T("2048X1556/23.98Psf");		//2K1556Psf_23.98
			dwWidth = 2048;
			dwHigh = 1556;
			dwCodecHigh = 1552;
			break;
		case SDVIDEOSTANDARD_2K1556Psf_24:
			strHint = _T("2048X1556/24Psf");		//2K1556Psf_24
			dwWidth = 2048;
			dwHigh = 1556;
			dwCodecHigh = 1552;
			break;

		case SDVIDEOSTANDARD_4K_3840P_2398:
			strHint = _T("4K3840X2160/23.98P");			//4K3840X2160-23.98P
			dwWidth = 3840;
			dwHigh = 2160;
			dwCodecHigh = 2160;
			break;
		case SDVIDEOSTANDARD_4K_3840P_24:
			strHint = _T("4K3840X2160/24P");			//4K3840X2160-24P
			dwWidth = 3840;
			dwHigh = 2160;
			dwCodecHigh = 2160;
			break;
		case SDVIDEOSTANDARD_4K_3840P_25:
			strHint = _T("4K3840X2160/25P");			//4K3840X2160-25P
			dwWidth = 3840;
			dwHigh = 2160;
			dwCodecHigh = 2160;
			break;
		case SDVIDEOSTANDARD_4K_3840P_2997:
			strHint = _T("4K3840X2160/29.97P");			//4K3840X2160-29.97P
			dwWidth = 3840;
			dwHigh = 2160;
			dwCodecHigh = 2160;
			break;
		case SDVIDEOSTANDARD_4K_3840P_30:
			strHint = _T("4K3840X2160/30P");			//4K3840X2160-30P
			dwWidth = 3840;
			dwHigh = 2160;
			dwCodecHigh = 2160;
			break;
		case SDVIDEOSTANDARD_4K_3840P_4796:
			strHint = _T("4K3840X2160/47.96P");			//4K3840X2160-47.96P
			dwWidth = 3840;
			dwHigh = 2160;
			dwCodecHigh = 2160;
			break;
		case SDVIDEOSTANDARD_4K_3840P_48:
			strHint = _T("4K3840X2160/48P");			//4K3840X2160-48P
			dwWidth = 3840;
			dwHigh = 2160;
			dwCodecHigh = 2160;
			break;
		case SDVIDEOSTANDARD_4K_3840P_50:
			strHint = _T("4K3840X2160/50P");			//4K3840X2160-50P
			dwWidth = 3840;
			dwHigh = 2160;
			dwCodecHigh = 2160;
			break;
		case SDVIDEOSTANDARD_4K_3840P_5994:
			strHint = _T("4K3840X2160/59.94P");			//4K3840X2160-59.94P
			dwWidth = 3840;
			dwHigh = 2160;
			dwCodecHigh = 2160;
			break;
		case SDVIDEOSTANDARD_4K_3840P_60:
			strHint = _T("4K3840X2160/60P");			//4K3840X2160-60P
			dwWidth = 3840;
			dwHigh = 2160;
			dwCodecHigh = 2160;
			break;

		case SDVIDEOSTANDARD_4K_3840Psf_2398:
			strHint = _T("4K3840X2160/23.98Psf");			//4K3840X2160-23.98Psf
			dwWidth = 3840;
			dwHigh = 2160;
			dwCodecHigh = 2160;
			break;
		case SDVIDEOSTANDARD_4K_3840Psf_24:
			strHint = _T("4K3840X2160/24Psf");			//4K3840X2160-24Psf
			dwWidth = 3840;
			dwHigh = 2160;
			dwCodecHigh = 2160;
			break;
		case SDVIDEOSTANDARD_4K_3840Psf_25:
			strHint = _T("4K3840X2160/25Psf");			//4K3840X2160-25Psf
			dwWidth = 3840;
			dwHigh = 2160;
			dwCodecHigh = 2160;
			break;
		case SDVIDEOSTANDARD_4K_3840Psf_2997:
			strHint = _T("4K3840X2160/29.97Psf");			//4K3840X2160-29.97Psf
			dwWidth = 3840;
			dwHigh = 2160;
			dwCodecHigh = 2160;
			break;
		case SDVIDEOSTANDARD_4K_3840Psf_30:
			strHint = _T("4K3840X2160/30Psf");			//4K3840X2160-30Psf
			dwWidth = 3840;
			dwHigh = 2160;
			dwCodecHigh = 2160;
			break;

		case SDVIDEOSTANDARD_4K_4096P_2398:
			strHint = _T("4K4096X2160/23.98P");				//4K4096X2160-23.98P
			dwWidth = 4096;
			dwHigh = 2160;
			dwCodecHigh = 2160;
			break;
		case SDVIDEOSTANDARD_4K_4096P_24:
			strHint = _T("4K4096X2160/24P");				//4K4096X2160-24P
			dwWidth = 4096;
			dwHigh = 2160;
			dwCodecHigh = 2160;
			break;
		case SDVIDEOSTANDARD_4K_4096P_25:
			strHint = _T("4K4096X2160/25P");				//4K4096X2160-25P
			dwWidth = 4096;
			dwHigh = 2160;
			dwCodecHigh = 2160;
			break;
		case SDVIDEOSTANDARD_4K_4096P_2997:
			strHint = _T("4K4096X2160/29.97P");				//4K4096X2160-29.97P
			dwWidth = 4096;
			dwHigh = 2160;
			dwCodecHigh = 2160;
			break;
		case SDVIDEOSTANDARD_4K_4096P_30:
			strHint = _T("4K4096X2160/30P");				//4K4096X2160-30P
			dwWidth = 4096;
			dwHigh = 2160;
			dwCodecHigh = 2160;
			break;
		case SDVIDEOSTANDARD_4K_4096P_4796:
			strHint = _T("4K4096X2160/47.96P");				//4K4096X2160-47.96P
			dwWidth = 4096;
			dwHigh = 2160;
			dwCodecHigh = 2160;
			break;
		case SDVIDEOSTANDARD_4K_4096P_48:
			strHint = _T("4K4096X2160/48P");				//4K4096X2160-48P
			dwWidth = 4096;
			dwHigh = 2160;
			dwCodecHigh = 2160;
			break;
		case SDVIDEOSTANDARD_4K_4096P_50:
			strHint = _T("4K4096X2160/50P");				//4K4096X2160-50P
			dwWidth = 4096;
			dwHigh = 2160;
			dwCodecHigh = 2160;
			break;
		case SDVIDEOSTANDARD_4K_4096P_5994:
			strHint = _T("4K4096X2160/59.94P");				//4K4096X2160-59.94P
			dwWidth = 4096;
			dwHigh = 2160;
			dwCodecHigh = 2160;
			break;
		case SDVIDEOSTANDARD_4K_4096P_60:
			strHint = _T("4K4096X2160/60P");				//4K4096X2160-60P
			dwWidth = 4096;
			dwHigh = 2160;
			dwCodecHigh = 2160;
			break;

		case SDVIDEOSTANDARD_4K_4096Psf_2398:
			strHint = _T("4K4096X2160/23.98Psf");			//4K4096X2160-23.98Psf
			dwWidth = 4096;
			dwHigh = 2160;
			dwCodecHigh = 2160;
			break;
		case SDVIDEOSTANDARD_4K_4096Psf_24:
			strHint = _T("4K4096X2160/24Psf");				//4K4096X2160-24Psf
			dwWidth = 4096;
			dwHigh = 2160;
			dwCodecHigh = 2160;
			break;
		case SDVIDEOSTANDARD_4K_4096Psf_25:
			strHint = _T("4K4096X2160/25Psf");				//4K4096X2160-25Psf
			dwWidth = 4096;
			dwHigh = 2160;
			dwCodecHigh = 2160;
			break;
		case SDVIDEOSTANDARD_4K_4096Psf_2997:
			strHint = _T("4K4096X2160/29.97Psf");			//4K4096X2160-29.97Psf
			dwWidth = 4096;
			dwHigh = 2160;
			dwCodecHigh = 2160;
			break;
		case SDVIDEOSTANDARD_4K_4096Psf_30:
			strHint = _T("4K4096X2160/30Psf");			//4K4096X2160-30Psf
			dwWidth = 4096;
			dwHigh = 2160;
			dwCodecHigh = 2160;
			break;

		case SDVIDEOSTANDARD_2398_P:
			strHint = _T("***/23.98P");				//Unknow-23.98
			break;
		case SDVIDEOSTANDARD_2398_Psf:
			strHint = _T("***/23.98Psf");
			break;
		case SDVIDEOSTANDARD_24_P:
			strHint = _T("***/24P");				//Unknow-24
			break;
		case SDVIDEOSTANDARD_24_Psf:
			strHint = _T("***/24Psf");
			break;
		case SDVIDEOSTANDARD_25_I:
			strHint = _T("***/25I");				//Unknow-25
			break;
		case SDVIDEOSTANDARD_25_P:
			strHint = _T("***/25P");
			break;
		case SDVIDEOSTANDARD_25_Psf:
			strHint = _T("***/25Psf");
			break;
		case SDVIDEOSTANDARD_2997_I:
			strHint = _T("***/29.97I");				//Unknow-29.97
			break;
		case SDVIDEOSTANDARD_2997_P:
			strHint = _T("***/29.97P");
			break;
		case SDVIDEOSTANDARD_2997_Psf:
			strHint = _T("***/29.97Psf");
			break;
		case SDVIDEOSTANDARD_30_I:
			strHint = _T("***/30I");				//Unknow-30
			break;
		case SDVIDEOSTANDARD_30_P:
			strHint = _T("***/30P");
			break;
		case SDVIDEOSTANDARD_30_Psf:
			strHint = _T("***/30Psf");
			break;
		case SDVIDEOSTANDARD_4796_P:
			strHint = _T("***/47.96P");				//Unknow-47.96
			break;
		case SDVIDEOSTANDARD_48_P:
			strHint = _T("***/48P");				//Unknow-48
			break;
		case SDVIDEOSTANDARD_50_P:
			strHint = _T("***/50P");				//Unknow-50
			break;
		case SDVIDEOSTANDARD_5994_P:
			strHint = _T("***/59.94P");				//Unknow-59.94
			break;
		case SDVIDEOSTANDARD_60_P:
			strHint = _T("***/60P");				//Unknow-60
			break;
	}
};


SD_INLINE	SD_VOID	_GetStandardRateScale(SD_VIDEO_STANDARD enumVideoStandard, SD_UINT32 &dwRate, SD_UINT32 &dwScale)
{
	switch(enumVideoStandard) 
	{
		case SDVIDEOSTANDARD_HD720p_2398:
		case SDVIDEOSTANDARD_HD1080p_2398:
		case SDVIDEOSTANDARD_HD1080psf_2398:
		case SDVIDEOSTANDARD_2K1080P_2398:
		case SDVIDEOSTANDARD_2K1080Psf_2398:
		case SDVIDEOSTANDARD_2K1556P_2398:
		case SDVIDEOSTANDARD_2K1556Psf_2398:
		case SDVIDEOSTANDARD_4K_3840P_2398:
		case SDVIDEOSTANDARD_4K_3840Psf_2398:
		case SDVIDEOSTANDARD_4K_4096P_2398:
		case SDVIDEOSTANDARD_4K_4096Psf_2398:
		case SDVIDEOSTANDARD_2398_P:
		case SDVIDEOSTANDARD_2398_Psf:
			dwRate = 24000;
			dwScale = 1001;
			break;
		case SDVIDEOSTANDARD_HD720p_24:
		case SDVIDEOSTANDARD_HD1080p_24:
		case SDVIDEOSTANDARD_HD1080psf_24:
		case SDVIDEOSTANDARD_2K1080P_24:
		case SDVIDEOSTANDARD_2K1080Psf_24:
		case SDVIDEOSTANDARD_2K1556P_24:
		case SDVIDEOSTANDARD_2K1556Psf_24:
		case SDVIDEOSTANDARD_4K_3840P_24:
		case SDVIDEOSTANDARD_4K_3840Psf_24:
		case SDVIDEOSTANDARD_4K_4096P_24:
		case SDVIDEOSTANDARD_4K_4096Psf_24:
		case SDVIDEOSTANDARD_24_P:
		case SDVIDEOSTANDARD_24_Psf:
			dwRate = 24;
			dwScale = 1;
			break;
		case SDVIDEOSTANDARD_PAL:
		case SDVIDEOSTANDARD_HD1080i_25:
		case SDVIDEOSTANDARD_HD720p_25:
		case SDVIDEOSTANDARD_HD1080p_25:
		case SDVIDEOSTANDARD_HD1080psf_25:
		case SDVIDEOSTANDARD_2K1080P_25:
		case SDVIDEOSTANDARD_2K1080Psf_25:
		case SDVIDEOSTANDARD_4K_3840P_25:
		case SDVIDEOSTANDARD_4K_3840Psf_25:
		case SDVIDEOSTANDARD_4K_4096P_25:
		case SDVIDEOSTANDARD_4K_4096Psf_25:
		case SDVIDEOSTANDARD_25_I:
		case SDVIDEOSTANDARD_25_P:
		case SDVIDEOSTANDARD_25_Psf:
			dwRate = 25;
			dwScale = 1;
			break;
		case SDVIDEOSTANDARD_NTSC2997:
		case SDVIDEOSTANDARD_HD1080i_2997:
		case SDVIDEOSTANDARD_HD720p_2997:
		case SDVIDEOSTANDARD_HD1080p_2997:
		case SDVIDEOSTANDARD_HD1080psf_2997:
		case SDVIDEOSTANDARD_2K1080P_2997:
		case SDVIDEOSTANDARD_2K1080Psf_2997:
		case SDVIDEOSTANDARD_4K_3840P_2997:
		case SDVIDEOSTANDARD_4K_3840Psf_2997:
		case SDVIDEOSTANDARD_4K_4096P_2997:
		case SDVIDEOSTANDARD_4K_4096Psf_2997:
		case SDVIDEOSTANDARD_2997_I:
		case SDVIDEOSTANDARD_2997_P:
		case SDVIDEOSTANDARD_2997_Psf:
			dwRate = 30000;
			dwScale = 1001;
			break;
		case SDVIDEOSTANDARD_NTSC30:
		case SDVIDEOSTANDARD_HD1080i_30:
		case SDVIDEOSTANDARD_HD720p_30:
		case SDVIDEOSTANDARD_HD1080p_30:
		case SDVIDEOSTANDARD_HD1080psf_30:
		case SDVIDEOSTANDARD_2K1080P_30:
		case SDVIDEOSTANDARD_2K1080Psf_30:
		case SDVIDEOSTANDARD_4K_3840P_30:
		case SDVIDEOSTANDARD_4K_3840Psf_30:
		case SDVIDEOSTANDARD_4K_4096P_30:
		case SDVIDEOSTANDARD_4K_4096Psf_30:
		case SDVIDEOSTANDARD_30_I:
		case SDVIDEOSTANDARD_30_P:
		case SDVIDEOSTANDARD_30_Psf:
			dwRate = 30;
			dwScale = 1;
			break;
		case SDVIDEOSTANDARD_HD1080P_4796:
		case SDVIDEOSTANDARD_2K1080P_4796:
		case SDVIDEOSTANDARD_4K_3840P_4796:
		case SDVIDEOSTANDARD_4K_4096P_4796:
		case SDVIDEOSTANDARD_4796_P:
			dwRate = 48000;
			dwScale = 1001;
			break;
		case SDVIDEOSTANDARD_HD1080P_48:
		case SDVIDEOSTANDARD_2K1080P_48:
		case SDVIDEOSTANDARD_4K_3840P_48:
		case SDVIDEOSTANDARD_4K_4096P_48:
		case SDVIDEOSTANDARD_48_P:
			dwRate = 48;
			dwScale = 1;
			break;
		case SDVIDEOSTANDARD_HD720p_50:
		case SDVIDEOSTANDARD_HD1080P_50:
		case SDVIDEOSTANDARD_2K1080P_50:
		case SDVIDEOSTANDARD_4K_3840P_50:
		case SDVIDEOSTANDARD_4K_4096P_50:
		case SDVIDEOSTANDARD_50_P:
			dwRate = 50;
			dwScale = 1;
			break;
		case SDVIDEOSTANDARD_HD720p_5994:
		case SDVIDEOSTANDARD_HD1080P_5994:
		case SDVIDEOSTANDARD_2K1080P_5994:
		case SDVIDEOSTANDARD_4K_3840P_5994:
		case SDVIDEOSTANDARD_4K_4096P_5994:
		case SDVIDEOSTANDARD_5994_P:
			dwRate = 60000;
			dwScale = 1001;
			break;
		case SDVIDEOSTANDARD_HD720p_60:
		case SDVIDEOSTANDARD_HD1080P_60:
		case SDVIDEOSTANDARD_2K1080P_60:
		case SDVIDEOSTANDARD_4K_3840P_60:
		case SDVIDEOSTANDARD_4K_4096P_60:
		case SDVIDEOSTANDARD_60_P:
			dwRate = 60;
			dwScale = 1;
			break;
		default:
			dwRate = 0;
			dwScale = 1;
			break;
	}
};

enum SD_VIDEO_TYPE		// 视频编码格式类型
{
	SDVIDEOTYPE_UNKNOW					= 0x00000000,	// 无效类型

	SDVIDEOTYPE_MJPEG_FIELD				= 0x00000001,	// MJPEG 场压缩方式
	SDVIDEOTYPE_MJPEG_FRAME				= 0x00000002,	// MJPEG 帧压缩方式
	SDVIDEOTYPE_MJPEG_LOSSLESS_FIELD	= 0x00000400,	// MJPEG 无损场压缩方式
	SDVIDEOTYPE_MJPEG_LOSSLESS_FRAME	= 0x00000800,	// MJPEG 无损帧压缩方式

	SDVIDEOTYPE_MPEG1					= 0x00000100,	// MPEG1 编码
	SDVIDEOTYPE_MPEG2_IFRAME			= 0x00000004,	// MPEG2 I帧压缩方式
	SDVIDEOTYPE_MPEG2_IBP				= 0x00000008,	// MPEG2 IBP帧压缩方式。
	SDVIDEOTYPE_MPEG2_D10				= 0x00000010,	// Mpeg2 D10 编码格式, Special Mpeg2 I
	SDVIDEOTYPE_MPEG2_HDV			    = 0x02000000,	// Mpeg2 HDV 编码格式, Special Mpeg2 IBP
	SDVIDEOTYPE_MPEG4					= 0x00000200,	// MPEG4 编码

	SDVIDEOTYPE_DV25					= 0x00000020,	// DV25编码格式 
	SDVIDEOTYPE_DV50					= 0x00000040,	// DV50编码格式
	SDVIDEOTYPE_DVSD					= 0x00000080,	// DVSD编码格式
	SDVIDEOTYPE_DVHD					= 0x00040000,	// DVC PRO HD 100M 压缩方式

	SDVIDEOTYPE_YUV_UNCOMPRESS			= 0x00001000,	// YUV or TYUV 非压缩方式
	SDVIDEOTYPE_RGB_UNCOMPRESS			= 0x00002000,	// RGB or ARGB 非压缩方式
	SDVIDEOTYPE_ZAXEL_LOSSLESS			= 0x00100000,	// Zaxtar 无损编码压缩方式

	SDVIDEOTYPE_REAL_MEDIA				= 0x00004000,	// real media(rm)格式
	SDVIDEOTYPE_WINDOWS_MEDIA			= 0x00008000,	// window media(wm)格式
	SDVIDEOTYPE_QUICKTIME_MOV			= 0x00010000,	// quicktime 格式
	SDVIDEOTYPE_VCM_COMPRESSED			= 0x00020000,	// video compression manager (VCM)压缩格式。

	SDVIDEOTYPE_AVS	             		= 0x00200000,	// AVS压缩格式
	SDVIDEOTYPE_H263             		= 0x00400000,	// H263压缩格式
	SDVIDEOTYPE_H264             		= 0x00800000,	// H264压缩格式
	SDVIDEOTYPE_H265             		= 0x40000000,	// H265压缩格式
	SDVIDEOTYPE_AVCINTRA_HD				= 0x04000000,	// P2 AVC Intra的压缩格式
	SDVIDEOTYPE_AVID_DNXHD			    = 0x08000000,	// AVID DNXHD的压缩格式
	SDVIDEOTYPE_MJ2K					= 0x01000000,	// MJPEG2000压缩格式
	SDVIDEOTYPE_PRORES422				= 0x10000000,	// Apple ProRes 422 压缩方式
	
	SDVIDEOTYPE_SWFFLV_TYPE				= 0x00080000,	// FLV 文件格式能包括的压缩格式
	SDVIDEOTYPE_DPX						= 0x00080001,	// DPX 文件的视频格式
	SDVIDEOTYPE_REDCODE					= 0x00080002,	// Red one的REDCODE格式
	SDVIDEOTYPE_AVCULTRA_LONGGOP		= 0x00080003,	// P2 AVC Ultra的压缩格式
														// SONY XAVC压缩格式
	SDVIDEOTYPE_XAVC_HD			        = 0x00080004,   //SONY XAVC HD Profile
	SDVIDEOTYPE_XAVC_4K                 = 0x00080005,   //SONY XAVC 4K Profile
	SDVIDEOTYPE_XAVC_HD_INTRA           = 0x00080006,   //SONY XAVC HD Intra Profile
	SDVIDEOTYPE_XAVC_4K_INTRA           = 0x00080007,   //SONY XAVC 4K Intra Profile
	SDVIDEOTYPE_XAVC_HD444_INTRA        = 0x00080008,   //SONY XAVC HD444 Intra Profile
	SDVIDEOTYPE_XAVC_4K444_INTRA        = 0x00080009,   //SONY XAVC 4K444 Intra Profile 
	SDVIDEOTYPE_SONY_RAW				= 0x0008000A,	// SONY RAW压缩格式
	SDVIDEOTYPE_MPEG4_SSTP				= 0x0008000B,	// SONY SONY MPEG-4 Simple Studio Profile Level 2
	
	SDVIDEOTYPE_GIA						= 0x20000000,	// EasyCode定义---Graphics Image of ALPHA
	SDVIDEOTYPE_LOSSLESS           		= 0x80000000,	// EasyCode无损压缩格式

	SDVIDEOTYPE_H264_INTEL				= 0x00000011,	// H264压缩格式intel编码器
};

enum SD_AUDIO_TYPE	// 音频编解码格式类型
{
	SDAUDIOTYPE_UNKNOW				= 0x00000000,       // @emem  unknow type.
	
	SDAUDIOTYPE_WAVE_PCM			= 0x00000001,		// WAVE PCM 音频压缩方式
	SDAUDIOTYPE_WAVE_PCM_32			= 0x00000011,		// WAVE PCM 音频压缩方式

	SDAUDIOTYPE_MP1					= 0x00000004,		// MPEG1 音频 (Layer 1) 压缩方式
	SDAUDIOTYPE_MP2					= 0x00000008,		// MPEG1 音频 (Layer 2) 压缩方式
	SDAUDIOTYPE_MP3					= 0x00000010,		// MPEG1 音频 (Layer 3) 压缩方式	
	SDAUDIOTYPE_MPEG4				= 0x00000002,		// MPEG4 (ACM) 音频压缩WAVE
	
	SDAUDIOTYPE_AAC					= 0x00000020,		// AAC 压缩方式。
	SDAUDIOTYPE_AC3					= 0x00000040,		// Dolby Digital (AC3) 音频压缩方式
	SDAUDIOTYPE_DTS					= 0x00000080,		// DTS 音频压缩方式
	SDAUDIOTYPE_DRA					= 0x00080000,		// DRA Audio
	SDAUDIOTYPE_AVS	            	= 0x00000800,		// AVS音频压缩方式
	SDAUDIOTYPE_DolbyE				= 0x00001000,		// Dolby-E 音频压缩方式
	SDAUDIOTYPE_EAC3				= 0x00002000,		// Dolby Digital Plus (EAC3) 音频压缩方式

	SDAUDIOTYPE_REAL_MEDIA			= 0x00000100,		// Real media 音频压缩方式
	SDAUDIOTYPE_WINDOWS_MEDIA		= 0x00000200,		// Windows media 音频压缩方式
	SDAUDIOTYPE_QUICKTIME_MOV		= 0x00000400,		// Quicktime 音频压缩方式

	SDAUDIOTYPE_G711				= 0x00004000,		// ITUT的语音压缩标准,分ALaw和ULaw两种模式
	SDAUDIOTYPE_AMRNB				= 0x00010000,		// AMR-NB for 3GPP or GSM
	SDAUDIOTYPE_AMRWB				= 0x00020000,		// AMR-NB for 3GPP only
	SDAUDIOTYPE_SWFFLV				= 0x00040000,		// Flv Audio
	SDAUDIOTYPE_ACM_COMPRESSED		= 0x01000000,		// Audio compression manager (ACM)压缩格式。
		
	SDAUDIOTYPE_SDDEF1				= 0x10000000,		// EasyCode自定义1
	SDAUDIOTYPE_SDDEF2				= 0x20000000,		// EasyCode自定义2
	SDAUDIOTYPE_SDDEF3				= 0x40000000,		// EasyCode自定义3
	SDAUDIOTYPE_SDDEF4				= 0x80000000,		// EasyCode自定义4
};

enum SD_COLOR_FORMAT		// 视频颜色格式
{
	SDCOLORFORMAT_UNKNOW			=	0x00000000,		// invalid color format.

	SDCOLORFORMAT_BGRA				=	0x00000001,		//BGRA4444,	8bit,	0xAARRGGBB...4个字节排列1个α通道分量A、1个R分量、1个G分量、1个B分量
	SDCOLORFORMAT_BGRA_SD10b		=	0x00002000,		//BGRA4444,	10bit,	3×1个图像像素, 详细定义见专门文档!
	SDCOLORFORMAT_BGRA_SD16b		=	0x00008000,		//BGRA4444,	16bit,	0xAAAARRRRGGGGBBBB...8个字节排列1个α通道分量A、1个R分量、1个G分量、1个B分量
	SDCOLORFORMAT_BGR				=	0x00000004,		//BGR444,	8bit,	0xRRGGBB...3个字节排列1个R分量、1个G分量、1个B分量
	SDCOLORFORMAT_BGR_SD10b			=	0x00004000,		//BGR444,	10bit,	4×1个图像像素, Method A Little Endian(暂时保留,与SDCOLORFORMAT_BGR_SD10b_Ma_LE一样)
	SDCOLORFORMAT_BGR_SD10b_Ma_LE	=	0x00004000,		//BGR444,	10bit,	4×1个图像像素, Method A Little Endian
	SDCOLORFORMAT_BGR_SD10b_Ma_BE	=	0x00004001,		//BGR444,	10bit,	4×1个图像像素, Method A Big Endian
	SDCOLORFORMAT_BGR_SD10b_Mb_LE	=	0x00004002,		//BGR444,	10bit,	4×1个图像像素, Method B Little Endian
	SDCOLORFORMAT_BGR_SD10b_Mb_BE	=	0x00004003,		//BGR444,	10bit,	4×1个图像像素, Method B Big Endian
	SDCOLORFORMAT_BGR_SD16b			=	0x00200000,		//BGR444,	16bit,	0xRRRRGGGGBBBB...6个字节排列1个R分量、1个G分量、1个B分量

	SDCOLORFORMAT_VUYT				=	0x00000020,		//VUYT4444,	8bit,	0xTTYYUUVV...4个字节排列1个T分量、1个Y分量、1个U分量和1个V分量
	SDCOLORFORMAT_VUYT_SD10b		=	0x00400000,		//VUYT4444,	10bit,	3×1个图像像素, 详细定义见专门文档!
	SDCOLORFORMAT_VUYT_SD16b		=	0x04000000,		//VUYT4444,	16bit,	0xTTTTYYYYUUUUVVVV...8个字节排列1个T分量、1个Y分量、1个U分量和1个V分量
	SDCOLORFORMAT_VUY				=	0x02000000,		//VUY444,	8bit,	0xYYUUVV...3个字节排列1个Y分量、1个U分量和1个V分量
	SDCOLORFORMAT_VUY_SD10b			=	0x08000000,		//VUY444,	10bit,	4×1个图像像素, 详细定义见专门文档!
	SDCOLORFORMAT_VUY_SD16b			=	0x10000000,		//VUY444,	16bit,	0xYYYYUUUUVVVV...6个字节排列1个Y分量、1个U分量和1个V分量

	SDCOLORFORMAT_YUYV				=	0x00000040,		//YUYV422,	8bit,	0xVVYYUUYY...4个字节排列排列2个图像像素的Y、U、V分量
	SDCOLORFORMAT_UYVY				=	0x00000080,		//UYVY422,	8bit,	0xYYVVYYUU...4个字节排列排列2个图像像素的Y、U、V分量
	SDCOLORFORMAT_YUYV_V210			=	0x00040000,		//YUYV422,	10bit,	Apple定义的采样格式, 详细定义见专门文档!
	SDCOLORFORMAT_YUYV_V216			=	0x00020000,		//YUYV422,	16bit,	Apple定义的采样格式, 详细定义见专门文档!
	SDCOLORFORMAT_YUYV_M101			=	0x00080000,		//YUYV422,	8bit,	Matrox定义的采样格式, 详细定义见专门文档!
	SDCOLORFORMAT_YUYV_M101_10BIT	=	0x00100000,		//YUYV422,	10bit,	Matrox定义的采样格式, 详细定义见专门文档!
	SDCOLORFORMAT_YUAYVA4224		=	0x00800000,		//YUAYVA4224,8bit,	Matrox定义的8bit带阿尔法通道的颜色格式, 以YUYV为基础，每8个像素为一个单元，详细定义见专门文档!
	SDCOLORFORMAT_YUYV_DNXHD_10BIT	=	0x00001000,		//YUYV422,	10bit,	AVID定义的采样格式, 详细定义见专门文档!

	SDCOLORFORMAT_YUVP_444			=	0x00000100,		//YUVP444,	8bit,	1个图像像素占3个字节,Y、U、V分量分别保存在三块缓存区中, 详细定义见专门文档!
	SDCOLORFORMAT_YUVP_422			=	0x00000200,		//YUVP422,	8bit,	2x1宏像素占4个字节,Y、U、V分量分别保存在三块缓存区中, 详细定义见专门文档!
	SDCOLORFORMAT_YUVP_420			=	0x00000400,		//YUVP420,	8bit,	2x2宏像素占6个字节,Y、U、V分量分别保存在三块缓存区中, 详细定义见专门文档!
	SDCOLORFORMAT_YUVP_411			=	0x00000800,		//YUVP411,	8bit,	4x1宏像素占6个字节,Y、U、V分量分别保存在三块缓存区中, 详细定义见专门文档!	
	SDCOLORFORMAT_YUV_J420P			=	0x20000001,

	SDCOLORFORMAT_SDDEF_20000000	=	0x20000000,
	SDCOLORFORMAT_SDDEF_40000000	=	0x40000000,
	SDCOLORFORMAT_SDDEF_80000000	=	0x80000000,
	SDCOLORFORMAT_SDDEF_00000001	=	0x00000008,
	SDCOLORFORMAT_SDDEF_00000002	=	0x00000002,
	SDCOLORFORMAT_SDDEF_00000010	=	0x00000010,
	SDCOLORFORMAT_SDDEF_01000000	=	0x01000000,
	SDCOLORFORMAT_SDDEF_00010000	=	0x00010000,
	SDCOLORFORMAT_INTEL				=	0x00000011,
};

//得到视频颜色格式类型的名称
SD_INLINE CSDString GetColorFormatHint(SD_COLOR_FORMAT enumColorFormat)
{
	CSDString strColorFormat = _T("Unknow");

	switch(enumColorFormat)
	{
		case SDCOLORFORMAT_BGRA:
			strColorFormat = _T("BGRA");	
			break;
		case SDCOLORFORMAT_BGRA_SD10b:
			strColorFormat = _T("BGRA_SD10b");	
			break;
		case SDCOLORFORMAT_BGRA_SD16b:
			strColorFormat = _T("BGRA_SD16b");	
			break;
		case SDCOLORFORMAT_BGR:
			strColorFormat = _T("BGR");	
			break;
		case SDCOLORFORMAT_BGR_SD10b:
			strColorFormat = _T("BGR_SD10b");	
			break;
		case SDCOLORFORMAT_BGR_SD10b_Ma_BE:
			strColorFormat = _T("BGR_SD10b_Ma_BE");	
			break;
		case SDCOLORFORMAT_BGR_SD10b_Mb_LE:
			strColorFormat = _T("BGR_SD10b_Mb_LE");	
			break;
		case SDCOLORFORMAT_BGR_SD10b_Mb_BE:
			strColorFormat = _T("BGR_SD10b_Mb_BE");	
			break;
		case SDCOLORFORMAT_BGR_SD16b:
			strColorFormat = _T("BGR_SD16b");	
			break;
		case SDCOLORFORMAT_VUYT:
			strColorFormat = _T("VUYT");	
			break;
		case SDCOLORFORMAT_VUYT_SD10b:
			strColorFormat = _T("VUYT_SD10b");	
			break;
		case SDCOLORFORMAT_VUYT_SD16b:
			strColorFormat = _T("VUYT_SD16b");	
			break;
		case SDCOLORFORMAT_VUY:
			strColorFormat = _T("VUY");	
			break;
		case SDCOLORFORMAT_VUY_SD10b:
			strColorFormat = _T("VUY_SD10b");	
			break;
		case SDCOLORFORMAT_VUY_SD16b:
			strColorFormat = _T("VUY_SD16b");	
			break;

		case SDCOLORFORMAT_YUYV:
			strColorFormat = _T("YUYV");	
			break;
		case SDCOLORFORMAT_UYVY:
			strColorFormat = _T("UYVY");	
			break;
		case SDCOLORFORMAT_YUYV_V210:
			strColorFormat = _T("YUYV_V210");	
			break;
		case SDCOLORFORMAT_YUYV_V216:
			strColorFormat = _T("YUYV_V216");	
			break;
		case SDCOLORFORMAT_YUYV_M101:
			strColorFormat = _T("YUYV_M101");	
			break;
		case SDCOLORFORMAT_YUYV_M101_10BIT:
			strColorFormat = _T("YUYV_M101_10BIT");	
			break;
		case SDCOLORFORMAT_YUAYVA4224:
			strColorFormat = _T("YUAYVA4224");	
			break;
		case SDCOLORFORMAT_YUYV_DNXHD_10BIT:
			strColorFormat = _T("YUYV_DNXHD_10BIT");	
			break;

		case SDCOLORFORMAT_YUVP_444:
			strColorFormat = _T("YUVP_444");	
			break;
		case SDCOLORFORMAT_YUVP_422:
			strColorFormat = _T("YUVP_422");	
			break;
		case SDCOLORFORMAT_YUVP_420:
			strColorFormat = _T("YUVP_420");	
			break;
		case SDCOLORFORMAT_YUVP_411:
			strColorFormat = _T("YUVP_411");	
			break;
	}
	return strColorFormat;
};

//依据视频颜色格式和像素点数目得到视频数据块的大小
SD_INLINE	SD_UINT32	GetColorFormatBufSizeInByte(SD_COLOR_FORMAT enumColorFormat, SD_UINT32 dwWidth, SD_UINT32 dwHeight, SD_UINT32 *pdwXScanByteSize=SD_NULL)
{
	if (pdwXScanByteSize && (*pdwXScanByteSize) != 0)
		return (*pdwXScanByteSize)*dwHeight;

	SD_UINT32	dwBufByteSize = 0;
	SD_UINT32	dwXScanByteSize = 0;

	switch(enumColorFormat)
	{
		case SDCOLORFORMAT_BGRA:
		case SDCOLORFORMAT_VUYT:
			dwXScanByteSize = 4*dwWidth;
			dwBufByteSize = dwXScanByteSize*dwHeight;
			break;
		case SDCOLORFORMAT_BGR:
		case SDCOLORFORMAT_VUY:
			dwXScanByteSize = 3*dwWidth;
			dwBufByteSize = dwXScanByteSize*dwHeight;
			break;

		case SDCOLORFORMAT_BGRA_SD10b:
		case SDCOLORFORMAT_VUYT_SD10b:
			if ((dwWidth%3) != 0)				// 其宏像素由3×1个图像像素组成，在缓存中占4个32位little-endian字节序双字（DWord）
				dwWidth = (dwWidth/3+1)*3;
			if (((dwWidth*16/3)%128) != 0)
				dwXScanByteSize = ((dwWidth*16/3)/128+1)*128;
			else
				dwXScanByteSize = dwWidth*16/3;
			dwBufByteSize = dwXScanByteSize*dwHeight;
			break;
		case SDCOLORFORMAT_BGR_SD10b:
		case SDCOLORFORMAT_VUY_SD10b:
			if ((dwWidth%4) != 0)				// 其宏像素由4×1个图像像素组成，在缓存中占4个32位little-endian字节序双字（DWord）
				dwWidth = (dwWidth/4+1)*3;
			if (((dwWidth*16/4)%128) != 0)
				dwXScanByteSize = ((dwWidth*16/4)/128+1)*128;
			else
				dwXScanByteSize = dwWidth*16/4;
			dwBufByteSize = dwXScanByteSize*dwHeight;
			break;
		case SDCOLORFORMAT_BGRA_SD16b:
		case SDCOLORFORMAT_VUYT_SD16b:
			dwXScanByteSize = dwWidth*8;		// 1个像素占8字节
			dwBufByteSize = dwXScanByteSize*dwHeight;
			break;
		case SDCOLORFORMAT_BGR_SD16b:
		case SDCOLORFORMAT_VUY_SD16b:
			dwXScanByteSize = dwWidth*6;		// 1个像素占6字节
			dwBufByteSize = dwXScanByteSize*dwHeight;
			break;

		case SDCOLORFORMAT_YUYV:
		case SDCOLORFORMAT_UYVY:
			dwXScanByteSize = 2*dwWidth;
			dwBufByteSize = dwXScanByteSize*dwHeight;
			break;
		case SDCOLORFORMAT_YUYV_V210:			// V210最小单位为6像素16字节, 跨距为128字节的整数倍(48像素)
			if ((dwWidth%6) != 0)				// 其宏像素由6×1个图像像素组成，在缓存中占4个32位little-endian字节序双字（DWord）
				dwWidth = (dwWidth/6+1)*6;
			if (((dwWidth*16/6)%128) != 0)
				dwXScanByteSize = ((dwWidth*16/6)/128+1)*128;
			else
				dwXScanByteSize = dwWidth*16/6;
			dwBufByteSize = dwXScanByteSize*dwHeight;
			break;
		case SDCOLORFORMAT_YUYV_V216:
			dwXScanByteSize = dwWidth*4;		// 2个像素占8字节
			dwBufByteSize = dwXScanByteSize*dwHeight;
			break;
		case SDCOLORFORMAT_YUYV_M101:			//最小单位为16像素32字节, 跨距为128字节的整数倍(48像素)
			if ((dwWidth%16) != 0)
				dwWidth = (dwWidth/16+1)*16;
			if (((dwWidth*2)%128) != 0)
				dwXScanByteSize = ((dwWidth*2/128)+1)*128;
			else
				dwXScanByteSize = dwWidth*2;
			dwBufByteSize = dwXScanByteSize*dwHeight;
			break;
		case SDCOLORFORMAT_YUYV_M101_10BIT:		//最小单位为16像素40字节, 跨距为128字节的整数倍(48像素)
			if ((dwWidth%16) != 0)
				dwWidth = (dwWidth/16+1)*16;
			if (((dwWidth*40/16)%128) != 0)
				dwXScanByteSize = ((dwWidth*40/16/128)+1)*128;
			else
				dwXScanByteSize = dwWidth*40/16;
			dwBufByteSize = dwXScanByteSize*dwHeight;
			break;
		case SDCOLORFORMAT_YUAYVA4224:			//最小单位为8像素,Picth为32字节对齐。在720时为2176字节，1920时为5760字节
			dwXScanByteSize = 3*dwWidth;		//每像素为3字节
			if ((dwXScanByteSize%32) != 0)
				dwXScanByteSize = (dwXScanByteSize/32 + 1) * 32;
			dwBufByteSize = dwXScanByteSize*dwHeight;
			break;
		case SDCOLORFORMAT_YUYV_DNXHD_10BIT:	//缓存排列2部分，前一部分和SDCOLORFORMAT_YUYV完全相同，后一部分是每个分量的低2位依次排列
			dwXScanByteSize = 20*dwWidth/8;	
			dwBufByteSize = dwXScanByteSize*dwHeight;
			break;

		case SDCOLORFORMAT_YUVP_444:
			dwXScanByteSize = 0;
			dwBufByteSize = 3*dwWidth*dwHeight;
			break;
		case SDCOLORFORMAT_YUVP_422:
			dwXScanByteSize = 0;
			dwBufByteSize = 2*dwWidth*dwHeight;
			break;
		case SDCOLORFORMAT_YUVP_420:
		case SDCOLORFORMAT_YUVP_411:
			dwXScanByteSize = 0;
			dwBufByteSize = 3*dwWidth*dwHeight/2;
			break;
	}
	if (pdwXScanByteSize)
		(*pdwXScanByteSize) = dwXScanByteSize;
	return dwBufByteSize;
};

enum SD_STREAM_TYPE  // 视音频流格式类型
{
	SDSTREAMTYPE_UNKNOWN			= 0x00000000,	//无效格式

	SDSTREAMTYPE_OPENDML_AVI		= 0x00000001,	// OPENDML Video 文件
	SDSTREAMTYPE_MSVFW_AVI			= 0x00000002,	// MSVFW Video 文件
	SDSTREAMTYPE_MSVFW_WAV			= 0x00000004,	// MSVFW Audio 文件
	
	SDSTREAMTYPE_ES					= 0x00000010,	// Element Stream file
	SDSTREAMTYPE_PS					= 0x00000020,	// Program Stream file
	SDSTREAMTYPE_VCD				= 0x00100000,	// VCD MPG file, --- Special PS	
	SDSTREAMTYPE_DVD				= 0x00400000,	// DVD MPG file, --- Special PS
	SDSTREAMTYPE_TS					= 0x00000040,	// Transport Stream file
	SDSTREAMTYPE_HDV				= 0x00000200,	// HDV file, --- Special TS
	SDSTREAMTYPE_SUBTITLE			= 0x00800000,	// TS SubTitle文件

	SDSTREAMTYPE_MXF				= 0x00010000,   // MXF File
	SDSTREAMTYPE_3GPP				= 0x00000400,   // 3GPP file
	SDSTREAMTYPE_FLV				= 0x00000800,	// FLV file
	SDSTREAMTYPE_ISOMP4				= 0x00000080,	// ISO MP4 Stream file

	SDSTREAMTYPE_REAL_MEDIA			= 0x01000000,	// REAL MEDIA 文件
	SDSTREAMTYPE_WINDOWS_MEDIA		= 0x02000000,	// WINDOWS MEDIA PLAY 文件
	SDSTREAMTYPE_QUICKTIME_MOV		= 0x04000000,	// QUICKTIME 文件
	SDSTREAMTYPE_ZAXEL              = 0x08000000,	// Zaxel文件
	SDSTREAMTYPE_AIFF				= 0x00200000,	// AIFF文件
	SDSTREAMTYPE_MKV				= 0x00000008,	// MKV文件

	SDSTREAMTYPE_GXF				= 0x00020000,   // GXF File
	SDSTREAMTYPE_OMNEON				= 0x00080000,   // OMNEON Video Server File
	SDSTREAMTYPE_LXF				= 0x00000100,   // LEITCH Video Server File
	SDSTREAMTYPE_SAF				= 0x00040000,   // SEACHANGE Video Server File
	SDSTREAMTYPE_MAV70				= 0x00001000,   // SONY MAV70 Video Server File
	SDSTREAMTYPE_VSR2000			= 0x00002000,   // SONY VSR2000 Video Server File
	SDSTREAMTYPE_MSS				= 0x00004000,   // PINNACLE MediaStream Server File
	
	SDSTREAMTYPE_P2CLIP				= 0x00008000,   // P2 Card Clip
	SDSTREAMTYPE_DPX				= 0x00008001,   // DPX File
	SDSTREAMTYPE_R3D                = 0x00008002,   // RED ONE R3D file
	SDSTREAMTYPE_E2CLIP             = 0x00008003,   // E2 Card Clip 
	SDSTREAMTYPE_HLS                = 0x00008004,   // HTTP Live Streaming 
	SDSTREAMTYPE_RTP                = 0x00008005,   // Real-time Transport Protocol 
	SDSTREAMTYPE_DMC_SEQUENCE_FILE  = 0x00008006,   // 分段生成时的中间文件格式(内部格式，不必显示)
	SDSTREAMTYPE_AMR                = 0x00008007,   // AMR格式
		
	SDSTREAMTYPE_SDDEF10000000		= 0x10000000,	// 扩展定义---0x10000000
	SDSTREAMTYPE_SDDEF20000000		= 0x20000000,	// 扩展定义---0x20000000
	SDSTREAMTYPE_SDDEF40000000		= 0x40000000,	// 扩展定义---0x40000000
	SDSTREAMTYPE_SDDEF80000000		= 0x80000000,	// 扩展定义---0x80000000
};

enum SD_VIDEOSCAN_MODE	// 视频扫描帧场数据排列方式, 有时间和空间两个概念，场序（First，Second）表示时间概念，奇偶场(Top，Bottom)表示空间（image Buffer)概念
{
	SDVIDEOSCANMODE_Invalid						=	-1,
	SDVIDEOSCANMODE_FirstFieldTop				=	0,			// 两场数据交织排列, 首(First)场排列在奇(Top)场位置
	SDVIDEOSCANMODE_SecondFieldTop				=	1,			// 两场数据交织排列, 第二(Second)场排列在奇(Top)场位置
	SDVIDEOSCANMODE_Progressive					=	2,			// 帧数据连续排列, 无场序时间概念
	SDVIDEOSCANMODE_ProgressiveSegmented		=	3,			// 帧数据分割排列, 无场序时间概念, 无奇偶场空间概念
	SDVIDEOSCANMODE_FirstFieldTopBackToBack		=	4,			// 两场数据分别排列,首(First)场后是第二(Second)场, 无奇偶场空间概念
	SDVIDEOSCANMODE_SecondFieldTopBackToBack	=	5,			// 两场数据分别排列,第二(Second)场后是首(First)场, 无奇偶场空间概念
};

enum SD_VIDEO_ASPECTRATIO	// 视频幅宽比类型
{
   SDVIDEOASPECTRATIO_Invalid	=	0x00000000,
   SDVIDEOASPECTRATIO_4_3		=	0x00000001,
   SDVIDEOASPECTRATIO_16_9		=	0x00000002,
   SDVIDEOASPECTRATIO_14_9		=	0x00000003,				//SMPTE 2016-1
};

enum SD_COLOR_PRIMARIES			// 源基色的色度坐标(ISO13818-2)
{
	SDCOLORPRIMARIES_Unknow			=	-1,		
	SDCOLORPRIMARIES_Forbidden		=	0,
	SDCOLORPRIMARIES_ITU_R709		=	1,		// SMPTE 274M-1995 and SMPTE 296M-1997
	SDCOLORPRIMARIES_Unspecified	=	2,
	SDCOLORPRIMARIES_Reserved		=	3,
	SDCOLORPRIMARIES_ITU_R470_2M	=	4,
	SDCOLORPRIMARIES_ITU_R470_2BG	=	5,		// EBU Tech. 3213 (1981).
	SDCOLORPRIMARIES_SMPTE_170M		=	6,		// SMPTE 293M-1996, SMPTE 240M-1995,SMPTE 274M-1995
	SDCOLORPRIMARIES_SMPTE_240M		=	7,		// Same as SMPTE 170M
	SDCOLORPRIMARIES_GenericFilm	=	8,		// from Mpeg4
	SDCOLORPRIMARIES_BT2020	        =	9,		// ITU-R BT.2020
};

enum SD_COLOR_TRANSFER		// 光电转换特性(ISO13818-2)
{
	SDCOLORTRANSFER_UNKNOW			=	-1,
	SDCOLORTRANSFER_Forbidden		=	0,
	SDCOLORTRANSFER_ITU_R709		=	1,		// SMPTE 274M-1995, SMPTE 296M-1997, SMPTE 293M-1996 and SMPTE 170M-1994.
	SDCOLORTRANSFER_Unspecified		=	2,
	SDCOLORTRANSFER_Reserved		=	3,
	SDCOLORTRANSFER_ITU_R470_2M		=	4,
	SDCOLORTRANSFER_ITU_R470_2BG	=	5, 
	SDCOLORTRANSFER_SMPTE_170M		=	6,		// Same as ITU_R709
	SDCOLORTRANSFER_SMPTE_240M		=	7, 
	SDCOLORTRANSFER_Linear			=	8,
	SDCOLORTRANSFER_LOG_100_1		=	9,		// form Mpeg4
	SDCOLORTRANSFER_LOG_316_1		=	10,		// form Mpeg4
	SDCOLORTRANSFER_IEC_61966_2_4	=	11,		// IEC 61966-2-4
	SDCOLORTRANSFER_BT1361	        =	12,		// Rec. ITU-R BT.1361 extended colour gamut system
	SDCOLORTRANSFER_IEC_61966_2_1	=	13,		// IEC 61966-2-1 (sRGB or sYCC)
	SDCOLORTRANSFER_BT2020_10BIT    =	14,		// Rec. ITU-R BT.2020 for 10 bit system
	SDCOLORTRANSFER_BT2020_12BIT    =	15,		// Rec. ITU-R BT.2020 for 12 bit system
};

enum SD_COLOR_MATRIX		//	颜色空间变换系数(ISO13818-2)
{	
	SDCOLORMATRIX_UNKNOW		=	-1,
	SDCOLORMATRIX_Forbidden		=	0,
	SDCOLORMATRIX_ITU_R709	    =	1,		// SMPTE 274M-1995 and SMPTE 296M-1997.
	SDCOLORMATRIX_Unspecified	=	2,
	SDCOLORMATRIX_Reserved	    =	3,
	SDCOLORMATRIX_FCC			=	4,
	SDCOLORMATRIX_ITU_R470_2BG	=	5,		// Same as SMPTE_170M
	SDCOLORMATRIX_SMPTE_170M	=	6,		// ITU-R BT.601-4, ITU-R BT.470-2 System B and G, SMPTE 293M-1996
	SDCOLORMATRIX_SMPTE_240M	=	7,
	SDCOLORMATRIX_YCgCo			=	8,
	SDCOLORMATRIX_BT2020_NCL	=	9,		// ITU-R BT.2020 non-constant luminance system
	SDCOLORMATRIX_BT2020_CL	    =	10		// ITU-R BT.2020 constant luminance system
};

enum SD_ACTIVE_FORMAT_DESCRIPTION				// 图像有效区域信息描述，按SMPTE 2016-1定义
{	
	SDAFD_UNKNOW	=	-1,
	SDAFD_0000		=	0x0,		// '0000'
	SDAFD_0001		=	0x1,		// '0001' 
	SDAFD_0010     =	0x2,		// '0010' 
	SDAFD_0011     =	0x3,		// '0011' 
	SDAFD_0100     =	0x4,		// '0100'
	SDAFD_0101     =	0x5,		// '0101'
	SDAFD_0110     =	0x6,		// '0110'
	SDAFD_0111     =	0x7,		// '0111'
	SDAFD_1000     =	0x8,		// '1000' 
	SDAFD_1001     =	0x9,		// '1001' 
	SDAFD_1010     =	0xA,		// '1010' 
	SDAFD_1011     =	0xB,		// '1011' 
	SDAFD_1100     =	0xC,		// '1100' 
	SDAFD_1101     =	0xD,		// '1101' 
	SDAFD_1110     =	0xE,		// '1110' 
	SDAFD_1111     =	0xF,		// '1111' 
};

enum SD_DATARATE_TYPE				// MPEG视频编解码格式码率类型
{
	SDDATARATE_VBR_QUILTY			=	0,			//可变码率编码(VBR),质量固定
	SDDATARATE_CONSTANT				=	1,			//恒定码率编码
	SDDATARATE_VBR_AVERAGE_SMALL	=	2,			//可变码率编码(VBR),平均码率, 小码率变化
	SDDATARATE_VBR_AVERAGE_LARGE	=	3,			//可变码率编码(VBR),平均码率, 大码率变化
};

struct SDVideoMediaInfo	// 视频基本属性
{
	SD_UINT32				dwStruSize;					// 结构大小
	SD_UINT32				dwWidth;					// 图像宽度（水平分辨率）
	SD_UINT32				dwHeight;					// 图像高度（垂直分辨率）
	SD_UINT32				dwStandardRate;				// 基本帧频
	SD_UINT32				dwStandardScale;			// 系数（用于帧序号计算）
	SD_VIDEOSCAN_MODE		enumScanMode;				// 视频扫描帧场数据排列方式
	SD_COLOR_FORMAT			enumColorFormat;			// 视频颜色格式
	SD_VIDEO_TYPE			enumVideoType;				// 视频编解码类型
	SD_UINT32				dwVideoSubType;				// 视频编解码的子类型,子类型定义随enumVideoType不同而不同
	SD_UINT32				dwDataRateInBitsPerSec;		// 码率, based on *****bits/S******	// Mpeg专用设置
	SD_DATARATE_TYPE		enumDataRateType;			// 码率类型							// Mpeg专用设置
	SD_UINT32				dwGOPSize;					// IBP帧压缩类型时的IBP帧组大小		// Mpeg专用设置
	SD_UINT32				dwReferencePeriod;			// IBP帧压缩类型时IP帧的间隔周期。	// Mpeg专用设置
	SD_BOOL					bIsClipped;					// SD_TRUE:Y(8bit)[16-235]/(10bit)[64,940]---normal, SD_FALSE:Y[0-255][0-1023]---KEY; maybe Cb/Cr

//Below is Version 2 Add.
	SD_UINT32				dwDisplayWidth;				// 视频显示幅宽度值
	SD_UINT32				dwDisplayHeight;			// 视频显示幅高度值
	SD_COLOR_PRIMARIES		enumColorPrimaries;			// 源基色的色度坐标(ISO13818-2)
	SD_COLOR_TRANSFER		enumColorTransfer;			// 光电转换特性(ISO13818-2)
	SD_COLOR_MATRIX			enumColorMatrix;			// 颜色空间变换系数(ISO13818-2)
	SD_ACTIVE_FORMAT_DESCRIPTION	enumAFD;			// 图像有效区域信息描述，按SMPTE 2016-1定义
	SD_UINT32				dwMaxDataRateInBitsPerSec;	// 最大码率, based on *****bits/S******
	SD_UINT32				dwMinDataRateInBitsPerSec;	// 最小码率, based on *****bits/S******
	SD_UINT8				dwH264EncoderLevel;	//H264编码级别，范围1-9，默认5，1最慢质量最高，9最快质量最低（仅对H264编码有效）
	mutable SD_INT32		dwFlags;
	SD_UINT8 *				extradata;
	int						extradata_size;
	SD_BOOL					bProfile;					//H264的profile参数是否生效
	
	SDVideoMediaInfo()
	{
		dwStruSize = sizeof(SDVideoMediaInfo);
		dwWidth = 720;
		dwHeight = 576;
		dwStandardRate = 25;
		dwStandardScale = 1;
		enumScanMode = SDVIDEOSCANMODE_FirstFieldTop;
		enumColorFormat = SDCOLORFORMAT_YUVP_420;
		enumVideoType = SDVIDEOTYPE_UNKNOW;
		dwVideoSubType = 0x00000000;
		dwDataRateInBitsPerSec = 25000000;
		enumDataRateType = SDDATARATE_CONSTANT;
		dwGOPSize = 14;
		dwReferencePeriod = 2;
		bIsClipped = SD_TRUE;
		dwDisplayWidth = 4;										// SD default
		dwDisplayHeight = 3;									// SD default
		enumColorPrimaries = SDCOLORPRIMARIES_ITU_R470_2BG;		// SD default
		enumColorTransfer = SDCOLORTRANSFER_ITU_R470_2BG;		// SD default
		enumColorMatrix = SDCOLORMATRIX_ITU_R470_2BG;			// SD default
		enumAFD = SDAFD_1000;
		dwMaxDataRateInBitsPerSec = 0;
		dwMinDataRateInBitsPerSec = 0;
		dwFlags = 0;
		dwH264EncoderLevel = 5;
		extradata = nullptr;
		extradata_size = 0;
		bProfile = SD_FALSE;
	};

	SDVideoMediaInfo(const SDVideoMediaInfo &other)
	{
		*this = other;
	};

	SDVideoMediaInfo& operator = (const SDVideoMediaInfo& other)
	{
		dwStruSize = other.dwStruSize;
		dwWidth = other.dwWidth;
		dwHeight = other.dwHeight;
		dwStandardRate = other.dwStandardRate;
		dwStandardScale = other.dwStandardScale;
		enumScanMode = other.enumScanMode;
		enumColorFormat = other.enumColorFormat;
		enumVideoType = other.enumVideoType;
		dwVideoSubType = other.dwVideoSubType;
		dwDataRateInBitsPerSec = other.dwDataRateInBitsPerSec;
		enumDataRateType = other.enumDataRateType;
		dwGOPSize = other.dwGOPSize;
		dwReferencePeriod = other.dwReferencePeriod;
		bIsClipped = other.bIsClipped;
		dwDisplayWidth = other.dwDisplayWidth;
		dwDisplayHeight = other.dwDisplayHeight;
		enumColorPrimaries = other.enumColorPrimaries;
		enumColorTransfer = other.enumColorTransfer;
		enumColorMatrix = other.enumColorMatrix;
		enumAFD = other.enumAFD;
		dwMaxDataRateInBitsPerSec = other.dwMaxDataRateInBitsPerSec;
		dwMinDataRateInBitsPerSec = other.dwMinDataRateInBitsPerSec;
		dwFlags = other.dwFlags;
		dwH264EncoderLevel = other.dwH264EncoderLevel;
		extradata = other.extradata;
		extradata_size = other.extradata_size;
		bProfile = other.bProfile;
		return *this;
	};
};

struct SDVideoFrameImageBufInfo	//视频帧图像数据块属性
{
	SD_UINT32			dwXSize;								// 图象宽度像素数量
	SD_UINT32			dwYSize;								// 图象高度像素数量
	SD_UINT32			dwScanXByteSize;						// 跨距
	SD_BOOL				bIsDirUPtoDOWN;							// 图象缓存是否为正
	SD_COLOR_FORMAT		enumColorFormat;						// 颜色格式
	SD_VIDEOSCAN_MODE	enumScanMode;							// 扫描方式
	SD_BOOL             bIsClipped;								// 16-235 or 0-255
	SD_UINT32           dwDisplayWidth;   						// 视频显示幅宽度值
	SD_UINT32           dwDisplayHeight;						// 视频显示幅高度值
	SD_COLOR_PRIMARIES	enumColorPrimaries;						// 源基色的色度坐标(ISO13818-2)
	SD_COLOR_TRANSFER	enumColorTransfer;						// 光电转换特性(ISO13818-2)
	SD_COLOR_MATRIX		enumColorMatrix;						// 颜色空间变换系数(ISO13818-2)
	SD_ACTIVE_FORMAT_DESCRIPTION	enumAFD;					// 图像有效区域信息描述，按SMPTE 2016-1定义
	
	SDVideoFrameImageBufInfo()
	{
		dwXSize = 0;
		dwYSize = 0;
		dwScanXByteSize = 0;
		bIsDirUPtoDOWN = SD_TRUE;
		enumColorFormat = SDCOLORFORMAT_UNKNOW;
		enumScanMode = SDVIDEOSCANMODE_FirstFieldTop;
		bIsClipped = SD_TRUE;
		dwDisplayWidth = 0;
		dwDisplayHeight = 0;
		enumColorPrimaries = SDCOLORPRIMARIES_ITU_R470_2BG;		// SD default
		enumColorTransfer = SDCOLORTRANSFER_ITU_R470_2BG;		// SD default
		enumColorMatrix = SDCOLORMATRIX_ITU_R470_2BG;			// SD default
		enumAFD = SDAFD_1000;
	};

	SDVideoFrameImageBufInfo(const SDVideoFrameImageBufInfo &other)
	{
		*this = other;
	};

	SDVideoFrameImageBufInfo& operator = (const SDVideoFrameImageBufInfo& other)
	{
		dwXSize = other.dwXSize;
		dwYSize = other.dwYSize;
		dwScanXByteSize = other.dwScanXByteSize;
		bIsDirUPtoDOWN = other.bIsDirUPtoDOWN;
		enumColorFormat = other.enumColorFormat;
		enumScanMode = other.enumScanMode;
		bIsClipped = other.bIsClipped;
		dwDisplayWidth = other.dwDisplayWidth;
		dwDisplayHeight = other.dwDisplayHeight;
		enumColorPrimaries = other.enumColorPrimaries;
		enumColorTransfer = other.enumColorTransfer;
		enumColorMatrix = other.enumColorMatrix;
		enumAFD = other.enumAFD;
		return *this;
	};
};

enum SD_AUDIO_CHANNELCONFIGURATION		// 声道属性枚举定义
{
	SDAUDIOCFG_UNKNOW				=	0,      // 声道属性未知
	SDAUDIOCFG_INDEPENDENT			=	1,      // 独立声道
	SDAUDIOCFG_STEREO				=	2,      // 立体声(左 右)
	SDAUDIOCFG_5_1					=	3,		// 5.1(左 右 中置 左环绕 右环绕 低音)
	SDAUDIOCFG_7_1					=	4,      // 7.0(前左 前右 中置 左 右 左环绕 右环绕  低音)

	SDAUDIOCFG_2_1					=	5,      // 2.1(左 右 低音)
	SDAUDIOCFG_3_0_C				=	6,      // 3.0(左 右 中置)
	SDAUDIOCFG_3_0_S				=	7,      // 3.0(左 右 环绕)
	SDAUDIOCFG_3_1_C_LFE			=	8,      // 3.1(左 右 中置 低音)
	SDAUDIOCFG_3_1_S_LFE			=	9,      // 3.1(左 右 环绕 低音)
	SDAUDIOCFG_4_0_C_S				=	10,     // 4.0(左 右 中置 环绕)
	SDAUDIOCFG_4_0_LS_RS			=	11,     // 4.0(左 右 左环绕 右环绕)
	SDAUDIOCFG_4_1_C_S_LFE			=	12,     // 4.1(左 右 中置 环绕 低音)
	SDAUDIOCFG_4_1_LS_RS_LFE		=	13,     // 4.1(左 右 左环绕 右环绕 低音)
	SDAUDIOCFG_5_0					=	14,     // 5.0(左 右 中置 左环绕 右环绕)
	SDAUDIOCFG_6_0_LRC_LRSRC		=	15,     // 6.0(左 右 前中置 左环绕 右环绕 后中置)
	SDAUDIOCFG_6_0_FLFR_LR_LRS		=	16,     // 6.0(前左 前右 左 右 左环绕 右环绕)
	SDAUDIOCFG_6_1_LRFC_LRSRC_LFE	=	17,     // 6.1(左 右 前中置 左环绕  右环绕 后中置 低音)
	SDAUDIOCFG_6_1_FLR_LRLRS_LFE	=	18,     // 6.1(前左 前右 左 右 左环绕 右环绕 低音)
	SDAUDIOCFG_7_0					=	19,     // 7.0(前左 前右 中置 左 右 左环绕 右环绕)
};

enum SD_CHANNELSAMPLE_FORMAT	//音频声道采样数据格式
{
	SDCHANNELSAMPLESFORMAT_Unknow				=	0,
	SDCHANNELSAMPLESFORMAT_Progressive			=	1,			//音频声道采样数据连续排列...CH1(Sn)CH2(Sn)CH1(Sn+1)CH2(Sn+1)...
	SDCHANNELSAMPLESFORMAT_Segmented			=	2,			//音频声道采样数据分割排列...CH1(Sn)CH1(Sn+1)...CH2(Sn)CH2(Sn+1)...
	SDCHANNELSAMPLESFORMAT_Progressive_32bit	=	3,			//音频声道采样数据连续排列...CH1(Sn)CH2(Sn)CH1(Sn+1)CH2(Sn+1)...
	SDCHANNELSAMPLESFORMAT_Segmented_32bit		=	4,			//音频声道采样数据分割排列...CH1(Sn)CH1(Sn+1)...CH2(Sn)CH2(Sn+1)...
};

struct SDAudioMediaInfo			// 音频基本属性
{
	SD_UINT32			dwStruSize;			// 结构大小
	SD_AUDIO_TYPE		enumAudioType;		// 音频编解码类型。
	SD_UINT32			dwAudioSubType;		// 音频编解码的子类型,子类型定义随enumAudioType不同而不同
	SD_UINT32			dwChannels;			// 声道数目
	SD_UINT32			dwBitsPerSample;	// 采样位数 
	SD_UINT32			dwSamplesPerSec;	// 每秒采样数量 
	SD_UINT32			dwAvgBitsPerSec;	// 音频码率 bits
	SD_UINT32			dwBlockAlign;		// 数据块对齐单位(每个采样样本需要的字节数), 声道数*量化数/8, 量化数(16,20?,24,32...)

//Below is Version 2 Add.
	SD_AUDIO_CHANNELCONFIGURATION	enumAudioCFG;		//声道属性
	SD_CHANNELSAMPLE_FORMAT enumChannelSamplesFormat;	//音频声道采样数据格式

	SD_UINT8 *			extradata;
	int					extradata_size;
		
	SDAudioMediaInfo()
	{
		dwStruSize = sizeof(SDAudioMediaInfo);
		enumAudioType = SDAUDIOTYPE_WAVE_PCM;
		dwAudioSubType = 0;
		dwChannels = 1;
		dwBitsPerSample = 16;
		dwSamplesPerSec = 48000;
		dwAvgBitsPerSec = dwSamplesPerSec*dwBitsPerSample*dwChannels;
		dwBlockAlign = 2;
		enumAudioCFG = SDAUDIOCFG_INDEPENDENT;
		enumChannelSamplesFormat = SDCHANNELSAMPLESFORMAT_Progressive;
		extradata = nullptr;
		extradata_size = 0;
	};

	SDAudioMediaInfo(const SDAudioMediaInfo &other)
	{
		*this = other;
	};

	SDAudioMediaInfo& operator = (const SDAudioMediaInfo& other)
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
		extradata = other.extradata;
		extradata_size = other.extradata_size;
		return *this;
	};
};

struct SDAudioSamplesBufInfo	//音频采样数据块属性
{
	SD_UINT32			dwChannels;								// 声道数目
	SD_UINT32			dwBitsPerSample;						// 采样位数 
	SD_UINT32			dwSamplesPerSec;						// 每秒采样数量 
	SD_UINT32			dwAvgBitsPerSec;						// 音频码率 bits
	SD_UINT32			dwBlockAlign;							// 数据块对齐单位(每个采样样本需要的字节数), 声道数*量化数/8, 量化数(16,20?,24,32...)
	SD_AUDIO_CHANNELCONFIGURATION	enumAudioCFG;				// 声道属性
	SD_CHANNELSAMPLE_FORMAT			enumChannelSamplesFormat;	// 音频声道采样数据格式

	SDAudioSamplesBufInfo()
	{
		dwChannels = 1;
		dwBitsPerSample = 16;
		dwSamplesPerSec = 48000;
		dwAvgBitsPerSec = dwSamplesPerSec*dwBitsPerSample*dwChannels;
		dwBlockAlign = 2;
		enumAudioCFG = SDAUDIOCFG_INDEPENDENT;
		enumChannelSamplesFormat = SDCHANNELSAMPLESFORMAT_Progressive;
	};

	SDAudioSamplesBufInfo(const SDAudioSamplesBufInfo &other)
	{
		*this = other;
	};

	SDAudioSamplesBufInfo& operator = (const SDAudioSamplesBufInfo& other)
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

struct SDStreamMediaInfo		// 视音频流(文件)属性
{
	SD_UINT32				dwStruSize;						// 结构大小
	SD_UINT32				dwTotalAverDataRateInBitsPerSec;// 总体平均码率, based on *****bits/S******
	SD_UINT32				dwTotalMaxDataRateInBitsPerSec;	// 总体最大码率, based on *****bits/S******
	SD_UINT32				dwTotalMinDataRateInBitsPerSec;	// 总体最小码率, based on *****bits/S******

	SD_STREAM_TYPE			enumStreamMediaType;			// stream type
	SD_UINT32				dwStreamMediaSubType;			// 文件属性的子类型,子类型定义随enumStreamMediaType不同而不同
	
	SD_UINT32				dwVideoStreamCount;				// 视音频流(文件)包含视频流的数量
	SDVideoMediaInfo		sVideoMediaInfo;				// 视音频流(文件)中第一个视频流的媒体属性.

	SD_UINT32				dwAudioStreamCount;				// 视音频流(文件)包含音频流的数量
	SDAudioMediaInfo		sAudioMediaInfo;				// 视音频流(文件)中第一个音频流的媒体属性.
//Below is Version 3 Add.
	SD_UINT32               dwSubtitleStreamCount;          //视音频流(文件)包含字幕流的数量

	SDStreamMediaInfo()
	{
		dwStruSize = sizeof(SDStreamMediaInfo);
		dwTotalAverDataRateInBitsPerSec = 0;
		dwTotalMaxDataRateInBitsPerSec = 0;
		dwTotalMinDataRateInBitsPerSec = 0;
		enumStreamMediaType = SDSTREAMTYPE_UNKNOWN;
		dwStreamMediaSubType = 0;
		dwVideoStreamCount = 0;
		dwAudioStreamCount = 0;
		dwSubtitleStreamCount = 0;

	};
	SDStreamMediaInfo(const SDStreamMediaInfo &other)
	{
		*this = other;
	};

	SDStreamMediaInfo& operator = (const SDStreamMediaInfo& other)
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
		dwSubtitleStreamCount = other.dwSubtitleStreamCount;

		return *this;
	};
};

struct SDStreamMediaInfoEx : public SDStreamMediaInfo		// 视音频流(文件)扩展属性
{
	SD_UINT64	llFileSize;				// 文件大小
	SD_UINT32	dwVideoFrameNum;		// 视频流数据的长度。(Unit:Frame)
	SD_UINT32	dwAudioSamplesNum;		// 音频流数据长度	 (Unit:Sample)
	SD_UINT32   dwSubtitleFrameNum;     // 字幕流数据的长度(Unit:SubtitleFrame)

	SDStreamMediaInfoEx()
	{
		dwStruSize = sizeof(SDStreamMediaInfoEx);
		llFileSize = 0;
		dwVideoFrameNum = 0;
		dwAudioSamplesNum = 0;
		dwSubtitleFrameNum = 0;
	};
	SDStreamMediaInfoEx(const SDStreamMediaInfoEx &other)
	{
		*this = other;
	};

	SDStreamMediaInfoEx(const SDStreamMediaInfo &other)
	{
		*this = other;
	};

	SDStreamMediaInfoEx& operator = (const SDStreamMediaInfoEx& other)
	{
		dwStruSize = other.dwStruSize;
		dwTotalAverDataRateInBitsPerSec = other.dwTotalAverDataRateInBitsPerSec;
		dwTotalMaxDataRateInBitsPerSec = other.dwTotalMaxDataRateInBitsPerSec;
		dwTotalMinDataRateInBitsPerSec = other.dwTotalMinDataRateInBitsPerSec;
		llFileSize = other.llFileSize;
		enumStreamMediaType = other.enumStreamMediaType;
		dwStreamMediaSubType = other.dwStreamMediaSubType;
		dwVideoStreamCount = other.dwVideoStreamCount;
		sVideoMediaInfo = other.sVideoMediaInfo;
		dwVideoFrameNum = other.dwVideoFrameNum;
		dwAudioStreamCount = other.dwAudioStreamCount;
		sAudioMediaInfo = other.sAudioMediaInfo;
		dwAudioSamplesNum = other.dwAudioSamplesNum;
		dwSubtitleFrameNum = other.dwSubtitleFrameNum;

		dwSubtitleStreamCount = other.dwSubtitleStreamCount;
		return *this;
	};

	SDStreamMediaInfoEx& operator = (const SDStreamMediaInfo& other)
	{
		dwStruSize = sizeof(SDStreamMediaInfoEx);
		dwTotalAverDataRateInBitsPerSec = other.dwTotalAverDataRateInBitsPerSec;
		dwTotalMaxDataRateInBitsPerSec = other.dwTotalMaxDataRateInBitsPerSec;
		dwTotalMinDataRateInBitsPerSec = other.dwTotalMinDataRateInBitsPerSec;
		enumStreamMediaType = other.enumStreamMediaType;
		dwStreamMediaSubType = other.dwStreamMediaSubType;
		dwVideoStreamCount = other.dwVideoStreamCount;
		sVideoMediaInfo = other.sVideoMediaInfo;
		dwAudioStreamCount = other.dwAudioStreamCount;
		sAudioMediaInfo = other.sAudioMediaInfo;
		dwSubtitleStreamCount = other.dwSubtitleStreamCount;

		llFileSize = 0;
		dwVideoFrameNum = 0;
		dwAudioSamplesNum = 0;
		dwSubtitleFrameNum = 0;
		
		return *this;
	};
};

enum SD_FIELD
{
   SD_ODD_FIELD			=	0,		//奇数场
   SD_EVEN_FIELD		=	1,		//偶数场
   SD_BOTH_FIELD		=	2,		//奇偶场
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
struct SDRFrameInfo
{
	//结构版本
	SD_UINT32				iVersion;		// 结构版本号。		4---4[序列化占用字节－序列化位置]

											//基本描述
	STREAM_DATATYPE			emDataType;		// 帧数据类型		4---8
	STREAMSTATE			    emStreamFlag;   // 标识是第一帧，还是中间帧，还是末尾帧
	SD_UINT32				iSize;			// 帧数据大小		4---16
	SD_UINT64 				dwFrameIndex;	// 帧数据流顺序		4---28
	SD_UINT32 				dwFrameNum;		// 视频/音频帧数量	4---32

	SD_INT32 				iSamplesOffset;	// 标识RawAudio音频、视频帧中有效采样的偏移数，大于0表示从开始偏移，小于0表示从尾部开始向前偏移		4---36

											// 时间信息扩展
	SD_UINT64				qwDTS;			// 解码时间(90Khz单位)	8---44
	SD_UINT64				qwPTS;			// 展现时间(90Khz单位)	8---52
	SD_UINT64				qwDuration;		// 持续时间(90Khz单位)	8---6

											// for Video
	SD_UINT64				dwShowIndex;	// 帧数据显示顺序			4---104
	FRAME_COMPRESS_TYPE		emFrameType;   	// 帧类型 				4---108

	int						extradata_size;

	SDRFrameInfo()
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

	SDRFrameInfo &operator = (const SDRFrameInfo &other)
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
struct SDResamplerPara
{

};
enum SD_CODEC_PROFILE
{
	PROFILE_UNKNOW = 0x00000000,	// 无效类型
	PROFILE_AVC_BASELINE = 0x00000042,
	PROFILE_AVC_MAIN = 0x0000004d,
	PROFILE_AVC_HIGH = 0x00000064
};
#pragma warning(pop)

#endif // !defined(_SD_SDVADEFINE_H)

