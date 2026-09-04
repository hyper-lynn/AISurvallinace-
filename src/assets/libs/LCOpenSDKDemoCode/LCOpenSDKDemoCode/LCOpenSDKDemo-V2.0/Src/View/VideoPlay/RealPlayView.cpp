#include <QPainter>

#include "Src/Utils/global.h"
#include "Src/Ctrl/RealPlayCtrl.h"
#include "Src/Utils/CommonView/IconTextBtn.h"
#include "Src/Utils/CommonView/IconBtn.h"
#include "Src/Utils/CommonView/SplitLine.h"
#include "Src/View/VideoPlay/PtzControlView.h"

#include "RealPlayView.h"

RealPlayView::RealPlayView(QWidget *parent)
	: QWidget(parent)
	, m_isInit(false)
	, m_videoBase(NULL)
	, m_viewCtrl(NULL)
	, m_btnBack(NULL)
	, m_btnSnap(NULL)
	, m_btnRecord(NULL)
	, m_btnTalk(NULL)
	, m_btnDefinition(NULL)
	, m_btnAudio(NULL)
	, m_btnFullScreen(NULL)
	, m_deviceIndex(-1)
	, m_isMaximize(false)
	, m_showInfo(NULL)
	, m_showInfoStreamMode(NULL)
	, m_definitionMode(0)
	, m_ptzControlView(NULL)
	, m_splitLine(NULL)
{
	hide();
}

RealPlayView::~RealPlayView()
{
	if (m_viewCtrl)
	{
		m_viewCtrl->stopPlay();
		SAFE_DELETE(m_viewCtrl);
	}
	SAFE_DELETE(m_videoBase);
	SAFE_DELETE(m_btnBack);
	SAFE_DELETE(m_btnSnap);
	SAFE_DELETE(m_btnRecord);
	SAFE_DELETE(m_btnTalk);
	SAFE_DELETE(m_btnDefinition);
	SAFE_DELETE(m_btnAudio);
	SAFE_DELETE(m_btnFullScreen);
	SAFE_DELETE(m_showInfo);
	SAFE_DELETE(m_ptzControlView);
	SAFE_DELETE(m_splitLine);
}

int RealPlayView::init()
{
	int ret = 0;
	fillBackGroundWithColor(this, QColor(38, 39, 42));

	do
	{
		m_videoBase = new QWidget(this);
		if (NULL == m_videoBase)
		{
			ret = -1;
			break;
		}

		m_viewCtrl = new RealPlayCtrl();
		if (NULL == m_viewCtrl)
		{
			ret = -1;
			break;
		}
		ret = m_viewCtrl->init(m_videoBase);
		if (ret != 0)
		{
			break;
		}
		connect(m_viewCtrl, SIGNAL(sgnPlayerStatusChanged(int)), this, SLOT(slotPlayerStatusChanged(int)));
		connect(m_viewCtrl, SIGNAL(sgnRecorderStatusChanged(int)), this, SLOT(slotRecorderStatusChanged(int)));
		connect(m_viewCtrl, SIGNAL(sgnTalkerStatusChanged(int)), this, SLOT(slotTalkerStatusChanged(int)));

		connect(m_viewCtrl, SIGNAL(sgnGetCurrentStreamMode(int)), this, SLOT(slotGetCurrentStreamMode(int)));
		

		m_showInfo = new QLabel(this);
		if (NULL == m_showInfo)
		{
			ret = -1;
			break;
		}

		m_showInfoStreamMode = new QLabel(this);

		m_splitLine = new SplitLine(this, QColor(0xfd, 0x8b, 0x30), 1);
		if (NULL == m_splitLine)
		{
			ret = -1;
			break;
		}

		m_btnBack = new IconTextBtn(this);
		m_btnSnap = new IconBtn(this, "Skin/real-time video/video_icon_screenshot", ICON_STATUS_DEFAULT | ICON_STATUS_NOABLE);
		m_btnRecord = new IconBtn(this, "Skin/real-time video/video_icon_takevideo", ICON_STATUS_DEFAULT | ICON_STATUS_NOABLE | ICON_STATUS_ING);
		m_btnTalk = new IconBtn(this, "Skin/real-time video/video_icon_speak", ICON_STATUS_DEFAULT | ICON_STATUS_NOABLE | ICON_STATUS_ING);
		m_btnDefinition = new IconBtn(this, "Skin/real-time video/video_hd", ICON_STATUS_DEFAULT | ICON_STATUS_NOABLE);
		m_btnAudio = new IconBtn(this, "Skin/real-time video/video_sound_off", ICON_STATUS_DEFAULT | ICON_STATUS_NOABLE);
		m_btnFullScreen = new IconBtn(this, "Skin/real-time video/video_icon_full_screen");

		if (NULL == m_btnBack || NULL == m_btnSnap || NULL == m_btnRecord
			|| NULL == m_btnTalk || NULL == m_btnDefinition || NULL == m_btnAudio
			|| NULL == m_btnFullScreen)
		{
			ret = -1;
			break;
		}

		m_btnBack->setBtnAttribute("Skin/common_icon_back", tr("Back to Devices List"), 11, QColor(0xb0, 0xaf, 0xaf));
		connect(m_btnBack, SIGNAL(clicked()), this, SLOT(slotBackBtnClicked()));
		connect(m_btnSnap, SIGNAL(clicked()), this, SLOT(slotSnapBtnClicked()));
		connect(m_btnRecord, SIGNAL(clicked()), this, SLOT(slotRecordBtnClicked()));
		connect(m_btnTalk, SIGNAL(clicked()), this, SLOT(slotTalkBtnClicked()));
		connect(m_btnDefinition, SIGNAL(clicked()), this, SLOT(slotDefinitionBtnClicked()));
		connect(m_btnAudio, SIGNAL(clicked()), this, SLOT(slotAudioBtnClicked()));
		connect(m_btnFullScreen, SIGNAL(clicked()), this, SLOT(slotFullScreenBtnClicked()));

		m_ptzControlView = new PtzControlView(this);
		if (NULL == m_ptzControlView)
		{
			ret = -1;
			break;
		}
		ret = m_ptzControlView->init();
		if (ret != 0)
		{
			ret = -1;
			break;
		}
		connect(m_ptzControlView, SIGNAL(sgnShowWhole(bool)), this, SLOT(slotPtzViewState(bool)));
		connect(m_ptzControlView, SIGNAL(sgnPtzControl(int, int)), this, SLOT(slotPtzControl(int, int)));

		m_isInit = true;
	} while (0);

	/*设置按钮默认有效性*/
	onPlayerStatusChanged(STATUS_STOP);

	/*调整布局*/
	refreshLayout();

	m_parentWidget = (QMainWindow *)parentWidget()->parentWidget()->parentWidget()->parentWidget();
	return ret;
}

void RealPlayView::setPosition(const QRect &position)
{
	m_position = position;

	this->setFixedSize(m_position.width(), m_position.height());
	this->move(m_position.left(), m_position.top());
}

void RealPlayView::hide()
{
	if (m_isInit)
	{
		stopPlay();
		onPlayerStatusChanged(STATUS_STOP);
	};
}

void RealPlayView::refreshLayout()
{
	if (!m_isInit)
	{
		DLOG("please call init() first!!!\n");
		return;
	}

	/*调整控件布局*/
	QWidget *parent = (QWidget*)this->parent();
	if (parent && !m_isMaximize)
	{
		setPosition(QRect(0, 0, parent->width(), parent->height()));
	}

	QPoint pt(2, 42 + 2);
	m_videoBase->move(pt);
	m_videoBase->setFixedSize(this->width() - 4, this->height() - pt.y() - 64);
	fillBackGroundWithColor(m_videoBase, QColor(0, 0, 0));

	/*分割线*/
	m_splitLine->move(0, 0);
	m_splitLine->setFixedWidth(this->width());

	m_btnBack->move(22, 6);

	int btnX = 20;
	int btnY = this->height() - 40 - 12;
	m_btnSnap->setPosition(QPoint(btnX, btnY));

	btnX += (m_btnSnap->width() + 14);
	m_btnRecord->setPosition(QPoint(btnX, btnY));

	btnX += (m_btnRecord->width() + 14);
	m_btnDefinition->setPosition(QPoint(btnX, btnY));

	btnX += (m_btnDefinition->width() + 14);
	m_btnTalk->setPosition(QPoint(btnX, btnY));

	btnX += (m_btnTalk->width() + 14);
	m_btnAudio->setPosition(QPoint(btnX, btnY));

	btnX += (m_btnAudio->width() + 14);
	m_btnFullScreen->setPosition(QPoint(btnX, btnY));

	QFont font("Microsoft YaHei", 11);
	m_showInfo->setFont(font);
	m_showInfo->setStyleSheet("color:#B0AFAF;");
	m_showInfo->adjustSize();
	m_showInfo->move(this->width() - 16 - m_showInfo->width(), (42 - m_showInfo->height()) / 2);

	/*根据云台控制窗口是否处于显示状态调整云台窗口布局*/
	if (m_ptzControlView->isShowWhole())
	{
		m_ptzControlView->move(this->width() - m_ptzControlView->width(), this->height() - 209);
	}
	else
	{
		m_ptzControlView->move(this->width() - m_ptzControlView->width(), this->height() - 64 + (64 - 32) / 2);
	}
}

void RealPlayView::fillBackGroundWithColor(QWidget *widget, QColor& color)
{
	if (NULL == widget)
	{
		return;
	}

	widget->setAutoFillBackground(true);
	QPalette palette;
	palette.setColor(QPalette::Background, color);
	widget->setPalette(palette);
}

void RealPlayView::paintEvent(QPaintEvent *paintEvent)
{
	QWidget::paintEvent(paintEvent);

	QPainter painter(this);

	/*绘制云台控制窗口部分的分割线和特殊背景色*/
	painter.setPen(QPen(QBrush(QColor(0x1a, 0x1a, 0x1a)), 1));
	painter.drawLine(this->width() - 247, this->height() - 64, this->width() - 247, this->height());
	painter.fillRect(this->width() - 246, this->height() - 64, 246, 42, QColor(0x2d, 0x2e, 0x31));
}

void RealPlayView::showRealPlayView(int deviceIndex, int definitionMode)
{
	if (!m_isInit)
	{
		DLOG("please call init() first!!!\n");
		return;
	}

	m_deviceIndex = deviceIndex;
	m_definitionMode = definitionMode;
	int ret = m_viewCtrl->play(m_deviceIndex, definitionMode);
}

void RealPlayView::stopPlay()
{
	if (!m_isInit)
	{
		DLOG("please call init() first!!!\n");
		return;
	}

	m_viewCtrl->stopPlay();
}

void RealPlayView::onPlayerStatusChanged(int status)
{
	if (!m_isInit)
	{
		DLOG("please call init() first!!!\n");
		return;
	}

	bool isBtnEnable = false;
	switch (status)
	{
	case STATUS_START:
		isBtnEnable = true;
		break;
	case STATUS_LOADING:
		break;
	default:
		m_viewCtrl->setTalkStatusBak(false);
		isBtnEnable = false;
		break;
	}

	/*调整按钮有效性*/
	m_btnSnap->setBtnEnable(isBtnEnable);
	m_btnRecord->setBtnEnable(isBtnEnable);
	m_btnDefinition->setBtnEnable(isBtnEnable);
	m_btnTalk->setBtnEnable(isBtnEnable);
	m_btnAudio->setBtnEnable(isBtnEnable);
	if (isBtnEnable)
	{
		m_btnDefinition->setIconPath("Skin/real-time video/video_" + (m_definitionMode == 0 ? QString("hd") : QString("sd")));
	}
	else
	{
		m_btnAudio->setIconPath("Skin/real-time video/video_sound_off");
		m_btnTalk->setIngStatus(false);
		m_btnRecord->setIngStatus(false);
	}

	/*开始播放后恢复对讲状态*/
	if (STATUS_START == status)
	{
		if (m_viewCtrl->getTalkStatusBak())
		{
			m_viewCtrl->playTalk();
		}
	}
}

void RealPlayView::onTalkerStatusChanged(int status)
{
	/* 修改对讲按钮状态(开启对讲中按钮不能重复点击) */
	m_btnTalk->setBtnEnable(STATUS_LOADING != status);
	m_btnTalk->setIngStatus(STATUS_START == status);

	/* 对讲时音频按钮不可操作 */
	m_btnAudio->setBtnEnable(status != STATUS_START);
}

void RealPlayView::setShowInfo(QString info)
{
	if (!m_isInit)
	{
		DLOG("please call init() first!!!\n");
		return;
	}

	m_showInfo->setText(tr("Status>>>") + info);
	m_showInfo->adjustSize();
	m_showInfo->show();
	//m_showInfo->repaint();

	m_showInfo->move(this->width() - 16 - m_showInfo->width(), m_showInfo->y());
}

void RealPlayView::setMaximize(bool isMaximize)
{
	m_isMaximize = isMaximize;
	setShowInfo(m_isMaximize ? tr("Full screen.") : tr("Normal window."));
	if (m_isMaximize)
	{
		this->setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint | Qt::X11BypassWindowManagerHint);  //隐藏任务栏
		m_parentWidget->setFixedSize(QApplication::desktop()->width(), QApplication::desktop()->height());
		this->setWindowFlags(Qt::Window);
		this->showFullScreen();

		m_btnFullScreen->setIconPath("Skin/real-time video/video_icon_exitfull_screen");
	}
	else
	{
		m_parentWidget->setFixedSize(1022, 670);
		this->setWindowFlags(Qt::SubWindow);
		this->showNormal();

		m_btnFullScreen->setIconPath("Skin/real-time video/video_icon_full_screen");
	}

	/*窗口最大化or还原时需要重新调整布局*/
	refreshLayout();
}

void RealPlayView::slotBackBtnClicked()
{
	DLOG("slotBackBtnClicked\n");
	m_ptzControlView->setShowWhole(false);
	setMaximize(false);

	this->hide();
	/* 返回设备列表 */
	emit sgnReturnToDevicesList(false);
}

void RealPlayView::slotSnapBtnClicked()
{
	DLOG("slotSnapBtnClicked\n");

	int ret = m_viewCtrl->snapShot();
	setShowInfo(0 == ret ? tr("Snapshot succeed.") : tr("Snapshot failed!"));
}

void RealPlayView::slotRecordBtnClicked()
{
	DLOG("slotRecordBtnClicked\n");

	if (m_viewCtrl->isRecording())
	{
		m_viewCtrl->stopRecord();
		m_btnRecord->setIngStatus(false);

		setShowInfo(tr("Stop recording."));
	}
	else
	{
		m_viewCtrl->startRecord();
		m_btnRecord->setIngStatus(true);

		setShowInfo(tr("Start recording."));
	}
}

void RealPlayView::slotDefinitionBtnClicked()
{
	DLOG("slotDefinitionBtnClicked\n");

	/* 备份好对讲状态 */
	m_viewCtrl->setTalkStatusBak(m_viewCtrl->isTalking());

	/* 高标清切换, 第二个参数控制清晰度(0高清, 1标清) */
	showRealPlayView(m_deviceIndex, m_definitionMode == 0 ? 1 : 0);
}

void RealPlayView::slotTalkBtnClicked()
{
	DLOG("slotTalkBtnClicked\n");

	if (m_viewCtrl->isTalking())
	{
		m_viewCtrl->stopTalk();
		slotTalkerStatusChanged(STATUS_STOP);
	}
	else
	{
		m_viewCtrl->playTalk();
	}
}

void RealPlayView::slotAudioBtnClicked()
{
	DLOG("slotAudioBtnClicked\n");

	if (m_viewCtrl->isAudioPlay())
	{
		m_viewCtrl->stopAudio();
		m_btnAudio->setIconPath("Skin/real-time video/video_sound_off");

		setShowInfo(tr("Close audio."));
	}
	else
	{
		m_viewCtrl->playAudio();
		m_btnAudio->setIconPath("Skin/real-time video/video_sound_on");

		setShowInfo(tr("Open audio."));
	}
}

void RealPlayView::slotFullScreenBtnClicked()
{
	DLOG("slotFullScreenBtnClicked\n");

	/*控制窗口最大化 or 还原*/
	setMaximize(!m_isMaximize);
}

void RealPlayView::slotPlayerStatusChanged(int status)
{
	QString str;
	switch (status)
	{
	case STATUS_LOADING:
		m_showInfoStreamMode->clear();
		str = tr("Loading video...");
		break;
	case STATUS_START:
		str = tr("Start play") + QString("[") + (m_definitionMode == 0 ? tr("HD") : tr("SD")) + QString("].");
		break;
	case STATUS_STOP:
		str = tr("Stop play.");
		break;
	case STATUS_FAIL:
		str = tr("Play failed!");
		break;
	}
	setShowInfo(str);

	/*响应播放状态更改*/
	onPlayerStatusChanged(status);
}

void RealPlayView::slotRecorderStatusChanged(int status)
{
	if (STATUS_STOP == status)
	{
		m_btnRecord->setIngStatus(false);
		setShowInfo(tr("Stop recording."));
	}
}

void RealPlayView::slotTalkerStatusChanged(int status)
{
	QString str;
	switch (status)
	{
	case STATUS_LOADING:
		str = tr("Starting to talk...");
		break;
	case STATUS_START:
		str = tr("Talk start.");
		break;
	case STATUS_STOP:
		str = tr("Talk stop.");
		break;
	case STATUS_FAIL:
		str = tr("Talk failed!");
		break;
	}
	setShowInfo(str);

	/* 响应对讲状态更改 */
	onTalkerStatusChanged(status);
}

void RealPlayView::slotGetCurrentStreamMode(int streamMode)
{
	QString str("");
	if (streamMode == 0)
	{
		str = tr("Start play") + QString("[") + QString("P2P") + QString("].");
	}
	else
	{
		str = tr("Start play") + QString("[") + QString("MTS") + QString("].");
	}
	QFont font("Microsoft YaHei", 11);
	m_showInfoStreamMode->setFont(font);
	m_showInfoStreamMode->setStyleSheet("color:#B0AFAF;");
	m_showInfoStreamMode->adjustSize();
	m_showInfoStreamMode->move(this->width() - 16 - m_showInfo->width() - m_showInfoStreamMode->width() - 300, (42 - m_showInfoStreamMode->height()) / 2);

	m_showInfoStreamMode->setText(str);
	m_showInfoStreamMode->adjustSize();
	m_showInfoStreamMode->show();
}

void RealPlayView::slotPtzViewState(bool isShow)
{
	/* 云台控制窗口显示和隐藏时都要重新布局 */
	if (!isShow)
	{
		QString str = tr("Start play") + QString("[") + (m_definitionMode == 0 ? tr("HD") : tr("SD")) + QString("].");
		setShowInfo(str);
	}
	refreshLayout();
}

void RealPlayView::slotPtzControl(int ptzCtrl, int ptzCtrlType)
{
	int ret = m_viewCtrl->ptzControlAsyn((PTZ_CONTROL_DIRECTION_E)ptzCtrl, (PTZ_CTRL_TYPE_E)ptzCtrlType);
	if (0 == ret)
	{
		setShowInfo(tr("PTZing..."));
	}
	else
	{
		if (-2 == ret)
		{
			setShowInfo(tr("PTZ isn't allowed unless real video is playing!"));
		}
		else if (-3 == ret)
		{
			setShowInfo(tr("The device has no PTZ ability!"));
		}
		else
		{
			setShowInfo(tr("PTZ failed") + QString("[") + QString::number(ret) + QString("]!"));
		}
	}
}

