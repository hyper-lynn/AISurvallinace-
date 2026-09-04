#include "BgColorBtn.h"

BgColorBtn::BgColorBtn(QWidget* parent)
: QPushButton(parent)
{

}

BgColorBtn::~BgColorBtn()
{

}

void BgColorBtn::setBtnAttribute(QColor normalBgColor, QColor suspendBgColor, QColor fontColor, unsigned int fontSize)
{
    m_NormalBgColor = normalBgColor;
    m_SuspendBgColor = suspendBgColor;
    m_FontColor = fontColor;
    m_FontSize = fontSize;

    setNormalAttribute();
}

void BgColorBtn::enterEvent(QEvent* ev)
{
    setMouseEnterAttribute();
    this->setCursor(QCursor(Qt::PointingHandCursor));
    return;
}

void BgColorBtn::leaveEvent(QEvent* ev)
{
    setNormalAttribute();
    this->setCursor(QCursor(Qt::ArrowCursor));
    return;
}

void BgColorBtn::setNormalAttribute()
{
    QString styleSheet("");
    styleSheet += QString("background-color:#") + QString::number(m_NormalBgColor.red(), 16) + QString::number(m_NormalBgColor.green(), 16) + QString::number(m_NormalBgColor.blue(), 16) + QString(";");
    styleSheet += QString("color:#") + QString::number(m_FontColor.red(), 16) + QString::number(m_FontColor.green(), 16) + QString::number(m_FontColor.blue(), 16) + QString(";");
    styleSheet += QString("font:") + QString::number(m_FontSize, 10) + QString("pt;");
    styleSheet += QString("font-family:Microsoft YaHei;");
    this->setStyleSheet(styleSheet);
    return;
}

void BgColorBtn::setMouseEnterAttribute()
{
    QString styleSheet("");
    styleSheet += QString("background-color:#") + QString::number(m_SuspendBgColor.red(), 16) + QString::number(m_SuspendBgColor.green(), 16) + QString::number(m_SuspendBgColor.blue(), 16) + QString(";");
    styleSheet += QString("color:#") + QString::number(m_FontColor.red(), 16) + QString::number(m_FontColor.green(), 16) + QString::number(m_FontColor.blue(), 16) + QString(";");
    styleSheet += QString("font:") + QString::number(m_FontSize, 10) + QString("pt;");
    styleSheet += QString("font-family:Microsoft YaHei;");
    this->setStyleSheet(styleSheet);
    return;
}
