#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_LCOpenSDKDemo.h"

#include "Login/LoginSelectView.h"
#include "DeviceList/DevicesListView.h"
#include "DeviceManage/DeviceAddView.h"
#include "DeviceManage/DeviceSetView.h"
#include "AlarmMsg/AlarmMsgsListView.h"
#include "VideoPlay/RealPlayView.h"
#include "RecordList/RecordListView.h"
#include "VideoPlay/RecordPlayView.h"
#include "Src/Utils/CommonView/TitleBar/PageTitle.h"


class LCOpenSDKDemo : public QMainWindow
{
	Q_OBJECT

		typedef enum EWidgetType
	{
		E_Widget_HomePage = 0,    // 首页
		E_Widget_DevicesListView,
		E_Widget_DeviceAddView,
		E_Widget_DeviceSetView,
		E_Widget_AlarmMsgListView,
		E_Widget_RealPlayView,
		E_Widget_RecordListView,
		E_Widget_RecordPlayView
	}EWidgetType_t;

public:
	LCOpenSDKDemo(QWidget *parent = Q_NULLPTR);

	//void release();

signals:
	void sgnGetDevicesList();
	void sgnGetCurrentAlarmMsgs();

public slots:
	void slotShowDevicesList();
	void slotReturnToHomePage();
	void slotShowAddDevice();
	void slotReturnToDevicesList(bool refreshDevicesList);
	void slotShowDeviceOperate(int deviceIndex);
	void slotPlay(int deviceIndex);
	void slotShowLocalRecordList(int deviceIndex);
	void slotShowCloudRecordList(int deviceIndex);
	void slotShowAlarmMsgsListView(int deviceIndex);
	void slotCloseWin();
	void slotMinimize();
	//////////////////////////////////////////////////////////////////////////
	void slotPlayCloudRecord(int deviceIndex, int index);
	void slotPlayDeviceRecord(int deviceIndex, int index);
	void slotBackToRecordList(int recordType);

	//void ResizeDemo();

protected:
	int init();
	/**自定义标题栏需要监听鼠标事件*/
	void mousePressEvent(QMouseEvent *e);
	void mouseMoveEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *e);
	bool eventFilter(QObject *watched, QEvent *event);

private:
	Ui::LCOpenSDKDemoClass ui;

	LoginSelectView*            m_HomePage;
	DevicesListView*            m_DevicesList;
	DeviceAddView*              m_AddDevice;
	DeviceSetView*              m_DeviceSet;

	AlarmMsgsListView           *m_alarmMsgsListView;  /**报警消息页面*/
	RealPlayView                *m_realPlayView;  /**实时预览页面*/
	RecordListView              *m_recordListView;/**录像列表页面*/
	RecordPlayView              *m_recordPlayView;/**录像播放页面*/

	QPoint                      m_oldPos;   /**标题栏拖动位置标识*/
	bool                        m_mouseDown;/**标题栏拖动鼠标标识*/
};
