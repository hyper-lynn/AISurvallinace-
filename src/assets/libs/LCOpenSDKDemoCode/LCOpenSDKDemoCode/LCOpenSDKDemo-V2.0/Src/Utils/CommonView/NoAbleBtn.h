#ifndef _NOABLEBTN_H_
#define _NOABLEBTN_H_

#include <QLabel>
#include <QMouseEvent>

class NoAbleBtn : public QLabel
{
    Q_OBJECT

public:
    NoAbleBtn(QWidget* parent);
    ~NoAbleBtn();

    void setBtnAttribute(QSize size, QColor normalBgColor, QColor suspendBgColor, QColor normalFontColor, QColor suspendFontColor, int fontSize);
    void setBtnText(QString text);

    void setNoAbleTime(unsigned int noableTime);

protected:
    /* void enterEvent(QEvent*); */
    void leaveEvent(QEvent*);
    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void paintEvent(QPaintEvent*);
    void timerEvent(QTimerEvent*);

private:
    bool isMouseEntered(QPoint point);

signals:
    void clicked();

private:
    QSize           m_Size;
    QColor          m_NormalBgColor;
    QColor          m_SuspendBgColor;
    QString         m_Text;
    QColor          m_NormalFontColor;
    QColor          m_SuspendFontColor;
    int             m_FontSize;

    QRect           m_CircleRect;
    bool            m_IsMouseEntered;
    bool            m_IsMousePressed;

    int             m_TimeId;
    unsigned int    m_NoAbleTime;
};

#endif /* _NOABLEBTN_H_ */
