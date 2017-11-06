#pragma once
#include "IecCodecFactory.h"
#include <queue>
#include <vector>

struct VABuffer
{
	SD_UINT8 * m_pVideoBuf;
	size_t m_nVideoSize;
	SD_UINT8 * m_pAudioBuf;
	size_t m_nAudioSampleCount;
	VABuffer();
	~VABuffer();
	void Reset(size_t nVideoSize, size_t nAudioSampleCount);
	void Clear();
	void Copy(const VABuffer & va);
	void CopyVideo(const SD_UINT8 * pVideoBuf);
	void CopyAudio(const SD_UINT8 * pAudioBuf);
};

struct VALoop
{
	std::queue<VABuffer *> m_queUnused;
	std::queue<VABuffer *> m_queData;
	size_t m_nMaxSize;
	CRITICAL_SECTION m_lock;
	VALoop();
	~VALoop();
	void Clear();
	void Reset(size_t nMaxSize, size_t nVideoSize, size_t nAudioSampleCount);

	void Lock();
	void Unlock();

	bool Push(const SD_UINT8* pFrameBuf, SD_UINT32 dwVideoBufSize, const SD_UINT8* pSamplesBuf, SD_UINT32 dwSampleNum);
	bool Push(const VABuffer & va);
	bool Pop(VABuffer & va);
};

class EncodecThreader
{
private:
	IecCodecProtocolEncoder * m_pEncoder;
	IecCodecFactory * m_ecfactory;

	VALoop m_vaLoop;
public:
	EncodecThreader();
	~EncodecThreader();
protected:
	CEvent m_evtStop;
	CWinThread * m_pThread;

	static UINT ThreadEncodec(LPVOID pParam);
	bool DoEncodec();
public:
	bool SetOutputVAParam(const SDStreamMediaInfo & streamInfo, const std::string & cstrFilePath);
	bool SetInputParam(const SDVideoFrameImageBufInfo & imageBufInfo, const SDAudioSamplesBufInfo & audioSamplesBufInfo);
	bool PutFrameBuffer(const SD_UINT8* pFrameBuf, SD_UINT32 dwVideoBufSize, const SD_UINT8* pSamplesBuf, SD_UINT32 dwSampleNum);

	bool Start();
	bool Stop();
};
