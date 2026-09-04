#ifndef RECORDLISTVIEW_H
#define RECORDLISTVIEW_H

#include <QWidget>
#include <QDate>
#include "Src/Model/RecordInfo.h"
#include "lcopensdk_download/LCOpenSDK_Download.h"
#include "lcopensdk_download/LCOpenSDK_DownloadListener.h"
class RecordListCtrl;
class IconTextBtn;
class RecordListScrollView;
class QLabel;
class SearchBar;
class Calendar;
class SplitLine;
class RecordListView : public QWidget, public LCOpenSDK_DownloadListener
{
	Q_OBJECT

public:
	RecordListView(QWidget *parent);
	~RecordListView();

	int init();
	void refreshLayout();
	inline QRect getPosition() { return m_position; };
	inline int getDeviceIndex() { return m_deviceIndex; };

	/**
	* 显示设备录像列表界面
	* @param   [in] int deviceIndex 设备index，由设备列表页提供
	* @return  void
	*/
	void showDeviceRecordListView(int deviceIndex);

	/**
	* 显示云录像列表界面
	* @param   [in] int deviceIndex 设备index，由设备列表页提供
	* @return  void
	*/
	void showCloudRecordListView(int deviceIndex);

	void hide();

	void onDownloadReceiveData(int index, int datalen);
	void onDownloadState(int index, const char* code, int type);
	void slotDownloadError(int status);
protected:
	virtual void paintEvent(QPaintEvent *paintEvent);

private:
	QRect           m_position;
	RecordListCtrl *m_viewCtrl;
	bool            m_isInit;
	QString         m_deviceId;
	int             m_channelId;
	RECORD_TYPE_E   m_recordType;
	int             m_deviceIndex;
	int             m_nstate;
	SplitLine              *m_splitLine;
	SplitLine              *m_splitLine2;
	IconTextBtn            *m_btnBack;
	RecordListScrollView   *m_scrollView;
	QLabel                 *m_labelChannelName;
	SearchBar              *m_searchBar;
	Calendar               *m_calendar;
	QDate                   m_searchDate;

	QLabel                 *m_showInfo;

	LCOpenSDK_Download*     m_lcopensdkDownloadInstance;
	int                     m_downloadingIndex;     /* 当前正在下载的index，Demo不支持多路同时下载，-1表示没有正在下载 */
	QString                 m_cloudRecordsDir;
	QString                 m_deviceRecordsDir;
	QByteArray              m_downloadingFilePath;  /* 保存当前正在下载的云录像文件路径，删除不完整的录像文件 */
	long long               m_fileLength;
	long long               m_downloadLength;

	/* 私有化show方法,外部只能通过showDeviceRecordListView && showCloudRecordListView 显示界面 */
	inline virtual void show() { QWidget::show(); };

	void fillBackGroundWithColor(QWidget *widget, QColor& color);
	void setPosition(const QRect &position);

signals:
	void sgnPlayCloudRecord(int deviceIndex, int index);
	void sgnPlayDeviceRecord(int deviceIndex, int index);
	void sgnReturnToDevicesList(bool refreshDevicesList);
	void sgnDownloadPercent(int index, int percent);
	void sgnCancelDownload(int index);
	void sgnSetDownloadUI(int index, bool flag);
	void sgnSetShowInfo(QString info);
	void sgnDownloadError(int status);
private slots:
	/**
	* 后台录像查询线程结果槽(查询结束会通知该槽)
	* @param   [in] int result 小于0表示执行失败，其他表示成功
	* @return  void
	*/
	void slotRecordThreadResult(int result);

	/**
	* 录像列表中的某个录像被点击播放
	* @param   [in] int index
	* @return  void
	*/
	void slotPlayBtnClicked(int index);
	void slotDownloadBtnClicked(int index);
	void slotCancelBtnClicked(int index);

	void slotBackBtnClicked();
	void slotSearch(QString date);
	void slotShowOrHideCalendar();
	void slotSetText(QDate date);
	// void slotDownloadError(int status);
	void slotSetShowInfo(QString info);
};

#endif // RECORDLISTVIEW_H
