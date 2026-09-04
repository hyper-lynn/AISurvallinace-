#include "LCOpenApi/ShareDeviceList.h"
#include "LCOpenApi/BeAuthDeviceList.h"
#include "LCOpenApi/CheckDeviceBindOrNot.h"
#include "LCOpenApi/DeviceOnline.h"
#include "LCOpenApi/BindDevice.h"
#include "LCOpenApi/UnBindDevice.h"
#include "LCOpenApi/UnBindDeviceInfo.h"
#include "LCOpenApi/BindDeviceInfo.h"
#include "LCOpenApi/ModifyDeviceAlarmStatus.h"
#include "LCOpenApi/SetStorageStrategy.h"
#include "LCOpenApi/ModifyDevicePwd.h"
#include "LCOpenApi/UpgradeDevice.h"
#include "LCOpenApi/QueryLocalRecordNum.h"
#include "LCOpenApi/QueryLocalRecords.h"
#include "LCOpenApi/QueryCloudRecordNum.h"
#include "LCOpenApi/QueryCloudRecords.h"
#include "LCOpenApi/DeleteAlarmMessage.h"
#include "LCOpenApi/GetAlarmMessage.h"
#include "LCOpenApi/ControlPTZ.h"
#include "LCOpenApi/DeviceVersionList.h"
#include "LCOpenApi/GetStorageStrategy.h"
#include "Src/Utils/global.h"
#include "lcopensdk_loginmanager/LCOpenSDK_LoginManager.h"
#include "lcopensdk_utils/LCOpenSdk_Utils.h"
#include "OpenApiCtrl.h"
#include "DevicesListCtrl.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
extern bool g_isReleasedForOverseas;

#define PROPERTY_TLS_ENABLE_REFID								"14500"								// IOT 物模型TLS使能

OpenApiCtrl::OpenApiCtrl()
	: m_OpenApiHandle(NULL)
	, m_IsGetTokenOK(false)
{

}

OpenApiCtrl::~OpenApiCtrl()
{
	unInit();
}

OpenApiCtrl* OpenApiCtrl::getInstance()
{
	static OpenApiCtrl instance;
	return &instance;
}

void OpenApiCtrl::init(const OPEN_API_INIT_PARAM* param)
{
	if (NULL == param)
	{
		return;
	}

	m_OpenApiHandle = LCOpenSDK_Api::GetInstance();
	m_OpenApiHandle->initOpenApiEx(param->host.toLatin1().data(), param->port, param->caPath.toLatin1().data(), m_Token.toStdString().c_str(), param->appID.toLatin1().data(), param->appSecret.toLatin1().data());

	return;
}

void OpenApiCtrl::unInit()
{
	return;
}

QString OpenApiCtrl::getToken()
{
	if (!m_IsGetTokenOK)
	{
		return QString();
	}

	return m_Token;
}

int OpenApiCtrl::getAccessToken(const TOKEN_PARAMETERS* param, OUT QString& ret_code, OUT QString& ret_msg)
{
	int ret = RET_OK;
	m_IsGetTokenOK = false;
	m_appId = param->appId;
	m_appSecret = param->appSecret;
	ret = TokenCtrl::getAccessToken(param, m_Token, ret_code, ret_msg);
	if (RET_OK == ret)
	{
		m_IsGetTokenOK = true;
	}

	return ret;
}

int OpenApiCtrl::getUserToken(const TOKEN_PARAMETERS* param, OUT QString& ret_code, OUT QString& ret_msg)
{
	int ret = RET_OK;
	m_IsGetTokenOK = false;

	ret = TokenCtrl::getUserToken(param, m_Token, ret_code, ret_msg);
	if (RET_OK == ret)
	{
		m_IsGetTokenOK = true;
	}

	return ret;
}

int OpenApiCtrl::userBindSms(const TOKEN_PARAMETERS* param, OUT QString& ret_code, OUT QString& ret_msg)
{
	return TokenCtrl::userBindSms(param, ret_code, ret_msg);
}

int OpenApiCtrl::userBind(const USERBIND_PARAMETERS* param, OUT QString& ret_code, OUT QString& ret_msg)
{
	return TokenCtrl::userBind(param, ret_code, ret_msg);
}

bool OpenApiCtrl::getDevicesListP2PPort(ChannelInfoList* channelInfoList)
{
	bool ret = 0;

	if (NULL == channelInfoList)
	{
		DLOG("Param Error!!!\n");
		return ret;
	}

	if (!m_IsGetTokenOK)
	{
		DLOG("get Token Failed!!!\n");
		return ret;
	}

	for (int i = 0; i < channelInfoList->size(); ++i)
	{
		if (channelInfoList->at(i)->deviceStatus == "online")
		{
			channelInfoList->at(i)->p2pPort = LCOpenSDK_LoginManager::getInstance()->getP2pPort(m_Token.toLatin1().data(), channelInfoList->at(i)->playToken.toStdString().c_str(), channelInfoList->at(i)->deviceId.toStdString().c_str(), 5000);
		}
	}

	ret = true;
	return ret;
}

bool OpenApiCtrl::getDevicesList(ChannelInfoList* channelInfoList)
{
	bool ret = 0;

	if (NULL == channelInfoList)
	{
		DLOG("Param Error!!!\n");
		return ret;
	}

	if (!m_IsGetTokenOK)
	{
		DLOG("get Token Failed!!!\n");
		return ret;
	}

	//分页查询 查到最后一页返回0
	int page = 1;
	QJsonArray DeviceArray;
	while (1)
	{
		std::string strUri("/openapi/listDeviceDetailsByPage");
		LCOpenApiResponse pHsRes = { 0 };
		QJsonObject reqJson;
		reqJson.insert("pageSize", 10);
		reqJson.insert("page", page);
		reqJson.insert("token", m_Token.toLatin1().data());
		reqJson.insert("source", "bindAndShare");
		QJsonDocument requestDocument;
		requestDocument.setObject(reqJson);
		QByteArray requestBa = requestDocument.toJson(QJsonDocument::Compact);
		QString strBody(requestBa);
		ret = m_OpenApiHandle->requestWithURL(strUri.c_str(), strBody.toStdString().c_str(), &pHsRes, 10, 0);
		if (0 != ret)
		{
			DLOG("request failed[%d]\n", ret);
			ret = HTTP_ERR;
			page++;
			continue;
		}

		int code = pHsRes.code;
		const char *desc = pHsRes.desc.cstr;
		char * ret_code = pHsRes.ret_code.cstr;
		if (HTTP_OK != code)
		{
			ret = HTTP_ERR;
			DLOG("HTTP_ERR[%d]\n", code);
			page++;
			continue;
		}
		//解析Json
		QJsonParseError jsonError;
		QByteArray responseBa = QString(CToS(pHsRes.content)).toUtf8();
		QJsonDocument doucment = QJsonDocument::fromJson(responseBa, &jsonError);
		if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError))
		{
			QJsonObject object = doucment.object();
			QJsonObject resultObj = object.value("result").toObject();
			QJsonObject dataObj = resultObj.value("data").toObject();

			if (0 == dataObj.value("count").toDouble())
			{
				break;
			}

			if (dataObj.contains("deviceList"))
			{
				QJsonValue devicesVal = dataObj.value("deviceList");
				if (devicesVal.isArray())
				{
					QJsonArray devicesArray = devicesVal.toArray();
					for (int i = 0; i < devicesArray.size(); ++i)
					{
						QJsonValue deviceValue = devicesArray.at(i);
						if (deviceValue.isObject())
						{
							QJsonObject channelsObj = deviceValue.toObject();
							if (channelsObj.contains("channelList"))
							{
								QJsonValue channelsVal = channelsObj.value("channelList");
								if (channelsVal.isArray())
								{
									QJsonArray channelsArray = channelsVal.toArray();
									for (int j = 0; j < channelsArray.size(); ++j)
									{
										ChannelInfo* channelInfo = new (std::nothrow) ChannelInfo();
										QJsonObject channelObj = channelsArray.at(j).toObject();
										QJsonObject DeviceJson;
										//设备信息
										channelInfo->deviceId = deviceValue.toObject().value("deviceId").toString();
										DeviceJson.insert("Sn", channelInfo->deviceId);
										channelInfo->productId = deviceValue.toObject().value("productId").toString();
										channelInfo->canBeUpgrade = deviceValue.toObject().value("canBeUpgrade").toBool();
										channelInfo->accessType = deviceValue.toObject().value("accessType").toString();
										channelInfo->deviceVersion = deviceValue.toObject().value("deviceVersion").toString();
										channelInfo->playToken = deviceValue.toObject().value("playToken").toString();
										DeviceJson.insert("PlayToken", channelInfo->playToken);
										channelInfo->brand = deviceValue.toObject().value("brand").toString();
										channelInfo->encryptMode = deviceValue.toObject().value("encryptMode").toString();
										channelInfo->decryptKey = channelInfo->deviceId;
										channelInfo->lastOffLineTime = deviceValue.toObject().value("lastOffLineTime").toString();
										channelInfo->deviceName = deviceValue.toObject().value("deviceName").toString();
										channelInfo->devicePassword = deviceValue.toObject().value("devicePassword").toString();
										channelInfo->deviceStatus = deviceValue.toObject().value("deviceStatus").toString();
										channelInfo->deviceModel = deviceValue.toObject().value("deviceModel").toString();
										channelInfo->catalog = deviceValue.toObject().value("catalog").toString();
										channelInfo->deviceAbility = deviceValue.toObject().value("deviceAbility").toString();
										channelInfo->channelNum = deviceValue.toObject().value("channelNum").toDouble();
										channelInfo->source = deviceValue.toObject().value("source").toString();
										channelInfo->isSubDevice = deviceValue.toObject().value("isSubDevice").toBool();
										channelInfo->sdcardStatus = deviceValue.toObject().value("sdcardStatus").toString();
										channelInfo->tlsEnable = deviceValue.toObject().value("tlsEnable").toBool();
										channelInfo->multiFlag = deviceValue.toObject().value("multiFlag").toBool();

										//通道信息
										channelInfo->channelPicUrl = channelObj.value("channelPicUrl").toString();
										channelInfo->csStatus = channelObj.value("csStatus").toString();
										channelInfo->shareFunctions = channelObj.value("shareFunctions").toString();
										channelInfo->channelId = channelObj.value("channelId").toDouble();
										channelInfo->channelName = channelObj.value("channelName").toString();
										channelInfo->channelAbility = channelObj.value("channelAbility").toString();
										channelInfo->channelStatus = channelObj.value("channelStatus").toString();
										channelInfo->channelLastOffLineTime = channelObj.value("lastOffLineTime").toString();
										channelInfo->movable = channelObj.value("movable").toBool();

										if (channelInfo->multiFlag)
										{
											//双目设备固定镜头没有14500，不能走物模型
										}
										else if (!channelInfo->productId.isEmpty())
										{
											//IOT设备从物模型中获取
											channelInfo->tlsEnable = getIotDeviceProperties(channelInfo->deviceId, channelInfo->productId, PROPERTY_TLS_ENABLE_REFID, channelInfo->channelId);				
										}
					
										if (channelInfo->deviceStatus == "online")
										{
											DeviceArray.append(DeviceJson);
											QJsonArray DeviceArrayP2P;
											DeviceArrayP2P.append(DeviceJson);
											QJsonDocument requestDocument;
											requestDocument.setArray(DeviceArrayP2P);
											QByteArray requestSDKBa = requestDocument.toJson(QJsonDocument::Compact);
											QString strBodyP2P = requestSDKBa.toStdString().c_str();
											//P2P预打洞
											LCOpenSDK_LoginManager::getInstance()->addDevices(m_Token.toLatin1().data(), strBodyP2P.toStdString().c_str());
										}
										channelInfoList->append(channelInfo);
									}
								}
							}
						}
					}
				}
			}
		}
		page++;
		if (g_isReleasedForOverseas)
		{
			ret = true;
			break;
		}
		ret = true;
		LCOPENAPI_DESTROY_OBJECT(&pHsRes);
	}

	if (channelInfoList->size() > 0)
	{
		QJsonDocument requestDocument;
		requestDocument.setArray(DeviceArray);
		QByteArray requestSDKBa = requestDocument.toJson(QJsonDocument::Compact);
		QString strBody(requestSDKBa);
		//拉流速度优化
		m_OpenApiHandle->loginStreamServers(m_Token.toLatin1().data(), strBody.toStdString().c_str());
		ret = true;
	}

	return ret;
}

bool OpenApiCtrl::getIotDeviceProperties(QString deviceId,QString productId,QString properties, int channelId)
{
	bool bRet = false;
	//以TLS为参考
	do
	{
		std::string strUri("/openapi/getIotDeviceProperties");
		LCOpenApiResponse pHsRes = { 0 };
		QJsonObject reqJson;
		reqJson.insert("deviceId", deviceId.toStdString().c_str());
		reqJson.insert("productId", productId.toStdString().c_str());
		reqJson.insert("token", m_Token.toLatin1().data());
		reqJson.insert("channelId", channelId);
		QJsonArray propertiesArray;
		propertiesArray.append(QJsonValue(properties.toStdString().c_str()));
		reqJson.insert("properties",propertiesArray);
		QJsonDocument requestDocument;
		requestDocument.setObject(reqJson);
		QByteArray requestBa = requestDocument.toJson(QJsonDocument::Compact);
		QString strBody(requestBa);
		int ret = m_OpenApiHandle->requestWithURL(strUri.c_str(), strBody.toStdString().c_str(), &pHsRes, 10, 0);
	
		if (0 != ret)
		{
			DLOG("request failed[%d]\n", ret);
			break;
		}

		int code = pHsRes.code;
		const char *desc = pHsRes.desc.cstr;
		char * ret_code = pHsRes.ret_code.cstr;
		if (HTTP_OK != code)
		{
			ret = HTTP_ERR;
			DLOG("HTTP_ERR[%d]\n", code);
			break;
		}

		if (0 != strcmp(ret_code, "0"))
		{
			DLOG("BUSINESS_ERR[%s]\n", ret_code);
			break;
		}

		QJsonParseError jsonError;
		QByteArray responseBa = QString(CToS(pHsRes.content)).toUtf8();
		QJsonDocument doucment = QJsonDocument::fromJson(responseBa, &jsonError);
		if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError))
		{
			QJsonObject object = doucment.object();
			QJsonObject resultObj = object.value("result").toObject();
			QJsonObject dataObj = resultObj.value("data").toObject();
			QJsonObject propertiesObj = dataObj.value("properties").toObject();
			if (propertiesObj.value(properties).toString() == "1" || propertiesObj.value(properties).toInt() == 1)
			{
				bRet = true;
			}
		}
		LCOPENAPI_DESTROY_OBJECT(&pHsRes);
	} while (0);
	return bRet;
}

QString OpenApiCtrl::checkDeviceBindOrNot(QString deviceId, bool& isMine, bool& isBind)
{
	QString ret = "OK";

	if (!m_IsGetTokenOK)
	{
		ret = "get token error";
		return ret;
	}

	/* CheckDeviceBindOrNot */
	CheckDeviceBindOrNotRequest* req;
	CheckDeviceBindOrNotResponse* resp;
	req = LCOPENAPI_INIT(CheckDeviceBindOrNotRequest);
	resp = LCOPENAPI_INIT(CheckDeviceBindOrNotResponse);
	req->data.token = CS(m_Token.toLatin1().data());
	req->data.deviceId = CS(deviceId.toLatin1().data());
	if (0 == m_OpenApiHandle->request(req, resp, 15))
	{
		if (HTTP_OK == resp->base.code)
		{
			if (!strcmp("0", resp->base.ret_code.cstr))
			{
				isMine = resp->data.isMine;
				isBind = resp->data.isBind;
			}
			else
			{
				ret = QString(resp->base.ret_code.cstr) + " " +QString(resp->base.ret_msg.cstr);
			}
		}
		else
		{
			ret = QString::number(resp->base.code);
		}
	}
	else
	{
		ret = "request failed";
	}
	LCOPENAPI_DESTROY(req);
	LCOPENAPI_DESTROY(resp);
	/* CheckDeviceBindOrNot */

	return ret;
}

QString OpenApiCtrl::checkDeviceOnlineOrNot(QString deviceId, bool& isOnline)
{
	QString ret = "OK";

	if (!m_IsGetTokenOK)
	{
		ret = "get token error";
		return ret;
	}

	DeviceOnlineRequest* req;
	DeviceOnlineResponse* resp;
	req = LCOPENAPI_INIT(DeviceOnlineRequest);
	resp = LCOPENAPI_INIT(DeviceOnlineResponse);
	req->data.token = CS(m_Token.toLatin1().data());
	req->data.deviceId = CS(deviceId.toLatin1().data());
	if (0 == m_OpenApiHandle->request(req, resp, 10))
	{
		if (HTTP_OK == resp->base.code)
		{
			if (!strcmp("0", resp->base.ret_code.cstr))
			{
				if (NULL == resp->data.onLine.cstr || !strcmp("0", resp->data.onLine.cstr))
				{
					isOnline = false;
				}
				else
				{
					isOnline = true;
				}
			}
			else
			{
				ret = QString(resp->base.ret_code.cstr) + " " + QString(resp->base.ret_msg.cstr);
			}
		}
		else
		{
			ret = QString::number(resp->base.code);
		}
	}
	else
	{
		ret = "request failed";
	}
	LCOPENAPI_DESTROY(req);
	LCOPENAPI_DESTROY(resp);

	return ret;
}

QString OpenApiCtrl::bindDevice(QString deviceId, QString code)
{
	QString ret = "OK";

	if (!m_IsGetTokenOK)
	{
		ret = "get token error";
		return ret;
	}

	BindDeviceRequest* req;
	BindDeviceResponse* resp;
	req = LCOPENAPI_INIT(BindDeviceRequest);
	resp = LCOPENAPI_INIT(BindDeviceResponse);
	req->data.token = CS(m_Token.toLatin1().data());
	req->data.deviceId = CS(deviceId.toLatin1().data());
	req->data.code = CS(code.toLatin1().data());
	do
	{
		if (RET_OK != m_OpenApiHandle->request(req, resp, 60))
		{
			ret = "request failed";
			break;
		}

		if (HTTP_OK != resp->base.code)
		{
			ret = QString::number(resp->base.code);
			break;
		}

		if (0 != strcmp(resp->base.ret_code.cstr, "0"))
		{
			ret = QString(resp->base.ret_code.cstr) + " " + QString(resp->base.ret_msg.cstr);
			break;
		}

	} while (0);

	LCOPENAPI_DESTROY(req);
	LCOPENAPI_DESTROY(resp);

	return ret;
}

QString OpenApiCtrl::unBindDevice(QString deviceId)
{
	QString Ret = "OK";
	do
	{
		std::string strUri("/openapi/unBindDevice");
		LCOpenApiResponse pHsRes = { 0 };
		QJsonObject reqJson;
		reqJson.insert("deviceId", deviceId.toLatin1().data());
		reqJson.insert("token", m_Token.toLatin1().data());
		QJsonDocument requestDocument;
		requestDocument.setObject(reqJson);
		QByteArray requestBa = requestDocument.toJson(QJsonDocument::Compact);
		QString strBody(requestBa);
		int ret = m_OpenApiHandle->requestWithURL(strUri.c_str(), strBody.toStdString().c_str(), &pHsRes, 10, 0);
		if (0 != ret)
		{
			DLOG("request failed[%d]\n", ret);
			Ret = "return failed";
			break;
		}

		int code = pHsRes.code;
		const char *desc = pHsRes.desc.cstr;
		const char *ret_code = pHsRes.ret_code.cstr;
		if (HTTP_OK != code)
		{
			ret = HTTP_ERR;
			Ret = "request failed";
			DLOG("HTTP_ERR[%d]\n", code);
			break;
		}


		if (0 != strcmp(ret_code, "0"))
		{
			Ret = QString(ret_code) + " " + QString(pHsRes.ret_msg.cstr);
			break;
		}

		LCOPENAPI_DESTROY_OBJECT(&pHsRes);
	} while (0);
	return Ret;

}

QString OpenApiCtrl::unBindDeviceInfo(QString deviceId, QString &ability,QString &productId)
{
	QString sRet;
	if (!m_IsGetTokenOK)
	{
		sRet = "get token error";
		return sRet;
	}

	do 
	{
		std::string strUri("/openapi/unBindDeviceInfo");
		LCOpenApiResponse pHsRes = { 0 };
		QJsonObject reqJson;
		reqJson.insert("deviceId", deviceId.toStdString().c_str());
		reqJson.insert("token", m_Token.toLatin1().data());
		QJsonDocument requestDocument;
		requestDocument.setObject(reqJson);
		QByteArray requestBa = requestDocument.toJson(QJsonDocument::Compact);
		QString strBody(requestBa);
		int ret = m_OpenApiHandle->requestWithURL(strUri.c_str(), strBody.toStdString().c_str(), &pHsRes, 10, 0);
		if (0 != ret)
		{
			DLOG("request failed[%d]\n", ret);
			sRet = "request failed!";
		}
		int code = pHsRes.code;
		const char *desc = pHsRes.desc.cstr;
		char * ret_code = pHsRes.ret_code.cstr;
		if (HTTP_OK != code)
		{
			sRet = "request failed";
			DLOG("HTTP_ERR[%d]\n", code);
			break;
		}

		if (0 != strcmp(ret_code, "0"))
		{
			sRet = QString(pHsRes.ret_code.cstr) + " " + QString(pHsRes.ret_msg.cstr);
			DLOG("BUSINESS_ERR[%s]\n", ret_code);
			break;
		}

		QJsonParseError jsonError;
		QByteArray responseBa = QString(CToS(pHsRes.content)).toUtf8();
		QJsonDocument doucment = QJsonDocument::fromJson(responseBa, &jsonError);
		if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError))
		{
			QJsonObject object = doucment.object();
			QJsonObject resultObj = object.value("result").toObject();
			QJsonObject dataObj = resultObj.value("data").toObject();
			ability = dataObj.value("ability").toString();
			productId = dataObj.value("productId").toString();

			sRet = "OK";
		}
		LCOPENAPI_DESTROY_OBJECT(&pHsRes);
	} while (0);
	return sRet;
}


QString OpenApiCtrl::getDeviceCameraStatus(QString deviceId, int channelId, QString enableType, QString &status)
{
	QString sRet;
	if (!m_IsGetTokenOK)
	{
		sRet = "get token error";
		return sRet;
	}

	ChannelInfo* ChannelInfo = DevicesListCtrl::getInstance()->getChannelInfoByChannel(deviceId, channelId);
	do
	{
		if (ChannelInfo->multiFlag)
		{
			enableType = "crMotionDetect";
		}

		std::string strUri("/openapi/getDeviceCameraStatus");
		LCOpenApiResponse pHsRes = { 0 };
		QJsonObject reqJson;
		reqJson.insert("deviceId", deviceId.toStdString().c_str());
		reqJson.insert("channelId", channelId);
		reqJson.insert("token", m_Token.toLatin1().data());
		reqJson.insert("enableType", enableType.toStdString().c_str());
		QJsonDocument requestDocument;
		requestDocument.setObject(reqJson);
		QByteArray requestBa = requestDocument.toJson(QJsonDocument::Compact);
		QString strBody(requestBa);
		int ret = m_OpenApiHandle->requestWithURL(strUri.c_str(), strBody.toStdString().c_str(), &pHsRes, 10, 0);
		if (0 != ret)
		{
			DLOG("request failed[%d]\n", ret);
			sRet = "request failed!";
			break;
		}
		
		int code = pHsRes.code;
		const char *desc = pHsRes.desc.cstr;
		char * ret_code = pHsRes.ret_code.cstr;
		if (HTTP_OK != code)
		{
			sRet = "request failed";
			DLOG("HTTP_ERR[%d]\n", code);
			break;
		}

		if (0 != strcmp(ret_code, "0"))
		{
			sRet = QString(pHsRes.ret_code.cstr) + " "+ QString(pHsRes.ret_msg.cstr);
			DLOG("BUSINESS_ERR[%s]\n", ret_code);
			break;
		}

		QJsonParseError jsonError;
		QByteArray responseBa = QString(CToS(pHsRes.content)).toUtf8();
		QJsonDocument doucment = QJsonDocument::fromJson(responseBa, &jsonError);
		if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError))
		{
			QJsonObject object = doucment.object();
			QJsonObject resultObj = object.value("result").toObject();
			QJsonObject dataObj = resultObj.value("data").toObject();
			QString respEnableType = dataObj.value("enableType").toString();

			if (respEnableType == enableType)
			{
				status = dataObj.value("status").toString();
			}
			sRet = "OK";
		}
		LCOPENAPI_DESTROY_OBJECT(&pHsRes);
	} while (0);
	return sRet;
}

QString OpenApiCtrl::setDeviceCameraStatus(QString deviceId, int channelId, QString enableType, bool enable)
{
	QString sRet;
	if (!m_IsGetTokenOK)
	{
		sRet = "get token error";
		return sRet;
	}
	ChannelInfo* ChannelInfo = DevicesListCtrl::getInstance()->getChannelInfoByChannel(deviceId, channelId);
	do
	{
		if (ChannelInfo->multiFlag)
		{
			enableType = "crMotionDetect";
		}
	
		std::string strUri("/openapi/setDeviceCameraStatus");
		LCOpenApiResponse pHsRes = { 0 };
		QJsonObject reqJson;
		reqJson.insert("deviceId", deviceId.toStdString().c_str());
		reqJson.insert("channelId", channelId);
		reqJson.insert("token", m_Token.toLatin1().data());
		reqJson.insert("enableType", enableType.toStdString().c_str());
		reqJson.insert("enable", enable);
		QJsonDocument requestDocument;
		requestDocument.setObject(reqJson);
		QByteArray requestBa = requestDocument.toJson(QJsonDocument::Compact);
		QString strBody(requestBa);
		int ret = m_OpenApiHandle->requestWithURL(strUri.c_str(), strBody.toStdString().c_str(), &pHsRes, 10, 0);
		if (0 != ret)
		{
			DLOG("request failed[%d]\n", ret);
			sRet = "request failed!";
		}

		int code = pHsRes.code;
		const char *desc = pHsRes.desc.cstr;
		char * ret_code = pHsRes.ret_code.cstr;
		if (HTTP_OK != code)
		{
			sRet = "request failed!";
			DLOG("HTTP_ERR[%d]\n", code);
			break;
		}

		if (0 != strcmp(ret_code, "0"))
		{
			sRet = QString(pHsRes.ret_code.cstr) + " " + QString(pHsRes.ret_msg.cstr);
			DLOG("BUSINESS_ERR[%s]\n", ret_code);
			break;
		}
		sRet = "OK";
		DLOG("setDeviceCameraStatus success\n");
		LCOPENAPI_DESTROY_OBJECT(&pHsRes);		
	} while (0);
	return sRet;
}

/*根据设备ID获取设备信息*/
bool OpenApiCtrl::searchDeviceByID(QString deviceID, ChannelInfoList* channelInfoList)
{
	printf("\n==OpenApiCtrl::searchDeviceByID param deviceID=%s\n", deviceID.toStdString().c_str());

	bool ret = false;
	if (NULL == channelInfoList)
	{
		DLOG("Param Error!!!\n");
		return ret;
	}
	if (!m_IsGetTokenOK)
	{
		ret = "get token error";
		return ret;
	}

	do
	{
		std::string strUri("/openapi/listDeviceDetailsByIds");
		LCOpenApiResponse pHsRes = { 0 };
		QJsonObject reqJson;
		reqJson.insert("token", m_Token.toLatin1().data());

		QJsonArray deviceListArrayJson;
		QJsonObject reqDeviceInfo;
		reqDeviceInfo.insert("deviceId", deviceID.toStdString().c_str());
		deviceListArrayJson.append(reqDeviceInfo);
		reqJson.insert("deviceList", deviceListArrayJson);

		QJsonDocument requestDocument;
		requestDocument.setObject(reqJson);
		QByteArray requestBa = requestDocument.toJson(QJsonDocument::Compact);
		QString strBody(requestBa);
		ret = m_OpenApiHandle->requestWithURL(strUri.c_str(), strBody.toStdString().c_str(), &pHsRes, 10, 0);
		if (0 != ret)
		{
			DLOG("request failed[%d]\n", ret);
			ret = HTTP_ERR;
			break;
		}

		int code = pHsRes.code;
		const char *desc = pHsRes.desc.cstr;
		char * ret_code = pHsRes.ret_code.cstr;
		if (HTTP_OK != code)
		{
			ret = HTTP_ERR;
			DLOG("HTTP_ERR[%d]\n", code);
			break;
		}

		//解析Json
		QJsonParseError jsonError;
		QByteArray responseBa = QString(CToS(pHsRes.content)).toUtf8();
		QJsonDocument doucment = QJsonDocument::fromJson(responseBa, &jsonError);
		if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError))
		{
			QJsonObject object = doucment.object();
			QJsonObject resultObj = object.value("result").toObject();
			QJsonObject dataObj = resultObj.value("data").toObject();

			if (0 == dataObj.value("count").toDouble())
			{
				break;
			}

			if (dataObj.contains("deviceList"))
			{
				QJsonValue devicesVal = dataObj.value("deviceList");
				if (devicesVal.isArray())
				{
					QJsonArray devicesArray = devicesVal.toArray();
					for (int i = 0; i < devicesArray.size(); ++i)
					{
						QJsonValue deviceValue = devicesArray.at(i);
						if (deviceValue.isObject())
						{
							QJsonObject channelsObj = deviceValue.toObject();
							if (channelsObj.contains("channelList"))
							{
								QJsonValue channelsVal = channelsObj.value("channelList");
								if (channelsVal.isArray())
								{
									QJsonArray channelsArray = channelsVal.toArray();
									for (int j = 0; j < channelsArray.size(); ++j)
									{
										ChannelInfo* channelInfo = new (std::nothrow) ChannelInfo();
										QJsonObject channelObj = channelsArray.at(j).toObject();
										//设备信息
										channelInfo->deviceId = deviceValue.toObject().value("deviceId").toString();
										channelInfo->productId = deviceValue.toObject().value("productId").toString();
										channelInfo->canBeUpgrade = deviceValue.toObject().value("canBeUpgrade").toBool();
										channelInfo->accessType = deviceValue.toObject().value("accessType").toString();
										channelInfo->deviceVersion = deviceValue.toObject().value("deviceVersion").toString();
										channelInfo->playToken = deviceValue.toObject().value("playToken").toString();
										channelInfo->brand = deviceValue.toObject().value("brand").toString();
										channelInfo->encryptMode = deviceValue.toObject().value("encryptMode").toString();
										channelInfo->decryptKey = channelInfo->deviceId;
										channelInfo->lastOffLineTime = deviceValue.toObject().value("lastOffLineTime").toString();
										channelInfo->deviceName = deviceValue.toObject().value("deviceName").toString();
										channelInfo->devicePassword = deviceValue.toObject().value("devicePassword").toString();
										channelInfo->deviceStatus = deviceValue.toObject().value("deviceStatus").toString();
										channelInfo->deviceModel = deviceValue.toObject().value("deviceModel").toString();
										channelInfo->catalog = deviceValue.toObject().value("catalog").toString();
										channelInfo->deviceAbility = deviceValue.toObject().value("deviceAbility").toString();
										channelInfo->channelNum = deviceValue.toObject().value("channelNum").toDouble();
										channelInfo->source = deviceValue.toObject().value("source").toString();
										channelInfo->isSubDevice = deviceValue.toObject().value("isSubDevice").toBool();
										channelInfo->sdcardStatus = deviceValue.toObject().value("sdcardStatus").toString();
										channelInfo->multiFlag = deviceValue.toObject().value("multiFlag").toBool();
										//通道信息
										channelInfo->channelPicUrl = channelObj.value("channelPicUrl").toString();
										channelInfo->csStatus = channelObj.value("csStatus").toString();
										channelInfo->shareFunctions = channelObj.value("shareFunctions").toString();
										channelInfo->channelId = channelObj.value("channelId").toDouble();
										channelInfo->channelName = channelObj.value("channelName").toString();
										channelInfo->channelAbility = channelObj.value("channelAbility").toString();
										channelInfo->channelStatus = channelObj.value("channelStatus").toString();
										channelInfo->channelLastOffLineTime = channelObj.value("lastOffLineTime").toString();
										channelInfo->movable = channelObj.value("movable").toBool();
									
										channelInfoList->append(channelInfo);
									}
								}
							}
						}
					}
				}
			}
		}
		if (g_isReleasedForOverseas)
		{
			ret = true;
			break;
		}
		ret = true;
		LCOPENAPI_DESTROY_OBJECT(&pHsRes);
	} while (0);


	return ret;
}

QString OpenApiCtrl::modifyDeviceAlarmStatus(QString deviceId, int channelId, bool flag)
{
	QString ret = "OK";

	if (!m_IsGetTokenOK)
	{
		ret = "get token error";
		return ret;
	}

	char strChannelId[16] = { 0 };
	sprintf_s(strChannelId, 16, "%d", channelId);

	ModifyDeviceAlarmStatusRequest* req;
	ModifyDeviceAlarmStatusResponse* resp;
	req = LCOPENAPI_INIT(ModifyDeviceAlarmStatusRequest);
	resp = LCOPENAPI_INIT(ModifyDeviceAlarmStatusResponse);
	req->data.token = CS(m_Token.toLatin1().data());
	req->data.deviceId = CS(deviceId.toLatin1().data());
	req->data.channelId = CS(strChannelId);
	req->data.enable = flag;
	do
	{
		if (RET_OK != m_OpenApiHandle->request(req, resp, 10))
		{
			ret = "request failed";
			break;
		}

		if (HTTP_OK != resp->base.code)
		{
			ret = QString::number(resp->base.code);
			break;
		}

		if (0 != strcmp(resp->base.ret_code.cstr, "0"))
		{
			ret = QString(resp->base.ret_code.cstr) + " " + QString(resp->base.ret_msg.cstr);
			break;
		}

	} while (0);
	LCOPENAPI_DESTROY(req);
	LCOPENAPI_DESTROY(resp);

	return ret;
}

QString OpenApiCtrl::setStorageStrategy(QString deviceId, int channelId, bool flag)
{
	QString ret = "OK";

	if (!m_IsGetTokenOK)
	{
		ret = "get token error";
		return ret;
	}

	char strChannelId[16] = { 0 };
	sprintf_s(strChannelId, 16, "%d", channelId);

	SetStorageStrategyRequest* req;
	SetStorageStrategyResponse* resp;
	req = LCOPENAPI_INIT(SetStorageStrategyRequest);
	resp = LCOPENAPI_INIT(SetStorageStrategyResponse);
	req->data.token = CS(m_Token.toLatin1().data());
	req->data.deviceId = CS(deviceId.toLatin1().data());
	req->data.channelId = CS(strChannelId);
	req->data.status = CS(flag ? "on" : "off");
	do
	{
		if (RET_OK != m_OpenApiHandle->request(req, resp, 10))
		{
			ret = "request failed";
			break;
		}

		if (HTTP_OK != resp->base.code)
		{
			ret = QString::number(resp->base.code);
			break;
		}

		if (0 != strcmp(resp->base.ret_code.cstr, "0"))
		{
			ret = QString(resp->base.ret_code.cstr) + " " + QString(resp->base.ret_msg.cstr);
			break;
		}

	} while (0);
	LCOPENAPI_DESTROY(req);
	LCOPENAPI_DESTROY(resp);

	return ret;
}

QString OpenApiCtrl::modifyDevicePassword(QString deviceId, QString oldPwd, QString newPwd)
{
	QString sRet;
	if (!m_IsGetTokenOK)
	{
		sRet = "get token error";
		return sRet;
	}
	do
	{
		std::string strUri("/openapi/modifyPassword");
		LCOpenApiResponse pHsRes = { 0 };
		QJsonObject reqJson;
		//获取加密的设备密码
		char pszOldPwd[128] = { 0 };
		char pszNewPwd[128] = { 0 };
		LCOpenSdk_Utils::EncryptDevPwd(oldPwd.toLatin1().data(),deviceId.toLatin1().data(),m_appSecret.toLatin1().data(), pszOldPwd);
		LCOpenSdk_Utils::EncryptDevPwd(newPwd.toLatin1().data(), deviceId.toLatin1().data(), m_appSecret.toLatin1().data(), pszNewPwd);
		reqJson.insert("deviceId", deviceId.toLatin1().data());
		reqJson.insert("token", m_Token.toLatin1().data());
		reqJson.insert("oldPassword", pszOldPwd);
		reqJson.insert("newPassword", pszNewPwd);
		QJsonDocument requestDocument;
		requestDocument.setObject(reqJson);
		QByteArray requestBa = requestDocument.toJson(QJsonDocument::Compact);
		QString strBody(requestBa);
		int ret = m_OpenApiHandle->requestWithURL(strUri.c_str(), strBody.toStdString().c_str(), &pHsRes, 10, 0);
		if (0 != ret)
		{
			DLOG("request failed[%d]\n", ret);
			sRet = "request failed!";
		}

		int code = pHsRes.code;
		const char *desc = pHsRes.desc.cstr;
		char * ret_code = pHsRes.ret_code.cstr;
		if (HTTP_OK != code)
		{
			sRet = "request failed!";
			DLOG("HTTP_ERR[%d]\n", code);
			break;
		}

		if (0 != strcmp(ret_code, "0"))
		{
			sRet = QString(pHsRes.ret_code.cstr) + " " + QString(pHsRes.ret_msg.cstr);
			DLOG("BUSINESS_ERR[%s]\n", ret_code);
			break;
		}
		sRet = "OK";
		DLOG("modifyDevicePassword success\n");
		LCOPENAPI_DESTROY_OBJECT(&pHsRes);
	} while (0);

	return sRet;
}

QString OpenApiCtrl::upgradeDevice(QString deviceId)
{
	QString ret = "OK";

	if (!m_IsGetTokenOK)
	{
		ret = "get token error";
		return ret;
	}

	UpgradeDeviceRequest* req;
	UpgradeDeviceResponse* resp;
	req = LCOPENAPI_INIT(UpgradeDeviceRequest);
	resp = LCOPENAPI_INIT(UpgradeDeviceResponse);
	req->data.token = CS(m_Token.toLatin1().data());
	req->data.deviceId = CS(deviceId.toLatin1().data());
	do
	{
		if (RET_OK != m_OpenApiHandle->request(req, resp, 10))
		{
			ret = "request failed";
			break;
		}

		if (HTTP_OK != resp->base.code)
		{
			ret = QString::number(resp->base.code);
			break;
		}

		if (0 != strcmp(resp->base.ret_code.cstr, "0"))
		{
			ret = QString(resp->base.ret_code.cstr) + " " + QString(resp->base.ret_msg.cstr);
			break;
		}

	} while (0);

	LCOPENAPI_DESTROY(req);
	LCOPENAPI_DESTROY(resp);

	return ret;
}

int OpenApiCtrl::getDeviceRecordNum(const RECORD_PARAMETERS *parameters)
{
	if (!m_IsGetTokenOK)
	{
		DLOG("get Token Failed!!!\n");
		return RET_FAIL;
	}

	if (NULL == parameters)
	{
		return RET_FAIL;
	}

	QueryLocalRecordNumRequest *req;
	QueryLocalRecordNumResponse *resp;
	int ret = 0;
	char strCh[10] = { 0 };
	_snprintf(strCh, sizeof(strCh), "%d", parameters->channelId);
	req = LCOPENAPI_INIT(QueryLocalRecordNumRequest);
	resp = LCOPENAPI_INIT(QueryLocalRecordNumResponse);

	req->data.token = CS(m_Token.toLatin1().data());
	req->data.deviceId = CS(parameters->deviceId.toLatin1().data());
	req->data.channelId = CS(strCh);
	req->data.beginTime = CS(parameters->beginTime.toLatin1().data());
	req->data.endTime = CS(parameters->endTime.toLatin1().data());

	do
	{
		ret = m_OpenApiHandle->request(req, resp, 10);
		if (ret != 0)
		{
			DLOG("request failed[%d]\n", ret);
			ret = HTTP_ERR;
			break;
		}

		int code = resp->base.code;
		const char *desc = resp->base.desc.cstr;
		char * ret_code = resp->base.ret_code.cstr;
		if (HTTP_OK != code)
		{
			ret = HTTP_ERR;
			DLOG("HTTP_ERR[%d]\n", code);
			break;
		}

		if (0 != strcmp(ret_code, "0"))
		{
			ret = BUSINESS_ERR;
			DLOG("BUSINESS_ERR[%s]\n", ret_code);
			break;
		}

		DLOG("getDeviceRecordNum num[%d]\n", resp->data.recordNum);
		ret = resp->data.recordNum;
	} while (0);

	LCOPENAPI_DESTROY(req);
	LCOPENAPI_DESTROY(resp);
	return ret;
}

int OpenApiCtrl::getDeviceRecords(const RECORD_PARAMETERS *parameters, OUT RECORD_INFO_LIST *recordList)
{
	if (!m_IsGetTokenOK)
	{
		DLOG("get Token Failed!!!\n");
		return RET_FAIL;
	}

	if (NULL == parameters || NULL == recordList)
	{
		return RET_FAIL;
	}

	/* clear list */
	//TODO

	QueryLocalRecordsRequest *req;
	QueryLocalRecordsResponse *resp;

	int ret = 0;
	char strCh[10] = { 0 };
	char strRange[100] = { 0 };
	_snprintf(strCh, sizeof(strCh) - 1, "%d", parameters->channelId);
	_snprintf(strRange, sizeof(strRange) - 1, "%d-%d", parameters->beginIndex, parameters->endIndex);
	req = LCOPENAPI_INIT(QueryLocalRecordsRequest);
	resp = LCOPENAPI_INIT(QueryLocalRecordsResponse);

	req->data.token = CS(m_Token.toLatin1().data());
	req->data.deviceId = CS(parameters->deviceId.toLatin1().data());
	req->data.channelId = CS(strCh);
	req->data.beginTime = CS(parameters->beginTime.toLatin1().data());
	req->data.endTime = CS(parameters->endTime.toLatin1().data());
	req->data.queryRange = CS(strRange);

	do
	{
		ret = m_OpenApiHandle->request(req, resp, 60);
		if (ret != 0)
		{
			DLOG("request failed[%d]\n", ret);
			ret = HTTP_ERR;
			break;
		}

		int code = resp->base.code;
		const char *desc = resp->base.desc.cstr;
		char * ret_code = resp->base.ret_code.cstr;
		if (HTTP_OK != code)
		{
			ret = HTTP_ERR;
			DLOG("HTTP_ERR[%d]\n", code);
			break;
		}

		if (0 != strcmp(ret_code, "0"))
		{
			if (0 == strcmp(ret_code, "DV1049"))
			{
				ret = -99;
				break;
			}
			ret = BUSINESS_ERR;
			DLOG("BUSINESS_ERR[%s]\n", ret_code);
			break;
		}

		int size = resp->data.records.size;
		RECORD_INFO *info = NULL;
		for (int i = 0; i < size; ++i)
		{
			info = new(std::nothrow)RECORD_INFO;
			if (NULL == info)
			{
				break;
			}
		
			info->name = resp->data.records.array[i].recordId.cstr;
			info->beginTime = resp->data.records.array[i].beginTime.cstr;
			info->endTime = resp->data.records.array[i].endTime.cstr;
			info->channelId = atoi(resp->data.records.array[i].channelID.cstr);
			info->fileLength = resp->data.records.array[i].fileLength;
			info->deviceId = parameters->deviceId;
			info->index = recordList->size();

			/* 要求最新的在最前 */
			recordList->push_front(info);
		}
		ret = recordList->size();
		DLOG("get %d deviceRecord success\n", ret);
	} while (0);

	LCOPENAPI_DESTROY(req);
	LCOPENAPI_DESTROY(resp);
	return ret;
}

int OpenApiCtrl::getCloudRecordNum(const RECORD_PARAMETERS *parameters)
{
	if (!m_IsGetTokenOK)
	{
		DLOG("get Token Failed!!!\n");
		return RET_FAIL;
	}

	if (NULL == parameters)
	{
		return RET_FAIL;
	}

	QueryCloudRecordNumRequest *req;
	QueryCloudRecordNumResponse *resp;

	int ret = 0;
	char strCh[10] = { 0 };
	_snprintf(strCh, sizeof(strCh), "%d", parameters->channelId);
	req = LCOPENAPI_INIT(QueryCloudRecordNumRequest);
	resp = LCOPENAPI_INIT(QueryCloudRecordNumResponse);
	req->data.token = CS(m_Token.toLatin1().data());
	req->data.deviceId = CS(parameters->deviceId.toLatin1().data());
	req->data.channelId = CS(strCh);
	req->data.beginTime = CS(parameters->beginTime.toLatin1().data());
	req->data.endTime = CS(parameters->endTime.toLatin1().data());

	do
	{
		ret = m_OpenApiHandle->request(req, resp, 10);
		if (ret != 0)
		{
			DLOG("request failed[%d]\n", ret);
			ret = HTTP_ERR;
			break;
		}

		int code = resp->base.code;
		const char *desc = resp->base.desc.cstr;
		char * ret_code = resp->base.ret_code.cstr;
		if (HTTP_OK != code)
		{
			ret = HTTP_ERR;
			DLOG("HTTP_ERR[%d]\n", code);
			break;
		}

		if (0 != strcmp(ret_code, "0"))
		{
			ret = BUSINESS_ERR;
			DLOG("BUSINESS_ERR[%s]\n", ret_code);
			break;
		}

		ret = resp->data.recordNum;
		DLOG("getCloudRecordNum [%d]\n", ret);
	} while (0);

	LCOPENAPI_DESTROY(req);
	LCOPENAPI_DESTROY(resp);
	return ret;
}

int OpenApiCtrl::getCloudRecords(const RECORD_PARAMETERS *parameters, OUT RECORD_INFO_LIST *recordList)
{
	int ret = 0;
	if (!m_IsGetTokenOK)
	{
		DLOG("get Token Failed!!!\n");
		return RET_FAIL;
	}

	if (NULL == parameters || NULL == recordList)
	{
		return RET_FAIL;
	}

	/* clear list */
	//TODO
	
	ChannelInfo* CloudRecordChannelInfo = DevicesListCtrl::getInstance()->getChannelInfoByChannel(parameters->deviceId, parameters->channelId);
	if (CloudRecordChannelInfo->accessType == "Easy4IP" || CloudRecordChannelInfo->accessType == "P2P")
	{
		QueryCloudRecordsRequest *req;
		QueryCloudRecordsResponse *resp;
		ret = 0;
		char strCh[20] = { 0 };
		char strRange[50] = { 0 };
		_snprintf(strCh, sizeof(strCh), "%d", parameters->channelId);
		_snprintf(strRange, sizeof(strRange), "%d-%d", parameters->beginIndex, parameters->endIndex);
		req = LCOPENAPI_INIT(QueryCloudRecordsRequest);
		resp = LCOPENAPI_INIT(QueryCloudRecordsResponse);
		req->data.token = CS(m_Token.toLatin1().data());
		req->data.deviceId = CS(parameters->deviceId.toLatin1().data());
		req->data.channelId = CS(strCh);
		req->data.queryRange = CS(strRange);
		req->data.beginTime = CS(parameters->beginTime.toLatin1().data());
		req->data.endTime = CS(parameters->endTime.toLatin1().data());

		do
		{
			ret = m_OpenApiHandle->request(req, resp, 10);
			if (ret != 0)
			{
				DLOG("request failed[%d]\n", ret);
				ret = HTTP_ERR;
				break;
			}

			int code = resp->base.code;
			const char *desc = resp->base.desc.cstr;
			char * ret_code = resp->base.ret_code.cstr;
			if (HTTP_OK != code)
			{
				ret = HTTP_ERR;
				DLOG("HTTP_ERR[%d]\n", code);
				break;
			}

			if (0 != strcmp(ret_code, "0"))
			{
				ret = BUSINESS_ERR;
				DLOG("BUSINESS_ERR[%s]\n", ret_code);
				break;
			}

			int size = resp->data.records.size;
			recInfo *info = NULL;
			for (int i = 0; i < size; ++i)
			{
				info = new(std::nothrow)recInfo;
				if (NULL == info)
				{
					break;
				}

				info->name.sprintf("%s-%s",
					resp->data.records.array[i].beginTime.cstr, resp->data.records.array[i].endTime.cstr);
				info->beginTime = resp->data.records.array[i].beginTime.cstr;
				info->endTime = resp->data.records.array[i].endTime.cstr;
				info->deviceId = resp->data.records.array[i].deviceId.cstr;
				info->thumbUrl = resp->data.records.array[i].thumbUrl.cstr;
				info->channelId = atoi(resp->data.records.array[i].channelId.cstr);
				info->recId = resp->data.records.array[i].recordId.cstr;
				info->fileLength = QString(resp->data.records.array[i].size.cstr).toLongLong();
				info->recordRegionId = resp->data.records.array[i].recordRegionId.cstr;

				info->index = recordList->size();

				/* 要求最新的在最前 */
				recordList->push_front(info);
			}
			ret = recordList->size();
			DLOG("get %d cloudRecord success\n", ret);
		} while (0);

		LCOPENAPI_DESTROY(req);
		LCOPENAPI_DESTROY(resp);
	}
	else
	{
		do
		{
			std::string strUri("/openapi/getCloudRecords");
			LCOpenApiResponse pHsRes = { 0 };
			QJsonObject reqJson;
			//获取加密的设备密码
			char strCh[20] = { 0 };
			char strRange[50] = { 0 };
			_snprintf(strCh, sizeof(strCh), "%d", parameters->channelId);
			_snprintf(strRange, sizeof(strRange), "%d-%d", parameters->beginIndex, parameters->endIndex);

			reqJson.insert("deviceId", parameters->deviceId.toLatin1().data());
			reqJson.insert("token", m_Token.toLatin1().data());
			reqJson.insert("channelId", strCh);
			reqJson.insert("count", (long)10);
			reqJson.insert("beginTime", parameters->beginTime.toLatin1().data());
			reqJson.insert("endTime", parameters->endTime.toLatin1().data());

			QJsonDocument requestDocument;
			requestDocument.setObject(reqJson);
			QByteArray requestBa = requestDocument.toJson(QJsonDocument::Compact);
			QString strBody(requestBa);
			ret = m_OpenApiHandle->requestWithURL(strUri.c_str(), strBody.toStdString().c_str(), &pHsRes, 10, 0);
			//解析Json
			QJsonParseError jsonError;
			QByteArray responseBa = QString(CToS(pHsRes.content)).toUtf8();
			QJsonDocument doucment = QJsonDocument::fromJson(responseBa, &jsonError);
			if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError))
			{
				QJsonObject object = doucment.object();
				QJsonObject resultObj = object.value("result").toObject();
				int code = pHsRes.code;
				const char *desc = pHsRes.desc.cstr;
				char * ret_code = pHsRes.ret_code.cstr;
				if (HTTP_OK != code)
				{
					ret = HTTP_ERR;
					DLOG("HTTP_ERR[%d]\n", code);
					break;
				}

				if (0 != strcmp(ret_code, "0"))
				{
					ret = BUSINESS_ERR;
					DLOG("BUSINESS_ERR[%s]\n", ret_code);
					break;
				}
				QJsonObject dataObj = resultObj.value("data").toObject();
				
				if (dataObj.contains("records"))
				{
					QJsonValue recordsVal = dataObj.value("records");
					if (recordsVal.isArray())
					{
						QJsonArray recordsArray = recordsVal.toArray();
						recInfo *info = NULL;
						for (int i = 0; i < recordsArray.size(); ++i)
						{
							QJsonValue recordsValue = recordsArray.at(i);
							info = new(std::nothrow)recInfo;
							if (NULL == info)
							{
								break;
							}

							int respChannelId = atoi(recordsValue.toObject().value("channelId").toString().toLatin1().data());
							if (parameters->channelId == respChannelId)
							{
								info->name.sprintf("%s-%s",
									recordsValue.toObject().value("beginTime").toString().toLatin1().data(), recordsValue.toObject().value("endTime").toString().toLatin1().data());

								info->beginTime = recordsValue.toObject().value("beginTime").toString();
								info->endTime = recordsValue.toObject().value("endTime").toString();

								info->deviceId = recordsValue.toObject().value("deviceId").toString();
								info->thumbUrl = recordsValue.toObject().value("thumbUrl").toString();
								info->channelId = atoi(recordsValue.toObject().value("channelId").toString().toLatin1().data());
								info->recId = recordsValue.toObject().value("recordId").toString();
								info->fileLength = QString(recordsValue.toObject().value("size").toString()).toLongLong();

								info->recordRegionId = recordsValue.toObject().value("recordRegionId").toString();
								info->pairKey = recordsValue.toObject().value("pairKey").toString();
								info->index = recordList->size();

								recordList->push_back(info);
							}
						}
					}
				}
			}
			ret = recordList->size();
			qDebug("get %d getCloudRecords. success\n", ret);
			LCOPENAPI_DESTROY_OBJECT(&pHsRes);
		} while (0);
	}

	return ret;
}


int OpenApiCtrl::getAlarmMsg(AlarmMsgParameter* alarmMsgParam, AlarmMsgInfoList* alarmMsgInfoList)
{
	if (!m_IsGetTokenOK)
	{
		qDebug("get Token Failed!!!\n");
		return RET_FAIL;
	}

	if (NULL == alarmMsgParam || NULL == alarmMsgInfoList)
	{
		qDebug("input param error!!!\n");
		return RET_FAIL;
	}

	int ret = -1;
	do
	{
		std::string strUri("/openapi/getAlarmMessage");
		LCOpenApiResponse pHsRes = { 0 };
		QJsonObject reqJson;
		QString strChannelID = QString("%1").arg(alarmMsgParam->channelId);
		QString strCount = QString("%1").arg(alarmMsgParam->maxCount);
		reqJson.insert("deviceId", alarmMsgParam->deviceId.toStdString().c_str());
		reqJson.insert("channelId", strChannelID.toStdString().c_str());
		reqJson.insert("token", m_Token.toLatin1().data());
		reqJson.insert("beginTime", alarmMsgParam->beginTime.toStdString().c_str());
		reqJson.insert("endTime", alarmMsgParam->endTime.toStdString().c_str());
		reqJson.insert("count", strCount.toStdString().c_str());
		QJsonDocument requestDocument;
		requestDocument.setObject(reqJson);
		QByteArray requestBa = requestDocument.toJson(QJsonDocument::Compact);
		QString strBody(requestBa);
		ret = m_OpenApiHandle->requestWithURL(strUri.c_str(), strBody.toStdString().c_str(), &pHsRes, 10, 0);

		if (ret != 0)
		{
			qDebug("request failed[%d]\n", ret);
			ret = HTTP_ERR;
			break;
		}
		//解析Json
		QJsonParseError jsonError;
		QByteArray responseBa = QString(CToS(pHsRes.content)).toUtf8();
		QJsonDocument doucment = QJsonDocument::fromJson(responseBa, &jsonError);
		if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError))
		{
			QJsonObject object = doucment.object();
			QJsonObject resultObj = object.value("result").toObject();
			int code = pHsRes.code;
			const char *desc = pHsRes.desc.cstr;
			char * ret_code = pHsRes.ret_code.cstr;
			if (HTTP_OK != code)
			{
				ret = HTTP_ERR;
				DLOG("HTTP_ERR[%d]\n", code);
				break;
			}

			if (0 != strcmp(ret_code, "0"))
			{
				ret = BUSINESS_ERR;
				DLOG("BUSINESS_ERR[%s]\n", ret_code);
				break;
			}
			QJsonObject dataObj = resultObj.value("data").toObject();
			if (0 == dataObj.value("count").toDouble())
			{
				break;
			}

			if (dataObj.contains("alarms"))
			{
				QJsonValue alarmsVal = dataObj.value("alarms");
				if (alarmsVal.isArray())
				{
					QJsonArray alarmsArray = alarmsVal.toArray();
					for (int i = 0; i < alarmsArray.size(); ++i)
					{
						QJsonValue alarmsValue = alarmsArray.at(i);
						
						AlarmMsgInfo* alarmMsgInfo = new AlarmMsgInfo();
						if (NULL == alarmMsgInfo)
						{
							break;
						}
						alarmMsgInfo->deviceId = alarmsValue.toObject().value("deviceId").toString();
						alarmMsgInfo->channelId = atoi(alarmsValue.toObject().value("channelId").toString().toStdString().c_str());
						alarmMsgInfo->Channelname = alarmsValue.toObject().value("name").toString();
						alarmMsgInfo->alarmId = alarmsValue.toObject().value("alarmId").toString();
						alarmMsgInfo->thumbUrl = alarmsValue.toObject().value("thumbUrl").toString();
						alarmMsgInfo->cname = alarmsValue.toObject().value("cname").toString();
						alarmMsgInfo->message = alarmsValue.toObject().value("message").toString();
						if (alarmsValue.toObject().value("picurlArray").isArray())
						{
							QJsonArray picurlArray = alarmsValue.toObject().value("picurlArray").toArray();
							for (int j = 0; j < picurlArray.size(); ++j)
							{
								alarmMsgInfo->picurlArray.append(picurlArray.at(j).toString());
							}
						}
						alarmMsgInfo->localDate = alarmsValue.toObject().value("localDate").toString();

						alarmMsgInfoList->append(alarmMsgInfo);
					}
				}
			}
		}
		ret = alarmMsgInfoList->size();
		qDebug("get %d AlarmMsg success\n", ret);
		LCOPENAPI_DESTROY_OBJECT(&pHsRes);
	} while (0);
	return ret;
}

bool OpenApiCtrl::deleteAlarmMsg(AlarmMsgInfo* alarmMsgInfo)
{
	int iret = 0;
	bool bret = false;
	do
	{
		std::string strUri("/openapi/deleteAlarmMessage");
		LCOpenApiResponse pHsRes = { 0 };
		QJsonObject reqJson;
		QString strChannelID = QString("%1").arg(alarmMsgInfo->channelId);
		reqJson.insert("deviceId", alarmMsgInfo->deviceId.toStdString().c_str());
		reqJson.insert("channelId", strChannelID);
		reqJson.insert("token", m_Token.toLatin1().data());
		reqJson.insert("indexId", alarmMsgInfo->alarmId);
		QJsonDocument requestDocument;
		requestDocument.setObject(reqJson);
		QByteArray requestBa = requestDocument.toJson(QJsonDocument::Compact);
		QString strBody(requestBa);
		iret = m_OpenApiHandle->requestWithURL(strUri.c_str(), strBody.toStdString().c_str(), &pHsRes, 10, 0);
		if (0 != iret)
		{
			DLOG("request failed[%d]\n", iret);
			bret = false;
		}

		int code = pHsRes.code;
		const char *desc = pHsRes.desc.cstr;
		char * ret_code = pHsRes.ret_code.cstr;
		if (HTTP_OK == code)
		{
			if (!strcmp(ret_code, "0"))
			{
				bret = true;
				qDebug("deleteAlarmMsg [%lld] success\n", alarmMsgInfo->alarmId);
			}
			else
			{
				qDebug("deleteAlarmMsg failed[%s]\n", ret_code);
			}
		}
		LCOPENAPI_DESTROY_OBJECT(&pHsRes);
	} while (0);
	return bret;
}

bool OpenApiCtrl::getDeviceVersionList(QString deviceId)
{
	bool ret = false;
	if (!m_IsGetTokenOK)
	{
		DLOG("get Token Failed!!!\n");
		return false;
	}

	/* getDeviceVersionList */
	DeviceVersionListRequest* req;
	DeviceVersionListResponse* resp;
	req = LCOPENAPI_INIT(DeviceVersionListRequest);
	resp = LCOPENAPI_INIT(DeviceVersionListResponse);
	req->data.token = CS(m_Token.toLatin1().data());
	req->data.deviceIds = CS(deviceId.toLatin1().data());

	do
	{
		if (LCOpenSDK_Api::GetInstance()->request(req, resp, 10) != 0)
		{
			DLOG("request failed[%d]\n", ret);
			return false;
		}

		int code = resp->base.code;
		char* ret_code = resp->base.ret_code.cstr;
		if (HTTP_OK != code)
		{
			DLOG("getDeviceVersionList failed[%s]\n", ret_code);
			return false;
		}

		if (0 != strcmp(ret_code, "0"))
		{
			DLOG("getDeviceVersionList BUSINESS_ERR[%s]\n", ret_code);
			return false;
		}
		
		ret = resp->data.deviceVersionList.array[0].canBeUpgrade;
		//ret = resp->data.deviceVersionList.canBeUpgrade;
		DLOG("getDeviceVersionList [%d]\n", ret);

	} while (0);

	LCOPENAPI_DESTROY(req);
	LCOPENAPI_DESTROY(resp);
	return ret;
}

int OpenApiCtrl::getStorageStrategy(QString deviceId, int channelId)
{
	int ret = 0;
	if (!m_IsGetTokenOK)
	{
		DLOG("get Token Failed!!!\n");
		return RET_FAIL;
	}

	GetStorageStrategyRequest *req;
	GetStorageStrategyResponse *resp;
	req = LCOPENAPI_INIT(GetStorageStrategyRequest);
	resp = LCOPENAPI_INIT(GetStorageStrategyResponse);
	req->data.token = CS(m_Token.toLatin1().data());
	req->data.deviceId = CS(deviceId.toLatin1().data());
	char strChannelId[16] = { 0 };
	sprintf_s(strChannelId, 16, "%d", channelId);
	req->data.channelId = CS(strChannelId);

	do
	{
		ret = m_OpenApiHandle->request(req, resp, 10);
		if (ret != 0)
		{
			DLOG("request failed[%d]\n", ret);
			ret = HTTP_ERR;
			break;
		}

		int code = resp->base.code;
		const char *desc = resp->base.desc.cstr;
		char * ret_code = resp->base.ret_code.cstr;
		if (HTTP_OK != code)
		{
			ret = HTTP_ERR;
			DLOG("HTTP_ERR[%d]\n", code);
			break;
		}

		if (0 != strcmp(ret_code, "0"))
		{
			ret = BUSINESS_ERR;
			DLOG("BUSINESS_ERR[%s]\n", ret_code);
			break;
		}

		ret = resp->data.strategyStatus;
		DLOG("getStorageStrategy [%d]\n", ret);
	} while (0);

	LCOPENAPI_DESTROY(req);
	LCOPENAPI_DESTROY(resp);
	return ret;
}
