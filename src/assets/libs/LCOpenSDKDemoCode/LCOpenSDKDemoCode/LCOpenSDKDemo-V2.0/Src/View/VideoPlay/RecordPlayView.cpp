#include <QPainter>
#include <QLabel>
#include <qinputdialog.h>
#include "Src/Utils/global.h"
#include "Src/Ctrl/RecordPlayCtrl.h"
#include "Src/Ctrl/RecordListCtrl.h"
#include "Src/Utils/CommonView/IconTextBtn.h"
#include "Src/Utils/CommonView/ProgressSlider.h"
#include "Src/Utils/CommonView/IconBtn.h"
#include "Src/Utils/CommonView/BaseWidget.h"
#include "Src/Utils/CommonView/SplitLine.h"
#include "Src/Utils/CommonView/PlayBackSpeed/PlayBackSpeed.h"
#include "RecordPlayView.h"


RecordPlayView::RecordPlayView(QWidget *parent)
	: QWidget(parent)
	, m_videoBase(NULL)
	, m_isInit(false)
	, m_viewCtrl(NULL)
	, m_labelChannelName(NULL)
	, m_btnBack(NULL)
	, m_btnPlay(NULL)
	, m_showInfo(NULL)
	, m_progressBar(NULL)
	, m_beginTimeLabel(NULL)
	, m_endTimeLabel(NULL)
	, m_btnFullScreen(NULL)
	, m_btnSpeed(NULL)
	, m_pSpeedMenu(NULL)
	, m_isMaximize(false)
	, m_isBtnSpeed(false)
	, m_channelName(tr("Channel name"))
	, m_splitLine(NULL)
	, m_splitLine2(NULL)
	, m_iSpeed(0)
	, m_showInfoStreamMode(NULL)
{
	hide();
}

RecordPlayView::~RecordPlayView()
{
	stopPlay();

	SAFE_DELETE(m_viewCtrl);
	SAFE_DELETE(m_btnPlay);
	SAFE_DELETE(m_videoBase);
	SAFE_DELETE(m_labelChannelName);
	SAFE_DELETE(m_btnBack);
	SAFE_DELETE(m_showInfo);
	SAFE_DELETE(m_progressBar);
	SAFE_DELETE(m_beginTimeLabel);
	SAFE_DELETE(m_endTimeLabel);
	SAFE_DELETE(m_btnFullScreen);
	SAFE_DELETE(m_btnSpeed);
	SAFE_DELETE(m_pSpeedMenu);
	SAFE_DELETE(m_splitLine);
	SAFE_DELETE(m_splitLine2);
	SAFE_DELETE(m_decryptKeyBox);
}

int RecordPlayView::init()
{
	int ret = 0;
	fillBackGroundWithColor(this, QColor(0x20, 0x22, 0x24));

	do
	{
		m_videoBase = new BaseWidget(this);
		if (NULL == m_videoBase)
		{
			ret = -1;
			break;
		}
		connect(m_videoBase, SIGNAL(sgnClicked()), this, SLOT(slotVideoBaseClicked()));

		m_viewCtrl = new RecordPlayCtrl();
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
		connect(m_viewCtrl, SIGNAL(sgnPlayerTime(long)), this, SLOT(slotPlayerTime(long)));
		connect(m_viewCtrl, SIGNAL(sgnPlayerError(int)), this, SLOT(slotPlayerKeyError(int)));

		connect(m_viewCtrl, SIGNAL(sgnGetCurrentStreamMode(int)), this, SLOT(slotGetCurrentStreamMode(int)));
		m_splitLine = new SplitLine(this, QColor(0xfd, 0x8b, 0x30), 1);
		if (NULL == m_splitLine)
		{
			ret = -1;
			break;
		}

		m_splitLine2 = new SplitLine(this, QColor(0x00, 0x00, 0x00), QColor(0x32, 0x34, 0x36));
		if (NULL == m_splitLine2)
		{
			ret = -1;
			break;
		}

		m_btnPlay = new IconBtn(/*m_videoBase*/this, "Skin/common_icon_btn_play", ICON_TYPE_MASK | ICON_TYPE_OPAQUEPAINT);
		if (NULL == m_btnPlay)
		{
			ret = -1;
			break;
		}
		m_btnPlay->raise();
		m_btnPlay->hide();
		connect(m_btnPlay, SIGNAL(clicked()), this, SLOT(slotPlayBtnClicked()));

		m_btnBack = new IconTextBtn(this);
		if (NULL == m_btnBack)
		{
			ret = -1;
			break;
		}
		m_btnBack->setBtnAttribute("Skin/common_icon_back", tr("Back to Records List"), 11, QColor(0xb0, 0xaf, 0xaf));
		m_btnBack->move(22, 6);
		m_btnPlay->hide();
		connect(m_btnBack, SIGNAL(clicked()), this, SLOT(slotBackBtnClicked()));

		m_labelChannelName = new QLabel(this);
		if (NULL == m_labelChannelName)
		{
			ret = -1;
			break;
		}

		m_showInfo = new QLabel(this);
		if (NULL == m_showInfo)
		{
			ret = -1;
			break;
		}

		m_showInfoStreamMode = new QLabel(this);

		m_progressBar = new ProgressSlider(Qt::Horizontal, this);
		if (NULL == m_progressBar)
		{
			ret = -1;
			break;
		}
		m_progressBar->setSingleStep(1);
		m_progressBar->setEnabled(false);
		connect(m_progressBar, SIGNAL(sgnProgressSeek(int)), this, SLOT(slotProgressSeek(int)));

		m_decryptKeyBox = new (std::nothrow) MyEditBox(this);
		if (NULL == m_decryptKeyBox)
		{
			ret = -1;
			break;
		}
		ret = m_decryptKeyBox->init(tr(""));
		if (0 != ret)
		{
			break;
		}
		connect(m_decryptKeyBox, SIGNAL(sgnOK(QString)), this, SLOT(slotDecryptKeyBoxOK(QString)));

		m_beginTimeLabel = new QLabel(this);
		if (NULL == m_beginTimeLabel)
		{
			ret = -1;
			break;
		}

		m_endTimeLabel = new QLabel(this);
		if (NULL == m_endTimeLabel)
		{
			ret = -1;
			break;
		}

		m_btnSpeed = new QPushButton(this);
		if (NULL == m_btnSpeed)
		{
			ret = -1;
			break;
		}
		m_btnSpeed->setFixedSize(40, 40);
		m_btnSpeed->setText(QString("%1x").arg(1));
		m_iSpeed = 1;
		m_btnSpeed->setEnabled(false);
		m_isBtnSpeed = false;
		connect(m_btnSpeed, SIGNAL(clicked()), this, SLOT(slotSpeedBtnClicked()));

		m_btnFullScreen = new IconBtn(this, "Skin/real-time video/video_icon_full_screen");
		if (NULL == m_btnFullScreen)
		{
			ret = -1;
			break;
		}
		connect(m_btnFullScreen, SIGNAL(clicked()), this, SLOT(slotFullScreenBtnClicked()));

		m_isInit = true;
	} while (0);

	m_parentWidget = (QMainWindow *)parentWidget()->parentWidget()->parentWidget()->parentWidget();
	refreshLayout();
	return ret;
}

void RecordPlayView::setPosition(const QRect &position)
{
	m_position = position;

	this->setFixedSize(m_position.width(), m_position.height());
	this->move(m_position.left(), m_position.top());
}

void RecordPlayView::setMaximize(bool isMaximize)
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

	refreshLayout();
}

void RecordPlayView::paintEvent(QPaintEvent *paintEvent)
{
	QWidget::paintEvent(paintEvent);

	QPainter painter(this);

	int y = 2;
	painter.fillRect(0, y, this->width(), 42, QColor(0x2c, 0x2d, 0x30));
}

void RecordPlayView::hide()
{
	if (m_isInit)
	{
		/* 隐藏的时候停止播放 */
		stopPlay();
		m_btnPlay->hide();
		m_progressBar->setValue(0);
		m_beginTimeLabel->setText(tr("Begin time"));
		m_beginTimeLabel->setText(tr("End time"));
	}
}

void RecordPlayView::refreshLayout()
{
	if (!m_isInit)
	{
		DLOG("please call init() first!!!\n");
		return;
	}

	QWidget *parent = (QWidget*)this->parent();
	if (parent && !m_isMaximize)
	{
		setPosition(QRect(0, 0, parent->width(), parent->height()));
	}

	m_splitLine->move(0, 0);
	m_splitLine->setFixedWidth(this->width());

	m_splitLine2->move(0, 42 + 42);
	m_splitLine2->setFixedWidth(this->width());

	QPoint pt(2, 2 + 42 + 42);
	m_videoBase->move(pt);
	m_videoBase->setFixedSize(this->width() - 4, this->height() - pt.y() - 50);
	fillBackGroundWithColor(m_videoBase, QColor(0x26, 0x27, 0x2a));

	m_btnPlay->move((this->width() - m_btnPlay->width()) / 2, (this->height() - m_btnPlay->height()) / 2);

	QFont font("Microsoft YaHei", 12);
	m_labelChannelName->setFont(font);
	m_labelChannelName->setStyleSheet("color:#ffffff;");
	m_labelChannelName->setText(m_channelName);
	m_labelChannelName->adjustSize();
	m_labelChannelName->move((this->width() - m_labelChannelName->width()) / 2, 2 + 42 + (42 - m_labelChannelName->height()) / 2);

	QFont fontShowInfo("Microsoft YaHei", 11);
	m_showInfo->setFont(fontShowInfo);
	m_showInfo->setStyleSheet("color:#B0AFAF;");
	m_showInfo->adjustSize();
	m_showInfo->move(this->width() - 16 - m_showInfo->width(), (42 - m_showInfo->height()) / 2);

	m_progressBar->setFixedSize(this->width() - 104 * 2 - 40 - m_btnFullScreen->width(), 10);
	m_progressBar->setStyleSheet(
		"QSlider::groove:horizontal"
		"{"
		"border:0px;"
		"height:4px;"
		"background:rgb(0,0,0);"
		"}"
		"QSlider::sub-page:horizontal"
		"{"
		"background:#fd8b30;"
		"}"
		"QSlider::add-page:horizontal"
		"{"
		"background:#141414;"
		"}"
		"QSlider::handle:horizontal"
		"{"
		"background:white;"
		"width:10px;"
		"border-radius:5px;"
		"margin:-3px 0px -3px 0px;"
		"}"
	);
	m_progressBar->adjustSize();
	m_progressBar->move(104, this->height() - 50 + (50 - m_progressBar->height()) / 2);

	m_beginTimeLabel->setFont(QFont("Microsoft YaHei", 11));
	m_beginTimeLabel->setStyleSheet("color:#929292;");
	m_beginTimeLabel->setText(m_realPlayTime.toString("hh:mm:ss"));
	m_beginTimeLabel->adjustSize();
	m_beginTimeLabel->move(30, this->height() - 50 + (50 - m_beginTimeLabel->height()) / 2);
	m_endTimeLabel->setFont(QFont("Microsoft YaHei", 11));
	m_endTimeLabel->setStyleSheet("color:#929292;");
	m_endTimeLabel->setText(m_endTime.toString("hh:mm:ss"));
	m_endTimeLabel->adjustSize();
	m_endTimeLabel->move(this->width() - m_btnFullScreen->width() - m_btnSpeed->width() - 66, this->height() - 50 + (50 - m_endTimeLabel->height()) / 2);
	m_btnSpeed->setStyleSheet(
		"QPushButton"
		"{"
		"background:transparent;"
		"font:15px;"
		"color:#ffffff;"
		"}"
		"QPushButton::hover"
		"{"
		"color:#fd8b30;"
		"}"
		"QPushButton::disabled"
		"{"
		"color:#929292;"
		"}"
	);
	m_btnSpeed->move(this->width() - m_btnSpeed->width() - m_btnFullScreen->width(), this->height() - 50 + (50 - m_btnSpeed->height()) / 2);
	m_btnFullScreen->move(this->width() - m_btnFullScreen->width(), this->height() - 50 + (50 - m_btnFullScreen->height()) / 2);
}

void RecordPlayView::fillBackGroundWithColor(QWidget *widget, QColor &color)
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

void RecordPlayView::showDeviceRecordPlayView(int deviceIndex, int recordIndex)
{
	if (!m_isInit)
	{
		DLOG("please call init() first!!!\n");
		return;
	}

	//this->show();
	m_recordIndex = recordIndex;
	m_deviceIndex = deviceIndex;
	m_iSpeed = 1;
	m_btnSpeed->setEnabled(false);
	m_isBtnSpeed = false;
	m_btnSpeed->setText(QString("%1x").arg(1));
	m_viewCtrl->setPlayBackSpeed(1);
	m_viewCtrl->setRecordType(DEVICE_RECORD);
	m_viewCtrl->playDeviceRecord(m_deviceIndex, recordIndex);

	/* 刷新通道名称 */
	refreshChannelName();

	/* 刷新视频开始和结束时间 */
	refreshRecordTime();
}

void RecordPlayView::showCloudRecordPlayView(int deviceIndex, int recordIndex)
{
	if (!m_isInit)
	{
		DLOG("please call init() first!!!\n");
		return;
	}

	//this->show();
	m_recordIndex = recordIndex;
	m_deviceIndex = deviceIndex;
	m_iSpeed = 1;
	m_btnSpeed->setEnabled(false);
	m_isBtnSpeed = false;
	m_btnSpeed->setText(QString("%1x").arg(1));
	m_viewCtrl->setPlayBackSpeed(1);
	m_viewCtrl->setRecordType(CLOUD_RECORD);
	m_viewCtrl->playCloudRecord(deviceIndex, recordIndex, NULL);

	/* 刷新通道名称 */
	refreshChannelName();

	/* 刷新视频开始和结束时间 */
	refreshRecordTime();
}

void RecordPlayView::refreshChannelName()
{
	if (!m_isInit)
	{
		DLOG("please call init() first!!!\n");
		return;
	}

	m_channelName = RecordListCtrl::getInstance()->getChannelName();

	/* 设置通道名称 */
	m_labelChannelName->setText(m_channelName);
	m_labelChannelName->adjustSize();
	m_labelChannelName->move((this->width() - m_labelChannelName->width()) / 2, 2 + 42 + (42 - m_labelChannelName->height()) / 2);
}

void RecordPlayView::refreshRecordTime()
{
	if (!m_isInit)
	{
		DLOG("please call init() first!!!\n");
		return;
	}

	m_realPlayTime = m_beginTime;

	m_beginTime = QDateTime::fromString(m_viewCtrl->getRecordBeginTime(), "yyyy-MM-dd hh:mm:ss");
	m_beginTimeLabel->setText(m_beginTime.toString("hh:mm:ss"));
	m_beginTimeLabel->adjustSize();
	m_endTime = QDateTime::fromString(m_viewCtrl->getRecordEndTime(), "yyyy-MM-dd hh:mm:ss");
	m_endTimeLabel->setText(m_endTime.toString("hh:mm:ss"));
	m_endTimeLabel->adjustSize();

	/* 设置进度条的刻度为视频时长(最少1秒) */
	m_progressBar->setMinimum(0);
	m_progressBar->setMaximum(max(1, m_beginTime.secsTo(m_endTime)));
}

void RecordPlayView::stopPlay()
{
	if (!m_isInit)
	{
		DLOG("please call init() first!!!\n");
		return;
	}

	m_viewCtrl->stopPlay();
}

void RecordPlayView::setShowInfo(QString info)
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

void RecordPlayView::onPlayerStatusChanged(int status)
{
	switch (status)
	{
	case STATUS_START:
		m_btnSpeed->setEnabled(true);
	case STATUS_SEEK_SUCCESS:
		m_btnSpeed->setEnabled(true);
	case STATUS_RESUME:
		/* 隐藏重播按钮 */
		m_btnPlay->hide();

		/* 设置进度条可用 */
		m_progressBar->setEnabled(true);

		/* 开启音频 */
		m_viewCtrl->playAudio();

		m_btnSpeed->setEnabled(true);
		m_viewCtrl->setPlayBackSpeed(m_iSpeed);
		break;

	case STATUS_FAIL:
	case STATUS_STOP:
		/* 调用停止播放 */
		stopPlay();
	case STATUS_SEEK_FAILD:
		/* 刷掉videoBase最后一帧 */
		m_videoBase->repaint();
		/* 设置进度条不可用 */
		m_progressBar->setEnabled(false);
		m_btnSpeed->setEnabled(false);
	case STATUS_PAUSE:
		/* 显示重播按钮 */
		m_btnPlay->raise();
		m_btnPlay->show();
		m_btnSpeed->setEnabled(false);
		/* 关闭音频 */
		m_viewCtrl->stopAudio();
	default:
		break;
	}
}

void RecordPlayView::slotBackBtnClicked()
{
	DLOG("slotBackBtnClicked\n");
	setMaximize(false);
	m_iSpeed = 1;
	m_btnSpeed->setText("");
	if (m_isBtnSpeed)
	{
		m_pSpeedMenu->SetCheckedSpeed(m_iSpeed);
	}
	this->hide();
	emit sgnBackToRecordList(m_viewCtrl->getRecordType());
}

void RecordPlayView::slotSpeedBtnClicked()
{
	if (NULL == m_pSpeedMenu)
	{
		m_pSpeedMenu = new PlayBackSpeed(this);
		connect(m_pSpeedMenu, SIGNAL(SignalPlaybackSpeedChanged()), this, SLOT(OnPlaybackSpeedChanged()));
	}

	if (!m_isBtnSpeed)
	{
		m_isBtnSpeed = true;
		m_pSpeedMenu->InitUI(32);
		m_pSpeedMenu->SetCheckedSpeed(m_iSpeed);
		QPoint pBtnBottomTopByGlobal = m_btnSpeed->mapToGlobal(QPoint(0, 0));
		QPoint pBtnRightTopByGlobal = this->mapToGlobal(QPoint(0, 0));
		QPoint pMenuLeftTopByGlobal = QPoint(
			pBtnRightTopByGlobal.x() + this->width() - m_pSpeedMenu->width() - 28,
			pBtnBottomTopByGlobal.y() - m_pSpeedMenu->height() - 10
		);
		m_pSpeedMenu->move(pMenuLeftTopByGlobal);
		m_pSpeedMenu->show();
		m_pSpeedMenu->activateWindow();
	}
	else
	{
		m_isBtnSpeed = false;
		m_pSpeedMenu->hide();
	}
}

void RecordPlayView::OnPlaybackSpeedChanged()
{
	if (NULL == m_pSpeedMenu)
	{
		return;
	}
	int iSpeed = m_pSpeedMenu->GetCheckedSpeed();
	m_isBtnSpeed = false;
	m_iSpeed = iSpeed;
	m_btnSpeed->setText(QString("%1x").arg(iSpeed));
	m_viewCtrl->setPlayBackSpeed(iSpeed);
}

void RecordPlayView::slotPlayerStatusChanged(int status)
{
	QString str;
	switch (status)
	{
	case STATUS_LOADING:
		str = tr("Loading video...");
		break;
	case STATUS_START:
		str = tr("Start play.");
		break;
	case STATUS_STOP:
		str = tr("Record playback finished.");
		/* 修正进度条位置(某些录像最后几秒没有I帧不能播则不会有slotPlayerTime回调,导致进度条没有走到结尾) */
		slotPlayerTime(m_endTime.toTime_t());
		break;
	case STATUS_FAIL:
		str = tr("Play failed!");
		break;
	case STATUS_SEEK_SUCCESS:
		str = tr("Seek succeed.");
		break;
	case STATUS_SEEK_FAILD:
		str = tr("Seek failed!");
		break;
	case STATUS_PAUSE:
		str = tr("Pausing.");
		break;
	case STATUS_RESUME:
		str = tr("Resume.");
		break;
	default:
		str = tr("Unknown status.");
		break;
	}
	setShowInfo(str);

	/* 响应播放状态改变 */
	onPlayerStatusChanged(status);
}

void RecordPlayView::slotPlayerTime(long time)
{
	m_realPlayTime = QDateTime::fromTime_t(time);
	//DLOG("playTime[%s]\n", playTime.toString("yyyy-MM-dd hh:mm:ss").toStdString().c_str());

	/* 设置进度条联动 */
	m_progressBar->setValue(m_beginTime.secsTo(m_realPlayTime));

	/* 设置视频时间联动 */
	m_beginTimeLabel->setText(m_realPlayTime.toString("hh:mm:ss"));
	m_beginTimeLabel->adjustSize();
}

void RecordPlayView::slotPlayerKeyError(int status)
{
	m_decryptKeyBox->setTitle(tr("Please input the key to play"));
	m_decryptKeyBox->show();
}

void RecordPlayView::slotFullScreenBtnClicked()
{
	DLOG("slotFullScreenBtnClicked\n");
	setMaximize(!m_isMaximize);
}

void RecordPlayView::slotProgressSeek(int value)
{
	/* 录像seek */
	if (value <= 0)
	{
		value = 1;
	}

	DLOG("slotProgressSeek[%d]\n", value);
	QDateTime seekTime = QDateTime::fromTime_t(m_beginTime.toTime_t() + value);
	QString toast = QString("seek to ") + seekTime.toString("hh:mm:ss");
	setShowInfo(toast);

	/* 录像seek */
	m_viewCtrl->seek(value);
}

void RecordPlayView::slotPlayBtnClicked()
{
	m_btnPlay->hide();

	if (m_viewCtrl->isPause())
	{
		/* 暂停状态下直接响应resume */
		slotVideoBaseClicked();
		return;
	}

	if (CLOUD_RECORD == m_viewCtrl->getRecordType())
	{
		m_progressBar->setValue(0);
		m_viewCtrl->setPlayBackSpeed(m_iSpeed);
		m_viewCtrl->playCloudRecord(m_deviceIndex, m_recordIndex, NULL);
	}
	else if (DEVICE_RECORD == m_viewCtrl->getRecordType())
	{
		m_progressBar->setValue(0);
		m_viewCtrl->setPlayBackSpeed(m_iSpeed);
		m_viewCtrl->playDeviceRecord(m_deviceIndex, m_recordIndex);
	}
}

void RecordPlayView::slotVideoBaseClicked()
{
	DLOG("slotVideoBaseClicked\n");
	if (!m_viewCtrl->isPlaying())
	{
		return;
	}

	/* 调用以下方法后成功后pause状态会被修改 */
	m_viewCtrl->isPause() ? m_viewCtrl->resume() : m_viewCtrl->pause();
	m_viewCtrl->isPause() ? m_btnPlay->show() : m_btnPlay->hide();
}

void RecordPlayView::slotGetCurrentStreamMode(int streamMode)
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


void RecordPlayView::slotDecryptKeyBoxOK(QString deviceKey)
{
	if (!deviceKey.isEmpty())
	{
		m_viewCtrl->playCloudRecord(m_deviceIndex, m_recordIndex, deviceKey.toStdString().c_str());
	}

	return;
}
