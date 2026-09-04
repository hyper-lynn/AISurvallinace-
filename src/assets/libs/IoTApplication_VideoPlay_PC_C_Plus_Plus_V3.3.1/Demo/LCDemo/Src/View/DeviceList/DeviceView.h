#ifndef _DEVICEVIEW_H_
#define _DEVICEVIEW_H_

#include <QWidget>
#include <QLabel>
#include "Utils/CommonView/IconBtn.h"
#include "Utils/CommonView/RoundRectTextBtn.h"
#include "Utils/CommonView/CheckBtn.h"
#include "Ctrl/OpenApiCtrl.h"
#include "Ctrl/DevicesListCtrl.h"

class DeviceView : public QWidget
{
    Q_OBJECT

public:
    DeviceView(QWidget* parent);
    ~DeviceView();

    int init();
    void release();

    void setDeviceIndex(int deviceIndex);
    void setChannelName(const QString& channelName);
    void setChannelPic(const QPixmap& pixmap);

    void setOfflineStatus();
    void setSleepStatus();
    void setDecryptStatus(bool flag);

signals:
    void sgnGetDevicesList();
    void sgnShowDeviceOperate(int deviceIndex);
    void sgnPlay(int deviceIndex);
    void sgnShowLocalRecord(int deviceIndex);
    void sgnShowCloudRecord(int deviceIndex);

    void sgnDecryptShadeClicked(int deviceIndex);

private slots:
    void slotDeviceRemove();
    void slotShowDeviceOperate();
    void slotPlay();
    void slotShowLocalRecord();
    void slotShowCloudRecord();

    void slotDecryptShadeClicked();

private:
    QLabel*             m_ChannelPicLbl;
    IconBtn*            m_PlayBtn;
    QLabel*             m_OfflineLbl;
    QLabel*             m_ChannelNameLbl;
    IconBtn*            m_DeviceRemoveBtn;
    RoundRectTextBtn*   m_DeviceRecordBtn;
    RoundRectTextBtn*   m_CloudRecordBtn;

    RoundRectTextBtn*   m_DeviceOperateBtn;
    QWidget*            m_TopShade;
    QWidget*            m_BottomShade;
    int                 m_DeviceIndex;
    OpenApiCtrl*        m_OpenApiCtrlInstance;
    DevicesListCtrl*    m_DevicesListCtrlInstance;
    CheckBtn*           m_decryptShade;
};

#endif /* _DEVICEVIEW_H_ */
