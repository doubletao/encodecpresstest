
// EncodecPressTestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "EncodecPressTest.h"
#include "EncodecPressTestDlg.h"
#include "afxdialogex.h"
#include "FFmpegVADecoder.h"
#include "IecCodecFactory.h"

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

void CEncodecPressTestDlg::DoPlay()
{
	CWnd * pEncodecNumWnd = GetDlgItem(IDC_EDIT_ENCODER_COUNT);
	if (pEncodecNumWnd && ::IsWindow(pEncodecNumWnd->GetSafeHwnd()))
	{
		CString strEncodecNum;
		pEncodecNumWnd->GetWindowText(strEncodecNum);
		m_nEncoderCount = _ttoi(strEncodecNum);
	}

	std::string cstrOutPath = "E:\\clip\\encodec.h264";
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
#if 0
	IFileDecoder * pDecode = CodecFactory::GetInstance().Create_FileDecoder();
	if (pDecode && pDecode->SetSourceFile("F:\\Media\\全民超人汉考克.威尔. 史密斯.查理兹. 塞隆.杰森. 贝特曼.2008.[1280x704高清晰版].rmvb"))
	{
		SStreamMediaInfo info;
		if (pDecode->GetFileGlobalMediaInfo(&info))
		{
			int i = 0;
			i++;
		}
	}
#endif
	PostMessage(MSG_PUSHINFO, 0, (LPARAM)_T("Starting"));
	pWnd = GetDlgItem(IDC_EDIT_FILE_PATH);
	if (pWnd && ::IsWindow(pWnd->GetSafeHwnd()))
	{
		FILE * pAudioFile = fopen("output.pcm", "wb");

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
					SDStreamMediaInfoEx streamMediaInfoEx;
					if (pDecoder->GetFileGlobalMediaInfo(&streamMediaInfoEx))
					{
						bool bContinue = true;
						int nWidth = 720;
						int nHeight = 576;
						m_player.SetBufferFWH(SDL_PIXELFORMAT_IYUV, nWidth, nHeight);
						SDVideoFrameImageBufInfo videoFrameImageBufInfo;
						videoFrameImageBufInfo.dwXSize = nWidth;
						videoFrameImageBufInfo.dwYSize = nHeight;
						videoFrameImageBufInfo.enumColorFormat = streamMediaInfoEx.sVideoMediaInfo.enumColorFormat;
						bContinue = pDecoder->SetVideoFrameBufInfo(&videoFrameImageBufInfo, nullptr);

						SDAudioSamplesBufInfo audioSamplesBufInfo;
						audioSamplesBufInfo.enumAudioCFG = SDAUDIOCFG_STEREO;
						audioSamplesBufInfo.enumChannelSamplesFormat = (SD_CHANNELSAMPLE_FORMAT)1;
						audioSamplesBufInfo.dwSamplesPerSec = 44100;
						audioSamplesBufInfo.dwChannels = 2;
						pDecoder->SetAudioSamplesBufInfo(&audioSamplesBufInfo);
						SD_UINT32 nVideoBufferSize = pDecoder->GetVideoBufferSize();
						SD_UINT32 nAudioBufferSize = AVCODEC_MAX_AUDIO_FRAME_SIZE;
						uint8_t * pVideoData = new uint8_t[nVideoBufferSize];
						memset(pVideoData, 0, nVideoBufferSize * sizeof(uint8_t));
						uint8_t * pAudioData = new uint8_t[nAudioBufferSize];
						memset(pAudioData, 0, nAudioBufferSize * sizeof(uint8_t));
						SD_UINT32 numAudioSample = 0;
						bool bFirst = false;
						m_ctrSlider.SetRange(0, streamMediaInfoEx.dwVideoFrameNum);
						m_ctrSlider.SetTicFreq(streamMediaInfoEx.dwVideoFrameNum / 100.0);
						while (bContinue)
						{
							if (WaitForSingleObject(m_evtPlayPause, 0) != WAIT_OBJECT_0)
							{
								SDRFrameInfo frameInfo;
								bContinue = pDecoder->GetVideoBuffer(-1, pVideoData, &frameInfo);
								bContinue = pDecoder->GetAudioSamples(-1, nAudioBufferSize, pAudioData, &numAudioSample);

								//音频先写到文件里
								fwrite(pAudioData, 1, numAudioSample, pAudioFile);

								m_nDispFrame++;
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
									bContinue = pDecoder->GetAudioSamples(m_nFrame, nAudioBufferSize, pAudioData, &numAudioSample);
									bContinue = pDecoder->GetVideoBuffer(-1, pVideoData, &frameInfo);

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
					}
				}
				fclose(pAudioFile);
				deleteC(pDecoder);
			}
			deleteC(ecfactory);
		}
#if 0
		FFmpegVADecoder codec;
		if (codec.OpenFile(cstrPath.c_str()))
		{
			int nSrcWidth = 0;
			int nSrcHeight = 0;
			DWORD emSrcPixFmt = 0;
			int bSucc = codec.GetVideoBasicInfo(nSrcWidth, nSrcHeight, emSrcPixFmt);
			if ((bSucc > 0)
				&& (nSrcWidth > 0)
				&& (nSrcHeight > 0)
				&& (emSrcPixFmt != -1))
			{
				int nWidth = 720;
				int nHeight = 576;
				DWORD emPixFmt = 0;
				int bContinue = codec.SetVideoScaleInfo(nWidth, nHeight, emPixFmt);

				PostMessage(MSG_PUSHINFO, 0, (LPARAM)_T("Creating encoder"));
#if 0
				IFileEncoder * pEncodec = nullptr;
				if (m_nEncoderCount > 0)
				{
					pEncodec = CodecFactory::GetInstance().Create_FileEncoder();
					if (pEncodec)
					{
						SStreamMediaInfo streamInfo;
						streamInfo.enumStreamMediaType = STREAMTYPE_OPENDML_AVI;
						streamInfo.dwStreamMediaSubType = 0;
						streamInfo.dwVideoStreamCount = 1;
						streamInfo.dwTotalAverDataRateInBitsPerSec = 0;
						streamInfo.dwTotalMaxDataRateInBitsPerSec = 0;
						streamInfo.dwTotalMinDataRateInBitsPerSec = 0;
						streamInfo.sVideoMediaInfo.dwWidth = 720;
						streamInfo.sVideoMediaInfo.dwHeight = 576;
						streamInfo.sVideoMediaInfo.dwStandardRate = 25;
						streamInfo.sVideoMediaInfo.dwStandardScale = 1;
						streamInfo.sVideoMediaInfo.enumScanMode = VIDEOSCANMODE_FirstFieldTop;
						streamInfo.sVideoMediaInfo.enumColorFormat = COLORFORMAT_YUVP_420;
						streamInfo.sVideoMediaInfo.enumVideoType = VIDEOTYPE_H264;
						streamInfo.sVideoMediaInfo.enumVideoSubType = PROFILE_AVC_MAIN;/////////////////////////////////////
						streamInfo.sVideoMediaInfo.dwDataRateInBitsPerSec = 400000;// 25000000;
						streamInfo.sVideoMediaInfo.enumDataRateType = DATARATE_CONSTANT;
						streamInfo.sVideoMediaInfo.dwGOPSize = 1000;
						streamInfo.sVideoMediaInfo.dwReferencePeriod = 1;
						streamInfo.sVideoMediaInfo.bIsClipped = 1;
						streamInfo.sVideoMediaInfo.enumRateControlMethod = RATECONTROL_CBR;/////////////////////////////////////
						streamInfo.sVideoMediaInfo.dwDisplayWidth = 4;
						streamInfo.sVideoMediaInfo.dwDisplayHeight = 3;
						streamInfo.sVideoMediaInfo.dwMaxDataRateInBitsPerSec = 0;
						streamInfo.sVideoMediaInfo.dwMinDataRateInBitsPerSec = 0;
						streamInfo.sVideoMediaInfo.dwStruSize = sizeof(SVideoMediaInfo);
						streamInfo.dwAudioStreamCount = 0;
						streamInfo.sAudioMediaInfo;
						streamInfo.dwStruSize = sizeof(SStreamMediaInfo);
						if (pEncodec->SetSinkFile(&streamInfo, cstrOutPath.c_str()))
						{
							SVideoFrameImageBufInfo imageBufInfo;
							imageBufInfo.dwXSize = nWidth;
							imageBufInfo.dwYSize = nHeight;
							imageBufInfo.dwScanXByteSize = nWidth * 2;
							imageBufInfo.enumColorFormat = COLORFORMAT_YUVP_420;
							imageBufInfo.enumScanMode = VIDEOSCANMODE_FirstFieldTop;
							//SResamplerPara resamplePara;
							if (pEncodec->SetVideoFrameBufInfo(&imageBufInfo, NULL))
							{
								PostMessage(MSG_PUSHINFO, 0, (LPARAM)_T("encoder created"));
							}
							else
							{
								PostMessage(MSG_PUSHINFO, 0, (LPARAM)_T("Creating encoder SetVideoFrameBufInfo error"));
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
#endif

				if (bContinue)
				{
					PostMessage(MSG_PUSHINFO, 0, (LPARAM)_T("Open File Success"));
				}
				else
				{
					PostMessage(MSG_PUSHINFO, 0, (LPARAM)_T("Open File Error"));
				}
				m_player.SetBufferFWH(SDL_PIXELFORMAT_IYUV, nWidth, nHeight);
				uint8_t ** pVideoData = nullptr;
				int * nLineSize = nullptr;
				bool bFirst = false;
				unsigned long long nFrame = 0;
				while (bContinue)
				{
					if (WaitForSingleObject(m_evtPlayPause, 0) != WAIT_OBJECT_0)
					{
						bContinue = codec.DecodeOneFrame(pVideoData, nLineSize);
						m_player.PushYUVFrame(pVideoData, nLineSize);
						if (1)
						{
							FILE * file;
							fopen_s(&file, "src.yuv", "wb+");
							if (file)
							{
								int y_size = nWidth * nHeight;
								fwrite(pVideoData[0], 1, y_size, file);    //Y 
								fwrite(pVideoData[1], 1, y_size / 4, file);  //U
								fwrite(pVideoData[2], 1, y_size / 4, file);  //V
								fclose(file);
							}
						}
#if 0
						if (pEncodec)
						{
							if (pEncodec->IsCanWriteVideoFrame())
							{
								SRFrameInfo frameInfo;
								frameInfo.emDataType = STREAM_DATATYPE_VIDEO;
								frameInfo.iVersion = 0;		// 结构版本号。		4---4[序列化占用字节－序列化位置]
								frameInfo.iSize = nWidth * nHeight * 2;			// 帧数据大小		4---16
								frameInfo.dwFrameIndex = nFrame;	// 帧数据流顺序		4---28
								frameInfo.dwFrameNum = 1;		// 视频/音频帧数量	4---32
								frameInfo.iSamplesOffset = 0;	// 标识RawAudio音频、视频帧中有效采样的偏移数，大于0表示从开始偏移，小于0表示从尾部开始向前偏移		4---36
								frameInfo.qwDTS = nFrame * 40;			// 解码时间(90Khz单位)	8---44
								frameInfo.qwPTS = nFrame * 40;			// 展现时间(90Khz单位)	8---52
								frameInfo.qwDuration = 40;		// 持续时间(90Khz单位)	8---6
								frameInfo.dwShowIndex = nFrame;	// 帧数据显示顺序			4---104
								frameInfo.emFrameType = FRAMETYPE_I;   	// 帧类型 				4---108
								frameInfo.extradata_size = 0;
								if (bFirst)
								{
									frameInfo.emStreamFlag = STREAMSTATE_BEGIN;   // 标识是第一帧，还是中间帧，还是末尾帧
									bFirst = false;
								}
								else
								{
									frameInfo.emStreamFlag = STREAMSTATE_CONTINUE;   // 标识是第一帧，还是中间帧，还是末尾帧
								}
								if (!pEncodec->PutVideoBuffer(*pVideoData, false, &frameInfo))
								{
									PostMessage(MSG_PUSHINFO, 0, (LPARAM)_T("encoder one failed"));
								}
								nFrame++;
							}
							else
							{
								PostMessage(MSG_PUSHINFO, 0, (LPARAM)_T("encoder lost one frame"));
							}
						}
#endif
					}
					if (WaitForSingleObject(m_evtPlayStop, 40) == WAIT_OBJECT_0)
					{
						break;
					}
				}
#if 0
				if (pEncodec)
				{
					pEncodec->Release();
					pEncodec = nullptr;
					PostMessage(MSG_PUSHINFO, 0, (LPARAM)_T("encoder released"));
				}
#endif
			}
			else
			{
				PostMessage(MSG_PUSHINFO, 0, (LPARAM)_T("File info get failed"));
			}
		}
		else
		{
			PostMessage(MSG_PUSHINFO, 0, (LPARAM)_T("open failed"));
		}
#endif
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

	CWnd * pEncodecNumWnd = GetDlgItem(IDC_EDIT_ENCODER_COUNT);
	if (pEncodecNumWnd && ::IsWindow(pEncodecNumWnd->GetSafeHwnd()))
	{
		pEncodecNumWnd->SetWindowText(_T("0"));
		CString strEncodecNum;
		pEncodecNumWnd->GetWindowText(strEncodecNum);
		m_nEncoderCount = _ttoi(strEncodecNum);
	}

	CWnd * pWnd = GetDlgItem(IDC_EDIT_OUT_FILE_PATH);
	if (pWnd && ::IsWindow(pWnd->GetSafeHwnd()))
	{
		pWnd->SetWindowText(_T("E:\\clip\\encodec.h264"));
	}

	m_ctrSlider.SetRange(0, 100);
	m_ctrSlider.SetTicFreq(10);

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
