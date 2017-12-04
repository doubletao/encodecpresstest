#pragma once
#include "ecCodec.h"
class IecCodecProtocolEncoder
{
public:
	//-----------------------------------------------------------------------------------------------//	
	// 设置扩展模式的编码目标信息
	// pStreamMediaInfo:  目标格式扩展描述信息
	// pFileName:		  目标文件名
	virtual bool SetSinkFile(const SDStreamMediaInfo *pStreamMediaInfo, const char* pFileName) = 0;

	// 获取当前文件信息
	virtual bool GetMediaInfo(SDStreamMediaInfo *pStreamMediaInfo) = 0;

	//-----------------------------------------------------------------------------------------------//
	// 设置编码的输入视频和音频数据参数
	// psVideoPara:		输入的无压缩视频帧参数
	// sResamplerPara:  在需要视频重采样的时候，重采样模式参数。
	virtual bool SetVideoFrameBufInfo(const SDVideoFrameImageBufInfo *pVideoBufInfo, const SDResamplerPara *pResamplerInfo) = 0;
	// 获取先前所设置的
	virtual bool GetVideoFrameBufInfo(SDVideoFrameImageBufInfo *pVideoInfo, SDResamplerPara *pResamplerInfo) = 0;

	// psAudioPara:		输入的无压缩音频参数
	virtual bool SetAudioSamplesBufInfo(const SDAudioSamplesBufInfo *pAudioBufInfo) = 0;
	// 获取先前所设置的解码音频采样数据参数
	virtual bool GetAudioSamplesBufInfo(SDAudioSamplesBufInfo *pAudioBufInfo) = 0;
	//-----------------------------------------------------------------------------------------------//

	//-----------------------------------------------------------------------------------------------//
	// 当前格式是否支持直接写入视频压缩数据
	// 需要保证写入的视频压缩数据与编码设置相同，如码率、颜色格式等
	virtual bool IsCanWriteVideoFrame() = 0;

	// 当前格式是否支持直接写入音频压缩数据
	// 需要保证写入的音频压缩数据与编码设置相同，如格式、声道、采样率等
	virtual bool IsCanWriteAudioFrame() = 0;

public:
	//-----------------------------------------------------------------------------------------------//
	// 输入一个视频帧
	virtual bool PutVideoBuffer(const SD_UINT8* pFrameBuf,
		bool bForceToKeyFrame = false,					// 强制将当前帧编码为关键帧
		const SDRFrameInfo *pFrameInfo = NULL			// 帧信息
	) = 0;

	// 直接写入压缩视频数据
	// 要在bool IsCanWriteVideoFrame()返回true时，才能调用该接口
	// 对帧间相关格式的第1帧应该为I帧，才能保证生成的文件可以正确解码
	virtual bool PutVideoFrame(const SD_UINT8* pFrameBuf,
		const SDRFrameInfo *pFrameInfo
	) = 0;

	// 输入一段PCM音频采样
	virtual bool PutAudioSamples(const SD_UINT8* pSamplesBuf,
		SD_UINT32 dwSampleNum						    // 音频采样数量
	) = 0;

	// 直接写入压缩音频数据
	// 要在bool IsCanWriteAudioFrame()返回true时，才能调用该接口
	virtual bool PutAudioFrame(const SD_UINT8* pFrameBuf,
		const SDRFrameInfo *pFrameInfo                   // 音频帧描述
	) = 0;

	// 关闭编码器
	virtual bool Release() = 0;
};

