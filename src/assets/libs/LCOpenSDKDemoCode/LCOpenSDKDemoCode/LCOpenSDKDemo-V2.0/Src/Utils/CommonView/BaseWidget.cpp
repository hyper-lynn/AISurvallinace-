#include <QMouseEvent>
#include "Src/Utils/global.h"
#include "BaseWidget.h"

BaseWidget::BaseWidget(QWidget *parent)
    : QLabel(parent)
{

}

BaseWidget::~BaseWidget()
{

}

void BaseWidget::enterEvent(QEvent* ev)
{
    /*通知鼠标进入*/
    emit sgnMouseEvent(this, true);
}

void BaseWidget::leaveEvent(QEvent* ev)
{
    QPoint pos = this->mapFromGlobal(QCursor::pos());
    if (!this->rect().contains(pos))
    {
        /*通知鼠标离开*/
        emit sgnMouseEvent(this, false);
    }
}

void BaseWidget::mouseReleaseEvent(QMouseEvent* ev)
{
    if (Qt::LeftButton == ev->button())
    {
        /*通知窗口被点击*/
        emit sgnClicked();
    }
}
