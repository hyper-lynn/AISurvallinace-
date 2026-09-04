#include <QPainter>
#include <QLabel>

#include "Utils/global.h"
#include "Ctrl/RecordPlayCtrl.h"
#include "Ctrl/RecordListCtrl.h"
#include "Utils/CommonView/IconTextBtn.h"
#include "Utils/CommonView/ProgressSlider.h"
#include "Utils/CommonView/IconBtn.h"
#include "Utils/CommonView/BaseWidget.h"
#include "Utils/CommonView/SplitLine.h"
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
    , m_streamModeLabel(NULL)
    , m_progressBar(NULL)
    , m_beginTimeLabel(NULL)
    , m_endTimeLabel(NULL)
    , m_btnFullScreen(NULL)
	, m_btnSpeedPlay(NULL)
	, m_speedIndex(0)
    , m_isMaximize(false)
    , m_channelName(tr("Channel name"))
    , m_splitLine(NULL)
    , m_splitLine2(NULL)
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
    SAFE_DELETE(m_streamModeLabel);
    SAFE_DELETE(m_progressBar);
    SAFE_DELETE(m_beginTimeLabel);
    SAFE_DELETE(m_endTimeLabel);
    SAFE_DELETE(m_btnFullScreen);
	SAFE_DELETE(m_btnSpeedPlay);
    SAFE_DELETE(m_splitLine);
    SAFE_DELETE(m_splitLine2)
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
        connect(m_viewCtrl, SIGNAL(sgnStreamModeChanged(QString)), this, SLOT(slotStreamModeChanged(QString)));

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

        m_btnPlay = new IconBtn(m_videoBase, "Skin/common_icon_btn_play", ICON_TYPE_MASK | ICON_TYPE_OPAQUEPAINT);
        if (NULL == m_btnPlay)
        {
            ret = -1;
            break;
        }
        m_btnPlay->hide();
        m_btnPlay->raise();
        connect(m_btnPlay, SIGNAL(clicked()), this, SLOT(slotPlayBtnClicked()));

        m_btnBack = new IconTextBtn(this);
        if (NULL == m_btnBack)
        {
            ret = -1;
            break;
        }
        m_btnBack->setBtnAttribute("Skin/common_icon_back", "Back to Records List", 11, QColor(0xb0, 0xaf, 0xaf));
        m_btnBack->move(22, 6);
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

        m_streamModeLabel = new QLabel(this);
        if (NULL == m_streamModeLabel)
        {
            ret = -1;
            break;
        }
        m_streamModeLabel->hide();

        m_progressBar = new ProgressSlider(Qt::Horizontal, this);
        if (NULL == m_progressBar)
        {
            ret = -1;
            break;
        }
        m_progressBar->setSingleStep(1);
        m_progressBar->setEnabled(false);
        connect(m_progressBar, SIGNAL(sgnProgressSeek(int)), this, SLOT(slotProgressSeek(int)));

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

        m_btnFullScreen = new IconBtn(this, "Skin/real-time vedio/video_icon_full_screen");
        if (NULL == m_btnFullScreen)
        {
            ret = -1;
            break;
        }
        connect(m_btnFullScreen, SIGNAL(clicked()), this, SLOT(slotFullScreenBtnClicked()));

        m_btnSpeedPlay = new QPushButton("1x", this);
        if (NULL == m_btnSpeedPlay)
        {
            ret = -1;
            break;
        }
        m_btnSpeedPlay->setFixedSize(40, 26);
        m_btnSpeedPlay->setCursor(Qt::PointingHandCursor);
        m_btnSpeedPlay->setStyleSheet(
            "QPushButton {"
                "background-color:#2a2d32;"
                "color:#d0d0d0;"
                "font:10pt;"
                "font-family:Microsoft YaHei;"
                "border:1px solid #3a3d42;"
                "border-radius:3px;"
            "}"
            "QPushButton:hover {"
                "background-color:#3a3d42;"
                "border:1px solid #fd8b30;"
            "}"
            "QPushButton:pressed {"
                "background-color:#fd8b30;"
                "color:#ffffff;"
            "}"
        );
        connect(m_btnSpeedPlay, &QPushButton::clicked, this, &RecordPlayView::slotSpeedPlayBtnClicked);

        m_isInit = true;
    }while(0);

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
    QWidget::hide();

    if(m_isInit)
    {
        /* Stop playback when hidden */
        stopPlay();
        m_btnPlay->hide();
        m_progressBar->setValue(0);
        /*m_beginTimeLabel->setText(tr("Begin time"));
        m_beginTimeLabel->setText(tr("End time"));*/
		m_beginTimeLabel->setText("Begin time");
		m_beginTimeLabel->setText("End time");
		m_speedIndex = 0;
		if (m_btnSpeedPlay) m_btnSpeedPlay->setText("1x");
        if (m_streamModeLabel) m_streamModeLabel->hide();
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

    /* Stream mode label at top-left of video */
    if (m_streamModeLabel)
    {
        m_streamModeLabel->move(m_videoBase->x() + 8, m_videoBase->y() + 6);
        m_streamModeLabel->raise();
    }

    m_btnPlay->move((m_videoBase->width() - m_btnPlay->width()) / 2, (m_videoBase->height() - m_btnPlay->height()) / 2);

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

    m_progressBar->setFixedSize(this->width() - 150*2 - 40 - m_btnFullScreen->width(), 10);
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
    m_progressBar->move(150, this->height() - 50 + (50 - m_progressBar->height()) / 2);

    m_beginTimeLabel->setFont(QFont("Microsoft YaHei", 11));
    m_beginTimeLabel->setStyleSheet("color:#929292;");
    m_beginTimeLabel->setText(m_realPlayTime.toString("hh:mm:ss"));
    m_beginTimeLabel->adjustSize();
    m_beginTimeLabel->move(30, this->height() - 50 + (50 - m_beginTimeLabel->height()) / 2);

    m_endTimeLabel->setFont(QFont("Microsoft YaHei", 11));
    m_endTimeLabel->setStyleSheet("color:#929292;");
    m_endTimeLabel->setText(m_endTime.toString("hh:mm:ss"));
    m_endTimeLabel->adjustSize();
    m_endTimeLabel->move(this->width() - 76 - 40 - m_btnFullScreen->width(), this->height() - 50 + (50 - m_endTimeLabel->height()) / 2);

    m_btnFullScreen->move(this->width() - 40 - m_btnFullScreen->width(), this->height() - 50 + (50 - m_btnFullScreen->height()) / 2);

    m_btnSpeedPlay->move(m_btnFullScreen->x() - 8 - m_btnSpeedPlay->width(), this->height() - 50 - m_btnSpeedPlay->height() - 4);
}

void RecordPlayView::fillBackGroundWithColor(QWidget *widget,  const QColor &color)
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

void RecordPlayView::showDeviceRecordPlayView(int deviceIndex, int recordIndex)
{
    if (!m_isInit)
    {
        DLOG("please call init() first!!!\n");
        return;
    }

    this->show();
    m_recordIndex = recordIndex;
	m_deviceIndex = deviceIndex;
    m_viewCtrl->setRecordType(DEVICE_RECORD);
    m_viewCtrl->playDeviceRecord(deviceIndex, recordIndex);

    /* Reset playback speed */
    m_speedIndex = 0;
    m_btnSpeedPlay->setText("1x");

    /* Refresh channel name */
    refreshChannelName();

    /* Refresh video start and end time */
    refreshRecordTime();
}

void RecordPlayView::showCloudRecordPlayView(int deviceIndex, int recordIndex)
{
    if (!m_isInit)
    {
        DLOG("please call init() first!!!\n");
        return;
    }

    this->show();
    m_recordIndex = recordIndex;
	m_deviceIndex = deviceIndex;
    m_viewCtrl->setRecordType(CLOUD_RECORD);
    m_viewCtrl->playCloudRecord(deviceIndex, recordIndex);

    /* Reset playback speed */
    m_speedIndex = 0;
    m_btnSpeedPlay->setText("1x");

    /* Refresh channel name */
    refreshChannelName();

    /* Refresh video start and end time */
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

    /* Set channel name */
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

    /* Set progress bar scale to video duration (minimum 1 second) */
    m_progressBar->setMinimum(0);
    qint64 range = m_beginTime.secsTo(m_endTime);
    m_progressBar->setMaximum((1 > range ? 1 : range));
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

    //m_showInfo->setText(tr("Status>>>") + info);
	m_showInfo->setText("Status>>>" + info);
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
    case STATUS_SEEK_SUCCESS:
    case STATUS_RESUME:
        /* Hide replay button */
        m_btnPlay->hide();

        /* Enable progress bar */
        m_progressBar->setEnabled(true);

        /* Open audio */
        m_viewCtrl->playAudio();
        break;
    case STATUS_FAIL:
    case STATUS_STOP:
        /* Stop playback */
        stopPlay();
        if (m_streamModeLabel) m_streamModeLabel->hide();
    case STATUS_SEEK_FAILD:
        /* Refresh last frame of videoBase */
        m_videoBase->repaint();
        /* Disable progress bar */
        m_progressBar->setEnabled(false);
    case STATUS_PAUSE:
        /* Show replay button */
        m_btnPlay->show();
        /* Close audio */
        m_viewCtrl->stopAudio();
    default:
        break;
    }
}

void RecordPlayView::slotBackBtnClicked()
{
    DLOG("slotBackBtnClicked\n");
    setMaximize(false);

    this->hide();
    emit sgnBackToRecordList(m_viewCtrl->getRecordType());
}

void RecordPlayView::slotPlayerStatusChanged(int status)
{
    QString str;
    switch (status)
    {
    case STATUS_LOADING:
        str = "Loading video...";
        break;
    case STATUS_START:
        str = "Start play.";
        break;
    case STATUS_STOP:
        str = "Record playback finished.";
        /* Fix progress bar position: some recordings have no I-frames in last seconds, no slotPlayerTime callback, progress bar won't reach end */
        slotPlayerTime(m_endTime.toTime_t());
        break;
    case STATUS_FAIL:
        str = "Play failed!";
        break;
    case STATUS_SEEK_SUCCESS:
        str = "Seek succeed.";
        break;
    case STATUS_SEEK_FAILD:
        str = "Seek failed!";
        break;
    case STATUS_PAUSE:
        str = "Pausing.";
        break;
    case STATUS_RESUME:
        str = "Resume.";
        break;
	case STATUS_SPEEDPLAY:
		str = QString("Speed: %1x").arg(m_btnSpeedPlay->text());
    default:
        str = "Unknown status.";
        break;
    }
    setShowInfo(str);

    /* Respond to playback status change */
    onPlayerStatusChanged(status);
}

void RecordPlayView::slotPlayerTime(long time)
{
    m_realPlayTime = QDateTime::fromTime_t(time);
    //DLOG("playTime[%s]\n", playTime.toString("yyyy-MM-dd hh:mm:ss").toStdString().c_str());

    /* Set progress bar linkage */
    m_progressBar->setValue(m_beginTime.secsTo(m_realPlayTime));

    /* Set video time linkage */
    m_beginTimeLabel->setText(m_realPlayTime.toString("hh:mm:ss"));
    m_beginTimeLabel->adjustSize();
}

void RecordPlayView::slotFullScreenBtnClicked()
{
    DLOG("slotFullScreenBtnClicked\n");
    setMaximize(!m_isMaximize);
}

void RecordPlayView::slotProgressSeek(int value)
{
    DLOG("slotProgressSeek[%d]\n", value);
    QDateTime seekTime = QDateTime::fromTime_t(m_beginTime.toTime_t() + value);
    QString toast = QString("seek to ") + seekTime.toString("hh:mm:ss");
    setShowInfo(toast);

    /* Record seek */
    m_viewCtrl->seek(value);
}

void RecordPlayView::slotPlayBtnClicked()
{
    m_btnPlay->hide();

    if (m_viewCtrl->isPause())
    {
        /* In paused state, directly respond with resume */
        slotVideoBaseClicked();
        return;
    }

    if (CLOUD_RECORD == m_viewCtrl->getRecordType())
    {
        m_progressBar->setValue(0);
        m_viewCtrl->playCloudRecord(m_deviceIndex, m_recordIndex);
    }
    else if (DEVICE_RECORD == m_viewCtrl->getRecordType())
    {
        m_progressBar->setValue(0);
        m_viewCtrl->playDeviceRecord(m_deviceIndex, m_recordIndex);
    }
}

void RecordPlayView::slotSpeedPlayBtnClicked()
{
	if (!m_viewCtrl->isPlaying())
	{
		return;
	}

	static const float speeds[] = { 1.0f, 2.0f, 4.0f };
	static const char* labels[] = { "1x", "2x", "4x" };
	m_speedIndex = (m_speedIndex + 1) % 3;

	m_viewCtrl->setPlaySpeed(speeds[m_speedIndex]);
	m_btnSpeedPlay->setText(labels[m_speedIndex]);
}

void RecordPlayView::slotVideoBaseClicked()
{
    DLOG("slotVideoBaseClicked\n");
    if (!m_viewCtrl->isPlaying())
    {
        return;
    }

    /* After calling the following method, pause status will be modified on success */
    m_viewCtrl->isPause() ? m_viewCtrl->resume() : m_viewCtrl->pause();
    m_viewCtrl->isPause() ? m_btnPlay->show() : m_btnPlay->hide();
}

void RecordPlayView::slotStreamModeChanged(QString mode)
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
