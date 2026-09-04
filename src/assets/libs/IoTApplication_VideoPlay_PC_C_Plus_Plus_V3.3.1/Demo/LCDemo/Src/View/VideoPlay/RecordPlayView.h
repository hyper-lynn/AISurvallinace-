#ifndef RECORDPLAYVIEW_H
#define RECORDPLAYVIEW_H

#include <QWidget>
#include <QDateTime>
#include <QPushButton>

class RecordPlayCtrl;
class QLabel;
class IconTextBtn;
class ProgressSlider;
class IconBtn;
class BaseWidget;
class SplitLine;
class RecordPlayView : public QWidget
{
    Q_OBJECT

public:
    RecordPlayView(QWidget *parent);
    ~RecordPlayView();

    int init();
    void refreshLayout();

    void setPosition(const QRect &position);
    QRect getPosition(){ return m_position; };

    /**
    * 显示设备录像播放页
    * @param   [in] int recordIndex 录像index，由录像列表提供
    * @return  void
    */
    void showDeviceRecordPlayView(int deviceIndex, int recordIndex);

    /**
    * 显示云录像播放页
    * @param   [in] int recordIndex 录像index，由录像列表提供
    * @return  void
    */
    void showCloudRecordPlayView(int deviceIndex, int recordIndex);

    virtual void hide();

protected:
    virtual void paintEvent(QPaintEvent *paintEvent);

private:
    bool            m_isInit;
    QRect           m_position;
    BaseWidget     *m_videoBase;
    RecordPlayCtrl *m_viewCtrl;
    QLabel         *m_labelChannelName;
    IconTextBtn    *m_btnBack;
    int             m_recordIndex;
	int				m_deviceIndex;

    SplitLine      *m_splitLine;
    SplitLine      *m_splitLine2;
    ProgressSlider *m_progressBar;
    QLabel         *m_beginTimeLabel;
    QLabel         *m_endTimeLabel;
    IconBtn        *m_btnFullScreen;
    IconBtn        *m_btnPlay;
	QPushButton    *m_btnSpeedPlay;
	int             m_speedIndex;
    bool            m_isMaximize;

    QDateTime       m_beginTime;
    QDateTime       m_endTime;
    QDateTime       m_realPlayTime;
    QString         m_channelName;

    QLabel  *m_showInfo;
    QLabel  *m_streamModeLabel;

    /*私有化show方法,外部只能通过showDeviceRecordPlayView && showCloudRecordPlayView 显示界面*/
    inline virtual void show(){ QWidget::show(); };

    void fillBackGroundWithColor(QWidget *widget, const QColor& color);
    void stopPlay();

    void setShowInfo(QString info);
    void refreshChannelName();
    void refreshRecordTime();
    void setMaximize(bool isMaximize);

    /**
    * 响应播放状态变化
    * @param   [in] int status
    * @return  void
    */
    void onPlayerStatusChanged(int status);

signals:
    void sgnBackToRecordList(int recordType);

private slots:
    void slotBackBtnClicked();
    void slotPlayerStatusChanged(int status);
    void slotPlayerTime(long time);
    void slotFullScreenBtnClicked();
    
    /**
    * 进度条被拖动
    * @param   [in] int value 拖动后的位置
    * @return  void
    */
    void slotProgressSeek(int value);

    void slotPlayBtnClicked();
    void slotVideoBaseClicked();
	void slotSpeedPlayBtnClicked();
    void slotStreamModeChanged(QString mode);
};

#endif // RECORDPLAYVIEW_H
