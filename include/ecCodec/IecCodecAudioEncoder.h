#pragma once
#include "ecCodec.h"
class EASY_CODEC_API_EXPORT IecCodecAudioEncoder
{
public:
	// 初始化编码器
	// 返回值：1 成功、0 错误
	//sAudioInfo:目标音频信息
	virtual bool InitAudioEncoder(const SDAudioMediaInfo &sAudioInfo) = 0;

	// 设置输入音频缓存格式
	// pAudioBufInfo:设置无压缩音频的参数
	virtual bool SetAudioSamplesBufInfo(const SDAudioSamplesBufInfo *pAudioBufInfo) = 0;

	// 送入音频数据
	// 返回值：1 成功、 0 错误
	// 说明：PCM音频数据信息与SAudioSamplesBufInfo描述一致
	// pData:PCM音频数据
	// iSize:PCM音频数据大小
	// emInputFlag:1结束、0未结束
	virtual bool WriteSample(const SD_UINT8* pData, SD_UINT32 iSize, bool emInputFlag) = 0;

	// 输入最后一帧数据后调用，可以保证编码器输出全部输入帧
	// 注意该函数需要在GetCompressFrame函数已经不能获取到输出帧时调用, 即WriteSample,GetCompressFrame，SetEndofInput，GetCompressFrame，不能WriteSample,SetEndofInput,GetCompressFrame
	virtual bool SetEndofInput() = 0;

	// 获取压缩数据
	// 返回值：1 成功、 0 错误
	//pData:压缩帧数据(指向由编解码模块内部分配的内存)
	//pFrameInfo:压缩帧信息
	virtual bool GetCompressFrame(SD_UINT8* &pData, SDRFrameInfo* pFrameInfo) = 0;

	virtual bool Release() = 0;
};

