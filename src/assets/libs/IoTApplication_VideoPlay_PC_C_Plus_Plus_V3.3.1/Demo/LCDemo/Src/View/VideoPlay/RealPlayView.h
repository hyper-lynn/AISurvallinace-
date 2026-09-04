#ifndef REALPLAYVIEW_H
#define REALPLAYVIEW_H

#include <QWidget>
#include <QTimer>
#include "Model/PtzControlInfo.h"

class RealPlayCtrl;
class IconTextBtn;
class IconBtn;
class QLabel;
class PtzControlView;
class SplitLine;

/* Clickable overlay widget for sleep countdown - handles mouse click to wake device */
class SleepOverlay : public QWidget
{
    Q_OBJECT
public:
    explicit SleepOverlay(QWidget *parent = NULL) : QWidget(parent) {}
signals:
    void clicked();
protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
};

class RealPlayView : public QWidget
{
	Q_OBJECT

public:
	RealPlayView(QWidget *parent);
	~RealPlayView();

    int init();
    void refreshLayout();
    inline QRect getPosition(){ return m_position; };

    
    /**
    * 显示实时预览界面
    * @param   [in] int deviceIndex     设备index, 设备列表界面传入
    * @param   [in] int definitionMode  清晰度(0高清，1标清, 默认高清)
    * @return  void
    */
    void showRealPlayView(int deviceIndex, int definitionMode = 0);
	void stopAllPlay();
    virtual void hide();

protected:
    virtual void paintEvent(QPaintEvent *);

    /* 私有化show方法,只能通过showRealPlayView显示界面 */
    inline virtual void show(){ QWidget::show(); };

private:
    QRect         m_position;
    QWidget      *m_videoBase;
    RealPlayCtrl *m_viewCtrl;
    int           m_deviceIndex;
    int           m_definitionMode;
    bool          m_isInit;
    bool          m_isMaximize;
    PtzControlView *m_ptzControlView;

    SplitLine    *m_splitLine;
    IconTextBtn  *m_btnBack;
    IconBtn      *m_btnSnap;
    IconBtn      *m_btnRecord;
    IconBtn      *m_btnTalk;
    IconBtn      *m_btnDefinition;
    IconBtn      *m_btnAudio;
    IconBtn      *m_btnFullScreen;

    QLabel       *m_showInfo;
    QLabel       *m_streamModeLabel;

    /* Low-power device sleep countdown overlay */
    SleepOverlay *m_sleepOverlay;
    QLabel       *m_sleepCountdownLabel;
    QTimer       *m_sleepCountdownTimer;
    int           m_sleepCountdownSeconds;
    bool          m_isSleepCountdownActive;

    void setPosition(const QRect &position);
    void fillBackGroundWithColor(QWidget *widget, const QColor& color);

    /* 控制播放窗口最大化 */
    void setMaximize(bool isMaximize);

    /* 停止播放 */
    void stopPlay();

    void setShowInfo(QString info);

    /* 响应播放状态更改，执行相应操作 */
    void onPlayerStatusChanged(int status);

    /* 响应对讲状态更改, 执行相应操作 */
    void onTalkerStatusChanged(int status);

signals:
    void sgnReturnToDevicesList(bool refreshDevicesList);

private slots:
    void slotBackBtnClicked();
    void slotSnapBtnClicked();
    void slotRecordBtnClicked();
    void slotDefinitionBtnClicked();
    void slotTalkBtnClicked();
    void slotAudioBtnClicked();
    void slotFullScreenBtnClicked();

    void slotPlayerStatusChanged(int status);
    void slotRecorderStatusChanged(int status);
    void slotTalkerStatusChanged(int status);

    void slotPtzViewState(bool isShow);
    void slotPtzControl(int ptzCtrl, int ptzCtrlType);
    void slotStreamModeChanged(QString mode);
    void slotSleepCountdown(int seconds);
    void slotSleepCountdownTick();
    void slotDeviceSleeping();
    void slotSleepOverlayClicked();
};

#endif // REALPLAYVIEW_H
