#ifndef BASESCROLLVIEW_H
#define BASESCROLLVIEW_H

#include <QScrollArea>

class BaseScrollView : public QScrollArea
{
    Q_OBJECT

public:
    BaseScrollView(QWidget *parent);
    virtual ~BaseScrollView();

    QWidget *m_rootWidget;

protected:
    bool m_isInit;

    virtual void resizeEvent(QResizeEvent *);
    virtual void refreshLayout();
    virtual void fillBackGroundWithColor(QWidget *widget,const QColor& color);

private:
    virtual int  init();
    virtual void release();
    virtual void setScrollBarStyle();
};

#endif // BASESCROLLVIEW_H
