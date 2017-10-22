#ifndef __H__IVIDEOENCODER__H__
#define __H__IVIDEOENCODER__H__

#include "VACommonDefine.h"
//-----------------------------------------------------------------------------------------------//
class IVideoEncoder
{
public:
	IVideoEncoder() {};
	virtual ~IVideoEncoder() {};

	// 初始化编码器
	// pDesVideoInfo:编码格式描述
	virtual bool InitVideoEncoder(const SVideoMediaInfo *pDesVideoInfo) = 0;

	// 设置视频采样系数
	//pVideoBufInfo: 输入无压缩帧参数
	virtual bool SetVideoFrameBufInfo(const SVideoFrameImageBufInfo *pVideoBufInfo) = 0;

	// 输入一帧数据，其颜色格式与大小要与初始化相同
	// 在输入一帧数据后，必须连续调用GetCompressFrame()直到其返回值为false，才能再次输入新数据
	// pFrameBuffer:输入无压缩帧数据
	// pFrameInfo:输入无压缩帧数据帧信息
	// bForceToKeyFrame:强制将当前帧编码为关键帧
	virtual bool PutFrame(const SW_UINT8* pFrameBuffer, const SRFrameInfo* pFrameInfo, bool bForceToKeyFrame = false) = 0;

	// 模式1时在输入最后一帧数据后调用，可以保证编码器输出全部输入帧
	// 注意该函数需要在GetCompressFrame函数已经不能获取到输出帧时调用, 即PutFrame,GetCompressFrame，SetEndofInput，GetCompressFrame，不能PutFrame,SetEndofInput,GetCompressFrame
	virtual bool SetEndofInput() = 0;

	// 获取压缩帧数据
	// 返回值为dwSYCODEC_NEED_MOREDATA时需要继续使用PutFrame输入新的数据
	// 编码得到的压缩帧数据指针(指向由编解码模块内部分配的内存,需要调用者自己保存指针内容)
	// pFrameBuffer :压缩帧缓存
	// pFrameInfo :输出压缩帧信息
	virtual bool GetCompressFrame(SW_UINT8* &pFrameBuffer, SRFrameInfo *pFrameInfo) = 0;

	virtual bool Release() = 0;
};

#endif 