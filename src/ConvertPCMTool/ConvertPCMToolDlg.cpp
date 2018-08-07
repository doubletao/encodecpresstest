
// ConvertPCMToolDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ConvertPCMTool.h"
#include "ConvertPCMToolDlg.h"
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


// CConvertPCMToolDlg 对话框
std::string ConverCStringToStdString(CString & cstrValue)
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




CConvertPCMToolDlg::CConvertPCMToolDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CONVERTPCMTOOL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CConvertPCMToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CConvertPCMToolDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_SCAN_INPUT_FILE, &CConvertPCMToolDlg::OnBnClickedBtnScanInputFile)
	ON_BN_CLICKED(IDC_BTN_SCAN_OUTPUT_FILE, &CConvertPCMToolDlg::OnBnClickedBtnScanOutputFile)
	ON_BN_CLICKED(IDC_BTN_START, &CConvertPCMToolDlg::OnBnClickedBtnStart)
END_MESSAGE_MAP()


// CConvertPCMToolDlg 消息处理程序

BOOL CConvertPCMToolDlg::OnInitDialog()
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CConvertPCMToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CConvertPCMToolDlg::OnPaint()
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
HCURSOR CConvertPCMToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CConvertPCMToolDlg::OnBnClickedBtnScanInputFile()
{
	CWnd * pWnd = GetDlgItem(IDC_EDIT_INPUT_FILE);
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


void CConvertPCMToolDlg::OnBnClickedBtnScanOutputFile()
{
	CWnd * pWnd = GetDlgItem(IDC_EDIT_OUTPUT_FILE);
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


void CConvertPCMToolDlg::OnBnClickedBtnStart()
{
	SDStreamMediaInfoEx streamMediaInfoEx;

	CString strInputPath;
	CString strOutputPath;
	CWnd * pWnd = GetDlgItem(IDC_EDIT_INPUT_FILE);
	if (pWnd && ::IsWindow(pWnd->GetSafeHwnd()))
	{
		pWnd->GetWindowText(strInputPath);
	}
	pWnd = GetDlgItem(IDC_EDIT_OUTPUT_FILE);
	if (pWnd && ::IsWindow(pWnd->GetSafeHwnd()))
	{
		pWnd->GetWindowText(strOutputPath);
	}

	if (!strInputPath.IsEmpty() && !strOutputPath.IsEmpty())
	{
		IecCodecFactory * ecFacetory = ecCodec_CreateCodecFactory();
		if (ecFacetory)
		{
			IecCodecProtocolDecoder * pDecoder = ecFacetory->GetProtocolDecoder();
			if (pDecoder)
			{
				if (pDecoder->SetSourcePath(ConverCStringToStdString(strInputPath).c_str()))
				{
					SDAudioMediaInfo audioInfo;
					audioInfo.enumAudioType = SDAUDIOTYPE_WAVE_PCM;
					audioInfo.enumAudioCFG = SDAUDIOCFG_INDEPENDENT;
					audioInfo.enumChannelSamplesFormat = SDCHANNELSAMPLESFORMAT_Progressive;
					audioInfo.dwSamplesPerSec = 16000;
					audioInfo.dwChannels = 1;
					if (pDecoder->SetAudioSamplesBufInfo(&audioInfo))
					{
						SDStreamMediaInfoEx streamMediaInfoEx;
						if (pDecoder->GetFileGlobalMediaInfo(&streamMediaInfoEx))
						{
							CFile filePCM;
							if (filePCM.Open(strOutputPath, CFile::modeCreate | CFile::modeWrite))
							{
								int nAudioBufSize = AVCODEC_MAX_AUDIO_FRAME_SIZE;
								SD_UINT8 * pAudioData = new SD_UINT8[nAudioBufSize];
								memset(pAudioData, 0, nAudioBufSize * sizeof(SD_UINT8));

								int nReadSize = 0;
								if (streamMediaInfoEx.dwAudioStreamCount > 0)
								{
									while (pDecoder->GetAudioSamples(0, 100, pAudioData, nullptr))
									{
										filePCM.Write(pAudioData, 100 * 2);
									}
								}

								delete pAudioData;
								pAudioData = nullptr;
								filePCM.Close();
							}
						}
					}
				}
				ecFacetory->DeleteProtocolDecoder(pDecoder);
			}
		}
	}
}
