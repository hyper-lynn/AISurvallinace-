#ifndef _LCOPENSDKDEMO_H_
#define _LCOPENSDKDEMO_H_

#include <QtWidgets/QFrame>
#include "Login/LoginSelectView.h"
#include "DeviceList/DevicesListView.h"
#include "DeviceManage/DeviceAddView.h"
#include "DeviceManage/DeviceSetView.h"
#include "VideoPlay/RealPlayView.h"
#include "RecordList/RecordListView.h"
#include "VideoPlay/RecordPlayView.h"
#include "Utils/CommonView/TitleBar/PageTitle.h"

class MainForm : public QFrame{
    Q_OBJECT

public:
    MainForm(QWidget *parent = 0);
    ~MainForm();

    int init();
    void release();

signals:
    void sgnGetDevicesList();

private slots:
    void slotShowDevicesList();
    void slotReturnToLogin();
    void slotShowAddDevice();
    void slotReturnToDevicesList(bool refreshDevicesList);
    void slotShowDeviceOperate(int deviceIndex);
    void slotPlay(int deviceIndex);
    void slotShowLocalRecordList(int deviceIndex);
    void slotShowCloudRecordList(int deviceIndex);
    void slotCloseWin();

    //////////////////////////////////////////////////////////////////////////
    void slotPlayCloudRecord(int deviceIndex, int recordIndex);
    void slotPlayDeviceRecord(int deviceIndex, int recordIndex);
    void slotBackToRecordList(int recordType);

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void closeEvent(QCloseEvent *event) override;

private:
    LoginSelectView*            m_HomePage;
    DevicesListView*            m_DevicesList;
    DeviceAddView*              m_AddDevice;
    DeviceSetView*              m_DeviceSet;
    RealPlayView*               m_realPlayView;
    RecordListView*             m_recordListView;
    RecordPlayView*             m_recordPlayView;
    PageTitle*                  m_titleBar;
    QWidget*                    m_content;
    QPoint                      m_oldPos;
    bool                        m_mouseDown;
};

#endif /* _LCOPENSDKDEMO_H_ */
