#ifndef BASEWIDGET_H
#define BASEWIDGET_H

#include <QLabel>

class BaseWidget : public QLabel
{
    Q_OBJECT

public:
    BaseWidget(QWidget *parent);
    ~BaseWidget();

protected:
    void enterEvent(QEvent* ev);
    void leaveEvent(QEvent* ev);
    void mouseReleaseEvent(QMouseEvent* ev);

private:

signals:
    void sgnMouseEvent(void *widget, bool isEnter);
    void sgnClicked();
    
};

#endif // BASEWIDGET_H
