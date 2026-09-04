#include <QtGui/QPainter>
#include "NoAbleBtn.h"

NoAbleBtn::NoAbleBtn(QWidget* parent)
: QLabel(parent)
{
    m_IsMouseEntered = false;
    m_IsMousePressed = false;
    m_TimeId = startTimer(1000);
    m_NoAbleTime = 0;
    this->setMouseTracking(true);
}

NoAbleBtn::~NoAbleBtn()
{
    if (0 != m_TimeId)
    {
        killTimer(m_TimeId);
        m_TimeId = 0;
    }
}

void NoAbleBtn::setBtnAttribute(QSize size, QColor normalBgColor, QColor suspendBgColor, QColor normalFontColor, QColor suspendFontColor, int fontSize)
{
    m_Size = size;
    m_CircleRect = QRect(m_Size.width() - m_Size.height() - 2, 0, m_Size.height(), m_Size.height());
    m_NormalBgColor = normalBgColor;
    m_SuspendBgColor = suspendBgColor;
    m_NormalFontColor = normalFontColor;
    m_SuspendFontColor = suspendFontColor;
    m_FontSize = fontSize;
    this->resize(m_Size);
}

void NoAbleBtn::setBtnText(QString text)
{
    m_Text = text;
    update();
}

void NoAbleBtn::setNoAbleTime(unsigned int noableTime)
{
    m_NoAbleTime = noableTime;
    m_Text = tr("Reobtain");
    update();
}

void NoAbleBtn::leaveEvent(QEvent* ev)
{
    m_IsMouseEntered = false;
    update();

    return;
}

void NoAbleBtn::mousePressEvent(QMouseEvent* ev)
{
    if (!m_NoAbleTime)
    {
        if (isMouseEntered(ev->pos()))
        {
            if (Qt::LeftButton == ev->button())
            {
                m_IsMousePressed = true;
            }
        }
    }

    return;
}

void NoAbleBtn::mouseReleaseEvent(QMouseEvent* ev)
{
    if (!m_NoAbleTime)
    {
        if (isMouseEntered(ev->pos()))
        {
            if (Qt::LeftButton == ev->button() && m_IsMousePressed)
            {
                emit clicked();
            }
        }
    }

    m_IsMousePressed = false;

    return;
}

void NoAbleBtn::mouseMoveEvent(QMouseEvent* ev)
{
    if (isMouseEntered(ev->pos()))
    {
        m_IsMouseEntered = true;
    } 
    else
    {
        m_IsMouseEntered = false;
    }

    if (!m_NoAbleTime)
    {
        update();
    }

    return;
}

void NoAbleBtn::paintEvent(QPaintEvent* ev)
{
    QPainter painter(this);

    if (m_NoAbleTime)
    {
        this->setCursor(QCursor(Qt::ArrowCursor));
        painter.setPen(m_NormalBgColor);
        painter.setBrush(m_NormalBgColor);
        painter.drawLine(0, 0, 0, this->height());
        painter.drawRect(2, 0, this->width() - 2 - (this->height() / 2) - 1, this->height() - 1);
        painter.drawPie(m_CircleRect, 0, 1440);
        painter.drawPie(m_CircleRect, 4320, 5760);

        painter.setFont(QFont("Microsoft YaHei",m_FontSize));
        painter.setPen(m_NormalFontColor);
        painter.drawText(rect(), Qt::AlignCenter, tr("Reobtain") + QString("(") + QString::number(m_NoAbleTime, 10) + QString(")"));
    } 
    else
    {
        if (m_IsMouseEntered)
        {
            this->setCursor(QCursor(Qt::PointingHandCursor));
            painter.setPen(m_SuspendBgColor);
            painter.setBrush(m_SuspendBgColor);
        } 
        else
        {
            this->setCursor(QCursor(Qt::ArrowCursor));
            painter.setPen(m_NormalBgColor);
            painter.setBrush(m_NormalBgColor);
        }

        painter.drawLine(0, 0, 0, this->height());
        painter.drawRect(2, 0, this->width() - 2 - (this->height() / 2) - 1, this->height() - 1);
        painter.drawPie(m_CircleRect, 0, 1440);
        painter.drawPie(m_CircleRect, 4320, 5760);

        painter.setFont(QFont("Microsoft YaHei",m_FontSize));
        if (m_IsMouseEntered)
        {
            painter.setPen(m_SuspendFontColor);
        } 
        else
        {
            painter.setPen(m_NormalFontColor);
        }
        painter.drawText(rect(), Qt::AlignCenter, m_Text);
    }

    return;
}

void NoAbleBtn::timerEvent(QTimerEvent* ev)
{
    if (ev->timerId() == m_TimeId)
    {
        if (m_NoAbleTime > 0)
        {
            m_NoAbleTime--;
            update();
        }
    }
}

bool NoAbleBtn::isMouseEntered(QPoint point)
{
    bool ret = false;

    int radius = (m_Size.height() + 1) / 2;
    QRect rect = QRect(2, 0, m_Size.width() - radius - 2, m_Size.height());
    QPoint circleCenter = QPoint(m_Size.width() - radius, radius);
    if (rect.contains(point))
    {
        ret = true;
    }
    else if ((point - circleCenter).manhattanLength() <= radius)
    {
        ret = true;
    }

    return ret;
}
