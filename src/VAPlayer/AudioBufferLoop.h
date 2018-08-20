#pragma once
#include <mutex>

class CAudioBufferLoop
{
private:
	char * m_pBuffer;
	int m_nBufSize;//缓冲区大小
	int m_nCursor;//当前读取游标
	int m_nRemainData;//当前数据size
	std::recursive_mutex data_lock;
public:
	CAudioBufferLoop();
	~CAudioBufferLoop();

	void Lock();
	void Unlock();
	void Reset(int nBufSize);
	void Release();
	void Push(char * pBuf, int nSize);
	void Pop(char * pBuf, int nSize);
};

