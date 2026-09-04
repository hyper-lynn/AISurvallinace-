#ifndef _DEVICESLISTVIEW_H_
#define _DEVICESLISTVIEW_H_

#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QVector>
#include "DeviceView.h"
#include "Utils/CommonView/IconTextBtn.h"
#include "Utils/CommonView/BaseScrollView.h"
#include "Utils/CommonView/MyEditBox.h"
#include "Ctrl/DevicesListCtrl.h"
#include "Ctrl/ThreadCtrl.h"

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

signals:
    void sgnReturnToLogin();
    void sgnShowAddDevice();
    void sgnShowDeviceOperate(int deviceIndex);
    void sgnGetChannelPic(int deviceIndex);
    void sgnPlay(int deviceIndex);
    void sgnShowLocalRecord(int deviceIndex);
    void sgnShowCloudRecord(int deviceIndex);


private slots:
    void slotGetDevicesList();
    void slotReturnToLogin();
    void slotShowAddDevice();
    void slotShowDeviceOperate(int deviceIndex);
    void slotGetChannelPicFinished(int deviceIndex, QPixmap pixmap);
    void slotPlay(int deviceIndex);
    void slotShowLocalRecord(int deviceIndex);
    void slotShowCloudRecord(int deviceIndex);

    void slotHandleResult(int result);
    void slotShowDecryptKeyBox(int decryptKeyIndex);
    void slotDecryptKeyBoxOK(QString decryptKey);

private:
    QLabel*                     m_SeparatorLbl;
    QWidget*                    m_ToolBar;
    IconTextBtn*                m_ReturnToLoginBtn;
    IconTextBtn*                m_AddDeviceBtn;
    BaseScrollView*             m_ScrollView;
    QVector<DeviceView*>        m_DeviceViewVector;
    DevicesListCtrl*            m_DevicesListCtrlInstance;
    ThreadCtrl*                 m_ThreadCtrl;
    ChannelInfoList*            m_ChannelInfoList;
	IOTDeviceInfoList*			m_IOTDeviceInfoList;
    MyEditBox*                  m_decryptKeyBox;
    int                         m_decryptKeyIndex;
};

#endif /* _DEVICESLISTVIEW_H_ */
