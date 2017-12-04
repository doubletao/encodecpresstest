//#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "stdafx.h"
#include "EncodecThreader.h"

static const int SAMPLE_SIZE = 4;

EncodecThreader::EncodecThreader()
	: m_pEncoder(nullptr)
	, m_ecfactory(nullptr)
	, m_pThread(nullptr)
	, m_evtStop(FALSE, TRUE, nullptr, nullptr)
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

UINT EncodecThreader::ThreadEncodec(LPVOID pParam)
{
	EncodecThreader * pThis = (EncodecThreader *)pParam;
	if (pThis)
	{
		pThis->DoEncodec();
	}
	return 0;
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
		if (WaitForSingleObject(m_evtStop, nWait > 0 ? 3 : 0) == WAIT_OBJECT_0)
		{
			break;
		}
		else
		{
			tmClock = clock();
			if (m_vaLoop.Pop(vaTmp))
			{
				frameInfoTmp.iSize = vaTmp.m_nVideoSize;// 帧数据大小		4---16
				if (!m_pEncoder->PutVideoBuffer(vaTmp.m_pVideoBuf, false, &frameInfoTmp))
				{
					OutputDebugString(_T("m_pEncoder->PutVideoBuffer failed\n"));
				}
				if (!m_pEncoder->PutAudioSamples(vaTmp.m_pAudioBuf, vaTmp.m_nAudioSampleCount))
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
	if (m_vaLoop.m_nMaxSize < 1)
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
			if (WaitForSingleObject(m_evtStop, 5) == WAIT_OBJECT_0)
			{
				break;
			}
		}
	} while (m_bForbitLostFrame);
	return false;
}

bool EncodecThreader::Start()
{
	Stop();
	m_evtStop.ResetEvent();
	m_pThread = AfxBeginThread(ThreadEncodec, this);
	return true;
}

bool EncodecThreader::Stop()
{
	m_evtStop.SetEvent();
	if (m_pThread)
	{
		WaitForSingleObject(m_pThread->m_hThread, INFINITE);
		m_pThread = nullptr;
	}
	return true;
}

VABuffer::VABuffer()
	: m_pVideoBuf(nullptr)
	, m_nVideoSize(0)
	, m_pAudioBuf(nullptr)
	, m_nAudioSampleCount(0)
{
}

VABuffer::~VABuffer()
{
	Clear();
}

void VABuffer::Reset(size_t nVideoSize, size_t nAudioSampleCount)
{
	Clear();
	m_pVideoBuf = new SD_UINT8[nVideoSize];
	m_nVideoSize = nVideoSize;
	m_pAudioBuf = new SD_UINT8[nAudioSampleCount * SAMPLE_SIZE];
	m_nAudioSampleCount = nAudioSampleCount;
}

void VABuffer::Clear()
{
	delete[] m_pVideoBuf;
	m_pVideoBuf = nullptr;
	m_nVideoSize = 0;
	delete[] m_pAudioBuf;
	m_pAudioBuf = nullptr;
	m_nAudioSampleCount = 0;
}

void VABuffer::Copy(const VABuffer & va)
{
	Reset(va.m_nVideoSize, va.m_nAudioSampleCount);
	memcpy(m_pVideoBuf, va.m_pVideoBuf, m_nVideoSize);
	memcpy(m_pAudioBuf, va.m_pAudioBuf, m_nAudioSampleCount * SAMPLE_SIZE);
}

void VABuffer::CopyVideo(const SD_UINT8 * pVideoBuf)
{
	assert(m_pVideoBuf);
	memcpy(m_pVideoBuf, pVideoBuf, m_nVideoSize);
}

void VABuffer::CopyAudio(const SD_UINT8 * pAudioBuf)
{
	assert(m_pAudioBuf);
	memcpy(m_pAudioBuf, pAudioBuf, m_nAudioSampleCount * SAMPLE_SIZE);
}

VALoop::VALoop()
{
	InitializeCriticalSection(&m_lock);
}

VALoop::~VALoop()
{
	Clear();
	DeleteCriticalSection(&m_lock);
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
	EnterCriticalSection(&m_lock);
}

void VALoop::Unlock()
{
	LeaveCriticalSection(&m_lock);
}

bool VALoop::Push(const SD_UINT8 * pFrameBuf, SD_UINT32 dwVideoBufSize, const SD_UINT8 * pSamplesBuf, SD_UINT32 dwSampleNum)
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
