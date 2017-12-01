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
