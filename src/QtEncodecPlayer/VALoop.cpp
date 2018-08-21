#include "VALoop.h"

VALoop::VALoop()
{
}

VALoop::~VALoop()
{
	Clear();
}

void VALoop::Clear()
{
	Lock();
	while (m_queUnused.size() > 0)
	{
		VABuffer * pBuffer = m_queUnused.front();
		delete pBuffer;
		pBuffer = nullptr;
		m_queUnused.pop();
	}

	while (m_queData.size() > 0)
	{
		VABuffer * pBuffer = m_queData.front();
		delete pBuffer;
		pBuffer = nullptr;
		m_queData.pop();
	}
	m_nMaxSize = 0;
	Unlock();
}

void VALoop::Reset(size_t nMaxSize, size_t nVideoSize, size_t nAudioSampleCount)
{
	Lock();
	Clear();
	for (size_t i = 0; i < nMaxSize; i++)
	{
		VABuffer * pBuffer = new VABuffer();
		pBuffer->Reset(nVideoSize, nAudioSampleCount);
		m_queUnused.push(pBuffer);
	}
	m_nMaxSize = nMaxSize;
	Unlock();
}

void VALoop::Lock()
{
	m_lock.lock();
}

void VALoop::Unlock()
{
	m_lock.unlock();
}

bool VALoop::Push(const unsigned char * pFrameBuf, unsigned int dwVideoBufSize, const unsigned char * pSamplesBuf, unsigned int dwSampleNum)
{
	bool bRet = false;
	Lock();
	if (m_queUnused.size() > 0)
	{
		VABuffer * pBuffer = m_queUnused.front();
		//assert(pBuffer->m_nVideoSize == dwVideoBufSize);
		//assert(pBuffer->m_nAudioSampleCount == dwSampleNum);
		pBuffer->CopyVideo(pFrameBuf);
		pBuffer->CopyAudio(pSamplesBuf);
		m_queData.push(pBuffer);
		m_queUnused.pop();
		bRet = true;
	}
	else
	{
		bRet = false;
	}
	Unlock();
	return bRet;
}

size_t VALoop::GetMaxSize()
{
	return m_nMaxSize;
}

bool VALoop::Push(const VABuffer & va)
{
	bool bRet = false;
	Lock();
	if (m_queUnused.size() > 0)
	{
		VABuffer * pBuffer = m_queUnused.front();
		pBuffer->Copy(va);
		m_queData.push(pBuffer);
		m_queUnused.pop();
		bRet = true;
	}
	else
	{
		bRet = false;
	}
	Unlock();
	return bRet;
}

bool VALoop::Pop(VABuffer & va)
{
	bool bRet = false;
	Lock();
	if (m_queData.size() > 0)
	{
		VABuffer * pBuffer = m_queData.front();
		va.Copy(*pBuffer);
		m_queUnused.push(pBuffer);
		m_queData.pop();
		bRet = true;
	}
	else
	{
		bRet = false;
	}
	Unlock();
	return bRet;
}

size_t VALoop::UnusedSize()
{
	size_t nRet = 0;
	Lock();
	nRet = m_queUnused.size();
	Unlock();
	return nRet;
}
