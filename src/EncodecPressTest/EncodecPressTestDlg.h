
// EncodecPressTestDlg.h : 头文件
//

#pragma once
#include "SDLVideoPlayer.h"
#include <string>
#include "afxcmn.h"

const int MSG_PUSHINFO = WM_USER + 0x00001;

// CEncodecPressTestDlg 对话框
class CEncodecPressTestDlg : public CDialogEx
{
private:
	SDLVideoPlayer m_player;
	unsigned int m_nEncoderCount;
	unsigned long long m_nFrame;
	unsigned long long m_nDispFrame;
	CRITICAL_SECTION m_lock;
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
};
