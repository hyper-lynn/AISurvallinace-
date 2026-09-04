#ifndef _ALARMMSGSLISTVIEW_H_
#define _ALARMMSGSLISTVIEW_H_

#include <QWidget>
#include <QDate>
#include "Src/Utils/CurlDownload.h"
#include <QVector>
#include "AlarmMsgView.h"
#include "AlarmMsgBigPicView.h"
#include "Src/Model/AlarmMsgInfo.h"
#include "Src/Utils/CommonView/IconTextBtn.h"
#include "Src/Utils/CommonView/BaseScrollView.h"
#include "Src/Utils/CommonView/SearchBar.h"
#include "Src/Utils/CommonView/Calendar.h"
#include "Src/Ctrl/DevicesListCtrl.h"
#include "Src/Ctrl/ThreadCtrl.h"

class AlarmMsgsListView : public QWidget
{
	Q_OBJECT

public:
	AlarmMsgsListView(QWidget* parent);
	~AlarmMsgsListView();

	int init();
	void release();

	void setDeviceIndex(int deviceIndex);
	void show();

private:
	void clearAlarmMsg();
	void getAlarmMsgByTime(QString beginTime, QString endTime);
	void loadAlarmMsgSmallPic(int alarmMsgIndex);
	void loadAlarmMsgBigPic();
	void refreshAlarmMsgBigPicView();

private:
	int                         m_deviceIndex;
	QLabel*                     m_separatorLbl;
	QWidget*                    m_toolBar;
	IconTextBtn*                m_returnToDevicesListBtn;
	QLabel*                     m_statusLbl;
	QWidget*                    m_workBar;
	QLabel*                     m_channelNameLbl;
	SearchBar*                  m_searchBar;
	Calendar*                   m_calendar;
	QLabel*                     m_separatorLbl1;
	QLabel*                     m_separatorLbl2;
	BaseScrollView*             m_scrollView;
	AlarmMsgBigPicView*         m_alarmMsgBigPicView;
	AlarmMsgParameter           m_alarmMsgParam;
	AlarmMsgInfoList            m_alarmMsgInfoList;
	QVector<AlarmMsgView*>      m_alarmMsgViewVector;
	CurlDownload*               m_CurlDownloadS;
	CurlDownload*               m_CurlDownloadB;
	int                         m_alarmMsgSmallPicIndex;    /* 报警消息小图index */
	int                         m_alarmMsgBigPicIndex;      /* 报警消息大图index */
	ThreadCtrl*                 m_threadCtrl;
	bool                        m_isOpenApiRunning; /* 是否正在进行OpenApi操作，如获取报警消息列表、删除报警消息等 */
	unsigned char*              m_decryptPicBuf;
	QString                     m_decryptKey;


	bool                        m_isCurlDownLoadEnabled;

signals:
	void sgnReturnToDevicesList(bool refreshDevicesList);
	void sgnReply(const QPixmap& alarmMsgBigPic);   /* 点击报警消息大图中last和next按钮的响应 */

private slots:
	void slotReturnToDevicesList();
	void slotGetCurrentAlarmMsgs();
	void slotHandleResult(int result);
	void slotCurlDownloadFinishedS(unsigned char* data, unsigned int dataLen, QString deviceId);
	void slotCurlDownloadFinishedB(unsigned char* data, unsigned int dataLen, QString deviceId);
	void slotAlarmSmallPicLblDblClicked(int alarmMsgIndex);
	void slotLast();
	void slotNext();
	void slotRemoveAlarmMsg(int alarmMsgIndex);
	void slotShowOrHideCalendar();
	void slotSetSearchData(QDate date);
	void slotSearch(QString date);
};

#endif /* _ALARMMSGSLISTVIEW_H_ */
