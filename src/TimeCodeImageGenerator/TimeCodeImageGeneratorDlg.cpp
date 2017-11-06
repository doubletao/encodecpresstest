
// TimeCodeImageGeneratorDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TimeCodeImageGenerator.h"
#include "TimeCodeImageGeneratorDlg.h"
#include "afxdialogex.h"
#include "IecCodecFactory.h"
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

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

CString ConvertStdStringToCString(const std::string & strValue)
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

void GetPathAndName(const CString &strSrcFilePath, CString &strPath, CString &strName)
{
	strPath.Empty();
	strName.Empty();

	int nPos = strSrcFilePath.ReverseFind(_T('\\'));
	if (nPos < 0)
	{
		//未发现反斜杠时，可能只有文件名而无路径，可以继续获取文件名
		strPath.Empty();
	}
	else
	{
		strPath = strSrcFilePath.Left(nPos);
		strName = strSrcFilePath.Right(strSrcFilePath.GetLength() - nPos - 1);
	}

	nPos = strName.ReverseFind(_T('.'));
	if (nPos < 0)
	{
		//未发现点号(.)，视为无后缀的文件名，不处理
	}
	else
	{
		strName = strName.Left(nPos);
	}
}

CString GetCurPath()
{
	CString strCurName;
	GetModuleFileName(NULL, strCurName.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
	strCurName.ReleaseBuffer();
	CString strCurPath;
	CString strCurPurName;
	GetPathAndName(strCurName, strCurPath, strCurPurName);
	return strCurPath;
}

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


// CTimeCodeImageGeneratorDlg 对话框



CTimeCodeImageGeneratorDlg::CTimeCodeImageGeneratorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TIMECODEIMAGEGENERATOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTimeCodeImageGeneratorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTimeCodeImageGeneratorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_START_GENERATE, &CTimeCodeImageGeneratorDlg::OnBnClickedBtnStartGenerate)
	ON_BN_CLICKED(IDC_BTN_OUTPUT_CODEC, &CTimeCodeImageGeneratorDlg::OnBnClickedBtnOutputCodec)
END_MESSAGE_MAP()


// CTimeCodeImageGeneratorDlg 消息处理程序

BOOL CTimeCodeImageGeneratorDlg::OnInitDialog()
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
	GetDlgItem(IDC_EDIT1_FRAME_COUNT)->SetWindowText(_T("1500"));
	GetDlgItem(IDC_EDIT_OUTPUT_WIDTH)->SetWindowText(_T("1920"));
	GetDlgItem(IDC_EDIT_OUTPUT_HEIGHT)->SetWindowText(_T("1080"));
	GetDlgItem(IDC_EDIT_OUTPUT_PATH)->SetWindowText(_T("E:\\TimeImg\\"));
	GetDlgItem(IDC_EDIT_OUT_FILENAME)->SetWindowText(_T("img_"));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTimeCodeImageGeneratorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTimeCodeImageGeneratorDlg::OnPaint()
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
HCURSOR CTimeCodeImageGeneratorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTimeCodeImageGeneratorDlg::OnBnClickedBtnStartGenerate()
{
	CString strTmp;
	GetDlgItem(IDC_EDIT1_FRAME_COUNT)->GetWindowText(strTmp);
	int nLength = _ttoi(strTmp);
	GetDlgItem(IDC_EDIT_OUTPUT_WIDTH)->GetWindowText(strTmp);
	int nWidth = _ttoi(strTmp);
	GetDlgItem(IDC_EDIT_OUTPUT_HEIGHT)->GetWindowText(strTmp);
	int nHeight = _ttoi(strTmp);
	GetDlgItem(IDC_EDIT_OUTPUT_PATH)->GetWindowText(strTmp);
	CString strFilePreName = strTmp;
	GetDlgItem(IDC_EDIT_OUT_FILENAME)->GetWindowText(strTmp);
	strFilePreName.Append(strTmp);

	CDC * pDC = GetDC();
	CDC dcMem;
	CBitmap bmpMem;
	CFont font;
	font.CreatePointFont(2000, _T("微软雅黑"));
	dcMem.CreateCompatibleDC(NULL);
	bmpMem.CreateCompatibleBitmap(pDC, nWidth, nHeight);
	CBitmap *pOldBmp = dcMem.SelectObject(&bmpMem);
	HGDIOBJ hOldBrush = dcMem.SelectStockObject(NULL_BRUSH);
	HGDIOBJ hOldPen = dcMem.SelectStockObject(WHITE_PEN);
	HGDIOBJ hFont = dcMem.SelectObject(font.GetSafeHandle());
	const int nFramePerSec = 25;

	CString strFileSufix;
	for (int i = 0; i < nLength; i++)
	{
		strFileSufix.Format(_T("%d.bmp"), i);
		dcMem.FillRect(CRect(0, 0, nWidth, nHeight), &CBrush(0xFFFFFF / nLength * (i / nFramePerSec)));

		int nHour = i / nFramePerSec / 3600;
		int nMin = (i / nFramePerSec % 3600) / 60;
		int nSecond = (i / nFramePerSec % 3600) % 60;
		int nFrame = i % nFramePerSec;
		CString strFrame;
		strFrame.Format(_T("%02d:%02d:%02d:%02d"), nHour, nMin, nSecond, nFrame);
		dcMem.DrawText(strFrame, CRect(0, 0, nWidth, nHeight), DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		if (bmpMem.m_hObject)
		{
			CImage imgTemp;
			// CImage是MFC中的类。
			imgTemp.Attach(bmpMem.operator HBITMAP());
			imgTemp.Save(strFilePreName + strFileSufix);
			imgTemp.Detach();
		}
	}

	dcMem.SelectObject(hOldPen);
	dcMem.SelectObject(hOldBrush);
	dcMem.SelectObject(hFont);
	dcMem.DeleteDC();
	ReleaseDC(pDC);
}


void CTimeCodeImageGeneratorDlg::OnBnClickedBtnOutputCodec()
{
	IecCodecFactory * ecFacetory = ecCodec_CreateCodecFactory();
	IecCodecProtocolEncoder* pEncodec = ecFacetory->GetProtocolEncoder();
	//拿基础参数
	CString strTmp;
	GetDlgItem(IDC_EDIT1_FRAME_COUNT)->GetWindowText(strTmp);
	int nLength = _ttoi(strTmp);
	GetDlgItem(IDC_EDIT_OUTPUT_WIDTH)->GetWindowText(strTmp);
	int nWidth = _ttoi(strTmp);
	GetDlgItem(IDC_EDIT_OUTPUT_HEIGHT)->GetWindowText(strTmp);
	int nHeight = _ttoi(strTmp);
	GetDlgItem(IDC_EDIT_OUTPUT_PATH)->GetWindowText(strTmp);
	CString strFilePreName = strTmp;
	GetDlgItem(IDC_EDIT_OUT_FILENAME)->GetWindowText(strTmp);
	strFilePreName.Append(strTmp);
	//读标准音频bufer
	CString strAudioBuferPath = GetCurPath() + _T("\\standard.pcm");
	int nAudioSampleWhole = 20480 / 4;
	int nAudioReadCursor = 0;
	SD_UINT32 * pAudioBufer = new SD_UINT32[nAudioSampleWhole];
	CFile fileAudio;
	if (fileAudio.Open(strAudioBuferPath, CFile::modeRead))
	{
		int nReaded = 0;
		for (size_t i = 0; i < 10; i++)
		{
			int nRead = fileAudio.Read((SD_UINT8 *)pAudioBufer + nReaded, 2048);
			nReaded += nRead;
		}
		nAudioSampleWhole = nReaded / 4;
		fileAudio.Close();
	}
	//开辟视频buf
	int nVideoBufSize = nWidth * nHeight * 4;
	SD_UINT8 * m_pVideoBuf = new SD_UINT8[nVideoBufSize];
	memset(m_pVideoBuf, 0, nVideoBufSize);
	//配置输出文件信息
	SDStreamMediaInfo streamInfo;
	CString strSufix = GetPresetMediaInfo(EmVideoStandard_HD, SDVIDEOTYPE_MPEG2_IFRAME, SDCOLORFORMAT_YUVP_422, SDAUDIOTYPE_WAVE_PCM, 48000, streamInfo);
	streamInfo.sVideoMediaInfo.dwGOPSize = 1;
	bool bRet =	pEncodec->SetSinkFile(&streamInfo, ConverCStringToStdString(strFilePreName + _T("video") + strSufix).c_str());
	//设置视频画面输入格式
	SDVideoFrameImageBufInfo imageBufInfo;
	imageBufInfo.dwXSize = nWidth;
	imageBufInfo.dwYSize = nHeight;
	imageBufInfo.dwScanXByteSize = nWidth * 2;
	imageBufInfo.enumColorFormat = SDCOLORFORMAT_BGRA;
	imageBufInfo.enumScanMode = SDVIDEOSCANMODE_FirstFieldTop;
	pEncodec->SetVideoFrameBufInfo(&imageBufInfo, nullptr);
	//设置音频输入格式
	SDAudioSamplesBufInfo audioBufInfo;
	audioBufInfo.enumAudioCFG = SDAUDIOCFG_STEREO;
	audioBufInfo.enumChannelSamplesFormat = (SD_CHANNELSAMPLE_FORMAT)1;
	audioBufInfo.dwSamplesPerSec = 48000;
	audioBufInfo.dwChannels = 2;
	pEncodec->SetAudioSamplesBufInfo(&audioBufInfo);
	//视频帧参数
	SDRFrameInfo frameInfoTmp;
	frameInfoTmp.emDataType = STREAM_DATATYPE_VIDEO;
	frameInfoTmp.iVersion = 0;		// 结构版本号。		4---4[序列化占用字节－序列化位置]
	frameInfoTmp.iSize = nWidth * nHeight * 4;// nWidth * nHeight * 2;			// 帧数据大小		4---16
	frameInfoTmp.dwFrameNum = 1;		// 视频/音频帧数量	4---32
	frameInfoTmp.iSamplesOffset = 0;	// 标识RawAudio音频、视频帧中有效采样的偏移数，大于0表示从开始偏移，小于0表示从尾部开始向前偏移		4---36
	frameInfoTmp.qwDuration = 40;		// 持续时间(90Khz单位)	8---6
	frameInfoTmp.emFrameType = FRAMETYPE_I;   	// 帧类型 				4---108
	frameInfoTmp.extradata_size = 0;
	CFile fileDebug;
	fileDebug.Open(_T("debug.pcm"), CFile::modeCreate | CFile::modeWrite);
	//循环读图片开始编码
	CString strFileSufix;
	for (int i = 0; i < nLength; i++)
	{
		strFileSufix.Format(_T("%d.bmp"), i);
		CString strVideoFileName = strFilePreName + strFileSufix;
		CFile fileImage;
		if (fileImage.Open(strVideoFileName, CFile::modeRead))
		{
			SD_UINT32 * pPixBuf = new SD_UINT32[nVideoBufSize / 4];
			memset(pPixBuf, 0, nVideoBufSize);
			int nRead = fileImage.Read(pPixBuf, 8294454 - 1920 * 1080 * 4);
			nRead = fileImage.Read(pPixBuf, 1920 * 1080 * 4);
			for (size_t x = 0; x < nWidth; x++)
			{
				for (size_t y = 0; y < nHeight; y++)
				{
					memcpy(m_pVideoBuf + ((nHeight - y - 1) * nWidth + x) * 4, pPixBuf + y * nWidth + x, 4);
				}
			}
			fileImage.Close();
			delete[] pPixBuf;
			pPixBuf = nullptr;
		}

		frameInfoTmp.dwFrameIndex = i;	// 帧数据流顺序		4---28
		frameInfoTmp.qwDTS = i * 40;			// 解码时间(90Khz单位)	8---44
		frameInfoTmp.qwPTS = i * 40;			// 展现时间(90Khz单位)	8---52
		frameInfoTmp.dwShowIndex = i;	// 帧数据显示顺序			4---104
		pEncodec->PutVideoBuffer(m_pVideoBuf, false, &frameInfoTmp);
		if (nAudioReadCursor + 1920 < nAudioSampleWhole)
		{
			pEncodec->PutAudioSamples((SD_UINT8 *)(pAudioBufer + nAudioReadCursor), 1920);
			fileDebug.Write((SD_UINT8 *)(pAudioBufer + nAudioReadCursor), 1920 * 4);
			nAudioReadCursor += 1920;
		}
		else
		{
			SD_UINT8 pBufTmp[1920 * 4] = {0};
			int nReaded = nAudioSampleWhole - nAudioReadCursor;
			memcpy(pBufTmp, pAudioBufer + nAudioReadCursor, nReaded * 4);
			nAudioReadCursor = 0;
			memcpy(pBufTmp + nReaded * 4, pAudioBufer, (1920 - nReaded) * 4);
			nAudioReadCursor = 1920 - nReaded;
			pEncodec->PutAudioSamples(pBufTmp, 1920);
			fileDebug.Write(pBufTmp, 1920 * 4);
		}
	}
	fileDebug.Close();
	delete[] m_pVideoBuf;
	m_pVideoBuf = nullptr;
	delete[] pAudioBufer;
	pAudioBufer = nullptr;
	ecFacetory->DeleteProtocolEncoder(pEncodec);
	ecCodec_ReleaseCodecFactory(ecFacetory);
}
