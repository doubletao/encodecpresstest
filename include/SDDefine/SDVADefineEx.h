////////////////////////////////////////////////////////////////////////////////
//  File:   SDVADefineEx.h
//==============================================================================
//  Description:
//      edit 系统公用宏，结构，函数定义，对视音频编解码的定义扩充，依赖SDVADefine.h
//==============================================================================

#if !defined( __H__SDVADefineEx__H__ )
#define __H__SDVADefineEx__H__

#include <shlwapi.h>
#include <process.h>
#include <atlbase.h>

#include  "SDType.h"
#include  "SDString.h"
#include  "SDDefine.h"
#include  "SDVADefine.h"

#define		PAI						3.1415926
#define		WM_SD_BASE				WM_USER+1000

//	资源类型定义
typedef	DWORD SDRESTYPEFLAG;
enum SDITEM_RESTYPE
{
	SDRESTYPE_UNKNOWN			= 0x00000000,				//  未知
	SDRESTYPE_CLIP				= 0x00000001,				//	素材
	SDRESTYPE_EDL				= 0x00000002,				//  编辑条目(故事板...)
	SDRESTYPE_NEWSEDL			= 0x00000004,				//  新闻编辑条目
	SDRESTYPE_EFFMODAL			= 0x00000008,				//  特技模板
	SDRESTYPE_XCGMODAL			= 0x00000010,				//	字幕模板
	SDRESTYPE_PROJECT			= 0x00000020,				//	项目
	SDRESTYPE_PROGRAM			= 0x00000040,				//	节目
	SDRESTYPE_EFFKEYMODAL		= 0x00000080,				//  特技关键帧模板
	SDRESTYPE_XCGKEYMODAL		= 0x00000100,				//	字幕关键帧模板
	SDRESTYPE_NEWS				= 0x00000200,				//	新闻条目
	SDRESTYPE_RUNLIST			= 0x00000400,				//	播出单
	SDRESTYPE_LAYOUT			= 0x00000800,
	SDRESTYPE_LAYOUTMODAL		= 0x00001000,
	SDRESTYPE_CGSCENCE			= 0x00002000,
	SDRESTYPE_LIST				= 0x00004000,				//	列表(List)
	SDRESTYPE_OTHER				= 0x80000000,				//	其它
};

//	资源拥有者类型定义
typedef	DWORD SDRESOWNERTYPEFLAG;
enum SDITEM_OWNERTYPE
{
	SDRES_OWNERTYPE_UNKNOW			=	0x00000000,		//  未知
	SDRES_OWNERTYPE_PUBLIC			=	0x00000001,		
	SDRES_OWNERTYPE_NMUSER			=	0x00000002,
	SDRES_OWNERTYPE_USER			=	0x00000004,
	SDRES_OWNERTYPE_SERVICEOBJECT	=	0x00000008,
	SDRES_OWNERTYPE_LEVEL			=	0x00000010,
	SDRES_OWNERTYPE_ACTOR			=	0x00000020,
	SDRES_OWNERTYPE_MIXER			=	0x80000000,
};

//=======================================================================================
// delete 替代宏
#ifndef	deleteC
	#define	deleteC(p) \
		do{ \
			if(p){ \
				delete (p); \
				(p) = NULL; \
			} \
		}while(0)
#endif	// !deleteC

// DeleteObject 替代宏
#ifndef	DeleteObjectC
	#define	DeleteObjectC(p) \
		do{ \
			if(p){ \
				::DeleteObject((HGDIOBJ)(p)); \
				(p) = NULL; \
			} \
		}while(0)
#endif	// !DeleteObjectC


//-----------------------------------------------------------------------------------------------


//=======================================================================================
//标记点定义
enum SD_MARKPOINT_TYPE
{
	SD_MARKPOINT_TYPE_1		= 0x00000001,
	SD_MARKPOINT_TYPE_2		= 0x00000002,
	SD_MARKPOINT_TYPE_3		= 0x00000004,
	SD_MARKPOINT_TYPE_4		= 0x00000008,
	SD_MARKPOINT_TYPE_5		= 0x00000010,
	SD_MARKPOINT_TYPE_6		= 0x00000020,
};

struct SDMarkPointInfo
{
	CSDString		strName;		//标记点名字
	DWORD		dwFrame;		//标记点位置
	CSDString		strHint;        //标记点描述
	DWORD		dwType;			//标记点类型
	COLORREF	clrMark;        //标记点颜色

	SDMarkPointInfo()
	{
		strName		= _T("");
		dwFrame		= 0;
		strHint		= _T("");
		dwType		= 0;
		clrMark		= RGB(0,0,0);
	};

	SDMarkPointInfo(const SDMarkPointInfo &other)
	{
		*this = other;
	};

	SDMarkPointInfo& operator = (const SDMarkPointInfo& other)
	{
		strName		= other.strName;
		dwFrame		= other.dwFrame;
		strHint		= other.strHint;
		dwType		= other.dwType;
		clrMark		= other.clrMark;	
		return *this;
	};
};
typedef CSDArray<SDMarkPointInfo, SDMarkPointInfo&> SDMarkPointInfoArray;

struct SDMarkSegmentInfo
{
	CSDString	strName;
	DWORD	dwSFrame;
	DWORD	dwEFrame;
	CSDString	strHint;
	DWORD	dwType;

	SDMarkSegmentInfo()
	{
		strName = _T("");
		dwSFrame = 0;
		dwEFrame = 0;
		strHint = _T("");
		dwType = 0;
	};

	SDMarkSegmentInfo(const SDMarkSegmentInfo &other)
	{
		*this = other;
	};

	SDMarkSegmentInfo& operator = (const SDMarkSegmentInfo& other)
	{
		strName = other.strName;
		dwSFrame = other.dwSFrame;
		dwEFrame = other.dwEFrame;
		strHint = other.strHint;
		dwType = other.dwType;
		return *this;
	};
};
typedef CSDArray<SDMarkSegmentInfo, SDMarkSegmentInfo&> SDMarkSegmentInfoArray;

//=======================================================================================
//根据AFD信息得到上下变换类型，bDown表示是否是下变换，
inline SDVIDEO_SCALE_TYPE SDGetScaleTypeFromAFD( int ar , int a1 , int a2 , int a3 , int a4 , BOOL& bDown )
{
	switch(ar)
	{
	case 0:
		bDown=FALSE;
		break;
	case 1:
		bDown=TRUE;
		break;
	}
	SDVIDEO_SCALE_TYPE eumRet=SDVIDEO_SCALE_TYPE_NONE;
	if(bDown)
	{
		if( (a1 == 1) && (a2 == 0) && (a3 == 1) && (a4 == 0 ) )
		{
			//"1010"
			eumRet=SDVIDEO_SCALE_TYPE_BOX;
		}
		else if( (a1 == 1) && (a2 == 0) && (a3 == 0) && (a4 == 1 ) )
		{
			//"1001"
			eumRet=SDVIDEO_SCALE_TYPE_CUT;
		}
		else if( (a1 == 1) && (a2 == 1) && (a3 == 1) && (a4 == 1 ) )
		{
			//"1111"
			eumRet=SDVIDEO_SCALE_TYPE_CUT;
		}
		else if( (a1 == 0) && (a2 == 0) && (a3 == 0) && (a4 == 0 ) )
		{
			//"0000"
			eumRet=SDVIDEO_SCALE_TYPE_ZOOM;
		}
	}
	else
	{
		if( (a1 == 1) && (a2 == 0) && (a3 == 0) && (a4 == 1 ) )
		{
			//"1001"
			eumRet=SDVIDEO_SCALE_TYPE_BOX;
		}
		else if( (a1 == 1) && (a2 == 0) && (a3 == 1) && (a4 == 0 ) )
		{
			//"1010"
			eumRet=SDVIDEO_SCALE_TYPE_CUT;
		}
		else if( (a1 == 0) && (a2 == 0) && (a3 == 0) && (a4 == 0 ) )
		{
			//"0000"
			eumRet=SDVIDEO_SCALE_TYPE_ZOOM;
		}
	}
	return eumRet;
}

//根据上下变换类型等得到AFD信息
inline void SDGetAFDFromScaleType(SDVIDEO_SCALE_TYPE eumScaleType,BOOL bDown,int& ar , int& a1 , int& a2 , int& a3 , int& a4 )
{
	ar=a1=a2=a3=a4=0;

	if(bDown)
	{
		switch(eumScaleType)
		{
		case SDVIDEO_SCALE_TYPE_BOX:
			{
				//"1010"
				a1 = 1;
				a2 = 0;
				a3 = 1;
				a4 = 0;
			}
			break;
		case SDVIDEO_SCALE_TYPE_CUT:
			{
				//"1001"
				a1 = 1;
				a2 = 0;
				a3 = 0;
				a4 = 1;
			}
			break;
		}
		ar = 1;
	}
	else
	{
		switch(eumScaleType)
		{
		case SDVIDEO_SCALE_TYPE_BOX:
			{
				//"1001"
				a1 = 1;
				a2 = 0;
				a3 = 0;
				a4 = 1;
			}
			break;
		case SDVIDEO_SCALE_TYPE_CUT:
			{
				//"1010"
				a1 = 1;
				a2 = 0;
				a3 = 1;
				a4 = 0;
			}
			break;
		}
		ar = 0;
	}
}

inline	BOOL	IsVideoStandardHD( SD_VIDEO_STANDARD enumVideoStandard )
{
	switch(enumVideoStandard)
	{
	case SDVIDEOSTANDARD_PAL		:
	case SDVIDEOSTANDARD_NTSC2997	:
	case SDVIDEOSTANDARD_NTSC30		:
		return FALSE;
	default:
		return TRUE;
	}

	return TRUE;
};

//=======================================================================================
//硬件板卡类型
enum SDHW_VIDEOMAINCARD_TYPE		//硬件Video卡类型
{
	SDHWVIDEOMAINCARDTYPE_UNKNOW			=	0,

	SDHWVIDEOMAINCARDTYPE_REDBRIDGE_3		=	1,
	SDHWVIDEOMAINCARDTYPE_SOFTWARE			=	2,
	SDHWVIDEOMAINCARDTYPE_REDBRIDGE2_HD		=	3,
};

enum SDHW_AUDIOMAINCARD_TYPE		//硬件Audio卡类型
{
	SDHWAUDIOMAINCARDTYPE_UNKNOW			=	0,
	SDHWAUDIOMAINCARDTYPE_REDBRIDGE_3		=	1,

	SDHWAUDIOMAINCARDTYPE_COMMON			=	2,
	SDHWAUDIOMAINCARDTYPE_DIGIGRAM			=	3,
	SDHWAUDIOMAINCARDTYPE_MERGING			=	4,
	SDHWAUDIOMAINCARDTYPE_ASIO				=	5,
	SDHWAUDIOMAINCARDTYPE_REDBRIDGE2_HD		=	6,
};

enum SD_VAFILETYPE							//视音频文件类型
{
	SD_VAFILETYPE_SEPERATE = 0x00000000,
	SD_VAFILETYPE_COMBINE = 0x00000001,
};
typedef DWORD SDVAFILETYPEFLAG;

struct SDVAPriority
{
	CdwordArray adwVideoClassPriority;		//视频制式分类优先级 SD_VIDEO_CLASS
	CdwordArray adwVideoStreamPriority;		//视频封装格式优先级 SD_STREAM_TYPE
	CdwordArray adwAudioStreamPriority;		//音频封装格式优先级 SD_STREAM_TYPE
	CdwordArray adwVideoTypePriority;		//视频编码类型优先级 SD_VIDEO_TYPE
	CdwordArray adwAudioTypePriority;		//音频编码类型优先级 SD_AUDIO_TYPE
	CdwordArray adwVideoFileTypePriority;	//视频文件类型优先级 SD_VAFILETYPE
	CdwordArray adwAudioFileTypePriority;	//音频文件类型优先级 SD_VAFILETYPE

	SDVAPriority()
	{

	};

	~SDVAPriority()
	{
		adwVideoClassPriority.RemoveAll();
		adwVideoStreamPriority.RemoveAll();
		adwAudioStreamPriority.RemoveAll();
		adwVideoTypePriority.RemoveAll();
		adwAudioTypePriority.RemoveAll();
		adwVideoFileTypePriority.RemoveAll();
		adwAudioFileTypePriority.RemoveAll();
	};

	SDVAPriority(SDVAPriority& other)
	{
		*this = other;
	};

	SDVAPriority& operator = (const SDVAPriority& other)
	{
		adwVideoClassPriority.Copy(other.adwVideoClassPriority);
		adwVideoStreamPriority.Copy(other.adwVideoStreamPriority);
		adwAudioStreamPriority.Copy(other.adwAudioStreamPriority);
		adwVideoTypePriority.Copy(other.adwVideoTypePriority);
		adwAudioTypePriority.Copy(other.adwAudioTypePriority);
		adwVideoFileTypePriority.Copy(other.adwVideoFileTypePriority);
		adwAudioFileTypePriority.Copy(other.adwAudioFileTypePriority);
		return *this;
	};
};


#ifdef _WIN64
#	define SD_GWL_WNDPROC		GWLP_WNDPROC
#	define SD_GWL_HINSTANCE	GWLP_HINSTANCE
#	define SD_GWL_HWNDPARENT	GWLP_HWNDPARENT
#	define SD_GWL_USERDATA		GWLP_USERDATA
#	define SD_GWL_ID			GWLP_ID
#else
#	define SD_GWL_WNDPROC		GWL_WNDPROC
#	define SD_GWL_HINSTANCE	GWL_HINSTANCE
#	define SD_GWL_HWNDPARENT	GWL_HWNDPARENT
#	define SD_GWL_USERDATA		GWL_USERDATA
#	define SD_GWL_ID			GWL_ID
#endif

#ifdef _WIN64
#	define SD_GCL_MENUNAME			GCLP_MENUNAME
#	define SD_GCL_HBRBACKGROUND	GCLP_HBRBACKGROUND
#	define SD_GCL_HCURSOR			GCLP_HCURSOR
#	define SD_GCL_HICON			GCLP_HICON
#	define SD_GCL_HMODULE			GCLP_HMODULE
#	define SD_GCL_WNDPROC			GCLP_WNDPROC
#	define SD_GCL_HICONSM			GCLP_HICONSM
#else
#	define SD_GCL_MENUNAME			GCL_MENUNAME
#	define SD_GCL_HBRBACKGROUND	GCL_HBRBACKGROUND
#	define SD_GCL_HCURSOR			GCL_HCURSOR
#	define SD_GCL_HICON			GCL_HICON
#	define SD_GCL_HMODULE			GCL_HMODULE
#	define SD_GCL_WNDPROC			GCL_WNDPROC
#	define SD_GCL_HICONSM			GCL_HICONSM
#endif


// MXF文件格式子类型
enum enumMXFStreamSubType
{
	STREAMTYPE_MXF_STD    = 0,   // 默认的MXF文件
	STREAMTYPE_MXF_XDCAM  = 1,   // XDCAM的MXF文件
	STREAMTYPE_MXF_K2     = 2,   // K2的MXF文件
};

//AIFF 音频文件格式子类型
enum enumAIFFStreamSubType
{
	STREAMTYPE_AIFF_AIFF = 0,
	STREAMTYPE_AIFF_AIFC = 1,
};

// TS文件格式子类型
enum enumTSStreamSubType
{
	STREAMTYPE_TS_STD  = 0, // 默认标准TS流文件(总码率固定)
	STREAMTYPE_TS_VBR  = 1, // 总码率可变的TS
};

// HLS格式子类型
enum enumHlsSubType
{
	STREAMTYPE_HLS_Record        = 0, // 默认记录方式,HLS记录所有片段文件      
	STREAMTYPE_HLS_SlidingWindow = 1, // 实时发布模式,HLS只记录当前播放窗的片段文件
};

// SAF文件格式子类型
enum enumSAFStreamSubType
{
	STREAMTYPE_SAF_BMC = 0,     // Seachange视频服务器的文件格式,分为一个MPEG2 PS流文件和一个VIX文件
	STREAMTYPE_SAF_BML_0_1 = 1, // Seachange存储的文件格式(版本0.1)
	STREAMTYPE_SAF_BML_1_0 = 2, // Seachange存储的文件格式(版本1.0)
};

// STREAMTYPE_OPENDML_AVI文件格式子类型
enum enumOPENDML_AVISubType
{
	STREAMTYPE_OPENDML_AVI_STD = 0,     // 标准OpenDml Avi(视频FOURCC为vids)
	STREAMTYPE_OPENDML_AVI_DVTYPE1 = 1, // DVType1 OpenDml Avi(视频FOURCC为iavs)
};

// STREAMTYPE_PS的子类型
enum enumPSSubType
{
	STREAMTYPE_PS_MPEG2 = 0,    // 13818-1系统层
	STREAMTYPE_PS_MPEG1 = 1,    // 11172-1系统层
};

// STREAMTYPE_OMNEON的子类型
enum enumOMNEONSubType
{
	STREAMTYPE_OMNEON_MOV = 0,    // MXF格式的Omneon文件
	STREAMTYPE_OMNEON_MXF = 1,    // MXf格式的Omneon文件
};

// STREAMTYPE_LXF的子类型
enum enumLXFSubType
{
	STREAMTYPE_LXF_V0 = 0,    // LXF格式的Version0文件
	STREAMTYPE_LXF_V1 = 1,    // LXf格式的Version1文件
};

// STREAMTYPE_ES的子类型
enum enumESSubType
{
	STREAMTYPE_ES_COMMON = 0,
	STREAMTYPE_ES_DIF = 1,
	STREAMTYPE_ES_LTC = 2,
};

// STREAMTYPE_MP4的子类型
enum enumMP4SubType
{
	STREAMTYPE_MP4_32BIT  = 0, // MP4格式,文件不能大于4GB
	STREAMTYPE_MP4_64BIT  = 1, // MP4格式扩展,文件可以大于4GB
	STREAMTYPE_MP4_EXCARD = 2, // 符合ExCard规范的Mp4文件,同时生成ppn文件
};

// STREAMTYPE_MSVFW_WAV的子类型(201407版本新增)
enum enumWAVEFileSubType
{
	STREAMTYPE_WAVE_32BIT  = 0, // WAVE基本格式(RIFF),文件不能大于4GB
	STREAMTYPE_WAVE_64BIT  = 1, // WAVE格式扩展(RF64),文件可以大于4GB(EBU Tech 3306-2009 MBWF / RF64: An Extended File Format for Audio))
};

////////////////////////////////////////////////////////////////////////////////////
// Mpeg4视频子类型
enum enumMpeg4VideoSubType
{
	VIDEOTYPE_MPEG4_ISOMPEG4     = 0,
	VIDEOTYPE_MPEG4_ISOMPEG4_ASP = 1,
	VIDEOTYPE_MPEG4_XVID         = 2,
	VIDEOTYPE_MPEG4_XVID_ASP     = 3,
	VIDEOTYPE_MPEG4_MSV3         = 4,
	VIDEOTYPE_MPEG4_MSV2         = 5,
	VIDEOTYPE_MPEG4_MSV1         = 6,
	VIDEOTYPE_MPEG4_DIVX         = 7
};

//  Lossless视频子类型 //20140603,为了更好地区分无损编码的内部颜色格式
enum enumLOSSLESSVideoSubType
{
	VIDEOTYPE_LOSSLESS_YUV_8BIT				= 0,
	VIDEOTYPE_LOSSLESS_YUV_10BIT			= 1,
	VIDEOTYPE_LOSSLESS_RGB_8BIT				= 2,
	VIDEOTYPE_LOSSLESS_RGB_10BIT			= 3,
	VIDEOTYPE_LOSSLESS_RGB_12BIT			= 4,
	VIDEOTYPE_LOSSLESS_RGB_16BIT			= 5,
	VIDEOTYPE_LOSSLESS_YUVA_8BIT			= 6,
	VIDEOTYPE_LOSSLESS_YUVA_10BIT			= 7,
	VIDEOTYPE_LOSSLESS_RGBA_8BIT			= 8,
	VIDEOTYPE_LOSSLESS_RGBA_10BIT			= 9,
	VIDEOTYPE_LOSSLESS_RGBA_12BIT			= 10,
	VIDEOTYPE_LOSSLESS_RGBA_16BIT			= 11,
};

// DPX 颜色空间子类型
enum enumDPXVideoSubType
{
	VIDEOTYPE_DPX_YUV_8BIT					= 0,
	VIDEOTYPE_DPX_YUV_10BIT					= 1,
	VIDEOTYPE_DPX_RGB_8BIT					= 2,
	VIDEOTYPE_DPX_RGB_10BIT					= 3,
	VIDEOTYPE_DPX_RGB_12BIT					= 4,
	VIDEOTYPE_DPX_RGB_16BIT					= 5,
	VIDEOTYPE_DPX_YUVA_8BIT					= 6,
	VIDEOTYPE_DPX_YUVA_10BIT				= 7,
	VIDEOTYPE_DPX_RGBA_8BIT					= 8,
	VIDEOTYPE_DPX_RGBA_10BIT				= 9,
	VIDEOTYPE_DPX_RGBA_12BIT				= 10,
	VIDEOTYPE_DPX_RGBA_16BIT				= 11,
};

// HEVC(H.265)视频子类型 //It should extend in the future.
enum enumHEVCVideoSubType
{
	VIDEOTYPE_HEVC_MAIN			= 0,
	VIDEOTYPE_HEVC_MAIN10		= 1,
	VIDEOTYPE_HEVC_MAIN_STILL	= 2,
};

// H264视频子类型 //It should extend in the future.
enum enumH264VideoSubType
{
	VIDEOTYPE_H264_BASELINE		= 0,
	VIDEOTYPE_H264_MAIN			= 1,
	VIDEOTYPE_H264_HIGH			= 2,
	VIDEOTYPE_X264_BASELINE		= 3,  // 与VIDEOTYPE_H264_BASELINE相同,FOURCC为"X264"
	VIDEOTYPE_X264_MAIN			= 4,  // 与VIDEOTYPE_H264_MAIN相同,FOURCC为"X264"
	VIDEOTYPE_X264_HIGH			= 5,  // 与VIDEOTYPE_H264_HIGH相同,FOURCC为"X264"
	VIDEOTYPE_H264_EXTENDED		= 6,  // 暂不使用
	VIDEOTYPE_H264_HIGH10		= 7,  // 420 8->10bit
	VIDEOTYPE_H264_HIGH422		= 8,  // 422 8->10bit
	VIDEOTYPE_H264_HIGH444		= 9,  // 444 8->16bit
};

//H263视频子类型
enum enumH263VideoSubType
{
	VIDEOTYPE_H263_SUBQCIF		= 0,	//128*96	recommend bitrate: 32kbps
	VIDEOTYPE_H263_QCIF			= 1,	//176*144	recommend bitrate: 64kbps
	VIDEOTYPE_H263_CIF			= 2,	//352*288	recommend bitrate: 256kbps
};


// Mpeg2视频子类型
enum enumMpeg2VideoSubType
{
	VIDEOTYPE_MPEG2_STD = 0,  // 标准 
	VIDEOTYPE_MPEG2_HQ  = 1,  // 高质量
	VIDEOTYPE_MPEG2_FUL	= 2,  // 全搜索
	VIDEOTYPE_MPEG2_TMP	= 3,  // 测试
	VIDEOTYPE_MPEG2_DN8 = 4,  // 8x8下采样
	VIDEOTYPE_MPEG2_NEW = 5,  // 8x8下采样优化
	VIDEOTYPE_MPEG2_NEW2 = 6,  // 8x8下采样优化2
};

// D10视频子类型
enum enumD10SubType
{
	VIDEOTYPE_D10_50M = 0,
	VIDEOTYPE_D10_40M = 1,
	VIDEOTYPE_D10_30M = 2,
};

// Winmedia视频子类型
enum enumWinMediaVideoSubType
{
	VIDEOTYPE_WM_V8  = 0,
	VIDEOTYPE_WM_V9  = 1,
	VIDEOTYPE_WM_V7  = 2,
	VIDEOTYPE_WM_VC1 = 3,
};

// Realmedia视频子类型
enum enumRealMediaMVideoSubType
{
	VIDEOTYPE_RM_V8  = 0,
	VIDEOTYPE_RM_V9  = 1,
	VIDEOTYPE_RM_V10 = 2		// added by liangyufan 081021
};

// DVCPROHD视频子类型
enum enumDVHDVideoSubType
{
	VIDEOTYPE_DVHD_1080_50I = 0,
	VIDEOTYPE_DVHD_1080_60I = 1,
	VIDEOTYPE_DVHD_720_50P  = 2,
	VIDEOTYPE_DVHD_720_60P  = 3,
};

// AVC_Intra_HD视频子类型
enum enumAVCINTRA_HDVideoSubType 
{
	VIDEOTYPE_AVCINTRA_C50_1080_50I    = 0,
	VIDEOTYPE_AVCINTRA_C50_1080_5994I  = 1,
	VIDEOTYPE_AVCINTRA_C50_1080_25P    = 2,
	VIDEOTYPE_AVCINTRA_C50_1080_2997P  = 3,
	VIDEOTYPE_AVCINTRA_C50_1080_2398P  = 4,  // C50_1080: 1440*1080 420 8bits
	VIDEOTYPE_AVCINTRA_C50_720_50P     = 5,
	VIDEOTYPE_AVCINTRA_C50_720_5994P   = 6,
	VIDEOTYPE_AVCINTRA_C50_720_25P     = 7,
	VIDEOTYPE_AVCINTRA_C50_720_2997P   = 8,
	VIDEOTYPE_AVCINTRA_C50_720_2398P   = 9,  // C50_720: 960*720 420 8bits

	VIDEOTYPE_AVCINTRA_C100_1080_50I   = 10,  
	VIDEOTYPE_AVCINTRA_C100_1080_5994I = 11,  
	VIDEOTYPE_AVCINTRA_C100_1080_25P   = 12,  
	VIDEOTYPE_AVCINTRA_C100_1080_2997P = 13,  
	VIDEOTYPE_AVCINTRA_C100_1080_2398P = 14, // C100_1080: 1920*1080 422 10bits
	VIDEOTYPE_AVCINTRA_C100_720_50P    = 15, 
	VIDEOTYPE_AVCINTRA_C100_720_5994P  = 16, 
	VIDEOTYPE_AVCINTRA_C100_720_25P    = 17,	
	VIDEOTYPE_AVCINTRA_C100_720_2997P  = 18, 
	VIDEOTYPE_AVCINTRA_C100_720_2398P  = 19, // C100_1080: 1280*720 422 10bits
		
	VIDEOTYPE_AVCINTRA_C200_1080_50I   = 30, 
	VIDEOTYPE_AVCINTRA_C200_1080_5994I = 31, 
	VIDEOTYPE_AVCINTRA_C200_1080_2997P = 32, 
	VIDEOTYPE_AVCINTRA_C200_1080_25P   = 33,
	VIDEOTYPE_AVCINTRA_C200_1080_2398P = 34,
	VIDEOTYPE_AVCINTRA_C200_1080_50P   = 35,
	VIDEOTYPE_AVCINTRA_C200_1080_5994P = 36, // C200_1080: 1920*1080 422 10bits
	
	VIDEOTYPE_AVCINTRA_C200_720_5994P  = 50, 
	VIDEOTYPE_AVCINTRA_C200_720_50P	   = 51,
	VIDEOTYPE_AVCINTRA_C200_720_2398P  = 52,
	VIDEOTYPE_AVCINTRA_C200_720_25P	   = 53,	
	VIDEOTYPE_AVCINTRA_C200_720_2997P  = 54,
	VIDEOTYPE_AVCINTRA_C200_720_100P   = 55,
	VIDEOTYPE_AVCINTRA_C200_720_11988P = 56, // C200_720: 1280*720 422 10bits

	// QFHD,4k/4:2:2 Class100
	VIDEOTYPE_AVCINTRA_C100_QFHD_2997P  = 57,
	VIDEOTYPE_AVCINTRA_C100_QFHD_2398P  = 58,
	VIDEOTYPE_AVCINTRA_C100_QFHD_25P    = 59,
	VIDEOTYPE_AVCINTRA_C100_QFHD_5994P  = 61,
	VIDEOTYPE_AVCINTRA_C100_QFHD_50P    = 62, 
	VIDEOTYPE_AVCINTRA_C100_4K_5994P    = 63,
	VIDEOTYPE_AVCINTRA_C100_4K_50P      = 64,
	VIDEOTYPE_AVCINTRA_C100_4K_2398P    = 67,
	VIDEOTYPE_AVCINTRA_C100_4K_2997P    = 68,
	VIDEOTYPE_AVCINTRA_C100_4K_25P      = 69,
};// AVC_Intra_HD视频子类型
//AVC-Ultra LongGOP 视频子类型
enum enumAVCUltra_LONGGop_HDVideoSubType 
{
	//Class G50
	VIDEOTYPE_AVCULTRA_LONGGOP_422_G50_1080_5994I  = 0x100,
	VIDEOTYPE_AVCULTRA_LONGGOP_422_G50_1080_50I    = 0x101, 
	VIDEOTYPE_AVCULTRA_LONGGOP_422_G50_1080_2997P  = 0x109,
	VIDEOTYPE_AVCULTRA_LONGGOP_422_G50_1080_2398P  = 0x10A,
	VIDEOTYPE_AVCULTRA_LONGGOP_422_G50_1080_25P    = 0x10D,
	VIDEOTYPE_AVCULTRA_LONGGOP_422_G50_720_5994P   = 0x110,
	VIDEOTYPE_AVCULTRA_LONGGOP_422_G50_720_50P     = 0x114,

	//Class G25			 
	VIDEOTYPE_AVCULTRA_LONGGOP_422_G25_1080_5994I  = 0x140,
	VIDEOTYPE_AVCULTRA_LONGGOP_422_G25_1080_50I    = 0x141, 
	VIDEOTYPE_AVCULTRA_LONGGOP_422_G25_1080_5994P  = 0x148,
	VIDEOTYPE_AVCULTRA_LONGGOP_422_G25_1080_2997P  = 0x149,
	VIDEOTYPE_AVCULTRA_LONGGOP_422_G25_1080_2398P  = 0x14A,
	VIDEOTYPE_AVCULTRA_LONGGOP_422_G25_1080_50P    = 0x14C,
	VIDEOTYPE_AVCULTRA_LONGGOP_422_G25_1080_25P    = 0x14D,
	VIDEOTYPE_AVCULTRA_LONGGOP_422_G25_720_5994P   = 0x150,
	VIDEOTYPE_AVCULTRA_LONGGOP_422_G25_720_50P     = 0x154,

	//Class G12	 
	VIDEOTYPE_AVCULTRA_LONGGOP_420_G12_1080_5994I  = 0x180,
	VIDEOTYPE_AVCULTRA_LONGGOP_420_G12_1080_50I    = 0x187,
	VIDEOTYPE_AVCULTRA_LONGGOP_420_G12_1080_5994P  = 0x188,
	VIDEOTYPE_AVCULTRA_LONGGOP_420_G12_1080_2997P  = 0x189,//文档有，sdk无
	VIDEOTYPE_AVCULTRA_LONGGOP_420_G12_1080_2398P  = 0x18A,//文档有，sdk无
	VIDEOTYPE_AVCULTRA_LONGGOP_420_G12_1080_50P    = 0x18C,
	VIDEOTYPE_AVCULTRA_LONGGOP_420_G12_1080_25P    = 0x18D,//文档有，sdk无
	VIDEOTYPE_AVCULTRA_LONGGOP_420_G12_720_5994P   = 0x190,
	VIDEOTYPE_AVCULTRA_LONGGOP_420_G12_720_50P     = 0x194,

	//Class G6				
	VIDEOTYPE_AVCULTRA_LONGGOP_420_G6_1080_5994I   = 0x1C0,
	VIDEOTYPE_AVCULTRA_LONGGOP_420_G6_1080_50I     = 0x1C1,
	VIDEOTYPE_AVCULTRA_LONGGOP_420_G6_1080_5994P   = 0x1C8,
	VIDEOTYPE_AVCULTRA_LONGGOP_420_G6_1080_2997P   = 0x1C9,//文档有，sdk无
	VIDEOTYPE_AVCULTRA_LONGGOP_420_G6_1080_2398P   = 0x1CA,//文档有，sdk无
	VIDEOTYPE_AVCULTRA_LONGGOP_420_G6_1080_50P     = 0x1CC,
	VIDEOTYPE_AVCULTRA_LONGGOP_420_G6_1080_25P     = 0x1CD,//文档有，sdk无
	VIDEOTYPE_AVCULTRA_LONGGOP_420_G6_720_5994P    = 0x1D0,
	VIDEOTYPE_AVCULTRA_LONGGOP_420_G6_720_50P      = 0x1D4,
};


//Sony XAVC视频子类型
//Sony XAVC HD Profile Subtype
//High422 Profile-->MXF
//Main/High Progile-->MP4
enum enumXAVC_HDVideoSubtype
{
	VIDOETYPE_XAVC35_1280_720_H422P_L41  = 0,
	VIDOETYPE_XAVC50_1280_720_H422P_L41  = 1,
	VIDOETYPE_XAVC_1920_1080_H422P_L41   = 2,
	VIDOETYPE_XAVC_1920_1080_H422P_L42   = 3,
	VIDOETYPE_XAVC25_1920_1080_H422P_L41 = 4, 
	VIDOETYPE_XAVC35_1920_1080_H422P_L41 = 5,
	VIDOETYPE_XAVC35_1920_1080_H422P_L42 = 6,
	VIDOETYPE_XAVC50_1920_1080_H422P_L41 = 7,
	VIDOETYPE_XAVC50_1920_1080_H422P_L42 = 8,
};
//Sony XAVC 4K Profile Subtype
//High Profile -->MXF/MP4
enum enumXAVC_4KVideoSubtype
{
	VIDOETYPE_XAVC_3840_2160_HP_L51 = 0,
	VIDOETYPE_XAVC_3840_2160_HP_L52 = 1,
};
//Sony XAVC HD Intra Profile Subtype
//CBG-->MXF
//VBR-->MP4
enum enumXAVC_HDIntraVideoSubtype
{
	VIDOETYPE_XAVC100CBG_1280_720_H422IP_L41  = 0,
	VIDOETYPE_XAVC50CBG_1440_1080_H10IP_L4    = 1,
	VIDOETYPE_XAVC100CBG_1920_1080_H422IP_L41 = 2,
	VIDOETYPE_XAVC100CBG_1920_1080_H422IP_L42 = 3,
	VIDOETYPE_XAVC200CBG_1920_1080_H422IP_L41 = 4,
	VIDOETYPE_XAVC200CBG_1920_1080_H422IP_L5  = 5,
};
//Sony XAVC 4K Intra Profile Subtype
//CBG/VBR-->MXF/MP4
enum enumXAVC_4KIntraVideoSubtype
{
	VIDOETYPE_XAVCCBG_2048_1080_H422IP_L42    = 0,
	VIDOETYPE_XAVCCBG_2048_1080_H422IP_L5     = 1,
	VIDOETYPE_XAVC_2048_1080_H422IP_L42       = 2,
	VIDOETYPE_XAVC_2048_1080_H422IP_L5        = 3, 
	VIDOETYPE_XAVCCBG_3840_2160_H422IP_L51    = 4,
	VIDOETYPE_XAVCCBG_3840_2160_H422IP_L52    = 5,
	VIDOETYPE_XAVC_3840_2160_H422IP_L51       = 6,
	VIDOETYPE_XAVC_3840_2160_H422IP_L52       = 7,
	VIDOETYPE_XAVC480CBG_3840_2160_H422IP_L51 = 8,
	VIDOETYPE_XAVC480CBG_3840_2160_H422IP_L52 = 9,
	VIDOETYPE_XAVC480_3840_2160_H422IP_L51    = 10,
	VIDOETYPE_XAVC480_3840_2160_H422IP_L52    = 11,
	VIDOETYPE_XAVCCBG_4096_2160_H422IP_L51    = 12,
	VIDOETYPE_XAVCCBG_4096_2160_H422IP_L52    = 13,
	VIDOETYPE_XAVC_4096_2160_H422IP_L51       = 14,
	VIDOETYPE_XAVC_4096_2160_H422IP_L52       = 15,
	VIDOETYPE_XAVC480CBG_4096_2160_H422IP_L51 = 16,
	VIDOETYPE_XAVC480CBG_4096_2160_H422IP_L52 = 17,
	VIDOETYPE_XAVC480_4096_2160_H422IP_L51    = 18,
	VIDOETYPE_XAVC480_4096_2160_H422IP_L52    = 19,
};
//Sony XAVC HD444 Intra Profile Subtype
enum enumXAVC_HD444IntraVideoSubtype
{

};
//Sony XAVC 4K444 Intra Profile Subtype
enum enumXAVC_4K444IntraVideoSubtype
{

};
//Sony SStP (Simple Studio Profile, Level xx)
enum enumMPEG4_SStPVideoSubtype
{
	VIDOETYPE_MPEG4SStP_Lite_1280_720_422     = 0,
	VIDOETYPE_MPEG4SStP_Lite_1920_1080_422	  = 1,
	VIDOETYPE_MPEG4SStP_SQ_1280_720_422		  = 2,
	VIDOETYPE_MPEG4SStP_SQ_1920_1080_422	  = 3,
	VIDOETYPE_MPEG4SStP_SQ_1920_1080_444RGB	  = 4,
	VIDOETYPE_MPEG4SStP_HQ_1920_1080_444RGB	  = 5,
	VIDOETYPE_MPEG4SStP_HQ_1920_1080_444RGB12 = 6,
	VIDOETYPE_MPEG4SStP_SQ_2048_1080_444RGB	  = 7,
	VIDOETYPE_MPEG4SStP_SQ_2048_1080_444XYZ	  = 8,
	VIDOETYPE_MPEG4SStP_HQ_2048_1080_444RGB	  = 9,
	VIDOETYPE_MPEG4SStP_HQ_2048_1080_444XYZ	  = 10,
	VIDOETYPE_MPEG4SStP_HQ_2048_1556_444RGB	  = 11,
};

//SonyRaw 
enum enumSonyRaw_VideoSubtype
{
	//xml中枚举定义
	VIDEOTYPE_SONYRAW_F65RAWLite_4096_2160    = 0,
	VIDEOTYPE_SONYRAW_F65RAWSQ_4096_2160	  = 1,
	VIDEOTYPE_SONYRAW_F65RAWHQ_4096_2160	  = 2,
	VIDEOTYPE_SONYRAW_F65RAWHFRLite_4096_2160 = 3,
	VIDEOTYPE_SONYRAW_F65RAWHFRSQ_4096_2160   = 4,
	VIDEOTYPE_SONYRAW_F65RAWHFRHQ_4096_2160   = 5,
	VIDEOTYPE_SONYRAW_F55RAWLite_2048_1080	  = 6,
	VIDEOTYPE_SONYRAW_F55RAWLite_4096_2160	  = 7,
	VIDEOTYPE_SONYRAW_F55RAWSQ_2048_1080	  = 8,
	VIDEOTYPE_SONYRAW_F55RAWSQ_4096_2160	  = 9,
	VIDEOTYPE_SONYRAW_F55RAWHQ_2048_1080	  = 10,
	VIDEOTYPE_SONYRAW_F55RAWHQ_4096_2160	  = 11,
};

// DNxHD视频子类型
enum enumDNxHDVideoSubType
{
	VIDEOTYPE_DNxHD_1080_50I_185_8bit      = 0,  // 1920*1080 50I
	VIDEOTYPE_DNxHD_1080_50I_120_8bit      = 1,
	VIDEOTYPE_DNxHD_1080_50I_185_10bit     = 2,
	VIDEOTYPE_DNxHD_TR_1080_50I_120_8bit   = 3,
	VIDEOTYPE_DNxHD_1080_5994I_220_8bit    = 4,  // 1920*1080 5994I
	VIDEOTYPE_DNxHD_1080_5994I_145_8bit    = 5,
	VIDEOTYPE_DNxHD_1080_5994I_220_10bit   = 6,
	VIDEOTYPE_DNxHD_TR_1080_5994I_145_8bit = 7,
	VIDEOTYPE_DNxHD_1080_25P_185_8bit      = 8,  // 1920*1080 25P
	VIDEOTYPE_DNxHD_1080_25P_120_8bit      = 9,
	VIDEOTYPE_DNxHD_1080_25P_36_8bit       = 10,
	VIDEOTYPE_DNxHD_1080_25P_185_10bit     = 11,
	VIDEOTYPE_DNxHD_1080_2397P_175_8bit    = 12, // 1920*1080 2397P
	VIDEOTYPE_DNxHD_1080_2397P_115_8bit    = 13,
	VIDEOTYPE_DNxHD_1080_2397P_36_8bit     = 14,
	VIDEOTYPE_DNxHD_1080_2397P_175_10bit   = 15,
	VIDEOTYPE_DNxHD_1080_24P_175_8bit      = 16, // 1920*1080 24P
	VIDEOTYPE_DNxHD_1080_24P_115_8bit      = 17,
	VIDEOTYPE_DNxHD_1080_24P_36_8bit       = 18,
	VIDEOTYPE_DNxHD_1080_24P_175_10bit     = 19,
	VIDEOTYPE_DNxHD_720_5994P_220_8bit     = 20, // 1280*720 5994P
	VIDEOTYPE_DNxHD_720_5994P_145_8bit     = 21,
	VIDEOTYPE_DNxHD_720_5994P_220_10bit    = 22,
	VIDEOTYPE_DNxHD_720_2397P_90_8bit      = 23, // 1280*720 2397P
	VIDEOTYPE_DNxHD_720_2397P_60_8bit      = 24,
	VIDEOTYPE_DNxHD_720_2397P_90_10bit     = 25,
	VIDEOTYPE_DNxHD_720_2997P_110_8bit     = 26, // 1280*720 2997P 
	VIDEOTYPE_DNxHD_720_2997P_75_8bit      = 27,
	VIDEOTYPE_DNxHD_720_2997P_110_10bit    = 28,
	VIDEOTYPE_DNxHD_720_25P_60_8bit        = 29, // 1280*720 25P
	VIDEOTYPE_DNxHD_720_50P_185_8bit       = 30, // 1280*720 50P
	VIDEOTYPE_DNxHD_720_50P_120_8bit       = 31,
	VIDEOTYPE_DNxHD_720_50P_185_10bit      = 32,
	VIDEOTYPE_DNxHD_1080_2997P_440_10bit   = 33, // dnx440
	VIDEOTYPE_DNxHD_1080_25P_370_10bit     = 34, 
	VIDEOTYPE_DNxHD_1080_2397P_360_10bit   = 35, 
	VIDEOTYPE_DNxHD_1080_24P_360_10bit     = 36, 
};// DNxHD视频子类型

enum enumHDVVideoSubType
{
	VIDEOTYPE_HDV_HD2_1080i50 = 0,       // HD2 1080i/50
	VIDEOTYPE_HDV_HD2_1080i60 = 1,       // HD2 1080i/60

	VIDEOTYPE_HDV_HD1_720p25  = 2,       // HD1 720p/25
	VIDEOTYPE_HDV_HD1_720p30  = 3,       // HD1 720p/30
	VIDEOTYPE_HDV_HD1_720p50  = 4,       // HD1 720p/50
	VIDEOTYPE_HDV_HD1_720p60  = 5,       // HD1 720p/60
};

// QuickTime视频子类型
enum enumQuciTimeVideoSubType
{
	VIDEOTYPE_QT_MPEG4Visual			= 'mp4v',
	VIDEOTYPE_QT_Raw					= 'raw ', 
	VIDEOTYPE_QT_Cinepak				= 'cvid',
	VIDEOTYPE_QT_Graphics				= 'smc ',
	VIDEOTYPE_QT_Animation				= 'rle ',
	VIDEOTYPE_QT_Video					= 'rpza',
	VIDEOTYPE_QT_ComponentVideo			= 'yuv2',
	VIDEOTYPE_QT_JPEG					= 'jpeg',
	VIDEOTYPE_QT_MotionJPEGA			= 'mjpa',
	VIDEOTYPE_QT_MotionJPEGB			= 'mjpb',
	VIDEOTYPE_QT_SGI					= '.SGI',
	VIDEOTYPE_QT_PlanarRGB				= '8BPS',
	VIDEOTYPE_QT_MacPaint				= 'PNTG',
	VIDEOTYPE_QT_GIF					= 'gif ',
	VIDEOTYPE_QT_PhotoCD				= 'kpcd',
	VIDEOTYPE_QT_QuickDrawGX			= 'qdgx',
	VIDEOTYPE_QT_AVRJPEG				= 'avr ',
	VIDEOTYPE_QT_OpenDMLJPEG			= 'dmb1',
	VIDEOTYPE_QT_BMP					= 'WRLE',
	VIDEOTYPE_QT_WindowsRaw				= 'WRAW',
	VIDEOTYPE_QT_Vector					= 'path',
	VIDEOTYPE_QT_QuickDraw				= 'qdrw',
	VIDEOTYPE_QT_WaterRipple			= 'ripl',
	VIDEOTYPE_QT_Fire					= 'fire',
	VIDEOTYPE_QT_Cloud					= 'clou',
	VIDEOTYPE_QT_H261					= 'h261',
	VIDEOTYPE_QT_H263					= 'h263',
	VIDEOTYPE_QT_H264					= 'avc1',
	VIDEOTYPE_QT_JPEG2000				= 'mjp2',
	VIDEOTYPE_QT_DVCNTSC				= 'dvc ',
	VIDEOTYPE_QT_DVCPAL					= 'dvcp',
	VIDEOTYPE_QT_DVCProPAL				= 'dvpp',
	VIDEOTYPE_QT_DVCPro50PAL		    = 'dv5p',
	VIDEOTYPE_QT_DVCPro50NTSC			= 'dv5n',
	VIDEOTYPE_QT_DVCPro100PAL           = 'dv1p',
	VIDEOTYPE_QT_DVCPro100NTSC          = 'dv1n',
	VIDEOTYPE_QT_DVCProHD720P           = 'dvhp',
	VIDEOTYPE_QT_DVCProHD1080i60        = 'dvh6',
	VIDEOTYPE_QT_DVCProHD1080i50        = 'dvh5',
	VIDEOTYPE_QT_Base                   = 'base',
	VIDEOTYPE_QT_FLC                    = 'flic',
	VIDEOTYPE_QT_Targa                  = 'tga ',
	VIDEOTYPE_QT_PNG                    = 'png ',
	VIDEOTYPE_QT_TIFF                   = 'tiff',
	VIDEOTYPE_QT_ComponentVideoSigned   = 'yuvu',
	VIDEOTYPE_QT_ComponentVideoUnsigned = 'yuvs',
	VIDEOTYPE_QT_CMYK                   = 'cmyk',
	VIDEOTYPE_QT_MicrosoftVideo1        = 'msvc',
	VIDEOTYPE_QT_Sorenson               = 'SVQ1',
	VIDEOTYPE_QT_Sorenson3              = 'SVQ3',
	VIDEOTYPE_QT_Indeo4                 = 'IV41',
	VIDEOTYPE_QT_64ARGB                 = 'b64a',
	VIDEOTYPE_QT_48RGB                  = 'b48r',
	VIDEOTYPE_QT_32AlphaGray            = 'b32a',
	VIDEOTYPE_QT_16Gray                 = 'b16g',
	VIDEOTYPE_QT_MpegYUV420             = 'myuv',
	VIDEOTYPE_QT_YUV420                 = 'y420',
	VIDEOTYPE_QT_SorensonYUV9           = 'syv9',
	VIDEOTYPE_QT_422YpCbCr8             = '2vuy',
	VIDEOTYPE_QT_444YpCbCr8             = 'v308',
	VIDEOTYPE_QT_4444YpCbCrA8           = 'v408',
	VIDEOTYPE_QT_422YpCbCr16            = 'v216',
	VIDEOTYPE_QT_422YpCbCr10            = 'v210',
	VIDEOTYPE_QT_444YpCbCr10            = 'v410',
	VIDEOTYPE_QT_4444YpCbCrA8R          = 'r408',
	/**********************************************************/
	// Mpeg2 video 
	VIDEOTYPE_QT_Mpeg                   = 'mpeg', // MPEG 
	VIDEOTYPE_QT_AVID_DNX               = 'AVdn', // AVID DNXHD
	VIDEOTYPE_QT_AVID_IMXP              = 'AVmp', // AVID IMX PAL
	VIDEOTYPE_QT_AVID_IMXN              = 'AVmn', // AVID IMX NTSC
	VIDEOTYPE_QT_AVID_DV				= 'AVdv', // AVID DV 
	VIDEOTYPE_QT_IMX50P                 = 'mx5p', // MPEG2 IMX PAL 625/50 50mb/s produced by FCP 
	VIDEOTYPE_QT_IMX50N                 = 'mx5n', // MPEG2 IMX NTSC 525/60 50mb/s produced by FCP 
	VIDEOTYPE_QT_IMX40P                 = 'mx4p', // MPEG2 IMX PAL 625/50 40mb/s produced by FCP 
	VIDEOTYPE_QT_IMX40N                 = 'mx4n', // MPEG2 IMX NTSC 525/60 40mb/s produced by FCP 
	VIDEOTYPE_QT_IMX30P                 = 'mx3p', // MPEG2 IMX PAL 625/50 30mb/s produced by FCP 
	VIDEOTYPE_QT_IMX30N                 = 'mx3n', // MPEG2 IMX NTSC 525/60 30mb/s produced by FCP 
	VIDEOTYPE_QT_XDCAMEX_720P30         = 'xdv1', // XDCAM EX 720p30 VBR
	VIDEOTYPE_QT_XDCAMHD_1080I60        = 'xdv2', // XDCAM HD 1080i60 VBR 
	VIDEOTYPE_QT_XDCAMHD_1080I50        = 'xdv3', // XDCAM HD 1080i50 VBR 
	VIDEOTYPE_QT_XDCAMEX_720P24         = 'xdv4', // XDCAM EX 720p24 VBR
	VIDEOTYPE_QT_XDCAMEX_720P25         = 'xdv5', // XDCAM EX 720p25 VBR
	VIDEOTYPE_QT_XDCAMHD_1080P24        = 'xdv6', // XDCAM HD 1080p24 VBR 
	VIDEOTYPE_QT_XDCAMHD_1080P25        = 'xdv7', // XDCAM HD 1080p25 VBR
	VIDEOTYPE_QT_XDCAMHD_1080P30        = 'xdv8', // XDCAM HD 1080p30 VBR
	VIDEOTYPE_QT_XDCAMEX_720P60         = 'xdv9', // XDCAM EX 720p60 VBR 
	VIDEOTYPE_QT_XDCAMEX_720P50         = 'xdva', // XDCAM EX 720p50 VBR 
	VIDEOTYPE_QT_XDCAMEX_1080I60        = 'xdvb', // XDCAM EX 1080i60 VBR 
	VIDEOTYPE_QT_XDCAMEX_1080I50        = 'xdvc', // XDCAM EX 1080i50 VBR
	VIDEOTYPE_QT_XDCAMEX_1080P24        = 'xdvd', // XDCAM EX 1080p24 VBR
	VIDEOTYPE_QT_XDCAMEX_1080P25        = 'xdve', // XDCAM EX 1080p25 VBR 
	VIDEOTYPE_QT_XDCAMEX_1080P30        = 'xdvf', // XDCAM EX 1080p30 VBR
	VIDEOTYPE_QT_XDCAM422HD_720P60      = 'xd59', // XDCAM HD422 720p60 CBR
	VIDEOTYPE_QT_XDCAM422HD_720P50      = 'xd5a', // XDCAM HD422 720p50 CBR 
	VIDEOTYPE_QT_XDCAM422HD_1080I60     = 'xd5b', // XDCAM HD422 1080i60 CBR
	VIDEOTYPE_QT_XDCAM422HD_1080I50     = 'xd5c', // XDCAM HD422 1080i50 CBR
	VIDEOTYPE_QT_XDCAM422HD_1080P24     = 'xd5d', // XDCAM HD422 1080p24 CBR
	VIDEOTYPE_QT_XDCAM422HD_1080P25     = 'xd5e', // XDCAM HD422 1080p25 CBR 
	VIDEOTYPE_QT_XDCAM422HD_1080P30     = 'xd5f', // XDCAM HD422 1080p30 CBR 
	VIDEOTYPE_QT_HDV1					= 'hdv1', // MPEG2 HDV 720p30
	VIDEOTYPE_QT_HDV2					= 'hdv2', // MPEG2 HDV 1080i60
	VIDEOTYPE_QT_HDV3					= 'hdv3', // MPEG2 HDV 1080i50
	VIDEOTYPE_QT_HDV5					= 'hdv5', // MPEG2 HDV 720p25
	VIDEOTYPE_QT_HDV6					= 'hdv6', // MPEG2 HDV 1080p24
	VIDEOTYPE_QT_HDV7					= 'hdv7', // MPEG2 HDV 1080p25
	VIDEOTYPE_QT_HDV8					= 'hdv8', // MPEG2 HDV 1080p30 
	// Mpeg2 video 
	/**********************************************************/
	VIDEOTYPE_QT_VC1					= 'vc-1', // SMPTE RP 2025
	VIDEOTYPE_QT_ProRes422_Proxy		= 'apco', // Apple Prores 422(Proxy)
	VIDEOTYPE_QT_ProRes422_LT			= 'apcs', // Apple Prores 422(LT)
	VIDEOTYPE_QT_ProRes422 				= 'apcn', // Apple Prores 422(Standard)
	VIDEOTYPE_QT_ProRes422_HQ			= 'apch', // Apple Prores 422(HQ)
	VIDEOTYPE_QT_ProRes444 				= 'ap4h', // Apple Prores 444
};

//swf-flv视频子类型
enum enumSwfFlvVideoSubType
{
	VIDEOTYPE_SORENSON_H263 = 0,
	VIDEOTYPE_AVC_BASE     	= 1,
	VIDEOTYPE_AVC_MAIN     	= 2,
	VIDEOTYPE_AVC_HIGH     	= 3,
	VIDEOTYPE_VP6			= 4,
	VIDEOTYPE_VP6A			= 5,
	VIDEOTYPE_SCREENVIDEO	= 6,
	VIDEOTYPE_SCREEN2VIDEO	= 7, 
};

enum enumProRes422VideoSubType
{
	VIDEOTYPE_ProRes422_Proxy = 0, // apco
	VIDEOTYPE_ProRes422_LT	  = 1, // apcs
	VIDEOTYPE_ProRes422 	  = 2, // apcn
	VIDEOTYPE_ProRes422_HQ	  = 3, // apch
};

/////////////////////////////////////////////////////////////////////////////////////
// Mpeg layer1音频子类型(AUDIOTYPE_MP1)
enum enumMpegLayer1SubType
{
	AUDIOTYPE_MP1_MPEG1 = 0,
	AUDIOTYPE_MP1_MPEG2 = 1,
};

// Mpeg layer2音频子类型(AUDIOTYPE_MP2)
enum enumMpegLayer2SubType
{
	AUDIOTYPE_MP2_MPEG1 = 0,
	AUDIOTYPE_MP2_MPEG2 = 1,
};

// Mpeg layer3音频子类型(AUDIOTYPE_MP3)
enum enumMpegLayer3SubType
{
	AUDIOTYPE_MP3_MPEG1  =  0,
	AUDIOTYPE_MP3_MPEG2  =  1,
	AUDIOTYPE_MP3_MPEG25 =  2,
};

enum enumDTSSubType
{
	AUDIOTYPE_DTS2 = 0,		//1024
	AUDIOTYPE_DTS1 = 1,		//512
	AUDIOTYPE_DTS0 = 2,		//256
	AUDIOTYPE_DTS3 = 3,		//2048
};

// AAC音频子类型(AUDIOTYPE_AAC)
enum enumAACSubType
{
	AUDIOTYPE_MPEG4_AAC_LC     = 0,
	AUDIOTYPE_MPEG4_AAC_MAIN   = 1,
	AUDIOTYPE_MPEG4_AAC_LTP    = 2,
	AUDIOTYPE_MPEG4_AAC_SSR    = 3,
	AUDIOTYPE_MPEG2_AAC_LC     = 4,
	AUDIOTYPE_MPEG2_AAC_MAIN   = 5,
	AUDIOTYPE_MPEG2_AAC_SSR    = 6,
	AUDIOTYPE_MPEG4_AAC_SBR    = 7,  // HE AAC v1
	AUDIOTYPE_MPEG4_AAC_SBR_PS = 8,  // HE AAC v2
};

// WAV_PCM音频子类型(AUDIOTYPE_WAVE_PCM)
enum enumWAVESubType
{
	AUDIOTYPE_WAVE_PCM		  = 0,
	AUDIOTYPE_WAVE_IEEE_FLOAT = 1, //  IEEE754: range (+1, -1], 32-bit/64-bit format.
};

// G711音频子类型(AUDIOTYPE_G711)
enum enumG711SubType
{
	AUDIOTYPE_G711_ALaw = 0,
	AUDIOTYPE_G711_ULaw = 1,
};

// AMR-NB 音频mode		add by lzy 2006-08-08
enum enumAMRNBMode
{
	AUDIOMODE_AMRNB_475 = 0,
	AUDIOMODE_AMRNB_515 = 1,
	AUDIOMODE_AMRNB_590 = 2,
	AUDIOMODE_AMRNB_670 = 3,
	AUDIOMODE_AMRNB_740 = 4,
	AUDIOMODE_AMRNB_795 = 5,
	AUDIOMODE_AMRNB_102 = 6,
	AUDIOMODE_AMRNB_122 = 7,
	AUDIOMODE_AMRNB_SID = 8,
};

//AMR-WB 音频mode
enum enumAMRWBMode
{
	AUDIOMODE_AMRWB_660  = 0,
	AUDIOMODE_AMRWB_885  = 1,
	AUDIOMODE_AMRWB_1265 = 2,
	AUDIOMODE_AMRWB_1425 = 3,
	AUDIOMODE_AMRWB_1585 = 4,
	AUDIOMODE_AMRWB_1825 = 5,
	AUDIOMODE_AMRWB_1985 = 6,
	AUDIOMODE_AMRWB_2305 = 7,
	AUDIOMODE_AMRWB_2385 = 8,
	AUDIOMODE_AMRWB_SID  = 9,
};

// QuickTime音频子类型(AUDIOTYPE_QUICKTIME_MOV)
enum enumQuciTimeAudioSubType
{
	AUDIOTYPE_QT_MPEG4Audio			= 'mp4a', // MPEG-4 AAC 
	AUDIOTYPE_QT_NotCompressed		= 'NONE', // uncompressed
	AUDIOTYPE_QT_8BitOffsetBinary	= 'raw ', // 8 bits unsigned 
	AUDIOTYPE_QT_16BitBigEndian		= 'twos',
	AUDIOTYPE_QT_16BitLittleEndian	= 'sowt',
	AUDIOTYPE_QT_Float32			= 'fl32',
	AUDIOTYPE_QT_Float64			= 'fl64',
	AUDIOTYPE_QT_24Bit				= 'in24',
	AUDIOTYPE_QT_32Bit				= 'in32',	
	AUDIOTYPE_QT_MACE3				= 'MAC3', // Macintosh Audio Compression and Expansion 3:1 
	AUDIOTYPE_QT_MACE6				= 'MAC6', // Macintosh Audio Compression and Expansion 6:1
	AUDIOTYPE_QT_CDXA4				= 'cdx4',
	AUDIOTYPE_QT_CDXA2				= 'cdx2',
	AUDIOTYPE_QT_IMA				= 'ima4', // IMA-4 ADPCM
	AUDIOTYPE_QT_ULaw				= 'ulaw', // 日本和美国的音频压缩标准。性能与ALaw相同。
	AUDIOTYPE_QT_ALaw				= 'alaw', // 欧洲及除了美国和日本之外的的音频压缩的标准。低压缩率，低质量，主要是用于传统的电话语音传播压缩编码。 
	AUDIOTYPE_QT_MicrosoftADPCM		= 0x6D730002,
	AUDIOTYPE_QT_DVIIntelIMA		= 0x6D730011,
	AUDIOTYPE_QT_DVAudio			= 'dvca',
	AUDIOTYPE_QT_QDesign			= 'QDMC',
	AUDIOTYPE_QT_QDesign2			= 'QDM2',
	AUDIOTYPE_QT_QUALCOMM			= 'Qclp',
	AUDIOTYPE_QT_MPEGLayer3			= 0x6D730055,
	AUDIOTYPE_QT_MPEGLayer3_S		= '.mp3', // MPEG layer 3
	AUDIOTYPE_QT_AMRNB				= 'samr', // AMR-NB 3gp
	AUDIOTYPE_QT_AMRWB				= 'sawb', // AMR-WB 3gp
	AUDIOTYPE_QT_GSM				= 'agsm', // gsm
	AUDIOTYPE_QT_ALAC				= 'alac', // Apple Lossless
	AUDIOTYPE_QT_WMA2				= 'WMA2', // winmedia audio
	AUDIOTYPE_QT_LPCM				= 'lpcm', // LPCM audio
};

enum enumSWFFLVAudioSubType
{
	AUDIOTYPE_SWFFLV_MP3_MPEG1  = 0,
	AUDIOTYPE_SWFFLV_MP3_MPEG2	= 1,
	AUDIOTYPE_SWFFLV_MP3_MPEG25 = 2,
	AUDIOTYPE_SWFFLV_AAC_LC		= 3,
	AUDIOTYPE_SWFFLV_AAC_MAIN	= 4,
	AUDIOTYPE_SWFFLV_AAC_LTP	= 5,
	AUDIOTYPE_SWFFLV_AAC_SSR	= 6,
	AUDIOTYPE_SWFFLV_PCMLE		= 7,	 
	AUDIOTYPE_SWFFLV_PCMBE		= 8,
	AUDIOTYPE_NELLYMOSER		= 9,
	AUDIOTYPE_SWFFLV_ADPCM4BIT  = 10,	// Adaptive Differential Pulse Code Modulation	
};

enum enumWMAudioSubType
{
	AUDIOTYPE_WMA9			= 0, // WMA2
	AUDIOTYPE_WMA10			= 1, // Professional, WMA3
	AUDIOTYPE_WMA9_LOSSLESS = 2, // lossless
	AUDIOTYPE_WMA9_VOICE	= 3, // low bitrate
	AUDIOTYPE_WMA9_ACELP	= 4, // not support in wm9 sdk
};
//-----------------------------------------------------------------------------------------------//

// 文件类型子类型描述字符
inline CSDString GetSTreamSubTypeHint( SD_STREAM_TYPE enumStreamType, SD_UINT32 dwStreamSubType )
{	
	CSDString strHint = _T("no subtype");
	switch( enumStreamType ) 
	{
	case SDSTREAMTYPE_MXF:
		switch( dwStreamSubType )
		{
		case STREAMTYPE_MXF_STD:    strHint = _T("MXF_STD");  break;
		case STREAMTYPE_MXF_XDCAM:  strHint = _T("MXF_XDCAM");break;
		case STREAMTYPE_MXF_K2:     strHint = _T("MXF_K2");   break;
		}
		break;
	case SDSTREAMTYPE_SAF:
		switch( dwStreamSubType )
		{
		case STREAMTYPE_SAF_BMC:     strHint = _T("BMC");  break;
		case STREAMTYPE_SAF_BML_0_1: strHint = _T("SAF0.1"); break;	
		case STREAMTYPE_SAF_BML_1_0: strHint = _T("SAF1.0"); break;	
		}
		break;
	case SDSTREAMTYPE_TS:
		switch( dwStreamSubType )
		{
		case STREAMTYPE_TS_STD:     strHint = _T("CBR TS");  break;
		case STREAMTYPE_TS_VBR:		strHint = _T("VBR TS"); break;	
		}
		break;
	case SDSTREAMTYPE_HLS:
		switch( dwStreamSubType )
		{
		case STREAMTYPE_HLS_Record:         strHint = _T("Record");        break;
		case STREAMTYPE_HLS_SlidingWindow:	strHint = _T("SlidingWindow"); break;	
		}
		break;
	case SDSTREAMTYPE_OPENDML_AVI:
		switch( dwStreamSubType )
		{
		case STREAMTYPE_OPENDML_AVI_STD:      strHint = _T("OpenDML_AVI_STD"); break;
		case STREAMTYPE_OPENDML_AVI_DVTYPE1:  strHint = _T("OpenDML_AVI_DVType1"); break;	
		}
		break;
	case SDSTREAMTYPE_PS:
		switch( dwStreamSubType )
		{
		case STREAMTYPE_PS_MPEG2:  strHint = _T("PS_Mpeg2"); break;       
		case STREAMTYPE_PS_MPEG1:  strHint = _T("PS_Mpeg1"); break;       
		}
		break;
	case SDSTREAMTYPE_OMNEON:
		switch( dwStreamSubType )
		{
		case STREAMTYPE_OMNEON_MOV:  strHint = _T("OMNEON_MOV"); break;       
		case STREAMTYPE_OMNEON_MXF:  strHint = _T("OMNEON_MXF"); break;       
		}
		break;
	case SDSTREAMTYPE_LXF:
		switch( dwStreamSubType )
		{
		case STREAMTYPE_LXF_V0:  strHint = _T("LXF_V0"); break;       
		case STREAMTYPE_LXF_V1:  strHint = _T("LXF_V1"); break;       
		}
		break;
	case SDSTREAMTYPE_AIFF:
		switch(dwStreamSubType)
		{
		case STREAMTYPE_AIFF_AIFF: strHint = _T("AIFF");	break;
		case STREAMTYPE_AIFF_AIFC: strHint = _T("AIFF-C"); break;
		}
		break;
	case SDSTREAMTYPE_ISOMP4:
		switch( dwStreamSubType )
		{
		case STREAMTYPE_MP4_32BIT:	 strHint = _T("MP4");			 break;       
		case STREAMTYPE_MP4_64BIT:	 strHint = _T("MP4(64BIT)");	 break;       
		case STREAMTYPE_MP4_EXCARD:  strHint = _T("ExCard Mp4+PPN"); break;       
		}
		break;
	case SDSTREAMTYPE_MSVFW_WAV:
		switch( dwStreamSubType )
		{
		case STREAMTYPE_WAVE_32BIT:	 strHint = _T("WAVE(RIFF)");	 break;       
		case STREAMTYPE_WAVE_64BIT:	 strHint = _T("WAVE(RF64)");	 break;       
		}
		break;
	default:
		break;
	}
	return strHint;
};
/////////////////////////////////////////////////////////////////////////////////////

// 视频子类型描述字符
inline CSDString GetVideoSubTypeHint( SD_VIDEO_TYPE enumVideoType, SD_UINT32 dwVideoSubType )
{
	CSDString strHint = _T("no subtype");
	switch( enumVideoType ) 
	{
		case SDVIDEOTYPE_MPEG4:
			switch( dwVideoSubType )
			{
			case VIDEOTYPE_MPEG4_ISOMPEG4:     strHint = _T("MPEG4 SP");           break;
			case VIDEOTYPE_MPEG4_ISOMPEG4_ASP: strHint = _T("MPEG4 ASP");          break;
			case VIDEOTYPE_MPEG4_XVID:         strHint = _T("XVID MPEG4");         break;
			case VIDEOTYPE_MPEG4_XVID_ASP:     strHint = _T("XVID MPEG4 ASP");     break;
			case VIDEOTYPE_MPEG4_MSV3:         strHint = _T("MS V3");              break;
			case VIDEOTYPE_MPEG4_MSV2:         strHint = _T("MS V2");              break;
			case VIDEOTYPE_MPEG4_MSV1:         strHint = _T("MS V1");              break;
			case VIDEOTYPE_MPEG4_DIVX:         strHint = _T("DIVX");               break;
			}
			break;
		case SDVIDEOTYPE_LOSSLESS:
			switch( dwVideoSubType )
			{
				case VIDEOTYPE_LOSSLESS_YUV_8BIT:	strHint = _T("YUV_8b");		break;
				case VIDEOTYPE_LOSSLESS_YUV_10BIT:	strHint = _T("YUV_10b");	break;
				case VIDEOTYPE_LOSSLESS_RGB_8BIT:	strHint = _T("RGB_8b");		break;
				case VIDEOTYPE_LOSSLESS_RGB_10BIT:	strHint = _T("RGB_10b");	break;
				case VIDEOTYPE_LOSSLESS_RGB_12BIT:	strHint = _T("RGB_12b");	break;
				case VIDEOTYPE_LOSSLESS_RGB_16BIT:	strHint = _T("RGB_16b");	break;
				case VIDEOTYPE_LOSSLESS_YUVA_8BIT:	strHint = _T("YUVA_8b");	break;
				case VIDEOTYPE_LOSSLESS_YUVA_10BIT:	strHint = _T("YUVA_10b");	break;
				case VIDEOTYPE_LOSSLESS_RGBA_8BIT:	strHint = _T("RGBA_8b");	break;
				case VIDEOTYPE_LOSSLESS_RGBA_10BIT:	strHint = _T("RGBA_10b");	break;
				case VIDEOTYPE_LOSSLESS_RGBA_12BIT:	strHint = _T("RGBA_12b");	break;
				case VIDEOTYPE_LOSSLESS_RGBA_16BIT:	strHint = _T("RGBA_16b");	break;
			}
			break;
		case SDVIDEOTYPE_DPX:
			switch( dwVideoSubType )
			{
			case VIDEOTYPE_DPX_YUV_8BIT:	strHint = _T("YUV_8b");		break;
			case VIDEOTYPE_DPX_YUV_10BIT:	strHint = _T("YUV_10b");	break;
			case VIDEOTYPE_DPX_RGB_8BIT:	strHint = _T("RGB_8b");		break;
			case VIDEOTYPE_DPX_RGB_10BIT:	strHint = _T("RGB_10b");	break;
			case VIDEOTYPE_DPX_RGB_12BIT:	strHint = _T("RGB_12b");	break;
			case VIDEOTYPE_DPX_RGB_16BIT:	strHint = _T("RGB_16b");	break;
			case VIDEOTYPE_DPX_YUVA_8BIT:	strHint = _T("YUVA_8b");	break;
			case VIDEOTYPE_DPX_YUVA_10BIT:	strHint = _T("YUVA_10b");	break;
			case VIDEOTYPE_DPX_RGBA_8BIT:	strHint = _T("RGBA_8b");	break;
			case VIDEOTYPE_DPX_RGBA_10BIT:	strHint = _T("RGBA_10b");	break;
			case VIDEOTYPE_DPX_RGBA_12BIT:	strHint = _T("RGBA_12b");	break;
			case VIDEOTYPE_DPX_RGBA_16BIT:	strHint = _T("RGBA_16b");	break;
			}
			break;
		case SDVIDEOTYPE_H265:
			switch( dwVideoSubType )
			{
				case VIDEOTYPE_HEVC_MAIN:		strHint = _T("H265 Main");			break;
				case VIDEOTYPE_HEVC_MAIN10:		strHint = _T("H265 Main10");		break;
				case VIDEOTYPE_HEVC_MAIN_STILL:	strHint = _T("H265 Main Still");	break;
			}
			break;
		case SDVIDEOTYPE_H264:
			switch( dwVideoSubType )
			{
			case VIDEOTYPE_H264_BASELINE:	strHint = _T("H264 Baseline");			break;
			case VIDEOTYPE_H264_MAIN:		strHint = _T("H264 Main");				break;
			case VIDEOTYPE_H264_HIGH:		strHint = _T("H264 High");				break;
			case VIDEOTYPE_X264_BASELINE:	strHint = _T("X264 Baseline");			break;
			case VIDEOTYPE_X264_MAIN:		strHint = _T("X264 Main");				break;
			case VIDEOTYPE_X264_HIGH:		strHint = _T("X264 High");				break;
			case VIDEOTYPE_H264_EXTENDED:	strHint = _T("H264 Extended");			break;
			case VIDEOTYPE_H264_HIGH10:		strHint = _T("H264 High 10");			break;
			case VIDEOTYPE_H264_HIGH422:	strHint = _T("H264 High 4:2:2");		break;
			case VIDEOTYPE_H264_HIGH444:	strHint = _T("H264 High 4:4:4");		break;
			}
			break;
		case SDVIDEOTYPE_H263:
			{
				switch( dwVideoSubType )
				{
				case VIDEOTYPE_H263_SUBQCIF:	strHint = _T("H263 subQCIF");			break;
				case VIDEOTYPE_H263_QCIF:		strHint = _T("H263 QCIF");				break;
				case VIDEOTYPE_H263_CIF:		strHint = _T("H263 CIF");				break;
				}
			}
			break;
		case SDVIDEOTYPE_MPEG2_IBP:
			switch( dwVideoSubType )
			{
			case VIDEOTYPE_MPEG2_STD:      strHint = _T("Mpeg2 STD"); break;
			case VIDEOTYPE_MPEG2_HQ:       strHint = _T("Mpeg2 HQ"); break;
			case VIDEOTYPE_MPEG2_FUL:      strHint = _T("Mpeg2 FUL"); break;
			case VIDEOTYPE_MPEG2_TMP:      strHint = _T("Mpeg2 TMP"); break;
			case VIDEOTYPE_MPEG2_DN8:      strHint = _T("Mpeg2 DN8"); break;
			case VIDEOTYPE_MPEG2_NEW:      strHint = _T("Mpeg2 NEW"); break;
			case VIDEOTYPE_MPEG2_NEW2:     strHint = _T("Mpeg2 NEW2"); break;
			}
			break;
		case SDVIDEOTYPE_MPEG2_D10:
			switch( dwVideoSubType )
			{
			case VIDEOTYPE_D10_50M:      strHint = _T("D10-50M"); break;
			case VIDEOTYPE_D10_40M:      strHint = _T("D10-40M"); break;
			case VIDEOTYPE_D10_30M:      strHint = _T("D10-30M"); break;
			}
			break;
		case SDVIDEOTYPE_WINDOWS_MEDIA:
			switch( dwVideoSubType )
			{
			case VIDEOTYPE_WM_V8:  strHint = _T("WM8");	break;
			case VIDEOTYPE_WM_V9:  strHint = _T("WM9");	break;
			case VIDEOTYPE_WM_V7:  strHint = _T("WM7");	break;
			case VIDEOTYPE_WM_VC1: strHint = _T("VC-1");break;
			}
		break;
		case SDVIDEOTYPE_REAL_MEDIA:
			switch( dwVideoSubType )
			{
			case VIDEOTYPE_RM_V8: strHint = _T("RM8"); break;
			case VIDEOTYPE_RM_V9: strHint = _T("RM9"); break;
			case VIDEOTYPE_RM_V10: strHint = _T("RM10"); break;		// added by liangyufan 081021
			}
			break;
		case SDVIDEOTYPE_DVHD:
			switch( dwVideoSubType )
			{
			case VIDEOTYPE_DVHD_1080_50I: strHint = _T("DVHD_1080_50I"); break;
			case VIDEOTYPE_DVHD_1080_60I: strHint = _T("DVHD_1080_60I"); break;
			case VIDEOTYPE_DVHD_720_50P:  strHint = _T("DVHD_720_50P");  break;
			case VIDEOTYPE_DVHD_720_60P:  strHint = _T("DVHD_720_60P");  break;
			}
			break;
		case SDVIDEOTYPE_MPEG2_HDV:
			switch( dwVideoSubType )
			{
			case VIDEOTYPE_HDV_HD2_1080i50:  strHint = _T("HD2 1080i/50");  break;
			case VIDEOTYPE_HDV_HD2_1080i60:  strHint = _T("HD2 1080i/60");  break;
			case VIDEOTYPE_HDV_HD1_720p25 :  strHint = _T("HD1 720p/25");   break;
			case VIDEOTYPE_HDV_HD1_720p30 :  strHint = _T("HD1 720p/30");   break;
			case VIDEOTYPE_HDV_HD1_720p50 :  strHint = _T("HD1 720p/50");   break;
			case VIDEOTYPE_HDV_HD1_720p60 :  strHint = _T("HD1 720p/60");   break;
			}
			break;
		case SDVIDEOTYPE_AVCINTRA_HD:
			switch( dwVideoSubType )
			{
			case VIDEOTYPE_AVCINTRA_C50_1080_50I    : strHint = _T("C50_1080_50I");   break;
			case VIDEOTYPE_AVCINTRA_C50_1080_5994I  : strHint = _T("C50_1080_5994I"); break;
			case VIDEOTYPE_AVCINTRA_C50_1080_25P    : strHint = _T("C50_1080_25P");   break;
			case VIDEOTYPE_AVCINTRA_C50_1080_2997P  : strHint = _T("C50_1080_2997P"); break;
			case VIDEOTYPE_AVCINTRA_C50_1080_2398P  : strHint = _T("C50_1080_2398P"); break;
			case VIDEOTYPE_AVCINTRA_C50_720_50P     : strHint = _T("C50_720_50P");    break;
			case VIDEOTYPE_AVCINTRA_C50_720_5994P   : strHint = _T("C50_720_5994P");  break;
			case VIDEOTYPE_AVCINTRA_C50_720_25P     : strHint = _T("C50_720_25P");    break;
			case VIDEOTYPE_AVCINTRA_C50_720_2997P   : strHint = _T("C50_720_2997P");  break;
			case VIDEOTYPE_AVCINTRA_C50_720_2398P   : strHint = _T("C50_720_2398P");  break;
			case VIDEOTYPE_AVCINTRA_C100_1080_50I   : strHint = _T("C100_1080_50I");  break;
			case VIDEOTYPE_AVCINTRA_C100_1080_5994I : strHint = _T("C100_1080_5994I");break;
			case VIDEOTYPE_AVCINTRA_C100_1080_25P   : strHint = _T("C100_1080_25P");  break;
			case VIDEOTYPE_AVCINTRA_C100_1080_2997P : strHint = _T("C100_1080_2997P");break;
			case VIDEOTYPE_AVCINTRA_C100_1080_2398P : strHint = _T("C100_1080_2398P");break;
			case VIDEOTYPE_AVCINTRA_C100_720_50P    : strHint = _T("C100_720_50P");   break;
			case VIDEOTYPE_AVCINTRA_C100_720_5994P  : strHint = _T("C100_720_5994P"); break;
			case VIDEOTYPE_AVCINTRA_C100_720_25P    : strHint = _T("C100_720_25P");   break;
			case VIDEOTYPE_AVCINTRA_C100_720_2997P  : strHint = _T("C100_720_2997P"); break;
			case VIDEOTYPE_AVCINTRA_C100_720_2398P  : strHint = _T("C100_720_2398P"); break;
			case VIDEOTYPE_AVCINTRA_C200_1080_50I   : strHint = _T("C200_1080_50I");  break;
			case VIDEOTYPE_AVCINTRA_C200_1080_5994I : strHint = _T("C200_1080_5994I");break;
			case VIDEOTYPE_AVCINTRA_C200_1080_2997P : strHint = _T("C200_1080_2997P");break;
			case VIDEOTYPE_AVCINTRA_C200_1080_25P   : strHint = _T("C200_1080_25P");  break;
			case VIDEOTYPE_AVCINTRA_C200_1080_2398P : strHint = _T("C200_1080_2398P");break;
			case VIDEOTYPE_AVCINTRA_C200_1080_50P   : strHint = _T("C200_1080_50P");  break;
			case VIDEOTYPE_AVCINTRA_C200_1080_5994P : strHint = _T("C200_1080_5994P");break;
			case VIDEOTYPE_AVCINTRA_C200_720_5994P  : strHint = _T("C200_720_5994P"); break;
			case VIDEOTYPE_AVCINTRA_C200_720_50P	: strHint = _T("C200_720_50P");	  break;   
			case VIDEOTYPE_AVCINTRA_C200_720_2398P  : strHint = _T("C200_720_2398P"); break;
			case VIDEOTYPE_AVCINTRA_C200_720_25P	: strHint = _T("C200_720_25P");   break;  
			case VIDEOTYPE_AVCINTRA_C200_720_2997P  : strHint = _T("C200_720_2997P"); break;
			case VIDEOTYPE_AVCINTRA_C200_720_100P   : strHint = _T("C200_720_100P");  break;
			case VIDEOTYPE_AVCINTRA_C200_720_11988P : strHint = _T("C200_720_11988P");break;
							
			case VIDEOTYPE_AVCINTRA_C100_QFHD_2997P : strHint = _T("C100_QFHD_2997P");break;
			case VIDEOTYPE_AVCINTRA_C100_QFHD_2398P : strHint = _T("C100_QFHD_2398P");break;
			case VIDEOTYPE_AVCINTRA_C100_QFHD_25P   : strHint = _T("C100_QFHD_25P");  break;
			case VIDEOTYPE_AVCINTRA_C100_QFHD_5994P : strHint = _T("C100_QFHD_5994P");break;
			case VIDEOTYPE_AVCINTRA_C100_QFHD_50P   : strHint = _T("C100_QFHD_50P");  break;
			case VIDEOTYPE_AVCINTRA_C100_4K_5994P   : strHint = _T("C100_4K_5994P");  break;
			case VIDEOTYPE_AVCINTRA_C100_4K_50P     : strHint = _T("C100_4K_50P");    break;
			case VIDEOTYPE_AVCINTRA_C100_4K_2398P   : strHint = _T("C100_4K_2398P");  break;
			case VIDEOTYPE_AVCINTRA_C100_4K_2997P   : strHint = _T("C100_4K_2997P");  break;
			case VIDEOTYPE_AVCINTRA_C100_4K_25P     : strHint = _T("C100_4K_25P");    break;
			}
			break;
		case SDVIDEOTYPE_AVCULTRA_LONGGOP:
			switch(dwVideoSubType)
			{
			case VIDEOTYPE_AVCULTRA_LONGGOP_422_G50_1080_5994I  :strHint = _T("422_G50_1080_5994I"); break;
			case VIDEOTYPE_AVCULTRA_LONGGOP_422_G50_1080_50I    :strHint = _T("422_G50_1080_50I"); break;
			case VIDEOTYPE_AVCULTRA_LONGGOP_422_G50_1080_2997P  :strHint = _T("422_G50_1080_2997P"); break;
			case VIDEOTYPE_AVCULTRA_LONGGOP_422_G50_1080_2398P  :strHint = _T("422_G50_1080_2398P"); break;
			case VIDEOTYPE_AVCULTRA_LONGGOP_422_G50_1080_25P    :strHint = _T("422_G50_1080_25P"); break;
			case VIDEOTYPE_AVCULTRA_LONGGOP_422_G50_720_5994P   :strHint = _T("422_G50_720_5994P"); break;
			case VIDEOTYPE_AVCULTRA_LONGGOP_422_G50_720_50P     :strHint = _T("422_G50_720_50P"); break;

			case VIDEOTYPE_AVCULTRA_LONGGOP_422_G25_1080_5994I  :strHint = _T("422_G25_1080_5994I"); break;
			case VIDEOTYPE_AVCULTRA_LONGGOP_422_G25_1080_50I    :strHint = _T("422_G25_1080_50I"); break;
			case VIDEOTYPE_AVCULTRA_LONGGOP_422_G25_1080_5994P  :strHint = _T("422_G25_1080_5994P"); break;
			case VIDEOTYPE_AVCULTRA_LONGGOP_422_G25_1080_2997P  :strHint = _T("422_G25_1080_2997P"); break;
			case VIDEOTYPE_AVCULTRA_LONGGOP_422_G25_1080_2398P  :strHint = _T("422_G25_1080_2398P"); break;
			case VIDEOTYPE_AVCULTRA_LONGGOP_422_G25_1080_50P    :strHint = _T("422_G25_1080_50P"); break;
			case VIDEOTYPE_AVCULTRA_LONGGOP_422_G25_1080_25P    :strHint = _T("422_G25_1080_25P"); break;
			case VIDEOTYPE_AVCULTRA_LONGGOP_422_G25_720_5994P   :strHint = _T("422_G25_720_5994P"); break;
			case VIDEOTYPE_AVCULTRA_LONGGOP_422_G25_720_50P     :strHint = _T("422_G25_720_50P"); break;

			case VIDEOTYPE_AVCULTRA_LONGGOP_420_G12_1080_5994I  :strHint = _T("420_G12_1080_5994I"); break;
			case VIDEOTYPE_AVCULTRA_LONGGOP_420_G12_1080_50I    :strHint = _T("420_G12_1080_50I"); break;
			case VIDEOTYPE_AVCULTRA_LONGGOP_420_G12_1080_5994P  :strHint = _T("420_G12_1080_5994P"); break;
			case VIDEOTYPE_AVCULTRA_LONGGOP_420_G12_1080_2997P  :strHint = _T("420_G12_1080_2997P"); break;
			case VIDEOTYPE_AVCULTRA_LONGGOP_420_G12_1080_2398P  :strHint = _T("420_G12_1080_2398P"); break;
			case VIDEOTYPE_AVCULTRA_LONGGOP_420_G12_1080_50P    :strHint = _T("420_G12_1080_50P"); break;
			case VIDEOTYPE_AVCULTRA_LONGGOP_420_G12_1080_25P    :strHint = _T("420_G12_1080_25P"); break;
			case VIDEOTYPE_AVCULTRA_LONGGOP_420_G12_720_5994P   :strHint = _T("420_G12_720_5994P"); break;
			case VIDEOTYPE_AVCULTRA_LONGGOP_420_G12_720_50P     :strHint = _T("420_G12_720_50P"); break;

			case VIDEOTYPE_AVCULTRA_LONGGOP_420_G6_1080_5994I   :strHint = _T("420_G6_1080_5994I"); break;
			case VIDEOTYPE_AVCULTRA_LONGGOP_420_G6_1080_50I     :strHint = _T("420_G6_1080_50I"); break;
			case VIDEOTYPE_AVCULTRA_LONGGOP_420_G6_1080_5994P   :strHint = _T("420_G6_1080_5994P"); break;
			case VIDEOTYPE_AVCULTRA_LONGGOP_420_G6_1080_2997P   :strHint = _T("420_G6_1080_2997P"); break;
			case VIDEOTYPE_AVCULTRA_LONGGOP_420_G6_1080_2398P   :strHint = _T("420_G6_1080_2398P"); break;
			case VIDEOTYPE_AVCULTRA_LONGGOP_420_G6_1080_50P     :strHint = _T("420_G6_1080_50P"); break;
			case VIDEOTYPE_AVCULTRA_LONGGOP_420_G6_1080_25P     :strHint = _T("420_G6_1080_25P"); break;
			case VIDEOTYPE_AVCULTRA_LONGGOP_420_G6_720_5994P    :strHint = _T("420_G6_720_5994P"); break;
			case VIDEOTYPE_AVCULTRA_LONGGOP_420_G6_720_50P      :strHint = _T("420_G6_720_50P"); break;			
			}
			break;
		case SDVIDEOTYPE_XAVC_HD:	
			switch(dwVideoSubType)
			{
			case VIDOETYPE_XAVC35_1280_720_H422P_L41 : strHint = _T("AVC35_1280_720_H422P@L41"); break;
			case VIDOETYPE_XAVC50_1280_720_H422P_L41 : strHint = _T("AVC50_1280_720_H422P@L41"); break;
			case VIDOETYPE_XAVC_1920_1080_H422P_L41	 : strHint = _T("AVC_1920_1080_H422P@L41"); break;
			case VIDOETYPE_XAVC_1920_1080_H422P_L42	 : strHint = _T("AVC_1920_1080_H422P@L42"); break;
			case VIDOETYPE_XAVC25_1920_1080_H422P_L41: strHint = _T("AVC25_1920_1080_H422P@L41"); break;
			case VIDOETYPE_XAVC35_1920_1080_H422P_L41: strHint = _T("AVC35_1920_1080_H422P@L41"); break;
			case VIDOETYPE_XAVC35_1920_1080_H422P_L42: strHint = _T("AVC35_1920_1080_H422P@L42"); break;
			case VIDOETYPE_XAVC50_1920_1080_H422P_L41: strHint = _T("AVC50_1920_1080_H422P@L41"); break;
			case VIDOETYPE_XAVC50_1920_1080_H422P_L42: strHint = _T("AVC50_1920_1080_H422P@L42"); break;
			}
			break;
		case SDVIDEOTYPE_XAVC_4K:
			switch(dwVideoSubType)
			{
			case VIDOETYPE_XAVC_3840_2160_HP_L51:   strHint = _T("AVC_3840_2160_HP@L51"); break;
			case VIDOETYPE_XAVC_3840_2160_HP_L52:   strHint = _T("AVC_3840_2160_HP@L52"); break;
			}
			break;
		case SDVIDEOTYPE_XAVC_HD_INTRA:
			switch(dwVideoSubType)
			{
			case VIDOETYPE_XAVC100CBG_1280_720_H422IP_L41 :   strHint = _T("AVC100CBG_1280_720_H422IP@L41");  break;
			case VIDOETYPE_XAVC50CBG_1440_1080_H10IP_L4	  :   strHint = _T("AVC50CBG_1440_1080_H10IP@L4");  break;
			case VIDOETYPE_XAVC100CBG_1920_1080_H422IP_L41:   strHint = _T("AVC100CBG_1920_1080_H422IP@L41");  break;
			case VIDOETYPE_XAVC100CBG_1920_1080_H422IP_L42:   strHint = _T("AVC100CBG_1920_1080_H422IP@L42");  break;
			case VIDOETYPE_XAVC200CBG_1920_1080_H422IP_L41:   strHint = _T("AVC200CBG_1920_1080_H422IP@L41");  break;
			case VIDOETYPE_XAVC200CBG_1920_1080_H422IP_L5 :   strHint = _T("AVC200CBG_1920_1080_H422IP@L5");  break;
			}
			break;
		case SDVIDEOTYPE_XAVC_4K_INTRA:
			switch(dwVideoSubType)
			{
			case VIDOETYPE_XAVCCBG_2048_1080_H422IP_L42   :   strHint = _T("AVCCBG_2048_1080_H422IP@L42"); break;
			case VIDOETYPE_XAVCCBG_2048_1080_H422IP_L5	  :   strHint = _T("AVCCBG_2048_1080_H422IP@L5"); break;
			case VIDOETYPE_XAVC_2048_1080_H422IP_L42	  :   strHint = _T("AVC_2048_1080_H422IP@L42"); break;
			case VIDOETYPE_XAVC_2048_1080_H422IP_L5		  :   strHint = _T("AVC_2048_1080_H422IP@L5"); break;
			case VIDOETYPE_XAVCCBG_3840_2160_H422IP_L51	  :   strHint = _T("AVCCBG_3840_2160_H422IP@L51"); break;
			case VIDOETYPE_XAVCCBG_3840_2160_H422IP_L52	  :   strHint = _T("AVCCBG_3840_2160_H422IP@L52"); break;
			case VIDOETYPE_XAVC_3840_2160_H422IP_L51	  :   strHint = _T("AVC_3840_2160_H422IP@L51"); break;
			case VIDOETYPE_XAVC_3840_2160_H422IP_L52	  :   strHint = _T("AVC_3840_2160_H422IP@L52"); break;
			case VIDOETYPE_XAVC480CBG_3840_2160_H422IP_L51:   strHint = _T("AVC480CBG_3840_2160_H422IP@L51"); break;
			case VIDOETYPE_XAVC480CBG_3840_2160_H422IP_L52:   strHint = _T("AVC480CBG_3840_2160_H422IP@L52"); break;
			case VIDOETYPE_XAVC480_3840_2160_H422IP_L51	  :   strHint = _T("AVC480_3840_2160_H422IP@L51"); break;
			case VIDOETYPE_XAVC480_3840_2160_H422IP_L52	  :   strHint = _T("AVC480_3840_2160_H422IP@L52"); break;
			case VIDOETYPE_XAVCCBG_4096_2160_H422IP_L51	  :   strHint = _T("AVCCBG_4096_2160_H422IP@L51"); break;
			case VIDOETYPE_XAVCCBG_4096_2160_H422IP_L52	  :   strHint = _T("AVCCBG_4096_2160_H422IP@L52"); break;
			case VIDOETYPE_XAVC_4096_2160_H422IP_L51	  :   strHint = _T("AVC_4096_2160_H422IP@L51"); break;
			case VIDOETYPE_XAVC_4096_2160_H422IP_L52	  :   strHint = _T("AVC_4096_2160_H422IP@L52"); break;
			case VIDOETYPE_XAVC480CBG_4096_2160_H422IP_L51:   strHint = _T("AVC480CBG_4096_2160_H422IP@L51"); break;
			case VIDOETYPE_XAVC480CBG_4096_2160_H422IP_L52:   strHint = _T("AVC480CBG_4096_2160_H422IP@L52"); break;
			case VIDOETYPE_XAVC480_4096_2160_H422IP_L51	  :   strHint = _T("AVC480_4096_2160_H422IP@L51"); break;
			case VIDOETYPE_XAVC480_4096_2160_H422IP_L52	  :   strHint = _T("AVC480_4096_2160_H422IP@L52"); break;
			}
			break;
		case SDVIDEOTYPE_XAVC_HD444_INTRA:
			switch(dwVideoSubType)
			{
			case 0:
			default:
				break;
			}
			break;
		case SDVIDEOTYPE_XAVC_4K444_INTRA:
			switch(dwVideoSubType)
			{
			case 0:
			default:
				break;
			}
			break;
		case SDVIDEOTYPE_MPEG4_SSTP:
			switch(dwVideoSubType)
			{
			case VIDOETYPE_MPEG4SStP_Lite_1280_720_422    : strHint = _T("MPEG4SStP_Lite_1280_720_422"); break;
			case VIDOETYPE_MPEG4SStP_Lite_1920_1080_422	  : strHint = _T("MPEG4SStP_Lite_1920_1080_422"); break;
			case VIDOETYPE_MPEG4SStP_SQ_1280_720_422	  : strHint = _T("MPEG4SStP_SQ_1280_720_422"); break;
			case VIDOETYPE_MPEG4SStP_SQ_1920_1080_422	  : strHint = _T("MPEG4SStP_SQ_1920_1080_422"); break;
			case VIDOETYPE_MPEG4SStP_SQ_1920_1080_444RGB  : strHint = _T("MPEG4SStP_SQ_1920_1080_444RGB"); break;
			case VIDOETYPE_MPEG4SStP_HQ_1920_1080_444RGB  : strHint = _T("MPEG4SStP_HQ_1920_1080_444RGB"); break;
			case VIDOETYPE_MPEG4SStP_HQ_1920_1080_444RGB12: strHint = _T("MPEG4SStP_HQ_1920_1080_444RGB12"); break;
			case VIDOETYPE_MPEG4SStP_SQ_2048_1080_444RGB  : strHint = _T("MPEG4SStP_SQ_2048_1080_444RGB"); break;
			case VIDOETYPE_MPEG4SStP_SQ_2048_1080_444XYZ  : strHint = _T("MPEG4SStP_SQ_2048_1080_444XYZ"); break;
			case VIDOETYPE_MPEG4SStP_HQ_2048_1080_444RGB  : strHint = _T("MPEG4SStP_HQ_2048_1080_444RGB"); break;
			case VIDOETYPE_MPEG4SStP_HQ_2048_1080_444XYZ  : strHint = _T("MPEG4SStP_HQ_2048_1080_444XYZ"); break;
			case VIDOETYPE_MPEG4SStP_HQ_2048_1556_444RGB  : strHint = _T("MPEG4SStP_HQ_2048_1556_444XYZ"); break;
			}
			break;
		case SDVIDEOTYPE_SONY_RAW:
			switch(dwVideoSubType)
			{
			case VIDEOTYPE_SONYRAW_F65RAWLite_4096_2160   : strHint = _T("SONYRAW_F65RAWLite_4096_2160"); break;
			case VIDEOTYPE_SONYRAW_F65RAWSQ_4096_2160	  : strHint = _T("SONYRAW_F65RAWSQ_4096_2160"); break;
			case VIDEOTYPE_SONYRAW_F65RAWHQ_4096_2160	  : strHint = _T("SONYRAW_F65RAWHQ_4096_2160"); break;
			case VIDEOTYPE_SONYRAW_F65RAWHFRLite_4096_2160: strHint = _T("SONYRAW_F65RAWHFRLite_4096_2160"); break;
			case VIDEOTYPE_SONYRAW_F65RAWHFRSQ_4096_2160  : strHint = _T("SONYRAW_F65RAWHFRSQ_4096_2160"); break;
			case VIDEOTYPE_SONYRAW_F65RAWHFRHQ_4096_2160  : strHint = _T("SONYRAW_F65RAWHFRHQ_4096_2160"); break;
			case VIDEOTYPE_SONYRAW_F55RAWLite_2048_1080	  : strHint = _T("SONYRAW_F55RAWLite_2048_1080"); break;
			case VIDEOTYPE_SONYRAW_F55RAWLite_4096_2160	  : strHint = _T("SONYRAW_F55RAWLite_4096_2160"); break;
			case VIDEOTYPE_SONYRAW_F55RAWSQ_2048_1080	  : strHint = _T("SONYRAW_F55RAWSQ_2048_1080"); break;
			case VIDEOTYPE_SONYRAW_F55RAWSQ_4096_2160	  : strHint = _T("SONYRAW_F55RAWSQ_4096_2160"); break;
			case VIDEOTYPE_SONYRAW_F55RAWHQ_2048_1080	  : strHint = _T("SONYRAW_F55RAWHQ_2048_1080"); break;
			case VIDEOTYPE_SONYRAW_F55RAWHQ_4096_2160	  : strHint = _T("SONYRAW_F55RAWHQ_4096_2160"); break;
			}
			break;
		case SDVIDEOTYPE_AVID_DNXHD:
			switch( dwVideoSubType )
			{
			case VIDEOTYPE_DNxHD_1080_50I_185_8bit		: strHint = _T("1080i/50 DNxHD 185 8bit");     break;
			case VIDEOTYPE_DNxHD_1080_50I_120_8bit		: strHint = _T("1080i/50 DNxHD 120 8bit");     break;
			case VIDEOTYPE_DNxHD_1080_50I_185_10bit		: strHint = _T("1080i/50 DNxHD 185 10bit");    break;
			case VIDEOTYPE_DNxHD_TR_1080_50I_120_8bit	: strHint = _T("1080i/50 DNxHD-TR 120 8bit");  break;
			case VIDEOTYPE_DNxHD_1080_5994I_220_8bit	: strHint = _T("1080i/5994 DNxHD 220 8bit");   break;
			case VIDEOTYPE_DNxHD_1080_5994I_145_8bit	: strHint = _T("1080i/5994 DNxHD 145 8bit");   break;
			case VIDEOTYPE_DNxHD_1080_5994I_220_10bit	: strHint = _T("1080i/5994 DNxHD 220 10bit");  break;
			case VIDEOTYPE_DNxHD_TR_1080_5994I_145_8bit : strHint = _T("1080i/5994 DNxHD-TR 145 8bit");break;
			case VIDEOTYPE_DNxHD_1080_25P_185_8bit      : strHint = _T("1080p/25 DNxHD 185 8bit");     break;
			case VIDEOTYPE_DNxHD_1080_25P_120_8bit      : strHint = _T("1080p/25 DNxHD 120 8bit");     break;
			case VIDEOTYPE_DNxHD_1080_25P_36_8bit       : strHint = _T("1080p/25 DNxHD 36 8bit");      break;
			case VIDEOTYPE_DNxHD_1080_25P_185_10bit     : strHint = _T("1080p/25 DNxHD 185 10bit");    break;
			case VIDEOTYPE_DNxHD_1080_2397P_175_8bit    : strHint = _T("1080p/23.97 DNxHD 175 8bit");  break;
			case VIDEOTYPE_DNxHD_1080_2397P_115_8bit    : strHint = _T("1080p/23.97 DNxHD 115 8bit");  break;
			case VIDEOTYPE_DNxHD_1080_2397P_36_8bit     : strHint = _T("1080p/23.97 DNxHD 36 8bit");   break;
			case VIDEOTYPE_DNxHD_1080_2397P_175_10bit   : strHint = _T("1080p/23.97 DNxHD 175 10bit"); break;
			case VIDEOTYPE_DNxHD_1080_24P_175_8bit      : strHint = _T("1080p/24 DNxHD 175 8bit");     break;
			case VIDEOTYPE_DNxHD_1080_24P_115_8bit      : strHint = _T("1080p/24 DNxHD 115 8bit");     break;
			case VIDEOTYPE_DNxHD_1080_24P_36_8bit       : strHint = _T("1080p/24 DNxHD 36 8bit");      break;
			case VIDEOTYPE_DNxHD_1080_24P_175_10bit     : strHint = _T("1080p/24 DNxHD 175 10bit");    break;
			case VIDEOTYPE_DNxHD_720_5994P_220_8bit     : strHint = _T("720p/59.94 DNxHD 220 8bit");   break;
			case VIDEOTYPE_DNxHD_720_5994P_145_8bit     : strHint = _T("720p/59.94 DNxHD 145 8bit");   break;
			case VIDEOTYPE_DNxHD_720_5994P_220_10bit    : strHint = _T("720p/59.94 DNxHD 220 10bit");  break;
			case VIDEOTYPE_DNxHD_720_2397P_90_8bit      : strHint = _T("720p/23.97 DNxHD 90 8bit");    break;
			case VIDEOTYPE_DNxHD_720_2397P_60_8bit      : strHint = _T("720p/23.97 DNxHD 60 8bit");    break;
			case VIDEOTYPE_DNxHD_720_2397P_90_10bit     : strHint = _T("720p/23.97 DNxHD 90 10bit");   break;
			case VIDEOTYPE_DNxHD_720_2997P_110_8bit     : strHint = _T("720p/29.97 DNxHD 110 8bit");   break;
			case VIDEOTYPE_DNxHD_720_2997P_75_8bit      : strHint = _T("720p/29.97 DNxHD 75 8bit");    break;
			case VIDEOTYPE_DNxHD_720_2997P_110_10bit    : strHint = _T("720p/29.97 DNxHD 110 10bit");  break;
			case VIDEOTYPE_DNxHD_720_25P_60_8bit        : strHint = _T("720p/25 DNxHD 60 8bit");       break;
			case VIDEOTYPE_DNxHD_720_50P_185_8bit       : strHint = _T("720p/50 DNxHD 185 8bit");      break;
			case VIDEOTYPE_DNxHD_720_50P_120_8bit       : strHint = _T("720p/50 DNxHD 120 8bit");      break;
			case VIDEOTYPE_DNxHD_720_50P_185_10bit      : strHint = _T("720p/50 DNxHD 185 10bit");     break;
			case VIDEOTYPE_DNxHD_1080_2997P_440_10bit   : strHint = _T("1080p/29.97 DNxHD 440 10bit"); break;
			case VIDEOTYPE_DNxHD_1080_2397P_360_10bit   : strHint = _T("1080p/23.97 DNxHD 360 10bit"); break;
			case VIDEOTYPE_DNxHD_1080_25P_370_10bit     : strHint = _T("1080p/25 DNxHD 370 10bit");    break;
			case VIDEOTYPE_DNxHD_1080_24P_360_10bit     : strHint = _T("1080p/24 DNxHD 360 10bit");    break;
			}
			break;
		case SDVIDEOTYPE_QUICKTIME_MOV:
			switch( dwVideoSubType )
			{
			case VIDEOTYPE_QT_MPEG4Visual: strHint = _T("MPEG4Visual"); break;
			case VIDEOTYPE_QT_Raw: strHint = _T("Raw"); break;
			case VIDEOTYPE_QT_Cinepak: strHint = _T("Cinepak"); break;
			case VIDEOTYPE_QT_Graphics: strHint = _T("Graphics"); break;
			case VIDEOTYPE_QT_Animation: strHint = _T("Animation"); break;
			case VIDEOTYPE_QT_Video: strHint = _T("Video"); break;
			case VIDEOTYPE_QT_ComponentVideo: strHint = _T("ComponentVideo"); break;
			case VIDEOTYPE_QT_JPEG: strHint = _T("JPEG"); break;
			case VIDEOTYPE_QT_MotionJPEGA: strHint = _T("MotionJPEGA"); break;
			case VIDEOTYPE_QT_MotionJPEGB: strHint = _T("MotionJPEGB"); break;
			case VIDEOTYPE_QT_SGI: strHint = _T("SGI"); break;
			case VIDEOTYPE_QT_PlanarRGB: strHint = _T("PlanarRGB"); break;
			case VIDEOTYPE_QT_MacPaint: strHint = _T("MacPaint"); break;
			case VIDEOTYPE_QT_GIF: strHint = _T("GIF"); break;
			case VIDEOTYPE_QT_PhotoCD: strHint = _T("PhotoCD"); break;
			case VIDEOTYPE_QT_QuickDrawGX: strHint = _T("QuickDrawGX"); break;
			case VIDEOTYPE_QT_AVRJPEG: strHint = _T("AVRJPEG"); break;
			case VIDEOTYPE_QT_OpenDMLJPEG: strHint = _T("OpenDMLJPEG"); break;
			case VIDEOTYPE_QT_BMP: strHint = _T("BMP"); break;
			case VIDEOTYPE_QT_WindowsRaw: strHint = _T("WindowsRaw"); break;
			case VIDEOTYPE_QT_Vector: strHint = _T("Vector"); break;
			case VIDEOTYPE_QT_QuickDraw: strHint = _T("QuickDraw"); break;
			case VIDEOTYPE_QT_WaterRipple: strHint = _T("WaterRipple"); break;
			case VIDEOTYPE_QT_Fire: strHint = _T("Fire"); break;
			case VIDEOTYPE_QT_Cloud: strHint = _T("Cloud"); break;
			case VIDEOTYPE_QT_H261: strHint = _T("H261"); break;
			case VIDEOTYPE_QT_H263: strHint = _T("H263"); break;
			case VIDEOTYPE_QT_H264: strHint = _T("H264"); break;
			case VIDEOTYPE_QT_JPEG2000: strHint = _T("JPEG2000"); break;
			case VIDEOTYPE_QT_DVCNTSC: strHint = _T("DVCNTSC"); break;
			case VIDEOTYPE_QT_DVCPAL: strHint = _T("DVCPAL"); break;
			case VIDEOTYPE_QT_DVCProPAL: strHint = _T("DVCProPAL"); break;
			case VIDEOTYPE_QT_DVCPro50PAL:  strHint = _T("DVCPro50PAL"); break;
			case VIDEOTYPE_QT_DVCPro50NTSC:  strHint = _T("DVCPro50NTSC"); break;
			case VIDEOTYPE_QT_DVCPro100PAL:  strHint = _T("DVCPro100PAL"); break;
			case VIDEOTYPE_QT_DVCPro100NTSC:  strHint = _T("DVCPro100NTSC"); break;
			case VIDEOTYPE_QT_DVCProHD720P:  strHint = _T("DVCProHD720P"); break;
			case VIDEOTYPE_QT_DVCProHD1080i60:  strHint = _T("DVCProHD1080i60"); break;
			case VIDEOTYPE_QT_DVCProHD1080i50:  strHint = _T("DVCProHD1080i50"); break;
			case VIDEOTYPE_QT_Base: strHint = _T("Base"); break;
			case VIDEOTYPE_QT_FLC: strHint = _T("FLC"); break;
			case VIDEOTYPE_QT_Targa: strHint = _T("Targa"); break;
			case VIDEOTYPE_QT_PNG: strHint = _T("PNG"); break;
			case VIDEOTYPE_QT_TIFF: strHint = _T("TIFF"); break;
			case VIDEOTYPE_QT_ComponentVideoSigned: strHint = _T("ComponentVideoSigned"); break;
			case VIDEOTYPE_QT_ComponentVideoUnsigned: strHint = _T("ComponentVideoUnsigned"); break;
			case VIDEOTYPE_QT_CMYK: strHint = _T("CMYK"); break;
			case VIDEOTYPE_QT_MicrosoftVideo1: strHint = _T("MicrosoftVideo1"); break;
			case VIDEOTYPE_QT_Sorenson: strHint = _T("Sorenson"); break;
			case VIDEOTYPE_QT_Sorenson3: strHint = _T("Sorenson3"); break;
			case VIDEOTYPE_QT_Indeo4: strHint = _T("Indeo4"); break;
			case VIDEOTYPE_QT_64ARGB: strHint = _T("64ARGB"); break;
			case VIDEOTYPE_QT_48RGB: strHint = _T("48RGB"); break;
			case VIDEOTYPE_QT_32AlphaGray: strHint = _T("32AlphaGray"); break;
			case VIDEOTYPE_QT_16Gray: strHint = _T("6Gray"); break;
			case VIDEOTYPE_QT_MpegYUV420: strHint = _T("MpegYUV420"); break;
			case VIDEOTYPE_QT_YUV420: strHint = _T("YUV420"); break;
			case VIDEOTYPE_QT_SorensonYUV9: strHint = _T("SorensonYUV9"); break;
			case VIDEOTYPE_QT_422YpCbCr8: strHint = _T("422YpCbCr8"); break;
			case VIDEOTYPE_QT_444YpCbCr8: strHint = _T("444YpCbCr8"); break;
			case VIDEOTYPE_QT_4444YpCbCrA8: strHint = _T("4444YpCbCrA8"); break;
			case VIDEOTYPE_QT_422YpCbCr16: strHint = _T("422YpCbCr16"); break;
			case VIDEOTYPE_QT_422YpCbCr10: strHint = _T("422YpCbCr10"); break;
			case VIDEOTYPE_QT_444YpCbCr10: strHint = _T("444YpCbCr10"); break;
			case VIDEOTYPE_QT_4444YpCbCrA8R: strHint = _T("4444YpCbCrA8R"); break;
			case VIDEOTYPE_QT_Mpeg: strHint = _T("Mpeg"); break;
			case VIDEOTYPE_QT_AVID_DNX: strHint = _T("AVID DNX"); break;
			case VIDEOTYPE_QT_AVID_IMXP: strHint = _T("AVID IMX PAL"); break;
			case VIDEOTYPE_QT_AVID_IMXN: strHint = _T("AVID IMX NTSC"); break;
			case VIDEOTYPE_QT_AVID_DV: strHint = _T("AVID DV"); break;
			case VIDEOTYPE_QT_IMX50P: strHint = _T("IMX50P"); break;
			case VIDEOTYPE_QT_IMX50N: strHint = _T("IMX50N"); break;
			case VIDEOTYPE_QT_IMX40P: strHint = _T("IMX40P"); break;
			case VIDEOTYPE_QT_IMX40N: strHint = _T("IMX40N"); break;
			case VIDEOTYPE_QT_IMX30P: strHint = _T("IMX30P"); break;
			case VIDEOTYPE_QT_IMX30N: strHint = _T("IMX30N"); break;
			case VIDEOTYPE_QT_XDCAMEX_720P30: strHint = _T("XDCAM EX 720p30 VBR"); break;
			case VIDEOTYPE_QT_XDCAMHD_1080I60: strHint = _T("XDCAM HD 1080i60 VBR"); break;
			case VIDEOTYPE_QT_XDCAMHD_1080I50: strHint = _T("XDCAM HD 1080i50 VBR"); break;
			case VIDEOTYPE_QT_XDCAMEX_720P24: strHint = _T("XDCAM EX 720p24 VBR"); break;
			case VIDEOTYPE_QT_XDCAMEX_720P25: strHint = _T("XDCAM EX 720p25 VBR"); break;
			case VIDEOTYPE_QT_XDCAMHD_1080P24: strHint = _T("XDCAM HD 1080p24 VBR"); break;
			case VIDEOTYPE_QT_XDCAMHD_1080P25: strHint = _T("XDCAM HD 1080p25 VBR"); break;
			case VIDEOTYPE_QT_XDCAMHD_1080P30: strHint = _T("XDCAM HD 1080p30 VBR"); break;
			case VIDEOTYPE_QT_XDCAMEX_720P60: strHint = _T("XDCAM EX 720p60 VBR"); break; 
			case VIDEOTYPE_QT_XDCAMEX_720P50: strHint = _T("XDCAM EX 720p50 VBR"); break; 
			case VIDEOTYPE_QT_XDCAMEX_1080I60: strHint = _T("XDCAM EX 1080i60 VBR"); break; 
			case VIDEOTYPE_QT_XDCAMEX_1080I50: strHint = _T("XDCAM EX 1080i50 VBR"); break;
			case VIDEOTYPE_QT_XDCAMEX_1080P24: strHint = _T("XDCAM EX 1080p24 VBR"); break;
			case VIDEOTYPE_QT_XDCAMEX_1080P25: strHint = _T("DCAM EX 1080p25 VBR"); break; 
			case VIDEOTYPE_QT_XDCAMEX_1080P30: strHint = _T("XDCAM EX 1080p30 VBR"); break;
			case VIDEOTYPE_QT_XDCAM422HD_720P60: strHint = _T("XDCAM HD422 720p60 CBR"); break;
			case VIDEOTYPE_QT_XDCAM422HD_720P50: strHint = _T("XDCAM HD422 720p50 CBR"); break; 
			case VIDEOTYPE_QT_XDCAM422HD_1080I60: strHint = _T("XDCAM HD422 1080i60 CBR"); break;
			case VIDEOTYPE_QT_XDCAM422HD_1080I50: strHint = _T("XDCAM HD422 1080i50 CBR"); break;
			case VIDEOTYPE_QT_XDCAM422HD_1080P24: strHint = _T("XDCAM HD422 1080p24 CBR"); break;
			case VIDEOTYPE_QT_XDCAM422HD_1080P25: strHint = _T("XDCAM HD422 1080p25 CBR"); break; 
			case VIDEOTYPE_QT_XDCAM422HD_1080P30: strHint = _T("XDCAM HD422 1080p30 CBR"); break; 
			case VIDEOTYPE_QT_HDV1: strHint = _T("MPEG2 HDV 720p30"); break; 
			case VIDEOTYPE_QT_HDV2: strHint = _T("MPEG2 HDV 1080i60"); break; 
			case VIDEOTYPE_QT_HDV3: strHint = _T("MPEG2 HDV 1080i50"); break; 
			case VIDEOTYPE_QT_HDV5: strHint = _T("MPEG2 HDV 720p25"); break; 
			case VIDEOTYPE_QT_HDV6: strHint = _T("MPEG2 HDV 1080p24"); break; 
			case VIDEOTYPE_QT_HDV7: strHint = _T("MPEG2 HDV 1080p25"); break; 
			case VIDEOTYPE_QT_HDV8: strHint = _T("MPEG2 HDV 1080p30 "); break; 
			case VIDEOTYPE_QT_VC1:  strHint = _T("VC-1"); break;
			case VIDEOTYPE_QT_ProRes422:		strHint = _T("ProRes422"); break; 
			case VIDEOTYPE_QT_ProRes422_Proxy:  strHint = _T("ProRes422(Proxy)"); break; 
			case VIDEOTYPE_QT_ProRes422_LT:		strHint = _T("ProRes422(LT)"); break; 
			case VIDEOTYPE_QT_ProRes422_HQ:     strHint = _T("ProRes422(HQ)"); break; 
			case VIDEOTYPE_QT_ProRes444:		strHint = _T("ProRes444"); break; 
			default:
				{
				char c1 = char(dwVideoSubType>>24);
				char c2 = char(dwVideoSubType>>16);
				char c3 = char(dwVideoSubType>>8);
				char c4 = char(dwVideoSubType);
				CSDString str;
				str.Format(_T("%c%c%c%c"), c1,c2,c3,c4);
				strHint = str;
				}
				break;
			}
			break;
		case SDVIDEOTYPE_SWFFLV_TYPE:
			switch(dwVideoSubType)
			{
			case VIDEOTYPE_SORENSON_H263: strHint = _T("Sorenson H263"); break;
			case VIDEOTYPE_AVC_BASE:	  strHint = _T("AVC BASELINE"); break;
			case VIDEOTYPE_AVC_MAIN:	  strHint = _T("AVC MAIN"); break;
			case VIDEOTYPE_AVC_HIGH:	  strHint = _T("AVC HIGH"); break;			
			case VIDEOTYPE_VP6:			  strHint = _T("VP6"); break;
			case VIDEOTYPE_VP6A:		  strHint = _T("VP6A"); break;
			case VIDEOTYPE_SCREENVIDEO:   strHint = _T("Screen Video"); break;
			case VIDEOTYPE_SCREEN2VIDEO:  strHint = _T("Screen Video 2"); break;
			
			}		
			break;
		case SDVIDEOTYPE_VCM_COMPRESSED:
			{
				char c1 = char(dwVideoSubType>>24);
				char c2 = char(dwVideoSubType>>16);
				char c3 = char(dwVideoSubType>>8);
				char c4 = char(dwVideoSubType);
				CSDString str;
				str.Format(_T("%c%c%c%c"), c4,c3,c2,c1);
				strHint = str;
			}
			break;
		case SDVIDEOTYPE_PRORES422:
			switch(dwVideoSubType)
			{
			case VIDEOTYPE_ProRes422_Proxy: strHint = _T("ProRes 422(Proxy)");    break;
			case VIDEOTYPE_ProRes422_LT:	strHint = _T("ProRes 422(LT)");		  break;
			case VIDEOTYPE_ProRes422:		strHint = _T("ProRes 422(Standard)"); break;
			case VIDEOTYPE_ProRes422_HQ:	strHint = _T("ProRes 422(HQ)");		  break;
			}		
			break;
		default:
			break;
	}// switch( enumVideoType ) 
	return strHint;
};

// 音频子类型描述字符
inline CSDString GetAudioSubTypeHint( SD_AUDIO_TYPE enumAudioType, SD_UINT32 dwAudioSubType )
{
	CSDString strHint = _T("no subtype");
	switch( enumAudioType ) 
	{
		case SDAUDIOTYPE_MP1:
		{
			switch( dwAudioSubType )
			{
			case AUDIOTYPE_MP1_MPEG1: strHint = _T("MPEG1 Layer1"); break; 
			case AUDIOTYPE_MP1_MPEG2: strHint = _T("MPEG2 Layer1"); break; 
			}
		}
		break;
		case SDAUDIOTYPE_MP2:
		{
			switch( dwAudioSubType )
			{
			case AUDIOTYPE_MP2_MPEG1: strHint = _T("MPEG1 Layer2"); break; 
			case AUDIOTYPE_MP2_MPEG2: strHint = _T("MPEG2 Layer2"); break; 
			}
		}
		break;
		case SDAUDIOTYPE_MP3:
		{
			switch( dwAudioSubType )
			{
			case AUDIOTYPE_MP3_MPEG1:  strHint = _T("MPEG1 Layer3"); break; 
			case AUDIOTYPE_MP3_MPEG2:  strHint = _T("MPEG2 Layer3"); break; 
			case AUDIOTYPE_MP3_MPEG25: strHint = _T("MPEG2.5 Layer3"); break;
			}
		}
		break;
		case SDAUDIOTYPE_QUICKTIME_MOV:
		{
			switch( dwAudioSubType )
			{
			case AUDIOTYPE_QT_MPEG4Audio: strHint = _T("MPEG-4 Audio"); break;
			case AUDIOTYPE_QT_NotCompressed: strHint = _T("NotCompressed"); break;    
			case AUDIOTYPE_QT_8BitOffsetBinary: strHint = _T("8BitOffsetBinary"); break;
			case AUDIOTYPE_QT_16BitBigEndian: strHint = _T("16BitBigEndian"); break;
			case AUDIOTYPE_QT_16BitLittleEndian: strHint = _T("16BitLittleEndian"); break;
			case AUDIOTYPE_QT_Float32: strHint = _T("Float32bit"); break;
			case AUDIOTYPE_QT_Float64: strHint = _T("Float64bit"); break;
			case AUDIOTYPE_QT_24Bit: strHint = _T("Integer24bit"); break;
			case AUDIOTYPE_QT_32Bit: strHint = _T("Integer32bit"); break;
			case AUDIOTYPE_QT_MACE3: strHint = _T("MACE3:1"); break;
			case AUDIOTYPE_QT_MACE6: strHint = _T("MACE6:1"); break;
			case AUDIOTYPE_QT_CDXA4: strHint = _T("CDXA4"); break;
			case AUDIOTYPE_QT_CDXA2: strHint = _T("CDXA2"); break;
			case AUDIOTYPE_QT_IMA: strHint = _T("IMA4:1"); break;
			case AUDIOTYPE_QT_ULaw: strHint = _T("ULaw2:1"); break;
			case AUDIOTYPE_QT_ALaw: strHint = _T("ALaw2:1"); break;
			case AUDIOTYPE_QT_MicrosoftADPCM: strHint = _T("MicrosoftADPCM"); break;
			case AUDIOTYPE_QT_DVIIntelIMA: strHint = _T("DVIIntelIMA"); break;
			case AUDIOTYPE_QT_DVAudio: strHint = _T("DVAudio"); break;
			case AUDIOTYPE_QT_QDesign: strHint = _T("QDesign Music"); break;
			case AUDIOTYPE_QT_QDesign2: strHint = _T("QDesign Music2"); break;
			case AUDIOTYPE_QT_QUALCOMM: strHint = _T("Qualcomm PureVoice"); break;
			case AUDIOTYPE_QT_MPEGLayer3: strHint = _T("MPEGLayer3"); break;
			case AUDIOTYPE_QT_MPEGLayer3_S: strHint = _T("MPEGLayer3(CBR&VBR)"); break;
			case AUDIOTYPE_QT_AMRNB: strHint = _T("AMRNB"); break;
			case AUDIOTYPE_QT_AMRWB: strHint = _T("AMRWB"); break;
			case AUDIOTYPE_QT_GSM: strHint = _T("GSM Auido"); break;
			case AUDIOTYPE_QT_ALAC: strHint = _T("Apple Lossless"); break;
			case AUDIOTYPE_QT_WMA2: strHint = _T("WMA2"); break;
			case AUDIOTYPE_QT_LPCM: strHint = _T("lpcm"); break;
			default:
				{
				char c1 = char(dwAudioSubType>>24);
				char c2 = char(dwAudioSubType>>16);
				char c3 = char(dwAudioSubType>>8);
				char c4 = char(dwAudioSubType);
				CSDString str;
				str.Format(_T("%c%c%c%c"), c1,c2,c3,c4);
				strHint = str;
				}
				break;
			}
		}
		break;
		case SDAUDIOTYPE_AAC:
		{
			switch( dwAudioSubType )
			{
			case AUDIOTYPE_MPEG4_AAC_LC:   strHint = _T("Mpeg4 AAC LC");   break;    
			case AUDIOTYPE_MPEG4_AAC_MAIN: strHint = _T("Mpeg4 AAC Main"); break;
			case AUDIOTYPE_MPEG4_AAC_SSR:  strHint = _T("Mpeg4 AAC SSR");  break;
			case AUDIOTYPE_MPEG4_AAC_LTP:  strHint = _T("Mpeg4 AAC LTP");  break;
			case AUDIOTYPE_MPEG4_AAC_SBR:  strHint = _T("HE-AAC v1");	   break;
			case AUDIOTYPE_MPEG4_AAC_SBR_PS:strHint = _T("HE-AAC v2");     break;
			case AUDIOTYPE_MPEG2_AAC_LC:   strHint = _T("Mpeg2 AAC LC");   break;    
			case AUDIOTYPE_MPEG2_AAC_MAIN: strHint = _T("Mpeg2 AAC Main"); break;
			case AUDIOTYPE_MPEG2_AAC_SSR:  strHint = _T("Mpeg2 AAC SSR");  break;
			}
		}
		break;
		case SDAUDIOTYPE_WAVE_PCM:
		{
			switch( dwAudioSubType )
			{
			case AUDIOTYPE_WAVE_PCM:        strHint = _T("WAVE PCM"); break;
			case AUDIOTYPE_WAVE_IEEE_FLOAT: strHint = _T("WAVE IEEE FLOAT"); break;    
			}
		}
		break;
		case SDAUDIOTYPE_G711:
		{
			switch( dwAudioSubType )
			{
			case AUDIOTYPE_G711_ALaw: strHint = _T("G711-ALaw"); break;
			case AUDIOTYPE_G711_ULaw: strHint = _T("G711-ULaw"); break;    
			}
		}
		break;
		case SDAUDIOTYPE_AMRNB:
		{
			switch(dwAudioSubType) 
			{
			case AUDIOMODE_AMRNB_475: strHint = _T("MODE-475"); break;
			case AUDIOMODE_AMRNB_515: strHint = _T("MODE-515"); break;
			case AUDIOMODE_AMRNB_590: strHint = _T("MODE-590"); break;
			case AUDIOMODE_AMRNB_670: strHint = _T("MODE-670"); break;
			case AUDIOMODE_AMRNB_740: strHint = _T("MODE-740"); break;
			case AUDIOMODE_AMRNB_795: strHint = _T("MODE-795"); break;
			case AUDIOMODE_AMRNB_102: strHint = _T("MODE-102"); break;
			case AUDIOMODE_AMRNB_122: strHint = _T("MODE-122"); break;
			case AUDIOMODE_AMRNB_SID: strHint = _T("MODE-SID"); break;
			}
		}
		break;
		case SDAUDIOTYPE_AMRWB:
		{
			switch(dwAudioSubType) 
			{
			case AUDIOMODE_AMRWB_660:  strHint = _T("MODE-660");  break;
			case AUDIOMODE_AMRWB_885:  strHint = _T("MODE-885");  break;
			case AUDIOMODE_AMRWB_1265: strHint = _T("MODE-1265"); break;
			case AUDIOMODE_AMRWB_1425: strHint = _T("MODE-1425"); break;
			case AUDIOMODE_AMRWB_1585: strHint = _T("MODE-1585"); break;
			case AUDIOMODE_AMRWB_1825: strHint = _T("MODE-1825"); break;
			case AUDIOMODE_AMRWB_1985: strHint = _T("MODE-1985"); break;
			case AUDIOMODE_AMRWB_2305: strHint = _T("MODE-2305"); break;
			case AUDIOMODE_AMRWB_2385: strHint = _T("MODE-2385"); break;
			case AUDIOMODE_AMRWB_SID:  strHint = _T("MODE-SID");  break;
			}
		}
		break;
		case SDAUDIOTYPE_DTS:
		{
			switch(dwAudioSubType)
			{
			case AUDIOTYPE_DTS2: strHint = _T("DTS2");  break;
			case AUDIOTYPE_DTS1: strHint = _T("DTS1");  break;
			case AUDIOTYPE_DTS0: strHint = _T("DTS0");  break;
			case AUDIOTYPE_DTS3: strHint = _T("DTS3");  break;  
			}
		}
		break;
		case SDAUDIOTYPE_SWFFLV:
		{		
			switch(dwAudioSubType)
			{
			case AUDIOTYPE_SWFFLV_MP3_MPEG1: strHint = _T("MP3-MPEG1");		break;
			case AUDIOTYPE_SWFFLV_MP3_MPEG2: strHint = _T("MP3-MPEG2");		break;
			case AUDIOTYPE_SWFFLV_MP3_MPEG25:strHint = _T("MP3-MPEG2.5");	break;
			case AUDIOTYPE_SWFFLV_AAC_LC:	 strHint = _T("MPEG4-AAC-LC");  break;
			case AUDIOTYPE_SWFFLV_AAC_MAIN:	 strHint = _T("MPEG4-AAC-MIAN");break;
			case AUDIOTYPE_SWFFLV_AAC_LTP:   strHint = _T("MPEG4-AAC-LC");  break;
			case AUDIOTYPE_SWFFLV_AAC_SSR:	 strHint = _T("MPEG4-AAC-LC");  break;
			case AUDIOTYPE_SWFFLV_PCMLE:     strHint = _T("PCM-LE");		break;  
			case AUDIOTYPE_SWFFLV_PCMBE:     strHint = _T("PCM-BE");		break;  
			case AUDIOTYPE_NELLYMOSER:       strHint = _T("NELLYMOSER");	break;   
			case AUDIOTYPE_SWFFLV_ADPCM4BIT: strHint = _T("ADPCM-4BIT");	break;
			}
		}
		break;
		case SDAUDIOTYPE_WINDOWS_MEDIA:
		{		
			switch(dwAudioSubType)
			{
			case AUDIOTYPE_WMA9:		 strHint = _T("WMA9");				 break;
			case AUDIOTYPE_WMA10:		 strHint = _T("WMA10-Professional"); break;
			case AUDIOTYPE_WMA9_LOSSLESS:strHint = _T("WMA9-Lossless");		 break;
			case AUDIOTYPE_WMA9_VOICE:	 strHint = _T("WMA9-Voice");		 break;
			case AUDIOTYPE_WMA9_ACELP:	 strHint = _T("WMA9-ACELP");		 break;
			}
		}
		break;
		default:
			break;
	}
	return strHint;
};

#endif // !defined(__H__SDVADefineEx__H__)
