#pragma once
#include "..\libcodec\IVideoDecoder.h"
class CDecodingPipeline;
struct sInputParamsDecoding;
class INTELCODECAPI CIntelVideoDecoderCPUHW : public IVideoDecoder
{
public:
	CIntelVideoDecoderCPUHW();
	~CIntelVideoDecoderCPUHW();
	int GetVersion() { return 0; };
	void SetBufferSize() {};
	// 初始化解码器
	// pSrcVideoInfo 初始解码器一些信息
	bool Init(const SVideoMediaInfo *pSrcVideoInfo);

	//
	bool SetInfo(const SVideoFrameImageBufInfo *pOutImageInfo);

	// lpFrameBuffer 压缩数据
	// pFrameInfo 压缩数据的帧信息
	bool PutFrame(const uint8_t *pFrameBuffer, const SRFrameInfo *pFrameInfo);

	// 最后一帧数据后调用，可以保证解码器输出全部输入帧
	bool GetEnd();

	// 得到解码数据
	// 解码得到的无压缩帧数据指针(指向由编解码模块内部分配的内存,需要调用者自己保存指针内容)
	bool GetFrame(uint8_t* &lpFrameBuffer, SRFrameInfo *pFrameInfo);
	
	bool Release();
private:
	CDecodingPipeline    *m_pVideoDecoder;

	sInputParamsDecoding *m_Params;

	bool                 m_IsHeade;           
};
