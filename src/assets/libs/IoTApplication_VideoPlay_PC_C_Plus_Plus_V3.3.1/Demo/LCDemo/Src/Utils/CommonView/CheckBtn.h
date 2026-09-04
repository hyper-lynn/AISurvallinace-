#ifndef _CHECKBTN_H_
#define _CHECKBTN_H_

#include <QtWidgets/QLabel>
#include <QMouseEvent>

class CheckBtn : public QLabel
{
    Q_OBJECT

public:
    CheckBtn(QWidget* parent);
    ~CheckBtn();

signals:
    void clicked();

protected:
    void enterEvent(QEvent*);
    void leaveEvent(QEvent*);
    void mouseReleaseEvent(QMouseEvent* ev);
};

#endif /* _CHECKBTN_H_ */
