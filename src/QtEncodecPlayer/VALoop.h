#pragma once
#include "VABuffer.h"
#include <queue>
#include <mutex>

class VALoop
{
protected:
	std::queue<VABuffer *> m_queUnused;
	std::queue<VABuffer *> m_queData;
	size_t m_nMaxSize;
	std::recursive_mutex m_lock;
public:
	VALoop();
	~VALoop();
	void Clear();
	void Reset(size_t nMaxSize, size_t nVideoSize, size_t nAudioSampleCount);

	void Lock();
	void Unlock();

	bool Push(const unsigned char * pFrameBuf, unsigned int dwVideoBufSize, const unsigned char * pSamplesBuf, unsigned int dwSampleNum);
	bool Push(const VABuffer & va);
	bool Pop(VABuffer & va);
	size_t UnusedSize();
	size_t GetMaxSize();
};

