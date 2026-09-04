#ifndef _DEVICESLISTVIEW_H_
#define _DEVICESLISTVIEW_H_

#include <QWidget>
#include <QLabel>
#include <QVector>
#include "DeviceView.h"
#include "Src/Utils/CommonView/IconTextBtn.h"
#include "Src/Utils/CommonView/BaseScrollView.h"
#include "Src/Utils/CommonView/MyEditBox.h"
#include "Src/Ctrl/DevicesListCtrl.h"
#include "Src/Ctrl/ThreadCtrl.h"
#include "Src/Utils/CommonView/SearchDeviceBar.h"

class DevicesListView : public QWidget
{
	Q_OBJECT

public:
	DevicesListView(QWidget* parent);
	~DevicesListView();

	int init();
	void release();
private:
	void clearDeviceViewVector();
	void onGetDevicesListP2PPort();

signals:
	void sgnReturnToLogin();
	void sgnShowAddDevice();
	//
	void sgnShowSearchDevice();
	void sgnShowDeviceOperate(int deviceIndex);
	void sgnGetChannelPic(int deviceIndex);
	void sgnPlay(int deviceIndex);
	void sgnShowLocalRecord(int deviceIndex);
	void sgnShowCloudRecord(int deviceIndex);
	void sgnShowAlarmMsgsListView(int deviceIndex);

private slots:
	void slotGetDevicesList();
	void slotReturnToLogin();
	void slotShowAddDevice();

	void slotShowSearchDevice();
	void slotShowDeviceOperate(int deviceIndex);
	void slotGetChannelPicFinished(int deviceIndex, QPixmap pixmap);
	void slotPlay(int deviceIndex);
	void slotShowLocalRecord(int deviceIndex);
	void slotShowCloudRecord(int deviceIndex);
	void slotShowAlarmMsgsListView(int deviceIndex);
	void slotHandleResult(int result);
	void slotShowDecryptKeyBox(int decryptKeyIndex);
	void slotDecryptKeyBoxOK(QString decryptKey);
	//
	void slotSearchDevice(QString deviceID);
	void slotSearchResult(int result);
	void slotGetP2PPortResult(int result);

private:
	QLabel*                     m_SeparatorLbl;
	QLabel*                     m_SeparatorLb2;
	QLabel*                     m_SeparatorLb3;
	QWidget*                    m_ToolBar;
	IconTextBtn*                m_ReturnToLoginBtn;
	IconTextBtn*                m_AddDeviceBtn;
	//
	IconTextBtn*                m_FindDeviceBtn;
	BaseScrollView*             m_ScrollView;
	QVector<DeviceView*>        m_DeviceViewVector;
	DevicesListCtrl*            m_DevicesListCtrlInstance;
	ThreadCtrl*                 m_ThreadCtrl;
	ThreadCtrl*                 m_ThreadCtrlGetP2PPort;
	ChannelInfoList*            m_ChannelInfoList;
	MyEditBox*                  m_decryptKeyBox;
	int                         m_decryptKeyIndex;
	//根据设备ID搜索设备信息
	SearchDeviceBar*			m_searchDeviceBar;
	QWidget*					m_workBar;
	QLabel*						m_HintLbl;
	QLabel*						m_HintIcon;
};

#endif /* _DEVICESLISTVIEW_H_ */
