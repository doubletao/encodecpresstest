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
