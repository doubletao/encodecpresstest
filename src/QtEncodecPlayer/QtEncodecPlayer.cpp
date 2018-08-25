#include "QtEncodecPlayer.h"
#include <QFileDialog>
#include <QMessageBox>

QtEncodecPlayer::QtEncodecPlayer(QWidget *parent)
	: QDialog(parent)
	, m_pWholeVLyaout(nullptr)
	, m_pTopHLayout(nullptr)
	, m_pTopRightWidgetVLayout(nullptr)
	, m_pInputOutputSettingHLayout(nullptr)
	, m_pOtherSettingHLayout(nullptr)
	, m_pPlayerWidget(nullptr)
	, m_pTopRightWidget(nullptr)
	, m_pMiddleHWidget(nullptr)
	, m_pInputOutputSettingWidget(nullptr)
	, m_pEncodecSetting(nullptr)
	, m_pOtherSettingWidget(nullptr)
	, m_pEditInfo(nullptr)
	, m_pAudioEffectWidget(nullptr)
	, m_pSldPlayProcess(nullptr)
	, m_pStSpeedShift(nullptr)
	, m_pCombSpeedShift(nullptr)
	, m_pCombSpeedRatio(nullptr)
	, m_pStPlayerSource(nullptr)
	, m_pCombPlayerSource(nullptr)
	, m_pBtnPlayerSourceSel(nullptr)
	, m_pStEncodecDes(nullptr)
	, m_pCombEncodecDes(nullptr)
	, m_pBtnEncodecDes(nullptr)
	, m_pChkPerformanceLog(nullptr)
	, m_pChkLockVAPts(nullptr)
	, m_pChkLoop(nullptr)
	, m_pChkForbitLoseFrame(nullptr)
	, m_pBtnCue(nullptr)
	, m_pBtnFirstFrame(nullptr)
	, m_pBtnPreFrame(nullptr)
	, m_pBtnPlayPause(nullptr)
	, m_pBtnNextFrame(nullptr)
	, m_pBtnLastFrame(nullptr)
	, m_pBtnStop(nullptr)
	, m_timerDisplay(nullptr)
	, m_pPlayer(nullptr)
{
	resize(1440, 900);
	Qt::WindowFlags flags = Qt::Dialog;
	flags |= Qt::WindowCloseButtonHint | Qt::WindowMinMaxButtonsHint;
	setWindowFlags(flags);

	CreateCtrl();
	LayoutCtrl();
	InitialConnect();
	m_evtQuit.ResetEvent();
	m_timerDisplay->start(40);
}

QtEncodecPlayer::~QtEncodecPlayer()
{
	m_evtQuit.SetEvent();
	DisConnect();
	Release();
}

void QtEncodecPlayer::Release()
{
	m_DecThreader.SetStop();
	for (auto it : m_vecEncThreader)
	{
		delete it;
		it = nullptr;
	}
	m_vecEncThreader.clear();
	if (m_pPlayer)
	{
		ReleasePlayer(m_pPlayer);
		m_pPlayer = nullptr;
	}
}

void QtEncodecPlayer::CreateCtrl()
{
	m_timerDisplay = new QTimer(this);
	m_timerDisplay->setTimerType(Qt::PreciseTimer);//毫秒级定时器

	m_pPlayerWidget = new QWidget(this);
	m_pPlayerWidget->setMinimumSize(400, 300);
	m_pTopRightWidget = new QWidget(this);
	m_pMiddleHWidget = new QWidget(this);
	m_pInputOutputSettingWidget = new QWidget(this);
	m_pEncodecSetting = new QWidget(this);
	m_pEncodecSetting->setMinimumHeight(250);
	m_pOtherSettingWidget = new QWidget(this);

	m_pEditInfo = new QTextEdit(m_pTopRightWidget);
	m_pEditInfo->setReadOnly(true);
	m_pAudioEffectWidget = new QWidget(m_pTopRightWidget);
	m_pAudioEffectWidget->setMinimumHeight(200);

	m_pSldPlayProcess = new QSlider(Qt::Horizontal, m_pMiddleHWidget);

	m_pStSpeedShift = new QLabel(tr("IDS_ENCODEC_PLAYER_SPEED_SWITCH"), m_pInputOutputSettingWidget);
	m_pCombSpeedShift = new QComboBox(m_pInputOutputSettingWidget);
	m_pCombSpeedShift->addItem(tr("IDS_ENCODEC_PLAYER_SPEED_UP"));
	m_pCombSpeedShift->addItem(tr("IDS_ENCODEC_PLAYER_SPEED_DOWN"));
	m_pCombSpeedShift->setCurrentIndex(0);
	m_pCombSpeedRatio = new QComboBox(m_pInputOutputSettingWidget);
	for (size_t i = 0; i < 25; i++)
	{
		m_pCombSpeedRatio->addItem(QString::number(i + 1));
	}
	m_pCombSpeedRatio->setCurrentIndex(0);

	m_pStPlayerSource = new QLabel(tr("IDS_ENCODEC_PLAYER_SRC_PATH"), m_pInputOutputSettingWidget);
	m_pCombPlayerSource = new QComboBox(m_pInputOutputSettingWidget);
	m_pCombPlayerSource->setEditable(true);
	m_pCombPlayerSource->addItem(tr("rtmp://live.hkstv.hk.lxdns.com/live/hks"));
	m_pCombPlayerSource->addItem(tr("rtmp://103.229.149.171/myapp/GoProCut"));
	m_pCombPlayerSource->addItem(tr("rtmp://192.168.20.153:1935/live/1"));
	m_pCombPlayerSource->setCurrentIndex(0);
	m_pBtnPlayerSourceSel = new QPushButton(tr("IDS_ENCODEC_PLAYER_SRC_SCAN"), m_pInputOutputSettingWidget);

	m_pStEncodecDes = new QLabel(tr("IDS_ENCODEC_PLAYER_DES_PATH"), m_pInputOutputSettingWidget);
	m_pCombEncodecDes = new QComboBox(m_pInputOutputSettingWidget);
	m_pCombEncodecDes->setEditable(true);
	m_pCombEncodecDes->addItem(tr("E:\\clip\\"));
	m_pCombEncodecDes->setCurrentIndex(0);
	m_pBtnEncodecDes = new QPushButton(tr("IDS_ENCODEC_PLAYER_DES_SCAN"), m_pInputOutputSettingWidget);

	m_pChkPerformanceLog = new QCheckBox(tr("IDS_ENCODEC_PLAYER_PERFORM_LOG"), m_pOtherSettingWidget);
	m_pChkLockVAPts = new QCheckBox(tr("IDS_ENCODEC_PLAYER_LOCK_VA_PTS"), m_pOtherSettingWidget);
	m_pChkLoop = new QCheckBox(tr("IDS_ENCODEC_PLAYER_LOOP_PLAY"), m_pOtherSettingWidget);
	m_pChkForbitLoseFrame = new QCheckBox(tr("IDS_ENCODEC_PLAYER_FORBID_FRAME_LOSE"), m_pOtherSettingWidget);
	m_pBtnCue = new QPushButton(tr("IDS_ENCODEC_PLAYER_PLCTRL_CUE"), m_pOtherSettingWidget);
	m_pBtnFirstFrame = new QPushButton(tr("IDS_ENCODEC_PLAYER_PLCTRL_FIRST_FRAME"), m_pOtherSettingWidget);
	m_pBtnPreFrame = new QPushButton(tr("IDS_ENCODEC_PLAYER_PLCTRL_PRE_FRAME"), m_pOtherSettingWidget);
	m_pBtnPlayPause = new QPushButton(tr("IDS_ENCODEC_PLAYER_PLCTRL_PLAY"), m_pOtherSettingWidget);
	m_pBtnNextFrame = new QPushButton(tr("IDS_ENCODEC_PLAYER_PLCTRL_NEXT_FRAME"), m_pOtherSettingWidget);
	m_pBtnLastFrame = new QPushButton(tr("IDS_ENCODEC_PLAYER_PLCTRL_LAST_FRAME"), m_pOtherSettingWidget);
	m_pBtnStop = new QPushButton(tr("IDS_ENCODEC_PLAYER_PLCTRL_STOP"), m_pOtherSettingWidget);

	m_pWholeVLyaout = new QVBoxLayout(this);
	m_pTopHLayout = new QHBoxLayout(this);
	m_pTopRightWidgetVLayout = new QVBoxLayout(m_pTopRightWidget);
	m_pMiddleHLayout = new QHBoxLayout(m_pMiddleHWidget);
	m_pInputOutputSettingHLayout = new QHBoxLayout(m_pInputOutputSettingWidget);
	m_pOtherSettingHLayout = new QHBoxLayout(m_pOtherSettingWidget);

	m_pPlayer = CreateVAPlayer(EM_VAPLayer_SDL);
	int nBufWidth = 1920;
	int nBugHeight = 1080;
	if (m_pPlayerWidget)
	{
		nBufWidth = m_pPlayerWidget->width();
		nBugHeight = m_pPlayerWidget->height();
	}
	m_pPlayer->CreatePayer((void *)m_pPlayerWidget->winId(), 0, 0, nBufWidth, nBugHeight, EmVAPlayerColorFmt_UYVY, nBufWidth, nBugHeight, true, EmVAPlayerSampleFmt_S16SYS, 48000, 2, 1920);
}

void QtEncodecPlayer::LayoutCtrl()
{
	//把控件加到布局里边
	setLayout(m_pWholeVLyaout);
	
	m_pWholeVLyaout->addLayout(m_pTopHLayout);
	m_pTopHLayout->addWidget(m_pPlayerWidget);
	m_pTopHLayout->addWidget(m_pTopRightWidget);

	m_pTopRightWidget->setLayout(m_pTopRightWidgetVLayout);
	m_pTopRightWidgetVLayout->addWidget(m_pEditInfo);
	m_pTopRightWidgetVLayout->addWidget(m_pAudioEffectWidget);

	m_pWholeVLyaout->addWidget(m_pInputOutputSettingWidget);
	m_pInputOutputSettingWidget->setLayout(m_pInputOutputSettingHLayout);
	m_pInputOutputSettingHLayout->addWidget(m_pStSpeedShift);
	m_pInputOutputSettingHLayout->addWidget(m_pCombSpeedShift);
	m_pInputOutputSettingHLayout->addWidget(m_pCombSpeedRatio);
	m_pInputOutputSettingHLayout->addStretch(1);
	m_pInputOutputSettingHLayout->addWidget(m_pStPlayerSource);
	m_pInputOutputSettingHLayout->addWidget(m_pCombPlayerSource, 1);
	m_pInputOutputSettingHLayout->addWidget(m_pBtnPlayerSourceSel);
	m_pInputOutputSettingHLayout->addStretch(1);
	m_pInputOutputSettingHLayout->addWidget(m_pStEncodecDes);
	m_pInputOutputSettingHLayout->addWidget(m_pCombEncodecDes, 1);
	m_pInputOutputSettingHLayout->addWidget(m_pBtnEncodecDes);

	m_pWholeVLyaout->addWidget(m_pMiddleHWidget);
	m_pMiddleHWidget->setLayout(m_pMiddleHLayout);
	m_pMiddleHLayout->addWidget(m_pSldPlayProcess);

	m_pWholeVLyaout->addWidget(m_pOtherSettingWidget);
	m_pOtherSettingWidget->setLayout(m_pOtherSettingHLayout);
	m_pOtherSettingHLayout->addWidget(m_pChkPerformanceLog);
	m_pOtherSettingHLayout->addWidget(m_pChkLockVAPts);
	m_pOtherSettingHLayout->addWidget(m_pChkLoop);
	m_pOtherSettingHLayout->addWidget(m_pChkForbitLoseFrame);
	m_pOtherSettingHLayout->addStretch(0);
	m_pOtherSettingHLayout->addWidget(m_pBtnCue);
	m_pOtherSettingHLayout->addWidget(m_pBtnFirstFrame);
	m_pOtherSettingHLayout->addWidget(m_pBtnPreFrame);
	m_pOtherSettingHLayout->addWidget(m_pBtnPlayPause);
	m_pOtherSettingHLayout->addWidget(m_pBtnNextFrame);
	m_pOtherSettingHLayout->addWidget(m_pBtnLastFrame);
	m_pOtherSettingHLayout->addWidget(m_pBtnStop);

	m_pWholeVLyaout->addWidget(m_pEncodecSetting);
}

void QtEncodecPlayer::InitialConnect()
{
	connect(m_pBtnPlayerSourceSel, SIGNAL(clicked()), this, SLOT(OnBnClickedSrcScan()));
	connect(m_pBtnEncodecDes, SIGNAL(clicked()), this, SLOT(OnBnClickedDesScan()));
	connect(m_pBtnCue, SIGNAL(clicked()), this, SLOT(OnBnClickedCue()));
	connect(m_pBtnFirstFrame, SIGNAL(clicked()), this, SLOT(OnBnClickedFirstFrame()));
	connect(m_pBtnPreFrame, SIGNAL(clicked()), this, SLOT(OnBnClickedPreFrame()));
	connect(m_pBtnPlayPause, SIGNAL(clicked()), this, SLOT(OnBnClickedPlayPause()));
	connect(m_pBtnNextFrame, SIGNAL(clicked()), this, SLOT(OnBnClickedNextFrame()));
	connect(m_pBtnLastFrame, SIGNAL(clicked()), this, SLOT(OnBnClickedLastFrame()));
	connect(m_pBtnStop, SIGNAL(clicked()), this, SLOT(OnBnClickedStop()));
	connect(this, SIGNAL(EmitInfoMsg(const char *)), this, SLOT(OnInfoMsgArrive(const char *)));
	connect(this, SIGNAL(EmitInfoMsg()), this, SLOT(OnInfoMsgArrive()));
	connect(m_timerDisplay, SIGNAL(timeout()), this, SLOT(DisplayBuf()));
}

void QtEncodecPlayer::DisConnect()
{
	disconnect(this, SIGNAL(EmitInfoMsg(const char *)), 0, 0);
	disconnect(this, SIGNAL(EmitInfoMsg()), 0, 0);
}

void QtEncodecPlayer::OnBnClickedSrcScan()
{
	QFileDialog fileDialog(this);
	fileDialog.setWindowTitle(tr("IDS_ENCODEC_PLAYER_SOURCE_FILE"));
	fileDialog.setDirectory(".");
	fileDialog.setFileMode(QFileDialog::ExistingFile);
	fileDialog.setViewMode(QFileDialog::Detail);
	fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
	QStringList fileNames;
	if (fileDialog.exec() == QDialog::Accepted)
	{
		fileNames = fileDialog.selectedFiles();
		for (int n = 0; n < fileNames.size(); n++)
		{
			QString str = fileNames.at(n);
			if (m_pCombPlayerSource)
			{
				m_pCombPlayerSource->setCurrentText(str);
			}
			break;
		}
	}
}

bool QtEncodecPlayer::CallbackOneFrameDecodecedFunc(unsigned long long nCurFrame, void * pData, size_t nVideoBufSize, size_t nAudioSampleCount)
{
	QtEncodecPlayer * pThis = (QtEncodecPlayer *)pData;
	if (pThis)
	{
		pThis->PushBuf();
	}
	return true;
}

bool QtEncodecPlayer::CallbackInfoMsgFunc(std::string strErr, void * pData)
{
	QtEncodecPlayer * pThis = (QtEncodecPlayer *)pData;
	if (pThis)
	{
		pThis->PushMsg(strErr);
	}
	return true;
}

void QtEncodecPlayer::PushMsg(std::string strMsg)
{
	m_lockMsgQueue.lock();
	m_queMsg.push(strMsg);
	m_lockMsgQueue.unlock();
	emit EmitInfoMsg();
}

bool QtEncodecPlayer::PushBuf()
{
	while (!m_vaLoop.Push(m_vaBuf))
	{
		//push不进去就等着，非得push进去了才算
		if (m_evtQuit.Wait(5))
		{
			break;
		}
	}
	return true;
}

void QtEncodecPlayer::DisplayBuf()
{
	if (m_vaLoop.Pop(m_vaBufDisp))
	{
		qDebug("%d", clock());
		//送入播放器
		m_pPlayer->PushFrame(m_vaBufDisp.GetVideoBuf(), m_desImageInfo.dwXSize * 2);
		m_pPlayer->PushAudioSample(m_vaBufDisp.GetAudioBuf(), m_vaBufDisp.GetAudioSampleCount() * m_desAudioInfo.dwBitsPerSample / 8);
	}
}

void QtEncodecPlayer::OnBnClickedDesScan()
{
	QString strFilePath = QFileDialog::getExistingDirectory(this, tr("IDS_ENCODEC_PLAYER_DESTINY_FILE"), "./");
	if (!strFilePath.isEmpty())
	{
		if (m_pCombEncodecDes)
		{
			m_pCombEncodecDes->setCurrentText(strFilePath);
		}
	}
}

void QtEncodecPlayer::OnBnClickedCue()
{
	QString strSrc = "";
	if (m_pCombPlayerSource)
	{
		strSrc = m_pCombPlayerSource->currentText();
		if (!strSrc.isEmpty())
		{
			m_DecThreader.SetStop();
			m_DecThreader.SetDecCallbackFunc(CallbackOneFrameDecodecedFunc, this);
			m_DecThreader.SetInfoMsgCallbackFunc(CallbackInfoMsgFunc, this);
			SDStreamMediaInfo mediaInfo;
			if (m_DecThreader.SetInputSource(strSrc.toStdString(), mediaInfo))
			{
				m_desImageInfo.dwXSize = 1920;
				m_desImageInfo.dwYSize = 1080;
				if (m_pPlayerWidget)
				{
					m_desImageInfo.dwXSize = m_pPlayerWidget->width();
					m_desImageInfo.dwYSize = m_pPlayerWidget->height();
				}
				m_desImageInfo.enumColorFormat = SDCOLORFORMAT_UYVY;
				m_desAudioInfo.enumAudioType = SDAUDIOTYPE_WAVE_PCM;
				m_desAudioInfo.dwBitsPerSample = 32;
				m_desAudioInfo.enumAudioCFG = SDAUDIOCFG_STEREO;
				m_desAudioInfo.dwAvgBitsPerSec = m_desAudioInfo.dwSamplesPerSec * m_desAudioInfo.dwBitsPerSample * m_desAudioInfo.dwChannels;
				m_desAudioInfo.enumChannelSamplesFormat = SDCHANNELSAMPLESFORMAT_Progressive;
				m_desAudioInfo.dwSamplesPerSec = 48000;
				m_desAudioInfo.dwChannels = 2;
				if (m_DecThreader.SetOutputParam(m_desImageInfo, m_desAudioInfo))
				{
					m_vaBuf.Reset(m_DecThreader.GetVideoBufSize(), m_DecThreader.GetSamplePerFrame());
					m_vaLoop.Reset(10, m_DecThreader.GetVideoBufSize(), m_DecThreader.GetSamplePerFrame());
					if (m_DecThreader.SetVideoBuf(m_vaBuf.GetVideoBuf(), m_vaBuf.GetVideoBufSize()))
					{
						if (m_DecThreader.SetAudioBuf(m_vaBuf.GetAudioBuf(), m_vaBuf.GetAudioSampleCount() * m_desAudioInfo.dwBitsPerSample / 8))
						{
							emit EmitInfoMsg("cued succ");
						}
					}
				}
				else
				{
					emit EmitInfoMsg("SetOutputParam failed");
				}
			}
			else
			{
				emit EmitInfoMsg("cue failed");
			}
		}
	}
}

void QtEncodecPlayer::OnBnClickedFirstFrame()
{
	m_DecThreader.SetFirstFrame();
}

void QtEncodecPlayer::OnBnClickedPreFrame()
{
	m_DecThreader.SetPreFrame();
}

void QtEncodecPlayer::OnBnClickedPlayPause()
{
	m_evtQuit.ResetEvent();
	if (m_pBtnPlayPause)
	{
		if (m_DecThreader.IsPlaying())
		{
			m_DecThreader.SetPlayPause(false);
			m_pBtnPlayPause->setText(tr("IDS_ENCODEC_PLAYER_PLCTRL_PLAY"));
		}
		else
		{
			m_DecThreader.SetPlayPause(true);
			m_pBtnPlayPause->setText(tr("IDS_ENCODEC_PLAYER_PLCTRL_PAUSE"));
		}
	}
}

void QtEncodecPlayer::OnBnClickedNextFrame()
{
	m_DecThreader.SetNextFrame();
}

void QtEncodecPlayer::OnBnClickedLastFrame()
{
	m_DecThreader.SetNextFrame();
}

void QtEncodecPlayer::OnBnClickedStop()
{
	m_evtQuit.SetEvent();
	m_DecThreader.SetStop();
	if (m_pBtnPlayPause)
	{
		m_pBtnPlayPause->setText(tr("IDS_ENCODEC_PLAYER_PLCTRL_PLAY"));
	}
}

void QtEncodecPlayer::OnInfoMsgArrive()
{
	std::string strMsg;
	m_lockMsgQueue.lock();
	if (!m_queMsg.empty())
	{
		strMsg = m_queMsg.front();
		m_queMsg.pop();
	}
	m_lockMsgQueue.unlock();
	OnInfoMsgArrive(strMsg.c_str());
}

void QtEncodecPlayer::OnInfoMsgArrive(const char * szInfoMsg)
{
	if (m_pEditInfo)
	{
		m_pEditInfo->append(szInfoMsg);
	}
}
