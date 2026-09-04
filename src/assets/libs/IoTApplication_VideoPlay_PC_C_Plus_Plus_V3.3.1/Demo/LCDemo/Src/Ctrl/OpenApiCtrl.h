#ifndef _OPENAPICTRL_H_
#define _OPENAPICTRL_H_

#include <QObject>
#include "LCOpenSDK_Api.h"
#include "Utils/global.h"
#include "Model/OpenApiInfo.h"
#include "Model/ChannelsListInfo.h"
#include "Model/RecordInfo.h"
#include "Ctrl/TokenCtrl.h"

#include "Model/PtzControlInfo.h"

class OpenApiCtrl : public QObject
{
    Q_OBJECT

public:
    ~OpenApiCtrl();
    static OpenApiCtrl* getInstance();
    void init(const OPEN_API_INIT_PARAM& param);
    void unInit();

    QString getToken();
    void setToken(QString token);
    int getIOTToken(QString host, QString AccessKey, QString productId, QString secretKey);
	int getP2PServerInfo(QString host, QString AccessKey, QString productId, QString secretKey);
	void getIOTPlayInfo(QString host, QString AccessKey, QString productId, QString secretKey);

    bool getDevicesList(ChannelInfoList* channelInfoList);
	bool getIOTDevicesList(IOTDeviceInfoList* channelInfoList);
    QString checkDeviceBindOrNot(QString deviceId, bool& isMine, bool& isBind);
    QString checkDeviceOnlineOrNot(QString deviceId, bool& isOnline);
    QString bindDevice(QString deviceId, QString code);
    bool unBindDevice(QString deviceId);
    QString unBindDeviceInfo(QString deviceId, QString& ability);
    QString bindDeviceInfo(QString deviceId, int channelId, int& alarmStatus);
    QString modifyDeviceAlarmStatus(QString deviceId, int channelId, bool flag);
    QString setStorageStrategy(QString deviceId, int channelId, bool flag);
    QString modifyDevicePassword(QString deviceId, QString oldPwd, QString newPwd);
    QString upgradeDevice(QString deviceId);
    int getDeviceRecordNum(const RECORD_PARAMETERS &parameters);
    int getDeviceRecords(const RECORD_PARAMETERS &parameters, OUT RECORD_INFO_LIST *recordList, ThreadCtrl* ptr);
    int getCloudRecordNum(const RECORD_PARAMETERS &parameters);
    int getCloudRecords(const RECORD_PARAMETERS &parameters, OUT RECORD_INFO_LIST *recordList, ThreadCtrl* ptr);

    int controlPTZ(const PTZ_CONTROL_PARAMETERS &parameters);
	int controlPaaSPTZ(const PTZ_CONTROL_PARAMETERS &parameters);

    QString getIotToken() { return m_IOTToken; }
    
signals:
    void sgnGetPlayInfoReslut(bool bGetIotToken);
signals:
	void sgnGetP2pInfoReslut(bool bGetP2pInfo);
private:
    OpenApiCtrl();

private:
    LCOpenSDK_Api*      m_OpenApiHandle;
    QString             m_Token;
	QString				m_IOTToken;
    bool                m_IsGetTokenOK;
	TokenCtrl*			m_tokenCtrl;
};

#endif /* _OPENAPICTRL_H_ */
