#ifndef _ICONOVERLAPTEXTBTN_H_
#define _ICONOVERLAPTEXTBTN_H_

#include <QLabel>
#include <QMouseEvent>

class IconOverlapTextBtn : public QLabel
{
    Q_OBJECT

public:
    IconOverlapTextBtn(QWidget* parent);
    ~IconOverlapTextBtn();

    void setBtnAttribute(QSize size, QColor normalBgColor, QColor suspendBgColor, QString text, QColor normalFontColor, QColor suspendFontColor, int fontSize);

protected:
    /* void enterEvent(QEvent*); */
    void leaveEvent(QEvent*);
    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void paintEvent(QPaintEvent*);

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
};

#endif /* _ICONOVERLAPTEXTBTN_H_ */
