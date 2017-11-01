
// EncodecPressTestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "EncodecPressTest.h"
#include "EncodecPressTestDlg.h"
#include "afxdialogex.h"
#include "FFmpegVADecoder.h"

CString GetPresetMediaInfo(EmVideoStandard emVideoStandard, SD_VIDEO_TYPE emVideoType, SD_COLOR_FORMAT emColorFormat, SD_AUDIO_TYPE emAudioType, DWORD dwSamplePerSec, OUT SDStreamMediaInfo & streamInfo)
{
	switch (emVideoStandard)
	{
	case EmVideoStandard_PAL:
		streamInfo.sVideoMediaInfo.dwWidth = 720;////////////////////////////////////////////////////////////////////////////
		streamInfo.sVideoMediaInfo.dwHeight = 576;////////////////////////////////////////////////////////////////////////////
		streamInfo.sVideoMediaInfo.dwStandardRate = 25;////////////////////////////////////////////////////////////////////////////
		streamInfo.sVideoMediaInfo.dwStandardScale = 1;////////////////////////////////////////////////////////////////////////////
		streamInfo.sVideoMediaInfo.dwDisplayWidth = 4;////////////////////////////////////////////////////////////////////////////
		streamInfo.sVideoMediaInfo.dwDisplayHeight = 3;////////////////////////////////////////////////////////////////////////////
		break;
	case EmVideoStandard_HD:
		streamInfo.sVideoMediaInfo.dwWidth = 1920;////////////////////////////////////////////////////////////////////////////
		streamInfo.sVideoMediaInfo.dwHeight = 1080;////////////////////////////////////////////////////////////////////////////
		streamInfo.sVideoMediaInfo.dwStandardRate = 25;////////////////////////////////////////////////////////////////////////////
		streamInfo.sVideoMediaInfo.dwStandardScale = 1;////////////////////////////////////////////////////////////////////////////
		streamInfo.sVideoMediaInfo.dwDisplayWidth = 16;////////////////////////////////////////////////////////////////////////////
		streamInfo.sVideoMediaInfo.dwDisplayHeight = 9;////////////////////////////////////////////////////////////////////////////
		break;
	default:
		break;
	}

	streamInfo.enumStreamMediaType = SDSTREAMTYPE_OPENDML_AVI;
	streamInfo.dwStreamMediaSubType = 0;
	streamInfo.dwVideoStreamCount = 1;
	streamInfo.dwTotalAverDataRateInBitsPerSec = 0;
	streamInfo.dwTotalMaxDataRateInBitsPerSec = 0;
	streamInfo.dwTotalMinDataRateInBitsPerSec = 0;
	streamInfo.sVideoMediaInfo.enumScanMode = SDVIDEOSCANMODE_FirstFieldTop;
	streamInfo.sVideoMediaInfo.enumColorFormat = emColorFormat;//(SDCOLORFORMAT_YUVP_420)////////////////////////////////////////////////////////////////////////////
	streamInfo.sVideoMediaInfo.enumVideoType = emVideoType; //(SDVIDEOTYPE_H264)////////////////////////////////////////////////////////////////////////////
	streamInfo.sVideoMediaInfo.dwVideoSubType = PROFILE_AVC_MAIN;
	streamInfo.sVideoMediaInfo.dwDataRateInBitsPerSec = 25000000;// 400000;////////////////////////////////////////////////////////////////////////////
	streamInfo.sVideoMediaInfo.enumDataRateType = SDDATARATE_CONSTANT;
	streamInfo.sVideoMediaInfo.dwGOPSize = 100;////////////////////////////////////////////////////////////////////////////
	streamInfo.sVideoMediaInfo.dwReferencePeriod = 1;
	streamInfo.sVideoMediaInfo.bIsClipped = 1;
	streamInfo.sVideoMediaInfo.dwMaxDataRateInBitsPerSec = 0;
	streamInfo.sVideoMediaInfo.dwMinDataRateInBitsPerSec = 0;
	streamInfo.sVideoMediaInfo.dwStruSize = sizeof(SDVideoMediaInfo);
	streamInfo.dwAudioStreamCount = 1;
	streamInfo.sAudioMediaInfo.enumAudioType = emAudioType;		// 音频编解码类型。////////////////////////////////////////////////////////////////////////////
	streamInfo.sAudioMediaInfo.dwAudioSubType = 0;		// 音频编解码的子类型,子类型定义随enumAudioType不同而不同
	streamInfo.sAudioMediaInfo.dwChannels = 2;			// 声道数目
	streamInfo.sAudioMediaInfo.dwSamplesPerSec = dwSamplePerSec;	// 每秒采样数量 ////////////////////////////////////////////////////////////////////////////
	streamInfo.sAudioMediaInfo.dwBitsPerSample = 32;	// 采样位数 
	streamInfo.sAudioMediaInfo.dwAvgBitsPerSec = 32 * dwSamplePerSec;	// 音频码率 bits
	streamInfo.sAudioMediaInfo.dwBlockAlign = 1;		// 数据块对齐单位(每个采样样本需要的字节数), 声道数*量化数/8, 量化数(16,20?,24,32...)
	streamInfo.sAudioMediaInfo.enumAudioCFG = SDAUDIOCFG_STEREO;		//声道属性
	streamInfo.sAudioMediaInfo.enumChannelSamplesFormat = SDCHANNELSAMPLESFORMAT_Progressive;	//音频声道采样数据格式(AV_SAMPLE_FMT_S16)
	streamInfo.sAudioMediaInfo.extradata = nullptr;
	streamInfo.sAudioMediaInfo.extradata_size = 0;
	streamInfo.sAudioMediaInfo.dwStruSize = sizeof(SDAudioMediaInfo);			// 结构大小
	streamInfo.dwStruSize = sizeof(SDStreamMediaInfo);

	CString strRet;
	if (emVideoType == SDVIDEOTYPE_H264 && emAudioType == SDAUDIOTYPE_AAC)
	{
		strRet = _T(".mp4");
	}
	else if (emVideoType == SDVIDEOTYPE_MPEG4 && emAudioType == SDAUDIOTYPE_MP3)
	{
		strRet = _T(".mp4");
	}
	else if (emVideoType == SDVIDEOTYPE_MPEG2_IFRAME && emAudioType == SDAUDIOTYPE_WAVE_PCM)
	{
		strRet = _T(".avi");
	}
	else
	{
		strRet = _T(".avi");
	}
	return strRet;
}

#ifdef _DEBUG
#	pragma comment(lib, "LibCodecD.lib")
#else
#	pragma comment(lib, "LibCodecU.lib")
#endif

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
	if (m_pThread)
	{
		m_evtPlayStop.SetEvent();
		WaitForSingleObject(m_pThread->m_hThread, INFINITE);
		m_pThread = NULL;
	}
}

void CEncodecPressTestDlg::StartPlay()
{
	StopPlay();
	m_evtPlayStop.ResetEvent();
	m_evtPlayPause.ResetEvent();
	m_pThread = AfxBeginThread(ThreadPlay, this);
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

CString strMsg;

void CEncodecPressTestDlg::DoPlay()
{
	CEdit * pEdit = (CEdit *)GetDlgItem(IDC_EDIT_INFOMATION);
	if (pEdit && ::IsWindow(pEdit->GetSafeHwnd()))
	{
		pEdit->SetWindowText(_T(""));
	}
	CWnd * pEncodecNumWnd = GetDlgItem(IDC_EDIT_ENCODER_COUNT);
	if (pEncodecNumWnd && ::IsWindow(pEncodecNumWnd->GetSafeHwnd()))
	{
		CString strEncodecNum;
		pEncodecNumWnd->GetWindowText(strEncodecNum);
		m_nEncoderCount = _ttoi(strEncodecNum);
	}

	std::string cstrOutPath = "E:\\clip\\";
	CWnd * pWnd = GetDlgItem(IDC_EDIT_OUT_FILE_PATH);
	if (pWnd && ::IsWindow(pWnd->GetSafeHwnd()))
	{
		CString strPath;
		pWnd->GetWindowText(strPath);
		cstrOutPath = ConverCStringToStdString(strPath);
	}
	m_nDispFrame = 0;
	Lock();
	m_nFrame = 0;
	Unlock();
	PostMessage(MSG_PUSHINFO, 0, (LPARAM)_T("Starting"));
	pWnd = GetDlgItem(IDC_EDIT_FILE_PATH);
	if (pWnd && ::IsWindow(pWnd->GetSafeHwnd()))
	{
		FILE * pAudioFile = nullptr;
		fopen_s(&pAudioFile, "output.pcm", "wb");

		CString strPath;
		pWnd->GetWindowText(strPath);
		std::string cstrPath = ConverCStringToStdString(strPath);
		IecCodecFactory * ecfactory = ecCodec_CreateCodecFactory();
		if (ecfactory)
		{
			IecCodecProtocolDecoder * pDecoder = ecfactory->GetProtocolDecoder();
			if (pDecoder)
			{
				if (pDecoder->SetSourcePath(cstrPath.c_str()))
				{
					int nWidth = 720;
					int nHeight = 576;
					SDStreamMediaInfoEx streamMediaInfoEx;
					SDAudioSamplesBufInfo audioSamplesBufInfo;
					audioSamplesBufInfo.enumAudioCFG = SDAUDIOCFG_STEREO;
					audioSamplesBufInfo.enumChannelSamplesFormat = (SD_CHANNELSAMPLE_FORMAT)1;
					audioSamplesBufInfo.dwSamplesPerSec = 48000;
					audioSamplesBufInfo.dwChannels = 2;
					pDecoder->SetAudioSamplesBufInfo(&audioSamplesBufInfo);
					if (pDecoder->GetFileGlobalMediaInfo(&streamMediaInfoEx))
					{
						m_nTimebaseDen = streamMediaInfoEx.sVideoMediaInfo.dwStandardRate;
						m_nTimebaseNum = streamMediaInfoEx.sVideoMediaInfo.dwStandardScale;
						bool bContinue = true;
						m_player.SetBufferFWH(SDL_PIXELFORMAT_IYUV, nWidth, nHeight);
						SDVideoFrameImageBufInfo videoFrameImageBufInfo;
						videoFrameImageBufInfo.dwXSize = nWidth;
						videoFrameImageBufInfo.dwYSize = nHeight;
						videoFrameImageBufInfo.enumColorFormat = SDCOLORFORMAT_YUVP_420;// streamMediaInfoEx.sVideoMediaInfo.enumColorFormat;
						bContinue = pDecoder->SetVideoFrameBufInfo(&videoFrameImageBufInfo, nullptr);

						SD_UINT32 nVideoBufferSize = pDecoder->GetVideoBufferSize();
						SD_UINT32 nAudioBufferSize = AVCODEC_MAX_AUDIO_FRAME_SIZE;
						uint8_t * pVideoData = new uint8_t[nVideoBufferSize];
						memset(pVideoData, 0, nVideoBufferSize * sizeof(uint8_t));
						uint8_t * pAudioData = new uint8_t[nAudioBufferSize];
						memset(pAudioData, 0, nAudioBufferSize * sizeof(uint8_t));
						SD_UINT32 numAudioSample = 0;
						//根据帧率及采样率来算出每帧对应的sample数
						SD_UINT32 SamplePerFrame = 2048;
						{
							//每秒的视频帧数
							double dFramePerSec = streamMediaInfoEx.sVideoMediaInfo.dwStandardRate * 1.0 / streamMediaInfoEx.sVideoMediaInfo.dwStandardScale;
							//每秒的采样数
							double dSamplePerSec = audioSamplesBufInfo.dwSamplesPerSec;
							//每帧对应的sample数=每秒的采样数/每秒的视频帧数
							SamplePerFrame = dSamplePerSec / dFramePerSec;
						}
						bool bFirst = false;
						m_ctrSlider.SetRange(0, streamMediaInfoEx.dwVideoFrameNum);
						m_ctrSlider.SetTicFreq(streamMediaInfoEx.dwVideoFrameNum / 100.0);
						uint32_t nAudioPos = 0;
#ifdef ENABLE_ENCODE
						IecCodecProtocolEncoder * pEncoder = nullptr;
						if (ecfactory)
						{
							if (m_nEncoderCount > 0)
							{
								pEncoder = ecfactory->GetProtocolEncoder();
								if (pEncoder)
								{
									SDStreamMediaInfo streamInfo;
									GetPresetMediaInfo(EmVideoStandard_PAL, SDVIDEOTYPE_H264, SDCOLORFORMAT_YUVP_420, SDAUDIOTYPE_AAC, 48000, streamInfo);
									if (pEncoder->SetSinkFile(&streamInfo, cstrOutPath.c_str()))
									{
										//设置视频编码格式
										SDVideoFrameImageBufInfo imageBufInfo;
										imageBufInfo.dwXSize = nWidth;
										imageBufInfo.dwYSize = nHeight;
										imageBufInfo.dwScanXByteSize = nWidth * 2;
										imageBufInfo.enumColorFormat = videoFrameImageBufInfo.enumColorFormat;
										imageBufInfo.enumScanMode = SDVIDEOSCANMODE_FirstFieldTop;
										//SResamplerPara resamplePara;
										if (pEncoder->SetVideoFrameBufInfo(&imageBufInfo, NULL))
										{
											PostMessage(MSG_PUSHINFO, 0, (LPARAM)_T("Video encoder created"));
										}
										else
										{
											PostMessage(MSG_PUSHINFO, 0, (LPARAM)_T("Creating Video encoder SetVideoFrameBufInfo error"));
										}
										//设置音频编码格式
										if (pEncoder->SetAudioSamplesBufInfo(&audioSamplesBufInfo))
										{
											PostMessage(MSG_PUSHINFO, 0, (LPARAM)_T("Audio encoder created"));
										}
										else
										{
											PostMessage(MSG_PUSHINFO, 0, (LPARAM)_T("Creating Audio encoder SetAudioSamplesBufInfo error"));
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
#endif
						while (bContinue)
						{
							if (WaitForSingleObject(m_evtPlayPause, 0) != WAIT_OBJECT_0)
							{
								SDRFrameInfo frameInfo;
								if (streamMediaInfoEx.dwVideoStreamCount > 0)
								{
									bContinue = pDecoder->GetVideoBuffer(m_nDispFrame, pVideoData, &frameInfo);
								}
								if (streamMediaInfoEx.dwAudioStreamCount > 0)
								{
									bContinue = pDecoder->GetAudioSamples(nAudioPos, SamplePerFrame, pAudioData, &numAudioSample);
								}

								//音频先写到文件里
								//fwrite(pAudioData, 1, numAudioSample * 4, pAudioFile);
#ifdef ENABLE_ENCODE
								if (pEncoder)
								{
									SDRFrameInfo frameInfoTmp;
									frameInfoTmp.emDataType = STREAM_DATATYPE_VIDEO;
									frameInfoTmp.iVersion = 0;		// 结构版本号。		4---4[序列化占用字节－序列化位置]
									frameInfoTmp.iSize = frameInfo.iSize;// nWidth * nHeight * 2;			// 帧数据大小		4---16
									frameInfoTmp.dwFrameIndex = m_nDispFrame;	// 帧数据流顺序		4---28
									frameInfoTmp.dwFrameNum = 1;		// 视频/音频帧数量	4---32
									frameInfoTmp.iSamplesOffset = 0;	// 标识RawAudio音频、视频帧中有效采样的偏移数，大于0表示从开始偏移，小于0表示从尾部开始向前偏移		4---36
									frameInfoTmp.qwDTS = m_nDispFrame * 40;			// 解码时间(90Khz单位)	8---44
									frameInfoTmp.qwPTS = m_nDispFrame * 40;			// 展现时间(90Khz单位)	8---52
									frameInfoTmp.qwDuration = 40;		// 持续时间(90Khz单位)	8---6
									frameInfoTmp.dwShowIndex = m_nDispFrame;	// 帧数据显示顺序			4---104
									frameInfoTmp.emFrameType = FRAMETYPE_I;   	// 帧类型 				4---108
									frameInfoTmp.extradata_size = 0;
									if (!pEncoder->PutVideoBuffer(pVideoData, false, &frameInfoTmp))
									{
										PostMessage(MSG_PUSHINFO, 0, (LPARAM)_T("one video failed"));
									}
									else
									{
										//PostMessage(MSG_PUSHINFO, 0, (LPARAM)_T("one video succed"));
									}
									if (!pEncoder->PutAudioSamples(pAudioData, numAudioSample))
									{
										PostMessage(MSG_PUSHINFO, 0, (LPARAM)_T("one audio failed"));
									}
									else
									{
										//PostMessage(MSG_PUSHINFO, 0, (LPARAM)_T("one audio succed"));
									}
								}
#endif
								m_nDispFrame++;
								nAudioPos += numAudioSample;
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

								m_player.PushFrame(pVideoData, nWidth);
								if (WaitForSingleObject(m_evtPlayStop, 40) == WAIT_OBJECT_0)
								{
									break;
								}
							}
							else
							{
								Lock();
								if (m_nFrame != m_nDispFrame)
								{
									SDRFrameInfo frameInfo;
									pDecoder->GetAudioSamples(m_nFrame * SamplePerFrame, SamplePerFrame, pAudioData, &numAudioSample);
									pDecoder->GetVideoBuffer(-1, pVideoData, &frameInfo);

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

									m_player.PushFrame(pVideoData, nWidth);
									m_nDispFrame = m_nFrame;
								}
								Unlock();
								if (WaitForSingleObject(m_evtPlayStop, 1) == WAIT_OBJECT_0)
								{
									break;
								}
							}
						}
						deleteC(pVideoData);
#ifdef ENABLE_ENCODE
						if (ecfactory && pEncoder)
						{
							ecfactory->DeleteProtocolEncoder(pEncoder);
						}
#endif
					}
				}
				fclose(pAudioFile); 
				ecfactory->DeleteProtocolDecoder(pDecoder);
			}
			ecCodec_ReleaseCodecFactory(ecfactory);
		}
	}
	PostMessage(MSG_PUSHINFO, 0, (LPARAM)_T("Stoped"));
}

CEncodecPressTestDlg::CEncodecPressTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ENCODECPRESSTEST_DIALOG, pParent)
	, m_pThread(nullptr)
	, m_evtPlayStop(FALSE, TRUE, NULL, NULL)
	, m_evtPlayPause(FALSE, TRUE, NULL, NULL)
	, m_nEncoderCount(0)
	, m_nFrame(0)
	, m_nDispFrame(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	InitializeCriticalSection(&m_lock);
}

CEncodecPressTestDlg::~CEncodecPressTestDlg()
{
	m_nFrame = 0;
	m_nDispFrame = 0;
	DeleteCriticalSection(&m_lock);
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
	int nSize = ::WideCharToMultiByte(CP_UTF8, 0, cstrValue.GetBuffer(), -1, NULL, 0, NULL, NULL);
	char * szcSrc = new char[nSize];
	memset(szcSrc, 0, sizeof(char) * nSize);
	::WideCharToMultiByte(CP_UTF8, 0, cstrValue.GetBuffer(), -1, szcSrc, nSize, NULL, NULL);
	strRet = szcSrc;
	delete[] szcSrc;
	szcSrc = NULL;
	return strRet;
}

CString CEncodecPressTestDlg::ConvertStdStringToCString(const std::string & strValue)
{
	CString cstrRet;
	cstrRet.Empty();
	int nLength = ::MultiByteToWideChar(CP_UTF8, 0, strValue.c_str(), -1, NULL, 0);
	TCHAR * szText1 = new TCHAR[nLength + 1];
	::MultiByteToWideChar(CP_UTF8, 0, strValue.c_str(), -1, szText1, nLength + 1);
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
END_MESSAGE_MAP()

// CEncodecPressTestDlg 消息处理程序

void CEncodecPressTestDlg::OnDestroy()
{
	StopPlay();
	CDialogEx::OnDestroy();
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
		m_player.IntialWnd(SDL_PIXELFORMAT_IYUV, pPlayerWnd->GetSafeHwnd(), rtPlayer.Width(), rtPlayer.Height(), rtPlayer.Width(), rtPlayer.Height());
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
		if (pVideoStandardComb
			&& pVideoTypeComb
			&& pColorFmtComb
			&& pAudioTypeComb
			&& pFileNameEdit
			)
		{
			pVideoStandardComb->SetCurSel(0);
			pVideoTypeComb->SetCurSel(0);
			pColorFmtComb->SetCurSel(0);
			pAudioTypeComb->SetCurSel(0);
			CString strName = _T("encodec");
			pFileNameEdit->SetWindowText(strName);
		}
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

EmVideoStandard CEncodecPressTestDlg::GetCodecVideoStandard(int nIndex)
{
	EmVideoStandard emRet = EmVideoStandard_PAL;
	CComboBox * pCombo = GetCodecVideoStandardCombo(nIndex);
	if (pCombo)
	{
		int nSel = pCombo->GetCurSel();
		if (nSel == 0)
		{
			emRet = EmVideoStandard_PAL;
		}
		else
		{
			emRet = EmVideoStandard_HD;
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
		else if (nSel = 1)
		{
			emRet = SDVIDEOTYPE_MPEG4;
		}
		else
		{
			emRet = SDVIDEOTYPE_MPEG2_IFRAME;
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
		else
		{
			emRet = SDCOLORFORMAT_YUVP_422;
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
		else if (nSel = 1)
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

void CEncodecPressTestDlg::DealCtrlFileName()
{
	for (size_t i = 0; i < 8; i++)
	{
		if (GetCodecCheck(i))
		{
			EmVideoStandard emVideoStandard = GetCodecVideoStandard(i);
			SD_VIDEO_TYPE emVideoType = GetCodecVideoType(i);
			SD_COLOR_FORMAT emColorFmt = GetCodecColorFmt(i);
			SD_AUDIO_TYPE emAudioType = GetCodecAudioType(i);

			CString strFileName = _T("en");
			switch (emVideoStandard)
			{
			case EmVideoStandard_PAL:
				strFileName.AppendFormat(_T("_PAL"));
				break;
			case EmVideoStandard_HD:
				strFileName.AppendFormat(_T("_HD"));
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
				break;
			default:
				break;
			}
			switch (emColorFmt)
			{
			case SDCOLORFORMAT_YUVP_422:
				strFileName.AppendFormat(_T("_YUV422p"));
				break;
			case SDCOLORFORMAT_YUVP_420:
				strFileName.AppendFormat(_T("_YUV420p"));
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
			strFileName.AppendFormat(_T("_%d"), i);
			GetCodecFileNameEdit(i)->SetWindowText(strFileName);

			SDStreamMediaInfo streamInfo;
			CString strSuffix = GetPresetMediaInfo(emVideoStandard, emVideoType, emColorFmt, emAudioType, 48000, streamInfo);
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

