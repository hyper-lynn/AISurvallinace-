#include <QPainter>
#include <QMouseEvent>

#include "Utils/global.h"
#include "Ctrl/RealPlayCtrl.h"
#include "Utils/CommonView/IconTextBtn.h"
#include "Utils/CommonView/IconBtn.h"
#include "Utils/CommonView/SplitLine.h"
#include "View/VideoPlay/PtzControlView.h"

#include "RealPlayView.h"

/* SleepOverlay mouse click handler */
void SleepOverlay::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        emit clicked();
    }
    QWidget::mousePressEvent(event);
}

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
    , m_streamModeLabel(NULL)
    , m_definitionMode(0)
    , m_ptzControlView(NULL)
    , m_splitLine(NULL)
    , m_sleepOverlay(NULL)
    , m_sleepCountdownLabel(NULL)
    , m_sleepCountdownTimer(NULL)
    , m_sleepCountdownSeconds(0)
    , m_isSleepCountdownActive(false)
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
    SAFE_DELETE(m_streamModeLabel);
    SAFE_DELETE(m_ptzControlView);
    SAFE_DELETE(m_splitLine);
    SAFE_DELETE(m_sleepCountdownTimer);
    SAFE_DELETE(m_sleepCountdownLabel);
    SAFE_DELETE(m_sleepOverlay);
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
        connect(m_viewCtrl, SIGNAL(sgnStreamModeChanged(QString)), this, SLOT(slotStreamModeChanged(QString)));
        connect(m_viewCtrl, SIGNAL(sgnSleepCountdown(int)), this, SLOT(slotSleepCountdown(int)));
        connect(m_viewCtrl, SIGNAL(sgnDeviceSleeping()), this, SLOT(slotDeviceSleeping()));

        m_showInfo = new QLabel(this);
        if (NULL == m_showInfo)
        {
            ret = -1;
            break;
        }

        m_streamModeLabel = new QLabel(this);
        if (NULL == m_streamModeLabel)
        {
            ret = -1;
            break;
        }
        m_streamModeLabel->hide();

        m_splitLine = new SplitLine(this, QColor(0xfd, 0x8b, 0x30), 1);
        if (NULL == m_splitLine)
        {
            ret = -1;
            break;
        }

        m_btnBack = new IconTextBtn(this);
        m_btnSnap = new IconBtn(this, "Skin/real-time vedio/video_icon_screenshot", ICON_STATUS_DEFAULT | ICON_STATUS_DISABLE);
        m_btnRecord = new IconBtn(this, "Skin/real-time vedio/video_icon_takevideo", ICON_STATUS_DEFAULT | ICON_STATUS_DISABLE | ICON_STATUS_ING);
        m_btnTalk = new IconBtn(this, "Skin/real-time vedio/video_icon_speak", ICON_STATUS_DEFAULT | ICON_STATUS_DISABLE | ICON_STATUS_ING);
        m_btnDefinition = new IconBtn(this, "Skin/real-time vedio/video_hd", ICON_STATUS_DEFAULT | ICON_STATUS_DISABLE);
        m_btnAudio = new IconBtn(this, "Skin/real-time vedio/video_sound_off", ICON_STATUS_DEFAULT | ICON_STATUS_DISABLE);
        m_btnFullScreen = new IconBtn(this, "Skin/real-time vedio/video_icon_full_screen");

        if (NULL == m_btnBack || NULL == m_btnSnap || NULL == m_btnRecord
          ||NULL == m_btnTalk || NULL == m_btnDefinition || NULL == m_btnAudio
          ||NULL == m_btnFullScreen)
        {
            ret = -1;
            break;
        }

        //m_btnBack->setBtnAttribute("Skin/common_icon_back", tr("Back to Devices List"), 11, QColor(0xb0, 0xaf, 0xaf));
		m_btnBack->setBtnAttribute("Skin/common_icon_back", "Back to Devices List", 11, QColor(0xb0, 0xaf, 0xaf));
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

        /* Create semi-transparent sleep countdown overlay (clickable to wake device) */
        m_sleepOverlay = new SleepOverlay(this);
        if (NULL == m_sleepOverlay)
        {
            ret = -1;
            break;
        }
        m_sleepOverlay->setAttribute(Qt::WA_TranslucentBackground, true);
        m_sleepOverlay->setStyleSheet("background-color: rgba(0, 0, 0, 128);");
        m_sleepOverlay->setCursor(Qt::PointingHandCursor);
        m_sleepOverlay->hide();
        connect(m_sleepOverlay, SIGNAL(clicked()), this, SLOT(slotSleepOverlayClicked()));

        m_sleepCountdownLabel = new QLabel(m_sleepOverlay);
        if (NULL == m_sleepCountdownLabel)
        {
            ret = -1;
            break;
        }
        m_sleepCountdownLabel->setAlignment(Qt::AlignCenter);
        m_sleepCountdownLabel->setStyleSheet(
            "QLabel {"
                "color: #ffffff;"
                "font: 36pt 'Microsoft YaHei';"
                "background-color: transparent;"
            "}"
        );
        m_sleepCountdownLabel->hide();

        m_sleepCountdownTimer = new QTimer(this);
        if (NULL == m_sleepCountdownTimer)
        {
            ret = -1;
            break;
        }
        m_sleepCountdownTimer->setInterval(1000);
        connect(m_sleepCountdownTimer, SIGNAL(timeout()), this, SLOT(slotSleepCountdownTick()));

        m_isInit = true;
    } while (0);

    /* Set buttons default enabled */
    onPlayerStatusChanged(STATUS_STOP);

    /* Adjust layout */
    refreshLayout();
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
    QWidget::hide();

    if (m_isInit)
    {
        stopPlay();
        onPlayerStatusChanged(STATUS_STOP);

        /* Stop sleep countdown and hide overlay */
        if (m_sleepCountdownTimer) m_sleepCountdownTimer->stop();
        if (m_sleepOverlay) m_sleepOverlay->hide();
        m_isSleepCountdownActive = false;
    };
}

void RealPlayView::refreshLayout()
{
    if (!m_isInit)
    {
        DLOG("please call init() first!!!\n");
        return;
    }

    /* Adjust widget layout */
    QWidget *parent = (QWidget*)this->parent();
    if (parent && !m_isMaximize)
    {
        setPosition(QRect(0, 0, parent->width(), parent->height()));
    }

    QPoint pt(2, 42 + 2);
    m_videoBase->move(pt);
    m_videoBase->setFixedSize(this->width() - 4, this->height() - pt.y() - 64);
    fillBackGroundWithColor(m_videoBase, QColor(0, 0, 0));

    /* Adjust sleep overlay to cover the entire video area */
    if (m_sleepOverlay)
    {
        m_sleepOverlay->setGeometry(m_videoBase->x(), m_videoBase->y(), m_videoBase->width(), m_videoBase->height());
        if (m_sleepCountdownLabel)
        {
            m_sleepCountdownLabel->setGeometry(0, 0, m_sleepOverlay->width(), m_sleepOverlay->height());
        }
    }

    /* Stream mode label at top-left of video */
    if (m_streamModeLabel)
    {
        m_streamModeLabel->move(m_videoBase->x() + 8, m_videoBase->y() + 6);
        m_streamModeLabel->raise();
    }

    /* Separator */
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

    /* Adjust PTZ window layout based on visibility */
    if (m_ptzControlView->isShowWhole())
    {
        m_ptzControlView->move(this->width() - m_ptzControlView->width(), this->height() - 209);
    }
    else
    {
        m_ptzControlView->move(this->width() - m_ptzControlView->width(), this->height() - 64 + (64 - 32) / 2);
    }
}

void RealPlayView::fillBackGroundWithColor(QWidget *widget, const QColor& color)
{
    if (NULL == widget)
    {
        return;
    }

    widget->setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Window, color);
    widget->setPalette(palette);
}

void RealPlayView::paintEvent(QPaintEvent *paintEvent)
{
    QWidget::paintEvent(paintEvent);

    QPainter painter(this);

    /* Draw separator and background for PTZ control area */
    painter.setPen(QPen(QBrush(QColor(0x1a, 0x1a, 0x1a)), 1));
    painter.drawLine(this->width()-247, this->height()-64, this->width()-247, this->height());
    painter.fillRect(this->width()-246, this->height()-64, 246, 42, QColor(0x2d, 0x2e, 0x31));
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
    show();
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
        /* Audio auto-enabled in onPlayBegan callback, update audio icon */
        m_btnAudio->setIconPath("Skin/real-time vedio/video_sound_on");
        break;
    case STATUS_LOADING:
        break;
    default:
        m_viewCtrl->setTalkStatusBak(false);
        isBtnEnable = false;
        if (m_streamModeLabel) m_streamModeLabel->hide();
        break;
    }

    /* Adjust button enabled state */
    m_btnSnap->setBtnEnable(isBtnEnable);
    m_btnRecord->setBtnEnable(isBtnEnable);
    m_btnDefinition->setBtnEnable(isBtnEnable);
    m_btnTalk->setBtnEnable(isBtnEnable);
    m_btnAudio->setBtnEnable(isBtnEnable);
    if (isBtnEnable)
    {
        m_btnDefinition->setIconPath("Skin/real-time vedio/video_" + (m_definitionMode == 0 ? QString("hd") : QString("sd")));
    }
    else
    {
        m_btnAudio->setIconPath("Skin/real-time vedio/video_sound_off");
        m_btnTalk->setIngStatus(false);
        m_btnRecord->setIngStatus(false);
    }

    /* Resume talk status after playback starts */
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
    /* Modify talk button status (prevent repeated clicks while talking) */
    m_btnTalk->setBtnEnable(STATUS_LOADING != status);
    m_btnTalk->setIngStatus(STATUS_START == status);

    /* Audio button disabled during talk */
    m_btnAudio->setBtnEnable(status != STATUS_START);

    /* On talk start: audio closed, icon off; On talk stop: audio restored, icon on */
    if (STATUS_START == status)
    {
        m_btnAudio->setIconPath("Skin/real-time vedio/video_sound_off");
    }
    else if (STATUS_STOP == status)
    {
        m_btnAudio->setIconPath("Skin/real-time vedio/video_sound_on");
    }
}

void RealPlayView::setShowInfo(QString info)
{
    if (!m_isInit)
    {
        DLOG("please call init() first!!!\n");
        return;
    }

    //m_showInfo->setText(tr("Status>>>") + info);
	m_showInfo->setText("Status>>>" + info);

    m_showInfo->adjustSize();
    m_showInfo->show();
    //m_showInfo->repaint();

    m_showInfo->move(this->width() - 16 - m_showInfo->width(), m_showInfo->y());
}

void RealPlayView::setMaximize(bool isMaximize)
{
    m_isMaximize = isMaximize;

    //setShowInfo(m_isMaximize ? tr("Full screen.") : tr("Normal window."));
	setShowInfo(m_isMaximize ? "Full screen." : "Normal window.");
    if (m_isMaximize)
    {
        this->setWindowFlags(Qt::Window);
        this->showFullScreen();

        m_btnFullScreen->setIconPath("Skin/real-time vedio/video_icon_exitfull_screen");
    }
    else
    {
        this->setWindowFlags(Qt::SubWindow);
        this->showNormal();

        m_btnFullScreen->setIconPath("Skin/real-time vedio/video_icon_full_screen");
    }

    /* Re-adjust layout on maximize or restore */
    refreshLayout();
}

void RealPlayView::slotBackBtnClicked()
{
    DLOG("slotBackBtnClicked\n");
    m_ptzControlView->setShowWhole(false);
    setMaximize(false);

    this->hide();
    /* Return to device list */
    emit sgnReturnToDevicesList(false);
}

void RealPlayView::slotSnapBtnClicked()
{
    DLOG("slotSnapBtnClicked\n");

    int ret = m_viewCtrl->snapShot();
    //setShowInfo(0 == ret ? tr("Snapshot succeed.") : tr("Snapshot failed!"));
	setShowInfo(0 == ret ? "Snapshot succeed." : "Snapshot failed!");
}

void RealPlayView::slotRecordBtnClicked()
{
    DLOG("slotRecordBtnClicked\n");

    if (m_viewCtrl->isRecording())
    {
        m_viewCtrl->stopRecord();
        m_btnRecord->setIngStatus(false);

        //setShowInfo(tr("Stop recording."));
		setShowInfo("Stop recording.");
    }
    else
    {
        m_viewCtrl->startRecord();
        m_btnRecord->setIngStatus(true);

        //setShowInfo(tr("Start recording."));
		setShowInfo("Start recording.");
    }
}

void RealPlayView::slotDefinitionBtnClicked()
{
    DLOG("slotDefinitionBtnClicked\n");

    /* Backup talk status */
    m_viewCtrl->setTalkStatusBak(m_viewCtrl->isTalking());

    /* HD/SD switch, param 2 controls definition (0=HD, 1=SD) */
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
        m_btnAudio->setIconPath("Skin/real-time vedio/video_sound_off");

        //setShowInfo(tr("Close audio."));
		setShowInfo("Close audio.");
    }
    else
    {
        m_viewCtrl->playAudio();
        m_btnAudio->setIconPath("Skin/real-time vedio/video_sound_on");

        //setShowInfo(tr("Open audio."));
		setShowInfo("Open audio.");
    }
}

void RealPlayView::slotFullScreenBtnClicked()
{
    DLOG("slotFullScreenBtnClicked\n");

    /* Toggle window maximize or restore */
    setMaximize(!m_isMaximize);
}

void RealPlayView::slotPlayerStatusChanged(int status)
{
    QString str;
    switch (status)
    {
    case STATUS_LOADING:
        //str = tr("Loading video...");
		str = "Loading video...";
        break;
    case STATUS_START:
        //str = tr("Start play") + QString("[") + (m_definitionMode == 0 ? tr("HD") : tr("SD")) + QString("].");
		//str = "Start play" + QString("[") + (m_definitionMode == 0 ? "HD" : "SD") + QString("].");
		str = "Start play" + QString("[") + (m_definitionMode == 0 ? ("HD") : ("SD")) + QString("].");
        break;
    case STATUS_STOP:
        //str = tr("Stop play.");
		str = "Stop play.";
        break;
    case STATUS_FAIL:
        //str = tr("Play failed!");
		str = "Play failed!";
        break;
    }
    setShowInfo(str);

    /* Respond to playback status update */
    onPlayerStatusChanged(status);
}

void RealPlayView::slotRecorderStatusChanged(int status)
{
    if (STATUS_STOP == status)
    {
        m_btnRecord->setIngStatus(false);
        //setShowInfo(tr("Stop recording."));
		setShowInfo("Stop recording.");
    }
}

void RealPlayView::slotTalkerStatusChanged(int status)
{
    QString str;
    switch (status)
    {
    case STATUS_LOADING:
        //str = tr("Starting to talk...");
		str = "Starting to talk...";
        break;
    case STATUS_START:
        //str = tr("Talk start.");
		str = "Talk start.";
        break;
    case STATUS_STOP:
        //str = tr("Talk stop.");
		str = "Talk stop.";
        break;
    case STATUS_FAIL:
        //str = tr("Talk failed!");
		str = "Talk failed!";
        break;
    }
    setShowInfo(str);

    /* Respond to talk status update */
    onTalkerStatusChanged(status);
}

void RealPlayView::slotPtzViewState(bool isShow)
{
    /* Re-layout when PTZ window is shown or hidden */
    refreshLayout();
}

void RealPlayView::slotPtzControl(int ptzCtrl, int ptzCtrlType)
{
    int ret = m_viewCtrl->ptzControlAsyn((PTZ_CONTROL_DIRECTION_E)ptzCtrl, (PTZ_CTRL_TYPE_E)ptzCtrlType);
    if (0 == ret)
    {
        //setShowInfo(tr("PTZing..."));
		setShowInfo("PTZing...");
		DLOG("RealPlayView::slotPtzControl ret success !\n");
    }
    else
    {
        if (-2 == ret)
        {
            //setShowInfo(tr("PTZ isn't allowed unless real video is playing!"));
			setShowInfo("PTZ isn't allowed unless real video is playing!");
        }
        else if (-3 == ret)
        {
            //setShowInfo(tr("The device has no PTZ ability!"));
			setShowInfo("The device has no PTZ ability!");
        }
        else
        {
            //setShowInfo(tr("PTZ failed") + QString("[") + QString::number(ret) + QString("]!"));
			setShowInfo("PTZ failed" + QString("[") + QString::number(ret) + QString("]!"));
        }
    }
}

void RealPlayView::stopAllPlay()
{
	if (m_viewCtrl)
	{
		m_viewCtrl->stopPlay();
	}
}

void RealPlayView::slotStreamModeChanged(QString mode)
{
    if (m_streamModeLabel)
    {
        m_streamModeLabel->setText(mode);
        m_streamModeLabel->setStyleSheet(
            "QLabel {"
                "background-color:rgba(0,0,0,160);"
                "color:#ffffff;"
                "font:10pt 'Microsoft YaHei';"
                "padding:2px 8px;"
                "border-radius:3px;"
            "}"
        );
        m_streamModeLabel->adjustSize();
        m_streamModeLabel->show();
        m_streamModeLabel->raise();
    }
}

void RealPlayView::slotSleepCountdown(int seconds)
{
    if (!m_sleepOverlay || !m_sleepCountdownLabel || !m_sleepCountdownTimer)
    {
        return;
    }

    DLOG("slotSleepCountdown: %d seconds\n", seconds);

    /* Stop previous countdown if running */
    m_sleepCountdownTimer->stop();

    m_sleepCountdownSeconds = seconds;
    m_isSleepCountdownActive = true;

    /* Update countdown text and show overlay */
    m_sleepCountdownLabel->setText(QString("Device will sleep in\n%1 s\n\nClick to wake device").arg(m_sleepCountdownSeconds));
    m_sleepCountdownLabel->setGeometry(0, 0, m_sleepOverlay->width(), m_sleepOverlay->height());
    m_sleepCountdownLabel->show();
    m_sleepOverlay->raise();
    m_sleepOverlay->show();

    /* Start 1-second tick timer */
    m_sleepCountdownTimer->start();
}

void RealPlayView::slotSleepCountdownTick()
{
    if (!m_sleepOverlay || !m_sleepCountdownLabel || !m_sleepCountdownTimer)
    {
        return;
    }

    m_sleepCountdownSeconds--;

    if (m_sleepCountdownSeconds <= 0)
    {
        /* Countdown finished, stop timer and hide overlay */
        m_sleepCountdownTimer->stop();
        m_sleepOverlay->hide();

        /* Stop playback and return to device list */
        slotBackBtnClicked();
        return;
    }

    /* Update countdown text */
    m_sleepCountdownLabel->setText(QString("Device will sleep in\n%1 s\n\nClick to wake device").arg(m_sleepCountdownSeconds));
}

void RealPlayView::slotDeviceSleeping()
{
    if (!m_sleepOverlay || !m_sleepCountdownLabel || !m_sleepCountdownTimer)
    {
        return;
    }

    DLOG("slotDeviceSleeping: device is about to enter sleep\n");

    /* Stop any running countdown */
    m_sleepCountdownTimer->stop();

    /* Show overlay with sleep hint for 1 second */
    m_sleepCountdownLabel->setText("Device is entering sleep mode");
    m_sleepCountdownLabel->setGeometry(0, 0, m_sleepOverlay->width(), m_sleepOverlay->height());
    m_sleepCountdownLabel->show();
    m_sleepOverlay->raise();
    m_sleepOverlay->show();

    /* Stop playback and return to device list after 2 seconds */
    QTimer::singleShot(2000, this, SLOT(slotBackBtnClicked()));
}

void RealPlayView::slotSleepOverlayClicked()
{
    if (!m_isSleepCountdownActive)
    {
        return;
    }

    DLOG("slotSleepOverlayClicked: attempting to wake device\n");

    int ret = m_viewCtrl->rewake();
    if (0 == ret)
    {
        DLOG("rewake success, stopping countdown\n");
        /* Wake successful, stop countdown and hide overlay */
        m_sleepCountdownTimer->stop();
        m_sleepOverlay->hide();
        m_isSleepCountdownActive = false;
        setShowInfo("Device wake-up succeed.");
    }
    else
    {
        DLOG("rewake failed: %d\n", ret);
        setShowInfo("Device wake-up failed!");
    }
}

