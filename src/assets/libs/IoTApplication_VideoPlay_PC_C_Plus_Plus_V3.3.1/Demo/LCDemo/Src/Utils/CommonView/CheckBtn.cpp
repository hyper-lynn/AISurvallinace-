#include "CheckBtn.h"

CheckBtn::CheckBtn(QWidget* parent)
:QLabel(parent)
{

}

CheckBtn::~CheckBtn()
{

}

void CheckBtn::enterEvent(QEvent* ev)
{
    this->setCursor(QCursor(Qt::PointingHandCursor));
}

void CheckBtn::leaveEvent(QEvent* ev)
{
    this->setCursor(QCursor(Qt::ArrowCursor));
}

void CheckBtn::mouseReleaseEvent(QMouseEvent* ev)
{
    if (!rect().contains(ev->pos()))
    {
        return;
    }

    if (Qt::LeftButton == ev->button())
    {
        emit clicked();
    }

    return;
}
