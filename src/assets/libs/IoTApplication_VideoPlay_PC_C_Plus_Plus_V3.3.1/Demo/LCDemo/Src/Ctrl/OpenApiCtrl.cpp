#include <libdsl/DPrintLog.h>
#include "LCOpenApi/DeviceList.h"
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
#include "LCOpenApi/ControlPTZ.h"
#include "LCOpenApi/PaaSPTZMove.h"
#include "Utils/global.h"
#include "LCOpenSDK_LoginManager.h"
#include "TokenCtrl.h"
#include <QDebug>
#include "OpenApiCtrl.h"
#include <QJsonDocument>
#include <QJsonObject>
#include "LCOpenSdk_Utils.h"
#include <QUuid>

extern bool g_isReleasedForOverseas;

OpenApiCtrl::OpenApiCtrl()
: m_OpenApiHandle(NULL)
, m_IsGetTokenOK(false)
, m_tokenCtrl(NULL)
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

void OpenApiCtrl::init(const OPEN_API_INIT_PARAM& param)
{
    m_OpenApiHandle = LCOpenSDK_Api::GetInstance();
	//m_OpenApiHandle->initOpenApi(param.host.toLatin1().data(), param.port, param.caPath.toLatin1().data());
	m_OpenApiHandle->initOpenApi(param.host.toLatin1().data(), param.port, NULL);

	m_tokenCtrl = new TokenCtrl();
	connect(m_tokenCtrl, &TokenCtrl::sgnGetPlayInfoReslut, this, &OpenApiCtrl::sgnGetPlayInfoReslut);
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

    return m_IOTToken;
}

void OpenApiCtrl::setToken(QString token)
{
    m_IsGetTokenOK = true;
    m_IOTToken = token;
}

int OpenApiCtrl::getIOTToken(QString host, QString AccessKey, QString productId, QString secretKey)
{
	int ret = RET_OK;
	m_IsGetTokenOK = false;

	if (!m_tokenCtrl)
	{
		return -1;
	}
	ret = m_tokenCtrl->getIOTToken(host, m_IOTToken, AccessKey, productId, secretKey);
	if (RET_OK == ret)
	{
		//	m_IsGetTokenOK = true;
	}
	return ret;
}

int OpenApiCtrl::getP2PServerInfo(QString host, QString AccessKey, QString productId, QString secretKey)
{
	std::string p2pKey = "12851d58e2f385s1d85f";

	std::string p2pValue = "iFOAESBRCAoFRKKHHN+GFrkBoWqmS5F3D9b7tlSVvTmP7YhI0No633ysVVTKVliZE4L7l0Fcydjx+GO/CfEufAI8m6cUVtM/UioeFV2eftpiLulHlTciHt9EbImgwcRTyuT/2ZCgEGdQ8pVf3G7EGQLKvKo2tVkzYQESilOk1Ev1WmqY66laJc0exyADyUriA0kO2DyZHeBAFLwMiY9JTSvvKfJOz9Dcb6pXaCYODBzLFHfx1ccNTrL2FYy6lkY5ABMX4iziHtzWrBCacpTi+xNRgGcNf5FMJ2wzWl2F5nspdS4USbfXthI6wyP1oPha2j9ktlAO8cGT04fbJZIj5PY78kKgh7oPzUq8zcJuGtZg7S3ozjBIghdKHu8x0Oo9SQwB9RDVHt+nRlkHm7+1mltwlUw/QgLGk636phMOYmJu/AX67so+bU0NOYm69w/ne4mwFn/W3AGU1oEDP0vtcLk1DczpU4ZKMy3v/g7Gv2g=";

	m_tokenCtrl->getP2pInfo(host, AccessKey, productId, secretKey);
	

	//LCOpenSDK_LoginManager::getInstance()->configureP2PServers(p2pKey.c_str(), p2pValue.c_str());
	return 0;
}

void OpenApiCtrl::getIOTPlayInfo(QString host, QString AccessKey, QString productId, QString secretKey)
{
	return m_tokenCtrl->getIOTPlayInfo(host, AccessKey, productId, secretKey);
}

bool OpenApiCtrl::getIOTDevicesList( IOTDeviceInfoList* channelInfoList)
{
	std::vector<std::string> deviceIds;
	std::vector<std::string> playInfos;

	bool ret = true;

	if (!m_IsGetTokenOK)
	{
		DLOG("get Token Failed!!!\n");
		ret = false;
		return ret;
	}

    if (!m_tokenCtrl)
    {
        return -1;
    }
	// parse m_deviList
	//devices

    std::vector<DEVICE_INFO> deviceVec = m_tokenCtrl->getDeviceVec();
	for (int i = 0; i< deviceVec.size(); i++) {
		IOTDeviceList* iodevicelist = new (std::nothrow) IOTDeviceList();
		if (NULL == iodevicelist)
		{
			qDebug() << "iodevicelist is empty !\n";
			ret = false;
			return ret;
		}
		iodevicelist->deviceId = deviceVec.at(i).deviceId;
		iodevicelist->playInfo = deviceVec.at(i).playInfo;
		iodevicelist->deviceName = deviceVec.at(i).deviceName;
		iodevicelist->deviceModel = deviceVec.at(i).deviceModel;
		iodevicelist->deviceStatus = deviceVec.at(i).deviceStatus;
		iodevicelist->deviceAbility = deviceVec.at(i).deviceAbility;
		iodevicelist->deviceVersion = deviceVec.at(i).deviceVersion;
		iodevicelist->canBeUpgrade = deviceVec.at(i).canBeUpgrade;
		iodevicelist->encryptMode = deviceVec.at(i).encryptMode;
		iodevicelist->platForm = 2;
		iodevicelist->decryptKey = deviceVec.at(i).deviceId;
		iodevicelist->catalog = deviceVec.at(i).catalog;

		deviceIds.push_back(iodevicelist->deviceId);
		playInfos.push_back(iodevicelist->playInfo);

		//channels
		for(int j = 0; j < deviceVec.at(i).iotChannel.size(); j++)
		{
			IOTChannels* iochannel = new (std::nothrow) IOTChannels();
			iochannel->channelName = deviceVec.at(i).iotChannel.at(j).channelName;
			iochannel->channelPicUrl = deviceVec.at(i).iotChannel.at(j).channelPicUrl;
			iochannel->channelAbility = deviceVec.at(i).iotChannel.at(j).channelAbility;
			iochannel->channelId = deviceVec.at(i).iotChannel.at(j).channelId;
			iochannel->channelStatus = deviceVec.at(i).iotChannel.at(j).channelStatus;
			iochannel->csStatus = deviceVec.at(i).iotChannel.at(j).csStatus;
			iodevicelist->iotChannel.append(iochannel);
		}
		channelInfoList->append(iodevicelist);
	}

	//qDebug() << "getIOTDevicesList channels: " << channels.c_str();
	//if (reader1.parse(channels, root1)) {
	//	int channelsSize = root1.size();
	//	for (int i = 0; i < channelsSize; i++) {
	//		iotDeviceList->iotChannel.channelName = root1[i]["channelName"].asString();
	//		iotDeviceList->iotChannel.channelPicUrl = root1[i]["channelPicUrl"].asString();
	//		iotDeviceList->iotChannel.channelAbility = root1[i]["channelAbility"].asString();
	//		iotDeviceList->iotChannel.channelId = root1[i]["channelId"].asString();
	//		iotDeviceList->iotChannel.channelStatus = root1[i]["channelStatus"].asString();
	//		iotDeviceList->iotChannel.csStatus = root1[i]["csStatus"].asString();
	//	}
	//} else {
	//	qDebug() << "parse channels failed!\n";
	//	ret = false;
	//	return ret;
	//}

	//std::string deviceLis = tokenctrl.m_deviList;
	//qDebug() << "getIOTDevicesList deviceLis: " << deviceLis.c_str();
	//if (reader.parse(deviceLis, root)) {
	//	int devicelisSize = root.size();
	//	for (int i = 0; i < devicelisSize; i++) {
	//	iotDeviceList->deviceId = root[i]["deviceId"].asString();

	//	qDebug() << "getIOTDevicesList root: " << iotDeviceList->deviceId.c_str();

	//	std::string deviceJsonString = "[{\"Sn\":\"" + iotDeviceList->deviceId + "\", \"Type\":1,\"Port\":554,\"User\":\"\", \"Pwd\":\"\"}]";
	//	LCOpenSDK_LoginManager::getInstance()->addDevices(m_IOTToken.toStdString().c_str(), deviceJsonString.c_str());
	//	qDebug() << "getIOTDevicesList m_IOTToken.toStdString().c_str(): " << m_IOTToken.toStdString().c_str();
	//	iotDeviceList->deviceName = root[i]["deviceName"].asString();
	//	qDebug() << "getIOTDevicesList iotDeviceList->deviceName: " << iotDeviceList->deviceName.c_str();
	//	iotDeviceList->deviceModel = root[i]["deviceModel"].asString();
	//	iotDeviceList->deviceStatus = root[i]["deviceStatus"].asString();
	//	qDebug() << "getIOTDevicesList iotDeviceList->deviceStatus: " << iotDeviceList->deviceStatus.c_str();
	//	iotDeviceList->deviceAbility = root[i]["deviceAbility"].asString();
	//	qDebug() << "getIOTDevicesList iotDeviceList->deviceAbility: " << iotDeviceList->deviceAbility.c_str();
	//	iotDeviceList->deviceVersion = root[i]["deviceVersion"].asString();
	//	iotDeviceList->canBeUpgrade = root[i]["canBeUpgrade"].asBool();
	//	iotDeviceList->encryptMode = root[i]["encryptMode"].asString();
//\tiotDeviceList- = 2; // Hardcoded for now
	//	iotDeviceList->decryptKey = root[i]["deviceId"].asString();
	//	channelInfoList->append(iotDeviceList);
	//	}
	//} else {
	//	qDebug() << "parse m_deviList failed!\n";
	//	ret = false;
	//	return ret;
	//}

	int size = deviceIds.size();
	std::vector<const char*> deviceIdPtrs(size);
	std::vector<const char*> playInfoPtrs(size);
	for (int index = 0; index < size; index++) {
		deviceIdPtrs[index] = deviceIds[index].c_str();
		playInfoPtrs[index] = playInfos[index].c_str();
	}

	LCOpenSDK_LoginManager::getInstance()->addDevices(deviceIdPtrs.data(), playInfoPtrs.data(), size);


	if (g_isReleasedForOverseas)
	{
		ret = true;
	}
	qDebug() << "22222ret:" << ret;
	return ret;
}

bool OpenApiCtrl::getDevicesList(ChannelInfoList* channelInfoList)
{
    bool ret = false;
	
    if (!m_IsGetTokenOK)
    {
        DLOG("get Token Failed!!!\n");
        return ret;
    }

    DeviceListRequest* req = LCOPENAPI_INIT(DeviceListRequest);
    DeviceListResponse* resp = LCOPENAPI_INIT(DeviceListResponse);
    ShareDeviceListRequest* req1 = LCOPENAPI_INIT(ShareDeviceListRequest);
    ShareDeviceListResponse* resp1 = LCOPENAPI_INIT(ShareDeviceListResponse);
    BeAuthDeviceListRequest* req2 = LCOPENAPI_INIT(BeAuthDeviceListRequest);
    BeAuthDeviceListResponse* resp2 = LCOPENAPI_INIT(BeAuthDeviceListResponse);
    do 
    {
        req->data.token = CS(m_Token.toLatin1().data());
        req->data.queryRange = CS("1-100");
        if (0 != m_OpenApiHandle->request(req, resp, 20))
        {
            break;
        }
        if (HTTP_OK != resp->base.code)
        {
            break;
        }
        if (0 != strcmp("0", resp->base.ret_code.cstr))
        {
            break;
        }
        int devicesNum = resp->data.devices.size;
        for (int i = 0; i < devicesNum; i++)
        {
            /*std::string deviceJsonString = "[{\"Sn\":\"" + std::string(resp->data.devices.array[i].deviceId.cstr) + "\", \"Type\":1,\"Port\":554,\"User\":\"\", \"Pwd\":\"\"}]";
            LCOpenSDK_LoginManager::getInstance()->addDevices(m_Token.toStdString().c_str(), deviceJsonString.c_str());*/
            int channelNum = resp->data.devices.array[i].channels.size;
            for (int j = 0; j < channelNum; j++)
            {
                ChannelInfo* channelInfo = new (std::nothrow) ChannelInfo();
                if (NULL == channelInfo)
                {
                    break;
                }
                channelInfo->deviceId = QString::fromUtf8(resp->data.devices.array[i].deviceId.cstr);
                channelInfo->platForm = resp->data.devices.array[i].platForm;
                channelInfo->name = QString::fromUtf8(resp->data.devices.array[i].name.cstr);
                channelInfo->deviceModel = QString::fromUtf8(resp->data.devices.array[i].deviceModel.cstr);
                channelInfo->status = resp->data.devices.array[i].status;
                channelInfo->ability = QString::fromUtf8(resp->data.devices.array[i].ability.cstr);
                channelInfo->version = QString::fromUtf8(resp->data.devices.array[i].version.cstr);
                channelInfo->canBeUpgrade = resp->data.devices.array[i].canBeUpgrade;
                channelInfo->encryptMode = resp->data.devices.array[i].encryptMode;
                channelInfo->decryptKey = channelInfo->deviceId;    /* 瑙ｅ瘑绉橀挜鍒濆鍖栦负璁惧搴忓垪鍙?*/

                channelInfo->channelName = QString::fromUtf8(resp->data.devices.array[i].channels.array[j].channelName.cstr);
                channelInfo->channelPicUrl = QString::fromUtf8(resp->data.devices.array[i].channels.array[j].channelPicUrl.cstr);
                channelInfo->channelAbility = QString::fromUtf8(resp->data.devices.array[i].channels.array[j].channelAbility.cstr);
                channelInfo->channelId = resp->data.devices.array[i].channels.array[j].channelId;
                channelInfo->channelOnline = resp->data.devices.array[i].channels.array[j].channelOnline;
                channelInfo->csStatus = resp->data.devices.array[i].channels.array[j].csStatus;

                channelInfoList->append(channelInfo);
            }
        }

        if (g_isReleasedForOverseas)
        {
            ret = true;
            break;
        }

        req1->data.token = CS(m_Token.toLatin1().data());
        req1->data.queryRange = CS("1-100");
        if (0 != m_OpenApiHandle->request(req1, resp1, 10))
        {
            break;
        }
        if (HTTP_OK != resp1->base.code)
        {
            break;
        }
        if (0 != strcmp("0", resp1->base.ret_code.cstr))
        {
            break;
        }
        int devicesNum1 = resp1->data.devices.size;
        for (int i = 0; i < devicesNum1; i++)
        {
            int channelNum1 = resp1->data.devices.array[i].channels.size;
            for (int j = 0; j < channelNum1; j++)
            {
                ChannelInfo* channelInfo = new (std::nothrow) ChannelInfo();
                if (NULL == channelInfo)
                {
                    break;
                }
                channelInfo->deviceId = QString::fromUtf8(resp1->data.devices.array[i].deviceId.cstr);
                channelInfo->name = QString::fromUtf8(resp1->data.devices.array[i].name.cstr);
                channelInfo->deviceModel = QString::fromUtf8(resp1->data.devices.array[i].deviceModel.cstr);
                channelInfo->status = resp1->data.devices.array[i].status;
                channelInfo->ability = QString::fromUtf8(resp1->data.devices.array[i].ability.cstr);
                channelInfo->version = QString::fromUtf8(resp1->data.devices.array[i].version.cstr);
                channelInfo->canBeUpgrade = resp1->data.devices.array[i].canBeUpgrade;
                channelInfo->encryptMode = resp1->data.devices.array[i].encryptMode;
                channelInfo->decryptKey = channelInfo->deviceId;    /* 瑙ｅ瘑绉橀挜鍒濆鍖栦负璁惧搴忓垪鍙?*/

                channelInfo->channelName = QString::fromUtf8(resp1->data.devices.array[i].channels.array[j].channelName.cstr) + "[shared]";
                channelInfo->channelPicUrl = QString::fromUtf8(resp1->data.devices.array[i].channels.array[j].channelPicUrl.cstr);
                channelInfo->channelId = resp1->data.devices.array[i].channels.array[j].channelId;
                channelInfo->channelOnline = resp1->data.devices.array[i].channels.array[j].channelOnline;

                channelInfoList->append(channelInfo);
            }
        }

        req2->data.token = CS(m_Token.toLatin1().data());
        req2->data.queryRange = CS("1-50");
        if (0 != m_OpenApiHandle->request(req2, resp2, 10))
        {
            break;
        }
        if (HTTP_OK != resp2->base.code)
        {
            break;
        }
        if (0 != strcmp("0", resp2->base.ret_code.cstr))
        {
            break;
        }
        int devicesNum2 = resp2->data.devices.size;
        for (int i = 0; i < devicesNum2; i++)
        {
            ChannelInfo* channelInfo = new (std::nothrow) ChannelInfo();
            if (NULL == channelInfo)
            {
                break;
            }
            channelInfo->deviceId = QString::fromUtf8(resp2->data.devices.array[i].deviceId.cstr);
            channelInfo->name = QString::fromUtf8(resp2->data.devices.array[i].name.cstr);
            channelInfo->deviceModel = QString::fromUtf8(resp2->data.devices.array[i].deviceModel.cstr);
            channelInfo->status = resp2->data.devices.array[i].status;
            channelInfo->ability = QString::fromUtf8(resp2->data.devices.array[i].ability.cstr);
            channelInfo->version = QString::fromUtf8(resp2->data.devices.array[i].version.cstr);
            channelInfo->canBeUpgrade = resp2->data.devices.array[i].canBeUpgrade;
            channelInfo->encryptMode = resp2->data.devices.array[i].encryptMode;
            channelInfo->decryptKey = channelInfo->deviceId;    /* 瑙ｅ瘑绉橀挜鍒濆鍖栦负璁惧搴忓垪鍙?*/

            channelInfo->channelName = QString::fromUtf8(resp2->data.devices.array[i].channelName.cstr) + "[authorized]";
            channelInfo->channelPicUrl = QString::fromUtf8(resp2->data.devices.array[i].channelPicUrl.cstr);
            channelInfo->channelId = resp2->data.devices.array[i].channelId;
            channelInfo->channelOnline = resp2->data.devices.array[i].channelOnline;
            channelInfo->csStatus = resp2->data.devices.array[i].csStatus;

            channelInfoList->append(channelInfo);
        }

        ret = true;
    } while (0);
    LCOPENAPI_DESTROY(req);
    LCOPENAPI_DESTROY(resp);
    LCOPENAPI_DESTROY(req1);
    LCOPENAPI_DESTROY(resp1);
    LCOPENAPI_DESTROY(req2);
    LCOPENAPI_DESTROY(resp2);

    return ret;
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
    if (0 == m_OpenApiHandle->request(req, resp, 10))
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
                ret = resp->base.ret_code.cstr;
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
                ret = resp->base.ret_code.cstr;
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
            ret = resp->base.ret_code.cstr;
            break;
        }

    } while (0);

    LCOPENAPI_DESTROY(req);
    LCOPENAPI_DESTROY(resp);

    return ret;
}

bool OpenApiCtrl::unBindDevice(QString deviceId)
{
    bool ret = false;

    if (!m_IsGetTokenOK)
    {
        DLOG("get Token Failed!!!\n");
        return ret;
    }

    UnBindDeviceRequest* req;
    UnBindDeviceResponse* resp;
    req = LCOPENAPI_INIT(UnBindDeviceRequest);
    resp = LCOPENAPI_INIT(UnBindDeviceResponse);
    req->data.token = CS(m_Token.toLatin1().data());
    req->data.deviceId = CS(deviceId.toLatin1().data());
    if (0 == m_OpenApiHandle->request(req, resp, 10))
    {
        if (HTTP_OK == resp->base.code)
        {
            if (!strcmp("0", resp->base.ret_code.cstr))
            {
                ret = true;
            }
        }
    }
    LCOPENAPI_DESTROY(req);
    LCOPENAPI_DESTROY(resp);

    return ret;
}

QString OpenApiCtrl::unBindDeviceInfo(QString deviceId,QString &ability)
{
    QString sRet;
	if (!m_IsGetTokenOK)
	{
		sRet = "get token error";
		return sRet;
	}
	
	UnBindDeviceInfoRequest* req;
    UnBindDeviceInfoResponse* resp;
	req = LCOPENAPI_INIT(UnBindDeviceInfoRequest);
	resp = LCOPENAPI_INIT(UnBindDeviceInfoResponse);
    req->data.token = CS(m_Token.toLatin1().data());
	req->data.deviceId = CS(deviceId.toLatin1().data());

	if (0 == m_OpenApiHandle->request(req, resp, 10))
	{
		if (HTTP_OK == resp->base.code)
		{
			if (!strcmp("0", resp->base.ret_code.cstr))
			{
				sRet = "OK";
				ability = QString(QLatin1String(resp->data.ability.cstr));
			}
			else
			{
                sRet = resp->base.ret_code.cstr;
			}
		}
		else
		{
            sRet = QString::number(resp->base.code);
		}
	}
	else
	{
        sRet = "request failed!";
	}
	LCOPENAPI_DESTROY(req);
	LCOPENAPI_DESTROY(resp);

	return sRet;
}

QString OpenApiCtrl::bindDeviceInfo(QString deviceId, int channelId, int& alarmStatus)
{
    QString sRet;
    if (!m_IsGetTokenOK)
    {
        sRet = "get token error";
        return sRet;
    }

    BindDeviceInfoRequest* req;
    BindDeviceInfoResponse* resp;
    req = LCOPENAPI_INIT(BindDeviceInfoRequest);
    resp = LCOPENAPI_INIT(BindDeviceInfoResponse);
    req->data.token = CS(m_Token.toLatin1().data());
    req->data.deviceId = CS(deviceId.toLatin1().data());

    if (0 == m_OpenApiHandle->request(req, resp, 10))
    {
        if (HTTP_OK == resp->base.code)
        {
            if (!strcmp("0", resp->base.ret_code.cstr))
            {
                sRet = "channel not found";
                int channelNum = resp->data.channels.size;
                for (int j = 0; j < channelNum; j++)
                {
                    if (channelId == resp->data.channels.array[j].channelId)
                    {
                        alarmStatus = resp->data.channels.array[j].alarmStatus;
                        sRet = "OK";
                        break;
                    }
                }
            }
            else
            {
                sRet = resp->base.ret_code.cstr;
            }
        }
        else
        {
            sRet = QString::number(resp->base.code);
        }
    }
    else
    {
        sRet = "request failed!";
    }
    LCOPENAPI_DESTROY(req);
    LCOPENAPI_DESTROY(resp);

    return sRet;
}

QString OpenApiCtrl::modifyDeviceAlarmStatus(QString deviceId, int channelId, bool flag)
{
    QString ret = "OK";

    if (!m_IsGetTokenOK)
    {
        ret = "get token error";
        return ret;
    }

    char strChannelId[16] = {0};
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
            ret = resp->base.ret_code.cstr;
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

    char strChannelId[16] = {0};
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
            ret = resp->base.ret_code.cstr;
            break;
        }

    } while (0);
    LCOPENAPI_DESTROY(req);
    LCOPENAPI_DESTROY(resp);

    return ret;
}

QString OpenApiCtrl::modifyDevicePassword(QString deviceId, QString oldPwd, QString newPwd)
{
    QString ret = "OK";

    if (!m_IsGetTokenOK)
    {
        ret = "get token error";
        return ret;
    }

    ModifyDevicePwdRequest* req;
    ModifyDevicePwdResponse* resp;
    req = LCOPENAPI_INIT(ModifyDevicePwdRequest);
    resp = LCOPENAPI_INIT(ModifyDevicePwdResponse);
    req->data.token = CS(m_Token.toLatin1().data());
    req->data.deviceId = CS(deviceId.toLatin1().data());
    req->data.oldPwd = CS(oldPwd.toLatin1().data());
    req->data.newPwd = CS(newPwd.toLatin1().data());
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
            ret = resp->base.ret_code.cstr;
            break;
        }

    } while (0);

    LCOPENAPI_DESTROY(req);
    LCOPENAPI_DESTROY(resp);

    return ret;
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
            ret = resp->base.ret_code.cstr;
            break;
        }

    } while (0);

    LCOPENAPI_DESTROY(req);
    LCOPENAPI_DESTROY(resp);

    return ret;
}

int OpenApiCtrl::getDeviceRecordNum(const RECORD_PARAMETERS &parameters)
{
	QJsonParseError jsonError;
	QJsonDocument json = QJsonDocument::fromJson(parameters.playInfo.c_str(), &jsonError);
	if (jsonError.error != QJsonParseError::NoError)
	{
		QString strError = jsonError.errorString();
	}

	if (!json.isObject())
	{
		return -1;
	}
	std::string token = json.object().value("userToken").toString().toStdString();
	std::string sourceType = json.object().value("sourceType").toString().toStdString();
	if (sourceType == "paas") //adapter for DHPaaS
	{
		return 10;
	}
	else
	{//sourceType == "lc";
		if (!m_IsGetTokenOK)
		{
			DLOG("get Token Failed!!!\n");
			return RET_FAIL;
		}

		QueryLocalRecordNumRequest *req;
		QueryLocalRecordNumResponse *resp;
		int ret = 0;
		char strCh[10] = { 0 };
		_snprintf(strCh, sizeof(strCh), "%d", parameters.channelId);
		req = LCOPENAPI_INIT(QueryLocalRecordNumRequest);
		resp = LCOPENAPI_INIT(QueryLocalRecordNumResponse);

		std::string userToken = "";
		std::vector<DEVICE_INFO> deviceVec = m_tokenCtrl->getDeviceVec();
		/*for (int i = 0; i< deviceVec.size(); i++)
		{*/
			//		Json::Reader reader;
			//		Json::Value root;
			/*QJsonParseError jsonError;
			QJsonDocument json = QJsonDocument::fromJson(deviceVec.at(i).playInfo.c_str(), &jsonError);
			if (jsonError.error != QJsonParseError::NoError)
			{
				QString strError = jsonError.errorString();
				continue;
			}

			if (!json.isObject())
			{
				continue;
			}*/

			userToken = json.object().value("userToken").toString().toStdString();
			//if (reader.parse(m_tokenCtrl.deviceVec.at(i).playInfo, root)) {
			//	userToken = root["userToken"].asString();
			//}
		//}

		req->base.uriPrefix =  CS("/openapi/");
		req->data.token = CS(userToken.c_str());
		req->data.deviceId = CS(parameters.deviceId.toLatin1().data());
		req->data.channelId = CS(strCh);
		req->data.beginTime = CS(parameters.beginTime.toLatin1().data());
		req->data.endTime = CS(parameters.endTime.toLatin1().data());

		do
		{
			DLOG_INFO("before m_OpenApiHandle->request");
			ret = m_OpenApiHandle->request(req, resp, 10, 0, parameters.playInfo.c_str());
			DLOG_INFO("after m_OpenApiHandle->request");
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
}

int OpenApiCtrl::getDeviceRecords(const RECORD_PARAMETERS &parameters, OUT RECORD_INFO_LIST *recordList, ThreadCtrl* ptr)
{
	int ret = 0;
	QJsonParseError jsonError;
	QJsonDocument json = QJsonDocument::fromJson(parameters.playInfo.c_str(), &jsonError);
	if (jsonError.error != QJsonParseError::NoError)
	{
		QString strError = jsonError.errorString();
	}

	if (!json.isObject())
	{
		return -1;
	}

	std::string token = json.object().value("userToken").toString().toStdString();
	std::string sourceType = json.object().value("sourceType").toString().toStdString();
	//if (sourceType == "paas") //adapter for DHPaaS
	if (1)
	{
		if (!m_tokenCtrl)
		{
			return -1;
		}

		m_tokenCtrl->getIOTPaaSQueryLocalRecords(parameters);
		m_tokenCtrl->setThreadCtrlPtr(ptr);
		QJsonObject queryLocalRecordsData = m_tokenCtrl->getLocalDeviceRecords();

		if (!queryLocalRecordsData.contains("records") || !queryLocalRecordsData["records"].isArray()) {
			qDebug() << "Missing or invalid 'records' array";
			return -1;
		}
		QJsonArray recordsArray = queryLocalRecordsData["records"].toArray();
		int size = recordsArray.size();

		RECORD_INFO *info = NULL;

		for (int i = 0; i < size; ++i)
		{
			info = new(std::nothrow)RECORD_INFO;
			if (NULL == info)
			{
				break;
			}
			QJsonValue value = recordsArray.at(i);
			if (value.isObject())
			{
				QJsonObject obj = value.toObject();

				info->name = obj["recordFileName"].toString();
				info->beginTime = obj["beginTime"].toString();
				info->endTime = obj["endTime"].toString();
				info->channelId = obj["channelID"].toString().toInt();
				info->fileLength = obj["fileLength"].toInt();
				info->deviceId = parameters.deviceId;
				info->index = recordList->size();
				info->token = token.c_str();
			}
			recordList->push_front(info);
		}
		ret = recordList->size();
		DLOG("get %d deviceRecord success\n", ret);
	}
	else
	{
		if (!m_IsGetTokenOK)
		{
			DLOG("get Token Failed!!!\n");
			return RET_FAIL;
		}

		if (NULL == recordList)
		{
			return RET_FAIL;
		}

		/* clear list */
		//TODO

		QueryLocalRecordsRequest *req;
		QueryLocalRecordsResponse *resp;

		char strCh[10] = { 0 };
		char strRange[100] = { 0 };
		_snprintf(strCh, sizeof(strCh) - 1, "%d", parameters.channelId);
		_snprintf(strRange, sizeof(strRange) - 1, "%d-%d", parameters.beginIndex, parameters.endIndex);
		req = LCOPENAPI_INIT(QueryLocalRecordsRequest);
		resp = LCOPENAPI_INIT(QueryLocalRecordsResponse);


		std::string userToken = "";
		std::vector<DEVICE_INFO> deviceVec = m_tokenCtrl->getDeviceVec();
		for (int i = 0; i< deviceVec.size(); i++)
		{
			//Json::Reader reader;
			//Json::Value root;

			QJsonParseError jsonError;
			QJsonDocument json = QJsonDocument::fromJson(deviceVec.at(i).playInfo.c_str(), &jsonError);
			if (jsonError.error != QJsonParseError::NoError)
			{
				QString strError = jsonError.errorString();
				continue;
			}

			if (!json.isObject())
			{
				continue;
			}

			userToken = json.object().value("userToken").toString().toStdString();

			//if (reader.parse(m_tokenCtrl.deviceVec.at(i).playInfo, root)) {
			//	userToken = root["userToken"].asString();
			//}
		}

		req->base.uriPrefix = CS("/openapi/");
		req->data.token = CS(userToken.c_str());

		// req->data.token = CS(m_Token.toLatin1().data());
		req->data.deviceId = CS(parameters.deviceId.toLatin1().data());
		req->data.channelId = CS(strCh);
		req->data.beginTime = CS(parameters.beginTime.toLatin1().data());
		req->data.endTime = CS(parameters.endTime.toLatin1().data());
		req->data.queryRange = CS(strRange);

		do
		{
			ret = m_OpenApiHandle->request(req, resp, 60, 0, parameters.playInfo.c_str());
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
				info->deviceId = parameters.deviceId;
				info->index = recordList->size();
				info->token = userToken.c_str();
				/* 瑕佹眰鏈€鏂扮殑鍦ㄦ渶鍓?*/
				recordList->push_front(info);
			}
			ret = recordList->size();
			DLOG("get %d deviceRecord success\n", ret);
		} while (0);

		if (req != NULL && resp != NULL)
		{
			LCOPENAPI_DESTROY(req);
			LCOPENAPI_DESTROY(resp);
		}
		return ret;
	}
}

int OpenApiCtrl::getCloudRecordNum(const RECORD_PARAMETERS &parameters)
{
	int ret = 0;
	QJsonParseError jsonError;
	QJsonDocument json = QJsonDocument::fromJson(parameters.playInfo.c_str(), &jsonError);
	if (jsonError.error != QJsonParseError::NoError)
	{
		QString strError = jsonError.errorString();
	}

	if (!json.isObject())
	{
		return -1;
	}

	std::string token = json.object().value("userToken").toString().toStdString();
	std::string sourceType = json.object().value("sourceType").toString().toStdString();

	if (sourceType == "paas") //adapter for DHPaaS
	{
		return 10;
	}
	else
	{//sourceType == "lc";
		if (!m_IsGetTokenOK)
		{
			DLOG("get Token Failed!!!\n");
			return RET_FAIL;
		}


		QueryCloudRecordNumRequest *req;
		QueryCloudRecordNumResponse *resp;

		std::string userToken = json.object().value("userToken").toString().toStdString();
		char strCh[10] = { 0 };
		_snprintf(strCh, sizeof(strCh), "%d", parameters.channelId);
		req = LCOPENAPI_INIT(QueryCloudRecordNumRequest);
		resp = LCOPENAPI_INIT(QueryCloudRecordNumResponse);
		req->data.token = CS(userToken.c_str());
		req->data.deviceId = CS(parameters.deviceId.toLatin1().data());
		req->data.channelId = CS(strCh);
		req->data.beginTime = CS(parameters.beginTime.toLatin1().data());
		req->data.endTime = CS(parameters.endTime.toLatin1().data());

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
	}
    return ret;
}

int OpenApiCtrl::getCloudRecords(const RECORD_PARAMETERS &parameters, OUT RECORD_INFO_LIST *recordList, ThreadCtrl* ptr)
{
	int ret = 0;
	QJsonParseError jsonError;
	QJsonDocument json = QJsonDocument::fromJson(parameters.playInfo.c_str(), &jsonError);
	if (jsonError.error != QJsonParseError::NoError)
	{
		QString strError = jsonError.errorString();
	}

	if (!json.isObject())
	{
		return -1;
	}

	std::string token = json.object().value("userToken").toString().toStdString();
	std::string sourceType = json.object().value("sourceType").toString().toStdString();
	//if (sourceType == "paas") //adapter for DHPaaS
	if (1)
	{
		if (!m_tokenCtrl)
		{
			return -1;
		}

		m_tokenCtrl->getIOTQueryCloudRecords(parameters);
		m_tokenCtrl->setThreadCtrlPtr(ptr);
		QJsonObject queryCloudRecordsData = m_tokenCtrl->getCloudRecords();

		if (!queryCloudRecordsData.contains("records") || !queryCloudRecordsData["records"].isArray()) {
			qDebug() << "Missing or invalid 'records' array";
			return -1;
		}
		QJsonArray recordsArray = queryCloudRecordsData["records"].toArray();
		int size = recordsArray.size();

		RECORD_INFO *info = NULL;

		for (int i = 0; i < size; ++i)
		{
			info = new(std::nothrow)RECORD_INFO;
			if (NULL == info)
			{
				break;
			}
			QJsonValue value = recordsArray.at(i);
			if (value.isObject())
			{
				QJsonObject obj = value.toObject();

				info->beginTime = obj["beginTime"].toString();
				info->endTime = obj["endTime"].toString();
				info->channelId = obj["channelID"].toString().toInt();
				//info->fileLength = obj["fileLength"].toInt();
				info->deviceId = obj["deviceId"].toString();

				info->name = obj["recordId"].toString();
				info->recordRegionId = obj["recordRegionId"].toString();
				info->recordPath = obj["recordPath"].toString();
				//info->signatureUrl = obj["signatureUrl"].toString();

				info->index = recordList->size();
				info->token = token.c_str();
			}
			recordList->push_front(info);
		}
		ret = recordList->size();

		DLOG("get %d deviceRecord success\n", ret);
	}

    //if (!m_IsGetTokenOK)
    //{
    //    DLOG("get Token Failed!!!\n");
    //    return RET_FAIL;
    //}

    //if ( NULL == recordList)
    //{
    //    return RET_FAIL;
    //}

    ///* clear list */
    ////TODO

    //QueryCloudRecordsRequest *req;
    //QueryCloudRecordsResponse *resp;
    //char strCh[20] = {0};
    //char strRange[50] = {0};
    //_snprintf(strCh, sizeof(strCh), "%d", parameters.channelId);
    //_snprintf(strRange, sizeof(strRange), "%d-%d", parameters.beginIndex, parameters.endIndex);
    //req = LCOPENAPI_INIT(QueryCloudRecordsRequest);
    //resp = LCOPENAPI_INIT(QueryCloudRecordsResponse);
    //req->data.token = CS(m_Token.toLatin1().data());
    //req->data.deviceId = CS(parameters.deviceId.toLatin1().data());
    //req->data.channelId = CS(strCh);
    //req->data.queryRange = CS(strRange);
    //req->data.beginTime = CS(parameters.beginTime.toLatin1().data());
    //req->data.endTime = CS(parameters.endTime.toLatin1().data());

    //do 
    //{
    //    ret = m_OpenApiHandle->request(req, resp, 10);
    //    if (ret != 0)
    //    {
    //        DLOG("request failed[%d]\n", ret);
    //        ret = HTTP_ERR;
    //        break;
    //    }

    //    int code = resp->base.code;
    //    const char *desc = resp->base.desc.cstr;
    //    char * ret_code = resp->base.ret_code.cstr;
    //    if (HTTP_OK != code)
    //    {
    //        ret = HTTP_ERR;
    //        DLOG("HTTP_ERR[%d]\n", code);
    //        break;
    //    }

    //    if (0 != strcmp(ret_code, "0"))
    //    {
    //        ret = BUSINESS_ERR;
    //        DLOG("BUSINESS_ERR[%s]\n", ret_code);
    //        break;
    //    }

    //    int size = resp->data.records.size;
    //    recInfo *info = NULL;
    //    for (int i = 0; i < size; ++i)
    //    {
    //        info = new(std::nothrow)recInfo;
    //        if (NULL == info)
    //        {
    //            break;
    //        }

    //        info->name.asprintf("%s-%s",
    //            resp->data.records.array[i].beginTime.cstr, resp->data.records.array[i].endTime.cstr);
    //        info->beginTime = resp->data.records.array[i].beginTime.cstr;
    //        info->endTime = resp->data.records.array[i].endTime.cstr;
    //        info->deviceId = resp->data.records.array[i].deviceId.cstr;
    //        info->thumbUrl = resp->data.records.array[i].thumbUrl.cstr;
    //        info->channelId = atoi(resp->data.records.array[i].channelId.cstr);
    //        info->recId = resp->data.records.array[i].recordId.cstr;
    //        info->fileLength = QString(resp->data.records.array[i].size.cstr).toLongLong();

    //        info->index = recordList->size();

    //        /* 瑕佹眰鏈€鏂扮殑鍦ㄦ渶鍓?*/
    //        recordList->push_front(info);
    //    }
    //    ret = recordList->size();
    //    DLOG("get %d cloudRecord success\n", ret);
    //} while (0);

    //LCOPENAPI_DESTROY(req);
    //LCOPENAPI_DESTROY(resp);
    //return ret;
}



int OpenApiCtrl::controlPTZ(const PTZ_CONTROL_PARAMETERS &parameters)
{
    ControlPTZRequest *req;
    ControlPTZResponse *resp;

    int ret = 0;
    char iCh[10]={0};
    char strDuration[10] = {0};
    _snprintf(iCh, sizeof(iCh), "%d", parameters.channelId);
    _snprintf(strDuration, sizeof(strDuration), "%d", parameters.duration);
    req = LCOPENAPI_INIT(ControlPTZRequest);
    resp = LCOPENAPI_INIT(ControlPTZResponse);
	req->base.uriPrefix = CS("/openapi/");
    req->data.deviceId = CS(parameters.deviceId.toStdString().c_str());
    req->data.duration = CS(strDuration);
    req->data.channelId = CS(iCh);
    req->data.h = parameters.horizon;
    req->data.v = parameters.vertical;
    req->data.z = parameters.zoom;
    req->data.operation = CS(parameters.operate.toStdString().c_str());

	
	std::string userToken = "";
    std::vector<DEVICE_INFO> deviceVec = m_tokenCtrl->getDeviceVec();
	for (int i = 0; i< deviceVec.size(); i++)
	{
		//Json::Reader reader;
		//Json::Value root;

        QJsonParseError jsonError;
        QJsonDocument json = QJsonDocument::fromJson(deviceVec.at(i).playInfo.c_str(), &jsonError);
        if (jsonError.error != QJsonParseError::NoError)
        {
            QString strError = jsonError.errorString();
            continue;
        }

        if (!json.isObject())
        {
            continue;
        }

        userToken = json.object().value("userToken").toString().toStdString();

		//if (reader.parse(m_tokenCtrl.deviceVec.at(i).playInfo, root)) {
		//	userToken = root["userToken"].asString();
		//}
	}

	req->data.token = CS(userToken.c_str());

    //req->data.token = CS(m_IOTToken.toStdString().c_str());

    do 
    {
        ret = m_OpenApiHandle->request(req, resp, 10, 0, parameters.playInfo.c_str());
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

        ret = 0;
        DLOG("control PTZ success\n");
    } while (0);

    LCOPENAPI_DESTROY(req);
    LCOPENAPI_DESTROY(resp);
    return ret;
}

int OpenApiCtrl::controlPaaSPTZ(const PTZ_CONTROL_PARAMETERS &parameters)
{
	PaaSPTZMoveRequest *req;
	ControlPTZResponse *resp;

	int ret = 0;
	char iCh[10] = { 0 };
	_snprintf(iCh, sizeof(iCh), "%d", parameters.channelId);
	req = LCOPENAPI_INIT(PaaSPTZMoveRequest);
	resp = LCOPENAPI_INIT(ControlPTZResponse);
	req->data.duration = parameters.duration;
	req->data.horizontal = parameters.horizon;
	req->data.vertical = parameters.vertical;

	std::string userToken = "";
	std::string DeviceId = "";
	QString strHost = "";
	int port = 0;
	std::vector<DEVICE_INFO> deviceVec = m_tokenCtrl->getDeviceVec();
	for (int i = 0; i< deviceVec.size(); i++)
	{
		//Json::Reader reader;
		//Json::Value root;

		QJsonParseError jsonError;
		QJsonDocument json = QJsonDocument::fromJson(deviceVec.at(i).playInfo.c_str(), &jsonError);
		if (jsonError.error != QJsonParseError::NoError)
		{
			QString strError = jsonError.errorString();
			continue;
		}

		if (!json.isObject())
		{
			continue;
		}
		QJsonObject rootObject = json.object();
		QJsonObject streamInfo = rootObject.value("streamInfo").toObject();
		std::string streamEntryAddr = streamInfo.value("streamEntryAddr").toString().toStdString();

		QString qStrStreamEntryAddr = QString::fromStdString(streamEntryAddr);
		int lastIndex = qStrStreamEntryAddr.lastIndexOf(":");
		QString strPost = qStrStreamEntryAddr.mid(lastIndex + 1);
		port = strPost.toInt();
		strHost = qStrStreamEntryAddr.left(lastIndex);
		strHost = strHost.mid(strHost.lastIndexOf("/") + 1);
		

		userToken = json.object().value("userToken").toString().toStdString();
		//channelId = json.object().value("userToken").toString().toStdString();
		DeviceId = json.object().value("deviceId").toString().toStdString();
		std::string host = streamEntryAddr;

		//if (reader.parse(m_tokenCtrl.deviceVec.at(i).playInfo, root)) {
		//	userToken = root["userToken"].asString();
		//}
	}
	std::string channelId = std::to_string(parameters.channelId);;

	req->base.paasAccessToken = CS(userToken.c_str());
	req->base.paasChannelId = CS((DeviceId + "-" + channelId.c_str()).c_str());
	req->base.paasDeviceId = CS(DeviceId.c_str());
	req->base.sourceType = CS("paas");
	req->base.host = CS(strHost.toStdString().c_str());
	req->base.port = port;
	req->base.uriPrefix = CS("/");
	req->base.protoType = 1;
	req->base.iotAccessToken = CS("fake_iot_token");
	req->base.iUseKeepAlive = 1;

	do
	{
		ret = m_OpenApiHandle->request(req, resp, 10, 0, parameters.playInfo.c_str());
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

		ret = 0;
		DLOG("control PTZ success\n");
	} while (0);

	LCOPENAPI_DESTROY(req);
	LCOPENAPI_DESTROY(resp);
	return ret;
}

