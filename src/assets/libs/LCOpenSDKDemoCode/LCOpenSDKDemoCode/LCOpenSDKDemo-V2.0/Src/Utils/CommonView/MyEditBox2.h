#ifndef _MYEDITBOX2_H_
#define _MYEDITBOX2_H_

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include "IconBtn.h"
#include "BgColorBtn.h"

class MyEditBox2 : public QDialog
{
    Q_OBJECT

public:
    MyEditBox2(QWidget* parent);
    ~MyEditBox2();
    int init(QString titleText, QString lbl1Text, QString lbl2Text);
    void release();
    void show();

protected:
    /* 为支持窗口可拖动 */
    void mousePressEvent(QMouseEvent* ev);
    void mouseMoveEvent(QMouseEvent* ev);
    void mouseReleaseEvent(QMouseEvent* ev);

signals:
    void sgnOK(QString edit1Text, QString edit2Text);

private slots:
    void slotClose();
    void slotOK();
    void slotCancel();

private:
    QWidget*            m_toolBar;
    QLabel*             m_titleLbl;
    IconBtn*            m_closeBtn;
    QWidget*            m_workBar;
    QLabel*             m_inputLbl1;
    QLabel*             m_inputLbl2;
    QLineEdit*          m_inputEdt1;
    QLineEdit*          m_inputEdt2;
    BgColorBtn*         m_okBtn;
    BgColorBtn*         m_cancelBtn;
    QPoint              m_oldPos;                   /* 鼠标按下去时的位置 */
    bool                m_isMousePressedInToolBar;  /* 鼠标是否在工具栏中被按下 */
};

#endif /* _MYEDITBOX2_H_ */
