#ifndef _ICONTEXTBTN_H_
#define _ICONTEXTBTN_H_

#include <QLabel>
#include <QMouseEvent>

class IconTextBtn : public QLabel
{
    Q_OBJECT

public:
    IconTextBtn(QWidget* parent);
    ~IconTextBtn();

    /* 对于iconPath，若完整路径为common_icon_add_n.png，只传入common_icon_add */
    /* textSize单位为pt */
    void setBtnAttribute(QString iconPath, QString text, unsigned int fontSize, QColor fontColor, QString fontStyle = "Microsoft YaHei");

protected:
    void enterEvent(QEvent*);
    void leaveEvent(QEvent*);
    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);

signals:
    void clicked();

private:
    int init();
    void release();

private:
    QLabel*     m_IconLabel;
    QLabel*     m_TextLabel;
    QString     m_IconPath;
};

#endif /* _ICONTEXTBTN_H_ */
