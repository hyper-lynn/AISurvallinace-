#include <QMouseEvent>
#include <QPainter>

#include "ProgressSlider.h"

ProgressSlider::ProgressSlider(Qt::Orientation orientation, QWidget *parent)
    : QSlider(orientation, parent)
{

}

ProgressSlider::~ProgressSlider()
{
}

void ProgressSlider::mouseReleaseEvent(QMouseEvent *ev)
{
    if (ev->button() & Qt::LeftButton && this->isEnabled())
    {
        int dur = this->maximum() - this->minimum();
        int pos = this->minimum() + dur * ev->x() / this->width();
        /* 录像回放seek功能优化，保证seek到末尾有2秒I帧间隔 */
        if (dur <= 2)
        {
            pos = 0;
        } 
        else if (pos + 2 > this->maximum())
        {
            pos = this->maximum() - 2;
        }

        if (pos != this->sliderPosition())
        {
            /* 点击拖动 */
            this->setValue(pos);
            emit sgnProgressSeek(pos);
        }
    }
}

void ProgressSlider::mousePressEvent(QMouseEvent *ev)
{
    return;
}

void ProgressSlider::enterEvent(QEvent* ev)
{
    if (this->isEnabled())
    {
        this->setCursor(QCursor(Qt::PointingHandCursor));
    }
}

void ProgressSlider::leaveEvent(QEvent* ev)
{
    this->setCursor(QCursor(Qt::ArrowCursor));
}

