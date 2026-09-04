#ifndef TOKENCTRL_H
#define TOKENCTRL_H

#include <QObject>
#include "Utils/global.h"
#include <vector>
#include <QNetworkReply>
#include "Network/Network.h"
#include <QJsonObject>
#include "Model/RecordInfo.h"
#include "ThreadCtrl.h"

typedef struct tokenParameters
{
    QString     host;
    int         port;
    QString     appId;
    QString     appSecret;
    QString     phone;
}TOKEN_PARAMETERS;

typedef struct _iotChannels_
{
	std::string channelPicUrl;
	std::string csStatus;
	std::string shareFunctions;
	std::string channelId;
	std::string channelName;
	std::string channelAbility;
	std::string lastOffLineTime;
	std::string channelStatus;
}IotChannels;

typedef struct deviceInfo
{
	std::string		deviceId;
	std::string		playInfo;
	std::string		deviceName;
	std::string		deviceModel;
	std::string		deviceAbility;
	std::string		deviceVersion;
	int				channelNum;
	std::string		accessType;
	std::string		deviceStatus;
	std::string		source;
	bool			canBeUpgrade;
	std::string		encryptMode;
	std::vector<IotChannels> iotChannel;
	std::string     catalog;
}DEVICE_INFO;

typedef struct structPara
{
	QString host;
	QString AccessKey;
	QString productId;
	QString secretKey;
} STRUCT_PARA;

class QNetworkAccessManager;
class TokenCtrl : public QObject, public Common::NetworkListener
{
    Q_OBJECT

friend class OpenApiCtrl;

public:
    TokenCtrl(QObject *pParent = NULL);
    ~TokenCtrl();

	int getIOTToken(QString host, OUT QString& token, QString AccessKey, QString productId, QString secretKey);
	void getIOTPlayInfo(QString host, QString AccessKey, QString productId, QString secretKey);
	void getIOTPaaSQueryLocalRecords(RECORD_PARAMETERS recordPara);
	void getIOTQueryCloudRecords(RECORD_PARAMETERS recordPara);
	void getP2pInfo(QString host, QString AccessKey, QString productId, QString secretKey);


	static QString getIOTSign(QString ak, QString sk, QString timestamp, QString nonce, QString bodySHA512, QString appAccessToken);
	static void setParam(STRUCT_PARA para);
	static STRUCT_PARA getParam();

	static void setLocalDeviceRecords(QJsonObject localDeviceRecord);
	static QJsonObject getLocalDeviceRecords();
	void setThreadCtrlPtr(ThreadCtrl* ptr);
	static void setCloudRecords(QJsonObject cloudRecord);
	static QJsonObject getCloudRecords();


	static std::string hmacSha512(const std::string str, const std::string key);
	void getIOTPlayInfo();
	static QString removeWhitespace(QString& str);

	std::vector<DEVICE_INFO> getDeviceVec() { return deviceVec; }


	virtual void onNetworkDataCallBack(QByteArray, QString strKeyName = "");
	virtual void onNetworkFinished(QString strKeyName = "");
	/*
	* iErrorCode = -1000 SSL¥ÌŒÛ£¨-1001 «Î«Û≥¨ ±£¨
	*/
	virtual void onNetworkError(Common::NetworkError_t, QString, QString strKeyName = "");

public:
	QString m_host;
	QString m_AccessKey;
	QString m_productId;
	QString m_secretKey;

signals:
	void sgnGetPlayInfoReslut(bool bGetIotToken);
signals:
	void sgnGetP2pInfoReslut(bool bGetIotToken);

private:

	std::string m_iotToken;
	ThreadCtrl* m_threadCtrlPtr;
	// char *m_decryptedPlayInfo;
	std::vector<DEVICE_INFO>deviceVec;

	static STRUCT_PARA inputParam;
	static QJsonObject queryLocalDeviceRecords;
	static QJsonObject queryCloudRecords;
	


	Common::Network		*m_pIotTokenNetWork;
	Common::Network		*m_pIotPlayInfoTokenNetWork;
	Common::Network		*m_pIotgetDeviceRecordsNetWork;
	Common::Network		*m_pIotgetCloudRecordsNetWork;
	Common::Network		*m_pIotgetP2pInfoNetWork;

};

#endif // TOKENCTRL_H
