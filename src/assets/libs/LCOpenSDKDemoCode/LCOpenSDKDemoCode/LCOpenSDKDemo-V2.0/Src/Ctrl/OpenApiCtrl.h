#ifndef _OPENAPICTRL_H_
#define _OPENAPICTRL_H_

#include <QObject>
#include "LCOpenSDK_Api.h"
#include "Src/Utils/global.h"
#include "Src/Model/OpenApiInfo.h"
#include "Src/Model/ChannelsListInfo.h"
#include "Src/Model/RecordInfo.h"
#include "Src/Ctrl/TokenCtrl.h"
#include "Src/Model/AlarmMsgInfo.h"
#include "Src/Model/PtzControlInfo.h"

class OpenApiCtrl : public QObject
{
	Q_OBJECT

public:
	~OpenApiCtrl();
	static OpenApiCtrl* getInstance();
	void init(const OPEN_API_INIT_PARAM* param);
	void unInit();

	QString getToken();
	int getAccessToken(const TOKEN_PARAMETERS* param, OUT QString& ret_code, OUT QString& ret_msg);
	int getUserToken(const TOKEN_PARAMETERS* param, OUT QString& ret_code, OUT QString& ret_msg);
	int userBindSms(const TOKEN_PARAMETERS* param, OUT QString& ret_code, OUT QString& ret_msg);
	int userBind(const USERBIND_PARAMETERS* param, OUT QString& ret_code, OUT QString& ret_msg);

	bool getDevicesList(ChannelInfoList* channelInfoList);
	bool getDevicesListP2PPort(ChannelInfoList* channelInfoList);
	bool getIotDeviceProperties(QString deviceId, QString productId, QString properties, int channelId);
	bool searchDeviceByID(QString deviceID, ChannelInfoList* ChannelInfoList);
	QString checkDeviceBindOrNot(QString deviceId, bool& isMine, bool& isBind);
	QString checkDeviceOnlineOrNot(QString deviceId, bool& isOnline);
	QString bindDevice(QString deviceId, QString code);
	QString unBindDevice(QString deviceId);
	QString unBindDeviceInfo(QString deviceId, QString &ability, QString &productId);
	QString getDeviceCameraStatus(QString deviceId, int channelId, QString enableType, QString &status);
	QString setDeviceCameraStatus(QString deviceId, int channelId, QString enableType, bool enable);
	QString modifyDeviceAlarmStatus(QString deviceId, int channelId, bool flag);
	QString setStorageStrategy(QString deviceId, int channelId, bool flag);
	QString modifyDevicePassword(QString deviceId, QString oldPwd, QString newPwd);
	QString upgradeDevice(QString deviceId);
	int getDeviceRecordNum(const RECORD_PARAMETERS *parameters);
	int getDeviceRecords(const RECORD_PARAMETERS *parameters, OUT RECORD_INFO_LIST *recordList);
	int getCloudRecordNum(const RECORD_PARAMETERS *parameters);
	int getCloudRecords(const RECORD_PARAMETERS *parameters, OUT RECORD_INFO_LIST *recordList);
	int getAlarmMsg(AlarmMsgParameter* alarmMsgParam, AlarmMsgInfoList* alarmMsgInfoList);
	bool deleteAlarmMsg(AlarmMsgInfo* alarmMsgInfo);
	bool getDeviceVersionList(QString deviceId);
	int getStorageStrategy(QString deviceId, int channelId);

private:
	OpenApiCtrl();

private:
	LCOpenSDK_Api*      m_OpenApiHandle;
	QString             m_Token;
	QString             m_appId;
	QString             m_appSecret;
	bool                m_IsGetTokenOK;
};

#endif /* _OPENAPICTRL_H_ */
