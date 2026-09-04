#ifndef _ROUNDRECTTEXTBTN_H_
#define _ROUNDRECTTEXTBTN_H_

#include <QLabel>
#include <QMouseEvent>

class RoundRectTextBtn : public QLabel
{
    Q_OBJECT

public:
    RoundRectTextBtn(QWidget* parent);
    ~RoundRectTextBtn();

    void setBtnAttribute(QString backgroundIconPath, QColor normalFontColor, QColor suspendFontColor, int fontSize);

protected:
    void enterEvent(QEvent*);
    void leaveEvent(QEvent*);
    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);

private:
    void setNormalAttribute();
    void setSuspendAttribute();

signals:
    void clicked();

private:
    QString         m_BackgroundIconPath;
    QColor          m_NormalFontColor;
    QColor          m_SuspendFontColor;
    int             m_FontSize;

    bool            m_IsMousePressed;
};

#endif /* _ROUNDRECTTEXTBTN_H_ */
