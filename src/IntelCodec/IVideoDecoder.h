#ifndef __H__IVIDEODECODER__H__
#define __H__IVIDEODECODER__H__

#include "VACommonDefine.h"
//-----------------------------------------------------------------------------------------------//
class IVideoDecoder
{
public:
	IVideoDecoder() {};
	virtual ~IVideoDecoder() {};

	// 初始化解码器
	// pSrcVideoInfo: 视频源格式描述
	virtual bool InitVideoDecoder(const SVideoMediaInfo	*pSrcVideoInfo) = 0;

	// 设置输出视频格式
	// pOutBufInfo:解码输出帧参数
	virtual bool SetVideoFrameBufInfo(const SVideoFrameImageBufInfo *pOutBufInfo) = 0;

	// 输入压缩帧数据
	// pFrameBuffer:输入压缩帧数据
	// pFrameInfo:输入压缩帧描述
	virtual bool PutVideoFrame(const SW_UINT8 *pFrameBuffer, const SRFrameInfo *pFrameInfo) = 0;

	// 模式1时在输入最后一帧数据后调用，可以保证解码器输出全部输入帧
	virtual bool SetEndofInput() = 0;

	// 得到解码数据
	// 返回值：
	// 解码得到的无压缩帧数据指针(指向由编解码模块内部分配的内存,需要调用者自己保存指针内容)
	// 返回值为dwCODEC_NEED_MOREDATA时需要继续使用PutFrame输入新的数据
	// pFrameBuffer:解压缩帧数据
	// pFrameInfo:输出帧信息
	virtual bool GetUnCompressFrame(SW_UINT8* &lpFrameBuffer, SRFrameInfo *pFrameInfo) = 0;

	virtual bool Release() = 0;
};
#endif // __H__IVIDEODECODER__H__