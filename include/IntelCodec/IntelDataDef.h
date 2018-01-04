#pragma once

struct IntelVideoMediaInfo	// 视频基本属性
{
	unsigned int				dwStruSize;					// 结构大小
	unsigned int				dwWidth;					// 图像宽度（水平分辨率）
	unsigned int				dwHeight;					// 图像高度（垂直分辨率）
	unsigned int				dwStandardRate;				// 基本帧频
	unsigned int				dwStandardScale;			// 系数（用于帧序号计算）同
	unsigned int				dwDataRateInBitsPerSec;		// 码率, based on *****bits/S******	// Mpeg专用设置
	unsigned int				dwGOPSize;					// IBP帧压缩类型时的IBP帧组大小		// Mpeg专用设置
	unsigned int				dwReferencePeriod;			// IBP帧压缩类型时IP帧的间隔周期。	// Mpeg专用设置
	bool					bIsClipped;					// true:Y(8bit)[16-235]/(10bit)[64,940]---normal, false:Y[0-255][0-1023]---KEY; maybe Cb/Cr
	unsigned int				dwDisplayWidth;				// 视频显示幅宽度值
	unsigned int				dwDisplayHeight;			// 视频显示幅高度值
	unsigned int				dwMaxDataRateInBitsPerSec;	// 最大码率, based on *****bits/S******
	unsigned int				dwMinDataRateInBitsPerSec;	// 最小码率, based on *****bits/S******

	IntelVideoMediaInfo()
	{
		dwStruSize = sizeof(IntelVideoMediaInfo);
		dwWidth = 720;
		dwHeight = 576;
		dwStandardRate = 25;
		dwStandardScale = 1;
		dwDataRateInBitsPerSec = 25000000;
		dwGOPSize = 14;
		dwReferencePeriod = 2;
		bIsClipped = true;
		dwDisplayWidth = 4;
		dwDisplayHeight = 3;
		dwMaxDataRateInBitsPerSec = 0;
		dwMinDataRateInBitsPerSec = 0;
	};
};

struct IntelVideoFrameImageBufInfo	//视频帧图像数据块属性
{
	unsigned int		dwXSize;								// 图象宽度像素数量
	unsigned int		dwYSize;								// 图象高度像素数量
	unsigned int		dwScanXByteSize;						// 跨距

	IntelVideoFrameImageBufInfo()
	{
		dwXSize = 0;
		dwYSize = 0;
		dwScanXByteSize = 0;
	};
};

// 帧数据描述
struct IntelFrameInfo
{
	//结构版本
	unsigned int				iVersion;		// 结构版本号。		4---4[序列化占用字节－序列化位置]
	unsigned int				iSize;			// 帧数据大小		4---16
	unsigned int 				dwFrameIndex;	// 帧数据流顺序		4---28
	unsigned int 				dwFrameNum;		// 视频/音频帧数量	4---32
	unsigned int 				iSamplesOffset;	// 标识RawAudio音频、视频帧中有效采样的偏移数，大于0表示从开始偏移，小于0表示从尾部开始向前偏移		4---36
	unsigned long long				qwDTS;			// 解码时间(90Khz单位)	8---44
	unsigned long long				qwPTS;			// 展现时间(90Khz单位)	8---52
	unsigned long long				qwDuration;		// 持续时间(90Khz单位)	8---6
	unsigned int				dwShowIndex;	// 帧数据显示顺序			4---104
	int						extradata_size;
	int						nFrameType;

	IntelFrameInfo()
	{
		iVersion = 1;
		iSize = 0;
		dwFrameNum = 1;
		dwShowIndex = 0; // 表示帧数据显示顺序无效
		qwDTS = -1;
		qwPTS = -1; // 表示帧数据展现顺序无效
		qwDuration = 0; // 表示帧数据持续时间未知

		iSamplesOffset = 0;

		extradata_size = 0;
	};
};