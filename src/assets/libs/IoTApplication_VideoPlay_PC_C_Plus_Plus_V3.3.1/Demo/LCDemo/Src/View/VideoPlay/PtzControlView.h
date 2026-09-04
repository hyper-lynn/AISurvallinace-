#ifndef PTZCONTROLVIEW_H
#define PTZCONTROLVIEW_H

#include <QWidget>

class QLabel;
class IconBtn;
class PtzControlView : public QWidget
{
	Q_OBJECT

public:
	PtzControlView(QWidget *parent);
	~PtzControlView();

    int init();
    void refreshLayout();
    inline void setShowWhole(bool isShowShole){ m_showWhole = isShowShole; refreshLayout(); };
    inline bool isShowWhole(){ return m_showWhole; };

protected:
    virtual void paintEvent(QPaintEvent *ev);

private:
    QLabel      *m_labelTitle;
    IconBtn     *m_btnArrow;
    bool         m_showWhole;
    QLabel      *m_labelShadow;
    QLabel      *m_labelCircle;

    IconBtn     *m_btnUp;
    IconBtn     *m_btnLeft;
    IconBtn     *m_btnDown;
    IconBtn     *m_btnRight;
    IconBtn     *m_btnLeftUp;
    IconBtn     *m_btnLeftDown;
    IconBtn     *m_btnRightUp;
    IconBtn     *m_btnRightDown;


private slots:
    void slotArrowClicked();

    void slotPtzUpClicked();
    void slotPtzLeftClicked();
    void slotPtzDownClicked();
    void slotPtzRightClicked();
    void slotPtzLeftUpClicked();
    void slotPtzLeftDownClicked();
    void slotPtzRightUpClicked();
    void slotPtzRightDownClicked();

    void slotPtzUpLongPress(bool isPress);
    void slotPtzLeftLongPress(bool isPress);
    void slotPtzDownLongPress(bool isPress);
    void slotPtzRightLongPress(bool isPress);
    void slotPtzLeftUpLongPress(bool isPress);
    void slotPtzLeftDownLongPress(bool isPress);
    void slotPtzRightUpLongPress(bool isPress);
    void slotPtzRightDownLongPress(bool isPress);

signals:
    void sgnShowWhole(bool isWhole);
    void sgnPtzControl(int ptzCtrl, int ptzCtrlType);
};

#endif // PTZCONTROLVIEW_H
