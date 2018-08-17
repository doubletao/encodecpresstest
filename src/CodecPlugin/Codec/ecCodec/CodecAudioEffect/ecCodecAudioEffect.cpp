#pragma once
#include "ecCodecAudioEffect.h"
#include "eq.h"

ecCodecAudioEquliazer::ecCodecAudioEquliazer()
	: m_nSamplePerSec(48000)
	, m_nChannelCount(2)
{

}

ecCodecAudioEquliazer::~ecCodecAudioEquliazer()
{
	Release();
}

bool ecCodecAudioEquliazer::InitAudioEquliazer(int nSamplePerSec, int nChannelCount, int nBand)
{
	bool bRet = true;
	init_equliazer(nBand);
	return bRet;
}

bool ecCodecAudioEquliazer::Release()
{
	bool bRet = false;
	uninit_equliazer();
	return bRet;
}

bool ecCodecAudioEquliazer::SetEqValue(int nBandIndex, int nChIndex, float fValue)
{
	bool bRet = false;
	//set_eq_value(fValue, nBandIndex, nChIndex);
	set_eq_value(20.0f + fValue, -nBandIndex, nChIndex);
	set_eq_value(fValue, nBandIndex, nChIndex);

	return bRet;
}

int ecCodecAudioEquliazer::DoEquliazer(const SD_UINT8 * pAudioBuf, int nBufSize)
{
	int nRet = 0;
	nRet = do_equliazer((short *)pAudioBuf, nBufSize, m_nSamplePerSec, m_nChannelCount);
	return nRet;
}

int ecCodecAudioEquliazer::GetEqBandCount()
{
	int nRet = 0;
	nRet = get_eq_band_count();
	return nRet;
}

float ecCodecAudioEquliazer::GetEqValue(int nBandIndex, int nChIndex)
{
	float fRet = 0;
	fRet = get_eq_value(nBandIndex, nChIndex);
	return fRet;
}

ecCodecAudioResound::ecCodecAudioResound()
	: m_nDelay(0)
	, m_fFailing(0)
	, m_pLastAudio(nullptr)
	, m_nLastAudioSampleCount(0)
	, m_nWritePos(0)
	, m_nReadPos(0)
{
}

ecCodecAudioResound::~ecCodecAudioResound()
{
	Release();
}

bool ecCodecAudioResound::InitialAudioResound(int nSamplePerSec, int nChannelCount)
{
	m_nSamplePerSec = nSamplePerSec;
	m_nChannelCount = nChannelCount;
	return true;
}

bool ecCodecAudioResound::SetParam(int nDelay, float fKeep)
{
	if (nDelay < 50)
	{
		nDelay = 50;
	}
	if (nDelay > 900)
	{
		nDelay = 900;
	}
	if (m_nDelay != nDelay)
	{
		m_nDelay = nDelay;
		m_nLastAudioSampleCount = 10 * m_nSamplePerSec * m_nChannelCount;//按照10秒的采样数来开辟空间，回声延迟最大到900ms
		m_nReadPos = 0;//从头开始读
		m_nWritePos = nDelay * m_nSamplePerSec / 1000 * m_nChannelCount;//从延时位置开始写
		if (!m_pLastAudio)
		{
			m_pLastAudio = new int[m_nLastAudioSampleCount];
			memset(m_pLastAudio, 0, m_nLastAudioSampleCount * sizeof(int));
		}
	}
	m_fFailing = fKeep;
	return true;
}

bool ecCodecAudioResound::DoResound(const SD_UINT8 * pAudioBuf, int nBufSize)
{
	int nInputSampleCount = nBufSize / sizeof(int);
	if (nInputSampleCount > m_nLastAudioSampleCount)
	{
		//一次进来的数据量过多，buf要爆
		nInputSampleCount = m_nLastAudioSampleCount;
	}
	int * pAudio = (int*)pAudioBuf;
	int * pAudioRes = new int[nInputSampleCount];
	memset(pAudioRes, 0, nInputSampleCount * sizeof(int));
	//取出
	if (m_nReadPos + nInputSampleCount <= m_nLastAudioSampleCount)
	{
		memcpy(pAudioRes, m_pLastAudio + m_nReadPos, nInputSampleCount * sizeof(int));
		m_nReadPos += nInputSampleCount;
	}
	else
	{
		int nRemain = m_nLastAudioSampleCount - m_nReadPos;
		memcpy(pAudioRes, m_pLastAudio + m_nReadPos, nRemain * sizeof(int));
		m_nReadPos = 0;
		memcpy(pAudioRes + nRemain, m_pLastAudio + m_nReadPos, (nInputSampleCount - nRemain)* sizeof(int));
		m_nReadPos += nInputSampleCount - nRemain;
	}
	//写回
	if (m_nWritePos + nInputSampleCount <= m_nLastAudioSampleCount)
	{
		memcpy(m_pLastAudio + m_nWritePos, pAudio, nInputSampleCount * sizeof(int));
		m_nWritePos += nInputSampleCount;
	}
	else
	{
		int nRemain = m_nLastAudioSampleCount - m_nWritePos;
		memcpy(m_pLastAudio + m_nWritePos, pAudio, nRemain * sizeof(int));
		m_nWritePos = 0;
		memcpy(m_pLastAudio + m_nWritePos, pAudio + nRemain, (nInputSampleCount - nRemain)* sizeof(int));
		m_nWritePos += nInputSampleCount - nRemain;
	}
	//叠加
	for (int i = 0; i < nInputSampleCount; i++)
	{
		pAudio[i] += pAudioRes[i] * m_fFailing;
	}
	delete pAudioRes;
	pAudioRes = nullptr;
	return true;
}

bool ecCodecAudioResound::Release()
{
	m_nDelay = 0;
	m_fFailing = 0;
	m_nWritePos = 0;
	m_nReadPos = 0;
	if (m_pLastAudio)
	{
		delete m_pLastAudio;
		m_pLastAudio = nullptr;
	}
	m_nLastAudioSampleCount = 0;
	return true;
}

ecCodecAudioVolumeAvg::ecCodecAudioVolumeAvg()
	: m_nVolume(0)
	, m_fSacal(0)
	, m_nAverageVolume(0)
{
}

ecCodecAudioVolumeAvg::~ecCodecAudioVolumeAvg()
{
	Release();
}

bool ecCodecAudioVolumeAvg::InitialAudioVolumeAvg(int nSamplePerSec, int nChannelCount)
{
	return true;
}

bool ecCodecAudioVolumeAvg::SetParam(float fVolume)
{
	m_nVolume = fVolume;
	return true;
}

bool ecCodecAudioVolumeAvg::DoVolumeAvg(const SD_UINT8 * pAudioBuf, int nBufSize)
{
	int nNum = nBufSize >> 1;
	short *pAudio = (short*)pAudioBuf;
	bool bScal = true;
	for (int i = 0; i < nNum; i++)
	{
		if (bScal)
		{
			int nCurVolum = abs(pAudio[i]);
			if (nCurVolum > 0)
			{
				m_nAverageVolume = (m_nAverageVolume * 999 + nCurVolum) / 1000.0;
				m_fSacal = m_nVolume / m_nAverageVolume;
			}
		}
		bScal = !bScal;
		pAudio[i] *= m_fSacal;
	}
	return true;
}

bool ecCodecAudioVolumeAvg::Release()
{
	m_nVolume = 0;
	m_fSacal = 0;
	m_nAverageVolume = 0;
	return true;
}

ecCodecAudioDenoise::ecCodecAudioDenoise()
	: m_pDenoiseSpeex(nullptr)
	, m_fDenoiseDb(0.0f)
{
}

ecCodecAudioDenoise::~ecCodecAudioDenoise()
{
	Release();
}

bool ecCodecAudioDenoise::InitialAudioDenoise(int nSamplePerSec, int nChannelCount)
{
	m_pDenoiseSpeex = speex_preprocess_state_init(nSamplePerSec * nChannelCount / 25, nSamplePerSec);//这里写死了25帧率和32位音频
	BOOL bDenoise = TRUE;
	speex_preprocess_ctl(m_pDenoiseSpeex, SPEEX_PREPROCESS_SET_DENOISE, &bDenoise);
	speex_preprocess_ctl(m_pDenoiseSpeex, SPEEX_PREPROCESS_SET_NOISE_SUPPRESS, &m_fDenoiseDb);	//设置最大噪声衰减，以db为单位

	int i = 0;
	speex_preprocess_ctl(m_pDenoiseSpeex, SPEEX_PREPROCESS_SET_AGC, &i);
	i = 8000;
	speex_preprocess_ctl(m_pDenoiseSpeex, SPEEX_PREPROCESS_SET_AGC_LEVEL, &i);
	i = 0;
	speex_preprocess_ctl(m_pDenoiseSpeex, SPEEX_PREPROCESS_SET_DEREVERB, &i);
	float f = .0;
	speex_preprocess_ctl(m_pDenoiseSpeex, SPEEX_PREPROCESS_SET_DEREVERB_DECAY, &f);
	f = .0;
	speex_preprocess_ctl(m_pDenoiseSpeex, SPEEX_PREPROCESS_SET_DEREVERB_LEVEL, &f);
	return true;
}

bool ecCodecAudioDenoise::SetParam(float fDenoiseDb)
{
	m_fDenoiseDb = fDenoiseDb;
	speex_preprocess_ctl(m_pDenoiseSpeex, SPEEX_PREPROCESS_SET_NOISE_SUPPRESS, &m_fDenoiseDb);	//设置最大噪声衰减，以db为单位
	return true;
}

bool ecCodecAudioDenoise::DoDenoise(const SD_UINT8 * pAudioBuf, int nBufSize)
{
	if (m_pDenoiseSpeex)
	{
		speex_preprocess_run(m_pDenoiseSpeex, (short *)pAudioBuf);
	}
	return true;
}

bool ecCodecAudioDenoise::Release()
{
	if (m_pDenoiseSpeex)
	{
		speex_preprocess_state_destroy(m_pDenoiseSpeex);
		m_pDenoiseSpeex = nullptr;
	}
	m_fDenoiseDb = 0.0f;
	return true;
}
