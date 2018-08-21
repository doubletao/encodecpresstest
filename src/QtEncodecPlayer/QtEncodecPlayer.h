#pragma once

#include <QtWidgets/QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QSlider>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QCheckBox>
#include "EncodecThreader.h"

class QtEncodecPlayer : public QDialog
{
	Q_OBJECT
public:
	QtEncodecPlayer(QWidget *parent = Q_NULLPTR);
	~QtEncodecPlayer();
protected:
	void CreateCtrl();
	void LayoutCtrl();
	void InitialConnect();
protected:
protected slots:
	void OnBnClickedSrcScan();
	void OnBnClickedDesScan();
	void OnBnClickedCue();
	void OnBnClickedFirstFrame();
	void OnBnClickedPreFrame();
	void OnBnClickedPlayPause();
	void OnBnClickedNextFrame();
	void OnBnClickedLastFrame();
	void OnBnClickedStop();
protected:
	//Layout
	QVBoxLayout * m_pWholeVLyaout;//全局的一个纵向layout
	QHBoxLayout * m_pTopHLayout;//上部区域layout
	QVBoxLayout * m_pTopRightWidgetVLayout;//上部右侧区域
	QHBoxLayout * m_pMiddleHLayout;//中部滑条
	QHBoxLayout * m_pInputOutputSettingHLayout;//输入输出和播放速度横向布局
	QHBoxLayout * m_pOtherSettingHLayout;//底部其他设置布局
	//第一层
	QWidget * m_pPlayerWidget;//播放器区域
	QWidget * m_pTopRightWidget;//播放器右边区域
	QWidget * m_pMiddleHWidget;//中部滑条区域
	QWidget * m_pInputOutputSettingWidget;//输入输出及播放速度设置
	QWidget * m_pEncodecSetting;//编解码设置
	QWidget * m_pOtherSettingWidget;//其他设置项
	//第二层
	//信息窗口及音频设置
	QTextEdit * m_pEditInfo;//信息窗口
	QWidget * m_pAudioEffectWidget;//音频设置窗
	//中部滑条区域
	QSlider * m_pSldPlayProcess;//播放进度滑条
	//输入输出及播放速度设置
	//变速
	QLabel * m_pStSpeedShift;//变速
	QComboBox * m_pCombSpeedShift;
	QComboBox * m_pCombSpeedRatio;
	//输入输出
	QLabel * m_pStPlayerSource;
	QComboBox * m_pCombPlayerSource;
	QPushButton * m_pBtnPlayerSourceSel;//浏览
	QLabel * m_pStEncodecDes;
	QComboBox * m_pCombEncodecDes;
	QPushButton * m_pBtnEncodecDes;//浏览
	//其他设置项
	QCheckBox * m_pChkPerformanceLog;//性能日志
	QCheckBox * m_pChkLockVAPts;//强制pts对齐
	QCheckBox * m_pChkLoop;//循环播放
	QCheckBox * m_pChkForbitLoseFrame;//禁止丢帧
	//播放控制
	QPushButton * m_pBtnCue;
	QPushButton * m_pBtnFirstFrame;
	QPushButton * m_pBtnPreFrame;
	QPushButton * m_pBtnPlayPause;
	QPushButton * m_pBtnNextFrame;
	QPushButton * m_pBtnLastFrame;
	QPushButton * m_pBtnStop;
};
