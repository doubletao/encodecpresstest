#pragma once
#include "ecCodec.h"
class EASY_CODEC_API_EXPORT IecCodecAudioDecoder
{
public:
	// 初始化解码器
	// 返回值：1 成功、0 错误
	// sAudioInfo	// 压缩音频信息
	virtual bool InitAudioDecoder(const SDAudioMediaInfo &sAudioInfo) = 0;

	// 设置输出音频格式
	virtual bool SetAudioMediaInfo(SDAudioMediaInfo * pAudioInfo) = 0;

	// 输入压缩音频数据(按帧为单位输入,带时间信息补偿)
	// 返回值：1 成功、0 错误
	// pData,					// 压缩帧数据
	// pFrameInfo				// 压缩帧信息
	virtual bool PutFrame(const SD_UINT8* pData, const SDRFrameInfo* pFrameInfo) = 0;

	virtual bool GetAudioMediaInfo(SDAudioMediaInfo * pAudioInfo) = 0;

	// 得到解码后的音频PCM采样,采样格式由SetAudioSamplesBufInfo决定
	// 返回值:成功则返回PCM采样的字节数量，
	//失败则返回负数
	//如果返回0，说明frame不足以凑足当前要求的采样数，需要继续put
	virtual int  GetSample(SD_UINT8* &lpBuffer, SD_UINT32 nSampleNum) = 0;

	//得到buffer大小
	virtual SD_UINT32 GetBufferSize() = 0;

	virtual bool IsInitialized() = 0;

	virtual bool Release() = 0;
};

