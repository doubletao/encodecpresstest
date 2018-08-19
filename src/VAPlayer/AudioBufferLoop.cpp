#include "stdafx.h"
#include "AudioBufferLoop.h"
#include <assert.h>

//buffer的基本单位
static const int BUFFER_GROWTH = 1024 * 4;

CAudioBufferLoop::CAudioBufferLoop()
	: m_pBuffer(nullptr)
	, m_nBufSize(0)
	, m_nCursor(0)
	, m_nRemainData(0)
{
}


CAudioBufferLoop::~CAudioBufferLoop()
{
	Release();
}

void CAudioBufferLoop::Lock()
{
	data_lock.lock();
}

void CAudioBufferLoop::Unlock()
{
	data_lock.unlock();
}

void CAudioBufferLoop::Reset(int nBufSize)
{
	Lock();
	Release();
	if (nBufSize > 0)
	{
		m_pBuffer = new char[nBufSize];
		assert(m_pBuffer);
		m_nBufSize = nBufSize;
	}
	Unlock();
}

void CAudioBufferLoop::Release()
{
	Lock();
	if (m_pBuffer)
	{
		delete[] m_pBuffer;
		m_pBuffer = nullptr;
	}
	m_nBufSize = 0;
	m_nCursor = 0;
	m_nRemainData = 0;
	Unlock();
}

void CAudioBufferLoop::Push(char * pBuf, int nSize)
{
	Lock();
	//nSize > 0才有得聊
	if (nSize > 0)
	{
		//当push量大于了缓冲区大小减去当前remain大小，则重新申请内存
		if (nSize > m_nBufSize - m_nRemainData)
		{
			int nNewSize = (nSize / BUFFER_GROWTH + 1) * BUFFER_GROWTH;
			assert(nNewSize > nSize - 1);
			char  * pNewBuf = new char[nNewSize];
			assert(pNewBuf);
			//拷贝原数据
			Pop(pNewBuf, m_nRemainData);
			m_nCursor = 0;
			m_nBufSize = nNewSize;
			delete[] m_pBuffer;
			m_pBuffer = pNewBuf;
			//拷贝新数据
			Push(pBuf, nSize);
		}
		else
		{
			//如果从游标到缓冲区末尾放不下，则先往里填，剩下的往开头填
			if (nSize > m_nBufSize - m_nCursor)
			{
				memcpy(m_pBuffer + m_nCursor, pBuf, m_nBufSize - m_nCursor);
				memcpy(m_pBuffer, pBuf + m_nBufSize - m_nCursor, nSize - (m_nBufSize - m_nCursor));
			}
			//如果游标位置能放下，直接往里填
			else
			{
				memcpy(m_pBuffer + m_nCursor, pBuf, nSize);
			}
			m_nRemainData += nSize;
		}
	}
	Unlock();
}

void CAudioBufferLoop::Pop(char * pBuf, int nSize)
{
	Lock();
	//nSize > 0才有得聊
	if (nSize > 0)
	{
		if (nSize > m_nRemainData)
		{
			//如果不够，则将现有的填进去，其他的部分填0
			memset(pBuf, 0, nSize);
			Pop(pBuf, m_nRemainData);
		}
		else
		{
			//如果从游标到缓冲区末尾数据不够，则先往里填，剩下的从开头往里填
			if (nSize > m_nBufSize - m_nCursor)
			{
				memcpy(pBuf, m_pBuffer + m_nCursor, m_nBufSize - m_nCursor);
				m_nCursor = 0;
				m_nRemainData = m_nRemainData - (m_nBufSize - m_nCursor);
				memcpy(pBuf + m_nBufSize - m_nCursor, m_pBuffer, nSize - (m_nBufSize - m_nCursor));
				m_nCursor = nSize - (m_nBufSize - m_nCursor);
				m_nRemainData = m_nRemainData - (nSize - (m_nBufSize - m_nCursor));
			}
			//如果游标位置能放下，直接往里填
			else
			{
				memcpy(pBuf, m_pBuffer + m_nCursor, nSize);
				m_nRemainData = m_nRemainData - nSize;
			}
		}
	}
	Unlock();
}
