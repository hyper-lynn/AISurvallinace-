#ifndef DEVICEADDVIEW_H
#define DEVICEADDVIEW_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit> 
#include "Src/Ctrl/OpenApiCtrl.h"
#include "Src/Utils/CommonView/IconTextBtn.h"
#include "Src/Utils/CommonView/IconBtn.h"
#include "Src/Utils/CommonView/MyEditBox.h"
#include "lcopensdk_deviceinit/LCOpenSDK_DeviceInit.h"

class DeviceAddView : public QWidget
{
	Q_OBJECT

public:
	DeviceAddView(QWidget *parent);
	~DeviceAddView();

	int init();
	void release();

signals:
	void sgnReturnToDevicesList(bool refreshDevicesList);

private slots:
	void slotAddDevice();
	void slotReturnToDevicesList();
	void slotDecryptKeyBoxOK(QString);
	void slotDevSafeCodeBox(QString);

protected:
	virtual void showEvent(QShowEvent *e);

private:
	QLabel*                     m_SeparatorLbl;
	QWidget*                    m_ToolBar;
	IconTextBtn*                m_ReturnToDevicesListBtn;
	QWidget*                    m_WorkBar;
	QLabel*                     m_DeviceIdLbl;
	QLabel*                     m_deviceIdCircularLbl;
	QLineEdit*                  m_DeviceIdEdt;
	QLabel*                     m_deviceKeyLbl;
	QLabel*                     m_deviceKeyCircularLbl;
	QLineEdit*                  m_deviceKeyEdt;
	IconBtn*                    m_bindDeviceBtn;
	QLabel*                     m_HintLbl;
	QLabel*                     m_HintIcon;
	OpenApiCtrl*                m_OpenApiCtrlInstance;
	MyEditBox*                  m_decryptKeyBox;
	MyEditBox*                  m_devSafeCodeBox;
	QString                     m_deviceId;
	ChannelInfoList             m_InitChannelInfoList;
	QString                     m_deviceKey;
	LCOpenSDK_DeviceInit::DEVICE_INIT_INFO m_devInitInfo;

	void restApiBind(QString deviceKey);
};

#endif // DEVICEADDVIEW_H
