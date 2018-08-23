#include "DecodecThreader.h"

DecodecThreader::DecodecThreader()
	: m_pNotifyDecFunc(nullptr)
	, m_pDecCallbackData(nullptr)
	, m_pInfoMsgFunc(nullptr)
	, m_pInfoMsgCallbackData(nullptr)
	, m_nCurFrame(0)
	, m_nLastFrame(0)
	, m_nLastAudioPos(0)
	, m_nSamplePerFrame(2048)
	, m_bLockPts(false)
	, m_bLoop(false)
	, m_bPause(false)
	, m_pVideoBuf(nullptr)
	, m_nVideoBufSize(0)
	, m_pAudioBuf(nullptr)
	, m_nAudioBufSize(0)
	, m_ecFactory(nullptr)
	, m_ecDecoder(nullptr)
	, m_pDecodecThread(nullptr)
{
	m_ecFactory = ecCodec_CreateCodecFactory();
}


DecodecThreader::~DecodecThreader()
{
	Release();
	if (m_ecFactory)
	{
		ecCodec_ReleaseCodecFactory(m_ecFactory);
		m_ecFactory = nullptr;
	}
}

void DecodecThreader::Release()
{
	SetStop();
	m_pNotifyDecFunc = nullptr;
	m_pDecCallbackData = nullptr;
	m_pInfoMsgFunc = nullptr;
	m_pInfoMsgCallbackData = nullptr;
	m_nCurFrame = 0;
	m_nLastFrame = 0;
	m_nLastAudioPos = 0;
	m_nSamplePerFrame = 2048;
	m_bLockPts = false;
	m_bLoop = false;
	m_bPause = false;
	m_cstrSourcePath.clear();
	SDStreamMediaInfo srcMediaInfo;
	m_srcMediaInfo = srcMediaInfo;
	SDVideoFrameImageBufInfo desImageBufInfo;
	m_desImageBufInfo = desImageBufInfo;
	SDAudioMediaInfo desAudioSamplesBufInfo;
	m_desAudioSamplesBufInfo = desAudioSamplesBufInfo;
	SDStreamMediaInfoEx srcMediaInfoEx;
	m_srcMediaInfoEx = srcMediaInfoEx;
	m_pVideoBuf = nullptr;
	m_nVideoBufSize = 0;
	m_pAudioBuf = nullptr;
	m_nAudioBufSize = 0;
	assert(nullptr != m_ecFactory);
	if (m_ecDecoder)
	{
		m_ecFactory->DeleteProtocolDecoder(m_ecDecoder);
		m_ecDecoder = nullptr;
	}
		
}

void DecodecThreader::ThreadDecodec(DecodecThreader * pThis)
{
	if (pThis)
	{
		pThis->DoDecodec();
	}
}

bool DecodecThreader::DoDecodec()
{
	if (m_ecFactory)
	{
		if (m_ecDecoder)
		{
			//开始前先获取长度，获取成功了才继续
			if (m_ecDecoder->GetFileGlobalMediaInfo(&m_srcMediaInfoEx))
			{
				SD_UINT32 nFrameLength = m_srcMediaInfoEx.dwVideoFrameNum;
				m_nLastFrame = m_nCurFrame + 1;//刚开始last不能和cur一致，否则不解码了
				while (nFrameLength > 0)
				{
					if (m_evtQuit.Wait(0))
					{
						break;
					}
					if (m_nCurFrame > nFrameLength - 1)
					{
						if (m_bLoop)
						{
							m_nCurFrame = 0;
						}
						else
						{
							break;
						}
					}
					DecodecCurFrame();
					if (!m_bPause)
					{
						m_nCurFrame++;
					}
				}
			}
			else
			{
				EmitInfoMsg("Err:get media length failed");
			}
			//结束要删掉解码器
			m_ecFactory->DeleteProtocolDecoder(m_ecDecoder);
			m_ecDecoder = nullptr;
			//退出标记设置
			m_evtQuit.SetEvent();
		}
	}
	EmitInfoMsg("Err:unexpected param err");
	return false;
}

bool DecodecThreader::DecodecCurFrame()
{
	if (m_ecDecoder)
	{
		if (m_nCurFrame != m_nLastFrame)
		{
			SDRFrameInfo frameInfo;
			SD_UINT32 numAudioSample = 0;
			//锁pts对齐只能在非暂停状态下
			if (!m_bPause && m_bLockPts)
			{
				m_ecDecoder->GetVABuffer(m_pVideoBuf, m_pAudioBuf, &numAudioSample);
				if (m_pNotifyDecFunc && m_pDecCallbackData)
				{
					m_pNotifyDecFunc(m_nCurFrame, m_pDecCallbackData, GetVideoBufSize(), numAudioSample);
				}
			}
			else
			{
				bool bSucc = false;
				if (m_srcMediaInfo.dwVideoStreamCount > 0)
				{
					bSucc = m_ecDecoder->GetVideoBuffer(m_nCurFrame, m_pVideoBuf, &frameInfo);
				}
				if (!bSucc)
				{
					char szOutput[256];
					sprintf_s(szOutput, 256, "video get failed:frame:%d audio:%d", (int)m_nCurFrame, m_nLastAudioPos);
					EmitInfoMsg(szOutput);
				}
				if (m_srcMediaInfo.dwAudioStreamCount > 0)
				{
					bSucc = m_ecDecoder->GetAudioSamples(m_nLastAudioPos, m_nSamplePerFrame, m_pAudioBuf, &numAudioSample);
				}
				if (!bSucc)
				{
					char szOutput[256];
					sprintf_s(szOutput, 256, "audio get failed:frame:%d audio:%d", (int)m_nCurFrame, m_nLastAudioPos);
					EmitInfoMsg(szOutput);
				}
				if (bSucc)
				{
					if (m_pNotifyDecFunc && m_pDecCallbackData)
					{
						m_pNotifyDecFunc(m_nCurFrame, m_pDecCallbackData, frameInfo.iSize, numAudioSample);
					}
				}
			}
			m_nLastFrame = m_nCurFrame;
			m_nLastAudioPos += numAudioSample;
		}
		else
		{
			//可能是暂停，就等着变化吧
			m_evtQuit.Wait(5);
		}
	}
	return true;
}

void DecodecThreader::EmitInfoMsg(std::string strInfo)
{
	if (m_pInfoMsgFunc && m_pInfoMsgCallbackData)
	{
		m_pInfoMsgFunc(strInfo, m_pInfoMsgCallbackData);
	}
}

bool DecodecThreader::SetVideoBuf(unsigned char * pVideoBuf, size_t nVideoBufSize)
{
	m_pVideoBuf = pVideoBuf;
	m_nVideoBufSize = nVideoBufSize;
	return true;
}

bool DecodecThreader::SetAudioBuf(unsigned char * pAudioBuf, size_t nAudioBufSize)
{
	m_pAudioBuf = pAudioBuf;
	m_nAudioBufSize = nAudioBufSize;
	return true;
}

bool DecodecThreader::SetDecCallbackFunc(OneFrameDecodecedFunc pFunc, void * pData)
{
	//运行过程中，禁止修改
	if (IsPlaying())
	{
		return false;
	}
	m_pNotifyDecFunc = pFunc;
	m_pDecCallbackData = pData;
	return true;
}

bool DecodecThreader::SetInfoMsgCallbackFunc(InfoMsgFunc pFunc, void * pData)
{
	//运行过程中，禁止修改
	if (IsPlaying())
	{
		return false;
	}
	m_pInfoMsgFunc = pFunc;
	m_pInfoMsgCallbackData = pData;
	return true;
}

bool DecodecThreader::SetInputSource(const std::string & cstrFilePath, SDStreamMediaInfo & mediaInfo)
{
	//运行过程中，禁止修改
	if (IsPlaying())
	{
		return false;
	}
	bool bRet = false;
	if (nullptr != m_ecFactory && nullptr == m_ecDecoder)
	{
		m_ecDecoder = m_ecFactory->GetProtocolDecoder();
		if (m_ecDecoder)
		{
			if (m_ecDecoder->SetSourcePath(cstrFilePath.c_str()))
			{
				if (m_ecDecoder->GetFileGlobalMediaInfo(&mediaInfo))
				{
					bRet = true;
				}
				else
				{
					EmitInfoMsg("Err:Decoder GetFileGlobalMediaInfo " + cstrFilePath + "failed");
				}
			}
			else
			{
				EmitInfoMsg("Err:Decoder SetSourcePath " + cstrFilePath + "failed");
			}
		}
		else
		{
			EmitInfoMsg("Err:Decoder create failed");
		}
	}
	else
	{
		EmitInfoMsg("Err:nullptr == Factory || nullptr != Decoder");
	}
	return bRet;
}

bool DecodecThreader::SetOutputParam(const SDVideoFrameImageBufInfo & imageBufInfo, const SDAudioMediaInfo & audioSamplesBufInfo)
{
	//运行过程中，禁止修改
	if (IsPlaying())
	{
		return false;
	}
	bool bRet = false;
	if (nullptr != m_ecFactory && nullptr != m_ecDecoder)
	{
		if (m_ecDecoder->SetVideoFrameBufInfo(&imageBufInfo, nullptr))
		{
			m_desImageBufInfo = imageBufInfo;
			if (m_ecDecoder->SetAudioSamplesBufInfo(&audioSamplesBufInfo))
			{
				m_desAudioSamplesBufInfo = audioSamplesBufInfo;
				//根据帧率及采样率来算出每帧对应的sample数
				m_nSamplePerFrame = 2048;
				{
					//每秒的视频帧数
					double dFramePerSec = m_srcMediaInfo.sVideoMediaInfo.dwStandardRate * 1.0 / m_srcMediaInfo.sVideoMediaInfo.dwStandardScale;
					//每秒的采样数
					double dSamplePerSec = m_desAudioSamplesBufInfo.dwSamplesPerSec;
					//每帧对应的sample数=每秒的采样数/每秒的视频帧数
					m_nSamplePerFrame = dSamplePerSec / dFramePerSec;
				}
				bRet = true;
			}
			else
			{
				EmitInfoMsg("Err:SetAudioSamplesBufInfo failed");
			}
		}
		else
		{
			EmitInfoMsg("Err:SetVideoFrameBufInfo failed");
		}
	}
	else
	{
		EmitInfoMsg("Err:nullptr == Factory || nullptr == Decoder");
	}
	return bRet;
}

bool DecodecThreader::SetPlayPause(bool bPlay)
{
	if (m_ecDecoder)
	{
		if (bPlay)
		{
			if (IsPlaying())
			{
				//如果正在运行，则停止
				SetStop();
			}
			if (nullptr == m_pDecodecThread)
			{
				m_evtQuit.ResetEvent();
				m_pDecodecThread = new std::thread(ThreadDecodec, this);
			}
			else
			{
				EmitInfoMsg("Err:unexpected Thread living");
			}
		}
		else
		{
			//非运行态，设置暂停没有用
			if (IsPlaying())
			{
				m_bPause = true;
				return true;
			}
			else
			{
				EmitInfoMsg("Warning:set pause while not playing");
			}
		}
	}
	else
	{
		EmitInfoMsg("Err:Play without Cue");
	}
	return false;
}

bool DecodecThreader::SetStop()
{
	m_evtQuit.SetEvent();
	if (m_pDecodecThread)
	{
		m_pDecodecThread->join();
		delete m_pDecodecThread;
		m_pDecodecThread = nullptr;
	}
	return true;
}

bool DecodecThreader::SetFirstFrame(bool bPause)
{
	return SetSeekPos(0, bPause);
}

bool DecodecThreader::SetPreFrame(bool bPause)
{
	if (m_nCurFrame > 0)
	{
		return SetSeekPos(m_nCurFrame - 1, bPause);
	}
	return false;
}

bool DecodecThreader::SetNextFrame(bool bPause)
{
	if (m_srcMediaInfoEx.dwVideoFrameNum > 0)
	{
		if (m_nCurFrame < m_srcMediaInfoEx.dwVideoFrameNum - 1)
		{
			return SetSeekPos(m_nCurFrame + 1, bPause);
		}
	}
	return false;
}

bool DecodecThreader::SetLastFrame(bool bPause)
{
	if (m_srcMediaInfoEx.dwVideoFrameNum > 0)
	{
		return SetSeekPos(m_srcMediaInfoEx.dwVideoFrameNum - 1, bPause);
	}
	else
	{
		return false;
	}
}

unsigned long long DecodecThreader::GetCurSeekPos()
{
	return m_nCurFrame;
}

bool DecodecThreader::IsPlaying()
{
	bool bRet = true;
	if (m_evtQuit.Wait(0))
	{
		bRet = false;
	}
	return bRet;
}

bool DecodecThreader::IsStoped()
{
	return !IsPlaying();
}

bool DecodecThreader::IsPause()
{
	if (IsPlaying())
	{
		if (m_bPause)
		{
			return true;
		}
	}
	return false;
}

bool DecodecThreader::IsLockVAPts()
{
	return m_bLockPts;
}

bool DecodecThreader::IsLoop()
{
	return m_bLoop;
}

std::string DecodecThreader::GetInputSourcePath()
{
	return m_cstrSourcePath;
}

const SDStreamMediaInfo & DecodecThreader::GetSrcMediaInfo()
{
	return m_srcMediaInfo;
}

const SDVideoFrameImageBufInfo & DecodecThreader::GetDesImageBufInfo()
{
	return m_desImageBufInfo;
}

const SDAudioMediaInfo & DecodecThreader::GetDesAudioInfo()
{
	return m_desAudioSamplesBufInfo;
}

size_t DecodecThreader::GetVideoBufSize()
{
	if (m_ecFactory && m_ecDecoder)
	{
		return m_ecDecoder->GetVideoBufferSize();
	}
	return 0;
}

size_t DecodecThreader::GetAudioBufSize()
{
	if (m_ecFactory && m_ecDecoder)
	{
		return m_ecDecoder->GetAudioBufferSize();
	}
	return 0;
}

unsigned int DecodecThreader::GetSamplePerFrame()
{
	return m_nSamplePerFrame;
}

bool DecodecThreader::SetSeekPos(unsigned long long m_nCurFrame, bool bPause)
{
	m_nCurFrame = m_nCurFrame;
	if (bPause)
	{
		if (IsPlaying())
		{
			SetPlayPause(false);
			return true;
		}
		else
		{
			EmitInfoMsg("Warning:set pause while not playing");
			return false;
		}
	}
	else
	{
		return true;
	}
}

bool DecodecThreader::SetLockVAPts(bool bLock)
{
	m_bLockPts = bLock;
	return true;
}

bool DecodecThreader::SetLoop(bool bLoop)
{
	m_bLoop = bLoop;
	return true;
}
