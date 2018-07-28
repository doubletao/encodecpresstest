#pragma once
#include "ecCodec.h"
#include "IecCodecAudioEffect.h"

//一个简单的均衡器实现
class ecCodecAudioEquliazer
	: public IecCodecAudioEquliazer
{
public:
	virtual ~ecCodecAudioEquliazer() {}

	// 初始化均衡器
	// 默认10个频段，一般用默认值就好
	virtual bool InitAudioEquliazer(int nBand = 10);

	//释放
	virtual bool Release();

	// 设定指定频段指定声道的value增益
	virtual bool SetEqValue(int nBandIndex, int nChIndex, float fValue);

	//执行均衡
	virtual int DoEquliazer(const SD_UINT8 * pAudioBuf, int nBufSize, int nSamplePerSec, int nChannelCount);

	//获取设置
	virtual int GetEqBandCount();

	//获取设置
	virtual float GetEqValue(int nBandIndex, int nChIndex);
};

