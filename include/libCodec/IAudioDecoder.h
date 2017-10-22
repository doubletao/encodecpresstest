//==============================================================================
// IAudioCodec.h
// 该文件定义了:
// 1.音频解码器IAudioDecoder();
//==============================================================================

#ifndef _H_IAUDIODECODER_H
#define _H_IAUDIODECODER_H

#include "VACommonDefine.h"
//-----------------------------------------------------------------------------------------------//
class IAudioDecoder
{
public:
	IAudioDecoder() {};
	virtual ~IAudioDecoder() {};
	
	// 初始化解码器
	// 返回值：1 成功、0 错误
	// sAudioInfo	// 压缩音频信息
	virtual bool InitAudioDecoder(const SAudioMediaInfo &sAudioInfo) = 0; 	

	// 设置输出音频格式
	virtual bool SetAudioSamplesBufInfo(SAudioSamplesBufInfo *pAudioBufInfo) = 0;

	// 输入压缩音频数据(按帧为单位输入,带时间信息补偿)
	// 返回值：1 成功、0 错误
	// pData,					// 压缩帧数据
	// pFrameInfo				// 压缩帧信息
	virtual bool PutFrame(const SW_UINT8* pData, const SRFrameInfo* pFrameInfo) = 0;

	// 得到解码后的音频PCM采样,采样格式由SetAudioSamplesBufInfo决定
	// 返回值:PCM采样的字节数量
	virtual int  GetSample(SW_UINT8* &lpBuffer) = 0;

	virtual bool Release() = 0;
};
#endif // _H_IAUDIODECODER_H
	
