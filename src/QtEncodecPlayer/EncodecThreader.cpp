//#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "EncodecThreader.h"

static const int SAMPLE_SIZE = 4;

EncodecThreader::EncodecThreader()
	: m_pEncoder(nullptr)
	, m_ecfactory(nullptr)
	, m_pPlayThread(nullptr)
	, m_bForbitLostFrame(false)
{
	m_ecfactory = ecCodec_CreateCodecFactory();
	m_vaLoop.Clear();
}


EncodecThreader::~EncodecThreader()
{
	Stop();
	m_ecfactory->DeleteProtocolEncoder(m_pEncoder);
	ecCodec_ReleaseCodecFactory(m_ecfactory);
}

EncodecThreader::EncodecThreader(const EncodecThreader &)
{
}

void EncodecThreader::ThreadEncodec(EncodecThreader * pThis)
{
	if (pThis)
	{
		pThis->DoEncodec();
	}
}

bool EncodecThreader::DoEncodec()
{
	VABuffer vaTmp;
	SDRFrameInfo frameInfoTmp;
	frameInfoTmp.emDataType = STREAM_DATATYPE_VIDEO;
	size_t tmClock = clock();
	while (true)
	{
		int nWait = 3 - (clock() - tmClock);
		std::unique_lock<std::mutex> lockWait(m_lockTime);
		std::cv_status cvsts = m_conTime.wait_for(lockWait, std::chrono::milliseconds(nWait));
		if (cvsts == std::cv_status::no_timeout)
		{
			//信号来了，退出
			break;
		}
		else
		{
			tmClock = clock();
			if (m_vaLoop.Pop(vaTmp))
			{
				frameInfoTmp.iSize = vaTmp.GetVideoBufSize();// 帧数据大小		4---16
				if (!m_pEncoder->PutVideoBuffer(vaTmp.GetVideoBuf(), false, &frameInfoTmp))
				{
					OutputDebugString(_T("m_pEncoder->PutVideoBuffer failed\n"));
				}
				if (!m_pEncoder->PutAudioSamples(vaTmp.GetAudioBuf(), vaTmp.GetAudioSampleCount()))
				{
					OutputDebugString(_T("m_pEncoder->PutAudioSamples failed\n"));
				}
			}
		}
	}
	return true;
}

bool EncodecThreader::SetOutputVAParam(const SDStreamMediaInfo & streamInfo, const std::string & cstrFilePath)
{
	Stop();
	if (streamInfo.sVideoMediaInfo.enumVideoType == SDVIDEOTYPE_H264_INTEL)
	{
		m_pEncoder = m_ecfactory->GetProtocolEncoder(EMCodec_Intel);
	}
	else
	{
		m_pEncoder = m_ecfactory->GetProtocolEncoder(EMCodec_FFmpeg);
	}
	return m_pEncoder->SetSinkFile(&streamInfo, cstrFilePath.c_str());
}

bool EncodecThreader::SetInputParam(const SDVideoFrameImageBufInfo & imageBufInfo, const SDAudioSamplesBufInfo & audioSamplesBufInfo, bool bForbidLostFrame)
{
	Stop();
	m_bForbitLostFrame = bForbidLostFrame;
	bool bRet = m_pEncoder->SetAudioSamplesBufInfo(&audioSamplesBufInfo);
	bRet &= m_pEncoder->SetVideoFrameBufInfo(&imageBufInfo, nullptr);
	return true;
}

bool EncodecThreader::PutFrameBuffer(const SD_UINT8* pFrameBuf, SD_UINT32 dwVideoBufSize, const SD_UINT8* pSamplesBuf, SD_UINT32 dwSampleNum)
{
	if (m_vaLoop.GetMaxSize() < 1)
	{
		m_vaLoop.Reset(10, dwVideoBufSize, dwSampleNum);
	}
	do
	{
		if (m_vaLoop.Push(pFrameBuf, dwVideoBufSize, pSamplesBuf, dwSampleNum))
		{
			return true;
		}
		else
		{
			std::unique_lock<std::mutex> lockWait(m_lockTime);
			std::cv_status cvsts = m_conTime.wait_for(lockWait, std::chrono::milliseconds(5));
			if (cvsts == std::cv_status::no_timeout)
			{
				//信号来了，退出
				break;
			}
		}
	} while (m_bForbitLostFrame);
	return false;
}

bool EncodecThreader::Start()
{
	Stop();
	m_pPlayThread = new std::thread(&ThreadEncodec, this);
	return true;
}

bool EncodecThreader::Stop()
{
	m_conTime.notify_all();
	if (m_pPlayThread)
	{
		m_pPlayThread->join();
		delete m_pPlayThread;
		m_pPlayThread = nullptr;
	}
	return true;
}
