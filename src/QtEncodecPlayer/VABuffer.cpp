#include "VABuffer.h"
#include <assert.h>
#include <string>

static const int SAMPLE_SIZE = 4;

VABuffer::VABuffer()
	: m_pVideoBuf(nullptr)
	, m_nVideoSize(0)
	, m_pAudioBuf(nullptr)
	, m_nAudioSampleCount(0)
{
}

VABuffer::~VABuffer()
{
	Clear();
}

void VABuffer::Reset(size_t nVideoSize, size_t nAudioSampleCount)
{
	Clear();
	m_pVideoBuf = new unsigned char[nVideoSize];
	m_nVideoSize = nVideoSize;
	m_pAudioBuf = new unsigned char[nAudioSampleCount * SAMPLE_SIZE];
	m_nAudioSampleCount = nAudioSampleCount;
}

void VABuffer::Clear()
{
	delete[] m_pVideoBuf;
	m_pVideoBuf = nullptr;
	m_nVideoSize = 0;
	delete[] m_pAudioBuf;
	m_pAudioBuf = nullptr;
	m_nAudioSampleCount = 0;
}

void VABuffer::Copy(const VABuffer & va)
{
	Reset(va.m_nVideoSize, va.m_nAudioSampleCount);
	memcpy(m_pVideoBuf, va.m_pVideoBuf, m_nVideoSize);
	memcpy(m_pAudioBuf, va.m_pAudioBuf, m_nAudioSampleCount * SAMPLE_SIZE);
}

void VABuffer::CopyVideo(const unsigned char * pVideoBuf)
{
	assert(m_pVideoBuf);
	memcpy(m_pVideoBuf, pVideoBuf, m_nVideoSize);
}

void VABuffer::CopyAudio(const unsigned char * pAudioBuf)
{
	assert(m_pAudioBuf);
	memcpy(m_pAudioBuf, pAudioBuf, m_nAudioSampleCount * SAMPLE_SIZE);
}

size_t VABuffer::GetVideoBufSize()
{
	return m_nVideoSize;
}

size_t VABuffer::GetAudioSampleCount()
{
	return m_nAudioSampleCount;
}

unsigned char * VABuffer::GetVideoBuf()
{
	return m_pVideoBuf;
}

unsigned char * VABuffer::GetAudioBuf()
{
	return m_pAudioBuf;
}
