#pragma once
#include "IecCodecFactory.h"
#include "VALoop.h"
#include <queue>
#include <vector>
#include <thread>

class EncodecThreader
{
private:
	IecCodecProtocolEncoder * m_pEncoder;
	IecCodecFactory * m_ecfactory;

	VALoop m_vaLoop;
	bool m_bForbitLostFrame;
public:
	EncodecThreader();
	~EncodecThreader();
	EncodecThreader(const EncodecThreader &);
protected:
	bool m_bQiut;//退出标记
	std::mutex m_lockTime;//时间等待锁
	std::condition_variable m_conTime;//时间等待条件锁
	std::thread * m_pPlayThread;

	static void ThreadEncodec(EncodecThreader * pThis);
	bool DoEncodec();
public:
	bool SetOutputVAParam(const SDStreamMediaInfo & streamInfo, const std::string & cstrFilePath);
	bool SetInputParam(const SDVideoFrameImageBufInfo & imageBufInfo, const SDAudioSamplesBufInfo & audioSamplesBufInfo, bool bForbidLostFrame);
	bool PutFrameBuffer(const SD_UINT8* pFrameBuf, SD_UINT32 dwVideoBufSize, const SD_UINT8* pSamplesBuf, SD_UINT32 dwSampleNum);

	bool Start();
	bool Stop();
};
