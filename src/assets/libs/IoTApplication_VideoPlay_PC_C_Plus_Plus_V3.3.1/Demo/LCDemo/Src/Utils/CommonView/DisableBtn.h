#ifndef _DISABLEBTN_H_
#define _DISABLEBTN_H_

#include <QtWidgets/QLabel>
#include <QMouseEvent>

class DisableBtn : public QLabel
{
    Q_OBJECT

public:
    DisableBtn(QWidget* parent);
    ~DisableBtn();

    void setBtnAttribute(QSize size, QColor normalBgColor, QColor suspendBgColor, QColor normalFontColor, QColor suspendFontColor, int fontSize);
    void setBtnText(QString text);

    void setDisableTime(unsigned int disableTime);

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
    unsigned int    m_DisableTime;
};

#endif /* _DISABLEBTN_H_ */
