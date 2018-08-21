#include "QtEncodecPlayer.h"
#include <QFileDialog>

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
{
	resize(1440, 900);
	Qt::WindowFlags flags = Qt::Dialog;
	flags |= Qt::WindowCloseButtonHint | Qt::WindowMinMaxButtonsHint;
	setWindowFlags(flags);

	CreateCtrl();
	LayoutCtrl();
	InitialConnect();
}

QtEncodecPlayer::~QtEncodecPlayer()
{
}

void QtEncodecPlayer::CreateCtrl()
{
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
}

void QtEncodecPlayer::OnBnClickedFirstFrame()
{
}

void QtEncodecPlayer::OnBnClickedPreFrame()
{
}

void QtEncodecPlayer::OnBnClickedPlayPause()
{
	if (m_pBtnPlayPause)
	{
		m_pBtnPlayPause->setText(tr("IDS_ENCODEC_PLAYER_PLCTRL_PAUSE"));
	}
}

void QtEncodecPlayer::OnBnClickedNextFrame()
{
}

void QtEncodecPlayer::OnBnClickedLastFrame()
{
}

void QtEncodecPlayer::OnBnClickedStop()
{
}
