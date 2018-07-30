#pragma once
#include "ecCodec.h"

//一个简单的均衡器实现
class IecCodecAudioEquliazer
{
public:
	virtual ~IecCodecAudioEquliazer() {}

	// 初始化均衡器
	// nBand频段数，默认10个频段，一般用默认值就好
	virtual bool InitAudioEquliazer(int nSamplePerSec, int nChannelCount, int nBand = 10) = 0;

	//设定指定频段指定声道的value增益，fValue范围-20.0f~20.0f,建议使用范围-16.0~16.0
	virtual bool SetEqValue(int nBandIndex, int nChIndex, float fValue) = 0;

	//执行均衡
	virtual int DoEquliazer(const SD_UINT8 * pAudioBuf, int nBufSize) = 0;

	//获取设置
	virtual int GetEqBandCount() = 0;

	//获取设置
	virtual float GetEqValue(int nBandIndex, int nChIndex) = 0;

	//释放
	virtual bool Release() = 0;
};

