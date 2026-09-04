#include <QPainter>
#include "IconOverlapTextBtn.h"

IconOverlapTextBtn::IconOverlapTextBtn(QWidget* parent)
: QLabel(parent)
{
    m_IsMouseEntered = false;
    m_IsMousePressed = false;
    this->setMouseTracking(true);
}

IconOverlapTextBtn::~IconOverlapTextBtn()
{

}

void IconOverlapTextBtn::setBtnAttribute(QSize size, QColor normalBgColor, QColor suspendBgColor, QString text, QColor normalFontColor, QColor suspendFontColor, int fontSize)
{
    m_Size = size;
    m_CircleRect = QRect(m_Size.width() - m_Size.height() - 2, 0, m_Size.height(), m_Size.height());
    m_NormalBgColor = normalBgColor;
    m_SuspendBgColor = suspendBgColor;
    m_Text = text;
    m_NormalFontColor = normalFontColor;
    m_SuspendFontColor = suspendFontColor;
    m_FontSize = fontSize;

    this->resize(m_Size);

    update();
}

void IconOverlapTextBtn::leaveEvent(QEvent* ev)
{
    m_IsMouseEntered = false;
    update();

    return;
}

void IconOverlapTextBtn::mousePressEvent(QMouseEvent* ev)
{
    if (isMouseEntered(ev->pos()))
    {
        if (Qt::LeftButton == ev->button())
        {
            m_IsMousePressed = true;
        }
    }

    return;
}

void IconOverlapTextBtn::mouseReleaseEvent(QMouseEvent* ev)
{
    if (isMouseEntered(ev->pos()))
    {
        if (Qt::LeftButton == ev->button() && m_IsMousePressed)
        {
            emit clicked();
        }
    }

    m_IsMousePressed = false;

    return;
}

void IconOverlapTextBtn::mouseMoveEvent(QMouseEvent* ev)
{
    if (isMouseEntered(ev->pos()))
    {
        m_IsMouseEntered = true;
    } 
    else
    {
        m_IsMouseEntered = false;
    }
    update();

    return;
}

void IconOverlapTextBtn::paintEvent(QPaintEvent* ev)
{
    QPainter painter(this);

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

    return;
}

bool IconOverlapTextBtn::isMouseEntered(QPoint point)
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
