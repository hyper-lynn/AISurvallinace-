#ifndef _MYEDITBOX_H_
#define _MYEDITBOX_H_

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include "IconBtn.h"
#include "BgColorBtn.h"

class MyEditBox : public QDialog
{
    Q_OBJECT

public:
    MyEditBox(QWidget* parent);
    ~MyEditBox();
    int init(QString titleText);
    void release();
    void show();
	void setTitle(QString title);

protected:
    /* 为支持窗口可拖动 */
    void mousePressEvent(QMouseEvent* ev);
    void mouseMoveEvent(QMouseEvent* ev);
    void mouseReleaseEvent(QMouseEvent* ev);

signals:
    void sgnOK(QString editText);

private slots:
    void slotClose();
    void slotOK();
    void slotCancel();

private:
    QWidget*            m_toolBar;
    QLabel*             m_titleLbl;
    IconBtn*            m_closeBtn;
    QWidget*            m_workBar;
    QLineEdit*          m_inputEdt;
    BgColorBtn*         m_okBtn;
    BgColorBtn*         m_cancelBtn;
    QPoint              m_oldPos;                   /* 鼠标按下去时的位置 */
    bool                m_isMousePressedInToolBar;  /* 鼠标是否在工具栏中被按下 */
};

#endif /* _MYEDITBOX_H_ */
