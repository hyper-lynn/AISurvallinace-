#include "RoundRectTextBtn.h"

RoundRectTextBtn::RoundRectTextBtn(QWidget* parent)
: QLabel(parent)
{
    m_IsMousePressed = false;
}

RoundRectTextBtn::~RoundRectTextBtn()
{

}

void RoundRectTextBtn::setBtnAttribute(QString backgroundIconPath, QColor normalFontColor, QColor suspendFontColor, int fontSize)
{
    m_BackgroundIconPath = backgroundIconPath;
    m_NormalFontColor = normalFontColor;
    m_SuspendFontColor = suspendFontColor;
    m_FontSize = fontSize;

    this->setAlignment(Qt::AlignCenter);

    QPixmap pixmap;
    pixmap.load(m_BackgroundIconPath + QString("_n.png"));
    this->resize(pixmap.size());

    this->setNormalAttribute();

    return;
}

void RoundRectTextBtn::enterEvent(QEvent* ev)
{
    this->setSuspendAttribute();
    this->setCursor(QCursor(Qt::PointingHandCursor));
    return;
}

void RoundRectTextBtn::leaveEvent(QEvent* ev)
{
    this->setNormalAttribute();
    this->setCursor(QCursor(Qt::ArrowCursor));
    return;
}

void RoundRectTextBtn::mousePressEvent(QMouseEvent* ev)
{
    if (Qt::LeftButton == ev->button())
    {
        m_IsMousePressed = true;
    }
    return;
}

void RoundRectTextBtn::mouseReleaseEvent(QMouseEvent* ev)
{
    if (rect().contains(ev->pos()))
    {
        if (Qt::LeftButton == ev->button() && m_IsMousePressed)
        {
            emit clicked();
        }
    }
    m_IsMousePressed = false;
    return;
}

void RoundRectTextBtn::setNormalAttribute()
{
    QPixmap pixmap;
    pixmap.load(m_BackgroundIconPath + QString("_n.png"));
    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    this->setPalette(palette);

    QString styleSheet;
    styleSheet += QString("color:#") + QString::number(m_NormalFontColor.red(), 16) + QString::number(m_NormalFontColor.green(), 16) + QString::number(m_NormalFontColor.blue(), 16) + QString(";");
    styleSheet += QString("font:") + QString::number(m_FontSize, 10) + QString("pt;");
    styleSheet += QString("font-family:Microsoft YaHei;");
    this->setStyleSheet(styleSheet);

    return;
}

void RoundRectTextBtn::setSuspendAttribute()
{
    QPixmap pixmap;
    pixmap.load(m_BackgroundIconPath + QString("_p.png"));
    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    this->setPalette(palette);

    QString styleSheet;
    styleSheet += QString("color:#") + QString::number(m_SuspendFontColor.red(), 16) + QString::number(m_SuspendFontColor.green(), 16) + QString::number(m_SuspendFontColor.blue(), 16) + QString(";");
    styleSheet += QString("font:") + QString::number(m_FontSize, 10) + QString("pt;");
    styleSheet += QString("font-family:Microsoft YaHei;");
    this->setStyleSheet(styleSheet);

    return;
}
