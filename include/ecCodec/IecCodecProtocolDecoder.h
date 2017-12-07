#pragma once
#include "ecCodec.h"

typedef int(*PCALLBACKREADPACKET)(void *,unsigned char *,int);
typedef int(*PCALLBACKINTERRUPT)(PVOID pM);

class IecCodecProtocolDecoder
{
public:
	virtual ~IecCodecProtocolDecoder() {}

	// 设置输入路径
	// 说明：必须先调用该函数并调用成功，才能继续调用其它函数
	// 参数：
	// pFullPath 可能是本地文件或网络地址
	virtual bool SetSourcePath(const char * pFullPath, void * pUserParam = nullptr, PCALLBACKINTERRUPT pCallbackInterupt = nullptr) = 0;

	// 设置输入回调
	// 说明：主要供网络流使用，只有数据包而没有具体文件或流地址的情况下使用
	virtual bool SetSourceCallback(PCALLBACKREADPACKET pCallbackReadPkt, void * pUserParam = nullptr, PCALLBACKINTERRUPT pCallbackInterupt = nullptr) = 0;

	//-----------------------------------------------------------------------------------------------//
	// 解码器信息获取------获取输入文件的信息
	//-----------------------------------------------------------------------------------------------//
	// 获取输入文件的全局流信息, 
	// 说明：此时还未完全读取解码所需全部信息和索引
	virtual bool GetFileGlobalMediaInfo(SDStreamMediaInfo *psMediaInfo) = 0;

	//获取输入文件的信息(包括素材长度), 
	// 说明：所需要用的时间可能比只获取SDYGlobalStreamMediaInfo信息要长
	virtual bool GetFileGlobalMediaInfo(SDStreamMediaInfoEx *psMediaInfoEx) = 0;

	// 是否能够直接读取视频压缩数据
	virtual bool IsCanReadVideoFrame() = 0;
	// 是否能够直接读取音频压缩数据
	virtual bool IsCanReadAudioFrame() = 0;

	//-----------------------------------------------------------------------------------------------//
	// 解码器开始工作命令
	//-----------------------------------------------------------------------------------------------//	
	// 在调用其他除GetFileGlobalMediaInfo()外其他功能接口时，必须调用Start()以进行索引读取和解码器初始化等工作。
	// 在特定文件格式下可以降低GetMediaInfo()的开销。
	virtual bool Start() = 0;

	// 设置解码得到的无压缩视频数据参数
	// 说明：如果不调用，将没有视频输出; 在只需要获取音频的情况下, 不调用该函数可以占用较少的资源。
	// pVideoBufInfo: 输出的无压缩视频帧参数
	// sResamplerPara:    在需要视频重采样的时候，重采样模式参数。
	virtual bool SetVideoFrameBufInfo(const SDVideoFrameImageBufInfo *pVideoBufInfo, const SDResamplerPara *pResamplerPara) = 0;
	// 获取先前所设置的解码得到的无压缩视频数据参数
	virtual bool GetVideoFrameBufInfo(SDVideoFrameImageBufInfo *pVideoBufInfo, SDResamplerPara *pResamplerPara) = 0;
	// 根据SetVideoDecodePara输入的视频解码参数取得解码得到的无压缩视频帧占用的缓存字节数
	// 该函数需要在调用SetVideoDecodePara()后再调用
	virtual SD_UINT32 GetVideoBufferSize() = 0;

	// 设置视频解码器线程数量,不调用该函数由底层自动选择线程数量
	virtual bool SetVideoDecoderThread(SD_INT32 dwDecoderThread) = 0;
	virtual SD_INT32 GetVideoDecoderThread() = 0;

	// 设置解码得到的音频采样数据参数
	// 说明：如果不调用，将没有音频频输出; 在只需要获取视频的情况下, 不调用该函数可以占用较少的资源。
	virtual bool SetAudioSamplesBufInfo(const SDAudioMediaInfo *pAudioBufInfo) = 0;
	// 获取先前所设置的解码音频采样数据参数
	virtual bool GetAudioSamplesBufInfo(SDAudioSamplesBufInfo *pAudioBufInfo) = 0;

	//-----------------------------------------------------------------------------------------------//
	// 从解码器获取视频数据
	// 读取指定帧序号的视频解码数据
	// 说明：		缓存的大小需要通过函数GetVideoBufferSize()得到
	// pFrameBuf：	解码得到的无压缩数据(由调用者分配内存)
	// 注意：		如果将pFrameBuf设置为DY_NULL,可以只获取pFrameInfo而不解码
	virtual bool GetVideoBuffer(SD_UINT64 dwCurFrameShowIndex,
		SD_UINT8* pFrameBuf,
		SDRFrameInfo *pFrameInfo = NULL
	) = 0;

	// 该函数用于直接读取压缩数据，不对该帧进行解码
	// 调用改函数前需要调用bool IsCanReadVideoFrame()来确定当前格式是否支持读取压缩数据
	// pFrameBuf：压缩数据(由编解码模块内部分配内存)
	virtual bool GetVideoFrame(SD_UINT64 dwCurFrameStreamIndex,
		SD_UINT8* &pFrameBuf,
		SDRFrameInfo *pFrameInfo = NULL
	) = 0;

	//-----------------------------------------------------------------------------------------------//
	// 从解码器获取音频数据
	//-----------------------------------------------------------------------------------------------//

	// 读取指定采样长度的音频解码数据
	// 参数表：
	//		dwCurSamplePos：	获取音频采样的起始位置。
	//		(*pdwRetSampleNum)：实际读出的采样数量
	//		pSamplesBuf：		解压缩后的音频数据(由调用者分配内存)
	// 说明：	通常双声道下输出缓存排列为: 左,右
	//			5.1声道下输出缓存排列为:左,右,中置,左后,右后,低音  
	// 输出音频缓存排列由SetAudioDecodePara指定。
	virtual bool GetAudioSamples(SD_UINT32 dwCurSamplePos,
		SD_UINT32 dwSampleNum,
		SD_UINT8* pSamplesBuf,
		SD_UINT32* pdwRetSampleNum
	) = 0;

	// 该函数用于直接读取压缩音频帧数据，不对该帧进行解码
	// 说明：音频帧是指由数个采样组成的一个最小的压缩单位，类似视频帧
	//		 比如 mp1 音频帧由384个采样构成；Mpeg1 Layer3(mp3) 音频帧由1152个采样构成。
	//		 调用该函数前需要调用bool IsCanReadAudioFrame()来确定当前格式是否支持读取压缩数据
	//		dwCurFrameStreamIndex：	帧序号
	//		pFrameBuf:				压缩音频数据(由编解码模块内部分配内存)
	//		pFrameInfo:				帧信息描述
	virtual bool GetAudioFrame(SD_UINT32 dwCurFrameStreamIndex,
		SD_UINT8* &pFrameBuf,
		SDRFrameInfo *pFrameInfo
	) = 0;

	virtual SD_UINT32 GetAudioBufferSize() = 0;

	// 顺解方式取出下一帧画面及一帧画面对应的音频
	virtual bool GetVABuffer(SD_UINT8* pFrameBuf,
		SD_UINT8* pSamplesBuf,
		SD_UINT32* pdwRetSampleNum) = 0;

	//-----------------------------------------------------------------------------------------------//
	// 解码器关闭操作
	//-----------------------------------------------------------------------------------------------//
	// 说明：在SetSourceFile()一个新文件前，必须先调用该函数
	virtual bool Release() = 0;
};

