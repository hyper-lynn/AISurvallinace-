#ifndef _BGCOLORBTN_H_
#define _BGCOLORBTN_H_

#include <QPushButton>
#include <QMouseEvent>

class BgColorBtn : public QPushButton
{
    Q_OBJECT

public:
    BgColorBtn(QWidget* parent);
    ~BgColorBtn();

    void setBtnAttribute(QColor normalBgColor, QColor suspendBgColor, QColor fontColor, unsigned int fontSize);

protected:
    void enterEvent(QEvent*);
    void leaveEvent(QEvent*);

private:
    void setNormalAttribute();
    void setMouseEnterAttribute();

private:
    QColor          m_NormalBgColor;
    QColor          m_SuspendBgColor;
    QColor          m_FontColor;
    unsigned int    m_FontSize;
};

#endif /* _BGCOLORBTN_H_ */
