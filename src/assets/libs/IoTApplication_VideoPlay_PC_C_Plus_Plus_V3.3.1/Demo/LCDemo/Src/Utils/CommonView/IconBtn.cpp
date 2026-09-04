#include "IconBtn.h"
#include <QMouseEvent>
#include <QBitmap>
#include <QPainter>
#include <QTimer>
#include "Utils/global.h"

IconBtn::IconBtn(QWidget *parent, QString iconPath, unsigned long stateSets)
    : QLabel(parent)
    , m_iconPath(iconPath)
    , m_isEnable(true)
    , m_isIngStatus(false)
    , m_stateSets(stateSets)
    , m_isMouseHover(false)
    , m_isMousePress(false)
    , m_longPressTimer(NULL)
    , m_isLongPress(false)
{
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    m_longPressTimer = new QTimer();
    connect(m_longPressTimer, SIGNAL(timeout()), this, SLOT(longPressTimeOut()));

    m_stateSets |= ICON_STATUS_NORMAL;
    setIconPath(m_iconPath);
}

IconBtn::~IconBtn()
{
    if (m_longPressTimer)
    {
        m_longPressTimer->stop();
        SAFE_DELETE(m_longPressTimer);
    }
}

void IconBtn::setPosition(const QPoint &position)
{
    this->move(position);
}

void IconBtn::setIconPath(const QString &iconPath)
{
    m_iconPath = iconPath;
    refreshIconStatu();
}

void IconBtn::refreshIconStatu()
{
    QPixmap pixmap;
    QString realIconPath = "";
    if (!m_isEnable)
    {
        if (!(m_stateSets & ICON_STATUS_DISABLE))
        {
            return;
        }
        realIconPath = m_iconPath + "_d.png";
    }
    else if (m_isMousePress)
    {
        if (!(m_stateSets & ICON_STATUS_PRESS))
        {
            return;
        }
        realIconPath = m_iconPath + "_h.png";
    }
    else if (m_isIngStatus)
    {
        if (!(m_stateSets & ICON_STATUS_ING))
        {
            return;
        }
        realIconPath = m_iconPath + "_ing.png";
    }
    else if (m_isMouseHover)
    {
        if (!(m_stateSets & ICON_STATUS_HOVER))
        {
            return;
        }
        realIconPath = m_iconPath + "_p.png";
    }
    else
    {
        if (!(m_stateSets & ICON_STATUS_NORMAL))
        {
            return;
        }
        realIconPath = m_iconPath + "_n.png";
    }

    if (!pixmap.load(realIconPath))
    {
        /* 加载图片失败 */
        DLOG("load icon failed>iconPath[%s]\n", realIconPath.toStdString().c_str());
        return;
    }

    /* 设置背景图片 */
    this->setPixmap(pixmap);

    /* 自适应控件大小 */
    this->setFixedSize(pixmap.size());

    /* 根据图片形状设置可见区域以及鼠标响应区域 */
    if (m_stateSets & ICON_TYPE_MASK)
    {
        this->setMask(pixmap.mask());
    }

    /* 已绘制区域不再绘制,仅用于视频播放窗口上悬浮不规则按钮去除黑框 */
    if (m_stateSets & ICON_TYPE_OPAQUEPAINT)
    {
        this->setAttribute(Qt::WA_OpaquePaintEvent, true);
    }
}

void IconBtn::setBtnEnable(bool enable)
{
    m_isEnable = enable;
    refreshIconStatu();
}

void IconBtn::setIngStatus(bool isIng)
{
    m_isIngStatus = isIng;
    refreshIconStatu();
}

void IconBtn::enterEvent(QEvent* ev)
{
    if (!m_isEnable)
    {
        return;
    }

    this->setCursor(QCursor(Qt::PointingHandCursor));

    m_isMouseHover = true;
    refreshIconStatu();

    return;
}

void IconBtn::leaveEvent(QEvent* ev)
{
    this->setCursor(QCursor(Qt::ArrowCursor));

    m_isMouseHover = false;
    m_isMousePress = false;
    refreshIconStatu();

    return;
}

void IconBtn::mousePressEvent(QMouseEvent* ev)
{
    if (!m_isEnable)
    {
        return;
    }

    m_isMousePress = true;
    refreshIconStatu();

    /* 按钮指定响应长按状态 */
    if (m_stateSets & ICON_TYPE_LONGPRESS)
    {
        if (m_longPressTimer->isActive())
        {
            m_longPressTimer->stop();
        }

        /* 按下持续450毫秒判定为长按 */
        m_longPressTimer->setSingleShot(true);
        m_longPressTimer->start(450);
    }

    return;
}

void IconBtn::mouseReleaseEvent(QMouseEvent* ev)
{
    if (!m_isEnable)
    {
        return;
    }

    /* 关闭长按检测定时器 */
    if (m_longPressTimer->isActive())
    {
        m_longPressTimer->stop();
    }

    bool isLongPress = m_isLongPress;
    m_isLongPress = false;
    m_isMousePress = false;
    refreshIconStatu();

    if (Qt::LeftButton == ev->button())
    {
        /* 只处理鼠标在按钮区域弹起 */
        if (this->rect().contains(ev->pos()))
        {
            if (isLongPress)
            {
                /* 长按结束 */
                emit longPressTrigger(false);
            }
            else
            {
                /* 单击 */
                emit clicked();
            }
        }
    }

    return;
}

void IconBtn::longPressTimeOut()
{
    /* 长按触发 */
    m_isLongPress = true;
    emit longPressTrigger(true);
}
