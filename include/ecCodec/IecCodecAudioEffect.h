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

//一个简单的回声特技的实现
class IecCodecAudioResound
{
public:
	virtual ~IecCodecAudioResound() {}

	//初始化(目前没有用)
	virtual bool InitialAudioResound(int nSamplePerSec, int nChannelCount) = 0;

	//设置参数
	virtual bool SetParam(int nDelay, float fKeep) = 0;

	//执行
	virtual bool DoResound(const SD_UINT8 * pAudioBuf, int nBufSize) = 0;

	//释放
	virtual bool Release() = 0;
};

//一个简单的响度均衡的实现
class IecCodecAudioVolumeAvg
{
public:
	virtual ~IecCodecAudioVolumeAvg() {}

	//初始化(目前没有用)
	virtual bool InitialAudioVolumeAvg(int nSamplePerSec, int nChannelCount) = 0;

	//设置参数
	virtual bool SetParam(float fVolume) = 0;

	//执行
	virtual bool DoVolumeAvg(const SD_UINT8 * pAudioBuf, int nBufSize) = 0;

	//释放
	virtual bool Release() = 0;
};

//一个简单的降噪
class IecCodecAudioDenoise
{
public:
	virtual ~IecCodecAudioDenoise() {}

	//初始化(目前没有用)
	virtual bool InitialAudioDenoise(int nSamplePerSec, int nChannelCount) = 0;

	//设置参数
	virtual bool SetParam(float fDenoiseDb) = 0;

	//执行
	virtual bool DoDenoise(const SD_UINT8 * pAudioBuf, int nBufSize) = 0;

	//释放
	virtual bool Release() = 0;
};
