#include <libdsl/DPrintLog.h>
#include "TokenCtrl.h"
#include "OpenApiCtrl.h"
#include "LCOpenSDK_LoginManager.h"
#include <QMessageAuthenticationCode>
#include <QCoreApplication>
// #include <QCryptographicHash> QT4.8.5 no HMAC-SHA512 algori
#include <QDebug>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <QDateTime>
#include <stdlib.h>
#include <QUuid>
#include <Windows.h>
#include <string>
#include <cstring>
#include "LCOpenSdk_Utils.h"
#include <QByteArray>
#include <wininet.h>
#include <QJsonDocument>
//#include <QJsonObject>
#include "LCOpenSDK_Crypter.h"
#include <QString>
#include <QJsonArray>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QSslConfiguration>
#include <QNetworkRequest>
#include <QNetworkConfiguration>
#include <QString>
#include <QRegularExpression>

#include <fstream>
#include <string>
#include <iterator>


//#include "NetworkThread.h"
#include <QThread>

#include <QTimer>
//#pragma comment(lib,"WinInet.lib")




//char *TokenCtrl::m_iotToken;
//std::string TokenCtrl::m_iotToken;
//char *TokenCtrl::m_decryptedPlayInfo;
//DEVICE_INFO TokenCtrl::m_deviceInfo;
//std::string TokenCtrl::m_deviList;
//std::string TokenCtrl::m_channels;
//std::vector<DEVICE_INFO> TokenCtrl::deviceVec;

//Key calculation rule version
typedef enum
{
	E_RULE_VERSION_UNKNOWN      = -1, //
	E_RULE_VERSION_EASY4IP      = 0, //easy4ip encryption rule
	E_RULE_VERSION_LECHANGE     = 1, //Lechange encryption rule
	E_RULE_VERSION_DAHUAPASS    = 2, //Unified PASS encryption rule
	E_RULE_VERSION_COUNT,
}E_RULE_VERSION;

structPara TokenCtrl::inputParam;
QJsonObject TokenCtrl::queryLocalDeviceRecords;
QJsonObject TokenCtrl::queryCloudRecords;

int p2pEncryptMode = 1;

QString TokenCtrl::removeWhitespace(QString& str) {
	return str.remove(QRegularExpression(R"(\s+)"));
}

TokenCtrl::TokenCtrl(QObject *parent):
	QObject(parent), m_pIotTokenNetWork(NULL), m_pIotPlayInfoTokenNetWork(NULL), m_pIotgetDeviceRecordsNetWork(NULL), m_pIotgetCloudRecordsNetWork(NULL), m_pIotgetP2pInfoNetWork(NULL)
{
	m_threadCtrlPtr = nullptr;

	if (m_pIotTokenNetWork)
	{
		m_pIotTokenNetWork->registerObject(NULL);
		m_pIotTokenNetWork->cancleRequest();
		m_pIotTokenNetWork->deleteLater();
	}

	{
		m_pIotTokenNetWork = new Common::Network("IotToken");
		m_pIotTokenNetWork->setTimeoutTime(10000);
		m_pIotTokenNetWork->registerObject(this);
	}

	if (m_pIotPlayInfoTokenNetWork)
	{
		m_pIotPlayInfoTokenNetWork->registerObject(NULL);
		m_pIotPlayInfoTokenNetWork->cancleRequest();
		m_pIotPlayInfoTokenNetWork->deleteLater();
	}

	{
		m_pIotPlayInfoTokenNetWork = new Common::Network("IotPlayInfo");
		m_pIotPlayInfoTokenNetWork->setTimeoutTime(10000);
		m_pIotPlayInfoTokenNetWork->registerObject(this);
	}

	if (m_pIotgetDeviceRecordsNetWork)
	{
		m_pIotgetDeviceRecordsNetWork->registerObject(NULL);
		m_pIotgetDeviceRecordsNetWork->cancleRequest();
		m_pIotgetDeviceRecordsNetWork->deleteLater();
	}

	{
		m_pIotgetDeviceRecordsNetWork = new Common::Network("IotGetDeviceRecord");
		m_pIotgetDeviceRecordsNetWork->setTimeoutTime(20000);
		m_pIotgetDeviceRecordsNetWork->registerObject(this);
	}

	//query cloud records
	if (m_pIotgetCloudRecordsNetWork)
	{
		m_pIotgetCloudRecordsNetWork->registerObject(NULL);
		m_pIotgetCloudRecordsNetWork->cancleRequest();
		m_pIotgetCloudRecordsNetWork->deleteLater();
	}

	{
		m_pIotgetCloudRecordsNetWork = new Common::Network("IotGetCloudRecord");
		m_pIotgetCloudRecordsNetWork->setTimeoutTime(20000);
		m_pIotgetCloudRecordsNetWork->registerObject(this);
	}

	//query p2p info
	if (m_pIotgetP2pInfoNetWork)
	{
		m_pIotgetP2pInfoNetWork->registerObject(NULL);
		m_pIotgetP2pInfoNetWork->cancleRequest();
		m_pIotgetP2pInfoNetWork->deleteLater();
	}

	{
		m_pIotgetP2pInfoNetWork = new Common::Network("IotGetP2pInfo");
		m_pIotgetP2pInfoNetWork->setTimeoutTime(20000);
		m_pIotgetP2pInfoNetWork->registerObject(this);
	}



}

TokenCtrl::~TokenCtrl()
{

}

int TokenCtrl::getIOTToken(QString host, OUT QString& token, QString AccessKey, QString productId, QString secretKey)
{
	m_host = host;
	m_AccessKey = AccessKey;
	m_productId = productId;
	m_secretKey = secretKey;
	//QString strVersionUrl = "https://open-api-or.dolynksecurity.com/open-api/api-base/auth/getAppAccessToken";
	QString strUrlPrefix = "https://";
	QString getAccessToken = "/open-api/api-base/auth/getAppAccessToken";
	QString strVersionUrl = strUrlPrefix.append(host).append(getAccessToken);
	//QString strVersionUrl = "https://open.dolynksecurity.com/open-api/api-base/auth/getAppAccessToken";
	QNetworkRequest *request = new QNetworkRequest(strVersionUrl);

	QString timetampValue = QString::number(QDateTime::currentDateTime().toMSecsSinceEpoch());

	QString nonceQstring = QUuid::createUuid().toString();
	nonceQstring = nonceQstring.mid(1, nonceQstring.length() - 2);

	//QString sk = "1n2jxipm2m5hls4dr4tybywlkt1ajno3";

	QString bodysha512 = "";
	QString signa = getIOTSign(AccessKey, secretKey, timetampValue, nonceQstring, bodysha512, "");
	signa = signa.toUpper();

	QString oldQstring = QUuid::createUuid().toString();
	oldQstring = oldQstring.mid(1, oldQstring.length() - 2);

	m_pIotTokenNetWork->setRequestUrl(strVersionUrl);
	QMap<QString, QString> heads;
	heads.insert("Content-Type", "application/json");
	heads.insert("Version", "v1");
	heads.insert("AccessKey", AccessKey.toLatin1());
	heads.insert("ProductId", productId.toLatin1());
	heads.insert("X-TraceId-Header", oldQstring.toLatin1());
	heads.insert("Timestamp", timetampValue.toLatin1());
	heads.insert("Sign", signa.toLatin1());
	heads.insert("Nonce", nonceQstring.toLatin1());
	DLOG_INFO("X-TraceId-Header = %s,timetampValue= %s, nonceQstring=%s, signa = %s", oldQstring.toLatin1().data(), timetampValue.toLatin1().data(), nonceQstring.toLatin1().data(), signa.toLatin1().data());
	m_pIotTokenNetWork->postRequest("", heads);
	DLOG_INFO("here TEST3");

	return 0;
}
void TokenCtrl::setThreadCtrlPtr(ThreadCtrl* ptr)
{
	m_threadCtrlPtr = ptr;
}

void TokenCtrl::getIOTPlayInfo(QString host, QString AccessKey, QString productId, QString secretKey)
{
	STRUCT_PARA tmpPara;
	tmpPara.AccessKey = AccessKey;
	tmpPara.host = host;
	tmpPara.productId = productId;
	tmpPara.secretKey = secretKey;
	setParam(tmpPara);

	QString timetampValue = QString::number(QDateTime::currentDateTime().toMSecsSinceEpoch());

	QString nonceQstring = QUuid::createUuid().toString();
	nonceQstring = nonceQstring.mid(1, nonceQstring.length() - 2);

	// QString sk = "1n2jxipm2m5hls4dr4tybywlkt1ajno3";
	// Add request body
	const char* jsonData = "{\"pageSize\":\"10\",\"pageNum\":\"1\"}";
	qDebug() << "jsonData length: " << strlen(jsonData);
	char *outData = LCOpenSdk_Utils::sha512Cry(jsonData);
	qDebug() << "bodyBuffer: " << jsonData;
	qDebug() << "sha512Cry outData: " << outData;
	QString bodySha512 = QString(outData);
	//delete[] outData;

	QString appToken = QString::fromUtf8(m_iotToken.c_str());
	QString signa = getIOTSign(AccessKey, secretKey, timetampValue, nonceQstring, bodySha512, appToken);
	signa = signa.toUpper();


	QString oldQstring = QUuid::createUuid().toString();
	oldQstring = oldQstring.mid(1, oldQstring.length() - 2);

	QString strUrlPrefix = "https://";
	QString getAccessToken = "/open-api/api-iot/device/getDeviceList";
	//QString getAccessToken = "/open-api/api-iot/device/listDeviceDetailsByIds";
	QString strVersionUrl = strUrlPrefix.append(host).append(getAccessToken);
	//QString strVersionUrl = "https://open-api-or.dolynksecurity.com/open-api/api-iot/device/getDeviceList";
	//QString strVersionUrl = "https://open.dolynksecurity.com/open-api/api-iot/device/getDeviceList";
	QNetworkRequest request(strVersionUrl);
	DLOG_INFO("here zjnTEST");
	request.setRawHeader("Content-Type", "application/json");
	request.setRawHeader("Version", "v1");
	request.setRawHeader("AppAccessToken", QString(m_iotToken.c_str()).toLatin1());
	request.setRawHeader("AccessKey", AccessKey.toLatin1());
	request.setRawHeader("ProductId", productId.toLatin1());
	request.setRawHeader("X-TraceId-Header", oldQstring.toLatin1());
	request.setRawHeader("Timestamp", timetampValue.toLatin1());
	request.setRawHeader("Sign", signa.toLatin1());
	request.setRawHeader("Nonce", nonceQstring.toLatin1());

	m_pIotPlayInfoTokenNetWork->setRequestUrl(strVersionUrl);
	QMap<QString, QString> heads;
	heads.insert("Content-Type", "application/json");
	heads.insert("Version", "v1");
	heads.insert("AppAccessToken", QString(m_iotToken.c_str()).toLatin1());
	heads.insert("AccessKey", AccessKey.toLatin1());
	heads.insert("ProductId", productId.toLatin1());
	heads.insert("X-TraceId-Header", oldQstring.toLatin1());
	heads.insert("Timestamp", timetampValue.toLatin1());
	heads.insert("Sign", signa.toLatin1());
	heads.insert("Nonce", nonceQstring.toLatin1());
	DLOG_INFO("here zjnTEST2");
	m_pIotPlayInfoTokenNetWork->postRequest(jsonData, heads);
}

void TokenCtrl::getIOTPaaSQueryLocalRecords(RECORD_PARAMETERS parameters)
{
	int count = 10;

	QJsonObject jsonObj;
	jsonObj["deviceId"] = parameters.deviceId;
	jsonObj["channelId"] = parameters.channelId;
	jsonObj["beginTime"] = parameters.beginTime;
	jsonObj["endTime"] = parameters.endTime;
	jsonObj["count"] = count;

	QJsonDocument jsonDoc(jsonObj);
	QByteArray jsonData = jsonDoc.toJson(QJsonDocument::Compact);

	const char* jsonDataChar = jsonData.constData();

	QString jsonString = QString::fromUtf8(jsonDataChar);

	//remove all Whitespace
	QString jsonStringRemovewhitespace = removeWhitespace(jsonString);
	std::string stdStrRemovewhitespace = jsonStringRemovewhitespace.toStdString();
	const char* bodySha512Removewhitespace = stdStrRemovewhitespace.c_str();
	QString timetampValue = QString::number(QDateTime::currentDateTime().toMSecsSinceEpoch());

	QString nonceQstring = QUuid::createUuid().toString();
	nonceQstring = nonceQstring.mid(1, nonceQstring.length() - 2);

	char *outData = LCOpenSdk_Utils::sha512Cry(bodySha512Removewhitespace);
	qDebug() << "sha512Cry outData: " << outData;
	QString bodySha512 = QString(outData);
	QString appToken = QString::fromUtf8(m_iotToken.c_str());

	STRUCT_PARA para = TokenCtrl::getParam();
	QString signa = TokenCtrl::getIOTSign(para.AccessKey, para.secretKey, timetampValue, nonceQstring, bodySha512, appToken);
	signa = signa.toUpper();


	QString oldQstring = QUuid::createUuid().toString();
	oldQstring = oldQstring.mid(1, oldQstring.length() - 2);

	QString strUrlPrefix = "https://";
	QString queryLocalRecordsUri = "/open-api/api-iot/device/queryLocalRecords";
	QString strVersionUrl = strUrlPrefix.append(para.host).append(queryLocalRecordsUri);
	QNetworkRequest request(strVersionUrl);
	DLOG_INFO("here TEST");
	request.setRawHeader("Content-Type", "application/json");
	request.setRawHeader("Version", "v1");
	request.setRawHeader("AppAccessToken", QString(m_iotToken.c_str()).toLatin1());
	request.setRawHeader("AccessKey", para.AccessKey.toLatin1());
	request.setRawHeader("ProductId", para.productId.toLatin1());
	request.setRawHeader("X-TraceId-Header", oldQstring.toLatin1());
	request.setRawHeader("Timestamp", timetampValue.toLatin1());
	request.setRawHeader("Sign", signa.toLatin1());
	request.setRawHeader("Nonce", nonceQstring.toLatin1());

	m_pIotgetDeviceRecordsNetWork->setRequestUrl(strVersionUrl);
	QMap<QString, QString> heads;
	heads.insert("Content-Type", "application/json");
	heads.insert("Version", "v1");
	heads.insert("AppAccessToken", QString(m_iotToken.c_str()).toLatin1());
	heads.insert("AccessKey", para.AccessKey.toLatin1());
	heads.insert("ProductId", para.productId.toLatin1());
	heads.insert("X-TraceId-Header", oldQstring.toLatin1());
	heads.insert("Timestamp", timetampValue.toLatin1());
	heads.insert("Sign", signa.toLatin1());
	heads.insert("Nonce", nonceQstring.toLatin1());
	DLOG_INFO("here test2");
	int a = m_pIotgetDeviceRecordsNetWork->postRequest(jsonDataChar, heads);
}

void TokenCtrl::getIOTQueryCloudRecords(RECORD_PARAMETERS parameters)
{
	QString queryRange = "10";
	QString channelId;
	channelId.setNum(parameters.channelId);

	QJsonObject jsonObj;
	jsonObj["deviceId"] = parameters.deviceId;
	jsonObj["channelId"] = channelId;
	jsonObj["beginTime"] = parameters.beginTime;
	jsonObj["endTime"] = parameters.endTime;
	jsonObj["queryRange"] = "1-10";

	QJsonDocument jsonDoc(jsonObj);
	QByteArray jsonData = jsonDoc.toJson(QJsonDocument::Compact);

	const char* jsonDataChar = jsonData.constData();

	QString jsonString = QString::fromUtf8(jsonDataChar);

	//remove all Whitespace
	QString jsonStringRemovewhitespace = removeWhitespace(jsonString);
	std::string stdStrRemovewhitespace = jsonStringRemovewhitespace.toStdString();
	const char* bodySha512Removewhitespace = stdStrRemovewhitespace.c_str();
	QString timetampValue = QString::number(QDateTime::currentDateTime().toMSecsSinceEpoch());

	QString nonceQstring = QUuid::createUuid().toString();
	nonceQstring = nonceQstring.mid(1, nonceQstring.length() - 2);

	char *outData = LCOpenSdk_Utils::sha512Cry(bodySha512Removewhitespace);
	qDebug() << "sha512Cry outData: " << outData;
	QString bodySha512 = QString(outData);
	QString appToken = QString::fromUtf8(m_iotToken.c_str());

	STRUCT_PARA para = TokenCtrl::getParam();
	QString signa = TokenCtrl::getIOTSign(para.AccessKey, para.secretKey, timetampValue, nonceQstring, bodySha512, appToken);
	signa = signa.toUpper();


	QString oldQstring = QUuid::createUuid().toString();
	oldQstring = oldQstring.mid(1, oldQstring.length() - 2);

	QString strUrlPrefix = "https://";
	QString queryLocalRecordsUri = "/open-api/api-aiot/device/queryCloudRecords";
	QString strVersionUrl = strUrlPrefix.append(para.host).append(queryLocalRecordsUri);
	QNetworkRequest request(strVersionUrl);
	DLOG_INFO("here TEST");
	request.setRawHeader("Content-Type", "application/json");
	request.setRawHeader("Version", "v1");
	request.setRawHeader("AppAccessToken", QString(m_iotToken.c_str()).toLatin1());
	request.setRawHeader("AccessKey", para.AccessKey.toLatin1());
	request.setRawHeader("ProductId", para.productId.toLatin1());
	request.setRawHeader("X-TraceId-Header", oldQstring.toLatin1());
	request.setRawHeader("Timestamp", timetampValue.toLatin1());
	request.setRawHeader("Sign", signa.toLatin1());
	request.setRawHeader("Nonce", nonceQstring.toLatin1());

	m_pIotgetCloudRecordsNetWork->setRequestUrl(strVersionUrl);
	QMap<QString, QString> heads;
	heads.insert("Content-Type", "application/json");
	heads.insert("Version", "v1");
	heads.insert("AppAccessToken", QString(m_iotToken.c_str()).toLatin1());
	heads.insert("AccessKey", para.AccessKey.toLatin1());
	heads.insert("ProductId", para.productId.toLatin1());
	heads.insert("X-TraceId-Header", oldQstring.toLatin1());
	heads.insert("Timestamp", timetampValue.toLatin1());
	heads.insert("Sign", signa.toLatin1());
	heads.insert("Nonce", nonceQstring.toLatin1());
	DLOG_INFO("here test2");
	int a = m_pIotgetCloudRecordsNetWork->postRequest(jsonDataChar, heads);
}

void TokenCtrl::getP2pInfo(QString host, QString AccessKey, QString productId, QString secretKey)
{
	STRUCT_PARA tmpPara;
	tmpPara.AccessKey = AccessKey;
	tmpPara.host = host;
	tmpPara.productId = productId;
	tmpPara.secretKey = secretKey;
	setParam(tmpPara);

	QJsonObject jsonObj;
	jsonObj["uniqueId"] = QUuid::createUuid().toString();;
	jsonObj["encryptionMode"] = p2pEncryptMode;

	QJsonDocument jsonDoc(jsonObj);
	QByteArray jsonData = jsonDoc.toJson(QJsonDocument::Compact);

	const char* jsonDataChar = jsonData.constData();

	QString jsonString = QString::fromUtf8(jsonDataChar);

	//remove all Whitespace
	QString jsonStringRemovewhitespace = removeWhitespace(jsonString);
	std::string stdStrRemovewhitespace = jsonStringRemovewhitespace.toStdString();
	const char* bodySha512Removewhitespace = stdStrRemovewhitespace.c_str();
	QString timetampValue = QString::number(QDateTime::currentDateTime().toMSecsSinceEpoch());

	QString nonceQstring = QUuid::createUuid().toString();
	nonceQstring = nonceQstring.mid(1, nonceQstring.length() - 2);

	char *outData = LCOpenSdk_Utils::sha512Cry(bodySha512Removewhitespace);
	qDebug() << "sha512Cry outData: " << outData;
	QString bodySha512 = QString(outData);
	QString appToken = QString::fromUtf8(m_iotToken.c_str());

	STRUCT_PARA para = TokenCtrl::getParam();
	QString signa = TokenCtrl::getIOTSign(para.AccessKey, para.secretKey, timetampValue, nonceQstring, bodySha512, appToken);
	signa = signa.toUpper();


	QString oldQstring = QUuid::createUuid().toString();
	oldQstring = oldQstring.mid(1, oldQstring.length() - 2);

	QString strUrlPrefix = "https://";
	QString queryLocalRecordsUri = "/open-api/api-biz/p2p/info";
	QString strVersionUrl = strUrlPrefix.append(para.host).append(queryLocalRecordsUri);
	QNetworkRequest request(strVersionUrl);
	request.setRawHeader("Content-Type", "application/json");
	request.setRawHeader("Version", "v1");
	request.setRawHeader("AppAccessToken", QString(m_iotToken.c_str()).toLatin1());
	request.setRawHeader("AccessKey", para.AccessKey.toLatin1());
	request.setRawHeader("ProductId", para.productId.toLatin1());
	request.setRawHeader("X-TraceId-Header", oldQstring.toLatin1());
	request.setRawHeader("Timestamp", timetampValue.toLatin1());
	request.setRawHeader("Sign", signa.toLatin1());
	request.setRawHeader("Nonce", nonceQstring.toLatin1());

	m_pIotgetP2pInfoNetWork->setRequestUrl(strVersionUrl);
	QMap<QString, QString> heads;
	heads.insert("Content-Type", "application/json");
	heads.insert("Version", "v1");
	heads.insert("AppAccessToken", QString(m_iotToken.c_str()).toLatin1());
	heads.insert("AccessKey", para.AccessKey.toLatin1());
	heads.insert("ProductId", para.productId.toLatin1());
	heads.insert("X-TraceId-Header", oldQstring.toLatin1());
	heads.insert("Timestamp", timetampValue.toLatin1());
	heads.insert("Sign", signa.toLatin1());
	heads.insert("Nonce", nonceQstring.toLatin1());
	DLOG_INFO("here test2");
	int a = m_pIotgetP2pInfoNetWork->postRequest(jsonDataChar, heads);
}



QString TokenCtrl::getIOTSign(QString ak, QString sk, QString timestamp, QString nonce, QString bodySHA512, QString appAccessToken)
{
	QString stringToSign = "";
	QString str = "";
	if (!bodySHA512.isEmpty()) {
		QString httpMethod = "POST";
		QString httpMethods = httpMethod + "\n";
		stringToSign = httpMethods + bodySHA512;
	} else {
		stringToSign = "POST";
	}
	if (!appAccessToken.isEmpty()) {

		str = ak + appAccessToken + timestamp + nonce + stringToSign;
	} else {
		str = ak + timestamp + nonce + stringToSign;
	}
	std::string strSrc = str.toStdString();
	QString qStr = QString::fromStdString(strSrc);

	std::string secretKey= sk.toStdString();

	//std::string accKey= "1n2jxipm2m5hls4dr4tybywlkt1ajno3";

	QByteArray hmac = QMessageAuthenticationCode::hash(strSrc.c_str(), secretKey.c_str(), QCryptographicHash::Sha512).toHex();
	//QByteArray hmac = QMessageAuthenticationCode::hash(aa.c_str(), secretKey.c_str(), QCryptographicHash::Sha512).toHex();
	return hmac;
}

void TokenCtrl::setParam(structPara para)
{
	inputParam.AccessKey = para.AccessKey;
	inputParam.host = para.host;
	inputParam.productId = para.productId;
	inputParam.secretKey = para.secretKey;
}

STRUCT_PARA TokenCtrl::getParam()
{
	return inputParam;
}

void TokenCtrl::onNetworkDataCallBack(QByteArray strReply, QString strKeyName)
{
	if (strKeyName == "IotToken")
	{
		QJsonParseError jsonError;
		QJsonDocument json = QJsonDocument::fromJson(strReply, &jsonError);
		if (jsonError.error != QJsonParseError::NoError)
		{
			QString strError = jsonError.errorString();
			return;
		}

		if (!json.isObject())
		{
			return;
		}

		std::string appAccessToken = json.object().value("data").toObject().value("appAccessToken").toString().toStdString();
		m_iotToken = appAccessToken;
		OpenApiCtrl::getInstance()->setToken(m_iotToken.c_str());

		/* P2P info and device list are independent, send in parallel */
		getP2pInfo(m_host, m_AccessKey, m_productId, m_secretKey);
		getIOTPlayInfo(m_host, m_AccessKey, m_productId, m_secretKey);
	}
	else if(strKeyName == "IotPlayInfo")
	{
		bool bSucceed = true;
		QJsonParseError jsonError;
		QJsonDocument json = QJsonDocument::fromJson(strReply, &jsonError);
		if (jsonError.error != QJsonParseError::NoError)
		{
			QString strError = jsonError.errorString();
			bSucceed = false;
		}

		if (!json.isObject())
		{
			bSucceed = false;
		}

		QJsonObject root = json.object();
		if (bSucceed) {
			// Check if data field exists
			if (root.contains("data")) {
				// Get the value of data field
				//	Json::Value data = root["data"];
				QJsonObject data = root.value("data").toObject();

				//qDebug() << "data: " << root["data"].toStyledString().c_str();

				// Check if pageData field exists
				if (data.contains("pageData") && data.value("pageData").isArray() && data.value("pageData").toArray().size() > 0) {
					//	if (data.contains("pageData") && data["pageData"].isArray() && data["pageData"].size() > 0) {
					// Get pageData array

					QJsonArray pageData = data.value("pageData").toArray();
					//Json::Value pageData = data["pageData"];
					//qDebug() << "pageData: " << pageData.toStyledString().c_str();
					// Iterate over pageData array
					for (int i = 0; i < pageData.size(); i++) {
						// Check if deviceList field exists
						if (pageData.at(i).toObject().contains("deviceList") && pageData.at(i).toObject().value("deviceList").isArray()) {
							// Get deviceList array
							QJsonArray deviceList = pageData.at(i).toObject().value("deviceList").toArray();
							//Json::Value deviceList = pageData[i]["deviceList"];

							for (int j = 0; j < deviceList.size(); j++)
							{
								DEVICE_INFO deviceinf;

								deviceinf.deviceId = deviceList.at(j).toObject().value("deviceId").toString().toStdString();
								std::string playinfo = deviceList.at(j).toObject().value("playInfo").toString().toStdString();
								qDebug() << "deviceinf.playInfo:" << playinfo.c_str();

								std::string sDevId = deviceinf.deviceId;
								int sDevIdLen = sDevId.length();

								std::string sSalt = deviceinf.deviceId;
								int sSaltLen = sSalt.length();


								LCOpenSDK_Crypter decrypter;
								decrypter.initWithRuleVersion(Dahua::LCOpenSDK::E_RULE_VERSION_LECHANGE);
								char deviceInfo[2048] = { 0 };
								int deviceInfoLen = 0;
								if (Dahua::LCOpenSDK::E_DECRYPT_RESULT_SUCCESS != decrypter.decryptIOTPlayInfo(playinfo.c_str(), playinfo.length(),
									sDevId.c_str(), sDevIdLen,
									sSalt.c_str(), sSaltLen, deviceInfo, deviceInfoLen))
								{
									DLOG_INFO("playInfo decrypter error");
									emit sgnGetPlayInfoReslut(false);
								}

								QJsonDocument json = QJsonDocument::fromJson(QString(deviceInfo).toUtf8().data(), &jsonError);
								std::string decryDa(QString(deviceInfo).toStdString());
								std::string DecryptedPlayInfo = decryDa.substr(0, playinfo.length());
								//qDebug() << "Decrypted playInfo:" << DecryptedPlayInfo.c_str();
								DLOG_INFO("Decrypted playInfo: %s", DecryptedPlayInfo.c_str());
								deviceinf.playInfo = DecryptedPlayInfo;


								////////// tmp decrypt playInfo
								if(0)
								{

									////////////////////
									std::string filePath = "D:\\tmpArcPlugin.txt";
									std::ifstream file(filePath);
									if (!file.is_open()) {
										throw std::runtime_error("Unable to open file: " + filePath);
									}

									// Read file content into string using iterator
									std::string content((std::istreambuf_iterator<char>(file)),
										std::istreambuf_iterator<char>());

									std::string playinfo1 = content;

									file.close();

									////////////////////

									std::string sDevId1 = "AA07D26PAJ00162";
									int sDevIdLen1 = sDevId1.length();

									std::string sSalt1 = sDevId1;
									int sSaltLen1 = sSalt1.length();


									LCOpenSDK_Crypter decrypter;
									decrypter.initWithRuleVersion(Dahua::LCOpenSDK::E_RULE_VERSION_LECHANGE);
									char deviceInfo1[2048] = { 0 };
									int deviceInfoLen1 = 0;
									if (Dahua::LCOpenSDK::E_DECRYPT_RESULT_SUCCESS != decrypter.decryptIOTPlayInfo(playinfo1.c_str(), playinfo1.length(),
										sDevId1.c_str(), sDevIdLen1,
										sSalt1.c_str(), sSaltLen1, deviceInfo1, deviceInfoLen1))
									{
										DLOG_INFO("playInfo decrypter error");
										emit sgnGetPlayInfoReslut(false);
									}

									QJsonDocument json = QJsonDocument::fromJson(QString(deviceInfo1).toUtf8().data(), &jsonError);
									std::string decryDa1(QString(deviceInfo1).toStdString());
									std::string DecryptedPlayInfo = decryDa1.substr(0, playinfo1.length());
								}

								/////////
								QJsonObject devObj = deviceList.at(j).toObject();
								deviceinf.deviceName = devObj.value("deviceName").toString().toStdString();
								deviceinf.deviceModel = devObj.value("deviceModel").toString().toStdString();
								deviceinf.deviceAbility = devObj.value("deviceAbility").toString().toStdString();
								deviceinf.deviceVersion = devObj.value("deviceVersion").toString().toStdString();
								deviceinf.encryptMode = devObj.value("encryptMode").toString().toStdString();
								deviceinf.channelNum = devObj.value("channelNum").toInt();
								deviceinf.accessType = devObj.value("accessType").toString().toStdString();
								deviceinf.deviceStatus = devObj.value("deviceStatus").toString().toStdString();
								deviceinf.source = devObj.value("source").toString().toStdString();
								deviceinf.canBeUpgrade = devObj.value("canBeUpgrade").toBool();
								deviceinf.catalog = devObj.value("catalog").toString().toStdString();

								QJsonArray channelsArray = devObj.value("channels").toArray();
								int channelNum = channelsArray.size();
								for (int k = 0; k < channelsArray.size(); k++)
								{
									IotChannels iotchannel;
									iotchannel.channelPicUrl = channelsArray.at(k).toObject().value("channelPicUrl").toString().toStdString();
									iotchannel.csStatus = channelsArray.at(k).toObject().value("csStatus").toString().toStdString();
									iotchannel.shareFunctions = channelsArray.at(k).toObject().value("shareFunctions").toString().toStdString();
									iotchannel.channelId = channelsArray.at(k).toObject().value("channelId").toString().toStdString();
									iotchannel.channelName = channelsArray.at(k).toObject().value("channelName").toString().toStdString();
									iotchannel.channelAbility = channelsArray.at(k).toObject().value("channelAbility").toString().toStdString();
									iotchannel.lastOffLineTime = channelsArray.at(k).toObject().value("lastOffLineTime").toString().toStdString();
									iotchannel.channelStatus = channelsArray.at(k).toObject().value("channelStatus").toString().toStdString();
									deviceinf.iotChannel.push_back(iotchannel);
								}
								deviceVec.push_back(deviceinf);
							}
						}
					}
				}
				else {
					qDebug() << "pageData not exist or pageData is empty !\n";
				}
			}
			emit sgnGetPlayInfoReslut(true);
		}
		else {
			DLOG_INFO("playInfo get respose error");
			emit sgnGetPlayInfoReslut(false);
			qDebug() << "FUll response with playInfo Parse failed!\n";
		}
	}
	else if (strKeyName == "IotGetDeviceRecord")
	{
		bool bSucceed = true;
		QJsonParseError jsonError;
		QJsonDocument json = QJsonDocument::fromJson(strReply, &jsonError);
		if (jsonError.error != QJsonParseError::NoError)
		{
			QString strError = jsonError.errorString();
			bSucceed = false;
		}

		if (!json.isObject())
		{
			bSucceed = false;
		}

		QJsonObject root = json.object();
		if (bSucceed) 
		{
			//setLocalDeviceRecords(root);
			if (m_threadCtrlPtr)
			{

				int size = 0;
				if (root.contains("success") && root["success"].toBool())
				{
					if (!root.contains("data") || !root["data"].isObject()) {
						qDebug() << "Missing or invalid 'data' field";
						return;
					}
					QJsonObject dataObj = root["data"].toObject();
					setLocalDeviceRecords(dataObj);

					if (!dataObj.contains("records") || !dataObj["records"].isArray()) {
						qDebug() << "Missing or invalid 'records' array";
						return;
					}
					QJsonArray recordsArray = dataObj["records"].toArray();
					size = recordsArray.size();

					//emit m_threadCtrlPtr->resultReady(size);
					emit m_threadCtrlPtr->sendDeviceRecords(root);
				}
			}
		}
		else
		{
			DLOG_ERR("parse IotGetDeviceRecord json failed !");
		}
	}
	else if (strKeyName == "IotGetCloudRecord")
	{
		bool bSucceed = true;
		QJsonParseError jsonError;
		QJsonDocument json = QJsonDocument::fromJson(strReply, &jsonError);
		if (jsonError.error != QJsonParseError::NoError)
		{
			QString strError = jsonError.errorString();
			bSucceed = false;
		}

		if (!json.isObject())
		{
			bSucceed = false;
		}

		QJsonObject root = json.object();
		if (bSucceed)
		{
			//setCloudRecords(root);
			if (m_threadCtrlPtr)
			{
				int size = 0;
				if (root.contains("success") && root["success"].toBool())
				{
					if (!root.contains("data") || !root["data"].isObject()) {
						qDebug() << "Missing or invalid 'data' field";
						return;
					}
					QJsonObject dataObj = root["data"].toObject();
					setCloudRecords(dataObj);

					if (!dataObj.contains("records") || !dataObj["records"].isArray()) {
						qDebug() << "Missing or invalid 'records' array";
						return;
					}
					QJsonArray recordsArray = dataObj["records"].toArray();
					size = recordsArray.size();

					//emit m_threadCtrlPtr->resultReady(size);
					emit m_threadCtrlPtr->sendCloudRecords(root);
				}
			}
		}
		else
		{
			emit sgnGetP2pInfoReslut(false);
			DLOG_ERR("parse IotGetCloudRecord json failed !");
		}
	}
	else if (strKeyName == "IotGetP2pInfo")
	{
		bool bSucceed = true;
		QJsonParseError jsonError;
		QJsonDocument json = QJsonDocument::fromJson(strReply, &jsonError);
		if (jsonError.error != QJsonParseError::NoError)
		{
			QString strError = jsonError.errorString();
			bSucceed = false;
		}

		if (!json.isObject())
		{
			bSucceed = false;
		}

		QJsonObject root = json.object();
		if (bSucceed)
		{
			int size = 0;
			if (root.contains("success") && root["success"].toBool())
			{
				if (!root.contains("data") || !root["data"].isObject()) {
					emit sgnGetP2pInfoReslut(false);
					qDebug() << "Missing or invalid 'data' field";
					return;
				}
				QJsonObject dataObj = root["data"].toObject();
				setCloudRecords(dataObj);

				if (!dataObj.contains("p2pKey") || !dataObj.contains("p2pInfo")) {
					qDebug() << "Missing or invalid IotGetP2pInfo data";
					emit sgnGetP2pInfoReslut(false);
					return;
				}
				QString p2pKey = dataObj["p2pKey"].toString();
				QString p2pInfo = dataObj["p2pInfo"].toString();

				LCOpenSDK_LoginManager::getInstance()->configureP2PServers(p2pKey.toUtf8().constData(), p2pInfo.toUtf8().constData(), p2pEncryptMode);

				//emit m_threadCtrlPtr->resultReady(size);
			}
		}
		else
		{
			emit sgnGetP2pInfoReslut(false);
			DLOG_INFO("parse IotGetP2pInfo json failed !");
		}
	}
	else
	{
		qDebug() << "strKeyName not exist !\n";
	}
}
void TokenCtrl::onNetworkFinished(QString strKeyName)
{

}

void TokenCtrl::setLocalDeviceRecords(QJsonObject localDeviceRecord)
{
	queryLocalDeviceRecords = localDeviceRecord;
}

QJsonObject TokenCtrl::getLocalDeviceRecords()
{
	return queryLocalDeviceRecords;
}

void TokenCtrl::setCloudRecords(QJsonObject cloudRecord)
{
	queryCloudRecords = cloudRecord;
}

QJsonObject TokenCtrl::getCloudRecords()
{
	return queryCloudRecords;
}

void TokenCtrl::onNetworkError(Common::NetworkError_t, QString, QString strKeyName)
{
	DLOG_INFO("get respose error [%s]",strKeyName.toStdString().c_str());

	emit sgnGetPlayInfoReslut(false);
}