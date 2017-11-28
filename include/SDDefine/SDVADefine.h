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
//=======================================================================================
//与视频制式标准相关的幅宽高、帧率定义和相应的相互转换函数
//=======================================================================================
//	定义数据类型:
//		SD_REFERENCETIME;		//以100ns为单位的64位整型数,目的是用整数表达帧的时间度量
//	定义枚举:
//		SD_VIDEO_STANDARD;		//视频制式标准
//		SD_VIDEO_CLASS;			//视频制式分类
//	定义函数:
//		CSDString	GetVideoStandardHint(SD_VIDEO_STANDARD enumVideoStandard);	//得到视频制式的名称
//		SD_UINT32	_GetWidth(SD_VIDEO_STANDARD enumVideoStandard);				//获得视频制式的水平分辨率。
//		SD_UINT32	_GetHeight(SD_VIDEO_STANDARD enumVideoStandard);				//获得视频制式的垂直分辨率。
//		SD_UINT32	_GetCodecWidth(SD_VIDEO_STANDARD enumVideoStandard);			//视频图像压缩编码的水平大小,是16的倍数
//		SD_UINT32	_GetCodecHeight(SD_VIDEO_STANDARD enumVideoStandard);			//视频图像压缩编码的垂直大小,是16的倍数
//
//		CSDString	GetVideoClassHint(SD_VIDEO_CLASS enumVideoClass);				//得到视频制式分类的名称
//		SD_VIDEO_CLASS	_GetVideoClass(SD_VIDEO_STANDARD enumVideoStandard);		//从视频制式标准得到视频制式分类
//		SD_VOID	_GetStandardRateScale(SD_VIDEO_STANDARD enumVideoStandard, SD_UINT32 &dwRate, SD_UINT32 &dwScale);	//从视频制式标准得到帧率
//		SD_VIDEO_STANDARD	_GetStandardRateScale(SD_UINT32 dwRate, SD_UINT32 dwScale, SD_VIDEO_CLASS enumVideoClass=SDVIDEOCLASS_SD);	//从帧率和分类得到视频制式标准
//
//场或帧与参考时间度量的相互转换函数
//		SD_REFERENCETIME	_FieldToRT(SD_UINT32 dwFieldCount, SD_VIDEO_STANDARD enumVideoStandard);	//依据视频制式转换场数至参考时间度量单位
//		SD_REFERENCETIME	_FieldToRT(SD_UINT32 dwFieldCount, SD_UINT32 dwRate, SD_UINT32 dwScale);	//依据帧率转换场数至参考时间度量单位
//		SD_REFERENCETIME	_FrameToRT(SD_UINT32 dwFrameCount, SD_VIDEO_STANDARD enumVideoStandard);	//依据视频制式转换帧数至参考时间度量单位
//		SD_REFERENCETIME	_FrameToRT(SD_UINT32 dwFrameCount, SD_UINT32 dwRate, SD_UINT32 dwScale);	//依据帧率转换帧数至参考时间度量单位
//		SD_UINT32 _RTToField(SD_REFERENCETIME rt, SD_VIDEO_STANDARD enumVideoStandard);	//依据视频制式转换参考时间度量单位至场数
//		SD_UINT32 _RTToField((SD_REFERENCETIME) rt, SD_UINT32 dwRate, SD_UINT32 dwScale);	//依据帧率转换参考时间度量单位至场数
//		SD_UINT32 _RTToFrame(SD_REFERENCETIME rt, SD_VIDEO_STANDARD enumVideoStandard);	//依据视频制式转换参考时间度量单位至帧数
//		SD_UINT32 _RTToFrame(SD_REFERENCETIME rt, SD_UINT32 dwRate, SD_UINT32 dwScale);	//依据帧率转换参考时间度量单位至帧数
//
//场或帧与浮点型秒数的相互转换函数
//		SD_DOUBLE _FieldToSec(SD_UINT32 dwFieldCount, SD_VIDEO_STANDARD enumVideoStandard);	//依据视频制式转换场数至浮点型秒数
//		SD_DOUBLE _FieldToSec(SD_UINT32 dwFieldCount, SD_UINT32 dwRate, SD_UINT32 dwScale);	//依据帧率转换场数至浮点型秒数
//		SD_DOUBLE _FrameToSec(SD_UINT32 dwFrameCount, SD_VIDEO_STANDARD enumVideoStandard);	//依据视频制式转换帧数至浮点型秒数
//		SD_DOUBLE _FrameToSec(SD_UINT32 dwFrameCount, SD_UINT32 dwRate, SD_UINT32 dwScale);	//依据帧率转换帧数至浮点型秒数
//		SD_UINT32 _SecToField(SD_DOUBLE dblSeconds, SD_VIDEO_STANDARD enumVideoStandard);		//依据视频制式转换浮点型秒数至场数
//		SD_UINT32 _SecToField(SD_DOUBLE dblSeconds, SD_UINT32 dwRate, SD_UINT32 dwScale);		//依据帧率转换浮点型秒数至场数
//		SD_UINT32 _SecToFrame(SD_DOUBLE dblSeconds, SD_VIDEO_STANDARD enumVideoStandard);		//依据视频制式转换浮点型秒数至帧数
//		SD_UINT32 _SecToFrame(SD_DOUBLE dblSeconds, SD_UINT32 dwRate, SD_UINT32 dwScale);		//依据帧率转换浮点型秒数至帧数
//
//帧或浮点型秒数与音频采样数的相互转换函数
//		SD_UINT32 GetAudioLengthInFrame(SD_UINT64 llAudioSamples, SD_UINT32 dwSamplesPerSec, SD_VIDEO_STANDARD enumVideoStandard);	//依据视频制式转换音频采样数至帧数
//		SD_UINT32 GetAudioLengthInFrame(SD_UINT64 llAudioSamples, SD_UINT32 dwSamplesPerSec, SD_UINT32 dwRate, SD_UINT32 dwScale);	//依据帧率转换音频采样数至帧数
//		SD_DOUBLE GetAudioTimeInSec(SD_UINT64 llAudioSamples, SD_UINT32 dwSamplesPerSec);												//转换音频采样数至浮点型秒数
//		SD_UINT64 GetAudioSamplesFromFrame(SD_UINT32 dwFrameCount, SD_UINT32 dwSamplesPerSec, SD_VIDEO_STANDARD enumVideoStandard);	//依据视频制式转换帧数至音频采样数
//		SD_DOUBLE GetAudioSamplesFromFrame(SD_UINT32 dwFrameCount, SD_UINT32 dwSamplesPerSec, SD_UINT32 dwRate, SD_UINT32 dwScale);	//依据帧率转换帧数至音频采样数
//		SD_UINT64 GetAudioSamplesFromSec(SD_DOUBLE dblSeconds, SD_UINT32 dwSamplesPerSec);											//转换浮点型秒数至音频采样数
//
//帧与32位整数的相互转换函数
//		SD_UINT32	_FrameToIOPoint(SD_UINT32 dwFrames, SD_VIDEO_STANDARD enumVideoStandard);	//依据视频制式转换帧数至32位整数
//		SD_UINT32	_FrameToIOPoint(SD_UINT32 dwFrames, SD_UINT32 dwRate, SD_UINT32 dwScale);	//依据帧率转换帧数至32位整数
//		SD_UINT32	_IOPointToFrame(SD_UINT32 ioPoint, SD_VIDEO_STANDARD enumVideoStandard);	//依据视频制式转换32位整数至帧数
//		SD_UINT32	_IOPointToFrame(SD_UINT32 ioPoint, SD_UINT32 dwRate, SD_UINT32 dwScale);	//依据帧率转换32位整数至帧数
//
//帧与时分秒帧字符串的相互转换函数
//		SD_VOID	FramesToTimeCodeString(SD_UINT32 dwFrameCount, CSDString &strTimeCode, SD_VIDEO_STANDARD enumVideoStandard);	//依据视频制式转换帧数至时分秒帧字符串
//		SD_VOID	FramesToTimeCodeStringEx(SD_UINT32 dwFrameCount, CSDString &strTimeCode, SD_VIDEO_STANDARD enumVideoStandard);	//依据视频制式转换帧数至时分秒字符串
//		SD_VOID	FramesToTimeCodeString(SD_UINT32 dwFrameCount, CSDString &strTimeCode, SD_UINT32 dwRate, SD_UINT32 dwScale);	//依据帧率转换帧数至时分秒帧字符串
//		SD_VOID	FramesToTimeCodeStringEx(SD_UINT32 dwFrameCount, CSDString &strTimeCode, SD_UINT32 dwRate, SD_UINT32 dwScale);	//依据帧率转换帧数至时分秒字符串
//		CSDString _FramesToTimeCodeString(SD_UINT32 dwFrameCount, SD_VIDEO_STANDARD enumVideoStandard);						//依据视频制式转换帧数至时分秒帧字符串
//		CSDString _FramesToTimeCodeString(SD_UINT32 dwFrameCount, SD_UINT32 dwRate, SD_UINT32 dwScale);						//依据帧率转换帧数至时分秒帧字符串
//		SD_UINT32	TimeCodeStringToFrames(SD_LPCTSTR lpszTimeCode, SD_VIDEO_STANDARD enumVideoStandard);						//依据视频制式转换时分秒帧字符串至帧数
//		SD_UINT32	TimeCodeStringToFrames(SD_LPCTSTR lpszTimeCode, SD_UINT32 dwRate, SD_UINT32 dwScale);						//依据帧率转换时分秒帧字符串至帧数
//
//浮点型秒数与时分秒帧字符串的相互转换函数
//		CSDString SecondToTimeCodeString(SD_DOUBLE dblSeconds, SD_VIDEO_STANDARD enumVideoStandard);		//依据视频制式转换浮点型秒数至时分秒帧字符串
//		CSDString SecondToTimeCodeString(SD_DOUBLE dblSeconds, SD_UINT32 dwRate, SD_UINT32 dwScale);		//依据帧率转换浮点型秒数至时分秒帧字符串
//		SD_DOUBLE TimeCodeStringToSecond(SD_LPCTSTR lpszTimeCode, SD_VIDEO_STANDARD enumVideoStandard);	//依据视频制式转换时分秒帧字符串至浮点型秒数
//		SD_DOUBLE TimeCodeStringToSecond(SD_LPCTSTR lpszTimeCode, SD_UINT32 dwRate, SD_UINT32 dwScale);	//依据帧率转换时分秒帧字符串至浮点型秒数
//		CSDString _SecondToTimeString(SD_DOUBLE dblSeconds, SD_UINT32 dwMilliSecBitNum=0);				//转换浮点型秒数至时分秒毫秒字符串
//=======================================================================================
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

//	获得视频制式的名称。
SD_INLINE CSDString	GetVideoStandardHint(SD_VIDEO_STANDARD enumVideoStandard)
{
	CSDString strHint;
	SD_UINT32 dwWidth, dwHigh, dwCodecHigh;
	GetVideoStandardPara(enumVideoStandard, strHint, dwWidth, dwHigh, dwCodecHigh);
	return strHint;
};

//获得视频制式的水平分辨率。
SD_INLINE	SD_UINT32	_GetWidth(SD_VIDEO_STANDARD enumVideoStandard)
{
	CSDString strHint;
	SD_UINT32 dwWidth, dwHigh, dwCodecHigh;
	GetVideoStandardPara(enumVideoStandard, strHint, dwWidth, dwHigh, dwCodecHigh);
	return dwWidth;
};

//获得视频制式的垂直分辨率。
SD_INLINE	SD_UINT32	_GetHeight(SD_VIDEO_STANDARD enumVideoStandard)
{
	CSDString strHint;
	SD_UINT32 dwWidth, dwHigh, dwCodecHigh;
	GetVideoStandardPara(enumVideoStandard, strHint, dwWidth, dwHigh, dwCodecHigh);
	return dwHigh;
};

//视频图像压缩编码的水平大小,是16的倍数
SD_INLINE	SD_UINT32	_GetCodecWidth(SD_VIDEO_STANDARD enumVideoStandard)
{
	return _GetWidth(enumVideoStandard);
};

//视频图像压缩编码的垂直大小,是16的倍数
SD_INLINE	SD_UINT32	_GetCodecHeight(SD_VIDEO_STANDARD enumVideoStandard)
{
	CSDString strHint;
	SD_UINT32 dwWidth, dwHigh, dwCodecHigh;
	GetVideoStandardPara(enumVideoStandard, strHint, dwWidth, dwHigh, dwCodecHigh);
	return dwCodecHigh;
};

enum SD_VIDEO_CLASS		//视频制式分类
{
	SDVIDEOCLASS_UNKNOW			=	0x00000000,
	SDVIDEOCLASS_SD				=	0x00000001,
	SDVIDEOCLASS_HD1080i		=	0x00000002,
	SDVIDEOCLASS_HD1080p		=	0x00000004,
	SDVIDEOCLASS_HD1080psf		=	0x00000008,
	SDVIDEOCLASS_HD720p			=	0x00000010,
	SDVIDEOCLASS_HD1080P		=	0x00000100,
	SDVIDEOCLASS_2K1080P		=	0x00000200,
	SDVIDEOCLASS_2K1080Psf		=	0x00000400,
	SDVIDEOCLASS_2K1556P		=	0x00000800,
	SDVIDEOCLASS_2K1556Psf		=	0x00001000,
	SDVIDEOCLASS_4K3840P		=	0x00010000,
	SDVIDEOCLASS_4K3840Psf		=	0x00040000,
	SDVIDEOCLASS_4K4096P		=	0x00020000,
	SDVIDEOCLASS_4K4096Psf		=	0x00080000,
	SDVIDEOCLASS_I_RateScale	=	0x00000020,
	SDVIDEOCLASS_P_RateScale	=	0x00000040,
	SDVIDEOCLASS_Psf_RateScale	=	0x00000080,
};

//得到视频制式分类的名称
SD_INLINE CSDString	GetVideoClassHint(SD_VIDEO_CLASS enumVideoClass)
{
	CSDString	strVideoClass = _T("Unknow");
	switch(enumVideoClass)
	{
		case SDVIDEOCLASS_SD:
			strVideoClass = _T("SD");
			break;
		case SDVIDEOCLASS_HD1080i:
			strVideoClass = _T("HD 1080i");
			break;
		case SDVIDEOCLASS_HD720p:
			strVideoClass = _T("HD 720p");
			break;
		case SDVIDEOCLASS_HD1080p:
			strVideoClass = _T("HD 1080p");
			break;
		case SDVIDEOCLASS_HD1080psf:
			strVideoClass = _T("HD 1080psf");
			break;
		case SDVIDEOCLASS_HD1080P:
			strVideoClass = _T("HD 1080P");
			break;
		case SDVIDEOCLASS_2K1080P:
			strVideoClass = _T("2K 1080P");
			break;
		case SDVIDEOCLASS_2K1080Psf:
			strVideoClass = _T("2K 1080Psf");
			break;
		case SDVIDEOCLASS_2K1556P:
			strVideoClass = _T("2K 1556P");
			break;
		case SDVIDEOCLASS_2K1556Psf:
			strVideoClass = _T("2K 1556Psf");
			break;
		case SDVIDEOCLASS_4K3840P:
			strVideoClass = _T("4K 3840P");
			break;
		case SDVIDEOCLASS_4K3840Psf:
			strVideoClass = _T("4K 3840Psf");
			break;
		case SDVIDEOCLASS_4K4096P:
			strVideoClass = _T("4K 4096P");
			break;
		case SDVIDEOCLASS_4K4096Psf:
			strVideoClass = _T("4K 4096Psf");
			break;
		case SDVIDEOCLASS_I_RateScale:
			strVideoClass = _T("I_RateScale");
			break;
		case SDVIDEOCLASS_P_RateScale:
			strVideoClass = _T("P_RateScale");
			break;
		case SDVIDEOCLASS_Psf_RateScale:
			strVideoClass = _T("Psf_RateScale");
			break;
	}
	return strVideoClass;
};

//从视频制式标准得到视频制式分类
SD_INLINE	SD_VIDEO_CLASS	_GetVideoClass(SD_VIDEO_STANDARD enumVideoStandard)
{
	switch(enumVideoStandard) 
	{
		case SDVIDEOSTANDARD_PAL:
		case SDVIDEOSTANDARD_NTSC2997:
		case SDVIDEOSTANDARD_NTSC30:
			return SDVIDEOCLASS_SD;

		case SDVIDEOSTANDARD_HD1080i_25:
		case SDVIDEOSTANDARD_HD1080i_2997:
		case SDVIDEOSTANDARD_HD1080i_30:
			return SDVIDEOCLASS_HD1080i;
	
		case SDVIDEOSTANDARD_HD720p_2398:
		case SDVIDEOSTANDARD_HD720p_24:
		case SDVIDEOSTANDARD_HD720p_25:
		case SDVIDEOSTANDARD_HD720p_2997:
		case SDVIDEOSTANDARD_HD720p_30:
		case SDVIDEOSTANDARD_HD720p_50:
		case SDVIDEOSTANDARD_HD720p_5994:
		case SDVIDEOSTANDARD_HD720p_60:
			return SDVIDEOCLASS_HD720p;

		case SDVIDEOSTANDARD_HD1080p_2398:
		case SDVIDEOSTANDARD_HD1080p_24:
		case SDVIDEOSTANDARD_HD1080p_25:
		case SDVIDEOSTANDARD_HD1080p_2997:
		case SDVIDEOSTANDARD_HD1080p_30:
			return SDVIDEOCLASS_HD1080p;

		case SDVIDEOSTANDARD_HD1080psf_2398:
		case SDVIDEOSTANDARD_HD1080psf_24:
		case SDVIDEOSTANDARD_HD1080psf_25:
		case SDVIDEOSTANDARD_HD1080psf_2997:
		case SDVIDEOSTANDARD_HD1080psf_30:
			return SDVIDEOCLASS_HD1080psf;

		case SDVIDEOSTANDARD_HD1080P_4796:
		case SDVIDEOSTANDARD_HD1080P_48:
		case SDVIDEOSTANDARD_HD1080P_50:
		case SDVIDEOSTANDARD_HD1080P_5994:
		case SDVIDEOSTANDARD_HD1080P_60:
			return SDVIDEOCLASS_HD1080P;

		case SDVIDEOSTANDARD_2K1080P_2398:
		case SDVIDEOSTANDARD_2K1080P_24:
		case SDVIDEOSTANDARD_2K1080P_25:
		case SDVIDEOSTANDARD_2K1080P_2997:
		case SDVIDEOSTANDARD_2K1080P_30:
		case SDVIDEOSTANDARD_2K1080P_4796:
		case SDVIDEOSTANDARD_2K1080P_48:
		case SDVIDEOSTANDARD_2K1080P_50:
		case SDVIDEOSTANDARD_2K1080P_5994:
		case SDVIDEOSTANDARD_2K1080P_60:
			return SDVIDEOCLASS_2K1080P;

		case SDVIDEOSTANDARD_2K1080Psf_2398:
		case SDVIDEOSTANDARD_2K1080Psf_24:
		case SDVIDEOSTANDARD_2K1080Psf_25:
		case SDVIDEOSTANDARD_2K1080Psf_2997:
		case SDVIDEOSTANDARD_2K1080Psf_30:
			return SDVIDEOCLASS_2K1080Psf;

		case SDVIDEOSTANDARD_2K1556P_2398:
		case SDVIDEOSTANDARD_2K1556P_24:
			return SDVIDEOCLASS_2K1556P;

		case SDVIDEOSTANDARD_2K1556Psf_2398:
		case SDVIDEOSTANDARD_2K1556Psf_24:
			return SDVIDEOCLASS_2K1556Psf;

		case SDVIDEOSTANDARD_4K_3840P_2398:
		case SDVIDEOSTANDARD_4K_3840P_24:
		case SDVIDEOSTANDARD_4K_3840P_25:
		case SDVIDEOSTANDARD_4K_3840P_2997:
		case SDVIDEOSTANDARD_4K_3840P_30:
		case SDVIDEOSTANDARD_4K_3840P_4796:
		case SDVIDEOSTANDARD_4K_3840P_48:
		case SDVIDEOSTANDARD_4K_3840P_50:
		case SDVIDEOSTANDARD_4K_3840P_5994:
		case SDVIDEOSTANDARD_4K_3840P_60:
			return SDVIDEOCLASS_4K3840P;

		case SDVIDEOSTANDARD_4K_3840Psf_2398:
		case SDVIDEOSTANDARD_4K_3840Psf_24:
		case SDVIDEOSTANDARD_4K_3840Psf_25:
		case SDVIDEOSTANDARD_4K_3840Psf_2997:
		case SDVIDEOSTANDARD_4K_3840Psf_30:
			return SDVIDEOCLASS_4K3840Psf;

		case SDVIDEOSTANDARD_4K_4096P_2398:
		case SDVIDEOSTANDARD_4K_4096P_24:
		case SDVIDEOSTANDARD_4K_4096P_25:
		case SDVIDEOSTANDARD_4K_4096P_2997:
		case SDVIDEOSTANDARD_4K_4096P_30:
		case SDVIDEOSTANDARD_4K_4096P_4796:
		case SDVIDEOSTANDARD_4K_4096P_48:
		case SDVIDEOSTANDARD_4K_4096P_50:
		case SDVIDEOSTANDARD_4K_4096P_5994:
		case SDVIDEOSTANDARD_4K_4096P_60:
			return SDVIDEOCLASS_4K4096P;

		case SDVIDEOSTANDARD_4K_4096Psf_2398:
		case SDVIDEOSTANDARD_4K_4096Psf_24:
		case SDVIDEOSTANDARD_4K_4096Psf_25:
		case SDVIDEOSTANDARD_4K_4096Psf_2997:
		case SDVIDEOSTANDARD_4K_4096Psf_30:
			return SDVIDEOCLASS_4K4096Psf;

		case SDVIDEOSTANDARD_25_I:
		case SDVIDEOSTANDARD_2997_I:
		case SDVIDEOSTANDARD_30_I:
			return SDVIDEOCLASS_I_RateScale;

		case SDVIDEOSTANDARD_2398_P:
		case SDVIDEOSTANDARD_24_P:
		case SDVIDEOSTANDARD_25_P:
		case SDVIDEOSTANDARD_2997_P:
		case SDVIDEOSTANDARD_30_P:
		case SDVIDEOSTANDARD_4796_P:
		case SDVIDEOSTANDARD_48_P:
		case SDVIDEOSTANDARD_50_P:
		case SDVIDEOSTANDARD_5994_P:
		case SDVIDEOSTANDARD_60_P:
			return SDVIDEOCLASS_P_RateScale;

		case SDVIDEOSTANDARD_2398_Psf:
		case SDVIDEOSTANDARD_24_Psf:
		case SDVIDEOSTANDARD_25_Psf:
		case SDVIDEOSTANDARD_2997_Psf:
		case SDVIDEOSTANDARD_30_Psf:
			return SDVIDEOCLASS_Psf_RateScale;
	}
	return SDVIDEOCLASS_UNKNOW;
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

#define c4796FRAMES_FIELD_RATE		96000		// the frequency of the 47.96 field.
#define	c4796FRAMES_FRAME_RATE		48000		// the frequency of the 47.96 frame.
#define c4796FRAMES_SCALE			1001

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

#define cNANO4796_NUM				1251250
#define cNANO4796_DENOM				3

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
			dwRate = c2398FRAMES_FRAME_RATE;
			dwScale = c2398FRAMES_SCALE;
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
			dwRate = c24FRAMES_FRAME_RATE;
			dwScale = c24FRAMES_SCALE;
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
			dwRate = c25FRAMES_FRAME_RATE;
			dwScale = c25FRAMES_SCALE;
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
			dwRate = c2997FRAME_FRAME_RATE;
			dwScale = c2997FRAME_SCALE;
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
			dwRate = c30FRAMES_FRAME_RATE;
			dwScale = c30FRAMES_SCALE;
			break;
		case SDVIDEOSTANDARD_HD1080P_4796:
		case SDVIDEOSTANDARD_2K1080P_4796:
		case SDVIDEOSTANDARD_4K_3840P_4796:
		case SDVIDEOSTANDARD_4K_4096P_4796:
		case SDVIDEOSTANDARD_4796_P:
			dwRate = c4796FRAMES_FRAME_RATE;
			dwScale = c4796FRAMES_SCALE;
			break;
		case SDVIDEOSTANDARD_HD1080P_48:
		case SDVIDEOSTANDARD_2K1080P_48:
		case SDVIDEOSTANDARD_4K_3840P_48:
		case SDVIDEOSTANDARD_4K_4096P_48:
		case SDVIDEOSTANDARD_48_P:
			dwRate = c48FRAMES_FRAME_RATE;
			dwScale = c48FRAMES_SCALE;
			break;
		case SDVIDEOSTANDARD_HD720p_50:
		case SDVIDEOSTANDARD_HD1080P_50:
		case SDVIDEOSTANDARD_2K1080P_50:
		case SDVIDEOSTANDARD_4K_3840P_50:
		case SDVIDEOSTANDARD_4K_4096P_50:
		case SDVIDEOSTANDARD_50_P:
			dwRate = c50FRAMES_FRAME_RATE;
			dwScale = c50FRAMES_SCALE;
			break;
		case SDVIDEOSTANDARD_HD720p_5994:
		case SDVIDEOSTANDARD_HD1080P_5994:
		case SDVIDEOSTANDARD_2K1080P_5994:
		case SDVIDEOSTANDARD_4K_3840P_5994:
		case SDVIDEOSTANDARD_4K_4096P_5994:
		case SDVIDEOSTANDARD_5994_P:
			dwRate = c5994FRAMES_FRAME_RATE;
			dwScale = c5994FRAMES_SCALE;
			break;
		case SDVIDEOSTANDARD_HD720p_60:
		case SDVIDEOSTANDARD_HD1080P_60:
		case SDVIDEOSTANDARD_2K1080P_60:
		case SDVIDEOSTANDARD_4K_3840P_60:
		case SDVIDEOSTANDARD_4K_4096P_60:
		case SDVIDEOSTANDARD_60_P:
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
SD_INLINE	SD_VIDEO_STANDARD	_GetStandardRateScale(SD_UINT32 dwRate, SD_UINT32 dwScale, SD_VIDEO_CLASS enumVideoClass)
{
	if (dwRate*c2398FRAMES_SCALE == dwScale*c2398FRAMES_FRAME_RATE) 
	{
		if (enumVideoClass == SDVIDEOCLASS_HD720p)
			return SDVIDEOSTANDARD_HD720p_2398;
		else if (enumVideoClass == SDVIDEOCLASS_HD1080p)
			return SDVIDEOSTANDARD_HD1080p_2398;
		else if (enumVideoClass == SDVIDEOCLASS_HD1080psf)
			return SDVIDEOSTANDARD_HD1080psf_2398;
		else if (enumVideoClass == SDVIDEOCLASS_2K1080P)
			return SDVIDEOSTANDARD_2K1080P_2398;
		else if (enumVideoClass == SDVIDEOCLASS_2K1080Psf)
			return SDVIDEOSTANDARD_2K1080Psf_2398;
		else if (enumVideoClass == SDVIDEOCLASS_2K1556P)
			return SDVIDEOSTANDARD_2K1556P_2398;
		else if (enumVideoClass == SDVIDEOCLASS_2K1556Psf)
			return SDVIDEOSTANDARD_2K1556Psf_2398;
		else if (enumVideoClass == SDVIDEOCLASS_4K3840P)
			return SDVIDEOSTANDARD_4K_3840P_2398;
		else if (enumVideoClass == SDVIDEOCLASS_4K3840Psf)
			return SDVIDEOSTANDARD_4K_3840Psf_2398;
		else if (enumVideoClass == SDVIDEOCLASS_4K4096P)
			return SDVIDEOSTANDARD_4K_4096P_2398;
		else if (enumVideoClass == SDVIDEOCLASS_4K4096Psf)
			return SDVIDEOSTANDARD_4K_4096Psf_2398;
		else if (enumVideoClass == SDVIDEOCLASS_P_RateScale)
			return SDVIDEOSTANDARD_2398_P;
		else if (enumVideoClass == SDVIDEOCLASS_Psf_RateScale)
			return SDVIDEOSTANDARD_2398_Psf;
	} 
	else if (dwRate*c24FRAMES_SCALE == dwScale*c24FRAMES_FRAME_RATE) 
	{
		if (enumVideoClass == SDVIDEOCLASS_HD720p)
			return SDVIDEOSTANDARD_HD720p_24;
		else if (enumVideoClass == SDVIDEOCLASS_HD1080p)
			return SDVIDEOSTANDARD_HD1080p_24;
		else if (enumVideoClass == SDVIDEOCLASS_HD1080psf)
			return SDVIDEOSTANDARD_HD1080psf_24;
		else if (enumVideoClass == SDVIDEOCLASS_2K1080P)
			return SDVIDEOSTANDARD_2K1080P_24;
		else if (enumVideoClass == SDVIDEOCLASS_2K1080Psf)
			return SDVIDEOSTANDARD_2K1080Psf_24;
		else if (enumVideoClass == SDVIDEOCLASS_2K1556P)
			return SDVIDEOSTANDARD_2K1556P_24;
		else if (enumVideoClass == SDVIDEOCLASS_2K1556Psf)
			return SDVIDEOSTANDARD_2K1556Psf_24;
		else if (enumVideoClass == SDVIDEOCLASS_4K3840P)
			return SDVIDEOSTANDARD_4K_3840P_24;
		else if (enumVideoClass == SDVIDEOCLASS_4K3840Psf)
			return SDVIDEOSTANDARD_4K_3840Psf_24;
		else if (enumVideoClass == SDVIDEOCLASS_4K4096P)
			return SDVIDEOSTANDARD_4K_4096P_24;
		else if (enumVideoClass == SDVIDEOCLASS_4K4096Psf)
			return SDVIDEOSTANDARD_4K_4096Psf_24;
		else if (enumVideoClass == SDVIDEOCLASS_P_RateScale)
			return SDVIDEOSTANDARD_24_P;
		else if (enumVideoClass == SDVIDEOCLASS_Psf_RateScale)
			return SDVIDEOSTANDARD_24_Psf;
	} 
	else if (dwRate*c25FRAMES_SCALE == dwScale*c25FRAMES_FRAME_RATE) 
	{
		if (enumVideoClass == SDVIDEOCLASS_SD)
			return SDVIDEOSTANDARD_PAL;
		else if (enumVideoClass == SDVIDEOCLASS_HD1080i)
			return SDVIDEOSTANDARD_HD1080i_25;
		else if (enumVideoClass == SDVIDEOCLASS_HD720p)
			return SDVIDEOSTANDARD_HD720p_25;
		else if (enumVideoClass == SDVIDEOCLASS_HD1080p)
			return SDVIDEOSTANDARD_HD1080p_25;
		else if (enumVideoClass == SDVIDEOCLASS_HD1080psf)
			return SDVIDEOSTANDARD_HD1080psf_25;
		else if (enumVideoClass == SDVIDEOCLASS_2K1080P)
			return SDVIDEOSTANDARD_2K1080P_25;
		else if (enumVideoClass == SDVIDEOCLASS_2K1080Psf)
			return SDVIDEOSTANDARD_2K1080Psf_25;
		else if (enumVideoClass == SDVIDEOCLASS_4K3840P)
			return SDVIDEOSTANDARD_4K_3840P_25;
		else if (enumVideoClass == SDVIDEOCLASS_4K3840Psf)
			return SDVIDEOSTANDARD_4K_3840Psf_25;
		else if (enumVideoClass == SDVIDEOCLASS_4K4096P)
			return SDVIDEOSTANDARD_4K_4096P_25;
		else if (enumVideoClass == SDVIDEOCLASS_4K4096Psf)
			return SDVIDEOSTANDARD_4K_4096Psf_25;
		else if (enumVideoClass == SDVIDEOCLASS_I_RateScale)
			return SDVIDEOSTANDARD_25_I;
		else if (enumVideoClass == SDVIDEOCLASS_P_RateScale)
			return SDVIDEOSTANDARD_25_P;
		else if (enumVideoClass == SDVIDEOCLASS_Psf_RateScale)
			return SDVIDEOSTANDARD_25_Psf;
	} 
	else if (dwRate*c2997FRAME_SCALE == dwScale*c2997FRAME_FRAME_RATE) 
	{
		if (enumVideoClass == SDVIDEOCLASS_SD)
			return SDVIDEOSTANDARD_NTSC2997;
		else if (enumVideoClass == SDVIDEOCLASS_HD1080i)
			return SDVIDEOSTANDARD_HD1080i_2997;
		else if (enumVideoClass == SDVIDEOCLASS_HD720p)
			return SDVIDEOSTANDARD_HD720p_2997;
		else if (enumVideoClass == SDVIDEOCLASS_HD1080p)
			return SDVIDEOSTANDARD_HD1080p_2997;
		else if (enumVideoClass == SDVIDEOCLASS_HD1080psf)
			return SDVIDEOSTANDARD_HD1080psf_2997;
		else if (enumVideoClass == SDVIDEOCLASS_2K1080P)
			return SDVIDEOSTANDARD_2K1080P_2997;
		else if (enumVideoClass == SDVIDEOCLASS_2K1080Psf)
			return SDVIDEOSTANDARD_2K1080Psf_2997;
		else if (enumVideoClass == SDVIDEOCLASS_4K3840P)
			return SDVIDEOSTANDARD_4K_3840P_2997;
		else if (enumVideoClass == SDVIDEOCLASS_4K3840Psf)
			return SDVIDEOSTANDARD_4K_3840Psf_2997;
		else if (enumVideoClass == SDVIDEOCLASS_4K4096P)
			return SDVIDEOSTANDARD_4K_4096P_2997;
		else if (enumVideoClass == SDVIDEOCLASS_4K4096Psf)
			return SDVIDEOSTANDARD_4K_4096Psf_2997;
		else if (enumVideoClass == SDVIDEOCLASS_I_RateScale)
			return SDVIDEOSTANDARD_2997_I;
		else if (enumVideoClass == SDVIDEOCLASS_P_RateScale)
			return SDVIDEOSTANDARD_2997_P;
		else if (enumVideoClass == SDVIDEOCLASS_Psf_RateScale)
			return SDVIDEOSTANDARD_2997_Psf;
	} 
	else if (dwRate*c30FRAMES_SCALE == dwScale*c30FRAMES_FRAME_RATE) 
	{
		if (enumVideoClass == SDVIDEOCLASS_SD)
			return SDVIDEOSTANDARD_NTSC30;
		else if (enumVideoClass == SDVIDEOCLASS_HD1080i)
			return SDVIDEOSTANDARD_HD1080i_30;
		else if (enumVideoClass == SDVIDEOCLASS_HD720p)
			return SDVIDEOSTANDARD_HD720p_30;
		else if (enumVideoClass == SDVIDEOCLASS_HD1080p)
			return SDVIDEOSTANDARD_HD1080p_30;
		else if (enumVideoClass == SDVIDEOCLASS_HD1080psf)
			return SDVIDEOSTANDARD_HD1080psf_30;
		else if (enumVideoClass == SDVIDEOCLASS_2K1080P)
			return SDVIDEOSTANDARD_2K1080P_30;
		else if (enumVideoClass == SDVIDEOCLASS_2K1080Psf)
			return SDVIDEOSTANDARD_2K1080Psf_30;
		else if (enumVideoClass == SDVIDEOCLASS_4K3840P)
			return SDVIDEOSTANDARD_4K_3840P_30;
		else if (enumVideoClass == SDVIDEOCLASS_4K3840Psf)
			return SDVIDEOSTANDARD_4K_3840Psf_30;
		else if (enumVideoClass == SDVIDEOCLASS_4K4096P)
			return SDVIDEOSTANDARD_4K_4096P_30;
		else if (enumVideoClass == SDVIDEOCLASS_4K4096Psf)
			return SDVIDEOSTANDARD_4K_4096Psf_30;
		else if (enumVideoClass == SDVIDEOCLASS_I_RateScale)
			return SDVIDEOSTANDARD_30_I;
		else if (enumVideoClass == SDVIDEOCLASS_P_RateScale)
			return SDVIDEOSTANDARD_30_P;
		else if (enumVideoClass == SDVIDEOCLASS_Psf_RateScale)
			return SDVIDEOSTANDARD_30_Psf;
	} 
	else if (dwRate*c4796FRAMES_SCALE == dwScale*c4796FRAMES_FRAME_RATE) 
	{
		if (enumVideoClass == SDVIDEOCLASS_HD1080P)
			return SDVIDEOSTANDARD_HD1080P_4796;
		else if (enumVideoClass == SDVIDEOCLASS_2K1080P)
			return SDVIDEOSTANDARD_2K1080P_4796;
		else if (enumVideoClass == SDVIDEOCLASS_4K3840P)
			return SDVIDEOSTANDARD_4K_3840P_4796;
		else if (enumVideoClass == SDVIDEOCLASS_4K4096P)
			return SDVIDEOSTANDARD_4K_4096P_4796;
		else if (enumVideoClass == SDVIDEOCLASS_P_RateScale)
			return SDVIDEOSTANDARD_48_P;
	} 
	else if (dwRate*c48FRAMES_SCALE == dwScale*c48FRAMES_FRAME_RATE) 
	{
		if (enumVideoClass == SDVIDEOCLASS_HD1080P)
			return SDVIDEOSTANDARD_HD1080P_48;
		else if (enumVideoClass == SDVIDEOCLASS_2K1080P)
			return SDVIDEOSTANDARD_2K1080P_48;
		else if (enumVideoClass == SDVIDEOCLASS_4K3840P)
			return SDVIDEOSTANDARD_4K_3840P_48;
		else if (enumVideoClass == SDVIDEOCLASS_4K4096P)
			return SDVIDEOSTANDARD_4K_4096P_48;
		else if (enumVideoClass == SDVIDEOCLASS_P_RateScale)
			return SDVIDEOSTANDARD_48_P;
	} 
	else if (dwRate*c50FRAMES_SCALE == dwScale*c50FRAMES_FRAME_RATE) 
	{
		if (enumVideoClass == SDVIDEOCLASS_HD720p)
			return SDVIDEOSTANDARD_HD720p_50;
		else if (enumVideoClass == SDVIDEOCLASS_HD1080P)
			return SDVIDEOSTANDARD_HD1080P_50;
		else if (enumVideoClass == SDVIDEOCLASS_2K1080P)
			return SDVIDEOSTANDARD_2K1080P_50;
		else if (enumVideoClass == SDVIDEOCLASS_4K3840P)
			return SDVIDEOSTANDARD_4K_3840P_50;
		else if (enumVideoClass == SDVIDEOCLASS_4K4096P)
			return SDVIDEOSTANDARD_4K_4096P_50;
		else if (enumVideoClass == SDVIDEOCLASS_P_RateScale)
			return SDVIDEOSTANDARD_50_P;
	} 
	else if (dwRate*c5994FRAMES_SCALE == dwScale*c5994FRAMES_FRAME_RATE) 
	{
		if (enumVideoClass == SDVIDEOCLASS_HD720p)
			return SDVIDEOSTANDARD_HD720p_5994;
		else if (enumVideoClass == SDVIDEOCLASS_HD1080P)
			return SDVIDEOSTANDARD_HD1080P_5994;
		else if (enumVideoClass == SDVIDEOCLASS_2K1080P)
			return SDVIDEOSTANDARD_2K1080P_5994;
		else if (enumVideoClass == SDVIDEOCLASS_4K3840P)
			return SDVIDEOSTANDARD_4K_3840P_5994;
		else if (enumVideoClass == SDVIDEOCLASS_4K4096P)
			return SDVIDEOSTANDARD_4K_4096P_5994;
		else if (enumVideoClass == SDVIDEOCLASS_P_RateScale)
			return SDVIDEOSTANDARD_5994_P;
	}
	else if (dwRate*c60FRAMES_SCALE == dwScale*c60FRAMES_FRAME_RATE) 
	{
		if (enumVideoClass == SDVIDEOCLASS_HD720p)
			return SDVIDEOSTANDARD_HD720p_60;
		else if (enumVideoClass == SDVIDEOCLASS_HD1080P)
			return SDVIDEOSTANDARD_HD1080P_60;
		else if (enumVideoClass == SDVIDEOCLASS_2K1080P)
			return SDVIDEOSTANDARD_2K1080P_60;
		else if (enumVideoClass == SDVIDEOCLASS_4K3840P)
			return SDVIDEOSTANDARD_4K_3840P_60;
		else if (enumVideoClass == SDVIDEOCLASS_4K4096P)
			return SDVIDEOSTANDARD_4K_4096P_60;
		else if (enumVideoClass == SDVIDEOCLASS_P_RateScale)
			return SDVIDEOSTANDARD_60_P;
	}

	return SDVIDEOSTANDARD_UNKNOW;
};

SD_INLINE	SD_VOID	_GetStandardNumDenom(SD_VIDEO_STANDARD enumVideoStandard, SD_UINT32 &dwNUM, SD_UINT32 &dwDENOM)
{
	dwNUM = cNANO25_NUM;
	dwDENOM = cNANO25_DENOM;
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
			dwNUM = cNANO2398_NUM;
			dwDENOM = cNANO2398_DENOM;
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
			dwNUM = cNANO24_NUM;
			dwDENOM = cNANO24_DENOM;
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
			dwNUM = cNANO25_NUM;
			dwDENOM = cNANO25_DENOM;
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
			dwNUM = cNANO2997_NUM;
			dwDENOM = cNANO2997_DENOM;
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
			dwNUM = cNANO30_NUM;
			dwDENOM = cNANO30_DENOM;
			break;
		case SDVIDEOSTANDARD_HD1080P_4796:	
		case SDVIDEOSTANDARD_2K1080P_4796:
		case SDVIDEOSTANDARD_4K_3840P_4796:
		case SDVIDEOSTANDARD_4K_4096P_4796:
		case SDVIDEOSTANDARD_4796_P:
			dwNUM = cNANO4796_NUM;
			dwDENOM = cNANO4796_DENOM;
			break;
		case SDVIDEOSTANDARD_HD1080P_48:	
		case SDVIDEOSTANDARD_2K1080P_48:
		case SDVIDEOSTANDARD_4K_3840P_48:
		case SDVIDEOSTANDARD_4K_4096P_48:
		case SDVIDEOSTANDARD_48_P:
			dwNUM = cNANO48_NUM;
			dwDENOM = cNANO48_DENOM;
			break;
		case SDVIDEOSTANDARD_HD720p_50:
		case SDVIDEOSTANDARD_HD1080P_50:
		case SDVIDEOSTANDARD_2K1080P_50:
		case SDVIDEOSTANDARD_4K_3840P_50:
		case SDVIDEOSTANDARD_4K_4096P_50:
		case SDVIDEOSTANDARD_50_P:
			dwNUM = cNANO50_NUM;
			dwDENOM = cNANO50_DENOM;
			break;
		case SDVIDEOSTANDARD_HD720p_5994:
		case SDVIDEOSTANDARD_HD1080P_5994:
		case SDVIDEOSTANDARD_2K1080P_5994:
		case SDVIDEOSTANDARD_4K_3840P_5994:
		case SDVIDEOSTANDARD_4K_4096P_5994:
		case SDVIDEOSTANDARD_5994_P:
			dwNUM = cNANO5994_NUM;
			dwDENOM = cNANO5994_DENOM;
			break;
		case SDVIDEOSTANDARD_HD720p_60:
		case SDVIDEOSTANDARD_HD1080P_60:
		case SDVIDEOSTANDARD_2K1080P_60:
		case SDVIDEOSTANDARD_4K_3840P_60:
		case SDVIDEOSTANDARD_4K_4096P_60:
		case SDVIDEOSTANDARD_60_P:
			dwNUM = cNANO60_NUM;
			dwDENOM = cNANO60_DENOM;
			break;
	}
};

typedef SD_INT64 SD_REFERENCETIME;			//以100ns为单位的64位整型数,目的是用整数表达帧的时间度量

//依据视频制式转换场数至参考时间度量单位
SD_INLINE SD_REFERENCETIME	_FieldToRT(SD_UINT32 dwFieldCount, SD_VIDEO_STANDARD enumVideoStandard)
{
	SD_UINT32 dwNUM, dwDENOM;
	_GetStandardNumDenom(enumVideoStandard, dwNUM, dwDENOM);
	return (((SD_REFERENCETIME)dwFieldCount * (SD_REFERENCETIME)dwNUM) / (SD_REFERENCETIME)dwDENOM);
};

//依据帧率转换场数至参考时间度量单位
SD_INLINE SD_REFERENCETIME	_FieldToRT(SD_UINT32 dwFieldCount, SD_UINT32 dwRate, SD_UINT32 dwScale)
{
	return (((SD_REFERENCETIME)dwFieldCount * 10000000 * (SD_REFERENCETIME)dwScale) / (2 * (SD_REFERENCETIME)dwRate));
};

//依据视频制式转换帧数至参考时间度量单位
SD_INLINE SD_REFERENCETIME	_FrameToRT(SD_UINT32 dwFrameCount, SD_VIDEO_STANDARD enumVideoStandard)
{
	return _FieldToRT(2*dwFrameCount, enumVideoStandard);
};

//依据帧率转换帧数至参考时间度量单位
SD_INLINE SD_REFERENCETIME	_FrameToRT(SD_UINT32 dwFrameCount, SD_UINT32 dwRate, SD_UINT32 dwScale)
{
	return _FieldToRT(2*dwFrameCount, dwRate, dwScale);
};

//依据视频制式转换参考时间度量单位至场数
SD_INLINE SD_UINT32 _RTToField(SD_REFERENCETIME rt, SD_VIDEO_STANDARD enumVideoStandard)
{
	SD_UINT32 dwNUM, dwDENOM;
	_GetStandardNumDenom(enumVideoStandard, dwNUM, dwDENOM);
	if (rt < 0)
		return (SD_UINT32)((rt * (SD_REFERENCETIME)dwDENOM - ((SD_REFERENCETIME)dwNUM / 2)) / (SD_REFERENCETIME)dwNUM);
	else
		return (SD_UINT32)((rt * (SD_REFERENCETIME)dwDENOM + ((SD_REFERENCETIME)dwNUM / 2)) / (SD_REFERENCETIME)dwNUM);
};

//依据帧率转换参考时间度量单位至场数
SD_INLINE SD_UINT32 _RTToField(SD_REFERENCETIME rt, SD_UINT32 dwRate, SD_UINT32 dwScale)
{
	return (SD_UINT32)(rt * (2 * (SD_REFERENCETIME)dwRate) / (SD_REFERENCETIME)dwScale / 10000000);
};

//依据视频制式转换参考时间度量单位至帧数
SD_INLINE SD_UINT32 _RTToFrame(SD_REFERENCETIME rt, SD_VIDEO_STANDARD enumVideoStandard)
{
	return _RTToField(rt, enumVideoStandard)/2;
};

//依据帧率转换参考时间度量单位至帧数
SD_INLINE SD_UINT32 _RTToFrame(SD_REFERENCETIME rt, SD_UINT32 dwRate, SD_UINT32 dwScale)
{
	return _RTToField(rt, dwRate, dwScale)/2;
};


//依据视频制式转换场数至浮点型秒数
SD_INLINE SD_DOUBLE _FieldToSec(SD_UINT32 dwFieldCount, SD_VIDEO_STANDARD enumVideoStandard)
{
	SD_UINT32	dwRate, dwScale;
	_GetStandardRateScale(enumVideoStandard, dwRate, dwScale);
	return ((SD_DOUBLE)dwFieldCount * (SD_DOUBLE)dwScale / (2.0*(SD_DOUBLE)dwRate));
};

//依据帧率转换场数至浮点型秒数
SD_INLINE SD_DOUBLE _FieldToSec(SD_UINT32 dwFieldCount, SD_UINT32 dwRate, SD_UINT32 dwScale)
{
	return ((SD_DOUBLE)dwFieldCount * (SD_DOUBLE)dwScale / (2.0*(SD_DOUBLE)dwRate));
};

//依据视频制式转换帧数至浮点型秒数
SD_INLINE SD_DOUBLE _FrameToSec(SD_UINT32 dwFrameCount, SD_VIDEO_STANDARD enumVideoStandard)
{
	SD_UINT32	dwRate, dwScale;
	_GetStandardRateScale(enumVideoStandard, dwRate, dwScale);
	return ((SD_DOUBLE)dwFrameCount * (SD_DOUBLE)dwScale / (SD_DOUBLE)dwRate);
};

//依据帧率转换帧数至浮点型秒数
SD_INLINE SD_DOUBLE _FrameToSec(SD_UINT32 dwFrameCount, SD_UINT32 dwRate, SD_UINT32 dwScale)
{
	return ((SD_DOUBLE)dwFrameCount * (SD_DOUBLE)dwScale / (SD_DOUBLE)dwRate);
};


//依据视频制式转换浮点型秒数至场数
SD_INLINE SD_UINT32 _SecToField(SD_DOUBLE dblSeconds, SD_VIDEO_STANDARD enumVideoStandard)
{
	SD_UINT32	dwRate, dwScale;
	_GetStandardRateScale(enumVideoStandard, dwRate, dwScale);

	// Add the 0.5 to account for any truncation errors
	if (dblSeconds < 0)
		return SD_UINT32(-0.5 + ((dblSeconds * 2.0 * (SD_DOUBLE)dwRate) / (SD_DOUBLE)dwScale));
	else
		return SD_UINT32(0.5 + ((dblSeconds * 2.0 * (SD_DOUBLE)dwRate) / (SD_DOUBLE)dwScale));
};

//依据帧率转换浮点型秒数至场数
SD_INLINE SD_UINT32 _SecToField(SD_DOUBLE dblSeconds, SD_UINT32 dwRate, SD_UINT32 dwScale)
{
	if (dblSeconds < 0)
		return SD_UINT32(-0.5 + ((dblSeconds * 2.0 * (SD_DOUBLE)dwRate) / (SD_DOUBLE)dwScale));
	else
		return SD_UINT32(0.5 + ((dblSeconds * 2.0 * (SD_DOUBLE)dwRate) / (SD_DOUBLE)dwScale));
};

//依据视频制式转换浮点型秒数至帧数
SD_INLINE SD_UINT32 _SecToFrame(SD_DOUBLE dblSeconds, SD_VIDEO_STANDARD enumVideoStandard)
{
	SD_UINT32	dwRate, dwScale;
	_GetStandardRateScale(enumVideoStandard, dwRate, dwScale);

	// Add the 0.5 to account for any truncation errors
	if (dblSeconds < 0)
		return SD_UINT32(-0.5 + ((dblSeconds * (SD_DOUBLE)dwRate) / (SD_DOUBLE)dwScale));
	else
		return SD_UINT32(0.5 + ((dblSeconds * (SD_DOUBLE)dwRate) / (SD_DOUBLE)dwScale));
};

//依据帧率转换浮点型秒数至帧数
SD_INLINE SD_UINT32 _SecToFrame(SD_DOUBLE dblSeconds, SD_UINT32 dwRate, SD_UINT32 dwScale)
{
	if (dblSeconds < 0)
		return SD_UINT32(-0.5 + ((dblSeconds * (SD_DOUBLE)dwRate) / (SD_DOUBLE)dwScale));
	else
		return SD_UINT32(0.5 + ((dblSeconds * (SD_DOUBLE)dwRate) / (SD_DOUBLE)dwScale));
};

//依据视频制式转换音频采样数至帧数
SD_INLINE SD_UINT32 GetAudioLengthInFrame(SD_UINT64 llAudioSamples, SD_UINT32 dwSamplesPerSec, SD_VIDEO_STANDARD enumVideoStandard)
{
	return _SecToFrame((SD_DOUBLE)llAudioSamples/(SD_DOUBLE)dwSamplesPerSec, enumVideoStandard);
};

//依据帧率转换音频采样数至帧数
SD_INLINE SD_UINT32 GetAudioLengthInFrame(SD_UINT64 llAudioSamples, SD_UINT32 dwSamplesPerSec, SD_UINT32 dwRate, SD_UINT32 dwScale)
{
	return _SecToFrame((SD_DOUBLE)llAudioSamples/(SD_DOUBLE)dwSamplesPerSec, dwRate, dwScale);
};

//转换音频采样数至浮点型秒数
SD_INLINE SD_DOUBLE GetAudioTimeInSec(SD_UINT64 llAudioSamples, SD_UINT32 dwSamplesPerSec)
{
	return (SD_DOUBLE)llAudioSamples/(SD_DOUBLE)dwSamplesPerSec;
};

//依据视频制式转换帧数至音频采样数
SD_INLINE SD_UINT64 GetAudioSamplesFromFrame(SD_UINT32 dwFrameCount, SD_UINT32 dwSamplesPerSec, SD_VIDEO_STANDARD enumVideoStandard)
{
	return (SD_UINT64)(_FrameToSec(dwFrameCount, enumVideoStandard) * (SD_DOUBLE)dwSamplesPerSec + 0.5);
};

//依据帧率转换帧数至音频采样数
SD_INLINE SD_UINT64 GetAudioSamplesFromFrame(SD_UINT32 dwFrameCount, SD_UINT32 dwSamplesPerSec, SD_UINT32 dwRate, SD_UINT32 dwScale)
{
	return (SD_UINT64)(_FrameToSec(dwFrameCount, dwRate, dwScale) * (SD_DOUBLE)dwSamplesPerSec + 0.5);
};

//转换浮点型秒数至音频采样数
SD_INLINE SD_UINT64 GetAudioSamplesFromSec(SD_DOUBLE dblSeconds, SD_UINT32 dwSamplesPerSec)
{
	return (SD_UINT64)(dblSeconds*(SD_DOUBLE)dwSamplesPerSec+0.5);
};

#define FR_HOUR_24				86400L		// frames per hour in 24 frame mode
#define FR_HOUR_2398_DROP		86314L		// frames per hour in drop 23.98 frame mode
#define FR_TENMIN_2398_DROP		14387L		// frames per ten minutes in drop 23.98 frame mode
#define FR_MINUTE_2398_DROP		1439L		// frame per minute in drop 23.98 frame mode
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
#define FR_HOUR_4796_DROP		172627L		// frames per hour in drop 47.96 frame mode
#define FR_TENMIN_4796_DROP		28771L		// frames per ten minutes in drop 47.96 frame mode
#define FR_MINUTE_4796_DROP		2877L		// frame per minute in drop 47.96 frame mode
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
SD_INLINE SD_UINT32	_FrameToIOPoint(SD_UINT32 dwFrameCount, SD_UINT32 dwRate, SD_UINT32 dwScale)
{
	SD_UINT32	dwReste, hour, minute;

	if (dwRate*c2398FRAMES_SCALE == dwScale*c2398FRAMES_FRAME_RATE) 
	{
/*
		hour = (dwFrameCount/FR_HOUR_24);
		dwReste = (dwFrameCount%FR_HOUR_24);
		minute = (dwReste/FR_MINUTE_24);
		dwReste = (dwReste%FR_MINUTE_24);
		return(((hour<<24)&0xff000000) + ((minute<<16)&0xff0000) + (((dwReste/FR_SECOND_24)<<8)&0xff00) + ((dwReste%FR_SECOND_24)&0xff));
*/
		hour = (dwFrameCount/FR_HOUR_2398_DROP);
		dwReste = (dwFrameCount%FR_HOUR_2398_DROP);
		minute = 10*(dwReste/FR_TENMIN_2398_DROP);
		dwReste = (dwReste%FR_TENMIN_2398_DROP);
		if (dwReste >= FR_MINUTE_2398_DROP) 
		{
			dwReste  -= FR_MINUTE_2398_DROP;
			minute += 1 + (dwReste / FR_MINUTE_2398_DROP);
			dwReste %= FR_MINUTE_2398_DROP;
			dwReste  += 2;
		}
		return(((hour<<24)&0xff000000) + ((minute<<16)&0xff0000) + (((dwReste/FR_SECOND_24)<<8)&0xff00) + ((dwReste%FR_SECOND_24)&0xff));
	} 
	else if (dwRate*c24FRAMES_SCALE == dwScale*c24FRAMES_FRAME_RATE) 
	{
		hour = (dwFrameCount/FR_HOUR_24);
		dwReste = (dwFrameCount%FR_HOUR_24);
		minute = (dwReste/FR_MINUTE_24);
		dwReste = (dwReste%FR_MINUTE_24);
		return(((hour<<24)&0xff000000) + ((minute<<16)&0xff0000) + (((dwReste/FR_SECOND_24)<<8)&0xff00) + ((dwReste%FR_SECOND_24)&0xff));
	} 
	else if (dwRate*c25FRAMES_SCALE == dwScale*c25FRAMES_FRAME_RATE) 
	{
		hour = (dwFrameCount/FR_HOUR_PAL);
		dwReste = (dwFrameCount%FR_HOUR_PAL);
		minute = (dwReste/FR_MINUTE_PAL);
		dwReste = (dwReste%FR_MINUTE_PAL);
		return(((hour<<24)&0xff000000) + ((minute<<16)&0xff0000) + (((dwReste/FR_SECOND_PAL)<<8)&0xff00) + ((dwReste%FR_SECOND_PAL)&0xff));
	} 
	else if (dwRate*c2997FRAME_SCALE == dwScale*c2997FRAME_FRAME_RATE) 
	{
		hour = (dwFrameCount/FR_HOUR_2997_DROP);
		dwReste = (dwFrameCount%FR_HOUR_2997_DROP);
		minute = 10*(dwReste/FR_TENMIN_2997_DROP);
		dwReste = (dwReste%FR_TENMIN_2997_DROP);
		if (dwReste >= FR_MINUTE_2997_ND) 
		{
			dwReste  -= FR_MINUTE_2997_ND;
			minute += 1 + (dwReste / FR_MINUTE_2997_DROP);
			dwReste %= FR_MINUTE_2997_DROP;
			dwReste  += 2;
		}
		return(((hour<<24)&0xff000000) + ((minute<<16)&0xff0000) + (((dwReste/FR_SECOND_2997)<<8)&0xff00) + ((dwReste%FR_SECOND_2997)&0xff));
	} 
	else if (dwRate*c30FRAMES_SCALE == dwScale*c30FRAMES_FRAME_RATE) 
	{
		hour = (dwFrameCount/FR_HOUR_2997_ND);
		dwReste = (dwFrameCount%FR_HOUR_2997_ND);
		minute = (dwReste/FR_MINUTE_2997_ND);
		dwReste = (dwReste%FR_MINUTE_2997_ND);
		return(((hour<<24)&0xff000000) + ((minute<<16)&0xff0000) + (((dwReste/FR_SECOND_2997)<<8)&0xff00) + ((dwReste%FR_SECOND_2997)&0xff));
	} 
	else if (dwRate*c4796FRAMES_SCALE == dwScale*c4796FRAMES_FRAME_RATE) 
	{
		hour = (dwFrameCount/FR_HOUR_4796_DROP);
		dwReste = (dwFrameCount%FR_HOUR_4796_DROP);
		minute = 10*(dwReste/FR_TENMIN_4796_DROP);
		dwReste = (dwReste%FR_TENMIN_4796_DROP);
		if (dwReste >= FR_MINUTE_4796_DROP) 
		{
			dwReste  -= FR_MINUTE_4796_DROP;
			minute += 1 + (dwReste / FR_MINUTE_4796_DROP);
			dwReste %= FR_MINUTE_4796_DROP;
			dwReste  += 2;
		}
		return(((hour<<24)&0xff000000) + ((minute<<16)&0xff0000) + (((dwReste/FR_SECOND_48)<<8)&0xff00) + ((dwReste%FR_SECOND_48)&0xff));
	} 
	else if (dwRate*c48FRAMES_SCALE == dwScale*c48FRAMES_FRAME_RATE) 
	{
		hour = (dwFrameCount/FR_HOUR_48);
		dwReste = (dwFrameCount%FR_HOUR_48);
		minute = (dwReste/FR_MINUTE_48);
		dwReste = (dwReste%FR_MINUTE_48);
		return(((hour<<24)&0xff000000) + ((minute<<16)&0xff0000) + (((dwReste/FR_SECOND_48)<<8)&0xff00) + ((dwReste%FR_SECOND_48)&0xff));
	} 
	else if (dwRate*c50FRAMES_SCALE == dwScale*c50FRAMES_FRAME_RATE) 
	{
		hour = (dwFrameCount/FR_HOUR_50);
		dwReste = (dwFrameCount%FR_HOUR_50);
		minute = (dwReste/FR_MINUTE_50);
		dwReste = (dwReste%FR_MINUTE_50);
		return(((hour<<24)&0xff000000) + ((minute<<16)&0xff0000) + (((dwReste/FR_SECOND_50)<<8)&0xff00) + ((dwReste%FR_SECOND_50)&0xff));
	} 
	else if (dwRate*c5994FRAMES_SCALE == dwScale*c5994FRAMES_FRAME_RATE) 
	{
		hour = (dwFrameCount/FR_HOUR_5994_DROP);
		dwReste = (dwFrameCount%FR_HOUR_5994_DROP);
		minute = 10*(dwReste/FR_TENMIN_5994_DROP);
		dwReste = (dwReste%FR_TENMIN_5994_DROP);
		if (dwReste >= FR_MINUTE_5994_ND) 
		{
			dwReste  -= FR_MINUTE_5994_ND;
			minute += 1 + (dwReste / FR_MINUTE_5994_DROP);
			dwReste %= FR_MINUTE_5994_DROP;
			dwReste  += 2;
		}
		return(((hour<<24)&0xff000000) + ((minute<<16)&0xff0000) + (((dwReste/FR_SECOND_5994)<<8)&0xff00) + ((dwReste%FR_SECOND_5994)&0xff));
	}
	else if (dwRate*c60FRAMES_SCALE == dwScale*c60FRAMES_FRAME_RATE) 
	{
		hour = (dwFrameCount/FR_HOUR_60);
		dwReste = (dwFrameCount%FR_HOUR_60);
		minute = (dwReste/FR_MINUTE_60);
		dwReste = (dwReste%FR_MINUTE_60);
		return(((hour<<24)&0xff000000) + ((minute<<16)&0xff0000) + (((dwReste/FR_SECOND_60)<<8)&0xff00) + ((dwReste%FR_SECOND_60)&0xff));
	} 
	else
	{
		SD_UINT32	uSecNum;
		hour = (dwFrameCount * dwScale / dwRate / 3600);
		dwReste = dwFrameCount - (hour*3600*dwRate/dwScale);
		minute = (dwReste * dwScale / dwRate / 60);
		dwReste -= (minute*60*dwRate/dwScale);
		uSecNum = dwReste * dwScale / dwRate;
		dwReste -= (uSecNum*dwRate/dwScale);
		return(((hour<<24)&0xff000000) + ((minute<<16)&0xff0000) + ((uSecNum<<8)&0xff00) + (dwReste&0xff));
	}
	return 0;
};

//依据视频制式转换帧数至32位整数, 32位整数的格式是0x(hh-mm-ss-ff)
SD_INLINE SD_UINT32	_FrameToIOPoint(SD_UINT32 dwFrameCount, SD_VIDEO_STANDARD enumVideoStandard)
{
	SD_UINT32	dwRate, dwScale;
	_GetStandardRateScale(enumVideoStandard, dwRate, dwScale);
	return _FrameToIOPoint(dwFrameCount, dwRate, dwScale);
};

//依据帧率转换32位整数至帧数, 32位整数的格式是0x(hh-mm-ss-ff)
SD_INLINE SD_UINT32	_IOPointToFrame(SD_UINT32 ioPoint, SD_UINT32 dwRate, SD_UINT32 dwScale)
{
	int	nhour = ((ioPoint>>24)&0xff);
	int	nminute = ((ioPoint>>16)&0xff);
	int	nsec = ((ioPoint>>8)&0xff);
	int	nframe = (ioPoint&0xff);

	if (dwRate*c2398FRAMES_SCALE == dwScale*c2398FRAMES_FRAME_RATE)
	{
		if ((nminute%10) != 0) 
		{
			if (nsec == 0 && (nframe == 0 || nframe == 1))
				nframe = 2;
		}
		return nhour*FR_HOUR_2398_DROP + (nminute/10)*FR_TENMIN_2398_DROP + (nminute%10)*FR_MINUTE_2398_DROP + nsec*FR_SECOND_24 + nframe;
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
		if ((nminute%10) != 0) 
		{
			if (nsec == 0 && (nframe == 0 || nframe == 1))
				nframe = 2;
		}
		return nhour*FR_HOUR_2997_DROP + (nminute/10)*FR_TENMIN_2997_DROP + (nminute%10)*FR_MINUTE_2997_DROP + nsec*FR_SECOND_2997 + nframe;
	} 
	else if (dwRate*c30FRAMES_SCALE == dwScale*c30FRAMES_FRAME_RATE) 
	{
		return nhour*FR_HOUR_2997_ND + nminute*FR_MINUTE_2997_ND + nsec*FR_SECOND_2997 + nframe;
	} 
	else if (dwRate*c4796FRAMES_SCALE == dwScale*c4796FRAMES_FRAME_RATE) 
	{
		if ((nminute%10) != 0) 
		{
			if (nsec == 0 && (nframe == 0 || nframe == 1))
				nframe = 2;
		}
		return nhour*FR_HOUR_4796_DROP + (nminute/10)*FR_TENMIN_4796_DROP + (nminute%10)*FR_MINUTE_4796_DROP + nsec*FR_SECOND_48 + nframe;
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
		if ((nminute%10) != 0) 
		{
			if (nsec == 0 && (nframe == 0 || nframe == 1))
				nframe = 2;
		}
		return nhour*FR_HOUR_5994_DROP + (nminute/10)*FR_TENMIN_5994_DROP + (nminute%10)*FR_MINUTE_5994_DROP + nsec*FR_SECOND_5994 + nframe;
	}
	else if (dwRate*c60FRAMES_SCALE == dwScale*c60FRAMES_FRAME_RATE) 
	{
		return nhour*FR_HOUR_60 + nminute*FR_MINUTE_60 + nsec*FR_SECOND_60 + nframe;
	} 
	else
	{
		return (nhour*3600*dwRate/dwScale) + (nminute*60*dwRate/dwScale) + (nsec*dwRate/dwScale) + nframe;
	}

	return 0;
};

//依据视频制式转换32位整数至帧数, 32位整数的格式是0x(hh-mm-ss-ff)
SD_INLINE SD_UINT32	_IOPointToFrame(SD_UINT32 ioPoint, SD_VIDEO_STANDARD enumVideoStandard)
{
	SD_UINT32	dwRate, dwScale;
	_GetStandardRateScale(enumVideoStandard, dwRate, dwScale);
	return _IOPointToFrame(ioPoint, dwRate, dwScale);
};

//依据帧率转换帧数至时分秒帧字符串
SD_INLINE SD_VOID	FramesToTimeCodeString(SD_UINT32 dwFrameCount, CSDString &strTimeCode, SD_UINT32 dwRate, SD_UINT32 dwScale)
{
	SD_UINT32	dwReste, hour, minute;

	if (dwRate*c2398FRAMES_SCALE == dwScale*c2398FRAMES_FRAME_RATE) 
	{
		hour = (dwFrameCount/FR_HOUR_2398_DROP);
		dwReste = (dwFrameCount%FR_HOUR_2398_DROP);
		minute = 10*(dwReste/FR_TENMIN_2398_DROP);
		dwReste = (dwReste%FR_TENMIN_2398_DROP);
		if (dwReste >= FR_MINUTE_24) 
		{
			dwReste  -= FR_MINUTE_24;
			minute += 1 + (dwReste / FR_MINUTE_2398_DROP);
			dwReste %= FR_MINUTE_2398_DROP;
			dwReste  += 2;
		}
		strTimeCode.Format(_T("%02d:%02d:%02d;%02d"), hour,minute, (dwReste / FR_SECOND_24), (dwReste % FR_SECOND_24));
	} 
	else if (dwRate*c24FRAMES_SCALE == dwScale*c24FRAMES_FRAME_RATE) 
	{
		hour = (dwFrameCount/FR_HOUR_24);
		dwReste = (dwFrameCount%FR_HOUR_24);
		minute = (dwReste/FR_MINUTE_24);
		dwReste = (dwReste%FR_MINUTE_24);
		strTimeCode.Format(_T("%02d:%02d:%02d:%02d"), hour,minute, (dwReste / FR_SECOND_24), (dwReste % FR_SECOND_24));
	} 
	else if (dwRate*c25FRAMES_SCALE == dwScale*c25FRAMES_FRAME_RATE) 
	{
		hour = (dwFrameCount/FR_HOUR_PAL);
		dwReste = (dwFrameCount%FR_HOUR_PAL);
		minute = (dwReste/FR_MINUTE_PAL);
		dwReste = (dwReste%FR_MINUTE_PAL);
		strTimeCode.Format(_T("%02d:%02d:%02d:%02d"), hour,minute, (dwReste / FR_SECOND_PAL), (dwReste % FR_SECOND_PAL));
	} 
	else if (dwRate*c2997FRAME_SCALE == dwScale*c2997FRAME_FRAME_RATE) 
	{
		hour = (dwFrameCount/FR_HOUR_2997_DROP);
		dwReste = (dwFrameCount%FR_HOUR_2997_DROP);
		minute = 10*(dwReste/FR_TENMIN_2997_DROP);
		dwReste = (dwReste%FR_TENMIN_2997_DROP);
		if (dwReste >= FR_MINUTE_2997_ND) 
		{
			dwReste  -= FR_MINUTE_2997_ND;
			minute += 1 + (dwReste / FR_MINUTE_2997_DROP);
			dwReste %= FR_MINUTE_2997_DROP;
			dwReste  += 2;
		}
		strTimeCode.Format(_T("%02d:%02d:%02d;%02d"), hour,minute, (dwReste / FR_SECOND_2997), (dwReste % FR_SECOND_2997));
	} 
	else if (dwRate*c30FRAMES_SCALE == dwScale*c30FRAMES_FRAME_RATE) 
	{
		hour = (dwFrameCount/FR_HOUR_2997_ND);
		dwReste = (dwFrameCount%FR_HOUR_2997_ND);
		minute = (dwReste/FR_MINUTE_2997_ND);
		dwReste = (dwReste%FR_MINUTE_2997_ND);
		strTimeCode.Format(_T("%02d:%02d:%02d:%02d"), hour,minute, (dwReste / FR_SECOND_2997), (dwReste % FR_SECOND_2997));
	} 
	else if (dwRate*c4796FRAMES_SCALE == dwScale*c4796FRAMES_FRAME_RATE) 
	{
		hour = (dwFrameCount/FR_HOUR_4796_DROP);
		dwReste = (dwFrameCount%FR_HOUR_4796_DROP);
		minute = 10*(dwReste/FR_TENMIN_4796_DROP);
		dwReste = (dwReste%FR_TENMIN_4796_DROP);
		if (dwReste >= FR_MINUTE_48) 
		{
			dwReste  -= FR_MINUTE_48;
			minute += 1 + (dwReste / FR_MINUTE_4796_DROP);
			dwReste %= FR_MINUTE_4796_DROP;
			dwReste  += 2;
		}
		strTimeCode.Format(_T("%02d:%02d:%02d;%02d"), hour,minute, (dwReste / FR_SECOND_48), (dwReste % FR_SECOND_48));
	}
	else if (dwRate*c48FRAMES_SCALE == dwScale*c48FRAMES_FRAME_RATE) 
	{
		hour = (dwFrameCount/FR_HOUR_48);
		dwReste = (dwFrameCount%FR_HOUR_48);
		minute = (dwReste/FR_MINUTE_48);
		dwReste = (dwReste%FR_MINUTE_48);
		strTimeCode.Format(_T("%02d:%02d:%02d:%02d"), hour,minute, (dwReste / FR_SECOND_48), (dwReste % FR_SECOND_48));
	} 
	else if (dwRate*c50FRAMES_SCALE == dwScale*c50FRAMES_FRAME_RATE) 
	{
		hour = (dwFrameCount/FR_HOUR_50);
		dwReste = (dwFrameCount%FR_HOUR_50);
		minute = (dwReste/FR_MINUTE_50);
		dwReste = (dwReste%FR_MINUTE_50);
		strTimeCode.Format(_T("%02d:%02d:%02d:%02d"), hour,minute, (dwReste / FR_SECOND_50), (dwReste % FR_SECOND_50));
	} 
	else if (dwRate*c5994FRAMES_SCALE == dwScale*c5994FRAMES_FRAME_RATE) 
	{
		hour = (dwFrameCount/FR_HOUR_5994_DROP);
		dwReste = (dwFrameCount%FR_HOUR_5994_DROP);
		minute = 10*(dwReste/FR_TENMIN_5994_DROP);
		dwReste = (dwReste%FR_TENMIN_5994_DROP);
		if (dwReste >= FR_MINUTE_5994_ND) 
		{
			dwReste  -= FR_MINUTE_5994_ND;
			minute += 1 + (dwReste / FR_MINUTE_5994_DROP);
			dwReste %= FR_MINUTE_5994_DROP;
			dwReste  += 2;
		}
		strTimeCode.Format(_T("%02d:%02d:%02d;%02d"), hour,minute, (dwReste / FR_SECOND_5994), (dwReste % FR_SECOND_5994));
	}
	else if (dwRate*c60FRAMES_SCALE == dwScale*c60FRAMES_FRAME_RATE) 
	{
		hour = (dwFrameCount/FR_HOUR_60);
		dwReste = (dwFrameCount%FR_HOUR_60);
		minute = (dwReste/FR_MINUTE_60);
		dwReste = (dwReste%FR_MINUTE_60);
		strTimeCode.Format(_T("%02d:%02d:%02d:%02d"), hour,minute, (dwReste / FR_SECOND_60), (dwReste % FR_SECOND_60));
	} 
	else
	{
		SD_UINT32	uSecNum;
		hour = (dwFrameCount * dwScale / dwRate / 3600);
		dwReste = dwFrameCount - (hour*3600*dwRate/dwScale);
		minute = (dwReste * dwScale / dwRate / 60);
		dwReste -= (minute*60*dwRate/dwScale);
		uSecNum = dwReste * dwScale / dwRate;
		dwReste -= (uSecNum*dwRate/dwScale);
		strTimeCode.Format(_T("%02d:%02d:%02d:%02d"), hour, minute, uSecNum, dwReste);
	}
};


//依据帧率转换帧数至时分秒字符串
SD_INLINE SD_VOID	FramesToTimeCodeStringEx(SD_UINT32 dwFrameCount, CSDString &strTimeCode, SD_UINT32 dwRate, SD_UINT32 dwScale)
{
	SD_UINT32	dwReste, hour, minute;

	if (dwRate*c2398FRAMES_SCALE == dwScale*c2398FRAMES_FRAME_RATE) 
	{
		hour = (dwFrameCount/FR_HOUR_2398_DROP);
		dwReste = (dwFrameCount%FR_HOUR_2398_DROP);
		minute = 10*(dwReste/FR_TENMIN_2398_DROP);
		dwReste = (dwReste%FR_TENMIN_2398_DROP);
		if (dwReste >= FR_MINUTE_24) 
		{
			dwReste  -= FR_MINUTE_24;
			minute += 1 + (dwReste / FR_MINUTE_2398_DROP);
			dwReste %= FR_MINUTE_2398_DROP;
			dwReste  += 2;
		}
		strTimeCode.Format(_T("%02d:%02d:%02d"), hour,minute, (dwReste / FR_SECOND_24));
	} 
	else if (dwRate*c24FRAMES_SCALE == dwScale*c24FRAMES_FRAME_RATE) 
	{
		hour = (dwFrameCount/FR_HOUR_24);
		dwReste = (dwFrameCount%FR_HOUR_24);
		minute = (dwReste/FR_MINUTE_24);
		dwReste = (dwReste%FR_MINUTE_24);
		strTimeCode.Format(_T("%02d:%02d:%02d"), hour,minute, (dwReste / FR_SECOND_24));
	} 
	else if (dwRate*c25FRAMES_SCALE == dwScale*c25FRAMES_FRAME_RATE) 
	{
		hour = (dwFrameCount/FR_HOUR_PAL);
		dwReste = (dwFrameCount%FR_HOUR_PAL);
		minute = (dwReste/FR_MINUTE_PAL);
		dwReste = (dwReste%FR_MINUTE_PAL);
		strTimeCode.Format(_T("%02d:%02d:%02d"), hour,minute, (dwReste / FR_SECOND_PAL));
	} 
	else if (dwRate*c2997FRAME_SCALE == dwScale*c2997FRAME_FRAME_RATE) 
	{
		hour = (dwFrameCount/FR_HOUR_2997_DROP);
		dwReste = (dwFrameCount%FR_HOUR_2997_DROP);
		minute = 10*(dwReste/FR_TENMIN_2997_DROP);
		dwReste = (dwReste%FR_TENMIN_2997_DROP);
		if (dwReste >= FR_MINUTE_2997_ND) 
		{
			dwReste  -= FR_MINUTE_2997_ND;
			minute += 1 + (dwReste / FR_MINUTE_2997_DROP);
			dwReste %= FR_MINUTE_2997_DROP;
			dwReste  += 2;
		}
		strTimeCode.Format(_T("%02d:%02d:%02d"), hour,minute, (dwReste / FR_SECOND_2997));
	} 
	else if (dwRate*c30FRAMES_SCALE == dwScale*c30FRAMES_FRAME_RATE) 
	{
		hour = (dwFrameCount/FR_HOUR_2997_ND);
		dwReste = (dwFrameCount%FR_HOUR_2997_ND);
		minute = (dwReste/FR_MINUTE_2997_ND);
		dwReste = (dwReste%FR_MINUTE_2997_ND);
		strTimeCode.Format(_T("%02d:%02d:%02d"), hour,minute, (dwReste / FR_SECOND_2997));
	} 
	else if (dwRate*c4796FRAMES_SCALE == dwScale*c4796FRAMES_FRAME_RATE) 
	{
		hour = (dwFrameCount/FR_HOUR_4796_DROP);
		dwReste = (dwFrameCount%FR_HOUR_4796_DROP);
		minute = 10*(dwReste/FR_TENMIN_4796_DROP);
		dwReste = (dwReste%FR_TENMIN_4796_DROP);
		if (dwReste >= FR_MINUTE_48) 
		{
			dwReste  -= FR_MINUTE_48;
			minute += 1 + (dwReste / FR_MINUTE_4796_DROP);
			dwReste %= FR_MINUTE_4796_DROP;
			dwReste  += 2;
		}
		strTimeCode.Format(_T("%02d:%02d:%02d"), hour,minute, (dwReste / FR_SECOND_48));
	}
	else if (dwRate*c48FRAMES_SCALE == dwScale*c48FRAMES_FRAME_RATE) 
	{
		hour = (dwFrameCount/FR_HOUR_48);
		dwReste = (dwFrameCount%FR_HOUR_48);
		minute = (dwReste/FR_MINUTE_48);
		dwReste = (dwReste%FR_MINUTE_48);
		strTimeCode.Format(_T("%02d:%02d:%02d"), hour,minute, (dwReste / FR_SECOND_48));
	} 
	else if (dwRate*c50FRAMES_SCALE == dwScale*c50FRAMES_FRAME_RATE) 
	{
		hour = (dwFrameCount/FR_HOUR_50);
		dwReste = (dwFrameCount%FR_HOUR_50);
		minute = (dwReste/FR_MINUTE_50);
		dwReste = (dwReste%FR_MINUTE_50);
		strTimeCode.Format(_T("%02d:%02d:%02d"), hour,minute, (dwReste / FR_SECOND_50));
	} 
	else if (dwRate*c5994FRAMES_SCALE == dwScale*c5994FRAMES_FRAME_RATE) 
	{
		hour = (dwFrameCount/FR_HOUR_5994_DROP);
		dwReste = (dwFrameCount%FR_HOUR_5994_DROP);
		minute = 10*(dwReste/FR_TENMIN_5994_DROP);
		dwReste = (dwReste%FR_TENMIN_5994_DROP);
		if (dwReste >= FR_MINUTE_5994_ND) 
		{
			dwReste  -= FR_MINUTE_5994_ND;
			minute += 1 + (dwReste / FR_MINUTE_5994_DROP);
			dwReste %= FR_MINUTE_5994_DROP;
			dwReste  += 2;
		}
		strTimeCode.Format(_T("%02d:%02d:%02d"), hour,minute, (dwReste / FR_SECOND_5994));
	}
	else if (dwRate*c60FRAMES_SCALE == dwScale*c60FRAMES_FRAME_RATE) 
	{
		hour = (dwFrameCount/FR_HOUR_60);
		dwReste = (dwFrameCount%FR_HOUR_60);
		minute = (dwReste/FR_MINUTE_60);
		dwReste = (dwReste%FR_MINUTE_60);
		strTimeCode.Format(_T("%02d:%02d:%02d"), hour,minute, (dwReste / FR_SECOND_60));
	} 
	else
	{
		SD_UINT32	uSecNum;
		hour = (dwFrameCount * dwScale / dwRate / 3600);
		dwReste = dwFrameCount - (hour*3600*dwRate/dwScale);
		minute = (dwReste * dwScale / dwRate / 60);
		dwReste -= (minute*60*dwRate/dwScale);
		uSecNum = dwReste * dwScale / dwRate;
		dwReste -= (uSecNum*dwRate/dwScale);
		strTimeCode.Format(_T("%02d:%02d:%02d"), hour, minute, uSecNum);
	}
};

//依据视频制式转换帧数至时分秒帧字符串
SD_INLINE SD_VOID	FramesToTimeCodeString(SD_UINT32 dwFrameCount, CSDString &strTimeCode, SD_VIDEO_STANDARD enumVideoStandard)
{
	SD_UINT32	dwRate, dwScale;
	_GetStandardRateScale(enumVideoStandard, dwRate, dwScale);
	FramesToTimeCodeString(dwFrameCount, strTimeCode, dwRate, dwScale);
};

//依据视频制式转换帧数至时分秒帧字符串
SD_INLINE SD_VOID	FramesToTimeCodeStringEx(SD_UINT32 dwFrameCount, CSDString &strTimeCode, SD_VIDEO_STANDARD enumVideoStandard)
{
	SD_UINT32	dwRate, dwScale;
	_GetStandardRateScale(enumVideoStandard, dwRate, dwScale);
	FramesToTimeCodeStringEx(dwFrameCount, strTimeCode, dwRate, dwScale);
};

//依据视频制式转换帧数至时分秒帧字符串
SD_INLINE CSDString _FramesToTimeCodeString(SD_UINT32 dwFrameCount, SD_VIDEO_STANDARD enumVideoStandard)
{
	CSDString	strTimeCode;
	FramesToTimeCodeString(dwFrameCount, strTimeCode, enumVideoStandard);
	return strTimeCode;
};

//依据帧率转换帧数至时分秒帧字符串
SD_INLINE CSDString _FramesToTimeCodeString(SD_UINT32 dwFrameCount, SD_UINT32 dwRate, SD_UINT32 dwScale)
{
	CSDString	strTimeCode;
	FramesToTimeCodeString(dwFrameCount, strTimeCode, dwRate, dwScale);
	return strTimeCode;
};

//依据帧率转换时分秒帧字符串至帧数
SD_INLINE SD_UINT32	TimeCodeStringToFrames(SD_LPCTSTR lpszTimeCode, SD_UINT32 dwRate, SD_UINT32 dwScale)
{
	CSDString	strTimeCode = CSDString(lpszTimeCode);
	if (strTimeCode.GetLength() != 11)
		return 0;

	int	nhour = (strTimeCode[0]-'0')*10 + (strTimeCode[1]-'0');
	int	nminute = (strTimeCode[3]-'0')*10 + (strTimeCode[4]-'0');
	int	nsec = (strTimeCode[6]-'0')*10 + (strTimeCode[7]-'0');
	int	nframe = (strTimeCode[9]-'0')*10 + (strTimeCode[10]-'0');

	if (dwRate*c2398FRAMES_SCALE == dwScale*c2398FRAMES_FRAME_RATE)
	{
		if ((nminute%10) != 0) 
		{
			if (nsec == 0 && (nframe == 0 || nframe == 1))
				nframe = 2;
		}
		return nhour*FR_HOUR_2398_DROP + (nminute/10)*FR_TENMIN_2398_DROP + (nminute%10)*FR_MINUTE_2398_DROP + nsec*FR_SECOND_24 + nframe;
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
		if ((nminute%10) != 0) 
		{
			if (nsec == 0 && (nframe == 0 || nframe == 1))
				nframe = 2;
		}
		return nhour*FR_HOUR_2997_DROP + (nminute/10)*FR_TENMIN_2997_DROP + (nminute%10)*FR_MINUTE_2997_DROP + nsec*FR_SECOND_2997 + nframe;
	} 
	else if (dwRate*c30FRAMES_SCALE == dwScale*c30FRAMES_FRAME_RATE) 
	{
		return nhour*FR_HOUR_2997_ND + nminute*FR_MINUTE_2997_ND + nsec*FR_SECOND_2997 + nframe;
	} 
	else if (dwRate*c4796FRAMES_SCALE == dwScale*c4796FRAMES_FRAME_RATE) 
	{
		if ((nminute%10) != 0) 
		{
			if (nsec == 0 && (nframe == 0 || nframe == 1))
				nframe = 2;
		}
		return nhour*FR_HOUR_4796_DROP + (nminute/10)*FR_TENMIN_4796_DROP + (nminute%10)*FR_MINUTE_4796_DROP + nsec*FR_SECOND_48 + nframe;
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
		if ((nminute%10) != 0) 
		{
			if (nsec == 0 && (nframe == 0 || nframe == 1))
				nframe = 2;
		}
		return nhour*FR_HOUR_5994_DROP + (nminute/10)*FR_TENMIN_5994_DROP + (nminute%10)*FR_MINUTE_5994_DROP + nsec*FR_SECOND_5994 + nframe;
	}
	else if (dwRate*c60FRAMES_SCALE == dwScale*c60FRAMES_FRAME_RATE) 
	{
		return nhour*FR_HOUR_60 + nminute*FR_MINUTE_60 + nsec*FR_SECOND_60 + nframe;
	} 
	else
	{
		return (nhour*3600*dwRate/dwScale) + (nminute*60*dwRate/dwScale) + (nsec*dwRate/dwScale) + nframe;
	}

	return 0;
};

//依据视频制式转换时分秒帧字符串至帧数
SD_INLINE SD_UINT32	TimeCodeStringToFrames(SD_LPCTSTR lpszTimeCode, SD_VIDEO_STANDARD enumVideoStandard)
{
	SD_UINT32	dwRate, dwScale;
	_GetStandardRateScale(enumVideoStandard, dwRate, dwScale);
	return TimeCodeStringToFrames(lpszTimeCode, dwRate, dwScale);
};

//依据视频制式转换浮点型秒数至时分秒帧字符串
SD_INLINE CSDString SecondToTimeCodeString(SD_DOUBLE dblSeconds, SD_VIDEO_STANDARD enumVideoStandard)
{
	return _FramesToTimeCodeString(_SecToFrame(dblSeconds, enumVideoStandard), enumVideoStandard);
};

//依据帧率转换浮点型秒数至时分秒帧字符串
SD_INLINE CSDString SecondToTimeCodeString(SD_DOUBLE dblSeconds, SD_UINT32 dwRate, SD_UINT32 dwScale)
{
	return _FramesToTimeCodeString(_SecToFrame(dblSeconds, dwRate, dwScale), dwRate, dwScale);
};

//依据视频制式转换时分秒帧字符串至浮点型秒数
SD_INLINE SD_DOUBLE TimeCodeStringToSecond(SD_LPCTSTR lpszTimeCode, SD_VIDEO_STANDARD enumVideoStandard)
{
	return _FrameToSec(TimeCodeStringToFrames(lpszTimeCode, enumVideoStandard), enumVideoStandard);
};

//依据帧率转换时分秒帧字符串至浮点型秒数
SD_INLINE SD_DOUBLE TimeCodeStringToSecond(SD_LPCTSTR lpszTimeCode, SD_UINT32 dwRate, SD_UINT32 dwScale)
{
	return _FrameToSec(TimeCodeStringToFrames(lpszTimeCode, dwRate, dwScale), dwRate, dwScale);
};

//转换浮点型秒数至时分秒毫秒字符串
SD_INLINE CSDString _SecondToTimeString(SD_DOUBLE dblSeconds, SD_UINT32 dwMilliSecBitNum=0)
{
	CSDString	strTimeString = _T("");
	SD_DOUBLE	xx = dblSeconds;
	SD_UINT32	hh = (SD_UINT32)xx/3600;
	xx -= (SD_DOUBLE)hh*3600;
	SD_UINT32	mm = (SD_UINT32)xx/60;
	xx -= (SD_DOUBLE)mm*60;
	if (dwMilliSecBitNum == 0) 
	{
		SD_UINT32	ss = (SD_UINT32)(xx+0.5);
		strTimeString.Format(_T("%02d:%02d:%02d"), hh, mm, ss);
	} 
	else 
	{
		SD_UINT32	ss = (SD_UINT32)xx;
		if (dwMilliSecBitNum == 1)
			strTimeString.Format(_T("%02d:%02d:%02d.%01d"), hh, mm, ss, (SD_UINT32)((xx-(SD_DOUBLE)ss)*10.0));
		else if (dwMilliSecBitNum == 2)
			strTimeString.Format(_T("%02d:%02d:%02d.%02d"), hh, mm, ss, (SD_UINT32)((xx-(SD_DOUBLE)ss)*100.0));
		else
			strTimeString.Format(_T("%02d:%02d:%02d.%03d"), hh, mm, ss, (SD_UINT32)((xx-(SD_DOUBLE)ss)*1000.0));
	}
	return strTimeString;
};


//=======================================================================================
//与视音频压缩编码、文件(流)封装、节目复用等有关的枚举、结构及函数定义
//=======================================================================================
//	定义枚举:
//		SD_VIDEO_TYPE;					// 视频编码格式类型
//		SD_AUDIO_TYPE;					// 音频编码格式类型
//		SD_COLOR_FORMAT					// 视频颜色格式类型
//		SD_STREAM_TYPE					// 视音频流格式类型
//		SD_VIDEOSCAN_MODE				// 视频扫描帧场数据排列方式
//		SD_VIDEO_ASPECTRATIO			// 视频幅宽比类型
//		SD_COLOR_PRIMARIES				// 源基色的色度坐标(ISO13818-2)
//		SD_COLOR_TRANSFER				// 光电转换特性(ISO13818-2)
//		SD_COLOR_MATRIX					// 颜色空间变换系数(ISO13818-2)
//		SD_ACTIVE_FORMAT_DESCRIPTION	// 图像有效区域信息描述，按SMPTE 2016-1定义
//		SD_DATARATE_TYPE				// MPEG视频编解码格式码率类型
//		SD_AUDIO_CHANNELCONFIGURATION	// 声道属性枚举定义
//		SD_CHANNELSAMPLE_FORMAT			// 音频声道采样数据格式
//		SD_STREAMMEDIA_TYPE				// 流媒体数据信息类型
//		SD_MEDIADATASTREAM_TYPE			// 媒体数据流数据类型
//		SD_STREAMCOMPRESSDATA_ACTMODE	// 流压缩数据获取/推送操作模式
//	定义结构:
//		SDVideoMediaInfo, SDVideoMediaInfoArray					//视频基本属性
//		SDVideoFrameImageBufInfo									//视频帧图像数据块属性
//		SDAudioMediaInfo, SDAudioMediaInfoArray					//音频基本属性
//		SDAudioSamplesBufInfo										//音频采样数据块属性
//		SDStreamMediaInfo, SDStreamMediaInfoArray				//视音频流(文件)属性
//		SDStreamMediaInfoEx, SDStreamMediaInfoExArray			//视音频流(文件)扩展属性
//		SDSingleProgramStreamMediaInfo, SDSingleProgramStreamMediaInfoArray			//单节目视音频流(文件)属性
//		SDSingleProgramStreamMediaInfoEx,SDSingleProgramStreamMediaInfoExArray		//单节目视音频流(文件)扩展属性
//		SDMultiProgramStreamMediaInfo													//多节目视音频流(文件)属性
//		SDMultiProgramStreamMediaInfoEx												//多节目视音频流(文件)扩展属性
//		SDGlobalStreamMediaInfo									//全局流媒体数据信息
//		SDGlobalStreamMediaInfoEx									//全局流媒体数据扩展信息
//		SDStreamCompressDataInfo		//流压缩数据信息
//	定义函数:
//		CSDString GetVideoTypeHint(SD_VIDEO_TYPE enumVideoType);	//得到视频编码格式类型的名称
//		CSDString GetAudioTypeHint(SD_AUDIO_TYPE enumAudioType);	//得到音频编码格式类型的名称
//		CSDString GetColorFormatHint(SD_COLOR_FORMAT enumColorFormat);	//得到视频颜色格式类型的名称
//		SD_UINT32 GetColorFormatBufSizeInByte(SD_COLOR_FORMAT enumColorFormat, SD_UINT32 dwPixelNum);	//依据视频颜色格式和像素点数目得到视频数据块的大小
//		CSDString GetStreamTypeHint(SD_STREAM_TYPE enumStreamType);	//得到视音频流格式类型的名称
//		CSDString GetVideoScanModeHint(SD_VIDEOSCAN_MODE enumScanMode);	//得到视频扫描帧场数据排列方式的名称
//		CSDString GetVideoAspectRatioHint(SD_VIDEO_ASPECTRATIO enumAspectRatio);	//得到视频幅宽比类型的名称
//		CSDString GetColorPrimariesHint(SD_COLOR_PRIMARIES emColorPrimaries);	//得到源基色的色度坐标类型的名称
//		CSDString GetColorTransferHint(SD_COLOR_TRANSFER emColorTransfer);	//得到光电转换特性类型的名称
//		CSDString GetColorMatrixHint(SD_COLOR_MATRIX emColorMatrix);	//得到颜色空间变换系数类型的名称
//		CSDString GetActiveFormatDescriptionHint(SD_ACTIVE_FORMAT_DESCRIPTION enumAFD, SD_BOOL bIs16_9);	//得到图像有效区域信息描述类型的名称
//		CSDString GetDataRateTypeHint(SD_DATARATE_TYPE enumDataRateType);	//得到MPEG视频编解码格式码率类型的名称
//		CSDString GeAudioCFGHint(SD_AUDIO_CHANNELCONFIGURATION enumAudioCFG)	////得到声道属性枚举定义的名称
//		CSDString GeChannelSamplesFormat(SD_CHANNELSAMPLE_FORMAT enumChannelSamplesFormat)	//得到音频声道采样数据格式的名称
//		SD_UINT32 GetChannelSamplesFormatBufSizeInByte(SD_CHANNELSAMPLE_FORMAT enumChannelSamplesFormat, SD_UINT32 dwChannels, SD_UINT32 dwBlockAlign, SD_UINT32 dwSamplesCount);	//依据音频声道采样数据格式,声道数目和数据块对齐单位得到音频数据块的大小
//=======================================================================================
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

//得到视频编码格式类型的名称
SD_INLINE CSDString	GetVideoTypeHint(SD_VIDEO_TYPE enumVideoType)
{
	CSDString strHint = _T("Unknow");
	switch(enumVideoType) 
	{
		case SDVIDEOTYPE_MJPEG_FIELD:
			strHint = _T("MJPEG_Field");
			break;
		case SDVIDEOTYPE_MJPEG_FRAME:
			strHint = _T("MJPEG_Frame");
			break;
		case SDVIDEOTYPE_MJPEG_LOSSLESS_FIELD:
			strHint = _T("MJPEG_LossLess_Field");
			break;
		case SDVIDEOTYPE_MJPEG_LOSSLESS_FRAME:
			strHint = _T("MJPEG_LossLess_Frame");
			break;

		case SDVIDEOTYPE_MPEG1:
			strHint = _T("MPEG1");
			break;
		case SDVIDEOTYPE_MPEG2_IFRAME:
			strHint = _T("MPEG2_I");
			break;
		case SDVIDEOTYPE_MPEG2_IBP:
			strHint = _T("MPEG2_IBP");
			break;
		case SDVIDEOTYPE_MPEG2_D10:
			strHint = _T("MPEG2_D10");
			break;
		case SDVIDEOTYPE_MPEG2_HDV:
			strHint = _T("MPEG2_HDV");
			break;
		case SDVIDEOTYPE_MPEG4:
			strHint = _T("MPEG4");
			break;

		case SDVIDEOTYPE_DV25:
			strHint = _T("DV25");
			break;
		case SDVIDEOTYPE_DV50:
			strHint = _T("DV50");
			break;
		case SDVIDEOTYPE_DVSD:
			strHint = _T("DVSD");
			break;
		case SDVIDEOTYPE_DVHD:
			strHint = _T("DVHD");
			break;

		case SDVIDEOTYPE_YUV_UNCOMPRESS:
			strHint = _T("YUV_UnCompress");
			break;
		case SDVIDEOTYPE_RGB_UNCOMPRESS:
			strHint = _T("RGB_UnCompress");
			break;
		case SDVIDEOTYPE_ZAXEL_LOSSLESS:
			strHint = _T("ZAXEL_LossLess");
			break;

		case SDVIDEOTYPE_REAL_MEDIA:
			strHint = _T("Real_Media");
			break;
		case SDVIDEOTYPE_WINDOWS_MEDIA:
			strHint = _T("Windows_Media");
			break;
		case SDVIDEOTYPE_QUICKTIME_MOV:
			strHint = _T("QuickTime_Mov");
			break;
		case SDVIDEOTYPE_VCM_COMPRESSED:
			strHint = _T("VCM_Compressed");
			break;

		case SDVIDEOTYPE_AVS:
			strHint = _T("AVS");
			break;
		case SDVIDEOTYPE_H263:
			strHint = _T("H263");
			break;
		case SDVIDEOTYPE_H264:
			strHint = _T("H264");
			break;
		case SDVIDEOTYPE_H265:
			strHint = _T("H265");
			break;
		case SDVIDEOTYPE_MJ2K:
			strHint = _T("MJ2K");
			break;
		case SDVIDEOTYPE_AVCINTRA_HD:
			strHint = _T("AVC_Intra_HD");
			break;
		case SDVIDEOTYPE_AVCULTRA_LONGGOP:
			strHint = _T("AVC_LongG");
			break;
		case SDVIDEOTYPE_AVID_DNXHD:
			strHint = _T("Avid_DNxHD");
			break;
		case SDVIDEOTYPE_PRORES422:
			strHint = _T("ProRes422");
			break;
		case SDVIDEOTYPE_SWFFLV_TYPE:
			strHint = _T("FLV-Video");
			break;
		case SDVIDEOTYPE_REDCODE:
			strHint = _T("RedCode");
			break;
		case SDVIDEOTYPE_DPX:
			strHint = _T("DPX");
			break;
		case SDVIDEOTYPE_XAVC_HD		 : strHint = _T("XAVC_HD");		    break;
		case SDVIDEOTYPE_XAVC_4K         : strHint = _T("XAVC_4K");		    break;
		case SDVIDEOTYPE_XAVC_HD_INTRA   : strHint = _T("XAVC_HDIntra");    break;
		case SDVIDEOTYPE_XAVC_4K_INTRA   : strHint = _T("XAVC_4KIntra");    break;
		case SDVIDEOTYPE_XAVC_HD444_INTRA: strHint = _T("XAVC_HD444Intra"); break;
		case SDVIDEOTYPE_XAVC_4K444_INTRA: strHint = _T("XAVC_4K444Intra"); break;
		case SDVIDEOTYPE_SONY_RAW:
			strHint = _T("SONY RAW");
			break;
		case SDVIDEOTYPE_MPEG4_SSTP:
			strHint = _T("MPEG4 SSTP");
			break;
		case SDVIDEOTYPE_GIA:
			strHint = _T("EasyCode GIA");
			break;
		case SDVIDEOTYPE_LOSSLESS:
			strHint = _T("EasyCode LOSSLESS");
			break;
	}
	return strHint;
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

//得到音频编码格式类型的名称
SD_INLINE CSDString	GetAudioTypeHint(SD_AUDIO_TYPE enumAudioType)
{
	CSDString strHint = _T("Unknow");
	switch(enumAudioType)
	{
		case SDAUDIOTYPE_WAVE_PCM:
			strHint = _T("PCM");
			break;

		case SDAUDIOTYPE_MP1:
			strHint = _T("MP1");
			break;
		case SDAUDIOTYPE_MP2:
			strHint = _T("MP2");
			break;
		case SDAUDIOTYPE_MP3:
			strHint = _T("MP3");
			break;
		case SDAUDIOTYPE_MPEG4:
			strHint = _T("MPEG4");
			break;

		case SDAUDIOTYPE_AAC:
			strHint = _T("AAC");
			break;
		case SDAUDIOTYPE_AC3:
			strHint = _T("AC3");
			break;
		case SDAUDIOTYPE_EAC3:
			strHint = _T("EAC3");
			break;
		case SDAUDIOTYPE_DTS:
			strHint = _T("DTS");
			break;
		case SDAUDIOTYPE_DRA:
			strHint = _T("DRA");
			break;
		case SDAUDIOTYPE_AVS:
			strHint = _T("AVS");
			break;
		case SDAUDIOTYPE_DolbyE:
			strHint = _T("Dolby-E");
			break;

		case SDAUDIOTYPE_REAL_MEDIA:
			strHint = _T("Real_Media");
			break;
		case SDAUDIOTYPE_WINDOWS_MEDIA:
			strHint = _T("Windows_Media");
			break;
		case SDAUDIOTYPE_QUICKTIME_MOV:
			strHint = _T("QuickTime_Mov");
			break;

		case SDAUDIOTYPE_G711:
			strHint = _T("G711");
			break;
		case SDAUDIOTYPE_AMRNB:
			strHint = _T("AMR-NB");
			break;
		case SDAUDIOTYPE_AMRWB:
			strHint = _T("AMR-WB");
			break;
		case SDAUDIOTYPE_SWFFLV:
			strHint = _T("FLV-Audio");
			break;
		case SDAUDIOTYPE_ACM_COMPRESSED:
			strHint = _T("ACM_Compressed");
			break;
	}
	return strHint;
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

//得到视音频流格式类型的名称
SD_INLINE CSDString GetStreamTypeHint(SD_STREAM_TYPE enumStreamType)
{
	CSDString strStreamType = _T("Unknow");

	switch(enumStreamType)
	{
		case SDSTREAMTYPE_OPENDML_AVI:
			strStreamType = _T("ODML_AVI");
			break;
		case SDSTREAMTYPE_MSVFW_AVI:
			strStreamType = _T("MSVFW_AVI");
			break;
		case SDSTREAMTYPE_MSVFW_WAV:
			strStreamType = _T("MSVFW_WAV");
			break;

		case SDSTREAMTYPE_ES:
			strStreamType = _T("ES");
			break;
		case SDSTREAMTYPE_PS:
			strStreamType = _T("PS");
			break;
		case SDSTREAMTYPE_VCD:
			strStreamType = _T("VCD");
			break;
		case SDSTREAMTYPE_DVD:
			strStreamType = _T("DVD");
			break;
		case SDSTREAMTYPE_TS:
			strStreamType = _T("TS");
			break;
		case SDSTREAMTYPE_HDV:
			strStreamType = _T("HDV");
			break;
		case SDSTREAMTYPE_SUBTITLE:
			strStreamType = _T("SubTitle");
			break;

		case SDSTREAMTYPE_MXF:
			strStreamType = _T("MXF");
			break;
		case SDSTREAMTYPE_3GPP:
			strStreamType = _T("3GPP");
			break;
		case SDSTREAMTYPE_FLV:
			strStreamType = _T("FLV");
			break;
		case SDSTREAMTYPE_ISOMP4:
			strStreamType = _T("ISO MP4");
			break;

		case SDSTREAMTYPE_REAL_MEDIA:
			strStreamType = _T("RealMedia");
			break;
		case SDSTREAMTYPE_WINDOWS_MEDIA:
			strStreamType = _T("WindowsMedia");
			break;
		case SDSTREAMTYPE_QUICKTIME_MOV:
			strStreamType = _T("QuickTime_Mov");
			break;
		case SDSTREAMTYPE_ZAXEL:
			strStreamType = _T("Zaxel_AVI");
			break;
		case SDSTREAMTYPE_AIFF:
			strStreamType = _T("AIFF");
			break;
		case SDSTREAMTYPE_MKV:
			strStreamType = _T("MKV");
			break;

		case SDSTREAMTYPE_GXF:
			strStreamType = _T("GXF");
			break;
		case SDSTREAMTYPE_OMNEON:
			strStreamType = _T("OMNEON");
			break;
		case SDSTREAMTYPE_SAF:
			strStreamType = _T("SAF");
			break;
		case SDSTREAMTYPE_LXF:
			strStreamType = _T("LXF");
			break;
		case SDSTREAMTYPE_MAV70:
			strStreamType = _T("MAV70");
			break;
		case SDSTREAMTYPE_VSR2000:
			strStreamType = _T("VSR2000");
			break;
		case SDSTREAMTYPE_MSS:
			strStreamType = _T("MSS");
			break;
		case SDSTREAMTYPE_P2CLIP:
			strStreamType = _T("P2 Clip");
			break;
		case SDSTREAMTYPE_E2CLIP:
			strStreamType = _T("E2 Clip");
			break;
		case SDSTREAMTYPE_DPX:
			strStreamType = _T("DPX");
			break;
		case SDSTREAMTYPE_R3D:
			strStreamType = _T("R3D");
			break;
		case SDSTREAMTYPE_HLS:
			strStreamType = _T("HLS");
			break;
		case SDSTREAMTYPE_RTP:
			strStreamType = _T("RTP");
			break;
		case SDSTREAMTYPE_AMR:
			strStreamType = _T("AMR");
			break;
		case SDSTREAMTYPE_DMC_SEQUENCE_FILE:
			strStreamType = _T("SEQ FILE");
			break;
	}
	return strStreamType;
}

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

//得到视频扫描帧场数据排列方式的名称
SD_INLINE CSDString GetVideoScanModeHint(SD_VIDEOSCAN_MODE enumScanMode)
{
	CSDString	strScanModeHint = _T("Unknow");
	switch(enumScanMode)
	{
		case SDVIDEOSCANMODE_FirstFieldTop:
			strScanModeHint = _T("FirstFieldTop");
			break;
		case SDVIDEOSCANMODE_SecondFieldTop:
			strScanModeHint = _T("SecondFieldTop");
			break;
		case SDVIDEOSCANMODE_Progressive:
			strScanModeHint = _T("Progressive");
			break;
		case SDVIDEOSCANMODE_ProgressiveSegmented:
			strScanModeHint = _T("ProgressiveSegmented");
			break;
		case SDVIDEOSCANMODE_FirstFieldTopBackToBack:
			strScanModeHint = _T("FirstFieldTopBackToBack");
			break;
		case SDVIDEOSCANMODE_SecondFieldTopBackToBack:
			strScanModeHint = _T("SecondFieldTopBackToBack");
			break;
	}
	return strScanModeHint;
};

enum SD_VIDEO_ASPECTRATIO	// 视频幅宽比类型
{
   SDVIDEOASPECTRATIO_Invalid	=	0x00000000,
   SDVIDEOASPECTRATIO_4_3		=	0x00000001,
   SDVIDEOASPECTRATIO_16_9		=	0x00000002,
   SDVIDEOASPECTRATIO_14_9		=	0x00000003,				//SMPTE 2016-1
};

//得到视频幅宽比类型的名称
SD_INLINE CSDString GetVideoAspectRatioHint(SD_VIDEO_ASPECTRATIO enumAspectRatio)
{
	CSDString	strAspectRatioHint = _T("Unknow");
	switch(enumAspectRatio)
	{
		case SDVIDEOASPECTRATIO_4_3:
			strAspectRatioHint = _T("4:3");
			break;
		case SDVIDEOASPECTRATIO_16_9:
			strAspectRatioHint = _T("16:9");
			break;
		case SDVIDEOASPECTRATIO_14_9:
			strAspectRatioHint = _T("14:9");
			break;
	}
	return strAspectRatioHint;
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

//得到源基色的色度坐标类型的名称
SD_INLINE CSDString GetColorPrimariesHint(SD_COLOR_PRIMARIES emColorPrimaries)
{
	CSDString str = _T("Unknow");
	switch(emColorPrimaries)
	{
		case SDCOLORPRIMARIES_Forbidden:
			str = _T("Forbidden");
			break;
		case SDCOLORPRIMARIES_ITU_R709:
			str = _T("ITU R709");
			break;
		case SDCOLORPRIMARIES_Unspecified:
			str = _T("Unspecified");
			break;
		case SDCOLORPRIMARIES_Reserved:
			str = _T("Reserved");
			break;
		case SDCOLORPRIMARIES_ITU_R470_2M:
			str = _T("ITU R470 2M");
			break;
		case SDCOLORPRIMARIES_ITU_R470_2BG:
			str = _T("ITU R470 2BG");
			break;
		case SDCOLORPRIMARIES_SMPTE_170M:
			str = _T("SMPTE 170M");
			break;
		case SDCOLORPRIMARIES_SMPTE_240M:
			str = _T("SMPTE 240M");
			break;
		case SDCOLORPRIMARIES_GenericFilm:
			str = _T("Generic Film");
			break;
		case SDCOLORPRIMARIES_BT2020:
			str = _T("BT2020");
			break;
	}
	return str;
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

//得到光电转换特性类型的名称
SD_INLINE CSDString GetColorTransferHint(SD_COLOR_TRANSFER emColorTransfer)
{
	CSDString str = _T("Unknow");
	switch(emColorTransfer)
	{
		case SDCOLORTRANSFER_Forbidden:
			str = _T("Forbidden");
			break;
		case SDCOLORTRANSFER_ITU_R709:
			str = _T("ITU R709");
			break; // 高清默认
		case SDCOLORTRANSFER_Unspecified:
			str = _T("Unspecified");
			break;
		case SDCOLORTRANSFER_Reserved:
			str = _T("Reserved");
			break;
		case SDCOLORTRANSFER_ITU_R470_2M:
			str = _T("ITU R470 2M");
			break;
		case SDCOLORTRANSFER_ITU_R470_2BG:
			str = _T("ITU R470 2BG");
			break; // 标清默认
		case SDCOLORTRANSFER_SMPTE_170M:
			str = _T("SMPTE 170M");
			break; // 苹果标清默认，参数与TRANSFER_ITU_R470_2BG相同
		case SDCOLORTRANSFER_Linear:
			str = _T("Linear");
			break;
		case SDCOLORTRANSFER_LOG_100_1:
			str = _T("Log(100:1)");
			break;
		case SDCOLORTRANSFER_LOG_316_1:
			str = _T("Log(316:1)");
			break;
		case SDCOLORTRANSFER_IEC_61966_2_4:
			str = _T("IEC 61966-2-4");
			break;
		case SDCOLORTRANSFER_BT1361:
			str = _T("ITU-R BT.1361");
			break;
		case SDCOLORTRANSFER_IEC_61966_2_1:
			str = _T("IEC 61966-2-1");
			break;
		case SDCOLORTRANSFER_BT2020_10BIT:
			str = _T("ITU-R BT.2020 for 10 bit");
			break;
		case SDCOLORTRANSFER_BT2020_12BIT:
			str = _T("ITU-R BT.2020 for 12 bit");
			break;
	}
	return str;
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

//得到颜色空间变换系数类型的名称
SD_INLINE CSDString GetColorMatrixHint(SD_COLOR_MATRIX emColorMatrix)
{
	CSDString str = _T("Unknow");
	switch(emColorMatrix)
	{
		case SDCOLORMATRIX_Forbidden:
			str = _T("Forbidden");
			break;
		case SDCOLORMATRIX_ITU_R709:
			str = _T("ITU R709");
			break;
		case SDCOLORMATRIX_Unspecified:
			str = _T("Unspecified");
			break;
		case SDCOLORMATRIX_Reserved:
			str = _T("Reserved");
			break;
		case SDCOLORMATRIX_FCC:
			str = _T("FCC");
			break;
		case SDCOLORMATRIX_ITU_R470_2BG:
			str = _T("ITU R470 2BG");
			break;
		case SDCOLORMATRIX_SMPTE_170M:
			str = _T("SMPTE 170M");
			break;
		case SDCOLORMATRIX_SMPTE_240M:
			str = _T("SMPTE 240M");
			break;
		case SDCOLORMATRIX_BT2020_NCL:
			str = _T("BT2020 Non-Constant Luminance");
			break;
		case SDCOLORMATRIX_BT2020_CL:
			str = _T("BT2020 Constant Luminance");
			break;
	}
	return str;
}

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

//得到图像有效区域信息描述类型的名称
SD_INLINE CSDString GetActiveFormatDescriptionHint(SD_ACTIVE_FORMAT_DESCRIPTION enumAFD, SD_BOOL bIs16_9)
{
	CSDString str = _T("Undefined");
	if (bIs16_9) 
	{
		switch(enumAFD) // 16:9
		{
			case SDAFD_0000: 
				str = _T("(0000)Undefined)");
				break;
			case SDAFD_0001:
				str = _T("(0001)Reserved");
				break;
			case SDAFD_0010:
				str = _T("(0010)Full Frame 16:9");
				break;
			case SDAFD_0011:
				str = _T("(0011)Pillarbox 14:9");
				break;
			case SDAFD_0100:
				str = _T("(0100)Letterbox 16:9 center");
				break;
			case SDAFD_0101:
				str = _T("(0101)Reserved");
				break;
			case SDAFD_0110:
				str = _T("(0110)Reserved");
				break;
			case SDAFD_0111:
				str = _T("(0111)Reserved");
				break;
			case SDAFD_1000:
				str = _T("(1000)Full Frame 16:9");
				break;
			case SDAFD_1001:
				str = _T("(1001)Pillarbox 4:3");
				break;
			case SDAFD_1010:
				str = _T("(1010)Full Frame 16:9 with protected");
				break;
			case SDAFD_1011:
				str = _T("(1011)Pillarbox 14:9");
				break;
			case SDAFD_1100:
				str = _T("(1100)Reserved");
				break;
			case SDAFD_1101:
				str = _T("(1101)Pillarbox 4:3 with alternative 14:9 center");
				break;
			case SDAFD_1110:
				str = _T("(1110)Full Frame 16:9 with alternative 14:9 center");
				break;
			case SDAFD_1111:
				str = _T("(1111)Full frame 16:9 with alternative 4:3 center");
				break;
		}
	}
	else 
	{
		switch(enumAFD) // 4:3
		{
			case SDAFD_0000:
				str = _T("(0000)Undefined");
				break;
			case SDAFD_0001:
				str = _T("(0001)Reserved");
				break;
			case SDAFD_0010:
				str = _T("(0010)Letterbox 16:9 top");
				break;
			case SDAFD_0011:
				str = _T("(0011)Letterbox 14:9 top");
				break;
			case SDAFD_0100:
				str = _T("(0100)Letterbox 16:9 center");
				break;
			case SDAFD_0101:
				str = _T("(0101)Reserved");
				break;
			case SDAFD_0110:
				str = _T("(0110)Reserved");
				break;
			case SDAFD_0111:
				str = _T("(0111)Reserved");
				break;
			case SDAFD_1000:
				str = _T("(1000)Full Frame 4:3");
				break;
			case SDAFD_1001:
				str = _T("(1001)Full Frame 4:3");
				break;
			case SDAFD_1010:
				str = _T("(1010)Letterbox 16:9 center");
				break;
			case SDAFD_1011:
				str = _T("(1011)Letterbox 14:9 center");
				break;
			case SDAFD_1100:
				str = _T("(1100)Reserved");
				break;
			case SDAFD_1101:
				str = _T("(1101)Full Frame 4:3 with alternative 14:9 center");
				break;
			case SDAFD_1110:
				str = _T("(1110)Letterbox 16:9 with alternative 14:9 center");
				break;
			case SDAFD_1111:
				str = _T("(1111)Letterbox 16:9 with alternative 4:3 center");
				break;
		}
	}
	return str;
}

enum SD_DATARATE_TYPE				// MPEG视频编解码格式码率类型
{
	SDDATARATE_VBR_QUILTY			=	0,			//可变码率编码(VBR),质量固定
	SDDATARATE_CONSTANT				=	1,			//恒定码率编码
	SDDATARATE_VBR_AVERAGE_SMALL	=	2,			//可变码率编码(VBR),平均码率, 小码率变化
	SDDATARATE_VBR_AVERAGE_LARGE	=	3,			//可变码率编码(VBR),平均码率, 大码率变化
};

//得到MPEG视频编解码格式码率类型的名称
SD_INLINE CSDString GetDataRateTypeHint(SD_DATARATE_TYPE enumDataRateType)
{
	CSDString str = _T("Unknow");
	switch(enumDataRateType)
	{
		case SDDATARATE_VBR_QUILTY: 
			str = _T("VBR-Quilty");
			break;
		case SDDATARATE_CONSTANT: 
			str = _T("ConstantRate");
			break;
		case SDDATARATE_VBR_AVERAGE_SMALL: 
			str = _T("VBR-Average_Small");
			break;
		case SDDATARATE_VBR_AVERAGE_LARGE: 
			str = _T("VBR-Average_Large");
			break;
	}
	return str;
};

#define	SDVIDEOMEDIAINFO_STRUSIZE_VER1		52
#define	SDVIDEOMEDIAINFO_STRUSIZE_VER2		88

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
		return *this;
	};

	SD_BOOL operator == (const SDVideoMediaInfo& other)
	{
		if (dwStruSize != other.dwStruSize)
			return SD_FALSE;
		if (dwWidth != other.dwWidth || dwHeight != other.dwHeight)
			return SD_FALSE;
		if (dwStandardRate != other.dwStandardRate)
			return SD_FALSE;
		if (dwStandardScale != other.dwStandardScale)
			return SD_FALSE;
		if (enumScanMode != other.enumScanMode)
			return SD_FALSE;
		if (enumColorFormat != other.enumColorFormat)
			return SD_FALSE;
		if (enumVideoType != other.enumVideoType)
			return SD_FALSE;
		if (dwVideoSubType != other.dwVideoSubType)
			return SD_FALSE;
		if (dwDataRateInBitsPerSec != other.dwDataRateInBitsPerSec)
			return SD_FALSE;
		if (enumDataRateType != other.enumDataRateType)
			return SD_FALSE;
		if (dwGOPSize != other.dwGOPSize)
			return SD_FALSE;
		if (dwReferencePeriod != other.dwReferencePeriod)
			return SD_FALSE;
		if (bIsClipped != other.bIsClipped)
			return SD_FALSE;

		if (dwDisplayWidth != other.dwDisplayWidth || dwDisplayHeight != other.dwDisplayHeight)
			return SD_FALSE;
		if (enumColorPrimaries != other.enumColorPrimaries)
			return SD_FALSE;
		if (enumColorTransfer != other.enumColorTransfer)
			return SD_FALSE;
		if (enumColorMatrix != other.enumColorMatrix)
			return SD_FALSE;
		if (enumAFD != other.enumAFD)
			return SD_FALSE;
		if (dwMaxDataRateInBitsPerSec != other.dwMaxDataRateInBitsPerSec || dwMinDataRateInBitsPerSec != other.dwMinDataRateInBitsPerSec)
			return SD_FALSE;
		if (dwFlags != other.dwFlags)
			return SD_FALSE;
		if (dwH264EncoderLevel != other.dwH264EncoderLevel)
			return SD_FALSE;
		if (extradata != other.extradata || extradata_size != other.extradata_size)
			return SD_FALSE;

		return SD_TRUE;
	};

	SD_BOOL operator != (const SDVideoMediaInfo& other)
	{
		if (dwStruSize != other.dwStruSize)
			return SD_TRUE;
		if (dwWidth != other.dwWidth || dwHeight != other.dwHeight)
			return SD_TRUE;
		if (dwStandardRate != other.dwStandardRate)
			return SD_TRUE;
		if (dwStandardScale != other.dwStandardScale)
			return SD_TRUE;
		if (enumScanMode != other.enumScanMode)
			return SD_TRUE;
		if (enumColorFormat != other.enumColorFormat)
			return SD_TRUE;
		if (enumVideoType != other.enumVideoType)
			return SD_TRUE;
		if (dwVideoSubType != other.dwVideoSubType)
			return SD_TRUE;
		if (dwDataRateInBitsPerSec != other.dwDataRateInBitsPerSec)
			return SD_TRUE;
		if (enumDataRateType != other.enumDataRateType)
			return SD_TRUE;
		if (dwGOPSize != other.dwGOPSize)
			return SD_TRUE;
		if (dwReferencePeriod != other.dwReferencePeriod)
			return SD_TRUE;
		if (bIsClipped != other.bIsClipped)
			return SD_TRUE;

		if (dwDisplayWidth != other.dwDisplayWidth || dwDisplayHeight != other.dwDisplayHeight)
			return SD_TRUE;
		if (enumColorPrimaries != other.enumColorPrimaries)
			return SD_TRUE;
		if (enumColorTransfer != other.enumColorTransfer)
			return SD_TRUE;
		if (enumColorMatrix != other.enumColorMatrix)
			return SD_TRUE;
		if (enumAFD != other.enumAFD)
			return SD_TRUE;
		if (dwMaxDataRateInBitsPerSec != other.dwMaxDataRateInBitsPerSec || dwMinDataRateInBitsPerSec != other.dwMinDataRateInBitsPerSec)
			return SD_TRUE;
		if (dwFlags != other.dwFlags || dwFlags != other.dwFlags)
			return SD_TRUE;
		if (dwH264EncoderLevel != other.dwH264EncoderLevel || dwH264EncoderLevel != other.dwH264EncoderLevel)
			return SD_TRUE;
		if (extradata != other.extradata || extradata_size != other.extradata_size)
			return SD_TRUE;

		return SD_FALSE;
	};

	SD_BOOL	CloneBufPtr(SD_PVOID pStruBuf)
	{
		if (pStruBuf)
		{
			SD_PUINT8	pbStruBuf = (SD_PUINT8)pStruBuf;
			SD_UINT32	dwStruBufSize = (*((SD_PUINT32)pStruBuf));
			if (dwStruBufSize == SDVIDEOMEDIAINFO_STRUSIZE_VER1 ||
				dwStruBufSize == SDVIDEOMEDIAINFO_STRUSIZE_VER2)
			{
				pbStruBuf += sizeof(SD_UINT32);

				if (dwStruBufSize == SDVIDEOMEDIAINFO_STRUSIZE_VER1)
				{
					dwWidth = (SD_UINT32)(*((SD_PUINT16)pbStruBuf));
					pbStruBuf += sizeof(SD_UINT16);

					dwHeight = (SD_UINT32)(*((SD_PUINT16)pbStruBuf));
					pbStruBuf += sizeof(SD_UINT16);
				}
				else
				{
					dwWidth = (*((SD_PUINT32)pbStruBuf));
					pbStruBuf += sizeof(SD_UINT32);

					dwHeight = (*((SD_PUINT32)pbStruBuf));
					pbStruBuf += sizeof(SD_UINT32);
				}

				dwStandardRate = (*((SD_PUINT32)pbStruBuf));
				pbStruBuf += sizeof(SD_UINT32);

				dwStandardScale = (*((SD_PUINT32)pbStruBuf));
				pbStruBuf += sizeof(SD_UINT32);

				enumScanMode = (SD_VIDEOSCAN_MODE)((*((SD_PINT32)pbStruBuf)));
				pbStruBuf += sizeof(SD_INT32);

				enumColorFormat = (SD_COLOR_FORMAT)((*((SD_PINT32)pbStruBuf)));
				pbStruBuf += sizeof(SD_INT32);

				enumVideoType = (SD_VIDEO_TYPE)((*((SD_PINT32)pbStruBuf)));
				pbStruBuf += sizeof(SD_INT32);

				dwVideoSubType = (*((SD_PUINT32)pbStruBuf));
				pbStruBuf += sizeof(SD_UINT32);

				dwDataRateInBitsPerSec = (*((SD_PUINT32)pbStruBuf));
				pbStruBuf += sizeof(SD_UINT32);

				enumDataRateType = (SD_DATARATE_TYPE)(*((SD_PINT32)enumDataRateType));
				pbStruBuf += sizeof(SD_INT32);

				dwGOPSize = (*((SD_PUINT32)pbStruBuf));
				pbStruBuf += sizeof(SD_UINT32);

				dwReferencePeriod = (*((SD_PUINT32)pbStruBuf));
				pbStruBuf += sizeof(SD_UINT32);

				bIsClipped = (*((SD_PBOOL)pbStruBuf));
				pbStruBuf += sizeof(SD_BOOL);

				if (dwWidth > 720)
				{
					dwDisplayWidth = 16;									// HD 1080 default
					dwDisplayHeight = 9;									// HD 1080 default
					enumColorPrimaries = SDCOLORPRIMARIES_ITU_R709;			// HD default
					enumColorTransfer = SDCOLORTRANSFER_ITU_R709;			// HD default
					enumColorMatrix = SDCOLORMATRIX_ITU_R709;				// HD default
				}
				else
				{
					dwDisplayWidth = 4;										// SD default
					dwDisplayHeight = 3;									// SD default
					enumColorPrimaries = SDCOLORPRIMARIES_ITU_R470_2BG;		// SD default
					enumColorTransfer = SDCOLORTRANSFER_ITU_R470_2BG;		// SD default
					enumColorMatrix = SDCOLORMATRIX_ITU_R470_2BG;			// SD default
				}
				enumAFD = SDAFD_1000;
				dwMaxDataRateInBitsPerSec = 0;
				dwMinDataRateInBitsPerSec = 0;

				if (dwStruBufSize == SDVIDEOMEDIAINFO_STRUSIZE_VER2)
				{
					dwDisplayWidth = (SD_UINT32)((*((SD_PINT32)pbStruBuf)));
					pbStruBuf += sizeof(SD_INT32);

					dwDisplayHeight = (SD_UINT32)((*((SD_PINT32)pbStruBuf)));
					pbStruBuf += sizeof(SD_INT32);

					enumColorPrimaries = (SD_COLOR_PRIMARIES)((*((SD_PINT32)pbStruBuf)));
					pbStruBuf += sizeof(SD_INT32);

					enumColorTransfer = (SD_COLOR_TRANSFER)((*((SD_PINT32)pbStruBuf)));
					pbStruBuf += sizeof(SD_INT32);

					enumColorMatrix = (SD_COLOR_MATRIX)((*((SD_PINT32)pbStruBuf)));
					pbStruBuf += sizeof(SD_INT32);

					enumAFD = (SD_ACTIVE_FORMAT_DESCRIPTION)((*((SD_PINT32)pbStruBuf)));
					pbStruBuf += sizeof(SD_INT32);

					dwMaxDataRateInBitsPerSec = (SD_UINT32)((*((SD_PINT32)pbStruBuf)));
					pbStruBuf += sizeof(SD_INT32);

					dwMinDataRateInBitsPerSec = (SD_UINT32)((*((SD_PINT32)pbStruBuf)));
					pbStruBuf += sizeof(SD_INT32);

					dwFlags = (SD_INT32)((*((SD_PINT32)pbStruBuf)));
					pbStruBuf += sizeof(SD_INT32);

					dwH264EncoderLevel = (SD_UINT8)((*((SD_UINT8 *)pbStruBuf)));
					pbStruBuf += sizeof(SD_UINT8);


				}
				
				return SD_TRUE;
			}
		}
		return SD_TRUE;
	};

	SD_VIDEO_STANDARD	GetVideoStandard()
	{
		SD_VIDEO_STANDARD enumVideoStandard = SDVIDEOSTANDARD_UNKNOW;
		if (dwWidth == 720 && (dwHeight == 576 || dwHeight == 486 || dwHeight == 480))
			enumVideoStandard = _GetStandardRateScale(dwStandardRate, dwStandardScale, SDVIDEOCLASS_SD);
		else if (dwWidth == 1280 && dwHeight == 720)
			enumVideoStandard = _GetStandardRateScale(dwStandardRate, dwStandardScale, SDVIDEOCLASS_HD720p);
		else if ((dwWidth == 1920 || dwWidth == 1440 || dwWidth == 1280) && (dwHeight == 1080 || dwHeight == 1088))
		{
			if (enumScanMode == SDVIDEOSCANMODE_Progressive)
			{
				enumVideoStandard = _GetStandardRateScale(dwStandardRate, dwStandardScale, SDVIDEOCLASS_HD1080p);
				if (enumVideoStandard == SDVIDEOSTANDARD_UNKNOW)
					enumVideoStandard = _GetStandardRateScale(dwStandardRate, dwStandardScale, SDVIDEOCLASS_HD1080P);
			}
			else if (enumScanMode == SDVIDEOSCANMODE_ProgressiveSegmented)
				enumVideoStandard = _GetStandardRateScale(dwStandardRate, dwStandardScale, SDVIDEOCLASS_HD1080psf);
			else
				enumVideoStandard = _GetStandardRateScale(dwStandardRate, dwStandardScale, SDVIDEOCLASS_HD1080i);
		}
		else if (dwWidth == 2048 && dwHeight == 1080)
		{
			if (enumScanMode == SDVIDEOSCANMODE_Progressive)
				enumVideoStandard = _GetStandardRateScale(dwStandardRate, dwStandardScale, SDVIDEOCLASS_2K1080P);
			else if (enumScanMode == SDVIDEOSCANMODE_ProgressiveSegmented)
				enumVideoStandard = _GetStandardRateScale(dwStandardRate, dwStandardScale, SDVIDEOCLASS_2K1080Psf);
		}
		else if (dwWidth == 2048 && dwHeight == 1556)
		{
			if (enumScanMode == SDVIDEOSCANMODE_Progressive)
				enumVideoStandard = _GetStandardRateScale(dwStandardRate, dwStandardScale, SDVIDEOCLASS_2K1556P);
			else if (enumScanMode == SDVIDEOSCANMODE_ProgressiveSegmented)
				enumVideoStandard = _GetStandardRateScale(dwStandardRate, dwStandardScale, SDVIDEOCLASS_2K1556Psf);
		}
		else if (dwWidth == 3840 && dwHeight == 2160)
		{
			if (enumScanMode == SDVIDEOSCANMODE_Progressive)
				enumVideoStandard = _GetStandardRateScale(dwStandardRate, dwStandardScale, SDVIDEOCLASS_4K3840P);
			else if (enumScanMode == SDVIDEOSCANMODE_ProgressiveSegmented)
				enumVideoStandard = _GetStandardRateScale(dwStandardRate, dwStandardScale, SDVIDEOCLASS_4K3840Psf);
		}
		else if (dwWidth == 4096 && dwHeight == 2160)
		{
			if (enumScanMode == SDVIDEOSCANMODE_Progressive)
				enumVideoStandard = _GetStandardRateScale(dwStandardRate, dwStandardScale, SDVIDEOCLASS_4K4096P);
			else if (enumScanMode == SDVIDEOSCANMODE_ProgressiveSegmented)
				enumVideoStandard = _GetStandardRateScale(dwStandardRate, dwStandardScale, SDVIDEOCLASS_4K4096Psf);
		}
		else
		{
			if (enumScanMode == SDVIDEOSCANMODE_Progressive)
				enumVideoStandard = _GetStandardRateScale(dwStandardRate, dwStandardScale, SDVIDEOCLASS_P_RateScale);
			else if (enumScanMode == SDVIDEOSCANMODE_ProgressiveSegmented)
				enumVideoStandard = _GetStandardRateScale(dwStandardRate, dwStandardScale, SDVIDEOCLASS_Psf_RateScale);
			else
				enumVideoStandard = _GetStandardRateScale(dwStandardRate, dwStandardScale, SDVIDEOCLASS_I_RateScale);
		}
		return enumVideoStandard;
	};

	// 序列化支持
	SD_INT32 GetSerializationSize()
	{
		return  SerializationToPtr(SD_NULL, 0);
	};
	SD_INT32 SerializationToPtr(SD_UINT8* pBuffer, SD_INT32 iBufferSize)
	{
		SD_INT32 iPtrSize = 0;
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &dwStruSize, sizeof(dwStruSize));
		iPtrSize += sizeof(dwStruSize);
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &dwWidth, sizeof(dwWidth));
		iPtrSize += sizeof(dwWidth);
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &dwHeight, sizeof(dwHeight));
		iPtrSize += sizeof(dwHeight);
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &dwStandardRate, sizeof(dwStandardRate));
		iPtrSize += sizeof(dwStandardRate);
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &dwStandardScale, sizeof(dwStandardScale));
		iPtrSize += sizeof(dwStandardScale);
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &enumScanMode, sizeof(enumScanMode));
		iPtrSize += sizeof(enumScanMode);
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &enumColorFormat, sizeof(enumColorFormat));
		iPtrSize += sizeof(enumColorFormat);
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &enumVideoType, sizeof(enumVideoType));
		iPtrSize += sizeof(enumVideoType);
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &dwVideoSubType, sizeof(dwVideoSubType));
		iPtrSize += sizeof(dwVideoSubType);
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &dwDataRateInBitsPerSec, sizeof(dwDataRateInBitsPerSec));
		iPtrSize += sizeof(dwDataRateInBitsPerSec);
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &enumDataRateType, sizeof(enumDataRateType));
		iPtrSize += sizeof(dwDataRateInBitsPerSec);
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &dwGOPSize, sizeof(dwGOPSize));
		iPtrSize += sizeof(dwGOPSize);
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &dwReferencePeriod, sizeof(dwReferencePeriod));
		iPtrSize += sizeof(dwReferencePeriod);
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &bIsClipped, sizeof(bIsClipped));
		iPtrSize += sizeof(bIsClipped);
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &dwDisplayWidth, sizeof(dwDisplayWidth));
		iPtrSize += sizeof(dwDisplayWidth);
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &dwDisplayHeight, sizeof(dwDisplayHeight));
		iPtrSize += sizeof(dwDisplayHeight);
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &enumColorPrimaries, sizeof(enumColorPrimaries));
		iPtrSize += sizeof(enumColorPrimaries);
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &enumColorTransfer, sizeof(enumColorTransfer));
		iPtrSize += sizeof(enumColorTransfer);
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &enumColorMatrix, sizeof(enumColorMatrix));
		iPtrSize += sizeof(enumColorMatrix);
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &enumAFD, sizeof(enumAFD));
		iPtrSize += sizeof(enumAFD);
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &dwMaxDataRateInBitsPerSec, sizeof(dwMaxDataRateInBitsPerSec));
		iPtrSize += sizeof(dwMaxDataRateInBitsPerSec);
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &dwMinDataRateInBitsPerSec, sizeof(dwMinDataRateInBitsPerSec));
		iPtrSize += sizeof(dwMinDataRateInBitsPerSec);
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &dwFlags, sizeof(dwFlags));
		iPtrSize += sizeof(dwFlags);
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &dwH264EncoderLevel, sizeof(dwH264EncoderLevel));
		iPtrSize += sizeof(dwH264EncoderLevel);
		return iPtrSize;
	};
	SD_INT32 SerializationFromPtr(SD_UINT8* pBuffer, SD_INT32 iBufferSize)
	{
		SD_INT32 iPtrSize = 0;
		memcpy(&dwStruSize, pBuffer + iPtrSize, sizeof(dwStruSize));								iPtrSize += sizeof(dwStruSize);
		memcpy(&dwWidth, pBuffer + iPtrSize, sizeof(dwWidth));										iPtrSize += sizeof(dwWidth);
		memcpy(&dwHeight, pBuffer + iPtrSize, sizeof(dwHeight));									iPtrSize += sizeof(dwHeight);
		memcpy(&dwStandardRate, pBuffer + iPtrSize, sizeof(dwStandardRate));						iPtrSize += sizeof(dwStandardRate);
		memcpy(&dwStandardScale, pBuffer + iPtrSize, sizeof(dwStandardScale));						iPtrSize += sizeof(dwStandardScale);
		memcpy(&enumScanMode, pBuffer + iPtrSize, sizeof(enumScanMode));							iPtrSize += sizeof(enumScanMode);
		memcpy(&enumColorFormat, pBuffer + iPtrSize, sizeof(enumColorFormat));						iPtrSize += sizeof(enumColorFormat);
		memcpy(&enumVideoType, pBuffer + iPtrSize, sizeof(enumVideoType));							iPtrSize += sizeof(enumVideoType);
		memcpy(&dwVideoSubType, pBuffer + iPtrSize, sizeof(dwVideoSubType));						iPtrSize += sizeof(dwVideoSubType);
		memcpy(&dwDataRateInBitsPerSec, pBuffer + iPtrSize, sizeof(dwDataRateInBitsPerSec));		iPtrSize += sizeof(dwDataRateInBitsPerSec);
		memcpy(&enumDataRateType, pBuffer + iPtrSize, sizeof(enumDataRateType));					iPtrSize += sizeof(dwDataRateInBitsPerSec);
		memcpy(&dwGOPSize, pBuffer + iPtrSize, sizeof(dwGOPSize));									iPtrSize += sizeof(dwGOPSize);
		memcpy(&dwReferencePeriod, pBuffer + iPtrSize, sizeof(dwReferencePeriod));					iPtrSize += sizeof(dwReferencePeriod);
		memcpy(&bIsClipped, pBuffer + iPtrSize, sizeof(bIsClipped));								iPtrSize += sizeof(bIsClipped);
		memcpy(&dwDisplayWidth, pBuffer + iPtrSize, sizeof(dwDisplayWidth));						iPtrSize += sizeof(dwDisplayWidth);
		memcpy(&dwDisplayHeight, pBuffer + iPtrSize, sizeof(dwDisplayHeight));						iPtrSize += sizeof(dwDisplayHeight);
		memcpy(&enumColorPrimaries, pBuffer + iPtrSize, sizeof(enumColorPrimaries));				iPtrSize += sizeof(enumColorPrimaries);
		memcpy(&enumColorTransfer, pBuffer + iPtrSize, sizeof(enumColorTransfer));					iPtrSize += sizeof(enumColorTransfer);
		memcpy(&enumColorMatrix, pBuffer + iPtrSize, sizeof(enumColorMatrix));						iPtrSize += sizeof(enumColorMatrix);
		memcpy(&enumAFD, pBuffer + iPtrSize, sizeof(enumAFD));										iPtrSize += sizeof(enumAFD);
		memcpy(&dwMaxDataRateInBitsPerSec, pBuffer + iPtrSize, sizeof(dwMaxDataRateInBitsPerSec));	iPtrSize += sizeof(dwMaxDataRateInBitsPerSec);
		memcpy(&dwMinDataRateInBitsPerSec, pBuffer + iPtrSize, sizeof(dwMinDataRateInBitsPerSec));	iPtrSize += sizeof(dwMinDataRateInBitsPerSec);
		memcpy(&dwFlags, pBuffer + iPtrSize, sizeof(dwFlags));	iPtrSize += sizeof(dwFlags);
		memcpy(&dwH264EncoderLevel, pBuffer + iPtrSize, sizeof(dwH264EncoderLevel));	iPtrSize += sizeof(dwH264EncoderLevel);
		return iPtrSize;
	};
};
typedef CSDArray<SDVideoMediaInfo, SDVideoMediaInfo&>	SDVideoMediaInfoArray;

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

//得到声道属性枚举定义的名称
SD_INLINE CSDString GeAudioCFGHint(SD_AUDIO_CHANNELCONFIGURATION enumAudioCFG)
{
	CSDString str = _T("Unknow");
	switch(enumAudioCFG)
	{
		case SDAUDIOCFG_INDEPENDENT:				// 独立声道
			str = _T("Independent");
			break;
		case SDAUDIOCFG_STEREO:						// 立体声(左 右)
			str = _T("Stereo");
			break;
		case SDAUDIOCFG_5_1:						// 5.1(左 右 中置 左环绕 右环绕 低音)
			str = _T("5.1");
			break;
		case SDAUDIOCFG_7_1:						// 7.0(前左 前右 中置 左 右 左环绕 右环绕  低音)
			str = _T("7.1");
			break;

		case SDAUDIOCFG_2_1:						// 2.1(左 右 低音)
			str = _T("2.1(Left_Right_Lfe)");
			break;
		case SDAUDIOCFG_3_0_C:						// 3.0(左 右 中置)
			str = _T("3.0(Left_Right_Center)");
			break;
		case SDAUDIOCFG_3_0_S:						// 3.0(左 右 环绕)
			str = _T("3.0(Left_Right_Surround)");
			break;
		case SDAUDIOCFG_3_1_C_LFE:					// 3.1(左 右 中置 低音)
			str = _T("3.1(Left_Right_Center_Lfe)");
			break;
		case SDAUDIOCFG_3_1_S_LFE:					// 3.1(左 右 环绕 低音)
			str = _T("3.1(Left_Right_Surround_Lfe)");
			break;
		case SDAUDIOCFG_4_0_C_S:					// 4.0(左 右 中置 环绕)
			str = _T("4.0(Left_Right_Center_Surround)");
			break;
		case SDAUDIOCFG_4_0_LS_RS:					// 4.0(左 右 左环绕 右环绕)
			str = _T("4.0(Left_Right_SurroundLeft_SurroundRight)");
			break;
		case SDAUDIOCFG_4_1_C_S_LFE:				// 4.1(左 右 中置 环绕 低音)
			str = _T("4.1(Left_Right_Center_Surround_Lfe)");
			break;
		case SDAUDIOCFG_4_1_LS_RS_LFE:				// 4.1(左 右 左环绕 右环绕 低音)
			str = _T("4.1(Left_Right_SurroundLeft_SurroundRight_Lfe)");
			break;
		case SDAUDIOCFG_5_0:						// 5.0(左 右 中置 左环绕 右环绕)
			str = _T("5.0(Left_Right_Center_SurroundLeft_SurroundRight)");
			break;
		case SDAUDIOCFG_6_0_LRC_LRSRC:				// 6.0(左 右 前中置 左环绕 右环绕 后中置)
			str = _T("6.0(Left_Right_FrontCenter_SurroundLeft_SurroundRight_RearCenter)");
			break;
		case SDAUDIOCFG_6_0_FLFR_LR_LRS:			// 6.0(前左 前右 左 右 左环绕 右环绕)
			str = _T("6.0(FrontLeft_FrontRight_Left_Right_SurroundLeft_SurroundRight)");
			break;
		case SDAUDIOCFG_6_1_LRFC_LRSRC_LFE:			// 6.1(左 右 前中置 左环绕  右环绕 后中置 低音)
			str = _T("6.1(Left_Right_FrontCenter_SurroundLeft_SurroundRight_RearCenter_Lfe)");
			break;
		case SDAUDIOCFG_6_1_FLR_LRLRS_LFE:			// 6.1(前左 前右 左 右 左环绕 右环绕 低音)
			str = _T("6.1(FrontLeft_FrontRight_Left_Right_SurroundLeft_SurroundRight_Lfe)");
			break;
		case SDAUDIOCFG_7_0:						// 7.0(前左 前右 中置 左 右 左环绕 右环绕)
			str = _T("7.0(FrontLeft_FrontRight_Center_Left_Right_SurroundLeft_SurroundRight)");
			break;
	}
	return str;
};

enum SD_CHANNELSAMPLE_FORMAT	//音频声道采样数据格式
{
	SDCHANNELSAMPLESFORMAT_Unknow				=	0,
	SDCHANNELSAMPLESFORMAT_Progressive			=	1,			//音频声道采样数据连续排列...CH1(Sn)CH2(Sn)CH1(Sn+1)CH2(Sn+1)...
	SDCHANNELSAMPLESFORMAT_Segmented			=	2,			//音频声道采样数据分割排列...CH1(Sn)CH1(Sn+1)...CH2(Sn)CH2(Sn+1)...
	SDCHANNELSAMPLESFORMAT_Progressive_32bit	=	3,			//音频声道采样数据连续排列...CH1(Sn)CH2(Sn)CH1(Sn+1)CH2(Sn+1)...
	SDCHANNELSAMPLESFORMAT_Segmented_32bit		=	4,			//音频声道采样数据分割排列...CH1(Sn)CH1(Sn+1)...CH2(Sn)CH2(Sn+1)...
};

//得到音频声道采样数据格式的名称
SD_INLINE CSDString GeChannelSamplesFormat(SD_CHANNELSAMPLE_FORMAT enumChannelSamplesFormat)
{
	CSDString str = _T("Unknow");
	switch(enumChannelSamplesFormat)
	{
		case SDCHANNELSAMPLESFORMAT_Progressive:
			str = _T("Progressive");
			break;
		case SDCHANNELSAMPLESFORMAT_Segmented:
			str = _T("Segmented");
			break;
		case SDCHANNELSAMPLESFORMAT_Progressive_32bit:
			str = _T("Progressive_32bit");
			break;
		case SDCHANNELSAMPLESFORMAT_Segmented_32bit:
			str = _T("Segmented_32bit");
			break;
	}
	return str;
};

//依据音频声道采样数据格式,声道数目和数据块对齐单位得到音频数据块的大小
SD_INLINE	SD_UINT32	GetChannelSamplesFormatBufSizeInByte(SD_CHANNELSAMPLE_FORMAT enumChannelSamplesFormat, SD_UINT32 dwChannels, SD_UINT32 dwBlockAlign, SD_UINT32 dwSamplesCount)
{
	if (enumChannelSamplesFormat == SDCHANNELSAMPLESFORMAT_Progressive
		|| enumChannelSamplesFormat == SDCHANNELSAMPLESFORMAT_Progressive_32bit)
		return dwBlockAlign*dwSamplesCount;
	else if (enumChannelSamplesFormat == SDCHANNELSAMPLESFORMAT_Segmented
		|| enumChannelSamplesFormat == SDCHANNELSAMPLESFORMAT_Segmented_32bit)
		return dwChannels*dwBlockAlign*dwSamplesCount;
	else
		return 0;
};


#define	SDAUDIOMEDIAINFO_STRUSIZE_VER1		32
#define	SDAUDIOMEDIAINFO_STRUSIZE_VER2		40

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

	SD_BOOL operator == (const SDAudioMediaInfo& other)
	{
		if (dwStruSize != other.dwStruSize)
			return SD_FALSE;
		if (enumAudioType != other.enumAudioType)
			return SD_FALSE;
		if (dwAudioSubType != other.dwAudioSubType)
			return SD_FALSE;
		if (dwChannels != other.dwChannels)
			return SD_FALSE;
		if (dwBitsPerSample != other.dwBitsPerSample)
			return SD_FALSE;
		if (dwSamplesPerSec != other.dwSamplesPerSec)
			return SD_FALSE;
		if (dwAvgBitsPerSec != other.dwAvgBitsPerSec)
			return SD_FALSE;
		if (dwBlockAlign != other.dwBlockAlign)
			return SD_FALSE;
		if (enumAudioCFG != other.enumAudioCFG)
			return SD_FALSE;
		if (enumChannelSamplesFormat != other.enumChannelSamplesFormat)
			return SD_FALSE;
		if (extradata != other.extradata)
			return SD_FALSE;
		if (extradata_size != other.extradata_size)
			return SD_FALSE;

		return SD_TRUE;
	};

	SD_BOOL operator != (const SDAudioMediaInfo& other)
	{
		if (dwStruSize != other.dwStruSize)
			return SD_TRUE;
		if (enumAudioType != other.enumAudioType)
			return SD_TRUE;
		if (dwAudioSubType != other.dwAudioSubType)
			return SD_TRUE;
		if (dwChannels != other.dwChannels)
			return SD_TRUE;
		if (dwBitsPerSample != other.dwBitsPerSample)
			return SD_TRUE;
		if (dwSamplesPerSec != other.dwSamplesPerSec)
			return SD_TRUE;
		if (dwAvgBitsPerSec != other.dwAvgBitsPerSec)
			return SD_TRUE;
		if (dwBlockAlign != other.dwBlockAlign)
			return SD_TRUE;
		if (enumAudioCFG != other.enumAudioCFG)
			return SD_TRUE;
		if (enumChannelSamplesFormat != other.enumChannelSamplesFormat)
			return SD_TRUE;
		if (extradata != other.extradata)
			return SD_TRUE;
		if (extradata_size != other.extradata_size)
			return SD_TRUE;

		return SD_FALSE;
	};

	SD_BOOL	CloneBufPtr(SD_PVOID pStruBuf)
	{
		if (pStruBuf)
		{
			SD_PUINT8	pbStruBuf = (SD_PUINT8)pStruBuf;
			SD_UINT32	dwStruBufSize = (*((SD_PUINT32)pStruBuf));
			if (dwStruBufSize == SDAUDIOMEDIAINFO_STRUSIZE_VER1 || dwStruBufSize == SDAUDIOMEDIAINFO_STRUSIZE_VER2)
			{
				pbStruBuf += sizeof(SD_UINT32);

				enumAudioType = (SD_AUDIO_TYPE)((*((SD_PINT32)pbStruBuf)));
				pbStruBuf += sizeof(SD_INT32);

				dwAudioSubType = (*((SD_PUINT32)pbStruBuf));
				pbStruBuf += sizeof(SD_UINT32);

				dwChannels = (*((SD_PUINT32)pbStruBuf));
				pbStruBuf += sizeof(SD_UINT32);

				dwBitsPerSample = (*((SD_PUINT32)pbStruBuf));
				pbStruBuf += sizeof(SD_UINT32);

				dwSamplesPerSec = (*((SD_PUINT32)pbStruBuf));
				pbStruBuf += sizeof(SD_UINT32);

				dwAvgBitsPerSec = (*((SD_PUINT32)pbStruBuf));
				pbStruBuf += sizeof(SD_UINT32);

				dwBlockAlign = (*((SD_PUINT32)pbStruBuf));
				pbStruBuf += sizeof(SD_UINT32);

				if (dwStruBufSize == SDAUDIOMEDIAINFO_STRUSIZE_VER2)
				{
					enumAudioCFG = (SD_AUDIO_CHANNELCONFIGURATION)((*((SD_PINT32)pbStruBuf)));
					pbStruBuf += sizeof(SD_INT32);
					enumChannelSamplesFormat = (SD_CHANNELSAMPLE_FORMAT)((*((SD_PINT32)pbStruBuf)));
					pbStruBuf += sizeof(SD_INT32);
				}
				else
				{
					enumAudioCFG = SDAUDIOCFG_INDEPENDENT;
					enumChannelSamplesFormat = SDCHANNELSAMPLESFORMAT_Progressive;
				}
				return SD_TRUE;
			}
			return SD_FALSE;
		}
	};

	// 序列化支持
	SD_INT32 GetSerializationSize()
	{
		return  SerializationToPtr(SD_NULL, 0);
	};
	SD_INT32 SerializationToPtr(SD_UINT8* pBuffer, SD_INT32 iBufferSize)
	{
		SD_INT32 iPtrSize = 0;
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &dwStruSize, sizeof(dwStruSize));
		iPtrSize += sizeof(dwStruSize);
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &enumAudioType, sizeof(enumAudioType));
		iPtrSize += sizeof(enumAudioType);
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &dwAudioSubType, sizeof(dwAudioSubType));
		iPtrSize += sizeof(dwAudioSubType);
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &dwChannels, sizeof(dwChannels));
		iPtrSize += sizeof(dwChannels);
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &dwBitsPerSample, sizeof(dwBitsPerSample));
		iPtrSize += sizeof(dwBitsPerSample);
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &dwSamplesPerSec, sizeof(dwSamplesPerSec));
		iPtrSize += sizeof(dwSamplesPerSec);
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &dwAvgBitsPerSec, sizeof(dwAvgBitsPerSec));
		iPtrSize += sizeof(dwAvgBitsPerSec);
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &dwBlockAlign, sizeof(dwBlockAlign));
		iPtrSize += sizeof(dwBlockAlign);
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &enumAudioCFG, sizeof(enumAudioCFG));
		iPtrSize += sizeof(enumAudioCFG);
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &enumChannelSamplesFormat, sizeof(enumChannelSamplesFormat));
		iPtrSize += sizeof(enumChannelSamplesFormat);
		return iPtrSize;
	};
	SD_INT32 SerializationFromPtr(SD_UINT8* pBuffer, SD_INT32 iBufferSize)
	{
		SD_INT32 iPtrSize = 0;
		memcpy(&dwStruSize, pBuffer + iPtrSize, sizeof(dwStruSize));							iPtrSize += sizeof(dwStruSize);
		memcpy(&enumAudioType, pBuffer + iPtrSize, sizeof(enumAudioType));						iPtrSize += sizeof(enumAudioType);
		memcpy(&dwAudioSubType, pBuffer + iPtrSize, sizeof(dwAudioSubType));					iPtrSize += sizeof(dwAudioSubType);
		memcpy(&dwChannels, pBuffer + iPtrSize, sizeof(dwChannels));							iPtrSize += sizeof(dwChannels);
		memcpy(&dwBitsPerSample, pBuffer + iPtrSize, sizeof(dwBitsPerSample));					iPtrSize += sizeof(dwBitsPerSample);
		memcpy(&dwSamplesPerSec, pBuffer + iPtrSize, sizeof(dwSamplesPerSec));					iPtrSize += sizeof(dwSamplesPerSec);
		memcpy(&dwAvgBitsPerSec, pBuffer + iPtrSize, sizeof(dwAvgBitsPerSec));					iPtrSize += sizeof(dwAvgBitsPerSec);
		memcpy(&dwBlockAlign, pBuffer + iPtrSize, sizeof(dwBlockAlign));						iPtrSize += sizeof(dwBlockAlign);
		memcpy(&enumAudioCFG, pBuffer + iPtrSize, sizeof(enumAudioCFG));						iPtrSize += sizeof(enumAudioCFG);
		memcpy(&enumChannelSamplesFormat, pBuffer + iPtrSize, sizeof(enumChannelSamplesFormat));iPtrSize += sizeof(enumChannelSamplesFormat);
		return iPtrSize;
	};
};
typedef CSDArray<SDAudioMediaInfo, SDAudioMediaInfo&>	SDAudioMediaInfoArray;

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

//枚举所有可能的subtitle文件类型
//是否作为dwStreamSubType？MediaType为SDSTREAMTYPE_SUBTITLE
enum SD_SUBTITLE_TYPE//字幕流类型
{
    SDSUBSTYPE_UNKNOWN     = 0,
    SDSUBSTYPE_SUBRIP      = 1, //srt字幕格式
	SDSUBSTYPE_DVBSUBTITLE = 2, //TS 字幕
	SDSUBSTYPE_DVDSUBTITLE = 3, //DVD字幕
    SDSUBSTYPE_SSA1        = 4,
    SDSUBSTYPE_SSA2_4      = 5,
    SDSUBSTYPE_ASS         = 6,
	SDSUBSTYPE_CEA708CCES  = 7,//CEA-708-E DTVCC，708CC字幕，Video ES的user_data中
	SDSUBSTYPE_CEA708CCTS  = 8,//708CC字幕，作为独立PES，保存在TS流中
};
//得到字幕类型的名称
SD_INLINE CSDString GetSubtitleTypeHint(SD_SUBTITLE_TYPE enumSubtitleType)
{
	CSDString strHint = _T("Unknown");
	switch(enumSubtitleType)
	{
	case SDSUBSTYPE_SUBRIP:
		strHint = _T("subrip");
		break;
	case SDSUBSTYPE_SSA1:
		strHint = _T("Sub Station Alpha V1");
		break;
	case SDSUBSTYPE_SSA2_4:
		strHint = _T("Sub Station Alpha V2-4");
		break;
	case SDSUBSTYPE_ASS:
		strHint = _T("Advanced Sub Station Alpha");
		break;
	case SDSUBSTYPE_DVDSUBTITLE:
		strHint = _T("DVD Subtitle");
		break;
	case SDSUBSTYPE_DVBSUBTITLE:
		strHint = _T("DVB Subtitle");
		break;
	case SDSUBSTYPE_CEA708CCES:
		strHint = _T("CEA 708 Closed Caption(ES)");
		break;
	case SDSUBSTYPE_CEA708CCTS:
		strHint = _T("CEA 708 Closed Caption(PES)");
		break;
	}
	return strHint;
}
// 字幕信息描述
#define SDSUBTITLEMEDIAINFO_STRUSIZE_VER1 8
struct SDSubtitleMediaInfo
{
	SD_SUBTITLE_TYPE emStreamType;
	SD_UINT32  dwStreamSubType;

	SDSubtitleMediaInfo()
	{
		emStreamType = SDSUBSTYPE_UNKNOWN;
		dwStreamSubType = 0;
	};
	SDSubtitleMediaInfo(const SDSubtitleMediaInfo& other)
	{
		emStreamType = other.emStreamType;
		dwStreamSubType = other.dwStreamSubType;
	}
	SDSubtitleMediaInfo &operator = (const SDSubtitleMediaInfo &other)
	{
		emStreamType = other.emStreamType;
		dwStreamSubType = other.dwStreamSubType;

		return *this;
	};
	SD_BOOL operator==(const SDSubtitleMediaInfo& other)
	{
		if (emStreamType!= other.emStreamType)
			return SD_FALSE;
		if (dwStreamSubType != other.dwStreamSubType)

			return SD_FALSE;
		return SD_TRUE;
	}
	SD_BOOL operator!=(const SDSubtitleMediaInfo& other)
	{		
		if (emStreamType != other.emStreamType)
			return SD_TRUE;
		if (dwStreamSubType != other.dwStreamSubType)
			return SD_TRUE;

		return SD_FALSE;
	}
	SD_BOOL CloneBufPtr(SD_PVOID pStruBuf)
	{
		if (pStruBuf)
		{
			SD_PUINT8 pbStruBuf = (SD_UINT8*)pStruBuf;
			SD_UINT32 dwStruBufSize = (*(SD_UINT32*)pStruBuf);
			if (dwStruBufSize == SDSUBTITLEMEDIAINFO_STRUSIZE_VER1)
			{
				pbStruBuf += sizeof(SD_UINT32);

				emStreamType = (*(SD_SUBTITLE_TYPE*)pbStruBuf);
				pbStruBuf += sizeof(SD_SUBTITLE_TYPE);

				dwStreamSubType = (*(SD_UINT32*)pbStruBuf);
				pbStruBuf += sizeof(SD_UINT32);
				return SD_TRUE;				
			}
			return SD_FALSE;
		}
		return SD_FALSE;
	}
	// 序列化支持
	SD_INT32 GetSerializationSize()
	{
		return  SerializationToPtr(SD_NULL, 0);
	};
	SD_INT32 SerializationToPtr(SD_UINT8* pBuffer, SD_INT32 iBufferSize)
	{
		SD_INT32 iPtrSize = 0;
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &emStreamType, sizeof(emStreamType));
		iPtrSize += sizeof(emStreamType);
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &dwStreamSubType, sizeof(dwStreamSubType));
		iPtrSize += sizeof(dwStreamSubType);
		return iPtrSize;
	};
	SD_INT32 SerializationFromPtr(SD_UINT8* pBuffer, SD_INT32 iBufferSize)
	{
		SD_INT32 iPtrSize = 0;
		memcpy(&emStreamType, pBuffer + iPtrSize, sizeof(emStreamType));       iPtrSize += sizeof(emStreamType);
		memcpy(&dwStreamSubType, pBuffer + iPtrSize, sizeof(dwStreamSubType)); iPtrSize += sizeof(dwStreamSubType);
		return iPtrSize;
	};
};
typedef CSDArray<SDSubtitleMediaInfo, SDSubtitleMediaInfo&> SDSubtitleMediaInfoArray;

#define	SDSTREAMMEDIAINFO_STRUSIZE_VER1		100		//SDVIDEOMEDIAINFO_STRUSIZE_VER1(52)+SDAUDIOMEDIAINFO_STRUSIZE_VER2(32)+16
#define	SDSTREAMMEDIAINFO_STRUSIZE_VER2		160		//SDVIDEOMEDIAINFO_STRUSIZE_VER2(88)+SDAUDIOMEDIAINFO_STRUSIZE_VER2(40)+32
#define	SDSTREAMMEDIAINFO_STRUSIZE_VER3		168		//SDVIDEOMEDIAINFO_STRUSIZE_VER2(88)+SDAUDIOMEDIAINFO_STRUSIZE_VER2(40)+32+SDSUBTITLEMEDIAINFO_STRUSIZE_VER1(8)

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
	SDSubtitleMediaInfo    sSubtitleMediaInfo;             //视音频流(文件)中第一个字幕流的媒体属性.

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
		sSubtitleMediaInfo = other.sSubtitleMediaInfo;

		return *this;
	};

	SD_BOOL operator == (const SDStreamMediaInfo& other)
	{
		if (dwStruSize != other.dwStruSize)
			return SD_FALSE;
		if (dwTotalAverDataRateInBitsPerSec != other.dwTotalAverDataRateInBitsPerSec)
			return SD_FALSE;
		if (dwTotalMaxDataRateInBitsPerSec != other.dwTotalMaxDataRateInBitsPerSec)
			return SD_FALSE;
		if (dwTotalMinDataRateInBitsPerSec != other.dwTotalMinDataRateInBitsPerSec)
			return SD_FALSE;
		if (enumStreamMediaType != other.enumStreamMediaType)
			return SD_FALSE;
		if (dwStreamMediaSubType != other.dwStreamMediaSubType)
			return SD_FALSE;
		
		if ((dwVideoStreamCount == 0 && other.dwVideoStreamCount > 0) || 
			(dwVideoStreamCount > 0 && other.dwVideoStreamCount == 0))
			return SD_FALSE;
		if ((dwAudioStreamCount == 0 && other.dwAudioStreamCount > 0) || 
			(dwAudioStreamCount > 0 && other.dwAudioStreamCount == 0))
			return SD_FALSE;
		
		if (dwVideoStreamCount > 0)
		{
			if (sVideoMediaInfo != other.sVideoMediaInfo)			  
				return SD_FALSE;
		}
		if (dwAudioStreamCount > 0)
		{
			if (sAudioMediaInfo != other.sAudioMediaInfo)
				return SD_FALSE;
		}
		if (dwSubtitleStreamCount > 0)
		{
			if (sSubtitleMediaInfo != other.sSubtitleMediaInfo)
				return SD_FALSE;
		}
		return SD_TRUE;
	};

	SD_BOOL	CloneBufPtr(SD_PVOID pStruBuf)
	{
		if (pStruBuf)
		{
			SD_PUINT8	pbStruBuf = (SD_PUINT8)pStruBuf;
			SD_UINT32	dwStruBufSize = (*((SD_PUINT32)pStruBuf));

			if (dwStruBufSize == SDSTREAMMEDIAINFO_STRUSIZE_VER2)
			{
				pbStruBuf += sizeof(SD_UINT32);
				
				dwTotalAverDataRateInBitsPerSec = (*((SD_PUINT32)pbStruBuf));
				pbStruBuf += sizeof(SD_UINT32);

				dwTotalMaxDataRateInBitsPerSec = (*((SD_PUINT32)pbStruBuf));
				pbStruBuf += sizeof(SD_UINT32);

				dwTotalMinDataRateInBitsPerSec = (*((SD_PUINT32)pbStruBuf));
				pbStruBuf += sizeof(SD_UINT32);

				enumStreamMediaType = (SD_STREAM_TYPE)((*((SD_PINT32)pbStruBuf)));
				pbStruBuf += sizeof(SD_INT32);

				dwStreamMediaSubType = (*((SD_PUINT32)pbStruBuf));
				pbStruBuf += sizeof(SD_UINT32);

				dwVideoStreamCount = (*((SD_PUINT32)pbStruBuf));
				pbStruBuf += sizeof(SD_UINT32);
	
				sVideoMediaInfo.CloneBufPtr(pbStruBuf);
				pbStruBuf += SDVIDEOMEDIAINFO_STRUSIZE_VER2;

				dwAudioStreamCount = (*((SD_PUINT32)pbStruBuf));
				pbStruBuf += sizeof(SD_UINT32);

				sAudioMediaInfo.CloneBufPtr(pbStruBuf);
				pbStruBuf += SDAUDIOMEDIAINFO_STRUSIZE_VER2;

				return SD_TRUE;
			}
			else if (dwStruBufSize == SDSTREAMMEDIAINFO_STRUSIZE_VER3)
			{

				pbStruBuf += sizeof(SD_UINT32);
				
				dwTotalAverDataRateInBitsPerSec = (*((SD_PUINT32)pbStruBuf));
				pbStruBuf += sizeof(SD_UINT32);

				dwTotalMaxDataRateInBitsPerSec = (*((SD_PUINT32)pbStruBuf));
				pbStruBuf += sizeof(SD_UINT32);

				dwTotalMinDataRateInBitsPerSec = (*((SD_PUINT32)pbStruBuf));
				pbStruBuf += sizeof(SD_UINT32);

				enumStreamMediaType = (SD_STREAM_TYPE)((*((SD_PINT32)pbStruBuf)));
				pbStruBuf += sizeof(SD_INT32);

				dwStreamMediaSubType = (*((SD_PUINT32)pbStruBuf));
				pbStruBuf += sizeof(SD_UINT32);

				dwVideoStreamCount = (*((SD_PUINT32)pbStruBuf));
				pbStruBuf += sizeof(SD_UINT32);
	
				sVideoMediaInfo.CloneBufPtr(pbStruBuf);
				pbStruBuf += SDVIDEOMEDIAINFO_STRUSIZE_VER2;

				dwAudioStreamCount = (*((SD_PUINT32)pbStruBuf));
				pbStruBuf += sizeof(SD_UINT32);

				sAudioMediaInfo.CloneBufPtr(pbStruBuf);
				pbStruBuf += SDAUDIOMEDIAINFO_STRUSIZE_VER2;

				sSubtitleMediaInfo.CloneBufPtr(pbStruBuf);
				pbStruBuf += SDSUBTITLEMEDIAINFO_STRUSIZE_VER1;

				return SD_TRUE;
			}
			else 
			{
				SD_PUINT8	pbVideoStruBuf = pbStruBuf + 12;
				SD_UINT32	dwVideoStruBufSize = (*((SD_PUINT32)pbVideoStruBuf));

				SD_PUINT8	pbAudioStruBuf = pbVideoStruBuf + SDVIDEOMEDIAINFO_STRUSIZE_VER1 + 4;
				SD_UINT32	dwAudioStruBufSize = (*((SD_PUINT32)pbAudioStruBuf));

				if (dwVideoStruBufSize == SDVIDEOMEDIAINFO_STRUSIZE_VER1 &&
					dwAudioStruBufSize == SDAUDIOMEDIAINFO_STRUSIZE_VER1)
				{
					dwTotalAverDataRateInBitsPerSec = 0;
					dwTotalMaxDataRateInBitsPerSec = 0;
					dwTotalMinDataRateInBitsPerSec = 0;

					enumStreamMediaType = (SD_STREAM_TYPE)((*((SD_PINT32)pbStruBuf)));
					pbStruBuf += sizeof(SD_INT32);

					dwStreamMediaSubType = (*((SD_PUINT32)pbStruBuf));
					pbStruBuf += sizeof(SD_UINT32);

					dwVideoStreamCount = (*((SD_PUINT32)pbStruBuf));
					pbStruBuf += sizeof(SD_UINT32);
		
					sVideoMediaInfo.CloneBufPtr(pbStruBuf);
					pbStruBuf += SDVIDEOMEDIAINFO_STRUSIZE_VER1;

					dwAudioStreamCount = (*((SD_PUINT32)pbStruBuf));
					pbStruBuf += sizeof(SD_UINT32);

					sAudioMediaInfo.CloneBufPtr(pbStruBuf);
					pbStruBuf += SDAUDIOMEDIAINFO_STRUSIZE_VER1;

					return SD_TRUE;
				}
			}
		}
		return SD_FALSE;
	};

	SD_VIDEO_STANDARD	GetVideoStandard()
	{
		if (dwVideoStreamCount > 0)
			return sVideoMediaInfo.GetVideoStandard();
		else
			return SDVIDEOSTANDARD_UNKNOW;
	};

	// 序列化支持
	SD_INT32 GetSerializationSize()
	{
		return  SerializationToPtr(SD_NULL, 0);
	};
	SD_INT32 SerializationToPtr(SD_UINT8* pBuffer, SD_INT32 iBufferSize)
	{
		SD_INT32 iPtrSize = 0;
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &dwStruSize, sizeof(dwStruSize));
		iPtrSize += sizeof(dwStruSize);
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &dwTotalAverDataRateInBitsPerSec, sizeof(dwTotalAverDataRateInBitsPerSec));
		iPtrSize += sizeof(dwTotalAverDataRateInBitsPerSec);
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &dwTotalMaxDataRateInBitsPerSec, sizeof(dwTotalMaxDataRateInBitsPerSec));
		iPtrSize += sizeof(dwTotalMaxDataRateInBitsPerSec);
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &dwTotalMinDataRateInBitsPerSec, sizeof(dwTotalMinDataRateInBitsPerSec));
		iPtrSize += sizeof(dwTotalMinDataRateInBitsPerSec);
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &enumStreamMediaType, sizeof(enumStreamMediaType));
		iPtrSize += sizeof(enumStreamMediaType);
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &dwStreamMediaSubType, sizeof(dwStreamMediaSubType));
		iPtrSize += sizeof(dwStreamMediaSubType);
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &dwVideoStreamCount, sizeof(dwVideoStreamCount));
		iPtrSize += sizeof(dwVideoStreamCount);
		SD_INT32 iVideoInfoSize = sVideoMediaInfo.GetSerializationSize();
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &iVideoInfoSize, sizeof(iVideoInfoSize)); 
		iPtrSize += sizeof(iVideoInfoSize);
		if (SD_NULL != pBuffer)
		{
			sVideoMediaInfo.SerializationToPtr(pBuffer + iPtrSize, iVideoInfoSize);
		}
		iPtrSize += iVideoInfoSize;
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &dwAudioStreamCount, sizeof(dwAudioStreamCount));
		iPtrSize += sizeof(dwAudioStreamCount);
		SD_INT32 iAudioInfoSize = sAudioMediaInfo.GetSerializationSize();
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &iAudioInfoSize, sizeof(iAudioInfoSize)); 
		iPtrSize += sizeof(iAudioInfoSize);
		if (SD_NULL != pBuffer)
		{
			sAudioMediaInfo.SerializationToPtr(pBuffer + iPtrSize, iAudioInfoSize);
		}
		iPtrSize += iAudioInfoSize;
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &dwSubtitleStreamCount, sizeof(dwSubtitleStreamCount));
		iPtrSize += sizeof(dwSubtitleStreamCount);
		SD_INT32 iSubInfoSize = sSubtitleMediaInfo.GetSerializationSize();
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &iSubInfoSize, sizeof(iSubInfoSize)); 
		iPtrSize += sizeof(iSubInfoSize);
		if (SD_NULL != pBuffer)
		{
			sSubtitleMediaInfo.SerializationToPtr(pBuffer + iPtrSize, iSubInfoSize);
		}
		iPtrSize += iSubInfoSize;
		return iPtrSize;
	};
	SD_INT32 SerializationFromPtr(SD_UINT8* pBuffer, SD_INT32 iBufferSize)
	{
		SD_INT32 iPtrSize = 0;
		memcpy(&dwStruSize, pBuffer + iPtrSize, sizeof(dwStruSize));											iPtrSize += sizeof(dwStruSize);
		memcpy(&dwTotalAverDataRateInBitsPerSec, pBuffer + iPtrSize, sizeof(dwTotalAverDataRateInBitsPerSec));	iPtrSize += sizeof(dwTotalAverDataRateInBitsPerSec);
		memcpy(&dwTotalMaxDataRateInBitsPerSec, pBuffer + iPtrSize, sizeof(dwTotalMaxDataRateInBitsPerSec));	iPtrSize += sizeof(dwTotalMaxDataRateInBitsPerSec);
		memcpy(&dwTotalMinDataRateInBitsPerSec, pBuffer + iPtrSize, sizeof(dwTotalMinDataRateInBitsPerSec));	iPtrSize += sizeof(dwTotalMinDataRateInBitsPerSec);
		memcpy(&enumStreamMediaType, pBuffer + iPtrSize, sizeof(enumStreamMediaType));							iPtrSize += sizeof(enumStreamMediaType);
		memcpy(&dwStreamMediaSubType, pBuffer + iPtrSize, sizeof(dwStreamMediaSubType));						iPtrSize += sizeof(dwStreamMediaSubType);
		memcpy(&dwVideoStreamCount, pBuffer + iPtrSize, sizeof(dwVideoStreamCount));							iPtrSize += sizeof(dwVideoStreamCount);
		SD_INT32 iVideoInfoSize;
		memcpy(&iVideoInfoSize, pBuffer + iPtrSize, sizeof(iVideoInfoSize));									iPtrSize += sizeof(iVideoInfoSize);
		sVideoMediaInfo.SerializationFromPtr(pBuffer + iPtrSize, iVideoInfoSize);								iPtrSize += iVideoInfoSize;
		memcpy(&dwAudioStreamCount, pBuffer + iPtrSize, sizeof(dwAudioStreamCount));							iPtrSize += sizeof(dwAudioStreamCount);
		SD_INT32 iAudioInfoSize;
		memcpy(&iAudioInfoSize, pBuffer + iPtrSize, sizeof(iAudioInfoSize));									iPtrSize += sizeof(iAudioInfoSize);
		sAudioMediaInfo.SerializationFromPtr(pBuffer + iPtrSize, iAudioInfoSize);								iPtrSize += iAudioInfoSize;
		memcpy(&dwSubtitleStreamCount, pBuffer + iPtrSize, sizeof(dwSubtitleStreamCount));						iPtrSize += sizeof(dwSubtitleStreamCount);
		SD_INT32 iSubInfoSize;
		memcpy(&iSubInfoSize, pBuffer + iPtrSize, sizeof(iSubInfoSize));										iPtrSize += sizeof(iSubInfoSize);
		sSubtitleMediaInfo.SerializationFromPtr(pBuffer + iPtrSize, iSubInfoSize);								iPtrSize += iSubInfoSize;
		return iPtrSize;
	};
};
typedef CSDArray<SDStreamMediaInfo, SDStreamMediaInfo&>	SDStreamMediaInfoArray;

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
		sSubtitleMediaInfo = other.sSubtitleMediaInfo;
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
		sSubtitleMediaInfo = other.sSubtitleMediaInfo;

		llFileSize = 0;
		dwVideoFrameNum = 0;
		dwAudioSamplesNum = 0;
		dwSubtitleFrameNum = 0;
		
		return *this;
	};

	SD_BOOL	GetStreamMediaInfo(SDStreamMediaInfo *psInfo)
	{
		if (psInfo)
		{
			psInfo->dwStruSize = sizeof(SDStreamMediaInfo);
			psInfo->dwTotalAverDataRateInBitsPerSec = dwTotalAverDataRateInBitsPerSec;
			psInfo->dwTotalMaxDataRateInBitsPerSec = dwTotalMaxDataRateInBitsPerSec;
			psInfo->dwTotalMinDataRateInBitsPerSec = dwTotalMinDataRateInBitsPerSec;
			psInfo->enumStreamMediaType = enumStreamMediaType;
			psInfo->dwStreamMediaSubType = dwStreamMediaSubType;
			psInfo->dwVideoStreamCount = dwVideoStreamCount;
			psInfo->sVideoMediaInfo = sVideoMediaInfo;
			psInfo->dwAudioStreamCount = dwAudioStreamCount;
			psInfo->sAudioMediaInfo = sAudioMediaInfo;
			psInfo->dwSubtitleStreamCount = dwSubtitleStreamCount;
			psInfo->sSubtitleMediaInfo = sSubtitleMediaInfo;
			return SD_TRUE;
		}
		else
			return SD_FALSE;
	};
	// 序列化支持
	SD_INT32 GetSerializationSize()
	{
		return  SerializationToPtr(SD_NULL, 0);
	};
	SD_INT32 SerializationToPtr(SD_UINT8* pBuffer, SD_INT32 iBufferSize)
	{
		SD_INT32 iPtrSize = 0;
		SD_INT32 iTempSize = SDStreamMediaInfo::SerializationToPtr(SD_NULL, 0);
		if (SD_NULL != pBuffer)
		{
			SDStreamMediaInfo::SerializationToPtr(pBuffer, iBufferSize);
		}
		iPtrSize += iTempSize;
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &llFileSize, sizeof(llFileSize));
		iPtrSize += sizeof(llFileSize);
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &dwVideoFrameNum, sizeof(dwVideoFrameNum));
		iPtrSize += sizeof(dwVideoFrameNum);
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &dwAudioSamplesNum, sizeof(dwAudioSamplesNum));
		iPtrSize += sizeof(dwAudioSamplesNum);
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &dwSubtitleFrameNum, sizeof(dwSubtitleFrameNum));
		iPtrSize += sizeof(dwSubtitleFrameNum);
		return iPtrSize;
	};
	SD_INT32 SerializationFromPtr(SD_UINT8* pBuffer, SD_INT32 iBufferSize)
	{
		SD_INT32 iPtrSize = 0;
		SD_INT32 iTempSize = SDStreamMediaInfo::SerializationFromPtr(pBuffer, iBufferSize);
		iPtrSize += iTempSize;
		memcpy(&llFileSize, pBuffer + iPtrSize, sizeof(llFileSize));				 iPtrSize += sizeof(llFileSize);
		memcpy(&dwVideoFrameNum,pBuffer + iPtrSize, sizeof(dwVideoFrameNum));	     iPtrSize += sizeof(dwVideoFrameNum);
		memcpy(&dwAudioSamplesNum, pBuffer + iPtrSize, sizeof(dwAudioSamplesNum));	 iPtrSize += sizeof(dwAudioSamplesNum);
		memcpy(&dwSubtitleFrameNum, pBuffer + iPtrSize, sizeof(dwSubtitleFrameNum)); iPtrSize += sizeof(dwSubtitleFrameNum);
		return iPtrSize;
	};
};
typedef CSDArray<SDStreamMediaInfoEx, SDStreamMediaInfoEx&>	SDStreamMediaInfoExArray;

SD_INLINE SD_INT32 SerializationToPtr_CSDStringArray(CSDStringArray &astrName, SD_UINT8* pBuffer, SD_INT32 iBufferSize)
{
	SD_INT32 iPtrSize = 0;
	SD_INT32 iStringCount = astrName.GetSize();
	if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &iStringCount, sizeof(iStringCount));
	iPtrSize += sizeof(iStringCount);
	if (0 == iStringCount)
	{
		return iPtrSize;
	}
	for (SD_INT32 i = 0; i < iStringCount; i++)
	{
		char Name[1204];
		SD_INT32 nSizeInChar = 1024;
		CSDString str = astrName[i];
		SD_INT32 iNameSize = str.GetCharBuffer(Name, nSizeInChar) + 1; // 将末尾NULL加上
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &iNameSize, sizeof(iNameSize)); // 记录strFileName字符缓冲大小
		iPtrSize += sizeof(iNameSize);
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, Name, iNameSize);
		iPtrSize += iNameSize;
	}
	return iPtrSize;
}
SD_INLINE SD_INT32 GetSerializationSize_CSDStringArray(CSDStringArray	&astrName)
{
	SD_INT32 iPtrSize = SerializationToPtr_CSDStringArray(astrName, SD_NULL, 0);
	return iPtrSize;
}
SD_INLINE SD_INT32 SerializationFromPtr_CSDStringArray(SD_UINT8* pBuffer, SD_INT32 iBufferSize, CSDStringArray &astrName)
{
	astrName.RemoveAll();
	SD_INT32 iPtrSize = 0;
	SD_INT32 iStringCount;
	memcpy(&iStringCount, pBuffer + iPtrSize,  sizeof(iStringCount)); iPtrSize += sizeof(iStringCount);
	if (0 == iStringCount)
	{
		return iPtrSize;
	}
	for (SD_INT32 i = 0; i < iStringCount; i++)
	{
		SD_INT32 iNameSize;
		memcpy(&iNameSize, pBuffer + iPtrSize,  sizeof(iNameSize)); iPtrSize += sizeof(iNameSize);
		CSDString str(SD_LPCSTR(pBuffer + iPtrSize));               iPtrSize += iNameSize;   
		astrName.Add(str);
	}
	return iPtrSize;
}

struct SDSingleProgramStreamMediaInfo		// 单节目视音频流(文件)属性
{
	CSDString					strProgramName;						// 单节目视音频流名称
	SD_STREAM_TYPE				enumStreamMediaType;				// 类型
	SD_UINT32					dwStreamMediaSubType;				// 子类型,子类型定义随类型不同而不同
	SD_UINT32					dwTotalAverDataRateInBitsPerSec;	// 总体平均码率, based on *****bits/S******
	SD_UINT32					dwTotalMaxDataRateInBitsPerSec;		// 总体最大码率, based on *****bits/S******
	SD_UINT32					dwTotalMinDataRateInBitsPerSec;		// 总体最小码率, based on *****bits/S******
	
	SD_UINT32					dwVideoStreamCount;					// 包含视频流的数量
	CSDStringArray				astrVideoStreamName;				// 视频流名称
	SDVideoMediaInfoArray		asVideoMediaInfo;					// 视音频流(文件)中视频流的媒体属性.
	CSDStringArray				astrVideoStreamType;				// 视频流种类
	CSDStringArray				astrVideoStreamCaption;				// 视频流描述

	SD_UINT32					dwAudioStreamCount;					// 包含音频流的数量
	CSDStringArray				astrAudioStreamName;				// 音频流名称
	SDAudioMediaInfoArray		asAudioMediaInfo;					// 视音频流(文件)中音频流的媒体属性
	CSDStringArray				astrAudioStreamLanguageType;		// 音频流语言种类
	CSDStringArray				astrAudioStreamLanguageCaption;		// 音频流语言描述

	SD_UINT32					dwSubTitleStreamCount;				// 包含字幕流的数量
	CSDStringArray				astrSubTitleStreamName;				// 字幕流流名称

	SDSubtitleMediaInfoArray  asSubTitleMediaInfo;                // 字幕流的媒体属性
	CSDStringArray				astrSubTitleStreamLanguageType;		// 字幕流语言种类
	CSDStringArray				astrSubTitleStreamLanguageCaption;	// 字幕流语言描述

	SDSingleProgramStreamMediaInfo()
	{
		strProgramName = _T("");
		enumStreamMediaType = SDSTREAMTYPE_UNKNOWN;
		dwStreamMediaSubType = 0;
		dwTotalAverDataRateInBitsPerSec = 0;
		dwTotalMaxDataRateInBitsPerSec = 0;
		dwTotalMinDataRateInBitsPerSec = 0;
		dwVideoStreamCount = 0;
		dwAudioStreamCount = 0;
		dwSubTitleStreamCount = 0;
	};

	SDSingleProgramStreamMediaInfo(const SDSingleProgramStreamMediaInfo &other)
	{
		*this = other;
	};

	SDSingleProgramStreamMediaInfo(SDStreamMediaInfo *psStreamMediaInfo)
	{
		strProgramName = _T("");
		enumStreamMediaType = SDSTREAMTYPE_UNKNOWN;
		dwStreamMediaSubType = 0;
		dwTotalAverDataRateInBitsPerSec = 0;
		dwTotalMaxDataRateInBitsPerSec = 0;
		dwTotalMinDataRateInBitsPerSec = 0;
		dwVideoStreamCount = 0;
		dwAudioStreamCount = 0;
		dwSubTitleStreamCount = 0;

		if (psStreamMediaInfo)
		{
			enumStreamMediaType = psStreamMediaInfo->enumStreamMediaType;
			dwStreamMediaSubType = psStreamMediaInfo->dwStreamMediaSubType;
			dwTotalAverDataRateInBitsPerSec = psStreamMediaInfo->dwTotalAverDataRateInBitsPerSec;
			dwTotalMaxDataRateInBitsPerSec = psStreamMediaInfo->dwTotalMaxDataRateInBitsPerSec;
			dwTotalMinDataRateInBitsPerSec = psStreamMediaInfo->dwTotalMinDataRateInBitsPerSec;
			dwVideoStreamCount = ((psStreamMediaInfo->dwVideoStreamCount > 0) ? 1 : 0);
			dwAudioStreamCount = ((psStreamMediaInfo->dwAudioStreamCount > 0) ? 1 : 0);
			dwSubTitleStreamCount = ((psStreamMediaInfo->dwSubtitleStreamCount > 0) ? 1 : 0);//version 3 add
			CSDString strTemp = _T("");
			if (dwVideoStreamCount == 1)
			{
				asVideoMediaInfo.Add(psStreamMediaInfo->sVideoMediaInfo);
				astrVideoStreamName.Add(strTemp);
				astrVideoStreamType.Add(strTemp);
				astrVideoStreamCaption.Add(strTemp);
			}
			if (dwAudioStreamCount == 1)
			{
				asAudioMediaInfo.Add(psStreamMediaInfo->sAudioMediaInfo);
				astrAudioStreamName.Add(strTemp);
				astrAudioStreamLanguageType.Add(strTemp);
				astrAudioStreamLanguageCaption.Add(strTemp);
			}
			if (dwSubTitleStreamCount == 1)
			{
				asSubTitleMediaInfo.Add(psStreamMediaInfo->sSubtitleMediaInfo);
				astrSubTitleStreamName.Add(strTemp);
				astrSubTitleStreamLanguageType.Add(strTemp);	
				astrSubTitleStreamLanguageCaption.Add(strTemp);
			}
		}
	};

	~SDSingleProgramStreamMediaInfo()
	{
		RemoveAllStreamInfo();
	};

	SD_VOID	RemoveAllStreamInfo()
	{
		dwVideoStreamCount = 0;
		dwAudioStreamCount = 0;
		dwSubTitleStreamCount = 0;

		astrVideoStreamName.RemoveAll();
		asVideoMediaInfo.RemoveAll();
		astrVideoStreamType.RemoveAll();
		astrVideoStreamCaption.RemoveAll();

		astrAudioStreamName.RemoveAll();
		asAudioMediaInfo.RemoveAll();
		astrAudioStreamLanguageType.RemoveAll();
		astrAudioStreamLanguageCaption.RemoveAll();

		astrSubTitleStreamName.RemoveAll();
		asSubTitleMediaInfo.RemoveAll();
		astrSubTitleStreamLanguageType.RemoveAll();
		astrSubTitleStreamLanguageCaption.RemoveAll();
	};

	SDSingleProgramStreamMediaInfo& operator = (const SDSingleProgramStreamMediaInfo& other)
	{
		strProgramName = other.strProgramName;
		enumStreamMediaType = other.enumStreamMediaType;
		dwStreamMediaSubType = other.dwStreamMediaSubType;
		dwTotalAverDataRateInBitsPerSec = other.dwTotalAverDataRateInBitsPerSec;
		dwTotalMaxDataRateInBitsPerSec = other.dwTotalMaxDataRateInBitsPerSec;
		dwTotalMinDataRateInBitsPerSec = other.dwTotalMinDataRateInBitsPerSec;

		dwVideoStreamCount = other.dwVideoStreamCount;
		astrVideoStreamName.Copy(other.astrVideoStreamName);
		asVideoMediaInfo.Copy(other.asVideoMediaInfo);
		astrVideoStreamType.Copy(other.astrVideoStreamType);
		astrVideoStreamCaption.Copy(other.astrVideoStreamCaption);

		dwAudioStreamCount = other.dwAudioStreamCount;
		astrAudioStreamName.Copy(other.astrAudioStreamName);
		asAudioMediaInfo.Copy(other.asAudioMediaInfo);
		astrAudioStreamLanguageType.Copy(other.astrAudioStreamLanguageType);
		astrAudioStreamLanguageCaption.Copy(other.astrAudioStreamLanguageCaption);

		dwSubTitleStreamCount = other.dwSubTitleStreamCount;
		astrSubTitleStreamName.Copy(other.astrSubTitleStreamName);
		asSubTitleMediaInfo.Copy(other.asSubTitleMediaInfo);
		astrSubTitleStreamLanguageType.Copy(other.astrSubTitleStreamLanguageType);
		astrSubTitleStreamLanguageCaption.Copy(other.astrSubTitleStreamLanguageCaption);
		return *this;
	};

	SD_BOOL	GetStreamMediaInfo(SDStreamMediaInfo *psStreamMediaInfo, SD_UINT32 dwVideoStreamNo = 0, SD_UINT32 dwAudioStreamNo = 0)
	{
		if (psStreamMediaInfo == NULL)
			return SD_FALSE;
		psStreamMediaInfo->dwStruSize = sizeof(SDStreamMediaInfo);
		psStreamMediaInfo->enumStreamMediaType = enumStreamMediaType;
		psStreamMediaInfo->dwStreamMediaSubType = dwStreamMediaSubType;
		psStreamMediaInfo->dwTotalAverDataRateInBitsPerSec = dwTotalAverDataRateInBitsPerSec;
		psStreamMediaInfo->dwTotalMaxDataRateInBitsPerSec = dwTotalMaxDataRateInBitsPerSec;
		psStreamMediaInfo->dwTotalMinDataRateInBitsPerSec = dwTotalMinDataRateInBitsPerSec;
		psStreamMediaInfo->dwVideoStreamCount = dwVideoStreamCount;
		psStreamMediaInfo->dwAudioStreamCount = dwAudioStreamCount;
		if (dwVideoStreamCount > 0)
		{
			if (dwVideoStreamNo >= dwVideoStreamCount || dwVideoStreamNo >= asVideoMediaInfo.GetDWSize())
				return SD_FALSE;
			else
				psStreamMediaInfo->sVideoMediaInfo = asVideoMediaInfo[dwVideoStreamNo];
		}
		if (dwAudioStreamCount > 0)
		{
			if (dwAudioStreamNo >= dwAudioStreamCount || dwAudioStreamNo >= asAudioMediaInfo.GetDWSize())
				return SD_FALSE;
			else
				psStreamMediaInfo->sAudioMediaInfo = asAudioMediaInfo[dwAudioStreamNo];
		}

		return SD_TRUE;
	};

	// 序列化支持
	SD_INT32 GetSerializationSize()
	{
		return  SerializationToPtr(SD_NULL, 0);
	};
	SD_INT32 SerializationToPtr(SD_UINT8* pBuffer, SD_INT32 iBufferSize)
	{
		SD_INT32 iPtrSize = 0;
		char Name[1204];
		SD_INT32 nSizeInChar = 1024;
		SD_INT32 iNameSize = strProgramName.GetCharBuffer(Name, nSizeInChar) + 1; // 将末尾NULL加上
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &iNameSize, sizeof(iNameSize)); // 记录strFileName字符缓冲大小
		iPtrSize += sizeof(iNameSize);
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, Name, iNameSize); // 记录strFileName字符数据
		iPtrSize += iNameSize;
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &enumStreamMediaType, sizeof(enumStreamMediaType));
		iPtrSize += sizeof(enumStreamMediaType);
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &dwStreamMediaSubType, sizeof(dwStreamMediaSubType));
		iPtrSize += sizeof(dwStreamMediaSubType);
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &dwTotalAverDataRateInBitsPerSec, sizeof(dwTotalAverDataRateInBitsPerSec));
		iPtrSize += sizeof(dwTotalAverDataRateInBitsPerSec);
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &dwTotalMaxDataRateInBitsPerSec, sizeof(dwTotalMaxDataRateInBitsPerSec));
		iPtrSize += sizeof(dwTotalMaxDataRateInBitsPerSec);
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &dwTotalMinDataRateInBitsPerSec, sizeof(dwTotalMinDataRateInBitsPerSec));
		iPtrSize += sizeof(dwTotalMinDataRateInBitsPerSec);

		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &dwVideoStreamCount, sizeof(dwVideoStreamCount));
		iPtrSize += sizeof(dwVideoStreamCount);
		SD_INT32 iastrVideoStreamNameSize = GetSerializationSize_CSDStringArray(astrVideoStreamName);
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &iastrVideoStreamNameSize, sizeof(iastrVideoStreamNameSize));
		iPtrSize += sizeof(iastrVideoStreamNameSize);
		if (SD_NULL != pBuffer) SerializationToPtr_CSDStringArray(astrVideoStreamName, pBuffer + iPtrSize, iastrVideoStreamNameSize);
		iPtrSize += iastrVideoStreamNameSize;
		SD_INT32 iVideoMediaInfoCount = asVideoMediaInfo.GetSize();
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &iVideoMediaInfoCount, sizeof(iVideoMediaInfoCount));
		iPtrSize += sizeof(iVideoMediaInfoCount);
		for (SD_INT32 i = 0; i < iVideoMediaInfoCount; i++)
		{
			SD_INT32 iVideoInfoSize = asVideoMediaInfo[i].GetSerializationSize();
			if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &iVideoInfoSize, sizeof(iVideoInfoSize));
			iPtrSize += sizeof(iVideoInfoSize);
			if (SD_NULL != pBuffer)
			{
				asVideoMediaInfo[i].SerializationToPtr(pBuffer + iPtrSize, iVideoInfoSize);
			}
			iPtrSize += iVideoInfoSize;
		}
		SD_INT32 iastrVideoStreamNameTypeSize = GetSerializationSize_CSDStringArray(astrVideoStreamType);
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &iastrVideoStreamNameTypeSize, sizeof(iastrVideoStreamNameTypeSize));
		iPtrSize += sizeof(iastrVideoStreamNameTypeSize);
		if (SD_NULL != pBuffer) SerializationToPtr_CSDStringArray(astrVideoStreamType, pBuffer + iPtrSize, iastrVideoStreamNameTypeSize);
		iPtrSize += iastrVideoStreamNameTypeSize;
		SD_INT32 iastrVideoStreamCaptionSize = GetSerializationSize_CSDStringArray(astrVideoStreamCaption);
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &iastrVideoStreamCaptionSize, sizeof(iastrVideoStreamCaptionSize));
		iPtrSize += sizeof(iastrVideoStreamCaptionSize);
		if (SD_NULL != pBuffer) SerializationToPtr_CSDStringArray(astrVideoStreamCaption, pBuffer + iPtrSize, iastrVideoStreamCaptionSize);
		iPtrSize += iastrVideoStreamCaptionSize;
		
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &dwAudioStreamCount, sizeof(dwAudioStreamCount));
		iPtrSize += sizeof(dwAudioStreamCount);
		SD_INT32 iastrAudioStreamNameSize = GetSerializationSize_CSDStringArray(astrAudioStreamName);
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &iastrAudioStreamNameSize, sizeof(iastrAudioStreamNameSize));
		iPtrSize += sizeof(iastrAudioStreamNameSize);
		if (SD_NULL != pBuffer) SerializationToPtr_CSDStringArray(astrAudioStreamName, pBuffer + iPtrSize, iastrAudioStreamNameSize);
		iPtrSize += iastrAudioStreamNameSize;
		SD_INT32 iAudioMediaInfoCount = asAudioMediaInfo.GetSize();
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &iAudioMediaInfoCount, sizeof(iAudioMediaInfoCount));
		iPtrSize += sizeof(iAudioMediaInfoCount);
		for (SD_INT32 i = 0; i < iAudioMediaInfoCount; i++)
		{
			SD_INT32 iAudioInfoSize = asAudioMediaInfo[i].GetSerializationSize();
			if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &iAudioInfoSize, sizeof(iAudioInfoSize));
			iPtrSize += sizeof(iAudioInfoSize);
			if (SD_NULL != pBuffer)
			{
				asAudioMediaInfo[i].SerializationToPtr(pBuffer + iPtrSize, iAudioInfoSize);
			}
			iPtrSize += iAudioInfoSize;
		}
		SD_INT32 iastrAudioStreamLanguageTypeSize = GetSerializationSize_CSDStringArray(astrAudioStreamLanguageType);
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &iastrAudioStreamLanguageTypeSize, sizeof(iastrAudioStreamLanguageTypeSize));
		iPtrSize += sizeof(iastrAudioStreamLanguageTypeSize);
		if (SD_NULL != pBuffer) SerializationToPtr_CSDStringArray(astrAudioStreamLanguageType, pBuffer + iPtrSize, iastrAudioStreamLanguageTypeSize);
		iPtrSize += iastrAudioStreamLanguageTypeSize;
		SD_INT32 iastrAudioStreamLanguageCaptionSize = GetSerializationSize_CSDStringArray(astrAudioStreamLanguageCaption);
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &iastrAudioStreamLanguageCaptionSize, sizeof(iastrAudioStreamLanguageCaptionSize));
		iPtrSize += sizeof(iastrAudioStreamLanguageCaptionSize);
		if (SD_NULL != pBuffer) SerializationToPtr_CSDStringArray(astrAudioStreamLanguageCaption, pBuffer + iPtrSize, iastrAudioStreamLanguageCaptionSize);
		iPtrSize += iastrAudioStreamLanguageCaptionSize;

		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &dwSubTitleStreamCount, sizeof(dwSubTitleStreamCount));
		iPtrSize += sizeof(dwSubTitleStreamCount);
		SD_INT32 iastrSubTitleStreamNameSize = GetSerializationSize_CSDStringArray(astrSubTitleStreamName);
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &iastrSubTitleStreamNameSize, sizeof(iastrSubTitleStreamNameSize));
		iPtrSize += sizeof(iastrSubTitleStreamNameSize);
		if (SD_NULL != pBuffer) SerializationToPtr_CSDStringArray(astrSubTitleStreamName, pBuffer + iPtrSize, iastrSubTitleStreamNameSize);
		iPtrSize += iastrSubTitleStreamNameSize;
		SD_INT32 iSubTitleMediaInfoCount = asSubTitleMediaInfo.GetSize();
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &iSubTitleMediaInfoCount, sizeof(iSubTitleMediaInfoCount));
		iPtrSize += sizeof(iSubTitleMediaInfoCount);
		for (SD_INT32 i = 0; i < iSubTitleMediaInfoCount; i++)
		{
			SD_INT32 iSubTitleInfoSize = asSubTitleMediaInfo[i].GetSerializationSize();
			if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &iSubTitleInfoSize, sizeof(iSubTitleInfoSize));
			iPtrSize += sizeof(iSubTitleInfoSize);
			if (SD_NULL != pBuffer)
			{
				asSubTitleMediaInfo[i].SerializationToPtr(pBuffer + iPtrSize, iSubTitleInfoSize);
			}
			iPtrSize += iSubTitleInfoSize;
		}
		SD_INT32 iastrSubTitleStreamLanguageTypeSize = GetSerializationSize_CSDStringArray(astrSubTitleStreamLanguageType);
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &iastrSubTitleStreamLanguageTypeSize, sizeof(iastrSubTitleStreamLanguageTypeSize));
		iPtrSize += sizeof(iastrSubTitleStreamLanguageTypeSize);
		if (SD_NULL != pBuffer) SerializationToPtr_CSDStringArray(astrSubTitleStreamLanguageType, pBuffer + iPtrSize, iastrSubTitleStreamLanguageTypeSize);
		iPtrSize += iastrSubTitleStreamLanguageTypeSize;
		SD_INT32 iastrSubTitleStreamLanguageCaptionSize = GetSerializationSize_CSDStringArray(astrSubTitleStreamLanguageCaption);
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &iastrSubTitleStreamLanguageCaptionSize, sizeof(iastrSubTitleStreamLanguageCaptionSize));
		iPtrSize += sizeof(iastrSubTitleStreamLanguageCaptionSize);
		if (SD_NULL != pBuffer) SerializationToPtr_CSDStringArray(astrSubTitleStreamLanguageCaption, pBuffer + iPtrSize, iastrSubTitleStreamLanguageCaptionSize);
		iPtrSize += iastrSubTitleStreamLanguageCaptionSize;
		return iPtrSize;
	};
	SD_INT32 SerializationFromPtr(SD_UINT8* pBuffer, SD_INT32 iBufferSize)
	{
		SD_INT32 iPtrSize = 0;
		SD_INT32 iNameSize;
		memcpy(&iNameSize, pBuffer + iPtrSize, sizeof(iNameSize));  iPtrSize += sizeof(iNameSize);
		if (iNameSize > 0)
		{
			CSDString str(SD_LPCSTR(pBuffer + iPtrSize));
			strProgramName = str;
			iPtrSize += iNameSize;
		}
		memcpy(&enumStreamMediaType, pBuffer + iPtrSize, sizeof(enumStreamMediaType));							iPtrSize += sizeof(enumStreamMediaType);
		memcpy(&dwStreamMediaSubType, pBuffer + iPtrSize, sizeof(dwStreamMediaSubType));						iPtrSize += sizeof(dwStreamMediaSubType);
		memcpy(&dwTotalAverDataRateInBitsPerSec, pBuffer + iPtrSize, sizeof(dwTotalAverDataRateInBitsPerSec));	iPtrSize += sizeof(dwTotalAverDataRateInBitsPerSec);
		memcpy(&dwTotalMaxDataRateInBitsPerSec, pBuffer + iPtrSize, sizeof(dwTotalMaxDataRateInBitsPerSec));	iPtrSize += sizeof(dwTotalMaxDataRateInBitsPerSec);
		memcpy(&dwTotalMinDataRateInBitsPerSec, pBuffer + iPtrSize, sizeof(dwTotalMinDataRateInBitsPerSec));	iPtrSize += sizeof(dwTotalMinDataRateInBitsPerSec);
		memcpy(&dwVideoStreamCount, pBuffer + iPtrSize, sizeof(dwVideoStreamCount));							iPtrSize += sizeof(dwVideoStreamCount);
		SD_INT32 iastrVideoStreamNameSize;
		memcpy(&iastrVideoStreamNameSize, pBuffer + iPtrSize, sizeof(iastrVideoStreamNameSize));				iPtrSize += sizeof(iastrVideoStreamNameSize);
		SerializationFromPtr_CSDStringArray(pBuffer + iPtrSize, iastrVideoStreamNameSize, astrVideoStreamName);	iPtrSize += iastrVideoStreamNameSize;
		SD_INT32 iVideoMediaInfoCount;
		memcpy(&iVideoMediaInfoCount, pBuffer + iPtrSize, sizeof(iVideoMediaInfoCount));						iPtrSize += sizeof(iVideoMediaInfoCount);
		for (SD_INT32 i = 0; i < iVideoMediaInfoCount; i++)
		{
			SD_INT32 iVideoInfoSize;
			memcpy(&iVideoInfoSize, pBuffer + iPtrSize, sizeof(iVideoInfoSize));								iPtrSize += sizeof(iVideoInfoSize);
			asVideoMediaInfo[i].SerializationFromPtr(pBuffer + iPtrSize, iVideoInfoSize);						iPtrSize += iVideoInfoSize;
		}
		SD_INT32 iastrVideoStreamNameTypeSize;;
		memcpy(&iastrVideoStreamNameTypeSize,pBuffer + iPtrSize, sizeof(iastrVideoStreamNameTypeSize));			iPtrSize += sizeof(iastrVideoStreamNameTypeSize);
		SerializationFromPtr_CSDStringArray(pBuffer + iPtrSize, iastrVideoStreamNameTypeSize, astrVideoStreamType); iPtrSize += iastrVideoStreamNameTypeSize;
		SD_INT32 iastrVideoStreamCaptionSize; 
		memcpy(&iastrVideoStreamCaptionSize, pBuffer + iPtrSize, sizeof(iastrVideoStreamCaptionSize));			iPtrSize += sizeof(iastrVideoStreamCaptionSize);
		SerializationFromPtr_CSDStringArray(pBuffer + iPtrSize, iastrVideoStreamCaptionSize, astrVideoStreamCaption); iPtrSize += iastrVideoStreamCaptionSize;
		
		memcpy(&dwAudioStreamCount, pBuffer + iPtrSize, sizeof(dwAudioStreamCount));							iPtrSize += sizeof(dwAudioStreamCount);
		SD_INT32 iastrAudioStreamNameSize;
		memcpy(&iastrAudioStreamNameSize, pBuffer + iPtrSize, sizeof(iastrAudioStreamNameSize));			    iPtrSize += sizeof(iastrAudioStreamNameSize);
		SerializationFromPtr_CSDStringArray(pBuffer + iPtrSize, iastrAudioStreamNameSize, astrAudioStreamName); iPtrSize += iastrAudioStreamNameSize;
		SD_INT32 iAudioMediaInfoCount;
		memcpy(&iAudioMediaInfoCount, pBuffer + iPtrSize, sizeof(iAudioMediaInfoCount));						iPtrSize += sizeof(iAudioMediaInfoCount);
		for (SD_INT32 i = 0; i < iAudioMediaInfoCount; i++)
		{
			SD_INT32 iAudioInfoSize;
			memcpy(&iAudioInfoSize, pBuffer + iPtrSize, sizeof(iAudioInfoSize));								iPtrSize += sizeof(iAudioInfoSize);
			asAudioMediaInfo[i].SerializationFromPtr(pBuffer + iPtrSize, iAudioInfoSize);						iPtrSize += iAudioInfoSize;
		}
		SD_INT32 iastrAudioStreamLanguageTypeSize;
		memcpy(&iastrAudioStreamLanguageTypeSize, pBuffer + iPtrSize, sizeof(iastrAudioStreamLanguageTypeSize));		iPtrSize += sizeof(iastrAudioStreamLanguageTypeSize);
		SerializationFromPtr_CSDStringArray(pBuffer + iPtrSize, iastrAudioStreamLanguageTypeSize,  astrAudioStreamLanguageType); iPtrSize += iastrAudioStreamLanguageTypeSize;
		SD_INT32 iastrAudioStreamLanguageCaptionSize;
		memcpy(&iastrAudioStreamLanguageCaptionSize, pBuffer + iPtrSize, sizeof(iastrAudioStreamLanguageCaptionSize)); iPtrSize += sizeof(iastrAudioStreamLanguageCaptionSize);
		SerializationFromPtr_CSDStringArray(pBuffer + iPtrSize, iastrAudioStreamLanguageCaptionSize, astrAudioStreamLanguageCaption); iPtrSize += iastrAudioStreamLanguageCaptionSize;

		memcpy(&dwSubTitleStreamCount,pBuffer + iPtrSize, sizeof(dwSubTitleStreamCount));						iPtrSize += sizeof(dwSubTitleStreamCount);
		SD_INT32 iastrSubTitleStreamNameSize;
		memcpy(&iastrSubTitleStreamNameSize,pBuffer + iPtrSize, sizeof(iastrSubTitleStreamNameSize));			iPtrSize += sizeof(iastrSubTitleStreamNameSize);
		SerializationFromPtr_CSDStringArray(pBuffer + iPtrSize, iastrSubTitleStreamNameSize, astrSubTitleStreamName); iPtrSize += iastrSubTitleStreamNameSize;
		SD_INT32 iSubTitleMediaInfoCount;
		memcpy(&iSubTitleMediaInfoCount, pBuffer + iPtrSize, sizeof(iSubTitleMediaInfoCount));					iPtrSize += sizeof(iSubTitleMediaInfoCount);
		for (SD_INT32 i = 0; i < iSubTitleMediaInfoCount; i++)
		{
			SD_INT32 iSubTitleInfoSize;
			memcpy(&iSubTitleInfoSize, pBuffer + iPtrSize, sizeof(iSubTitleInfoSize));							iPtrSize += sizeof(iSubTitleInfoSize);
			asSubTitleMediaInfo[i].SerializationFromPtr(pBuffer + iPtrSize, iSubTitleInfoSize); 				iPtrSize += iSubTitleInfoSize;
		}
		SD_INT32 iastrSubTitleStreamLanguageTypeSize;
		memcpy(&iastrSubTitleStreamLanguageTypeSize, pBuffer + iPtrSize, sizeof(iastrSubTitleStreamLanguageTypeSize)); iPtrSize += sizeof(iastrSubTitleStreamLanguageTypeSize);
		SerializationFromPtr_CSDStringArray(pBuffer + iPtrSize, iastrSubTitleStreamLanguageTypeSize, astrSubTitleStreamLanguageType); iPtrSize += iastrSubTitleStreamLanguageTypeSize;
		SD_INT32 iastrSubTitleStreamLanguageCaptionSize;
		memcpy(&iastrSubTitleStreamLanguageCaptionSize, pBuffer + iPtrSize, sizeof(iastrSubTitleStreamLanguageCaptionSize)); iPtrSize += sizeof(iastrSubTitleStreamLanguageCaptionSize);
		SerializationFromPtr_CSDStringArray(pBuffer + iPtrSize, iastrSubTitleStreamLanguageCaptionSize, astrSubTitleStreamLanguageCaption);	iPtrSize += iastrSubTitleStreamLanguageCaptionSize;
		return iPtrSize;
	};
};
typedef CSDArray<SDSingleProgramStreamMediaInfo*, SDSingleProgramStreamMediaInfo*&>	SDSingleProgramStreamMediaInfoArray;

SD_INLINE SD_VOID SDRelease(SDSingleProgramStreamMediaInfoArray *paDataArray)
{
	if (paDataArray) 
	{
		SD_UINT32	size = paDataArray->GetDWSize();
		for (SD_UINT32 i=0; i<size; i++) 
		{
			SDSingleProgramStreamMediaInfo *pElement = paDataArray->GetAt(i);
			delete pElement;
		}
		paDataArray->RemoveAll();
	}
};

SD_INLINE SD_BOOL SDClone(SDSingleProgramStreamMediaInfoArray *pNewData, const SDSingleProgramStreamMediaInfoArray *pOldData)
{
	if (pNewData == SD_NULL || pOldData == SD_NULL)
		return SD_FALSE;

	SDRelease(pNewData);

	SD_UINT32 size = pOldData->GetDWSize();
	for (SD_UINT32 i=0; i<size; i++) 
	{
		SDSingleProgramStreamMediaInfo *pNewElement = new SDSingleProgramStreamMediaInfo;
		SDSingleProgramStreamMediaInfo *pOldElement = pOldData->GetAt(i);
		(*pNewElement) = (*pOldElement);
		pNewData->Add(pNewElement);
	}
	return SD_TRUE;
};

struct SDSingleProgramStreamMediaInfoEx : public SDSingleProgramStreamMediaInfo		// 单节目视音频流(文件)扩展属性
{
	SD_UINT64		llFileSize;				//文件大小
	CSDUINT32Array	adwVideoFrameNum;		//视频流数据的长度。(Unit:Frame)
	CSDUINT32Array	adwAudioSamplesNum;		//音频流数据长度	 (Unit:Sample)
	CSDUINT32Array	adwSubTitleFrameNum;	//字幕流数据的长度。(Unit:Frame)

	SDSingleProgramStreamMediaInfoEx()
	{
		llFileSize = 0;
	};

	~SDSingleProgramStreamMediaInfoEx()
	{
		astrVideoStreamName.RemoveAll();
		asVideoMediaInfo.RemoveAll();
		astrVideoStreamType.RemoveAll();
		astrVideoStreamCaption.RemoveAll();
		astrAudioStreamName.RemoveAll();
		asAudioMediaInfo.RemoveAll();
		astrAudioStreamLanguageType.RemoveAll();
		astrAudioStreamLanguageCaption.RemoveAll();
		astrSubTitleStreamName.RemoveAll();
		astrSubTitleStreamLanguageType.RemoveAll();
		astrSubTitleStreamLanguageCaption.RemoveAll();
		adwVideoFrameNum.RemoveAll();
		adwAudioSamplesNum.RemoveAll();
		adwSubTitleFrameNum.RemoveAll();
	};

	SDSingleProgramStreamMediaInfoEx(const SDSingleProgramStreamMediaInfoEx &other)
	{
		*this = other;
	};

	SDSingleProgramStreamMediaInfoEx(const SDSingleProgramStreamMediaInfo &other)
	{
		*this = other;
	};

	SDSingleProgramStreamMediaInfoEx& operator = (const SDSingleProgramStreamMediaInfoEx& other)
	{
		strProgramName = other.strProgramName;
		enumStreamMediaType = other.enumStreamMediaType;
		dwStreamMediaSubType = other.dwStreamMediaSubType;
		dwTotalAverDataRateInBitsPerSec = other.dwTotalAverDataRateInBitsPerSec;
		dwTotalMaxDataRateInBitsPerSec = other.dwTotalMaxDataRateInBitsPerSec;
		dwTotalMinDataRateInBitsPerSec = other.dwTotalMinDataRateInBitsPerSec;
		dwVideoStreamCount = other.dwVideoStreamCount;
		astrVideoStreamName.Copy(other.astrVideoStreamName);
		asVideoMediaInfo.Copy(other.asVideoMediaInfo);
		astrVideoStreamType.Copy(other.astrVideoStreamType);
		astrVideoStreamCaption.Copy(other.astrVideoStreamCaption);
		dwAudioStreamCount = other.dwAudioStreamCount;
		astrAudioStreamName.Copy(other.astrAudioStreamName);
		asAudioMediaInfo.Copy(other.asAudioMediaInfo);
		astrAudioStreamLanguageType.Copy(other.astrAudioStreamLanguageType);
		astrAudioStreamLanguageCaption.Copy(other.astrAudioStreamLanguageCaption);
		dwSubTitleStreamCount = other.dwSubTitleStreamCount;
		astrSubTitleStreamName.Copy(other.astrSubTitleStreamName);
		asSubTitleMediaInfo.Copy(other.asSubTitleMediaInfo);
		astrSubTitleStreamLanguageType.Copy(other.astrSubTitleStreamLanguageType);
		astrSubTitleStreamLanguageCaption.Copy(other.astrSubTitleStreamLanguageCaption);
		llFileSize = other.llFileSize;
		adwVideoFrameNum.Copy(other.adwVideoFrameNum);
		adwAudioSamplesNum.Copy(other.adwAudioSamplesNum);
		adwSubTitleFrameNum.Copy(other.adwSubTitleFrameNum);
		return *this;
	};

	SDSingleProgramStreamMediaInfoEx& operator = (const SDSingleProgramStreamMediaInfo& other)
	{
		strProgramName = other.strProgramName;
		enumStreamMediaType = other.enumStreamMediaType;
		dwStreamMediaSubType = other.dwStreamMediaSubType;
		dwTotalAverDataRateInBitsPerSec = other.dwTotalAverDataRateInBitsPerSec;
		dwTotalMaxDataRateInBitsPerSec = other.dwTotalMaxDataRateInBitsPerSec;
		dwTotalMinDataRateInBitsPerSec = other.dwTotalMinDataRateInBitsPerSec;
		dwVideoStreamCount = other.dwVideoStreamCount;
		astrVideoStreamName.Copy(other.astrVideoStreamName);
		asVideoMediaInfo.Copy(other.asVideoMediaInfo);
		astrVideoStreamType.Copy(other.astrVideoStreamType);
		astrVideoStreamCaption.Copy(other.astrVideoStreamCaption);
		dwAudioStreamCount = other.dwAudioStreamCount;
		astrAudioStreamName.Copy(other.astrAudioStreamName);
		asAudioMediaInfo.Copy(other.asAudioMediaInfo);
		astrAudioStreamLanguageType.Copy(other.astrAudioStreamLanguageType);
		astrAudioStreamLanguageCaption.Copy(other.astrAudioStreamLanguageCaption);
		dwSubTitleStreamCount = other.dwSubTitleStreamCount;
		astrSubTitleStreamName.Copy(other.astrSubTitleStreamName);
		asSubTitleMediaInfo.Copy(other.asSubTitleMediaInfo);
		astrSubTitleStreamLanguageType.Copy(other.astrSubTitleStreamLanguageType);
		astrSubTitleStreamLanguageCaption.Copy(other.astrSubTitleStreamLanguageCaption);

		llFileSize = 0;
		adwVideoFrameNum.RemoveAll();
		adwAudioSamplesNum.RemoveAll();
		adwSubTitleFrameNum.RemoveAll();
		return *this;
	};

	SD_BOOL	GetSingleProgramStreamMediaInfo(SDSingleProgramStreamMediaInfo *psInfo)
	{
		if (psInfo)
		{
			psInfo->strProgramName = strProgramName;
			psInfo->enumStreamMediaType = enumStreamMediaType;
			psInfo->dwStreamMediaSubType = dwStreamMediaSubType;
			psInfo->dwTotalAverDataRateInBitsPerSec = dwTotalAverDataRateInBitsPerSec;
			psInfo->dwTotalMaxDataRateInBitsPerSec = dwTotalMaxDataRateInBitsPerSec;
			psInfo->dwTotalMinDataRateInBitsPerSec = dwTotalMinDataRateInBitsPerSec;
			psInfo->dwVideoStreamCount = dwVideoStreamCount;
			psInfo->astrVideoStreamName.Copy(astrVideoStreamName);
			psInfo->asVideoMediaInfo.Copy(asVideoMediaInfo);
			psInfo->astrVideoStreamType.Copy(astrVideoStreamType);
			psInfo->astrVideoStreamCaption.Copy(astrVideoStreamCaption);
			psInfo->dwAudioStreamCount = dwAudioStreamCount;
			psInfo->astrAudioStreamName.Copy(astrAudioStreamName);
			psInfo->asAudioMediaInfo.Copy(asAudioMediaInfo);
			psInfo->astrAudioStreamLanguageType.Copy(astrAudioStreamLanguageType);
			psInfo->astrAudioStreamLanguageCaption.Copy(astrAudioStreamLanguageCaption);
			psInfo->dwSubTitleStreamCount = dwSubTitleStreamCount;
			psInfo->astrSubTitleStreamName.Copy(astrSubTitleStreamName);
		    psInfo->asSubTitleMediaInfo.Copy(asSubTitleMediaInfo);
			psInfo->astrSubTitleStreamLanguageType.Copy(astrSubTitleStreamLanguageType);
			psInfo->astrSubTitleStreamLanguageCaption.Copy(astrSubTitleStreamLanguageCaption);
			return SD_TRUE;
		}
		else
			return SD_FALSE;
	};
	// 序列化支持
	SD_INT32 GetSerializationSize()
	{
		return  SerializationToPtr(SD_NULL, 0);
	};
	SD_INT32 SerializationToPtr(SD_UINT8* pBuffer, SD_INT32 iBufferSize)
	{
		SD_INT32 iPtrSize = 0;
		SD_INT32 iTempSize = SDSingleProgramStreamMediaInfo::GetSerializationSize();
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &iTempSize, sizeof(iTempSize)); 
		iPtrSize += sizeof(iTempSize);
		if (SD_NULL != pBuffer) SDSingleProgramStreamMediaInfo::SerializationToPtr(pBuffer + iPtrSize, iTempSize);
		iPtrSize += iTempSize;
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &llFileSize, sizeof(llFileSize)); 
		iPtrSize += sizeof(llFileSize);
		SD_INT32 iVideoFrameNumCount = adwVideoFrameNum.GetSize();
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &iVideoFrameNumCount, sizeof(iVideoFrameNumCount)); 
		iPtrSize += sizeof(iVideoFrameNumCount);
		for (SD_INT32 i = 0; i < iVideoFrameNumCount; i++)
		{
			if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &adwVideoFrameNum[i], sizeof(adwVideoFrameNum[i])); 
			iPtrSize += sizeof(adwVideoFrameNum[i]);
		}
		SD_INT32 iAudioSamplesNumCount = adwAudioSamplesNum.GetSize();
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &iAudioSamplesNumCount, sizeof(iAudioSamplesNumCount)); 
		iPtrSize += sizeof(iAudioSamplesNumCount);
		for (SD_INT32 i = 0; i < iAudioSamplesNumCount; i++)
		{
			if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &adwAudioSamplesNum[i], sizeof(adwAudioSamplesNum[i])); 
			iPtrSize += sizeof(adwAudioSamplesNum[i]);
		}
		SD_INT32 iSubTitleFrameNumCount = adwSubTitleFrameNum.GetSize();
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &iSubTitleFrameNumCount, sizeof(iSubTitleFrameNumCount)); 
		iPtrSize += sizeof(iSubTitleFrameNumCount);
		for (SD_INT32 i = 0; i < iSubTitleFrameNumCount; i++)
		{
			if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &adwSubTitleFrameNum[i], sizeof(adwSubTitleFrameNum[i])); 
			iPtrSize += sizeof(adwSubTitleFrameNum[i]);
		}
		return iPtrSize;
	};
	SD_INT32 SerializationFromPtr(SD_UINT8* pBuffer, SD_INT32 iBufferSize)
	{
		SD_INT32 iPtrSize = 0;
		SD_INT32 iTempSize;
		memcpy(&iTempSize, pBuffer + iPtrSize,  sizeof(iTempSize));								iPtrSize += sizeof(iTempSize);
		SDSingleProgramStreamMediaInfo::SerializationFromPtr(pBuffer + iPtrSize, iTempSize);	iPtrSize += iTempSize;
		memcpy(&llFileSize,  pBuffer + iPtrSize,  sizeof(llFileSize));							iPtrSize += sizeof(llFileSize);
		SD_INT32 iVideoFrameNumCount;
		memcpy(&iVideoFrameNumCount, pBuffer + iPtrSize, sizeof(iVideoFrameNumCount)); 			iPtrSize += sizeof(iVideoFrameNumCount);
		for (SD_INT32 i = 0; i < iVideoFrameNumCount; i++)
		{
			memcpy(&adwVideoFrameNum[i], pBuffer + iPtrSize, sizeof(adwVideoFrameNum[i]));  	iPtrSize += sizeof(adwVideoFrameNum[i]);
		}
		SD_INT32 iAudioSamplesNumCount;
		memcpy(&iAudioSamplesNumCount, pBuffer + iPtrSize, sizeof(iAudioSamplesNumCount)); 		iPtrSize += sizeof(iAudioSamplesNumCount);
		for (SD_INT32 i = 0; i < iAudioSamplesNumCount; i++)
		{
			memcpy(&adwAudioSamplesNum[i], pBuffer + iPtrSize, sizeof(adwAudioSamplesNum[i])); 	iPtrSize += sizeof(adwAudioSamplesNum[i]);
		}
		SD_INT32 iSubTitleFrameNumCount;
		memcpy(&iSubTitleFrameNumCount, pBuffer + iPtrSize, sizeof(iSubTitleFrameNumCount)); 	iPtrSize += sizeof(iSubTitleFrameNumCount);
		for (SD_INT32 i = 0; i < iSubTitleFrameNumCount; i++)
		{
			memcpy(&adwSubTitleFrameNum[i], pBuffer + iPtrSize, sizeof(adwSubTitleFrameNum[i]));iPtrSize += sizeof(adwSubTitleFrameNum[i]);
		}
		return iPtrSize;
	};
};
typedef CSDArray<SDSingleProgramStreamMediaInfoEx*, SDSingleProgramStreamMediaInfoEx*&>	SDSingleProgramStreamMediaInfoExArray;

SD_INLINE SD_VOID SDRelease(SDSingleProgramStreamMediaInfoExArray *paDataArray)
{
	if (paDataArray) 
	{
		SD_UINT32	size = paDataArray->GetDWSize();
		for (SD_UINT32 i=0; i<size; i++) 
		{
			SDSingleProgramStreamMediaInfoEx *pElement = paDataArray->GetAt(i);
			delete pElement;
		}
		paDataArray->RemoveAll();
	}
};

SD_INLINE SD_BOOL SDClone(SDSingleProgramStreamMediaInfoExArray *pNewData, const SDSingleProgramStreamMediaInfoExArray *pOldData)
{
	if (pNewData == SD_NULL || pOldData == SD_NULL)
		return SD_FALSE;

	SDRelease(pNewData);

	SD_UINT32 size = pOldData->GetDWSize();
	for (SD_UINT32 i=0; i<size; i++) 
	{
		SDSingleProgramStreamMediaInfoEx *pNewElement = new SDSingleProgramStreamMediaInfoEx;
		SDSingleProgramStreamMediaInfoEx *pOldElement = pOldData->GetAt(i);
		(*pNewElement) = (*pOldElement);
		pNewData->Add(pNewElement);
	}
	return SD_TRUE;
};


struct SDMultiProgramStreamMediaInfo		// 多节目视音频流(文件)属性
{
	SDSingleProgramStreamMediaInfoArray	aSingleProgramStreamMediaInfo;

	SDMultiProgramStreamMediaInfo()
	{
	};

	~SDMultiProgramStreamMediaInfo()
	{
		SDRelease(&aSingleProgramStreamMediaInfo);
	};

	SDMultiProgramStreamMediaInfo(const SDMultiProgramStreamMediaInfo &other)
	{
		*this = other;
	};

	SDMultiProgramStreamMediaInfo& operator = (const SDMultiProgramStreamMediaInfo& other)
	{
		SDClone(&aSingleProgramStreamMediaInfo, &(other.aSingleProgramStreamMediaInfo));

		return *this;
	};

	SD_UINT32	GetProgramNum()
	{
		return aSingleProgramStreamMediaInfo.GetDWSize();
	};

	// 序列化支持
	SD_INT32 GetSerializationSize()
	{
		return  SerializationToPtr(SD_NULL, 0);
	};
	SD_INT32 SerializationToPtr(SD_UINT8* pBuffer, SD_INT32 iBufferSize)
	{
		SD_INT32 iPtrSize = 0;
		SD_INT32  iSGMCount = aSingleProgramStreamMediaInfo.GetSize();
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &iSGMCount, sizeof(iSGMCount));
		iPtrSize += sizeof(iSGMCount);
		for (SD_INT32 i = 0; i < iSGMCount; i++)
		{
			SD_INT32 iSGMInfoSize = aSingleProgramStreamMediaInfo[i]->GetSerializationSize();
			if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &iSGMCount, sizeof(iSGMInfoSize));
			iPtrSize += sizeof(iSGMInfoSize);
			if (SD_NULL != pBuffer) aSingleProgramStreamMediaInfo[i]->SerializationToPtr(pBuffer + iPtrSize, iSGMInfoSize);
			iPtrSize += iSGMInfoSize;
		}
		return iPtrSize;
	};
	SD_INT32 SerializationFromPtr(SD_UINT8* pBuffer, SD_INT32 iBufferSize)
	{
		SD_INT32 iCount = aSingleProgramStreamMediaInfo.GetSize();
		for (SD_INT32 i = 0; i < iCount; i++)
		{
			delete aSingleProgramStreamMediaInfo[i];
		}
		aSingleProgramStreamMediaInfo.RemoveAll();

		SD_INT32 iPtrSize = 0;
		SD_INT32  iSGMCount;
		memcpy(&iSGMCount, pBuffer + iPtrSize, sizeof(iSGMCount));   iPtrSize += sizeof(iSGMCount);
		for (SD_INT32 i = 0; i < iSGMCount; i++)
		{
			SD_INT32 iSGMInfoSize;
			memcpy(&iSGMInfoSize, pBuffer + iPtrSize, sizeof(iSGMInfoSize)); iPtrSize += sizeof(iSGMInfoSize);
			SDSingleProgramStreamMediaInfo *pPGMInfo = new SDSingleProgramStreamMediaInfo(); 			
			pPGMInfo->SerializationFromPtr(pBuffer + iPtrSize, iSGMInfoSize);
			iPtrSize += iSGMInfoSize;
			aSingleProgramStreamMediaInfo.Add(pPGMInfo);
		}
		return iPtrSize;
	};
};

struct SDMultiProgramStreamMediaInfoEx		// 多节目视音频流(文件)扩展属性
{
	SDSingleProgramStreamMediaInfoExArray	aSingleProgramStreamMediaInfoEx;

	SDMultiProgramStreamMediaInfoEx()
	{
	};

	SDMultiProgramStreamMediaInfoEx(const SDMultiProgramStreamMediaInfoEx &other)
	{
		*this = other;
	};

	SDMultiProgramStreamMediaInfoEx(const SDMultiProgramStreamMediaInfo &other)
	{
		*this = other;
	};

	~SDMultiProgramStreamMediaInfoEx()
	{
		SDRelease(&aSingleProgramStreamMediaInfoEx);
	};

	SDMultiProgramStreamMediaInfoEx& operator = (const SDMultiProgramStreamMediaInfoEx& other)
	{
		SDClone(&aSingleProgramStreamMediaInfoEx, &(other.aSingleProgramStreamMediaInfoEx));

		return *this;
	};

	SDMultiProgramStreamMediaInfoEx& operator = (const SDMultiProgramStreamMediaInfo& other)
	{
		SDRelease(&aSingleProgramStreamMediaInfoEx);

		SD_UINT32 size = other.aSingleProgramStreamMediaInfo.GetDWSize();
		for (SD_UINT32 i=0; i<size; i++)
		{
			SDSingleProgramStreamMediaInfoEx *psInfoEx = new SDSingleProgramStreamMediaInfoEx;
			(*psInfoEx) = (*(other.aSingleProgramStreamMediaInfo[i]));
			aSingleProgramStreamMediaInfoEx.Add(psInfoEx);
		}
		return *this;
	};

	SD_BOOL	GetMultiProgramStreamMediaInfo(SDMultiProgramStreamMediaInfo *psMInfo)
	{
		if (psMInfo)
		{
			SDRelease(&(psMInfo->aSingleProgramStreamMediaInfo));
			SD_UINT32 size = aSingleProgramStreamMediaInfoEx.GetDWSize();
			for (SD_UINT32 i=0; i<size; i++)
			{
				SDSingleProgramStreamMediaInfo *psSInfo = new SDSingleProgramStreamMediaInfo;
				aSingleProgramStreamMediaInfoEx[i]->GetSingleProgramStreamMediaInfo(psSInfo);
				psMInfo->aSingleProgramStreamMediaInfo.Add(psSInfo);
			}
			return SD_TRUE;
		}
		else
			return SD_FALSE;
	};

	SD_UINT32	GetProgramNum()
	{
		return aSingleProgramStreamMediaInfoEx.GetDWSize();
	};

	SD_UINT64	GetFileSize()
	{
		SD_UINT64 llFileSize = 0;
		SD_UINT32 size = aSingleProgramStreamMediaInfoEx.GetDWSize();
		for (SD_UINT32 i=0; i<size; i++)
		{
			if (llFileSize < aSingleProgramStreamMediaInfoEx[i]->llFileSize)
				llFileSize = aSingleProgramStreamMediaInfoEx[i]->llFileSize;
		}
		return llFileSize;
	};

	// 序列化支持
	SD_INT32 GetSerializationSize()
	{
		return  SerializationToPtr(SD_NULL, 0);
	};
	SD_INT32 SerializationToPtr(SD_UINT8* pBuffer, SD_INT32 iBufferSize)
	{
		SD_INT32 iPtrSize = 0;
		SD_INT32  iSGMCount = aSingleProgramStreamMediaInfoEx.GetSize();
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &iSGMCount, sizeof(iSGMCount));
		iPtrSize += sizeof(iSGMCount);
		for (SD_INT32 i = 0; i < iSGMCount; i++)
		{
			SD_INT32 iSGMInfoSize = aSingleProgramStreamMediaInfoEx[i]->GetSerializationSize();
			if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &iSGMInfoSize, sizeof(iSGMInfoSize));
			iPtrSize += sizeof(iSGMInfoSize);
			if (SD_NULL != pBuffer) aSingleProgramStreamMediaInfoEx[i]->SerializationToPtr(pBuffer + iPtrSize, iSGMInfoSize);
			iPtrSize += iSGMInfoSize;
		}
		return iPtrSize;
	};
	SD_INT32 SerializationFromPtr(SD_UINT8* pBuffer, SD_INT32 iBufferSize)
	{
		SD_INT32 iCount = aSingleProgramStreamMediaInfoEx.GetSize();
		for (SD_INT32 i = 0; i < iCount; i++)
		{
			delete aSingleProgramStreamMediaInfoEx[i];
		}
		aSingleProgramStreamMediaInfoEx.RemoveAll();

		SD_INT32 iPtrSize = 0;
		SD_INT32  iSGMCount;
		memcpy(&iSGMCount, pBuffer + iPtrSize, sizeof(iSGMCount));   iPtrSize += sizeof(iSGMCount);
		for (SD_INT32 i = 0; i < iSGMCount; i++)
		{
			SD_INT32 iSGMInfoSize;
			memcpy(&iSGMInfoSize, pBuffer + iPtrSize, sizeof(iSGMInfoSize)); iPtrSize += sizeof(iSGMInfoSize);
			SDSingleProgramStreamMediaInfoEx *pPGMInfoEx = new SDSingleProgramStreamMediaInfoEx(); 			
			pPGMInfoEx->SerializationFromPtr(pBuffer + iPtrSize, iSGMInfoSize);
			iPtrSize += iSGMInfoSize;
			aSingleProgramStreamMediaInfoEx.Add(pPGMInfoEx);
		}
		return iPtrSize;
	};
};

enum SD_STREAMMEDIA_TYPE	//流媒体数据信息类型
{
	SDSTREAMMEDIATYPE_Unknow			=	0,
	SDSTREAMMEDIATYPE_VIDEOAUDIO		=	1,		//视音频格式
	SDSTREAMMEDIATYPE_SINGLEPROGRAM		=	2,		//单节目流格式
	SDSTREAMMEDIATYPE_MULTIPROGRAM		=	3,		//多节目流格式
};

//得到流媒体数据信息类型的名称
SD_INLINE CSDString GetStreamMediaTypeHint(SD_STREAMMEDIA_TYPE enumStreamMediaType)
{
	CSDString strHint = _T("Unknow");

	switch(enumStreamMediaType)
	{
		case SDSTREAMMEDIATYPE_VIDEOAUDIO:
			strHint = _T("VideoAudio");
			break;
		case SDSTREAMMEDIATYPE_SINGLEPROGRAM:
			strHint = _T("Single Program");
			break;
		case SDSTREAMMEDIATYPE_MULTIPROGRAM:
			strHint = _T("Multi Program");
			break;
	}
	return strHint;
};

struct SDGlobalStreamMediaInfo		//全局流媒体数据信息
{
	SD_STREAMMEDIA_TYPE				enumStreamMediaType;						//流媒体数据信息类型

	SDStreamMediaInfo				*psStreamMediaInfo;							//视音频媒体信息
	SDSingleProgramStreamMediaInfo	*psSingleProgramMediaInfo;					//单节目流媒体信息
	SDMultiProgramStreamMediaInfo	*psMultiProgramMediaInfo;					//多节目流媒体信息

	SDGlobalStreamMediaInfo()
	{
		enumStreamMediaType = SDSTREAMMEDIATYPE_Unknow;
		psStreamMediaInfo = SD_NULL;
		psSingleProgramMediaInfo = SD_NULL;
		psMultiProgramMediaInfo = SD_NULL;
	};

	SDGlobalStreamMediaInfo(const SDGlobalStreamMediaInfo &other)
	{
		*this = other;
	};

	SDGlobalStreamMediaInfo(SD_STREAMMEDIA_TYPE enumMediaType)
	{
		enumStreamMediaType = enumMediaType;
		psStreamMediaInfo = SD_NULL;
		psSingleProgramMediaInfo = SD_NULL;
		psMultiProgramMediaInfo = SD_NULL;
		if (enumMediaType == SDSTREAMMEDIATYPE_VIDEOAUDIO)
			psStreamMediaInfo = new SDStreamMediaInfo;
		else if (enumMediaType == SDSTREAMMEDIATYPE_SINGLEPROGRAM)
			psSingleProgramMediaInfo = new SDSingleProgramStreamMediaInfo;
		else if (enumMediaType == SDSTREAMMEDIATYPE_MULTIPROGRAM)
			psMultiProgramMediaInfo = new SDMultiProgramStreamMediaInfo;
	};

	SDGlobalStreamMediaInfo(SDStreamMediaInfo *psMediaInfo)
	{
		enumStreamMediaType = SDSTREAMMEDIATYPE_Unknow;
		psStreamMediaInfo = SD_NULL;
		psSingleProgramMediaInfo = SD_NULL;
		psMultiProgramMediaInfo = SD_NULL;
		if (psMediaInfo)
		{
			enumStreamMediaType = SDSTREAMMEDIATYPE_VIDEOAUDIO;
			psStreamMediaInfo = new SDStreamMediaInfo;
			(*psStreamMediaInfo) = (*psMediaInfo);
		}
	};

	SDGlobalStreamMediaInfo(SDSingleProgramStreamMediaInfo *psMediaInfo)
	{
		enumStreamMediaType = SDSTREAMMEDIATYPE_Unknow;
		psStreamMediaInfo = SD_NULL;
		psSingleProgramMediaInfo = SD_NULL;
		psMultiProgramMediaInfo = SD_NULL;
		if (psMediaInfo)
		{
			enumStreamMediaType = SDSTREAMMEDIATYPE_SINGLEPROGRAM;
			psSingleProgramMediaInfo = new SDSingleProgramStreamMediaInfo;
			(*psSingleProgramMediaInfo) = (*psMediaInfo);
		}
	};

	SDGlobalStreamMediaInfo(SDMultiProgramStreamMediaInfo *psMediaInfo)
	{
		enumStreamMediaType = SDSTREAMMEDIATYPE_Unknow;
		psStreamMediaInfo = SD_NULL;
		psSingleProgramMediaInfo = SD_NULL;
		psMultiProgramMediaInfo = SD_NULL;
		if (psMediaInfo)
		{
			enumStreamMediaType = SDSTREAMMEDIATYPE_MULTIPROGRAM;
			psMultiProgramMediaInfo = new SDMultiProgramStreamMediaInfo;
			(*psMultiProgramMediaInfo) = (*psMediaInfo);
		}
	};

	~SDGlobalStreamMediaInfo()
	{
		if (psStreamMediaInfo)
			delete psStreamMediaInfo;
		if (psSingleProgramMediaInfo)
			delete psSingleProgramMediaInfo;
		if (psMultiProgramMediaInfo)
			delete psMultiProgramMediaInfo;
	};

	SDGlobalStreamMediaInfo& operator = (const SDGlobalStreamMediaInfo& other)
	{
		if (psStreamMediaInfo)
			delete psStreamMediaInfo;
		if (psSingleProgramMediaInfo)
			delete psSingleProgramMediaInfo;
		if (psMultiProgramMediaInfo)
			delete psMultiProgramMediaInfo;
		psStreamMediaInfo = SD_NULL;
		psSingleProgramMediaInfo = SD_NULL;
		psMultiProgramMediaInfo = SD_NULL;
		if (other.enumStreamMediaType == SDSTREAMMEDIATYPE_VIDEOAUDIO && other.psStreamMediaInfo)
		{
			enumStreamMediaType = SDSTREAMMEDIATYPE_VIDEOAUDIO;
			psStreamMediaInfo = new SDStreamMediaInfo;
			(*psStreamMediaInfo) = (*(other.psStreamMediaInfo));
		}
		else if (other.enumStreamMediaType == SDSTREAMMEDIATYPE_SINGLEPROGRAM && other.psSingleProgramMediaInfo)
		{
			enumStreamMediaType = SDSTREAMMEDIATYPE_SINGLEPROGRAM;
			psSingleProgramMediaInfo = new SDSingleProgramStreamMediaInfo;
			(*psSingleProgramMediaInfo) = (*(other.psSingleProgramMediaInfo));
		}
		else if (other.enumStreamMediaType == SDSTREAMMEDIATYPE_MULTIPROGRAM && other.psMultiProgramMediaInfo)
		{
			enumStreamMediaType = SDSTREAMMEDIATYPE_MULTIPROGRAM;
			psMultiProgramMediaInfo = new SDMultiProgramStreamMediaInfo;
			(*psMultiProgramMediaInfo) = (*(other.psMultiProgramMediaInfo));
		}

		return *this;
	};

	SD_UINT32	GetProgramNum()
	{
		if (enumStreamMediaType == SDSTREAMMEDIATYPE_VIDEOAUDIO || enumStreamMediaType == SDSTREAMMEDIATYPE_SINGLEPROGRAM)
			return 1;
		else if (enumStreamMediaType == SDSTREAMMEDIATYPE_MULTIPROGRAM && psMultiProgramMediaInfo)
			return psMultiProgramMediaInfo->GetProgramNum();
		else
			return 0;
	};

	SD_UINT32	GetVideoStreamNum(SD_UINT32 dwProgramNo)
	{
		if (enumStreamMediaType == SDSTREAMMEDIATYPE_VIDEOAUDIO && psStreamMediaInfo)
			return ((psStreamMediaInfo->dwVideoStreamCount > 0 && dwProgramNo == 0) ? 1 : 0);
		else if (enumStreamMediaType == SDSTREAMMEDIATYPE_SINGLEPROGRAM && psSingleProgramMediaInfo)
			return ((dwProgramNo == 0) ? psSingleProgramMediaInfo->dwVideoStreamCount : 0);
		else if (enumStreamMediaType == SDSTREAMMEDIATYPE_MULTIPROGRAM && psMultiProgramMediaInfo)
		{
			if (dwProgramNo < psMultiProgramMediaInfo->GetProgramNum())
				return psMultiProgramMediaInfo->aSingleProgramStreamMediaInfo[dwProgramNo]->dwVideoStreamCount;
			else
				return 0;
		}
		else
			return 0;
	};

	SD_UINT32	GetAudioStreamNum(SD_UINT32 dwProgramNo)
	{
		if (enumStreamMediaType == SDSTREAMMEDIATYPE_VIDEOAUDIO && psStreamMediaInfo)
			return ((psStreamMediaInfo->dwAudioStreamCount > 0 && dwProgramNo == 0) ? 1 : 0);
		else if (enumStreamMediaType == SDSTREAMMEDIATYPE_SINGLEPROGRAM && psSingleProgramMediaInfo)
			return ((dwProgramNo == 0) ? psSingleProgramMediaInfo->dwAudioStreamCount : 0);
		else if (enumStreamMediaType == SDSTREAMMEDIATYPE_MULTIPROGRAM && psMultiProgramMediaInfo)
		{
			if (dwProgramNo < psMultiProgramMediaInfo->GetProgramNum())
				return psMultiProgramMediaInfo->aSingleProgramStreamMediaInfo[dwProgramNo]->dwAudioStreamCount;
			else
				return 0;
		}
		else
			return 0;
	};

	SD_UINT32	GetSubTitleStreamNum(SD_UINT32 dwProgramNo)
	{
		if (enumStreamMediaType == SDSTREAMMEDIATYPE_VIDEOAUDIO)
			return 0;
		else if (enumStreamMediaType == SDSTREAMMEDIATYPE_SINGLEPROGRAM && psSingleProgramMediaInfo)
			return ((dwProgramNo == 0) ? psSingleProgramMediaInfo->dwSubTitleStreamCount : 0);
		else if (enumStreamMediaType == SDSTREAMMEDIATYPE_MULTIPROGRAM && psMultiProgramMediaInfo)
		{
			if (dwProgramNo < psMultiProgramMediaInfo->GetProgramNum())
				return psMultiProgramMediaInfo->aSingleProgramStreamMediaInfo[dwProgramNo]->dwSubTitleStreamCount;
			else
				return 0;
		}
		else
			return 0;
	};

	// 序列化支持
	SD_INT32 GetSerializationSize()
	{
		return  SerializationToPtr(SD_NULL, 0);
	};
	SD_INT32 SerializationToPtr(SD_UINT8* pBuffer, SD_INT32 iBufferSize)
	{
		SD_INT32 iPtrSize = 0;
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &enumStreamMediaType, sizeof(enumStreamMediaType));
		iPtrSize += sizeof(enumStreamMediaType);
		SD_INT32 iInfoSize = 0;
		if ((SDSTREAMMEDIATYPE_VIDEOAUDIO == enumStreamMediaType) && (SD_NULL != psStreamMediaInfo))
		{
			iInfoSize = psStreamMediaInfo->GetSerializationSize();
			if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &iInfoSize, sizeof(iInfoSize));
			iPtrSize += sizeof(iInfoSize);
			if (SD_NULL != pBuffer) psStreamMediaInfo->SerializationToPtr(pBuffer + iPtrSize, iInfoSize);
			iPtrSize += iInfoSize;
		}
		else if ((SDSTREAMMEDIATYPE_SINGLEPROGRAM == enumStreamMediaType) && (SD_NULL != psSingleProgramMediaInfo))
		{
			iInfoSize = psStreamMediaInfo->GetSerializationSize();
			if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &iInfoSize, sizeof(iInfoSize));
			iPtrSize += sizeof(iInfoSize);
			if (SD_NULL != pBuffer) psSingleProgramMediaInfo->SerializationToPtr(pBuffer + iPtrSize, iInfoSize);
			iPtrSize += iInfoSize;
		}
		else if ((SDSTREAMMEDIATYPE_MULTIPROGRAM == enumStreamMediaType) && (SD_NULL != psMultiProgramMediaInfo))
		{
			iInfoSize = psMultiProgramMediaInfo->GetSerializationSize();
			if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &iInfoSize, sizeof(iInfoSize));
			iPtrSize += sizeof(iInfoSize);
			if (SD_NULL != pBuffer) psMultiProgramMediaInfo->SerializationToPtr(pBuffer + iPtrSize, iInfoSize);
			iPtrSize += iInfoSize;
		}
		else
		{
			if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &iInfoSize, sizeof(iInfoSize));
			iPtrSize += sizeof(iInfoSize);
		}
		return iPtrSize;
	};
	SD_INT32 SerializationFromPtr(SD_UINT8* pBuffer, SD_INT32 iBufferSize)
	{
		SD_INT32 iPtrSize = 0;
		memcpy(&enumStreamMediaType, pBuffer + iPtrSize, sizeof(enumStreamMediaType)); iPtrSize += sizeof(enumStreamMediaType);
		SD_INT32 iInfoSize;
		memcpy(&iInfoSize, pBuffer + iPtrSize, sizeof(iInfoSize)); iPtrSize += sizeof(iInfoSize);
		if (SD_NULL != psStreamMediaInfo)
		{
			delete psStreamMediaInfo; psStreamMediaInfo = SD_NULL;
		}
		if (SD_NULL != psSingleProgramMediaInfo)
		{
			delete psSingleProgramMediaInfo; psSingleProgramMediaInfo = SD_NULL;
		}
		if (SD_NULL != psMultiProgramMediaInfo)
		{
			delete psMultiProgramMediaInfo; psMultiProgramMediaInfo = SD_NULL;
		}
		if ((SDSTREAMMEDIATYPE_VIDEOAUDIO == enumStreamMediaType) && (iInfoSize > 0))
		{
			psStreamMediaInfo = new SDStreamMediaInfo();
			psStreamMediaInfo->SerializationFromPtr(pBuffer + iPtrSize, iInfoSize);
			iPtrSize += iInfoSize;
		}
		else if ((SDSTREAMMEDIATYPE_SINGLEPROGRAM == enumStreamMediaType) && (SD_NULL != psSingleProgramMediaInfo))
		{
			psSingleProgramMediaInfo = new SDSingleProgramStreamMediaInfo();
			psSingleProgramMediaInfo->SerializationFromPtr(pBuffer + iPtrSize, iInfoSize);
			iPtrSize += iInfoSize;
		}
		else if ((SDSTREAMMEDIATYPE_MULTIPROGRAM == enumStreamMediaType) && (SD_NULL != psMultiProgramMediaInfo))
		{
			psMultiProgramMediaInfo = new SDMultiProgramStreamMediaInfo();
			psMultiProgramMediaInfo->SerializationFromPtr(pBuffer + iPtrSize, iInfoSize);
			iPtrSize += iInfoSize;
		}
		return iPtrSize;
	};
};

struct SDGlobalStreamMediaInfoEx		//全局流媒体数据扩展信息
{
	SD_STREAMMEDIA_TYPE					enumStreamMediaType;						//流媒体数据信息类型

	SDStreamMediaInfoEx				*psStreamMediaInfoEx;						//视音频媒体扩展信息
	SDSingleProgramStreamMediaInfoEx	*psSingleProgramMediaInfoEx;				//单节目流媒体扩展信息
	SDMultiProgramStreamMediaInfoEx	*psMultiProgramMediaInfoEx;					//多节目流媒体扩展信息

	SDGlobalStreamMediaInfoEx()
	{
		enumStreamMediaType = SDSTREAMMEDIATYPE_Unknow;
		psStreamMediaInfoEx = SD_NULL;
		psSingleProgramMediaInfoEx = SD_NULL;
		psMultiProgramMediaInfoEx = SD_NULL;
	};

	SDGlobalStreamMediaInfoEx(const SDGlobalStreamMediaInfoEx &other)
	{
		*this = other;
	};

	SDGlobalStreamMediaInfoEx(const SDGlobalStreamMediaInfo &other)
	{
		*this = other;
	};

	SDGlobalStreamMediaInfoEx(SD_STREAMMEDIA_TYPE enumMediaType)
	{
		enumStreamMediaType = enumMediaType;
		psStreamMediaInfoEx = SD_NULL;
		psSingleProgramMediaInfoEx = SD_NULL;
		psMultiProgramMediaInfoEx = SD_NULL;
		if (enumMediaType == SDSTREAMMEDIATYPE_VIDEOAUDIO)
			psStreamMediaInfoEx = new SDStreamMediaInfoEx;
		else if (enumMediaType == SDSTREAMMEDIATYPE_SINGLEPROGRAM)
			psSingleProgramMediaInfoEx = new SDSingleProgramStreamMediaInfoEx;
		else if (enumMediaType == SDSTREAMMEDIATYPE_MULTIPROGRAM)
			psMultiProgramMediaInfoEx = new SDMultiProgramStreamMediaInfoEx;
	};

	SDGlobalStreamMediaInfoEx(SDStreamMediaInfoEx *psMediaInfoEx)
	{
		enumStreamMediaType = SDSTREAMMEDIATYPE_Unknow;
		psStreamMediaInfoEx = SD_NULL;
		psSingleProgramMediaInfoEx = SD_NULL;
		psMultiProgramMediaInfoEx = SD_NULL;
		if (psMediaInfoEx)
		{
			enumStreamMediaType = SDSTREAMMEDIATYPE_VIDEOAUDIO;
			psStreamMediaInfoEx = new SDStreamMediaInfoEx;
			(*psStreamMediaInfoEx) = (*psMediaInfoEx);
		}
	};

	SDGlobalStreamMediaInfoEx(SDSingleProgramStreamMediaInfoEx *psMediaInfoEx)
	{
		enumStreamMediaType = SDSTREAMMEDIATYPE_Unknow;
		psStreamMediaInfoEx = SD_NULL;
		psSingleProgramMediaInfoEx = SD_NULL;
		psMultiProgramMediaInfoEx = SD_NULL;
		if (psMediaInfoEx)
		{
			enumStreamMediaType = SDSTREAMMEDIATYPE_SINGLEPROGRAM;
			psSingleProgramMediaInfoEx = new SDSingleProgramStreamMediaInfoEx;
			(*psSingleProgramMediaInfoEx) = (*psMediaInfoEx);
		}
	};

	SDGlobalStreamMediaInfoEx(SDMultiProgramStreamMediaInfo *psMediaInfoEx)
	{
		enumStreamMediaType = SDSTREAMMEDIATYPE_Unknow;
		psStreamMediaInfoEx = SD_NULL;
		psSingleProgramMediaInfoEx = SD_NULL;
		psMultiProgramMediaInfoEx = SD_NULL;
		if (psMediaInfoEx)
		{
			enumStreamMediaType = SDSTREAMMEDIATYPE_MULTIPROGRAM;
			psMultiProgramMediaInfoEx = new SDMultiProgramStreamMediaInfoEx;
			(*psMultiProgramMediaInfoEx) = (*psMediaInfoEx);
		}
	};

	~SDGlobalStreamMediaInfoEx()
	{
		if (psStreamMediaInfoEx)
			delete psStreamMediaInfoEx;
		if (psSingleProgramMediaInfoEx)
			delete psSingleProgramMediaInfoEx;
		if (psMultiProgramMediaInfoEx)
			delete psMultiProgramMediaInfoEx;
	};

	SDGlobalStreamMediaInfoEx& operator = (const SDGlobalStreamMediaInfoEx& other)
	{
		if (psStreamMediaInfoEx)
			delete psStreamMediaInfoEx;
		if (psSingleProgramMediaInfoEx)
			delete psSingleProgramMediaInfoEx;
		if (psMultiProgramMediaInfoEx)
			delete psMultiProgramMediaInfoEx;
		psStreamMediaInfoEx = SD_NULL;
		psSingleProgramMediaInfoEx = SD_NULL;
		psMultiProgramMediaInfoEx = SD_NULL;

		if (other.psStreamMediaInfoEx && other.enumStreamMediaType == SDSTREAMMEDIATYPE_VIDEOAUDIO)
		{
			enumStreamMediaType = SDSTREAMMEDIATYPE_VIDEOAUDIO;
			psStreamMediaInfoEx = new SDStreamMediaInfoEx;
			(*psStreamMediaInfoEx) = (*(other.psStreamMediaInfoEx));
		}
		if (other.psSingleProgramMediaInfoEx && other.enumStreamMediaType == SDSTREAMMEDIATYPE_SINGLEPROGRAM)
		{
			enumStreamMediaType = SDSTREAMMEDIATYPE_SINGLEPROGRAM;
			psSingleProgramMediaInfoEx = new SDSingleProgramStreamMediaInfoEx;
			(*psSingleProgramMediaInfoEx) = (*(other.psSingleProgramMediaInfoEx));
		}
		if (other.psMultiProgramMediaInfoEx && other.enumStreamMediaType == SDSTREAMMEDIATYPE_MULTIPROGRAM)
		{
			enumStreamMediaType = SDSTREAMMEDIATYPE_MULTIPROGRAM;
			psMultiProgramMediaInfoEx = new SDMultiProgramStreamMediaInfoEx;
			(*psMultiProgramMediaInfoEx) = (*(other.psMultiProgramMediaInfoEx));
		}
		return *this;
	};

	SDGlobalStreamMediaInfoEx& operator = (const SDGlobalStreamMediaInfo& other)
	{
		if (psStreamMediaInfoEx)
			delete psStreamMediaInfoEx;
		if (psSingleProgramMediaInfoEx)
			delete psSingleProgramMediaInfoEx;
		if (psMultiProgramMediaInfoEx)
			delete psMultiProgramMediaInfoEx;
		psStreamMediaInfoEx = SD_NULL;
		psSingleProgramMediaInfoEx = SD_NULL;
		psMultiProgramMediaInfoEx = SD_NULL;

		if (other.psStreamMediaInfo && other.enumStreamMediaType == SDSTREAMMEDIATYPE_VIDEOAUDIO)
		{
			enumStreamMediaType = SDSTREAMMEDIATYPE_VIDEOAUDIO;
			psStreamMediaInfoEx = new SDStreamMediaInfoEx;
			(*psStreamMediaInfoEx) = (*(other.psStreamMediaInfo));
		}
		if (other.psSingleProgramMediaInfo && other.enumStreamMediaType == SDSTREAMMEDIATYPE_SINGLEPROGRAM)
		{
			enumStreamMediaType = SDSTREAMMEDIATYPE_SINGLEPROGRAM;
			psSingleProgramMediaInfoEx = new SDSingleProgramStreamMediaInfoEx;
			(*psSingleProgramMediaInfoEx) = (*(other.psSingleProgramMediaInfo));
		}
		if (other.psMultiProgramMediaInfo && other.enumStreamMediaType == SDSTREAMMEDIATYPE_MULTIPROGRAM)
		{
			enumStreamMediaType = SDSTREAMMEDIATYPE_MULTIPROGRAM;
			psMultiProgramMediaInfoEx = new SDMultiProgramStreamMediaInfoEx;
			(*psMultiProgramMediaInfoEx) = (*(other.psMultiProgramMediaInfo));
		}
		return *this;
	};

	SD_VOID	GetGlobalStreamMediaInfo(SDGlobalStreamMediaInfo &sInfo)
	{
		if (sInfo.psStreamMediaInfo)
			delete sInfo.psStreamMediaInfo;
		if (sInfo.psSingleProgramMediaInfo)
			delete sInfo.psSingleProgramMediaInfo;
		if (sInfo.psMultiProgramMediaInfo)
			delete sInfo.psMultiProgramMediaInfo;
		sInfo.psStreamMediaInfo = SD_NULL;
		sInfo.psSingleProgramMediaInfo = SD_NULL;
		sInfo.psMultiProgramMediaInfo = SD_NULL;

		sInfo.enumStreamMediaType = enumStreamMediaType;
		if (psStreamMediaInfoEx && enumStreamMediaType == SDSTREAMMEDIATYPE_VIDEOAUDIO)
		{
			sInfo.psStreamMediaInfo = new SDStreamMediaInfo;
			psStreamMediaInfoEx->GetStreamMediaInfo(sInfo.psStreamMediaInfo);
		}
		if (psSingleProgramMediaInfoEx && enumStreamMediaType == SDSTREAMMEDIATYPE_SINGLEPROGRAM)
		{
			sInfo.psSingleProgramMediaInfo = new SDSingleProgramStreamMediaInfo;
			psSingleProgramMediaInfoEx->GetSingleProgramStreamMediaInfo(sInfo.psSingleProgramMediaInfo);
		}
		if (psMultiProgramMediaInfoEx && enumStreamMediaType == SDSTREAMMEDIATYPE_MULTIPROGRAM)
		{
			sInfo.psMultiProgramMediaInfo = new SDMultiProgramStreamMediaInfo;
			psMultiProgramMediaInfoEx->GetMultiProgramStreamMediaInfo(sInfo.psMultiProgramMediaInfo);
		}
		
	};

	SD_UINT32	GetProgramNum()
	{
		if (enumStreamMediaType == SDSTREAMMEDIATYPE_VIDEOAUDIO || enumStreamMediaType == SDSTREAMMEDIATYPE_SINGLEPROGRAM)
			return 1;
		else if (enumStreamMediaType == SDSTREAMMEDIATYPE_MULTIPROGRAM && psMultiProgramMediaInfoEx)
			return psMultiProgramMediaInfoEx->GetProgramNum();
		else
			return 0;
	};

	SD_UINT32	GetVideoStreamNum(SD_UINT32 dwProgramNo)
	{
		if (enumStreamMediaType == SDSTREAMMEDIATYPE_VIDEOAUDIO && psStreamMediaInfoEx)
			return ((psStreamMediaInfoEx->dwVideoStreamCount > 0 && dwProgramNo == 0) ? 1 : 0);
		else if (enumStreamMediaType == SDSTREAMMEDIATYPE_SINGLEPROGRAM && psSingleProgramMediaInfoEx)
			return ((dwProgramNo == 0) ? psSingleProgramMediaInfoEx->dwVideoStreamCount : 0);
		else if (enumStreamMediaType == SDSTREAMMEDIATYPE_MULTIPROGRAM && psMultiProgramMediaInfoEx)
		{
			if (dwProgramNo < psMultiProgramMediaInfoEx->GetProgramNum())
				return psMultiProgramMediaInfoEx->aSingleProgramStreamMediaInfoEx[dwProgramNo]->dwVideoStreamCount;
			else
				return 0;
		}
		else
			return 0;
	};

	SD_UINT32	GetAudioStreamNum(SD_UINT32 dwProgramNo)
	{
		if (enumStreamMediaType == SDSTREAMMEDIATYPE_VIDEOAUDIO && psStreamMediaInfoEx)
			return ((psStreamMediaInfoEx->dwAudioStreamCount > 0 && dwProgramNo == 0) ? 1 : 0);
		else if (enumStreamMediaType == SDSTREAMMEDIATYPE_SINGLEPROGRAM && psSingleProgramMediaInfoEx)
			return ((dwProgramNo == 0) ? psSingleProgramMediaInfoEx->dwAudioStreamCount : 0);
		else if (enumStreamMediaType == SDSTREAMMEDIATYPE_MULTIPROGRAM && psMultiProgramMediaInfoEx)
		{
			if (dwProgramNo < psMultiProgramMediaInfoEx->GetProgramNum())
				return psMultiProgramMediaInfoEx->aSingleProgramStreamMediaInfoEx[dwProgramNo]->dwAudioStreamCount;
			else
				return 0;
		}
		else
			return 0;
	};

	SD_UINT32	GetSubTitleStreamNum(SD_UINT32 dwProgramNo)
	{
		if (enumStreamMediaType == SDSTREAMMEDIATYPE_VIDEOAUDIO)
			return 0;
		else if (enumStreamMediaType == SDSTREAMMEDIATYPE_SINGLEPROGRAM && psSingleProgramMediaInfoEx)
			return ((dwProgramNo == 0) ? psSingleProgramMediaInfoEx->dwSubTitleStreamCount : 0);
		else if (enumStreamMediaType == SDSTREAMMEDIATYPE_MULTIPROGRAM && psMultiProgramMediaInfoEx)
		{
			if (dwProgramNo < psMultiProgramMediaInfoEx->GetProgramNum())
				return psMultiProgramMediaInfoEx->aSingleProgramStreamMediaInfoEx[dwProgramNo]->dwSubTitleStreamCount;
			else
				return 0;
		}
		else
			return 0;
	};

	SD_UINT32	GetVideoFrameCount(SD_UINT32 dwProgramNo = 0, SD_UINT32 dwVideoStreamNo = 0)
	{
		if (enumStreamMediaType == SDSTREAMMEDIATYPE_VIDEOAUDIO && psStreamMediaInfoEx)
		{
			if (dwProgramNo == 0 && dwVideoStreamNo == 0)
				return psStreamMediaInfoEx->dwVideoFrameNum;
			else
				return 0;
		}
		else if (enumStreamMediaType == SDSTREAMMEDIATYPE_SINGLEPROGRAM && psSingleProgramMediaInfoEx)
		{
			if (dwProgramNo == 0 && dwVideoStreamNo < psSingleProgramMediaInfoEx->adwVideoFrameNum.GetDWSize())
				return psSingleProgramMediaInfoEx->adwVideoFrameNum[dwVideoStreamNo];
			else
				return 0;
		}
		else if (enumStreamMediaType == SDSTREAMMEDIATYPE_MULTIPROGRAM && psMultiProgramMediaInfoEx)
		{
			if (dwProgramNo < psMultiProgramMediaInfoEx->GetProgramNum())
			{
				if (dwVideoStreamNo < psMultiProgramMediaInfoEx->aSingleProgramStreamMediaInfoEx[dwProgramNo]->adwVideoFrameNum.GetDWSize())
					return psMultiProgramMediaInfoEx->aSingleProgramStreamMediaInfoEx[dwProgramNo]->adwVideoFrameNum[dwVideoStreamNo];
				else
					return 0;
			}
			else
				return 0;
		}
		else
			return 0;
	};

	SD_UINT32	GetAudioSampleCount(SD_UINT32 dwProgramNo = 0, SD_UINT32 dwAudioStreamNo = 0)
	{
		if (enumStreamMediaType == SDSTREAMMEDIATYPE_VIDEOAUDIO && psStreamMediaInfoEx)
		{
			if (dwProgramNo == 0 && dwAudioStreamNo == 0)
				return psStreamMediaInfoEx->dwAudioSamplesNum;
			else
				return 0;
		}
		else if (enumStreamMediaType == SDSTREAMMEDIATYPE_SINGLEPROGRAM && psSingleProgramMediaInfoEx)
		{
			if (dwProgramNo == 0 && dwAudioStreamNo < psSingleProgramMediaInfoEx->adwAudioSamplesNum.GetDWSize())
				return psSingleProgramMediaInfoEx->adwAudioSamplesNum[dwAudioStreamNo];
			else
				return 0;
		}
		else if (enumStreamMediaType == SDSTREAMMEDIATYPE_MULTIPROGRAM && psMultiProgramMediaInfoEx)
		{
			if (dwProgramNo < psMultiProgramMediaInfoEx->GetProgramNum())
			{
				if (dwAudioStreamNo < psMultiProgramMediaInfoEx->aSingleProgramStreamMediaInfoEx[dwProgramNo]->adwAudioSamplesNum.GetDWSize())
					return psMultiProgramMediaInfoEx->aSingleProgramStreamMediaInfoEx[dwProgramNo]->adwAudioSamplesNum[dwAudioStreamNo];
				else
					return 0;
			}
			else
				return 0;
		}
		else
			return 0;
	};

	SD_UINT32	GetSubTitleFrameCount(SD_UINT32 dwProgramNo = 0, SD_UINT32 dwSubTitleStreamNo = 0)
	{
		if (enumStreamMediaType == SDSTREAMMEDIATYPE_VIDEOAUDIO)
			return 0;
		else if (enumStreamMediaType == SDSTREAMMEDIATYPE_SINGLEPROGRAM && psSingleProgramMediaInfoEx)
		{
			if (dwProgramNo == 0 && dwSubTitleStreamNo < psSingleProgramMediaInfoEx->adwSubTitleFrameNum.GetDWSize())
				return psSingleProgramMediaInfoEx->adwSubTitleFrameNum[dwSubTitleStreamNo];
			else
				return 0;
		}
		else if (enumStreamMediaType == SDSTREAMMEDIATYPE_MULTIPROGRAM && psMultiProgramMediaInfoEx)
		{
			if (dwProgramNo < psMultiProgramMediaInfoEx->GetProgramNum())
			{
				if (dwSubTitleStreamNo < psMultiProgramMediaInfoEx->aSingleProgramStreamMediaInfoEx[dwProgramNo]->adwSubTitleFrameNum.GetDWSize())
					return psMultiProgramMediaInfoEx->aSingleProgramStreamMediaInfoEx[dwProgramNo]->adwSubTitleFrameNum[dwSubTitleStreamNo];
				else
					return 0;
			}
			else
				return 0;
		}
		else
			return 0;
	};

	SD_UINT64	GetFileSize()
	{
		if (enumStreamMediaType == SDSTREAMMEDIATYPE_VIDEOAUDIO && psStreamMediaInfoEx)
			return psStreamMediaInfoEx->llFileSize;
		else if (enumStreamMediaType == SDSTREAMMEDIATYPE_SINGLEPROGRAM && psSingleProgramMediaInfoEx)
			return psSingleProgramMediaInfoEx->llFileSize;
		else if (enumStreamMediaType == SDSTREAMMEDIATYPE_MULTIPROGRAM && psMultiProgramMediaInfoEx)
			return psMultiProgramMediaInfoEx->GetFileSize();
		else
			return 0;
	};

	SD_BOOL	SetFileSize(SD_UINT64 llFileSize)
	{
		if (enumStreamMediaType == SDSTREAMMEDIATYPE_VIDEOAUDIO && psStreamMediaInfoEx)
			psStreamMediaInfoEx->llFileSize = llFileSize;
		else if (enumStreamMediaType == SDSTREAMMEDIATYPE_SINGLEPROGRAM && psSingleProgramMediaInfoEx)
			psSingleProgramMediaInfoEx->llFileSize = llFileSize;
		else if (enumStreamMediaType == SDSTREAMMEDIATYPE_MULTIPROGRAM && psMultiProgramMediaInfoEx)
		{
			if (psMultiProgramMediaInfoEx->GetProgramNum() > 0)
				psMultiProgramMediaInfoEx->aSingleProgramStreamMediaInfoEx[0]->llFileSize = llFileSize;
			else
				return SD_FALSE;
		} 
		else
			return SD_FALSE;
		return SD_TRUE;
	};

	SD_BOOL	SetVideoFrameCount(SD_UINT32 dwVideoFrameNum, SD_UINT32 dwProgramNo = 0, SD_UINT32 dwVideoStreamNo = 0)
	{
		if (enumStreamMediaType == SDSTREAMMEDIATYPE_VIDEOAUDIO && psStreamMediaInfoEx)
		{
			if (dwProgramNo == 0 && dwVideoStreamNo == 0)
				psStreamMediaInfoEx->dwVideoFrameNum = dwVideoFrameNum;
			else
				return SD_FALSE;
		}
		else if (enumStreamMediaType == SDSTREAMMEDIATYPE_SINGLEPROGRAM && psSingleProgramMediaInfoEx)
		{
			if (dwProgramNo == 0 && dwVideoStreamNo < psSingleProgramMediaInfoEx->adwVideoFrameNum.GetDWSize())
				psSingleProgramMediaInfoEx->adwVideoFrameNum[dwVideoStreamNo] = dwVideoFrameNum;
			else
				return SD_FALSE;
		}
		else if (enumStreamMediaType == SDSTREAMMEDIATYPE_MULTIPROGRAM && psMultiProgramMediaInfoEx)
		{
			if (dwProgramNo < psMultiProgramMediaInfoEx->GetProgramNum())
			{
				if (dwVideoStreamNo < psMultiProgramMediaInfoEx->aSingleProgramStreamMediaInfoEx[dwProgramNo]->adwVideoFrameNum.GetDWSize())
					psMultiProgramMediaInfoEx->aSingleProgramStreamMediaInfoEx[dwProgramNo]->adwVideoFrameNum[dwVideoStreamNo] = dwVideoFrameNum;
				else
					return SD_FALSE;
			}
			else
				return SD_FALSE;
		}
		else
			return SD_FALSE;
		return SD_TRUE;
	};

	SD_BOOL	SetAudioSampleCount(SD_UINT32 dwAudioSamplesNum, SD_UINT32 dwProgramNo = 0, SD_UINT32 dwAudioStreamNo = 0)
	{
		if (enumStreamMediaType == SDSTREAMMEDIATYPE_VIDEOAUDIO && psStreamMediaInfoEx)
		{
			if (dwProgramNo == 0 && dwAudioStreamNo == 0)
				psStreamMediaInfoEx->dwAudioSamplesNum = dwAudioSamplesNum;
			else
				return SD_FALSE;
		}
		else if (enumStreamMediaType == SDSTREAMMEDIATYPE_SINGLEPROGRAM && psSingleProgramMediaInfoEx)
		{
			if (dwProgramNo == 0 && dwAudioStreamNo < psSingleProgramMediaInfoEx->adwAudioSamplesNum.GetDWSize())
				psSingleProgramMediaInfoEx->adwAudioSamplesNum[dwAudioStreamNo] = dwAudioSamplesNum;
			else
				return SD_FALSE;
		}
		else if (enumStreamMediaType == SDSTREAMMEDIATYPE_MULTIPROGRAM && psMultiProgramMediaInfoEx)
		{
			if (dwProgramNo < psMultiProgramMediaInfoEx->GetProgramNum())
			{
				if (dwAudioStreamNo < psMultiProgramMediaInfoEx->aSingleProgramStreamMediaInfoEx[dwProgramNo]->adwAudioSamplesNum.GetDWSize())
					psMultiProgramMediaInfoEx->aSingleProgramStreamMediaInfoEx[dwProgramNo]->adwAudioSamplesNum[dwAudioStreamNo] = dwAudioSamplesNum;
				else
					return SD_FALSE;
			}
			else
				return SD_FALSE;
		}
		else
			return SD_FALSE;
		return SD_TRUE;
	};

	SD_BOOL	SetSubTitleFrameCount(SD_UINT32 dwSubTitleFrameNum, SD_UINT32 dwProgramNo = 0, SD_UINT32 dwSubTitleStreamNo = 0)
	{
		if (enumStreamMediaType == SDSTREAMMEDIATYPE_SINGLEPROGRAM && psSingleProgramMediaInfoEx)
		{
			if (dwProgramNo == 0 && dwSubTitleStreamNo < psSingleProgramMediaInfoEx->adwSubTitleFrameNum.GetDWSize())
				psSingleProgramMediaInfoEx->adwSubTitleFrameNum[dwSubTitleStreamNo] = dwSubTitleFrameNum;
			else
				return SD_FALSE;
		}
		else if (enumStreamMediaType == SDSTREAMMEDIATYPE_MULTIPROGRAM && psMultiProgramMediaInfoEx)
		{
			if (dwProgramNo < psMultiProgramMediaInfoEx->GetProgramNum())
			{
				if (dwSubTitleStreamNo < psMultiProgramMediaInfoEx->aSingleProgramStreamMediaInfoEx[dwProgramNo]->adwSubTitleFrameNum.GetDWSize())
					psMultiProgramMediaInfoEx->aSingleProgramStreamMediaInfoEx[dwProgramNo]->adwSubTitleFrameNum[dwSubTitleStreamNo] = dwSubTitleFrameNum;
				else
					return SD_FALSE;
			}
			else
				return SD_FALSE;
		}
		else
			return SD_FALSE;
		return SD_TRUE;
	};

	// 序列化支持
	SD_INT32 GetSerializationSize()
	{
		return  SerializationToPtr(SD_NULL, 0);
	};
	SD_INT32 SerializationToPtr(SD_UINT8* pBuffer, SD_INT32 iBufferSize)
	{
		SD_INT32 iPtrSize = 0;
		if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &enumStreamMediaType, sizeof(enumStreamMediaType));
		iPtrSize += sizeof(enumStreamMediaType);
		SD_INT32 iInfoSize = 0;
		if ((SDSTREAMMEDIATYPE_VIDEOAUDIO == enumStreamMediaType) && (SD_NULL != psStreamMediaInfoEx))
		{
			iInfoSize = psStreamMediaInfoEx->GetSerializationSize();
			if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &iInfoSize, sizeof(iInfoSize));
			iPtrSize += sizeof(iInfoSize);
			if (SD_NULL != pBuffer) psStreamMediaInfoEx->SerializationToPtr(pBuffer + iPtrSize, iInfoSize);
			iPtrSize += iInfoSize;
		}
		else if ((SDSTREAMMEDIATYPE_SINGLEPROGRAM == enumStreamMediaType) && (SD_NULL != psSingleProgramMediaInfoEx))
		{
			iInfoSize = psSingleProgramMediaInfoEx->GetSerializationSize();
			if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &iInfoSize, sizeof(iInfoSize));
			iPtrSize += sizeof(iInfoSize);
			if (SD_NULL != pBuffer) psSingleProgramMediaInfoEx->SerializationToPtr(pBuffer + iPtrSize, iInfoSize);
			iPtrSize += iInfoSize;
		}
		else if ((SDSTREAMMEDIATYPE_MULTIPROGRAM == enumStreamMediaType) && (SD_NULL != psMultiProgramMediaInfoEx))
		{
			iInfoSize = psMultiProgramMediaInfoEx->GetSerializationSize();
			if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &iInfoSize, sizeof(iInfoSize));
			iPtrSize += sizeof(iInfoSize);
			if (SD_NULL != pBuffer) psMultiProgramMediaInfoEx->SerializationToPtr(pBuffer + iPtrSize, iInfoSize);
			iPtrSize += iInfoSize;
		}
		else
		{
			if (SD_NULL != pBuffer) memcpy(pBuffer + iPtrSize, &iInfoSize, sizeof(iInfoSize));
			iPtrSize += sizeof(iInfoSize);
		}
		return iPtrSize;
	};
	SD_INT32 SerializationFromPtr(SD_UINT8* pBuffer, SD_INT32 iBufferSize)
	{
		SD_INT32 iPtrSize = 0;
		memcpy(&enumStreamMediaType, pBuffer + iPtrSize, sizeof(enumStreamMediaType)); iPtrSize += sizeof(enumStreamMediaType);
		SD_INT32 iInfoSize;
		memcpy(&iInfoSize, pBuffer + iPtrSize, sizeof(iInfoSize));  iPtrSize += sizeof(iInfoSize);
		if (SD_NULL != psStreamMediaInfoEx)
		{
			delete psStreamMediaInfoEx; psStreamMediaInfoEx = SD_NULL;
		}
		if (SD_NULL != psSingleProgramMediaInfoEx)
		{
			delete psSingleProgramMediaInfoEx; psSingleProgramMediaInfoEx = SD_NULL;
		}
		if (SD_NULL != psMultiProgramMediaInfoEx)
		{
			delete psMultiProgramMediaInfoEx; psMultiProgramMediaInfoEx = SD_NULL;
		}
		if ((SDSTREAMMEDIATYPE_VIDEOAUDIO == enumStreamMediaType) && (iInfoSize > 0))
		{
			psStreamMediaInfoEx = new SDStreamMediaInfoEx();
			psStreamMediaInfoEx->SerializationFromPtr(pBuffer + iPtrSize, iInfoSize);
			iPtrSize += iInfoSize;
		}
		else if ((SDSTREAMMEDIATYPE_SINGLEPROGRAM == enumStreamMediaType) && (iInfoSize > 0))
		{
			psSingleProgramMediaInfoEx = new SDSingleProgramStreamMediaInfoEx();
			psSingleProgramMediaInfoEx->SerializationFromPtr(pBuffer + iPtrSize, iInfoSize);
			iPtrSize += iInfoSize;
		}
		else if ((SDSTREAMMEDIATYPE_MULTIPROGRAM == enumStreamMediaType) && (iInfoSize > 0))
		{
			psMultiProgramMediaInfoEx = new SDMultiProgramStreamMediaInfoEx();
			psMultiProgramMediaInfoEx->SerializationFromPtr(pBuffer + iPtrSize, iInfoSize);
			iPtrSize += iInfoSize;
		}
		return iPtrSize;
	};
};
typedef CSDArray<SDGlobalStreamMediaInfoEx, SDGlobalStreamMediaInfoEx&> SDGlobalStreamMediaInfoExArray;

enum SD_MEDIADATASTREAM_TYPE	//媒体数据流数据类型
{
	SDMEDIADATASTREAMTYPE_Unknow		=	0,
	SDMEDIADATASTREAMTYPE_VIDEO1		=	0x00000001,		//视频流1
	SDMEDIADATASTREAMTYPE_VIDEO2		=	0x00000002,		//视频流2
	SDMEDIADATASTREAMTYPE_VIDEO3		=	0x00000004,		//视频流3
	SDMEDIADATASTREAMTYPE_VIDEO4		=	0x00000008,		//视频流4
	SDMEDIADATASTREAMTYPE_AUDIO1		=	0x00000100,		//音频流1
	SDMEDIADATASTREAMTYPE_AUDIO2		=	0x00000200,		//音频流2
	SDMEDIADATASTREAMTYPE_AUDIO3		=	0x00000400,		//音频流3
	SDMEDIADATASTREAMTYPE_AUDIO4		=	0x00000800,		//音频流4
	SDMEDIADATASTREAMTYPE_AUDIO5		=	0x00001000,		//音频流5
	SDMEDIADATASTREAMTYPE_AUDIO6		=	0x00002000,		//音频流6
	SDMEDIADATASTREAMTYPE_AUDIO7		=	0x00004000,		//音频流7
	SDMEDIADATASTREAMTYPE_AUDIO8		=	0x00008000,		//音频流8
	SDMEDIADATASTREAMTYPE_AUDIO9		=	0x00010000,		//音频流9
	SDMEDIADATASTREAMTYPE_AUDIO10		=	0x00020000,		//音频流10
	SDMEDIADATASTREAMTYPE_AUDIO11		=	0x00040000,		//音频流11
	SDMEDIADATASTREAMTYPE_AUDIO12		=	0x00080000,		//音频流12
	SDMEDIADATASTREAMTYPE_AUDIO13		=	0x00100000,		//音频流13
	SDMEDIADATASTREAMTYPE_AUDIO14		=	0x00200000,		//音频流14
	SDMEDIADATASTREAMTYPE_AUDIO15		=	0x00400000,		//音频流15
	SDMEDIADATASTREAMTYPE_AUDIO16		=	0x00800000,		//音频流16
	SDMEDIADATASTREAMTYPE_SUBTITLE1		=	0x01000000,		//字幕流1
	SDMEDIADATASTREAMTYPE_SUBTITLE2		=	0x02000000,		//字幕流2
	SDMEDIADATASTREAMTYPE_SUBTITLE3		=	0x04000000,		//字幕流3
	SDMEDIADATASTREAMTYPE_SUBTITLE4		=	0x08000000,		//字幕流4
	SDMEDIADATASTREAMTYPE_SUBTITLE5		=	0x10000000,		//字幕流5
	SDMEDIADATASTREAMTYPE_SUBTITLE6		=	0x20000000,		//字幕流6
	SDMEDIADATASTREAMTYPE_SUBTITLE7		=	0x40000000,		//字幕流7
	SDMEDIADATASTREAMTYPE_SUBTITLE8		=	0x80000000,		//字幕流8
};

enum SD_STREAMCOMPRESSDATA_ACTMODE	//流压缩数据获取/推送操作模式
{
	SDSCDACTMODE_UNKNOW					=	0,		
	SDSCDACTMODE_PR_VF_AL				=	1,		// V/T:[dwFramePos,dwFramePos+dwFrameNum);A:[[dwFramePos,dwFramePos+dwFrameNum))
	SDSCDACTMODE_PR_VF_AR				=	2,		// V/T:[dwFramePos,dwFramePos+dwFrameNum);A:((dwFramePos,dwFramePos+dwFrameNum]]
	SDSCDACTMODE_PR_VGOP_AL				=	3,		// V/T:[[dwFramePos,!dwFramePos+GOPSize);A:[[dwFramePos,!dwFramePos+GOPSize))
	SDSCDACTMODE_PR_VGOP_AR				=	4,		// V/T:[[dwFramePos,!dwFramePos+GOPSize);A:((dwFramePos,!dwFramePos+GOPSize]]
	SDSCDACTMODE_SEEK_VGOP_AMAX			=	5,		// V/T:[[dwFramePos,!dwFramePos+GOPSize);A:[[dwFramePos,!dwFramePos+GOPSize]]
	SDSCDACTMODE_SEEK_VGOP_AMIN			=	6,		// V/T:[[dwFramePos,!dwFramePos+GOPSize);A:((dwFramePos,!dwFramePos+GOPSize))
	SDSCDACTMODE_SEEK_VF_AMAX			=	7,		// V/T:[dwFramePos,dwFramePos+dwFrameNum);A:[[dwFramePos,dwFramePos+GOPSize]]
	SDSCDACTMODE_SEEK_VF_AMIN			=	8,		// V/T:[dwFramePos,dwFramePos+dwFrameNum);A:((dwFramePos,dwFramePos+GOPSize))
	SDSCDACTMODE_SEEK_VFI_APCM			=	9,		// V/T:[dwFramePos,dwFramePos+1);A:[dwFramePos,dwFramePos+1)
};

struct SDStreamCompressDataInfo		//流压缩数据信息
{
	SD_UINT32						dwStreamTypeFlag;			//媒体数据流数据类型组合；see SD_MEDIADATASTREAM_TYPE;
	SD_STREAMCOMPRESSDATA_ACTMODE	enumActMode;				//流压缩数据获取/推送操作模式
	SD_UINT32						dwPointPosInVideoFrame;		//获取流压缩数据调用时希望的时间位置, 以视频帧为单位
	SD_UINT32						dwPointNumInVideoFrame;		//获取流压缩数据调用时希望的时间长度, 以视频帧为单位
	SD_UINT32						dwProgramNo;				//节目号
	SD_BOOL							bIfSelfNewPtr;				//TRUE:调用者直接为结构变量pbBuffer用new方法分配内存，结构负责删除此内存； FALSE：结构变量pbBuffer直接引用外部数据指针,结构不管理此内存！！！
	SD_PUINT8						pbBuffer;					//流压缩数据指针
	SD_UINT32						dwBufSize;					//流压缩数据大小
	SD_UINT32						dwBufVideoFramePos;			//流压缩数据指针体现的第一个视频流帧位置
	SD_UINT32						dwBufVideoFrameNum;			//流压缩数据指针体现的第一个视频流帧数量
	SD_UINT32						dwBufAudioFramePos;			//流压缩数据指针体现的第一个音频流帧位置
	SD_UINT32						dwBufAudioFrameNum;			//流压缩数据指针体现的第一个音频流帧数量
	SD_UINT32						dwBufSubTitleFramePos;		//流压缩数据指针体现的第一个字幕流帧位置
	SD_UINT32						dwBufSubTitleFrameNum;		//流压缩数据指针体现的第一个字幕流帧数量

	SDStreamCompressDataInfo()
	{
		dwStreamTypeFlag = 0xffffffff;
		enumActMode = SDSCDACTMODE_UNKNOW;
		dwPointPosInVideoFrame = 0xffffffff;
		dwPointNumInVideoFrame = 0;
		dwProgramNo = 0;
		bIfSelfNewPtr = SD_TRUE;
		pbBuffer = SD_NULL;
		dwBufSize = 0;
		dwBufVideoFramePos = 0xffffffff;
		dwBufVideoFrameNum = 0;
		dwBufAudioFramePos = 0xffffffff;
		dwBufAudioFrameNum = 0;
		dwBufSubTitleFramePos = 0xffffffff;
		dwBufSubTitleFrameNum = 0;
	};

	SDStreamCompressDataInfo(const SDStreamCompressDataInfo &other)
	{
		*this = other;
	};

	~SDStreamCompressDataInfo()
	{
		if (pbBuffer && bIfSelfNewPtr)
			delete[] pbBuffer;
	};

	SDStreamCompressDataInfo& operator = (const SDStreamCompressDataInfo& other)
	{
		if (pbBuffer && bIfSelfNewPtr)
			delete[] pbBuffer;
		pbBuffer = SD_NULL;

		dwStreamTypeFlag = other.dwStreamTypeFlag;
		enumActMode = other.enumActMode;
		dwPointPosInVideoFrame = other.dwPointPosInVideoFrame;
		dwPointNumInVideoFrame = other.dwPointNumInVideoFrame;
		dwProgramNo = other.dwProgramNo;
		bIfSelfNewPtr = other.bIfSelfNewPtr;
		dwBufSize = other.dwBufSize;
		dwBufVideoFramePos = other.dwBufVideoFramePos;
		dwBufVideoFrameNum = other.dwBufVideoFrameNum;
		dwBufAudioFramePos = other.dwBufAudioFramePos;
		dwBufAudioFrameNum = other.dwBufAudioFrameNum;
		dwBufSubTitleFramePos = other.dwBufSubTitleFramePos;
		dwBufSubTitleFrameNum = other.dwBufSubTitleFrameNum;

		if (bIfSelfNewPtr)
		{
			if (dwBufSize > 0)
			{
				pbBuffer = new SD_UINT8[dwBufSize];
				memcpy(pbBuffer, other.pbBuffer, dwBufSize);
			}
		}
		else
			pbBuffer = other.pbBuffer;

		return *this;
	};

	SD_BOOL	IsIncludeVideoData()
	{
		if ((dwStreamTypeFlag & 0x0000000f))
			return SD_TRUE;
		else
			return SD_FALSE;
	};

	SD_BOOL	IsIncludeAudioData()
	{
		if ((dwStreamTypeFlag & 0x00ffff00))
			return SD_TRUE;
		else
			return SD_FALSE;
	};

	SD_BOOL	IsIncludeSubTitleData()
	{
		if ((dwStreamTypeFlag & 0xff000000))
			return SD_TRUE;
		else
			return SD_FALSE;
	};
};

//=======================================================================================
//与视音频信号、设备、数据块相关的扩展定义
//=======================================================================================
//	定义数据类型:
//		SDAUDIOFX_VOLUME;		//音频幅度的面向的归一化整数值变量
//	定义枚举:
//		SD_VIDEO_SIGNAL_TYPE;					// 视频信号传输类型
//		SD_AUDIO_SIGNAL_TYPE					// 音频信号传输类型
//		SD_RUN_STATE							// 播放状态类型。
//		SD_DEVICE_TYPE							// 设备类型
//		SD_DEVICE_STATUS						// 设备状态
//		SD_DEVICE_TAPE_FORMAT					// 设备磁带格式
//		SDVIDEO_SCALE_TYPE						// 高标清上下变换类型定义
//	定义结构:
//		SDVideoFrameImageBuffer, SDVideoFrameImageBufferPtrArray			//视频帧图像数据块定义
//		SDAudioSamplesSegmentBuffer, SDAudioSamplesSegmentBufferPtrArray	//音频采样数据块定义
//		SDVideoScaleWindow											//窗口类型的描述结构
//
//	定义函数:
//		SDAUDIOFX_VOLUME DOUBLETOSDAUDIOFXVOLUME(SD_DOUBLE dValue);	//归一化音频幅度与浮点型音频幅度的转换函数
//		SD_DOUBLE SDAUDIOFXVOLUMETODOUBLE(SDAUDIOFX_VOLUME fxValue);	//归一化音频幅度与浮点型音频幅度的转换函数
//		CSDString GetVideoSignalString(SD_VIDEO_SIGNAL_TYPE enumVideoSignalType);	//得到视频信号传输类型的名称
//		SD_BOOL	IsVideoSignalAnalog(SD_VIDEO_SIGNAL_TYPE enumVideoSignalType);	//判断此现视频信号类型是否为模拟信号
//		CSDString GetAudioSignalString(SD_AUDIO_SIGNAL_TYPE enumAudioSignalType);	//得到音频信号传输类型的名称
//		CSDString GetRunStateString(SD_RUN_STATE enumRunState);					//得到播放状态的名称
//		SD_UINT32	SDGetColorBarDef(int nIndex, SD_BOOL b75or100=SD_TRUE);		//得到彩条色值
//=======================================================================================
typedef unsigned long SDAUDIOFX_VOLUME;		//音频幅度的面向的归一化整数值变量
#define	MAXSDAUDIOFXVOLUME			0x1000000
#define	DOUBLETOSDAUDIOFXVOLUME(d)	(SDAUDIOFX_VOLUME)(0.5 + (SD_DOUBLE)(d) * (SD_DOUBLE)MAXSDAUDIOFXVOLUME)	//归一化音频幅度与浮点型音频幅度的转换函数
#define	SDAUDIOFXVOLUMETODOUBLE(t)	(SD_DOUBLE)((SD_DOUBLE)(t) / (SD_DOUBLE)MAXSDAUDIOFXVOLUME)

enum SD_VIDEO_SIGNAL_TYPE				// 视频信号传输类型
{
	SDVIDEOSIGNALTYPE_UNKNOW		=	0x00000000,		// 非法
	SDVIDEOSIGNALTYPE_Composite		=	0x00000001,		// 复合类型
	SDVIDEOSIGNALTYPE_YC			=	0x00000002,		// YC分量类型
	SDVIDEOSIGNALTYPE_Component		=	0x00000004,		// YUV分量类型
	SDVIDEOSIGNALTYPE_SDI			=	0x00000008,		// 串行传输
	SDVIDEOSIGNALTYPE_SDTI			=	0x00000010,
	SDVIDEOSIGNALTYPE_SDTI_CP		=	0x00000020,
	SDVIDEOSIGNALTYPE_IPNETWORK		=	0x00000040,
	SDVIDEOSIGNALTYPE_HDMI			=	0x00000100,
	SDVIDEOSIGNALTYPE_ASI			=	0x00000200,
	SDVIDEOSIGNALTYPE_DISPLAYPORT	=	0x00000400,
	SDVIDEOSIGNALTYPE_VGA			=	0x00000800,
	SDVIDEOSIGNALTYPE_DVI			=	0x00001000,
	SDVIDEOSIGNALTYPE_OPTICAL		=	0x00002000,		//光纤
};

//得到视频信号传输类型的名称
SD_INLINE CSDString GetVideoSignalString(SD_VIDEO_SIGNAL_TYPE enumVideoSignalType)
{
	CSDString strVideoSignal = _T("Unknow");

	switch(enumVideoSignalType)
	{
		case SDVIDEOSIGNALTYPE_Composite:
			strVideoSignal = _T("Composite");
			break;
		case SDVIDEOSIGNALTYPE_YC:
			strVideoSignal = _T("YC");
			break;
		case SDVIDEOSIGNALTYPE_Component:
			strVideoSignal = _T("Component");
			break;
		case SDVIDEOSIGNALTYPE_SDI:
			strVideoSignal = _T("SDI");
			break;
		case SDVIDEOSIGNALTYPE_SDTI:
			strVideoSignal = _T("SDTI");
			break;
		case SDVIDEOSIGNALTYPE_SDTI_CP:
			strVideoSignal = _T("SDTI_CP");
			break;
		case SDVIDEOSIGNALTYPE_IPNETWORK:
			strVideoSignal = _T("IP-Network");
			break;
		case SDVIDEOSIGNALTYPE_HDMI:
			strVideoSignal = _T("HDMI");
			break;
		case SDVIDEOSIGNALTYPE_ASI:
			strVideoSignal = _T("ASI");
			break;
		case SDVIDEOSIGNALTYPE_DISPLAYPORT:
			strVideoSignal = _T("DISPLAYPORT");
			break;
		case SDVIDEOSIGNALTYPE_VGA:
			strVideoSignal = _T("VGA");
			break;
		case SDVIDEOSIGNALTYPE_DVI:
			strVideoSignal = _T("DVI");
			break;
		case SDVIDEOSIGNALTYPE_OPTICAL:
			strVideoSignal = _T("Optical");
			break;
	}
	
	return strVideoSignal;
}

//判断此现视频信号类型是否为模拟信号
SD_INLINE	SD_BOOL	IsVideoSignalAnalog(SD_VIDEO_SIGNAL_TYPE enumVideoSignalType)
{
	if (enumVideoSignalType == SDVIDEOSIGNALTYPE_Composite ||
		enumVideoSignalType == SDVIDEOSIGNALTYPE_YC ||
		enumVideoSignalType == SDVIDEOSIGNALTYPE_Component)
		return SD_TRUE;
	else
		return SD_FALSE;
};

enum SD_AUDIO_SIGNAL_TYPE				// 音频信号传输类型
{
	SDAUDIOSIGNALTYPE_UNKNOW		=	0x00000000,
	SDAUDIOSIGNALTYPE_Analog		=	0x00000001,
	SDAUDIOSIGNALTYPE_AESEBU		=	0x00000002,
	SDAUDIOSIGNALTYPE_SDI			=	0x00000004,
	SDAUDIOSIGNALTYPE_SDTI			=	0x00000008,
	SDAUDIOSIGNALTYPE_SDTI_CP		=	0x00000010,
	SDAUDIOSIGNALTYPE_IPNETWORK		=	0x00000020,
	SDAUDIOSIGNALTYPE_HDMI			=	0x00000100,
	SDAUDIOSIGNALTYPE_ASI			=	0x00000200,
	SDAUDIOSIGNALTYPE_DISPLAYPORT	=	0x00000400,
	SDAUDIOSIGNALTYPE_OPTICAL		=	0x00000800,			//光纤
	SDAUDIOSIGNALTYPE_Mic			=	0x00001000,
	SDAUDIOSIGNALTYPE_HeadPhone		=	0x00002000,
};

//得到音频信号传输类型的名称
SD_INLINE CSDString GetAudioSignalString(SD_AUDIO_SIGNAL_TYPE enumAudioSignalType)
{
	CSDString strAudioSignal = _T("Unknow");

	switch(enumAudioSignalType)
	{
		case SDAUDIOSIGNALTYPE_Analog:
			strAudioSignal = _T("Analog");
			break;
		case SDAUDIOSIGNALTYPE_AESEBU:
			strAudioSignal = _T("AESEBU");
			break;
		case SDAUDIOSIGNALTYPE_SDI:
			strAudioSignal = _T("SDI");
			break;
		case SDAUDIOSIGNALTYPE_SDTI:
			strAudioSignal = _T("SDTI");
			break;
		case SDAUDIOSIGNALTYPE_SDTI_CP:
			strAudioSignal = _T("SDTI_CP");
			break;
		case SDAUDIOSIGNALTYPE_IPNETWORK:
			strAudioSignal = _T("IP-Network");
			break;
		case SDAUDIOSIGNALTYPE_HDMI:
			strAudioSignal = _T("HDMI");
			break;
		case SDAUDIOSIGNALTYPE_ASI:
			strAudioSignal = _T("ASI");
			break;
		case SDAUDIOSIGNALTYPE_DISPLAYPORT:
			strAudioSignal = _T("DISPLAYPORT");
			break;
		case SDAUDIOSIGNALTYPE_OPTICAL:
			strAudioSignal = _T("Optical");
			break;
		case SDAUDIOSIGNALTYPE_Mic:
			strAudioSignal = _T("Mic");
			break;
		case SDAUDIOSIGNALTYPE_HeadPhone:
			strAudioSignal = _T("HeadPhone");
			break;
	}
	
	return strAudioSignal;
}

enum SD_RUN_STATE						// 运行状态类型。
{ 
	SD_RUN_Unknow			= 0,
	SD_RUN_Stopped			= 1,
	SD_RUN_Paused			= 2,
	SD_RUN_Playing			= 3,
	SD_RUN_Looping			= 4,
	SD_RUN_Ending			= 5,
	SD_RUN_Intermediate		= 6,
	SD_RUN_JogShuttle		= 7,
	SD_RUN_Seek				= 8,
	SD_RUN_Recording		= 9,
	SD_RUN_Other			= 99,
};

//得到播放状态的名称
SD_INLINE CSDString GetRunStateString(SD_RUN_STATE enumRunState)
{
	CSDString strRunState = _T("Unknow");

	switch(enumRunState)
	{
		case SD_RUN_Stopped:
			strRunState = _T("Stopped");
			break;
		case SD_RUN_Paused:
			strRunState = _T("Paused");
			break;
		case SD_RUN_Playing:
			strRunState = _T("Playing");
			break;
		case SD_RUN_Looping:
			strRunState = _T("Looping");
			break;
		case SD_RUN_Ending:
			strRunState = _T("Ending");
			break;
		case SD_RUN_Intermediate:
			strRunState = _T("Intermediate");
			break;
		case SD_RUN_JogShuttle:
			strRunState = _T("JogShuttle");
			break;
		case SD_RUN_Seek:
			strRunState = _T("Seek");
			break;
		case SD_RUN_Recording:
			strRunState = _T("Recording");
			break;
		case SD_RUN_Other:
			strRunState = _T("Other");
			break;
	}
	
	return strRunState;
};

// 得到彩条色值
SD_INLINE	SD_UINT32	SDGetColorBarDef(int nIndex, SD_BOOL b75or100=SD_TRUE)
{
	switch(nIndex) 
	{
		case 0:
			if (b75or100)
				return (0xff000000	+ 255*256*256 + 255*256 + 255);
			else
				return (0xff000000	+ 255*256*256 + 255*256 + 255);
		case 1:
			if (b75or100)
				return (0xff000000  + 191*256*256 + 191*256);
			else
				return (0xff000000  + 255*256*256 + 255*256);
		case 2:
			if (b75or100)
				return (0xff000000  +               191*256 + 191);
			else
				return (0xff000000  +               255*256 + 255);
		case 3:
			if (b75or100)
				return (0xff000000  +               191*256);
			else
				return (0xff000000  +               255*256);
		case 4:
			if (b75or100)
				return (0xff000000  + 191*256*256 +           191);
			else
				return (0xff000000  + 255*256*256 +           255);
		case 5:
			if (b75or100)
				return (0xff000000  + 191*256*256);
			else
				return (0xff000000  + 255*256*256);
		case 6:
			if (b75or100)
				return (0xff000000  +                         191);
			else
				return (0xff000000  +                         255);
		default:
			return	   (0xff000000);
	}
};

typedef	SD_UINT32 SDDEVICETYPEFLAG;
enum SD_DEVICE_TYPE			// 设备类型
{
	SD_DEVICE_UNKNOW	=	0x00000000,

	SD_DEVICE_VTR1		=	0x00000001,
	SD_DEVICE_VTR2		=	0x00000002,
	SD_DEVICE_VTR3		=	0x00000004,
	SD_DEVICE_VTR4		=	0x00000008,
	SD_DEVICE_VTR5		=	0x00000010,
	SD_DEVICE_VTR6		=	0x00000020,
	SD_DEVICE_VTR7		=	0x00000040,
	SD_DEVICE_VTR8		=	0x00000080,
	SD_DEVICE_VTR9		=	0x00000100,
	SD_DEVICE_VTR10		=	0x00000200,
	SD_DEVICE_VTR11		=	0x00000400,
	SD_DEVICE_VTR12		=	0x00000800,
	SD_DEVICE_VTR13		=	0x00001000,
	SD_DEVICE_VTR14		=	0x00002000,
	SD_DEVICE_VTR15		=	0x00004000,
	SD_DEVICE_VTR16		=	0x00008000,

	SD_DEVICE_1394		=	0x00010000,
	SD_DEVICE_VTR17		=	0x00100000,
	SD_DEVICE_VTR18		=	0x00200000,
	SD_DEVICE_VTR19		=	0x00400000,
	SD_DEVICE_VTR20		=	0x00800000,
	SD_DEVICE_VTR21		=	0x01000000,
	SD_DEVICE_VTR22		=	0x02000000,
	SD_DEVICE_VTR23		=	0x04000000,
	SD_DEVICE_VTR24		=	0x08000000,
};

enum SD_DEVICE_STATUS		// 设备状态
{
	SD_DEVICE_NOT_READY,			// not ready.
	SD_DEVICE_NO_TAPE,				// no tape in recorder.
	SD_DEVICE_PLAY,					// play	
	SD_DEVICE_STOP,					// stop
	SD_DEVICE_PAUSE,				// pause
	SD_DEVICE_FF,					// fast forward
	SD_DEVICE_REW,					// rewind
	SD_DEVICE_RECORD,				// record
	SD_DEVICE_STEP,					// single step 
	SD_DEVICE_SHUTTLE,				// shuttle forward
	SD_DEVICE_VAR,					//
	SD_DEVICE_OTHER,				// reserve.
};

enum SD_DEVICE_TAPE_FORMAT	// 设备磁带格式
{
	SDDEVICETAPEFORMAT_FRAME,
	SDDEVICETAPEFORMAT_2398,
	SDDEVICETAPEFORMAT_24,
	SDDEVICETAPEFORMAT_25,
	SDDEVICETAPEFORMAT_2997,
	SDDEVICETAPEFORMAT_30,
	SDDEVICETAPEFORMAT_50,
	SDDEVICETAPEFORMAT_5994,
	SDDEVICETAPEFORMAT_60,
};

//========================================================================================
typedef	SD_UINT32 SDDEVICERECTRACKFLAG;
//----------------------------------------------------------------------------------------
#define	SDDEVICE_RECTRACK_AUDIO_ALL				0x10000000	//	or any of the following OR'd together
#define SDDEVICE_RECTRACK_AUDIO_1				0x0000001L
#define SDDEVICE_RECTRACK_AUDIO_2				0x0000002L
#define SDDEVICE_RECTRACK_AUDIO_3				0x0000004L
#define SDDEVICE_RECTRACK_AUDIO_4				0x0000008L
#define SDDEVICE_RECTRACK_AUDIO_5				0x0000010L
#define SDDEVICE_RECTRACK_AUDIO_6				0x0000020L
#define SDDEVICE_RECTRACK_AUDIO_7				0x0000040L
#define SDDEVICE_RECTRACK_AUDIO_8				0x0000080L
#define SDDEVICE_RECTRACK_AUDIO_9				0x0000100L
#define SDDEVICE_RECTRACK_AUDIO_10				0x0000200L
#define SDDEVICE_RECTRACK_AUDIO_11				0x0000400L
#define SDDEVICE_RECTRACK_AUDIO_12				0x0000800L
#define SDDEVICE_RECTRACK_AUDIO_13				0x0001000L
#define SDDEVICE_RECTRACK_AUDIO_14				0x0002000L
#define SDDEVICE_RECTRACK_AUDIO_15				0x0004000L
#define SDDEVICE_RECTRACK_AUDIO_16				0x0008000L
#define SDDEVICE_RECTRACK_AUDIO_17				0x0010000L
#define SDDEVICE_RECTRACK_AUDIO_18				0x0020000L
#define SDDEVICE_RECTRACK_AUDIO_19				0x0040000L
#define SDDEVICE_RECTRACK_AUDIO_20				0x0080000L
#define SDDEVICE_RECTRACK_AUDIO_21				0x0100000L
#define SDDEVICE_RECTRACK_AUDIO_22				0x0200000L
#define SDDEVICE_RECTRACK_AUDIO_23				0x0400000L
#define SDDEVICE_RECTRACK_AUDIO_24				0x0800000L
#define SDDEVICE_RECTRACK_VIDEO					0x2000000L	
//========================================================================================

//========================================================================================
#define SDDEVICE_RECMODE_ASSEMBLE				(0x1000L+660L)
#define SDDEVICE_RECMODE_INSERT					(0x1000L+661L)
//========================================================================================

enum SD_FIELD
{
   SD_ODD_FIELD			=	0,		//奇数场
   SD_EVEN_FIELD		=	1,		//偶数场
   SD_BOTH_FIELD		=	2,		//奇偶场
};

struct SDVideoFrameImageBuffer : public SDVideoFrameImageBufInfo		//视频帧图像数据块定义
{
	SD_PUINT8			pbBuffer;					// 视频帧图像数据块指针
	SD_BOOL				bIfDirectNewBufPtr;			// TRUE:结构用 new 方法分配图像指针的内存，结构负责删除此内存； FALSE：图像指针的分配、删除等完全由调用者来控制
	
	SDVideoFrameImageBuffer()
	{
		pbBuffer = SD_NULL;
		bIfDirectNewBufPtr = SD_FALSE;
	};

	SDVideoFrameImageBuffer(const SDVideoFrameImageBuffer &other)
	{
		*this = other;
	};

	~SDVideoFrameImageBuffer()
	{
		if (pbBuffer && bIfDirectNewBufPtr)
			delete[] pbBuffer;
	};

	SD_VOID	Release()
	{
		if (pbBuffer && bIfDirectNewBufPtr) 
			delete[] pbBuffer;
		pbBuffer = SD_NULL;
		bIfDirectNewBufPtr = SD_FALSE;
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

	SD_BOOL	IsValid()
	{
		if (pbBuffer == SD_NULL || dwXSize <= 0 || dwYSize <= 0 || enumColorFormat == SDCOLORFORMAT_UNKNOW)
			return SD_FALSE;
		if (dwScanXByteSize == 0)
			return SD_TRUE;

		SD_UINT32	dwCalcBufByteSize = GetColorFormatBufSizeInByte(enumColorFormat, dwXSize, dwYSize);
		if (dwCalcBufByteSize <= dwScanXByteSize*dwYSize)
			return SD_TRUE;
		else
			return SD_FALSE;
	};

	SDVideoFrameImageBuffer& operator = (const SDVideoFrameImageBuffer& other)
	{
		Release();

		SD_UINT32	dwCalcBufByteSize = GetColorFormatBufSizeInByte(other.enumColorFormat, other.dwXSize, other.dwYSize);
		if (other.pbBuffer && other.dwXSize > 0 && other.dwYSize > 0 && (other.dwScanXByteSize == 0 || dwCalcBufByteSize <= other.dwScanXByteSize*other.dwYSize))
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
			bIfDirectNewBufPtr = other.bIfDirectNewBufPtr;

			if (bIfDirectNewBufPtr)
			{
				SD_UINT32	dwNeedBufByteSize = dwScanXByteSize*dwYSize;
				if (dwNeedBufByteSize == 0)
					dwNeedBufByteSize = dwCalcBufByteSize;
				pbBuffer = new SD_UINT8[dwNeedBufByteSize];
				memcpy(pbBuffer, other.pbBuffer, dwNeedBufByteSize);
			}
			else
				pbBuffer = other.pbBuffer;
		}
		return *this;
	};
};
typedef CSDArray<SDVideoFrameImageBuffer*, SDVideoFrameImageBuffer*&> SDVideoFrameImageBufferPtrArray;

SD_INLINE SD_VOID SDRelease(SDVideoFrameImageBufferPtrArray *paDataArray)
{
	if (paDataArray) 
	{
		SD_UINT32	size = paDataArray->GetDWSize();
		for (SD_UINT32 i=0; i<size; i++) 
		{
			SDVideoFrameImageBuffer *pElement = paDataArray->GetAt(i);
			pElement->Release();
			delete pElement;
		}
		paDataArray->RemoveAll();
	}
};

SD_INLINE SD_BOOL SDClone(SDVideoFrameImageBufferPtrArray *pNewData, const SDVideoFrameImageBufferPtrArray *pOldData)
{
	if (pNewData == SD_NULL || pOldData == SD_NULL)
		return SD_FALSE;

	SDRelease(pNewData);

	SD_UINT32 size = pOldData->GetDWSize();
	for (SD_UINT32 i=0; i<size; i++) 
	{
		SDVideoFrameImageBuffer *pNewElement = new SDVideoFrameImageBuffer;
		SDVideoFrameImageBuffer *pOldElement = pOldData->GetAt(i);
		(*pNewElement) = (*pOldElement);
		pNewData->Add(pNewElement);
	}
	return SD_TRUE;
};

struct SDAudioSamplesSegmentBuffer : public SDAudioSamplesBufInfo		//音频采样数据块定义
{
	SD_PUINT8			pbBuffer;					// 音频采样数据块指针
	SD_UINT32			dwSamplesCount;				// 音频采样数
	SD_BOOL				bIfDirectNewBufPtr;			// TRUE:结构用 new 方法分配图像指针的内存，结构负责删除此内存； FALSE：图像指针的分配、删除等完全由调用者来控制

	SDAudioSamplesSegmentBuffer()
	{
		pbBuffer = SD_NULL;
		dwSamplesCount = 0;
		bIfDirectNewBufPtr = SD_FALSE;
	};

	SDAudioSamplesSegmentBuffer(const SDAudioSamplesSegmentBuffer &other)
	{
		*this = other;
	};

	~SDAudioSamplesSegmentBuffer()
	{
		if (pbBuffer && bIfDirectNewBufPtr)
			delete[] pbBuffer;
	};

	SDAudioSamplesSegmentBuffer& operator = (const SDAudioSamplesSegmentBuffer& other)
	{
		if (pbBuffer && bIfDirectNewBufPtr) 
			delete[] pbBuffer;
		dwSamplesCount = other.dwSamplesCount;
		bIfDirectNewBufPtr = other.bIfDirectNewBufPtr;
		dwChannels = other.dwChannels;
		dwBitsPerSample = other.dwBitsPerSample;
		dwSamplesPerSec = other.dwSamplesPerSec;
		dwAvgBitsPerSec = other.dwAvgBitsPerSec;
		dwBlockAlign = other.dwBlockAlign;
		enumAudioCFG = other.enumAudioCFG;
		enumChannelSamplesFormat = other.enumChannelSamplesFormat;

		SD_UINT32 dwNeedBufByteSize = GetChannelSamplesFormatBufSizeInByte(enumChannelSamplesFormat, dwChannels, dwBlockAlign, dwSamplesCount);
		if (bIfDirectNewBufPtr && dwNeedBufByteSize > 0)
		{
			pbBuffer = new SD_UINT8[dwNeedBufByteSize];
			memcpy(pbBuffer, other.pbBuffer, dwNeedBufByteSize);
		}
		else
			pbBuffer = other.pbBuffer;
		return *this;
	};
};
typedef CSDArray<SDAudioSamplesSegmentBuffer*, SDAudioSamplesSegmentBuffer*&> SDAudioSamplesSegmentBufferPtrArray;

SD_INLINE SD_VOID SDRelease(SDAudioSamplesSegmentBufferPtrArray *paDataArray)
{
	if (paDataArray) 
	{
		SD_UINT32	size = paDataArray->GetDWSize();
		for (SD_UINT32 i=0; i<size; i++) 
		{
			SDAudioSamplesSegmentBuffer *pElement = paDataArray->GetAt(i);
			delete pElement;
		}
		paDataArray->RemoveAll();
	}
};

SD_INLINE SD_BOOL SDClone(SDAudioSamplesSegmentBufferPtrArray *pNewData, const SDAudioSamplesSegmentBufferPtrArray *pOldData)
{
	if (pNewData == SD_NULL || pOldData == SD_NULL)
		return SD_FALSE;

	SDRelease(pNewData);

	SD_UINT32 size = pOldData->GetDWSize();
	for (SD_UINT32 i=0; i<size; i++) 
	{
		SDAudioSamplesSegmentBuffer *pNewElement = new SDAudioSamplesSegmentBuffer;
		SDAudioSamplesSegmentBuffer *pOldElement = pOldData->GetAt(i);
		(*pNewElement) = (*pOldElement);
		pNewData->Add(pNewElement);
	}
	return SD_TRUE;
};

enum SDVIDEO_SCALE_TYPE		//高标清上下变换类型定义
{
	SDVIDEO_SCALE_TYPE_NONE					= 0,
	SDVIDEO_SCALE_TYPE_BOX					= 1,	//信箱 
	SDVIDEO_SCALE_TYPE_ZOOM					= 2,	//放大	
	SDVIDEO_SCALE_TYPE_CUT					= 3,	//切边
	SDVIDEO_SCALE_TYPE_WINDOW				= 4,	//窗口
};

struct SDVideoScaleWindow		//窗口类型的描述结构
{
	SD_POINT		ptCenter;					//中心位置   
	SD_COLORREF		clBKColor;					//背景颜色	
	SD_TCHAR		strBKImageFileName[256];	//背景图片

	SDVideoScaleWindow()
	{
		ptCenter.x = 0;
		ptCenter.y = 0; 

		clBKColor = SD_ARGB(0 , 0 ,0 , 0);
		strBKImageFileName[0] = 0;
	};

	SDVideoScaleWindow(const SDVideoScaleWindow &other)
	{
		*this = other;
	};

	SDVideoScaleWindow& operator = (const SDVideoScaleWindow& other)
	{
		ptCenter  = other.ptCenter;
		clBKColor = other.clBKColor;
		memcpy(strBKImageFileName, other.strBKImageFileName, 256*sizeof(SD_TCHAR));
		return *this;
	};
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

