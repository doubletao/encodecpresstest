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
	m_lockData.lock();
}

void CAudioBufferLoop::Unlock()
{
	m_lockData.unlock();
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
	m_conTime.notify_all();//退出前释放所有等待
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
		//每次有push的时候，
		m_conTime.notify_one();
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

bool CAudioBufferLoop::Pop(char * pBuf, int nSize)
{
	bool bRet = false;
	Lock();
	//nSize > 0才有得聊
	if (nSize > 0)
	{
		if (nSize > m_nRemainData)
		{
			//如果不够，不凑活，直接false
			bRet = false;
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
			bRet = true;
		}
	}
	Unlock();
	return bRet;
}

bool CAudioBufferLoop::WaitPop(char * pBuf, int nSize, unsigned long nTimeup)
{
	if (!Pop(pBuf, nSize))
	{
		std::unique_lock<std::mutex> lockWait(m_lockTime);
		std::cv_status cvsts = m_conTime.wait_for(lockWait, std::chrono::milliseconds(nTimeup));
		if (cvsts == std::cv_status::timeout)
		{
			//时间到，退出
			return false;
		}
		else if (cvsts == std::cv_status::no_timeout)
		{
			//等到了信号，再试一次就返回
			return Pop(pBuf, nSize);
		}
	}
	return true;
}
