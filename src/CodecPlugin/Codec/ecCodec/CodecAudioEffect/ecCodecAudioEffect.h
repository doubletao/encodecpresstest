#pragma once
#include "ecCodec.h"
#include "IecCodecAudioEffect.h"
#include "speex\speex_preprocess.h"

//一个简单的频率均衡器实现
class ecCodecAudioEquliazer
	: public IecCodecAudioEquliazer
{
protected:
	int m_nSamplePerSec;
	int m_nChannelCount;
public:
	ecCodecAudioEquliazer();
	virtual ~ecCodecAudioEquliazer();

	// 初始化均衡器
	// 默认10个频段，一般用默认值就好
	virtual bool InitAudioEquliazer(int nSamplePerSec, int nChannelCount, int nBand = 10);

	//释放
	virtual bool Release();

	// 设定指定频段指定声道的value增益
	virtual bool SetEqValue(int nBandIndex, int nChIndex, float fValue);

	//执行均衡
	virtual int DoEquliazer(const SD_UINT8 * pAudioBuf, int nBufSize);

	//获取设置
	virtual int GetEqBandCount();

	//获取设置
	virtual float GetEqValue(int nBandIndex, int nChIndex);
};

//一个简单的回声特技的实现(注意，回声处理器目前默认按照16位pcm格式处理)
class ecCodecAudioResound : public IecCodecAudioResound
{
protected:
	int m_nDelay;//毫秒(ms)
	float m_fFailing;//回声衰减系数
	int * m_pLastAudio;//用来存储回声buf
	int m_nLastAudioSampleCount;//回声bufsize
	int m_nSamplePerSec;
	int m_nChannelCount;
	int m_nWritePos;
	int m_nReadPos;
public:
	ecCodecAudioResound();
	virtual ~ecCodecAudioResound();

	//初始化
	virtual bool InitialAudioResound(int nSamplePerSec, int nChannelCount);

	//设置参数
	virtual bool SetParam(int nDelay, float fKeep);

	//执行
	virtual bool DoResound(const SD_UINT8 * pAudioBuf, int nBufSize);

	//释放
	virtual bool Release();
};

//一个简单的响度均衡的实现(注意，回声处理器目前默认按照16位pcm格式处理)
class ecCodecAudioVolumeAvg : public IecCodecAudioVolumeAvg
{
protected:
	int m_nVolume;
	float m_fSacal;
	float m_nAverageVolume;
public:
	ecCodecAudioVolumeAvg();
	virtual ~ecCodecAudioVolumeAvg();

	//初始化(目前没有用)
	virtual bool InitialAudioVolumeAvg(int nSamplePerSec, int nChannelCount);

	//设置参数
	virtual bool SetParam(float fVolume);

	//执行
	virtual bool DoVolumeAvg(const SD_UINT8 * pAudioBuf, int nBufSize);

	//释放
	virtual bool Release();
};

//一个简单的降噪
class ecCodecAudioDenoise : public IecCodecAudioDenoise
{
protected:
	SpeexPreprocessState * m_pDenoiseSpeex;
	float m_fDenoiseDb;
public:
	ecCodecAudioDenoise();
	virtual ~ecCodecAudioDenoise();

	//初始化(目前没有用)
	virtual bool InitialAudioDenoise(int nSamplePerSec, int nChannelCount);

	//设置参数
	virtual bool SetParam(float fDenoiseDb);

	//执行
	virtual bool DoDenoise(const SD_UINT8 * pAudioBuf, int nBufSize);

	//释放
	virtual bool Release();
};
