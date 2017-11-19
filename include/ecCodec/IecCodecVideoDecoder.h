#pragma once
#include "ecCodec.h"
class EASY_CODEC_API_EXPORT IecCodecVideoDecoder
{
public:
	// 初始化解码器
	// pSrcVideoInfo: 视频源格式描述
	virtual bool InitVideoDecoder(const SDVideoMediaInfo & pSrcVideoInfo) = 0;

	// 设置输出视频格式
	// pOutBufInfo:解码输出帧参数
	virtual bool SetVideoFrameBufInfo(const SDVideoFrameImageBufInfo *pOutBufInfo) = 0;

	// 输入压缩帧数据
	// pFrameBuffer:输入压缩帧数据
	// pFrameInfo:输入压缩帧描述
	virtual bool PutVideoFrame(const SD_UINT8 *pFrameBuffer, const SDRFrameInfo *pFrameInfo) = 0;

	// 模式1时在输入最后一帧数据后调用，可以保证解码器输出全部输入帧
	virtual bool SetEndofInput() = 0;

	// 得到解码数据
	// 返回值：
	// 解码得到的无压缩帧数据指针(指向由编解码模块内部分配的内存,需要调用者自己保存指针内容)
	// 返回值为dwCODEC_NEED_MOREDATA时需要继续使用PutFrame输入新的数据
	// pFrameBuffer:解压缩帧数据
	// pFrameInfo:输出帧信息
	// 返回值：>0成功，=0需要继续put，<0失败
	virtual int GetUnCompressFrame(SD_UINT8* &lpFrameBuffer, SDRFrameInfo *pFrameInfo) = 0;

	// 取得最近一次数据的时间戳（单位：毫秒）
	virtual double GetCurrentMilSecTimestamp(int num, int den) = 0;

	// 得到解码的流信息
	// 返回值：
	virtual bool GetVideoMediaInfo(SDVideoMediaInfo * mediaInfo) = 0;

	//得到buffer大小
	virtual SD_UINT32 GetBufferSize() = 0;

	virtual bool IsInitialized() = 0;

	virtual bool Release() = 0;
};

