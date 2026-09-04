#ifndef SPLITLINE_H
#define SPLITLINE_H

#include <QWidget>
#include <QLayout>

class SplitLine : public QWidget
{
    Q_OBJECT

public:
    SplitLine(QWidget *parent);
    SplitLine(QWidget *parent, QColor &colorOver, QColor &colorBelow, int height = 2);
    SplitLine(QWidget *parent, QColor &color, int height);
    ~SplitLine();

protected:
    void resizeEvent(QResizeEvent *ev);

private:
    QWidget     *m_topLine;
    QWidget     *m_bottomLine;

    void init();
    /*绘制上下边缘颜色不同的线*/
    void createSplitLine(QColor &colorOver, QColor &colorBelow, int height);

    /*绘制单色的线*/
    void createSplitLine(QColor &color, int height);
};

#endif // SPLITLINE_H
