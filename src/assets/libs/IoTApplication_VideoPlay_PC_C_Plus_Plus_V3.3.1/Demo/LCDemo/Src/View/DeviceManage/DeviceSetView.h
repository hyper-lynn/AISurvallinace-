#ifndef DEVICESETVIEW_H
#define DEVICESETVIEW_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include "Utils/CommonView/IconTextBtn.h"
#include "Utils/CommonView/CheckBtn.h"
#include "Utils/CommonView/IconBtn.h"
#include "Utils/CommonView/MyEditBox2.h"
#include "Ctrl/OpenApiCtrl.h"
#include "Ctrl/DevicesListCtrl.h"

class DeviceSetView : public QWidget
{
    Q_OBJECT

public:
    DeviceSetView(QWidget *parent);
    ~DeviceSetView();

    int init();
    void release();

    void setDeviceIndex(int deviceIndex);

    void show();

private:
    void setAlarmStatusBtnPixmap(bool flag);
    void setCloudStorageStatusBtnPixmap(bool flag);

signals:
    void sgnReturnToDevicesList(bool refreshDevicesList);

private slots:
    void slotChangeAlarmStatus();
    void slotChangeCloudStorageStatus();
    void slotModifyPassword();
    void slotModifyPasswordBoxOK(QString oldPwd, QString newPwd);
    void slotCloudUpgrade();
    void slotReturnToDevicesList();

private:
    QLabel*                     m_SeparatorLbl;
    QWidget*                    m_ToolBar;
    IconTextBtn*                m_ReturnToDevicesListBtn;
    QLabel*                     m_statusLbl;
    QWidget*                    m_WorkBar;
    QLabel*                     m_AlarmStatusLbl;
    CheckBtn*                   m_AlarmStatusBtn;
    QLabel*                     m_SeparatorAlarmStatusLbl;
    QLabel*                     m_CloudStorageStatusLbl;
    CheckBtn*                   m_CloudStorageStatusBtn;
    QLabel*                     m_SeparatorCloudStorageStatusLbl;
    QLabel*                     m_modifyPasswordLbl;
    IconBtn*                    m_modifyPasswordBtn;
    QLabel*                     m_separatorModifyPasswordLbl;
    MyEditBox2*                 m_modifyPasswordBox;
    QLabel*                     m_cloudUpgradeLbl;
    IconBtn*                    m_cloudUpgradeBtn;
    QLabel*                     m_separatorCloudUpgradeLbl;
    OpenApiCtrl*                m_OpenApiCtrlInstance;
    DevicesListCtrl*            m_DevicesListCtrlInstance;
    int                         m_DeviceIndex;
};

#endif // DEVICESETVIEW_H
