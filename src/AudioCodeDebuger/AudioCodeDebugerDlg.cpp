
// AudioCodeDebugerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AudioCodeDebuger.h"
#include "AudioCodeDebugerDlg.h"
#include "afxdialogex.h"
#include "IecCodecFactory.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CAudioCodeDebugerDlg 对话框




CAudioCodeDebugerDlg::CAudioCodeDebugerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAudioCodeDebugerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAudioCodeDebugerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAudioCodeDebugerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CAudioCodeDebugerDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CAudioCodeDebugerDlg 消息处理程序

BOOL CAudioCodeDebugerDlg::OnInitDialog()
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CAudioCodeDebugerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CAudioCodeDebugerDlg::OnPaint()
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
HCURSOR CAudioCodeDebugerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAudioCodeDebugerDlg::OnBnClickedOk()
{
	CString strFilePath = _T("D:\\audio.aac");
	IecCodecFactory * pFac = ecCodec_CreateCodecFactory();
	IecCodecAudioDecoder * pAudioDecoder = pFac->GetAudioDecoder();
	SDStreamMediaInfo mediaInfo;
	GetPresetMediaInfo(SDVIDEOSTANDARD_PAL, SDVIDEOTYPE_H264, SDCOLORFORMAT_YUVP_420, SDAUDIOTYPE_AAC, 48000, 5, mediaInfo);
	pAudioDecoder->InitAudioDecoder(mediaInfo.sAudioMediaInfo);
	SDAudioMediaInfo audioInfo;
	audioInfo.enumAudioType = SDAUDIOTYPE_AAC;
	audioInfo.dwAudioSubType = 0;
	audioInfo.dwChannels = 2;
	audioInfo.dwBitsPerSample = 16;
	audioInfo.dwSamplesPerSec = 48000;
	audioInfo.dwAvgBitsPerSec = audioInfo.dwSamplesPerSec * audioInfo.dwBitsPerSample;
	audioInfo.dwBlockAlign = 2;
	audioInfo.enumAudioCFG = SDAUDIOCFG_STEREO;
	audioInfo.enumChannelSamplesFormat = SDCHANNELSAMPLESFORMAT_Progressive;
	audioInfo.dwStruSize = sizeof(SDAudioMediaInfo);
	pAudioDecoder->SetAudioMediaInfo(&audioInfo);

	CFile fileOut;
	if (fileOut.Open(_T("result.pcm"), CFile::modeCreate | CFile::modeWrite))
	{
		CFile fileIn;
		if (fileIn.Open(strFilePath, CFile::modeRead))
		{
			int nSize = 0;
			int nBufSize = 1024 * 1024;
			unsigned char * pBufIn = new unsigned char[nBufSize];
			unsigned char * pBufOut = new unsigned char[nBufSize];
			while (true)
			{
				nSize = 0;
				memset(pBufIn, 0, nBufSize);
				if (fileIn.Read(&nSize, 4) > 0)
				{
					if (nSize > 0)
					{
						if (fileIn.Read(pBufIn, nSize) == nSize)
						{
							SDRFrameInfo frameInfo;
							frameInfo.iSize = nSize;
							frameInfo.extradata_size = 0;
							if (pAudioDecoder->PutFrame(pBufIn, &frameInfo))
							{
								int nRetSample = pAudioDecoder->GetSample(pBufOut, 1920);
								if (nRetSample > 0)
								{
									fileOut.Write(pBufOut, nRetSample * 4);
								}
								else if (nRetSample == 0)
								{
									continue;
								}
								else
								{
									break;
								}
							}
							else
							{
								break;
							}
						}
						else
						{
							break;
						}
					}
					else
					{
						break;
					}
				}
				else
				{
					break;
				}
			}
			delete pBufIn;
			delete pBufOut;
			pBufIn = nullptr;
			pBufOut = nullptr;
			fileIn.Close();
		}
		fileOut.Close();
	}

	pFac->DeleteAudioDecoder(pAudioDecoder);
	ecCodec_ReleaseCodecFactory(pFac);
}
