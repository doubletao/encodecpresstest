#pragma once
#include <mutex>
#include <chrono>
#include <condition_variable>

class CAudioBufferLoop
{
private:
	char * m_pBuffer;
	int m_nBufSize;//缓冲区大小
	int m_nCursor;//当前读取游标
	int m_nRemainData;//当前数据size
	std::recursive_mutex m_lockData;//数据读写锁
	std::mutex m_lockTime;//时间等待锁
	std::condition_variable m_conTime;//时间等待条件锁
public:
	CAudioBufferLoop();
	~CAudioBufferLoop();

	void Lock();
	void Unlock();
	void Reset(int nBufSize);
	void Release();
	void Push(char * pBuf, int nSize);
	bool Pop(char * pBuf, int nSize);
	bool WaitPop(char * pBuf, int nSize, unsigned long nTimeup);//如果当前数据不够本次pop，则死等nTimeup毫秒
};

