
// EncodecPressTestDlg.h : 头文件
//

#pragma once
#include "SDLVideoPlayer.h"
#include <string>
#include "afxcmn.h"
#include "IecCodecFactory.h"
#include "EncodecThreader.h"

const int MSG_PUSHINFO = WM_USER + 0x00001;

// CEncodecPressTestDlg 对话框
class CEncodecPressTestDlg : public CDialogEx
{
private:
	SDLVideoPlayer m_player;
	unsigned long long m_nFrame;
	unsigned long long m_nDispFrame;
	int m_nTimebaseDen;
	int m_nTimebaseNum;
	EncodecThreader * m_pEncoder[8];
	IecCodecFactory * m_ecfactory;
	CRITICAL_SECTION m_lock;

	CStdioFile m_fileLog;
	bool m_bLogOpened;
private:
	CWinThread * m_pThread;
	CEvent m_evtPlayStop;
	CEvent m_evtPlayPause;
	static UINT ThreadPlay(LPVOID pParam);

	void StartPlay();
	void PausePlay();
	void StopPlay();
	void DoPlay();
// 构造
public:
	CEncodecPressTestDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CEncodecPressTestDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ENCODECPRESSTEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	void Lock();
	void Unlock();

protected:
	static std::string ConverCStringToStdString(CString & cstrValue);//CString与string之间的转换
	static CString ConvertStdStringToCString(const std::string & strValue);//CString与string之间的转换

protected:
	afx_msg LRESULT PushInfoMsg(WPARAM wParam, LPARAM lParam);
	void PushInfo(CString strInfo);
// 实现
private:
	CButton	*	GetCodecCheckBtn(int nCodecIndex);
	CComboBox * GetCodecVideoStandardCombo(int nCodecIndex);
	CComboBox * GetCodecVideoTypeCombo(int nCodecIndex);
	CComboBox * GetCodecColorFmtCombo(int nCodecIndex);
	CComboBox * GetCodecAudioTypeCombo(int nCodecIndex);
	CEdit *		GetCodecH264LevelEdit(int nCodecIndex);
	CEdit *		GetCodecFileNameEdit(int nCodecIndex);
	CEdit *		GetCodecFileSurfixEdit(int nCodecIndex);
	void OnCheckEncodec(int nIndex);

	bool GetCodecCheck(int nIndex);
	SD_VIDEO_STANDARD GetCodecVideoStandard(int nIndex);
	SD_VIDEO_TYPE GetCodecVideoType(int nIndex);
	SD_COLOR_FORMAT GetCodecColorFmt(int nIndex);
	SD_AUDIO_TYPE GetCodecAudioType(int nIndex);
	int GetCodecH264Level(int nIndex);

	void DealCtrlFileName();
	CString GenerateFileInfoName(SD_VIDEO_STANDARD emVideoStandard, SD_VIDEO_TYPE emVideoType, SD_COLOR_FORMAT emColorFormat, SD_AUDIO_TYPE emAudioType, int nH264Level);
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnStart();
	afx_msg void OnBnClickedBtnPause();
	afx_msg void OnBnClickedBtnStop();
	afx_msg void OnBnClickedBtnChooseFile();
	afx_msg void OnBnClickedBtnOutChooseFile();
	CSliderCtrl m_ctrSlider;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnNMReleasedcaptureSliderSeek(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedCheckEncodec1();
	afx_msg void OnBnClickedCheckEncodec2();
	afx_msg void OnBnClickedCheckEncodec3();
	afx_msg void OnBnClickedCheckEncodec4();
	afx_msg void OnBnClickedCheckEncodec5();
	afx_msg void OnBnClickedCheckEncodec6();
	afx_msg void OnBnClickedCheckEncodec7();
	afx_msg void OnBnClickedCheckEncodec8();
	afx_msg void OnBnClickedBtnCopyFirstParam();
};
