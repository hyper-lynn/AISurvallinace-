#include "Src/Utils/CommonView/MyMessageBox.h"
#include "AlarmMsgView.h"

AlarmMsgView::AlarmMsgView(QWidget* parent)
:QWidget(parent)
{
    m_alarmMsgIndex         = -1;
    m_alarmSmallPicLbl      = NULL;
    m_labelArea             = NULL;
    m_alarmTimeNameLbl      = NULL;
    m_alarmTimeLbl          = NULL;
    m_removeAlarmMsgBtn     = NULL;
}

AlarmMsgView::~AlarmMsgView()
{
    release();
}

int AlarmMsgView::init()
{
    int ret = 0;

    do 
    {
        this->resize(230, 168);
        this->move(0, 0);

        m_alarmSmallPicLbl = new (std::nothrow) QLabel(this);
        if (NULL == m_alarmSmallPicLbl)
        {
            ret = -1;
            break;
        }
        m_alarmSmallPicLbl->resize(230, 132);
        m_alarmSmallPicLbl->move(0, 0);
        m_alarmSmallPicLbl->setScaledContents(true);
        m_alarmSmallPicLbl->installEventFilter(this);

        m_labelArea = new (std::nothrow) QWidget(this);
        if (NULL == m_labelArea)
        {
            ret = -1;
            break;
        }
        m_labelArea->resize(this->width(), 36);
        m_labelArea->move(0, 132);
        m_labelArea->setStyleSheet("background-color:#2c2d30;");

        m_alarmTimeNameLbl = new (std::nothrow) QLabel(m_labelArea);
        if (NULL == m_alarmTimeNameLbl)
        {
            ret = -1;
            break;
        }
        m_alarmTimeNameLbl->setFixedHeight(18);
        m_alarmTimeNameLbl->move(5, 9);
        m_alarmTimeNameLbl->setStyleSheet("color:#e2e2e2;font:9pt;font-family:Microsoft YaHei;");
        m_alarmTimeNameLbl->setText(tr("Alarm Time : "));
        m_alarmTimeNameLbl->adjustSize();

        m_alarmTimeLbl = new (std::nothrow) QLabel(m_labelArea);
        if (NULL == m_alarmTimeLbl)
        {
            ret = -1;
            break;
        }
        m_alarmTimeLbl->resize(220 - m_alarmTimeNameLbl->width(), 18);
        m_alarmTimeLbl->move(4 + m_alarmTimeNameLbl->width(), 9);
        m_alarmTimeLbl->setStyleSheet("color:#a4a4a5;font:9pt;font-family:Microsoft YaHei;");

        m_removeAlarmMsgBtn = new (std::nothrow) IconBtn(m_labelArea, "Skin/devicelist_icon_delete");
        if (NULL == m_removeAlarmMsgBtn)
        {
            ret = -1;
            break;
        }
        m_removeAlarmMsgBtn->move(196, 3);
        connect(m_removeAlarmMsgBtn, SIGNAL(clicked()), this, SLOT(slotRemoveAlarmMsg()));

    } while (0);

    if (0 != ret)
    {
        release();
    }

    return ret;
}

void AlarmMsgView::release()
{
    if (NULL != m_removeAlarmMsgBtn)
    {
        delete m_removeAlarmMsgBtn;
        m_removeAlarmMsgBtn = NULL;
    }

    if (NULL != m_alarmTimeLbl)
    {
        delete m_alarmTimeLbl;
        m_alarmTimeLbl = NULL;
    }

    if (NULL != m_alarmTimeNameLbl)
    {
        delete m_alarmTimeNameLbl;
        m_alarmTimeNameLbl = NULL;
    }

    if (NULL != m_labelArea)
    {
        delete m_labelArea;
        m_labelArea = NULL;
    }

    if (NULL != m_alarmSmallPicLbl)
    {
        delete m_alarmSmallPicLbl;
        m_alarmSmallPicLbl = NULL;
    }

    return;
}

void AlarmMsgView::setAlarmMsgIndex(int alarmMsgIndex)
{
    m_alarmMsgIndex = alarmMsgIndex;
}

void AlarmMsgView::setAlarmMsgSmallPic(const QPixmap& alarmMsgSmallPic)
{
    m_alarmSmallPicLbl->setPixmap(alarmMsgSmallPic);
}

void AlarmMsgView::setAlarmTime(const QString& alarmTime)
{
    m_alarmTimeLbl->setText(alarmTime);
}

void AlarmMsgView::setAlarmMsgBigPic(const QPixmap& alarmMsgBigPic)
{
    m_alarmMsgBigPic = alarmMsgBigPic;
}

const QPixmap& AlarmMsgView::getAlarmMsgBigPic()
{
    return m_alarmMsgBigPic;
}

bool AlarmMsgView::eventFilter(QObject* watched, QEvent* ev)
{
    if (watched == m_alarmSmallPicLbl)
    {
        if (QEvent::MouseButtonDblClick == ev->type())
        {
            emit sgnAlarmSmallPicLblDblClicked(m_alarmMsgIndex);
        }
    }
    return QWidget::eventFilter(watched, ev);
}

void AlarmMsgView::slotRemoveAlarmMsg()
{
    if (MyMessageBox::Accepted == MyMessageBox::warning(this, tr("Prompt"), tr("Be Sure to Delete This Alarm Message?")))
    {
        emit sgnRemoveAlarmMsg(m_alarmMsgIndex);
    }
    return;
}
