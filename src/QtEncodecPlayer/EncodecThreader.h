#pragma once
#include "IecCodecFactory.h"
#include "VALoop.h"
#include <queue>
#include <vector>
#include <thread>
#include "StdEvent.h"

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
	CStdEvent m_evtQuit;
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
