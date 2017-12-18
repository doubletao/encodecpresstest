#pragma once
#include "IVideoEncoder.h"
struct sInputParams;
class CEncodingPipeline;
class INTELCODECAPI CIntelVideoEncoderCPUHW : public IVideoEncoder
{
public:
	CIntelVideoEncoderCPUHW();
	~CIntelVideoEncoderCPUHW();
	int GetVersion() { return 0; };
	void SetBufferSize() {};

	bool Init(const SVideoMediaInfo *pDesVideoInfo);

	// 设置视频采样系数
	//pInImageInfo: 输入无压缩帧参数
    bool SetInfo(const SVideoFrameImageBufInfo *pInImageInfo);

	// 输入一帧数据，其颜色格式与大小要与初始化相同
	bool PutFrame(const uint8_t* pFrameBuffer, const SRFrameInfo* pFrameInfo, bool bForceToKeyFrame = false);

	// 模式1时在输入最后一帧数据后调用，可以保证编码器输出全部输入帧
	bool GetEnd();

	// 获取压缩帧数据
	bool GetFrame(uint8_t* &pFrameBuffer, SRFrameInfo *pFrameInfo);

	bool Release();
private:
	bool SWMediaInfoToParams(const SVideoMediaInfo *pVideoMediaInfo);

    CEncodingPipeline *m_pVideoEncoder;

	sInputParams  *m_Params;

	int   m_nTargetUsage;

	char m_pFrameBuffer[720*576*2];
	int  nframe;
};

