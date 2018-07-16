
// EncodecPressTestDlg.cpp : 实现文件
//
//#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "stdafx.h"
#include "EncodecPressTest.h"
#include "EncodecPressTestDlg.h"
#include "afxdialogex.h"
#include "CpuUsage.h"
#include <set>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

typedef unsigned __int8 uint8_t;
typedef uint8_t Uint8;
typedef unsigned __int32 uint32_t;
typedef uint32_t Uint32;
#define SDL_static_cast(type, expression) static_cast<type>(expression)
#define SDL_FOURCC(A, B, C, D) \
    ((SDL_static_cast(Uint32, SDL_static_cast(Uint8, (A))) << 0) | \
     (SDL_static_cast(Uint32, SDL_static_cast(Uint8, (B))) << 8) | \
     (SDL_static_cast(Uint32, SDL_static_cast(Uint8, (C))) << 16) | \
     (SDL_static_cast(Uint32, SDL_static_cast(Uint8, (D))) << 24))
#define SDL_DEFINE_PIXELFOURCC(A, B, C, D) SDL_FOURCC(A, B, C, D)
DWORD SDL_PIXELFORMAT_IYUV =      /**< Planar mode: Y + U + V  (3 planes) */
SDL_DEFINE_PIXELFOURCC('I', 'Y', 'U', 'V');

DWORD SDL_PIXELFORMAT_UYVY =      /**< Packed mode: U0+Y0+V0+Y1 (1 plane) */
	SDL_DEFINE_PIXELFOURCC('U', 'Y', 'V', 'Y');

#define ENABLE_ENCODE

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CEncodecPressTestDlg 对话框



UINT CEncodecPressTestDlg::ThreadPlay(LPVOID pParam)
{
	CEncodecPressTestDlg * pThis = (CEncodecPressTestDlg *)pParam;
	if (pThis)
	{
		pThis->DoPlay();
	}
	return 0;
}

void CEncodecPressTestDlg::StopPlay()
{
	if (m_pPlayThread)
	{
		m_evtPlayStop.SetEvent();
		WaitForSingleObject(m_pPlayThread->m_hThread, INFINITE);
		m_pPlayThread = NULL;
	}
}

void CEncodecPressTestDlg::StartPlay()
{
	StopPlay();
	m_evtPlayStop.ResetEvent();
	m_evtPlayPause.ResetEvent();
	m_pPlayThread = AfxBeginThread(ThreadPlay, this);
}

void CEncodecPressTestDlg::PausePlay()
{
	if (WaitForSingleObject(m_evtPlayPause, 0) == WAIT_OBJECT_0)
	{
		m_evtPlayPause.ResetEvent();
		PushInfo(_T("Continue"));
	}
	else
	{
		m_evtPlayPause.SetEvent();
		PushInfo(_T("Paused"));
	}
}

//#define DEBUG_AUDIO_OUTFILE
CString strMsg;

void CEncodecPressTestDlg::DoPlay()
{
	int nMaxCpu = 0;
	int nMaxMem = 0;
	CEdit * pEdit = (CEdit *)GetDlgItem(IDC_EDIT_INFOMATION);
	if (pEdit && ::IsWindow(pEdit->GetSafeHwnd()))
	{
		pEdit->SetWindowText(_T(""));
	}

	std::string cstrOutPath = "E:\\clip\\";
	CWnd * pWnd = GetDlgItem(IDC_EDIT_OUT_FILE_PATH);
	if (pWnd && ::IsWindow(pWnd->GetSafeHwnd()))
	{
		CString strPath;
		pWnd->GetWindowText(strPath);
		cstrOutPath = ConverCStringToStdString(strPath);
	}

	CRect rectDraw;
	CWnd * pPlayerWnd = GetDlgItem(IDC_DECODER_SCREEN);
	if (pPlayerWnd && ::IsWindow(pPlayerWnd->GetSafeHwnd()))
	{
		::GetClientRect(pPlayerWnd->GetSafeHwnd(), &rectDraw);
		POINT po;
		po.x = rectDraw.left;
		po.y = rectDraw.top;
		::ClientToScreen(pPlayerWnd->GetSafeHwnd(), &po);
		rectDraw.top += po.y;
		rectDraw.left += po.x;
		rectDraw.right += po.x;
		rectDraw.bottom += po.y;
	}

	bool bLoopPlay = false;
	CButton * pBtn = (CButton *)GetDlgItem(IDC_CHK_LOOPPLAY);
	if (pBtn && ::IsWindow(pBtn->GetSafeHwnd()))
	{
		bLoopPlay = pBtn->GetCheck();
	}

	bool bForbidLoseFrame = false;
	pBtn = (CButton *)GetDlgItem(IDC_CHK_FORBID_LOSTFRAME);
	if (pBtn && ::IsWindow(pBtn->GetSafeHwnd()))
	{
		bForbidLoseFrame = pBtn->GetCheck();
	}

	bool bForcePtsAlign = false;
	pBtn = (CButton *)GetDlgItem(IDC_CHK_FRAME_PLAY);
	if (pBtn && ::IsWindow(pBtn->GetSafeHwnd()))
	{
		bForcePtsAlign = pBtn->GetCheck();
	}

	m_nDispFrame = 0;
	Lock();
	m_nFrame = 0;
	Unlock();
	PostMessage(MSG_PUSHINFO, 0, (LPARAM)_T("Starting"));
	pWnd = GetDlgItem(IDC_EDIT_FILE_PATH);
	if (pWnd && ::IsWindow(pWnd->GetSafeHwnd()))
	{
#ifdef DEBUG_AUDIO_OUTFILE
		FILE * pAudioFile = nullptr;
		fopen_s(&pAudioFile, "output.pcm", "wb");
#endif
		StartDisplay();
		CString strPath;
		pWnd->GetWindowText(strPath);
		std::string cstrPath = ConverCStringToStdString(strPath);
		if (m_ecfactory)
		{
			IecCodecProtocolDecoder * pDecoder = m_ecfactory->GetProtocolDecoder();
			if (pDecoder)
			{
				if (pDecoder->SetSourcePath(cstrPath.c_str()))
				{
					int nWidth = rectDraw.Width();
					int nHeight = rectDraw.Height();
					nWidth = (nWidth + 1) / 2 * 2;
					nHeight = (nHeight + 1) / 2 * 2;
					nWidth = 1920;
					nHeight = 1080;
					SDStreamMediaInfoEx streamMediaInfoEx;
					SDAudioMediaInfo audioInfo;
					audioInfo.enumAudioType = SDAUDIOTYPE_WAVE_PCM;
					audioInfo.dwBitsPerSample = 32;
					audioInfo.enumAudioCFG = SDAUDIOCFG_STEREO;
					audioInfo.dwAvgBitsPerSec = audioInfo.dwSamplesPerSec*audioInfo.dwBitsPerSample*audioInfo.dwChannels;
					audioInfo.enumChannelSamplesFormat = SDCHANNELSAMPLESFORMAT_Progressive;
					audioInfo.dwSamplesPerSec = 48000;
					audioInfo.dwChannels = 2;
					pDecoder->SetAudioSamplesBufInfo(&audioInfo);
					if (pDecoder->GetFileGlobalMediaInfo(&streamMediaInfoEx))
					{
						m_nTimebaseDen = streamMediaInfoEx.sVideoMediaInfo.dwStandardRate;
						m_nTimebaseNum = streamMediaInfoEx.sVideoMediaInfo.dwStandardScale;
						bool bContinue = true;
						m_player.SetBufferFWH(SDL_PIXELFORMAT_UYVY, nWidth, nHeight);
						SDVideoFrameImageBufInfo videoFrameImageBufInfo;
						videoFrameImageBufInfo.dwXSize = nWidth;
						videoFrameImageBufInfo.dwYSize = nHeight;
						videoFrameImageBufInfo.enumColorFormat = SDCOLORFORMAT_UYVY;// streamMediaInfoEx.sVideoMediaInfo.enumColorFormat;
						bContinue = pDecoder->SetVideoFrameBufInfo(&videoFrameImageBufInfo, nullptr);

						//根据帧率及采样率来算出每帧对应的sample数
						SD_UINT32 SamplePerFrame = 2048;
						{
							//每秒的视频帧数
							double dFramePerSec = streamMediaInfoEx.sVideoMediaInfo.dwStandardRate * 1.0 / streamMediaInfoEx.sVideoMediaInfo.dwStandardScale;
							//每秒的采样数
							double dSamplePerSec = audioInfo.dwSamplesPerSec;
							//每帧对应的sample数=每秒的采样数/每秒的视频帧数
							SamplePerFrame = dSamplePerSec / dFramePerSec;
						}

						SD_UINT32 nVideoBufferSize = pDecoder->GetVideoBufferSize();
						SD_UINT32 nAudioBufferSize = AVCODEC_MAX_AUDIO_FRAME_SIZE;
						nAudioBufferSize = SamplePerFrame * 4;
						uint8_t * pVideoData = new uint8_t[nVideoBufferSize];
						memset(pVideoData, 0, nVideoBufferSize * sizeof(uint8_t));
						uint8_t * pAudioData = new uint8_t[nAudioBufferSize];
						memset(pAudioData, 0, nAudioBufferSize * sizeof(uint8_t));
						SD_UINT32 numAudioSample = 0;

						m_vaBuf.Reset(nVideoBufferSize, SamplePerFrame);
						m_vaLoop.Reset(100, nVideoBufferSize, SamplePerFrame);
						
						bool bFirst = false;
						m_ctrSlider.SetRange(0, streamMediaInfoEx.dwVideoFrameNum);
						m_ctrSlider.SetTicFreq(streamMediaInfoEx.dwVideoFrameNum / 100.0);
						uint32_t nAudioPos = 0;
#ifdef ENABLE_ENCODE
						for (size_t i = 0; i < 8; i++)
						{
							EncodecThreader *& pEncoder = m_pEncoder[i];
							if (m_ecfactory)
							{
								if (GetCodecCheck(i))
								{
									pEncoder = new EncodecThreader;
									if (pEncoder)
									{
										SDStreamMediaInfo streamInfo;
										SD_VIDEO_STANDARD emVideoStandard = GetCodecVideoStandard(i);
										SD_VIDEO_TYPE emVideoType = GetCodecVideoType(i);
										SD_COLOR_FORMAT emColorFmt = GetCodecColorFmt(i);
										//SD_COLOR_FORMAT emColorFmt = SDCOLORFORMAT_YUVP_422;
										SD_AUDIO_TYPE emAudioType = GetCodecAudioType(i);
										int nH264Level = GetCodecH264Level(i);
										CString strFileName;
										CString strTmp;
										GetCodecFileNameEdit(i)->GetWindowText(strTmp);
										strFileName.Append(strTmp);
										GetCodecFileSurfixEdit(i)->GetWindowText(strTmp);
										strFileName.Append(strTmp);

										if (m_bLogOpened)
										{
											strMsg.Format(_T("encoder%i:%s"), i, GenerateFileInfoName(emVideoStandard, emVideoType, emColorFmt, emAudioType, nH264Level));
											m_fileLog.WriteString(strMsg);
											m_fileLog.WriteString(_T("\r\n"));
										}

										GetPresetMediaInfo(emVideoStandard, emVideoType, emColorFmt, emAudioType, 48000, nH264Level, streamInfo);
										//streamInfo.sVideoMediaInfo.enumColorFormat = SDCOLORFORMAT_INTEL;
										//streamInfo.sVideoMediaInfo.dwWidth = nWidth;
										//streamInfo.sVideoMediaInfo.dwHeight = nHeight;
										if (pEncoder->SetOutputVAParam(streamInfo, (cstrOutPath + ConverCStringToStdString(strFileName).c_str()).c_str()))
										{
											//设置视频编码输入格式
											SDVideoFrameImageBufInfo imageBufInfo;
											imageBufInfo.dwXSize = nWidth;
											imageBufInfo.dwYSize = nHeight;
											imageBufInfo.dwScanXByteSize = nWidth * 2;
											imageBufInfo.enumColorFormat = videoFrameImageBufInfo.enumColorFormat;
											imageBufInfo.enumScanMode = SDVIDEOSCANMODE_FirstFieldTop;

											SDAudioSamplesBufInfo audioBufInfo;
											audioBufInfo.dwChannels = audioInfo.dwChannels;
											audioBufInfo.dwBitsPerSample = audioInfo.dwBitsPerSample;
											audioBufInfo.dwSamplesPerSec = audioInfo.dwSamplesPerSec;
											audioBufInfo.dwAvgBitsPerSec = audioInfo.dwAvgBitsPerSec;
											audioBufInfo.dwBlockAlign = audioInfo.dwBlockAlign;
											audioBufInfo.enumAudioCFG = audioInfo.enumAudioCFG;
											audioBufInfo.enumChannelSamplesFormat = audioInfo.enumChannelSamplesFormat;
											//SResamplerPara resamplePara;
											if (pEncoder->SetInputParam(imageBufInfo, audioBufInfo, bForbidLoseFrame))
											{
												pEncoder->Start();
											}
											else
											{
												PostMessage(MSG_PUSHINFO, 0, (LPARAM)_T("Creating encoder SetInputParam error"));
											}
										}
										else
										{
											PostMessage(MSG_PUSHINFO, 0, (LPARAM)_T("Creating encoder SetSinkFile error"));
										}
									}
									else
									{
										PostMessage(MSG_PUSHINFO, 0, (LPARAM)_T("Creating encoder error"));
									}
								}
							}
						}
#endif
						while (bContinue)
						{
							if (WaitForSingleObject(m_evtPlayPause, 0) != WAIT_OBJECT_0)
							{
								int nClock = clock();
								SDRFrameInfo frameInfo;
								if (!bForcePtsAlign)
								{
									if (streamMediaInfoEx.dwVideoStreamCount > 0)
									{
										bContinue = pDecoder->GetVideoBuffer(m_nDispFrame, pVideoData, &frameInfo);
									}
									if (!bContinue)
									{
										strMsg.Format(_T("video get failed:frame:%d audio:%d"), m_nDispFrame, nAudioPos);
										PostMessage(MSG_PUSHINFO, 0, (LPARAM)strMsg.GetBuffer());
									}
									if (streamMediaInfoEx.dwAudioStreamCount > 0)
									{
										bContinue = pDecoder->GetAudioSamples(nAudioPos, SamplePerFrame, pAudioData, &numAudioSample);
										//bContinue = pDecoder->GetAudioSamples(-1, SamplePerFrame, pAudioData, &numAudioSample);
									}
									if (!bContinue)
									{
										strMsg.Format(_T("audio get failed:frame:%d audio:%d"), m_nDispFrame, nAudioPos);
										PostMessage(MSG_PUSHINFO, 0, (LPARAM)strMsg.GetBuffer());
									}
								}
								else
								{
									bContinue = pDecoder->GetVABuffer(pVideoData, pAudioData, &numAudioSample);
								}
#ifdef DEBUG_AUDIO_OUTFILE
								//音频先写到文件里
								fwrite(pAudioData, 1, numAudioSample * 8, pAudioFile);
#endif
#ifdef ENABLE_ENCODE
								for (size_t i = 0; i < 8; i++)
								{
									EncodecThreader *& pEncoder = m_pEncoder[i];
									if (pEncoder)
									{
										SDRFrameInfo frameInfoTmp;
										frameInfoTmp.emDataType = STREAM_DATATYPE_VIDEO;
										frameInfoTmp.iVersion = 0;		// 结构版本号。		4---4[序列化占用字节－序列化位置]
										//frameInfoTmp.iSize = frameInfo.iSize;// nWidth * nHeight * 2;			// 帧数据大小		4---16
										frameInfoTmp.iSize = pDecoder->GetVideoBufferSize();// nWidth * nHeight * 2;			// 帧数据大小		4---16
										frameInfoTmp.dwFrameIndex = m_nDispFrame;	// 帧数据流顺序		4---28
										frameInfoTmp.dwFrameNum = 1;		// 视频/音频帧数量	4---32
										frameInfoTmp.iSamplesOffset = 0;	// 标识RawAudio音频、视频帧中有效采样的偏移数，大于0表示从开始偏移，小于0表示从尾部开始向前偏移		4---36
										frameInfoTmp.qwDTS = m_nDispFrame * 40;			// 解码时间(90Khz单位)	8---44
										frameInfoTmp.qwPTS = m_nDispFrame * 40;			// 展现时间(90Khz单位)	8---52
										frameInfoTmp.qwDuration = 40;		// 持续时间(90Khz单位)	8---6
										frameInfoTmp.dwShowIndex = m_nDispFrame;	// 帧数据显示顺序			4---104
										frameInfoTmp.emFrameType = FRAMETYPE_I;   	// 帧类型 				4---108
										frameInfoTmp.extradata_size = 0;

										if (0)
										{
											FILE * file;
											fopen_s(&file, "h264.yuv", "wb+");
											if (file)
											{
												int nSize = frameInfoTmp.iSize;
												fwrite(pVideoData, nSize, 1, file);
												fclose(file);
											}
										}

										if (!pEncoder->PutFrameBuffer(pVideoData, frameInfoTmp.iSize, pAudioData, numAudioSample))
										{
											strMsg.Format(_T("encoder %d: lost one frame\n"), i);
											//PostMessage(MSG_PUSHINFO, 0, (LPARAM)strMsg.GetBuffer());
											OutputDebugString(strMsg);
										}
									}
								}
#endif
								m_nDispFrame++;
								nAudioPos += numAudioSample;
								if (bLoopPlay && !bContinue)
								{
									if (m_nDispFrame > 3)
									{
										m_nDispFrame = 0;
										nAudioPos = 0;
										bContinue = true;
										strMsg.Format(_T("loop mark repair continue:frame:%d audio:%d"), m_nDispFrame, nAudioPos);
										PostMessage(MSG_PUSHINFO, 0, (LPARAM)strMsg.GetBuffer());

										if (streamMediaInfoEx.dwVideoStreamCount > 0)
										{
											bContinue = pDecoder->GetVideoBuffer(m_nDispFrame, pVideoData, &frameInfo);
										}
										if (!bContinue)
										{
											strMsg.Format(_T("video get failed:frame:%d audio:%d"), m_nDispFrame, nAudioPos);
											PostMessage(MSG_PUSHINFO, 0, (LPARAM)strMsg.GetBuffer());
										}
										if (streamMediaInfoEx.dwAudioStreamCount > 0)
										{
											bContinue = pDecoder->GetAudioSamples(nAudioPos, SamplePerFrame, pAudioData, &numAudioSample);
											//bContinue = pDecoder->GetAudioSamples(-1, SamplePerFrame, pAudioData, &numAudioSample);
										}
										if (!bContinue)
										{
											strMsg.Format(_T("audio get failed:frame:%d audio:%d"), m_nDispFrame, nAudioPos);
											PostMessage(MSG_PUSHINFO, 0, (LPARAM)strMsg.GetBuffer());
										}
									}
								}
								Lock();
								m_nFrame++;
								Unlock();
								if (0)
								{
									FILE * file;
									fopen_s(&file, "out.yuv", "wb+");
									if (file)
									{
										fwrite(pVideoData, 1, nVideoBufferSize, file);  //V
										fclose(file);
									}
								}

								while (!m_vaLoop.Push(pVideoData, nVideoBufferSize, pAudioData, numAudioSample))
								{
									//push不进去就等5个毫秒再说
									if (WaitForSingleObject(m_evtPlayStop, 5) == WAIT_OBJECT_0)
									{
										break;
									}
								}
								
								if (WaitForSingleObject(m_evtPlayStop, 0) == WAIT_OBJECT_0)
								{
									break;
								}
								if (m_nFrame % 25 == 0)
								{
									if (m_bLogOpened)
									{
										int nValue = 0;
										strMsg = GetCpuInfoText(&nValue);
										m_fileLog.WriteString(strMsg);
										m_fileLog.WriteString(_T("\t"));
										if (nValue > nMaxCpu)
										{
											nMaxCpu = nValue;
										}

										nValue = 0;
										strMsg = GetMemInfoText(&nValue);
										m_fileLog.WriteString(strMsg);
										m_fileLog.WriteString(_T("\r\n"));
										if (nValue > nMaxMem)
										{
											nMaxMem = nValue;
										}
									}
								}
							}
							else
							{
								Lock();
								if (m_nFrame != m_nDispFrame)
								{
									SDRFrameInfo frameInfo;
									pDecoder->GetVideoBuffer(m_nFrame, pVideoData, &frameInfo);
									pDecoder->GetAudioSamples(m_nFrame * SamplePerFrame, SamplePerFrame, pAudioData, &numAudioSample);

									strMsg.Format(_T("m_nFrame=%d, m_nFrame * SamplePerFrame=%d"), m_nFrame, m_nFrame * SamplePerFrame);
									PostMessage(MSG_PUSHINFO, 0, (LPARAM)strMsg.GetBuffer());

									if (0)
									{
										FILE * file;
										fopen_s(&file, "out.yuv", "wb+");
										if (file)
										{
											fwrite(pVideoData, 1, nVideoBufferSize, file);  //V
											fclose(file);
										}
									}

									while (!m_vaLoop.Push(pVideoData, nVideoBufferSize, pAudioData, numAudioSample))
									{
										//push不进去就等5个毫秒再说
										if (WaitForSingleObject(m_evtPlayStop, 5) == WAIT_OBJECT_0)
										{
											break;
										}
									}
									m_nDispFrame = m_nFrame;
									nAudioPos = m_nFrame * SamplePerFrame;
								}
								Unlock();
								if (WaitForSingleObject(m_evtPlayStop, 1) == WAIT_OBJECT_0)
								{
									break;
								}
							}
						}
						delete pAudioData;
						pAudioData = nullptr;
						delete pVideoData;
						pVideoData = nullptr;
					}
				}
#ifdef DEBUG_AUDIO_OUTFILE
				fclose(pAudioFile); 
#endif

				//干掉解码器
				pDecoder->Release();
				m_ecfactory->DeleteProtocolDecoder(pDecoder);
				//干掉编码器
				for (size_t i = 0; i < 8; i++)
				{
					delete m_pEncoder[i];
					m_pEncoder[i] = nullptr;
				}
			}
		}
	}
	StopDisplay();
	PostMessage(MSG_PUSHINFO, 0, (LPARAM)_T("Stoped"));
	if (m_bLogOpened)
	{
		strMsg.Format(_T("maxcpu = %d"), nMaxCpu);
		m_fileLog.WriteString(strMsg);
		m_fileLog.WriteString(_T("\t"));

		strMsg.Format(_T("maxmem = %d"), nMaxMem);
		m_fileLog.WriteString(strMsg);
		m_fileLog.WriteString(_T("\r\n"));
	}
}

UINT CEncodecPressTestDlg::ThreadDisplay(LPVOID pParam)
{
	CEncodecPressTestDlg * pThis = (CEncodecPressTestDlg *)pParam;
	if (pThis)
	{
		pThis->DoDisplay();
	}
	return 0;
}

void CEncodecPressTestDlg::StartDisplay()
{
	StopDisplay();
	assert(m_pDisplayThread == nullptr);
	m_evtDisplayStop.ResetEvent();
	m_pDisplayThread = AfxBeginThread(ThreadDisplay, this);
}

void CEncodecPressTestDlg::StopDisplay()
{
	if (m_pDisplayThread)
	{
		m_evtDisplayStop.SetEvent();
		WaitForSingleObject(m_pDisplayThread->m_hThread, INFINITE);
		m_pDisplayThread = nullptr;
	}
}

void CEncodecPressTestDlg::DoDisplay()
{
	time_t tmLastPush = 0;
	while (true)
	{
		if (m_vaLoop.Pop(m_vaBuf))
		{
			//每40ms从队列里拿一帧出来
			time_t nWait = 40 - (clock() - tmLastPush);
			if (nWait < 1)
			{
				nWait = 1;
			}
			if (WaitForSingleObject(m_evtDisplayStop, nWait) == WAIT_OBJECT_0)
			{
				break;
			}
			TRACE(_T("m_vaLoop.Size()=%d\n"), m_vaLoop.Size());
			tmLastPush = clock();
			m_player.PushFrame(m_vaBuf.m_pVideoBuf, 1920 * 2);
			m_player.PushAudioSample(m_vaBuf.m_pAudioBuf, m_vaBuf.m_nAudioSampleCount * 4);
		}
		else
		{
			//没取到则等3ms
			if (WaitForSingleObject(m_evtDisplayStop, 3) == WAIT_OBJECT_0)
			{
				break;
			}
		}
	}
}

CEncodecPressTestDlg::CEncodecPressTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ENCODECPRESSTEST_DIALOG, pParent)
	, m_pPlayThread(nullptr)
	, m_evtPlayStop(FALSE, TRUE, NULL, NULL)
	, m_evtPlayPause(FALSE, TRUE, NULL, NULL)
	, m_nFrame(0)
	, m_nDispFrame(0)
	, m_ecfactory(nullptr)
	, m_bLogOpened(false)
	, m_pDisplayThread(nullptr)
	, m_evtDisplayStop(FALSE, TRUE, NULL, NULL)
{
	m_ecfactory = ecCodec_CreateCodecFactory();
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	InitializeCriticalSection(&m_lock);
	for (size_t i = 0; i < 8; i++)
	{
		m_pEncoder[i] = nullptr;
	}
}

CEncodecPressTestDlg::~CEncodecPressTestDlg()
{
	m_nFrame = 0;
	m_nDispFrame = 0;
	DeleteCriticalSection(&m_lock);
	for (size_t i = 0; i < 8; i++)
	{
		delete m_pEncoder[i];
		m_pEncoder[i] = nullptr;
	}
	ecCodec_ReleaseCodecFactory(m_ecfactory);
	if (m_bLogOpened)
	{
		m_fileLog.Close();
		m_bLogOpened = false;
	}
}

void CEncodecPressTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_SEEK, m_ctrSlider);
}

void CEncodecPressTestDlg::Lock()
{
	EnterCriticalSection(&m_lock);
}

void CEncodecPressTestDlg::Unlock()
{
	LeaveCriticalSection(&m_lock);
}

std::string CEncodecPressTestDlg::ConverCStringToStdString(CString & cstrValue)
{
	std::string strRet;
	strRet.clear();
	int nSize = ::WideCharToMultiByte(CP_ACP, 0, cstrValue.GetBuffer(), -1, NULL, 0, NULL, NULL);
	char * szcSrc = new char[nSize];
	memset(szcSrc, 0, sizeof(char) * nSize);
	::WideCharToMultiByte(CP_ACP, 0, cstrValue.GetBuffer(), -1, szcSrc, nSize, NULL, NULL);
	strRet = szcSrc;
	delete[] szcSrc;
	szcSrc = NULL;
	return strRet;
}

CString CEncodecPressTestDlg::ConvertStdStringToCString(const std::string & strValue)
{
	CString cstrRet;
	cstrRet.Empty();
	int nLength = ::MultiByteToWideChar(CP_ACP, 0, strValue.c_str(), -1, NULL, 0);
	TCHAR * szText1 = new TCHAR[nLength + 1];
	::MultiByteToWideChar(CP_ACP, 0, strValue.c_str(), -1, szText1, nLength + 1);
	cstrRet = szText1;
	delete[] szText1;
	szText1 = NULL;
	return cstrRet;
}

LRESULT CEncodecPressTestDlg::PushInfoMsg(WPARAM wParam, LPARAM lParam)
{
	PushInfo((LPCTSTR)lParam);
	return 0;
}

void CEncodecPressTestDlg::PushInfo(CString strInfo)
{
	CEdit * pWnd = (CEdit *)GetDlgItem(IDC_EDIT_INFOMATION);
	if (pWnd && ::IsWindow(pWnd->GetSafeHwnd()))
	{
		pWnd->SetSel(-1);
		pWnd->ReplaceSel(strInfo);
		pWnd->SetSel(-1);
		pWnd->ReplaceSel(_T("\r\n"));
	}
}

BEGIN_MESSAGE_MAP(CEncodecPressTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_START, &CEncodecPressTestDlg::OnBnClickedBtnStart)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_PAUSE, &CEncodecPressTestDlg::OnBnClickedBtnPause)
	ON_BN_CLICKED(IDC_BTN_STOP, &CEncodecPressTestDlg::OnBnClickedBtnStop)
	ON_BN_CLICKED(IDC_BTN_CHOOSE_FILE, &CEncodecPressTestDlg::OnBnClickedBtnChooseFile)
	ON_MESSAGE(MSG_PUSHINFO, &CEncodecPressTestDlg::PushInfoMsg)
	ON_BN_CLICKED(IDC_BTN_OUT_CHOOSE_FILE, &CEncodecPressTestDlg::OnBnClickedBtnOutChooseFile)
	ON_WM_HSCROLL()
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_SEEK, &CEncodecPressTestDlg::OnNMReleasedcaptureSliderSeek)
	ON_BN_CLICKED(IDC_CHECK_ENCODEC1, &CEncodecPressTestDlg::OnBnClickedCheckEncodec1)
	ON_BN_CLICKED(IDC_CHECK_ENCODEC2, &CEncodecPressTestDlg::OnBnClickedCheckEncodec2)
	ON_BN_CLICKED(IDC_CHECK_ENCODEC3, &CEncodecPressTestDlg::OnBnClickedCheckEncodec3)
	ON_BN_CLICKED(IDC_CHECK_ENCODEC4, &CEncodecPressTestDlg::OnBnClickedCheckEncodec4)
	ON_BN_CLICKED(IDC_CHECK_ENCODEC5, &CEncodecPressTestDlg::OnBnClickedCheckEncodec5)
	ON_BN_CLICKED(IDC_CHECK_ENCODEC6, &CEncodecPressTestDlg::OnBnClickedCheckEncodec6)
	ON_BN_CLICKED(IDC_CHECK_ENCODEC7, &CEncodecPressTestDlg::OnBnClickedCheckEncodec7)
	ON_BN_CLICKED(IDC_CHECK_ENCODEC8, &CEncodecPressTestDlg::OnBnClickedCheckEncodec8)
	ON_BN_CLICKED(IDC_BTN_COPY_FIRST_PARAM, &CEncodecPressTestDlg::OnBnClickedBtnCopyFirstParam)
END_MESSAGE_MAP()

// CEncodecPressTestDlg 消息处理程序

void CEncodecPressTestDlg::OnDestroy()
{
	StopPlay();
	StopDisplay();
	CDialogEx::OnDestroy();
}

RECT CallbackGetDrawRect(HWND hWnd)
{
	RECT rtRet = {0};
	::GetClientRect(hWnd, &rtRet);
	POINT po;
	po.x = rtRet.left;
	po.y = rtRet.top;
	::ClientToScreen(hWnd, &po);
	rtRet.top += po.y;
	rtRet.left += po.x;
	rtRet.right += po.x;
	rtRet.bottom += po.y;
	return rtRet;
}

BOOL CEncodecPressTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	CWnd * pPlayerWnd = GetDlgItem(IDC_DECODER_SCREEN);
	if (pPlayerWnd && ::IsWindow(pPlayerWnd->GetSafeHwnd()))
	{
		CRect rtPlayer;
		pPlayerWnd->GetWindowRect(rtPlayer);
#ifdef PLAYER_USE_SDLPAINT
		m_player.IntialWnd(SDL_PIXELFORMAT_UYVY, pPlayerWnd->GetSafeHwnd(), rtPlayer.Width(), rtPlayer.Height(), rtPlayer.Width(), rtPlayer.Height(), 48000, 1920);
#else
		m_player.IntialWnd(SDL_PIXELFORMAT_UYVY, pPlayerWnd->GetSafeHwnd(), rtPlayer.Width(), rtPlayer.Height(), rtPlayer.Width(), rtPlayer.Height(), 48000, 1920, CallbackGetDrawRect);
#endif
	}

	CWnd * pWnd = GetDlgItem(IDC_EDIT_OUT_FILE_PATH);
	if (pWnd && ::IsWindow(pWnd->GetSafeHwnd()))
	{
		pWnd->SetWindowText(_T("E:\\clip\\"));
	}

	CEdit * pEdit = (CEdit *)GetDlgItem(IDC_EDIT_INFOMATION);
	if (pEdit && ::IsWindow(pEdit->GetSafeHwnd()))
	{
		pEdit->SetLimitText(-1);
	}

	pEdit = (CEdit *)GetDlgItem(IDC_EDIT_FILE_PATH);
	if (pEdit && ::IsWindow(pEdit->GetSafeHwnd()))
	{
		pEdit->SetWindowText(_T("rtmp://live.hkstv.hk.lxdns.com/live/hks"));
	}

	m_ctrSlider.SetRange(0, 100);
	m_ctrSlider.SetTicFreq(10);

	for (size_t i = 0; i < 8; i++)
	{
		//combox选第一项，文件名选inddex
		CComboBox * pVideoStandardComb = GetCodecVideoStandardCombo(i);
		CComboBox * pVideoTypeComb = GetCodecVideoTypeCombo(i);
		CComboBox * pColorFmtComb = GetCodecColorFmtCombo(i);
		CComboBox * pAudioTypeComb = GetCodecAudioTypeCombo(i);
		CEdit *		pFileNameEdit = GetCodecFileNameEdit(i);
		CEdit *		pH264LevelEdit = GetCodecH264LevelEdit(i);
		if (pVideoStandardComb
			&& pVideoTypeComb
			&& pColorFmtComb
			&& pAudioTypeComb
			&& pFileNameEdit
			&& pH264LevelEdit
			)
		{
			switch (i)
			{
			case 0:
				pVideoStandardComb->SetCurSel(1);
				pVideoTypeComb->SetCurSel(3);
				pColorFmtComb->SetCurSel(2);
				pAudioTypeComb->SetCurSel(0);
				break;
			case 1:
				pVideoStandardComb->SetCurSel(0);
				pVideoTypeComb->SetCurSel(0);
				pColorFmtComb->SetCurSel(1);
				pAudioTypeComb->SetCurSel(0);
				break;
			case 2:
				pVideoStandardComb->SetCurSel(0);
				pVideoTypeComb->SetCurSel(1);
				pColorFmtComb->SetCurSel(0);
				pAudioTypeComb->SetCurSel(1);
				break;
			case 3:
				pVideoStandardComb->SetCurSel(0);
				pVideoTypeComb->SetCurSel(2);
				pColorFmtComb->SetCurSel(0);
				pAudioTypeComb->SetCurSel(2);
				break;
			case 4:
				pVideoStandardComb->SetCurSel(1);
				pVideoTypeComb->SetCurSel(0);
				pColorFmtComb->SetCurSel(0);
				pAudioTypeComb->SetCurSel(0);
				break;
			case 5:
				pVideoStandardComb->SetCurSel(1);
				pVideoTypeComb->SetCurSel(0);
				pColorFmtComb->SetCurSel(1);
				pAudioTypeComb->SetCurSel(0);
				break;
			case 6:
				pVideoStandardComb->SetCurSel(1);
				pVideoTypeComb->SetCurSel(1);
				pColorFmtComb->SetCurSel(0);
				pAudioTypeComb->SetCurSel(1);
				break;
			case 7:
				pVideoStandardComb->SetCurSel(1);
				pVideoTypeComb->SetCurSel(2);
				pColorFmtComb->SetCurSel(0);
				pAudioTypeComb->SetCurSel(2);
				break;
			default:
				break;
			}
			CString strName = _T("encodec");
			pFileNameEdit->SetWindowText(strName);
			pH264LevelEdit->SetWindowText(_T("5"));
		}
	}

	CString strFileName;
	CTime tm = CTime::GetCurrentTime();
	strFileName.Format(_T("%04d%02d%02d%02d%02d%02d_%d.txt"), tm.GetYear(), tm.GetMonth(), tm.GetDay(), tm.GetHour(), tm.GetMinute(), tm.GetSecond(), clock());
	if (!m_bLogOpened && m_fileLog.Open(strFileName, CFile::modeCreate | CFile::modeWrite))
	{
		m_bLogOpened = true;
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CEncodecPressTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CEncodecPressTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CEncodecPressTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CEncodecPressTestDlg::OnBnClickedBtnStart()
{
	StartPlay();
}

void CEncodecPressTestDlg::OnBnClickedBtnPause()
{
	PausePlay();
}

void CEncodecPressTestDlg::OnBnClickedBtnStop()
{
	StopPlay();
}


void CEncodecPressTestDlg::OnBnClickedBtnChooseFile()
{
	CWnd * pWnd = GetDlgItem(IDC_EDIT_FILE_PATH);
	if (pWnd && ::IsWindow(pWnd->GetSafeHwnd()))
	{
		CFileDialog dialog(TRUE);
		if (dialog.DoModal() == IDOK)
		{
			CString strPath = dialog.GetPathName();
			pWnd->SetWindowText(strPath);
		}
	}
}


void CEncodecPressTestDlg::OnBnClickedBtnOutChooseFile()
{
	CWnd * pWnd = GetDlgItem(IDC_EDIT_OUT_FILE_PATH);
	if (pWnd && ::IsWindow(pWnd->GetSafeHwnd()))
	{
		CFileDialog dialog(FALSE);
		if (dialog.DoModal() == IDOK)
		{
			CString strPath = dialog.GetPathName();
			pWnd->SetWindowText(strPath);
		}
	}
}


void CEncodecPressTestDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (pScrollBar)
	{
		int nID = pScrollBar->GetDlgCtrlID();
		if (nID == IDC_SLIDER_SEEK)
		{
			Lock();
			m_nFrame = m_ctrSlider.GetPos();
			Unlock();
		}
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CEncodecPressTestDlg::OnNMReleasedcaptureSliderSeek(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (::IsWindow(m_ctrSlider.GetSafeHwnd()))
	{
		Lock();
		m_nFrame = m_ctrSlider.GetPos();
		Unlock();
	}
	*pResult = 0;
}

CButton * CEncodecPressTestDlg::GetCodecCheckBtn(int nCodecIndex)
{
	CWnd * pWnd = nullptr;
	switch (nCodecIndex)
	{
	case 0:
		pWnd = GetDlgItem(IDC_CHECK_ENCODEC1);
		break;
	case 1:
		pWnd = GetDlgItem(IDC_CHECK_ENCODEC2);
		break;
	case 2:
		pWnd = GetDlgItem(IDC_CHECK_ENCODEC3);
		break;
	case 3:
		pWnd = GetDlgItem(IDC_CHECK_ENCODEC4);
		break;
	case 4:
		pWnd = GetDlgItem(IDC_CHECK_ENCODEC5);
		break;
	case 5:
		pWnd = GetDlgItem(IDC_CHECK_ENCODEC6);
		break;
	case 6:
		pWnd = GetDlgItem(IDC_CHECK_ENCODEC7);
		break;
	default:
		pWnd = GetDlgItem(IDC_CHECK_ENCODEC8);
		break;
	}
	if (pWnd && ::IsWindow(pWnd->GetSafeHwnd()))
	{
		return (CButton *)pWnd;
	}
	return nullptr;
}

CComboBox * CEncodecPressTestDlg::GetCodecVideoStandardCombo(int nCodecIndex)
{
	CWnd * pWnd = nullptr;
	switch (nCodecIndex)
	{
	case 0:
		pWnd = GetDlgItem(IDC_COMBO_VIDEOSTANDARD_CODEC1);
		break;
	case 1:
		pWnd = GetDlgItem(IDC_COMBO_VIDEOSTANDARD_CODEC2);
		break;
	case 2:
		pWnd = GetDlgItem(IDC_COMBO_VIDEOSTANDARD_CODEC3);
		break;
	case 3:
		pWnd = GetDlgItem(IDC_COMBO_VIDEOSTANDARD_CODEC4);
		break;
	case 4:
		pWnd = GetDlgItem(IDC_COMBO_VIDEOSTANDARD_CODEC5);
		break;
	case 5:
		pWnd = GetDlgItem(IDC_COMBO_VIDEOSTANDARD_CODEC6);
		break;
	case 6:
		pWnd = GetDlgItem(IDC_COMBO_VIDEOSTANDARD_CODEC7);
		break;
	default:
		pWnd = GetDlgItem(IDC_COMBO_VIDEOSTANDARD_CODEC8);
		break;
	}
	if (pWnd && ::IsWindow(pWnd->GetSafeHwnd()))
	{
		return (CComboBox *)pWnd;
	}
	return nullptr;
}

CComboBox * CEncodecPressTestDlg::GetCodecVideoTypeCombo(int nCodecIndex)
{
	CWnd * pWnd = nullptr;
	switch (nCodecIndex)
	{
	case 0:
		pWnd = GetDlgItem(IDC_COMBO_VIDEOTYPE_CODEC1);
		break;
	case 1:
		pWnd = GetDlgItem(IDC_COMBO_VIDEOTYPE_CODEC2);
		break;
	case 2:
		pWnd = GetDlgItem(IDC_COMBO_VIDEOTYPE_CODEC3);
		break;
	case 3:
		pWnd = GetDlgItem(IDC_COMBO_VIDEOTYPE_CODEC4);
		break;
	case 4:
		pWnd = GetDlgItem(IDC_COMBO_VIDEOTYPE_CODEC5);
		break;
	case 5:
		pWnd = GetDlgItem(IDC_COMBO_VIDEOTYPE_CODEC6);
		break;
	case 6:
		pWnd = GetDlgItem(IDC_COMBO_VIDEOTYPE_CODEC7);
		break;
	default:
		pWnd = GetDlgItem(IDC_COMBO_VIDEOTYPE_CODEC8);
		break;
	}
	if (pWnd && ::IsWindow(pWnd->GetSafeHwnd()))
	{
		return (CComboBox *)pWnd;
	}
	return nullptr;
}

CComboBox * CEncodecPressTestDlg::GetCodecColorFmtCombo(int nCodecIndex)
{
	CWnd * pWnd = nullptr;
	switch (nCodecIndex)
	{
	case 0:
		pWnd = GetDlgItem(IDC_COMBO_COLORFMT_CODEC1);
		break;
	case 1:
		pWnd = GetDlgItem(IDC_COMBO_COLORFMT_CODEC2);
		break;
	case 2:
		pWnd = GetDlgItem(IDC_COMBO_COLORFMT_CODEC3);
		break;
	case 3:
		pWnd = GetDlgItem(IDC_COMBO_COLORFMT_CODEC4);
		break;
	case 4:
		pWnd = GetDlgItem(IDC_COMBO_COLORFMT_CODEC5);
		break;
	case 5:
		pWnd = GetDlgItem(IDC_COMBO_COLORFMT_CODEC6);
		break;
	case 6:
		pWnd = GetDlgItem(IDC_COMBO_COLORFMT_CODEC7);
		break;
	default:
		pWnd = GetDlgItem(IDC_COMBO_COLORFMT_CODEC8);
		break;
	}
	if (pWnd && ::IsWindow(pWnd->GetSafeHwnd()))
	{
		return (CComboBox *)pWnd;
	}
	return nullptr;
}

CComboBox * CEncodecPressTestDlg::GetCodecAudioTypeCombo(int nCodecIndex)
{
	CWnd * pWnd = nullptr;
	switch (nCodecIndex)
	{
	case 0:
		pWnd = GetDlgItem(IDC_COMBO_AUDIOTYPE_CODEC1);
		break;
	case 1:
		pWnd = GetDlgItem(IDC_COMBO_AUDIOTYPE_CODEC2);
		break;
	case 2:
		pWnd = GetDlgItem(IDC_COMBO_AUDIOTYPE_CODEC3);
		break;
	case 3:
		pWnd = GetDlgItem(IDC_COMBO_AUDIOTYPE_CODEC4);
		break;
	case 4:
		pWnd = GetDlgItem(IDC_COMBO_AUDIOTYPE_CODEC5);
		break;
	case 5:
		pWnd = GetDlgItem(IDC_COMBO_AUDIOTYPE_CODEC6);
		break;
	case 6:
		pWnd = GetDlgItem(IDC_COMBO_AUDIOTYPE_CODEC7);
		break;
	default:
		pWnd = GetDlgItem(IDC_COMBO_AUDIOTYPE_CODEC8);
		break;
	}
	if (pWnd && ::IsWindow(pWnd->GetSafeHwnd()))
	{
		return (CComboBox *)pWnd;
	}
	return nullptr;
}

CEdit * CEncodecPressTestDlg::GetCodecH264LevelEdit(int nCodecIndex)
{
	CWnd * pWnd = nullptr;
	switch (nCodecIndex)
	{
	case 0:
		pWnd = GetDlgItem(IDC_EDIT_H264LEVEL_CODEC1);
		break;
	case 1:
		pWnd = GetDlgItem(IDC_EDIT_H264LEVEL_CODEC2);
		break;
	case 2:
		pWnd = GetDlgItem(IDC_EDIT_H264LEVEL_CODEC3);
		break;
	case 3:
		pWnd = GetDlgItem(IDC_EDIT_H264LEVEL_CODEC4);
		break;
	case 4:
		pWnd = GetDlgItem(IDC_EDIT_H264LEVEL_CODEC5);
		break;
	case 5:
		pWnd = GetDlgItem(IDC_EDIT_H264LEVEL_CODEC6);
		break;
	case 6:
		pWnd = GetDlgItem(IDC_EDIT_H264LEVEL_CODEC7);
		break;
	default:
		pWnd = GetDlgItem(IDC_EDIT_H264LEVEL_CODEC8);
		break;
	}
	if (pWnd && ::IsWindow(pWnd->GetSafeHwnd()))
	{
		return (CEdit *)pWnd;
	}
	return nullptr;
}

CEdit * CEncodecPressTestDlg::GetCodecFileNameEdit(int nCodecIndex)
{
	CWnd * pWnd = nullptr;
	switch (nCodecIndex)
	{
	case 0:
		pWnd = GetDlgItem(IDC_EDIT_FILENAME_CODEC1);
		break;
	case 1:
		pWnd = GetDlgItem(IDC_EDIT_FILENAME_CODEC2);
		break;
	case 2:
		pWnd = GetDlgItem(IDC_EDIT_FILENAME_CODEC3);
		break;
	case 3:
		pWnd = GetDlgItem(IDC_EDIT_FILENAME_CODEC4);
		break;
	case 4:
		pWnd = GetDlgItem(IDC_EDIT_FILENAME_CODEC5);
		break;
	case 5:
		pWnd = GetDlgItem(IDC_EDIT_FILENAME_CODEC6);
		break;
	case 6:
		pWnd = GetDlgItem(IDC_EDIT_FILENAME_CODEC7);
		break;
	default:
		pWnd = GetDlgItem(IDC_EDIT_FILENAME_CODEC8);
		break;
	}
	if (pWnd && ::IsWindow(pWnd->GetSafeHwnd()))
	{
		return (CEdit *)pWnd;
	}
	return nullptr;
}

CEdit * CEncodecPressTestDlg::GetCodecFileSurfixEdit(int nCodecIndex)
{
	CWnd * pWnd = nullptr;
	switch (nCodecIndex)
	{
	case 0:
		pWnd = GetDlgItem(IDC_EDIT_FILESUFIX_CODEC1);
		break;
	case 1:
		pWnd = GetDlgItem(IDC_EDIT_FILESUFIX_CODEC2);
		break;
	case 2:
		pWnd = GetDlgItem(IDC_EDIT_FILESUFIX_CODEC3);
		break;
	case 3:
		pWnd = GetDlgItem(IDC_EDIT_FILESUFIX_CODEC4);
		break;
	case 4:
		pWnd = GetDlgItem(IDC_EDIT_FILESUFIX_CODEC5);
		break;
	case 5:
		pWnd = GetDlgItem(IDC_EDIT_FILESUFIX_CODEC6);
		break;
	case 6:
		pWnd = GetDlgItem(IDC_EDIT_FILESUFIX_CODEC7);
		break;
	default:
		pWnd = GetDlgItem(IDC_EDIT_FILESUFIX_CODEC8);
		break;
	}
	if (pWnd && ::IsWindow(pWnd->GetSafeHwnd()))
	{
		return (CEdit *)pWnd;
	}
	return nullptr;
}

void CEncodecPressTestDlg::OnCheckEncodec(int nIndex)
{
	CButton * pBtn = GetCodecCheckBtn(nIndex);
	bool bCheck = pBtn->GetCheck() > 0;
	if (bCheck)
	{
		for (size_t i = 0; i < nIndex; i++)
		{
			CButton * pBtnBefore = GetCodecCheckBtn(i);
			if (pBtnBefore)
			{
				pBtnBefore->SetCheck(true);
			}
		}
	}
	else
	{
		for (size_t i = nIndex; i < 8; i++)
		{
			CButton * pBtnAfter = GetCodecCheckBtn(i);
			if (pBtnAfter)
			{
				pBtnAfter->SetCheck(false);
			}
		}
	}
	DealCtrlFileName();
}

bool CEncodecPressTestDlg::GetCodecCheck(int nIndex)
{
	bool bRet = false;
	CButton * pBtn = GetCodecCheckBtn(nIndex);
	if (pBtn)
	{
		bRet = pBtn->GetCheck();
	}
	return bRet;
}

SD_VIDEO_STANDARD CEncodecPressTestDlg::GetCodecVideoStandard(int nIndex)
{
	SD_VIDEO_STANDARD emRet = SDVIDEOSTANDARD_PAL;
	CComboBox * pCombo = GetCodecVideoStandardCombo(nIndex);
	if (pCombo)
	{
		int nSel = pCombo->GetCurSel();
		if (nSel == 0)
		{
			emRet = SDVIDEOSTANDARD_PAL;
		}
		else
		{
			emRet = SDVIDEOSTANDARD_HD1080i_25;
		}
	}
	return emRet;
}

SD_VIDEO_TYPE CEncodecPressTestDlg::GetCodecVideoType(int nIndex)
{
	SD_VIDEO_TYPE emRet = SDVIDEOTYPE_H264;
	CComboBox * pCombo = GetCodecVideoTypeCombo(nIndex);
	if (pCombo)
	{
		int nSel = pCombo->GetCurSel();
		if (nSel == 0)
		{
			emRet = SDVIDEOTYPE_H264;
		}
		else if (nSel == 1)
		{
			emRet = SDVIDEOTYPE_MPEG4;
		}
		else if (nSel == 2)
		{
			emRet = SDVIDEOTYPE_MPEG2_IFRAME;
		}
		else if (nSel == 3)
		{
			emRet = SDVIDEOTYPE_H264_INTEL;
		}
	}
	return emRet;
}

SD_COLOR_FORMAT CEncodecPressTestDlg::GetCodecColorFmt(int nIndex)
{
	SD_COLOR_FORMAT emRet = SDCOLORFORMAT_YUVP_420;
	CComboBox * pCombo = GetCodecColorFmtCombo(nIndex);
	if (pCombo)
	{
		int nSel = pCombo->GetCurSel();
		if (nSel == 0)
		{
			emRet = SDCOLORFORMAT_YUVP_420;
		}
		else if (nSel == 1)
		{
			emRet = SDCOLORFORMAT_YUVP_422;
		}
		else
		{
			emRet = SDCOLORFORMAT_INTEL;
		}
	}
	return emRet;
}

SD_AUDIO_TYPE CEncodecPressTestDlg::GetCodecAudioType(int nIndex)
{
	SD_AUDIO_TYPE emRet = SDAUDIOTYPE_AAC;
	CComboBox * pCombo = GetCodecAudioTypeCombo(nIndex);
	if (pCombo)
	{
		int nSel = pCombo->GetCurSel();
		if (nSel == 0)
		{
			emRet = SDAUDIOTYPE_AAC;
		}
		else if (nSel == 1)
		{
			emRet = SDAUDIOTYPE_MP3;
		}
		else
		{
			emRet = SDAUDIOTYPE_WAVE_PCM;
		}
	}
	return emRet;
}

int CEncodecPressTestDlg::GetCodecH264Level(int nIndex)
{
	int nRet = 0;
	CEdit * pEdit = GetCodecH264LevelEdit(nIndex);
	if (pEdit)
	{
		CString strNum;
		pEdit->GetWindowText(strNum);
		nRet = _ttoi(strNum);
	}
	return nRet;
}

void CEncodecPressTestDlg::DealCtrlFileName()
{
	std::set<CString> setFileName;
	for (size_t i = 0; i < 8; i++)
	{
		if (GetCodecCheck(i))
		{
			SD_VIDEO_STANDARD emVideoStandard = GetCodecVideoStandard(i);
			SD_VIDEO_TYPE emVideoType = GetCodecVideoType(i);
			SD_COLOR_FORMAT emColorFmt = GetCodecColorFmt(i);
			SD_AUDIO_TYPE emAudioType = GetCodecAudioType(i);
			int nH264Level = GetCodecH264Level(i);

			CString strFileName = GenerateFileInfoName(emVideoStandard, emVideoType, emColorFmt, emAudioType, nH264Level);
			CString strTmpName = strFileName;
			//文件名去重
			int nTail = 1;
			while (setFileName.count(strTmpName) > 0)
			{
				strTmpName.Format(_T("%s(%d)"), strFileName, nTail++);
			}
			setFileName.insert(strTmpName);
			GetCodecFileNameEdit(i)->SetWindowText(strTmpName);

			SDStreamMediaInfo streamInfo;
			CString strSuffix = GetPresetMediaInfo(emVideoStandard, emVideoType, emColorFmt, emAudioType, 48000, nH264Level, streamInfo);
			GetCodecFileSurfixEdit(i)->SetWindowText(strSuffix);

			GetCodecVideoStandardCombo(i)->EnableWindow(false);
			GetCodecVideoTypeCombo(i)->EnableWindow(false);
			GetCodecColorFmtCombo(i)->EnableWindow(false);
			GetCodecAudioTypeCombo(i)->EnableWindow(false);
			GetCodecFileNameEdit(i)->SetReadOnly(true);
		}
		else
		{
			GetCodecFileNameEdit(i)->SetWindowText(_T("encodec"));

			GetCodecVideoStandardCombo(i)->EnableWindow(true);
			GetCodecVideoTypeCombo(i)->EnableWindow(true);
			GetCodecColorFmtCombo(i)->EnableWindow(true);
			GetCodecAudioTypeCombo(i)->EnableWindow(true);
			GetCodecFileNameEdit(i)->SetReadOnly(false);
		}
	}
}

CString CEncodecPressTestDlg::GenerateFileInfoName(SD_VIDEO_STANDARD emVideoStandard, SD_VIDEO_TYPE emVideoType, SD_COLOR_FORMAT emColorFormat, SD_AUDIO_TYPE emAudioType, int nH264Level)
{
	CString strFileName;
	switch (emVideoStandard)
	{
	case SDVIDEOSTANDARD_PAL:
		strFileName.AppendFormat(_T("PAL"));
		break;
	case SDVIDEOSTANDARD_HD1080i_25:
		strFileName.AppendFormat(_T("HD"));
		break;
	default:
		break;
	}
	switch (emVideoType)
	{
	case SDVIDEOTYPE_MPEG2_IFRAME:
		strFileName.AppendFormat(_T("_MPEG2_I"));
		break;
	case SDVIDEOTYPE_MPEG4:
		strFileName.AppendFormat(_T("_MPEG4"));
		break;
	case SDVIDEOTYPE_H264:
		strFileName.AppendFormat(_T("_H264"));
		strFileName.AppendFormat(_T("_%d"), nH264Level);
		break;
	case SDVIDEOTYPE_H264_INTEL:
		strFileName.AppendFormat(_T("_Intel264"));
		strFileName.AppendFormat(_T("_%d"), nH264Level);
		break;
	default:
		break;
	}
	switch (emColorFormat)
	{
	case SDCOLORFORMAT_YUVP_422:
		strFileName.AppendFormat(_T("_YUV422p"));
		break;
	case SDCOLORFORMAT_YUVP_420:
		strFileName.AppendFormat(_T("_YUV420p"));
		break;
	case SDCOLORFORMAT_INTEL:
		strFileName.AppendFormat(_T("_Intel_NV12"));
		break;
	default:
		break;
	}
	switch (emAudioType)
	{
	case SDAUDIOTYPE_WAVE_PCM:
		strFileName.AppendFormat(_T("_pcm"));
		break;
	case SDAUDIOTYPE_MP3:
		strFileName.AppendFormat(_T("_mp3"));
		break;
	case SDAUDIOTYPE_AAC:
		strFileName.AppendFormat(_T("_aac"));
		break;
	default:
		break;
	}
	return strFileName;
}

void CEncodecPressTestDlg::OnBnClickedCheckEncodec1()
{
	OnCheckEncodec(0);
}
void CEncodecPressTestDlg::OnBnClickedCheckEncodec2()
{
	OnCheckEncodec(1);
}
void CEncodecPressTestDlg::OnBnClickedCheckEncodec3()
{
	OnCheckEncodec(2);
}
void CEncodecPressTestDlg::OnBnClickedCheckEncodec4()
{
	OnCheckEncodec(3);
}
void CEncodecPressTestDlg::OnBnClickedCheckEncodec5()
{
	OnCheckEncodec(4);
}
void CEncodecPressTestDlg::OnBnClickedCheckEncodec6()
{
	OnCheckEncodec(5);
}
void CEncodecPressTestDlg::OnBnClickedCheckEncodec7()
{
	OnCheckEncodec(6);
}
void CEncodecPressTestDlg::OnBnClickedCheckEncodec8()
{
	OnCheckEncodec(7);
}



void CEncodecPressTestDlg::OnBnClickedBtnCopyFirstParam()
{
	int nSel1 = 0;
	int nSel2 = 0;
	int nSel3 = 0;
	int nSel4 = 0;
	int nSel5 = 0;
	for (size_t i = 0; i < 8; i++)
	{
		//combox选第一项，文件名选inddex
		CComboBox * pVideoStandardComb = GetCodecVideoStandardCombo(i);
		CComboBox * pVideoTypeComb = GetCodecVideoTypeCombo(i);
		CComboBox * pColorFmtComb = GetCodecColorFmtCombo(i);
		CComboBox * pAudioTypeComb = GetCodecAudioTypeCombo(i);
		CEdit *		pFileNameEdit = GetCodecFileNameEdit(i);
		CEdit *		pH264LevelEdit = GetCodecH264LevelEdit(i);
		if (pVideoStandardComb
			&& pVideoTypeComb
			&& pColorFmtComb
			&& pAudioTypeComb
			&& pFileNameEdit
			&& pH264LevelEdit
			)
		{
			if (0 == i)
			{
				nSel1 = pVideoStandardComb->GetCurSel();
				nSel2 = pVideoTypeComb->GetCurSel();
				nSel3 = pColorFmtComb->GetCurSel();
				nSel4 = pAudioTypeComb->GetCurSel();
				nSel5 = GetCodecH264Level(i);
			}
			else
			{
				pVideoStandardComb->SetCurSel(nSel1);
				pVideoTypeComb->SetCurSel(nSel2);
				pColorFmtComb->SetCurSel(nSel3);
				pAudioTypeComb->SetCurSel(nSel4);
				CString strLevel;
				strLevel.Format(_T("%d"), nSel5);
				pH264LevelEdit->SetWindowText(strLevel);
			}
			CString strName = _T("encodec");
			pFileNameEdit->SetWindowText(strName);
		}
	}
}
