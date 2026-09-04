#ifndef RECORDPLAYVIEW_H
#define RECORDPLAYVIEW_H

#include <QWidget>
#include <QDateTime>
#include <QMainWindow>
#include <QDesktopWidget>
#include <QApplication>
#include "Src/Utils/CommonView/MyEditBox.h"

class RecordPlayCtrl;
class QLabel;
class IconTextBtn;
class ProgressSlider;
class IconBtn;
class BaseWidget;
class SplitLine;
class PlayBackSpeed;
class QPushButton;
class RecordPlayView : public QWidget
{
	Q_OBJECT

public:
	RecordPlayView(QWidget *parent);
	~RecordPlayView();

	int init();
	void refreshLayout();

	void setPosition(const QRect &position);
	QRect getPosition() { return m_position; };

	/**
	* 显示设备录像播放页
	* @param   [in] int deviceIndex 设备index，由录像列表提供
	* @param   [in] int recordIndex 录像index，由录像列表提供
	* @return  void
	*/
	void showDeviceRecordPlayView(int deviceIndex, int recordIndex);

	/**
	* 显示云录像播放页
	* @param   [in] int deviceIndex 设备index，由录像列表提供
	* @param   [in] int recordIndex 录像index，由录像列表提供
	* @return  void
	*/
	void showCloudRecordPlayView(int deviceIndex, int recordIndex);

	virtual void hide();

protected:
	virtual void paintEvent(QPaintEvent *paintEvent);

private:
	QMainWindow    *m_parentWidget;  //保存父窗口 用于还原
	bool            m_isInit;
	QRect           m_position;
	BaseWidget     *m_videoBase;
	RecordPlayCtrl *m_viewCtrl;
	QLabel         *m_labelChannelName;
	IconTextBtn    *m_btnBack;
	int             m_recordIndex;
	int             m_deviceIndex;

	SplitLine      *m_splitLine;
	SplitLine      *m_splitLine2;
	ProgressSlider *m_progressBar;
	QLabel         *m_beginTimeLabel;
	QLabel         *m_endTimeLabel;
	IconBtn        *m_btnFullScreen;
	IconBtn        *m_btnPlay;
	QPushButton    *m_btnSpeed;
	PlayBackSpeed  *m_pSpeedMenu;
	bool            m_isMaximize;
	bool            m_isBtnSpeed;

	QDateTime       m_beginTime;
	QDateTime       m_endTime;
	QDateTime       m_realPlayTime;
	QString         m_channelName;
	int             m_iSpeed;

	MyEditBox*      m_decryptKeyBox;

	QLabel  *m_showInfo;
	QLabel  *m_showInfoStreamMode;

	/*私有化show方法,外部只能通过showDeviceRecordPlayView && showCloudRecordPlayView 显示界面*/
	inline virtual void show() { QWidget::show(); };

	void fillBackGroundWithColor(QWidget *widget, QColor& color);
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
	void slotSpeedBtnClicked();
	void OnPlaybackSpeedChanged();
	void slotPlayerStatusChanged(int status);
	void slotPlayerTime(long time);
	void slotFullScreenBtnClicked();
	void slotPlayerKeyError(int status);
	/**
	* 进度条被拖动
	* @param   [in] int value 拖动后的位置
	* @return  void
	*/
	void slotProgressSeek(int value);

	void slotPlayBtnClicked();
	void slotVideoBaseClicked();
	void slotDecryptKeyBoxOK(QString deviceKey);

	void slotGetCurrentStreamMode(int streamMode);
};

#endif // RECORDPLAYVIEW_H
