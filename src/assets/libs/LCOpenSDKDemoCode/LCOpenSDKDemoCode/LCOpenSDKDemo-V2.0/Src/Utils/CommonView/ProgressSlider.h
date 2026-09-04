#ifndef PROGRESSSLIDER_H
#define PROGRESSSLIDER_H

#include <QSlider>

class ProgressSlider : public QSlider
{
    Q_OBJECT

public:
    ProgressSlider(Qt::Orientation orientation, QWidget *parent);
    ~ProgressSlider();

protected:
    virtual void mouseReleaseEvent(QMouseEvent *ev);
    virtual void mousePressEvent(QMouseEvent *ev);
    virtual void enterEvent(QEvent* ev);
    virtual void leaveEvent(QEvent* ev);

private:

signals:
    void sgnProgressSeek(int value);
};

#endif // PROGRESSSLIDER_H
