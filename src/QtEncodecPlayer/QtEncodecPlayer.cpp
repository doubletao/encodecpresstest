#include "QtEncodecPlayer.h"

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
{
	resize(1440, 900);
	Qt::WindowFlags flags = Qt::Dialog;
	flags |= Qt::WindowCloseButtonHint | Qt::WindowMinMaxButtonsHint;
	setWindowFlags(flags);

	CreateCtrl();
	LayoutCtrl();
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

	m_pWholeVLyaout->addWidget(m_pMiddleHWidget);
	m_pMiddleHWidget->setLayout(m_pMiddleHLayout);
	m_pMiddleHLayout->addWidget(m_pSldPlayProcess);

	m_pWholeVLyaout->addWidget(m_pInputOutputSettingWidget);
	m_pInputOutputSettingWidget->setLayout(m_pInputOutputSettingHLayout);
	m_pInputOutputSettingHLayout->addWidget(m_pStSpeedShift);
	m_pInputOutputSettingHLayout->addWidget(m_pCombSpeedShift);
	m_pInputOutputSettingHLayout->addWidget(m_pCombSpeedRatio);
	m_pInputOutputSettingHLayout->addStretch(1);
	m_pInputOutputSettingHLayout->addWidget(m_pStPlayerSource);
	m_pInputOutputSettingHLayout->addWidget(m_pCombPlayerSource, 3);
	m_pInputOutputSettingHLayout->addWidget(m_pBtnPlayerSourceSel);
	m_pInputOutputSettingHLayout->addStretch(1);
	m_pInputOutputSettingHLayout->addWidget(m_pStEncodecDes);
	m_pInputOutputSettingHLayout->addWidget(m_pCombEncodecDes, 3);
	m_pInputOutputSettingHLayout->addWidget(m_pBtnEncodecDes);

	m_pWholeVLyaout->addWidget(m_pEncodecSetting);

	m_pWholeVLyaout->addWidget(m_pOtherSettingWidget);
	m_pOtherSettingWidget->setLayout(m_pOtherSettingHLayout);
	m_pOtherSettingHLayout->addWidget(m_pChkPerformanceLog);
	m_pOtherSettingHLayout->addWidget(m_pChkLockVAPts);
	m_pOtherSettingHLayout->addWidget(m_pChkLoop);
	m_pOtherSettingHLayout->addWidget(m_pChkForbitLoseFrame);
}
