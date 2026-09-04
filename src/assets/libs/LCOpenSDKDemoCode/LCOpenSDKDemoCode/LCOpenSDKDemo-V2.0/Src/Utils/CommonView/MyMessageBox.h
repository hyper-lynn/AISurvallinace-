#ifndef _MYMESSAGEBOX_H_
#define _MYMESSAGEBOX_H_

#include <QDialog>
#include <QLabel>
#include "IconBtn.h"
#include "BgColorBtn.h"

class MyMessageBox : public QDialog
{
    Q_OBJECT

public:
    enum RetCode { Rejected, Accepted };
    static RetCode warning(QWidget* parent, QString title, QString text);

private:
    MyMessageBox(QWidget* parent);
    ~MyMessageBox();
    int init(QString title, QString text);
    void release();

    /* 为支持窗口可拖动 */
    void mousePressEvent(QMouseEvent* ev);
    void mouseMoveEvent(QMouseEvent* ev);
    void mouseReleaseEvent(QMouseEvent* ev);

private slots:
    void slotClose();

private:
    QWidget*            m_toolBar;
    QLabel*             m_titleLbl;
    IconBtn*            m_closeBtn;
    QWidget*            m_workBar;
    QLabel*             m_textLbl;
    BgColorBtn*         m_okBtn;
    BgColorBtn*         m_cancelBtn;
    QPoint              m_oldPos;                   /* 鼠标按下去时的位置 */
    bool                m_isMousePressedInToolBar;  /* 鼠标是否在工具栏中被按下 */
};

#endif /* _MYMESSAGEBOX_H_ */
