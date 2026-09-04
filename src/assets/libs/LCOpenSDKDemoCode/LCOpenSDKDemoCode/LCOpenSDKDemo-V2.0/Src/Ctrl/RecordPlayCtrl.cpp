#include <QDateTime>
#include "lcopensdk_videoplay/LCOpenSDK_VideoPlay.h"
#include "Src/Utils/global.h"
#include "Src/Ctrl/OpenApiCtrl.h"
#include "Src/Ctrl/RecordListCtrl.h"
#include "Src/Ctrl/DevicesListCtrl.h"
#include "RecordPlayCtrl.h"

RecordPlayCtrl::RecordPlayCtrl()
	: PlayCtrl(PLAYCTRL_CLOUDPLAY)
	, m_recordInfo(NULL)
{

}

RecordPlayCtrl::~RecordPlayCtrl()
{

}

int RecordPlayCtrl::playCloudRecord(int deviceIndex, int recordIndex, const char *key)
{
	setPlayCtrlType(PLAYCTRL_CLOUDPLAY);
	m_recordInfo = NULL;
	int ret = 0;
	do
	{
		if (!m_isInit)
		{
			DLOG("please call init() first!!!\n");
			ret = -1;
			break;
		}

		/* 查询录像详细信息 */
		m_recordInfo = RecordListCtrl::getInstance()->getRecordInfoByIndex(recordIndex);
		if (NULL == m_recordInfo)
		{
			ret = -2;
			break;
		}

		/* 查询设备详细信息 */
		m_deviceInfo = DevicesListCtrl::getInstance()->getChannelInfo(deviceIndex);
		if (NULL == m_deviceInfo)
		{
			ret = -4;
			break;
		}

		if (key == NULL)
		{
			QString decryptKey = DevicesListCtrl::getInstance()->getDecryptKeyByDeviceID(m_recordInfo->deviceId);
			/*LCOpenSDK_ParamCloudRecord */
			LCOpenSDK_ParamCloudRecord stuRecordInfo;
			std::string strAccessToken = OpenApiCtrl::getInstance()->getToken().toStdString();
			stuRecordInfo.accessToken = strAccessToken.c_str();
			std::string strDeviceID = m_recordInfo->deviceId.toStdString();
			stuRecordInfo.deviceID = strDeviceID.c_str();
			std::string strPid = m_deviceInfo->productId.toStdString();
			stuRecordInfo.pid = strPid.c_str();
			stuRecordInfo.channel = m_recordInfo->channelId;
			std::string strPSK = decryptKey.toStdString();
			stuRecordInfo.psk = strPSK.c_str();
			std::string strPlayToken = m_deviceInfo->playToken.toStdString();
			stuRecordInfo.playToken = strPlayToken.c_str();
			std::string strRecordRegionID = m_recordInfo->recordRegionId.toStdString();
			stuRecordInfo.recordRegionID = strRecordRegionID.c_str();
			stuRecordInfo.offsetTime = 0;
			stuRecordInfo.recordType = RECORD_TYPE_ALARM;
			stuRecordInfo.timeout = 86400;
			videoPlayReset();
			ret = m_videoPlay->playCloudEx(&stuRecordInfo);
			// ret = m_videoPlay->playCloud(OpenApiCtrl::getInstance()->getToken().toStdString().c_str(), m_recordInfo->deviceId.toStdString().c_str(), m_recordInfo->channelId,
			// 	decryptKey.toStdString().c_str(), m_recordInfo->recordRegionId.toStdString().c_str(), 0, 1000, 86400);
		}
		else
		{
			LCOpenSDK_ParamCloudRecord stuRecordInfo;
			std::string strAccessToken = OpenApiCtrl::getInstance()->getToken().toStdString();
			stuRecordInfo.accessToken = strAccessToken.c_str();
			std::string strDeviceID = m_recordInfo->deviceId.toStdString();
			stuRecordInfo.deviceID = strDeviceID.c_str();
			std::string strPid = m_deviceInfo->productId.toStdString();
			stuRecordInfo.pid = strPid.c_str();
			stuRecordInfo.channel = m_recordInfo->channelId;
			std::string strPSK = key;
			stuRecordInfo.psk = strPSK.c_str();
			std::string strPlayToken = m_deviceInfo->playToken.toStdString();
			stuRecordInfo.playToken = strPlayToken.c_str();
			std::string strRecordRegionID = m_recordInfo->recordRegionId.toStdString();
			stuRecordInfo.recordRegionID = strRecordRegionID.c_str();
			stuRecordInfo.offsetTime = 0;
			stuRecordInfo.recordType = RECORD_TYPE_ALARM;
			stuRecordInfo.timeout = 86400;
			videoPlayReset();
			ret = m_videoPlay->playCloudEx(&stuRecordInfo);
			// ret = m_videoPlay->playCloud(OpenApiCtrl::getInstance()->getToken().toStdString().c_str(), m_recordInfo->deviceId.toStdString().c_str(), m_recordInfo->channelId,
			// 	key, m_recordInfo->recordRegionId.toStdString().c_str(), 0, 1000, 86400);
		}
	} while (0);

	DLOG("RecordPlayCtrl::playCloudRecord>[%d]\n", ret);
	emit sgnPlayerStatusChanged(0 == ret ? STATUS_LOADING : STATUS_FAIL);
	return ret;
}

int RecordPlayCtrl::playDeviceRecord(int deviceIndex, int recordIndex)
{
	setPlayCtrlType(PLAYCTRL_DEVICEPLAY);
	m_recordInfo = NULL;
	int ret = 0;
	do
	{
		if (!m_isInit)
		{
			DLOG("please call init() first!!!\n");
			ret = -1;
			break;
		}

		/* 查询录像详细信息 */
		m_recordInfo = RecordListCtrl::getInstance()->getRecordInfoByIndex(recordIndex);
		if (NULL == m_recordInfo)
		{
			ret = -2;
			break;
		}

		/* 查询设备详细信息 */
		m_deviceInfo = DevicesListCtrl::getInstance()->getChannelInfo(deviceIndex);
		if (NULL == m_deviceInfo)
		{
			ret = -4;
			break;
		}

		QDateTime beginTime = QDateTime::fromString(m_recordInfo->beginTime, "yyyy-MM-dd HH:mm:ss");
		QDateTime endTime = QDateTime::fromString(m_recordInfo->endTime, "yyyy-MM-dd HH:mm:ss");

		int beginTimeTmp = beginTime.toTime_t();
		int endTimeTmp = endTime.toTime_t();
		QString decryptKey = DevicesListCtrl::getInstance()->getDecryptKeyByDeviceID(m_recordInfo->deviceId);
		/* playDeviceRecord */
		//ret = m_videoPlay->playDeviceRecord(OpenApiCtrl::getInstance()->getToken().toStdString().c_str(), m_recordInfo->deviceId.toStdString().c_str(), decryptKey.toStdString().c_str(), m_recordInfo->channelId, m_recordInfo->name.toStdString().c_str(), beginTime.toTime_t(), endTime.toTime_t(), 0, true);

		/* playDeviceRecordByFileName */
// 		LCOpenSDK_ParamDeviceRecordFileName stuRecordInfo;
// 		std::string strAccessToken = OpenApiCtrl::getInstance()->getToken().toStdString();
// 		stuRecordInfo.accessToken = strAccessToken.c_str();
// 		std::string strDeviceID = m_recordInfo->deviceId.toStdString();
// 		stuRecordInfo.deviceID = strDeviceID.c_str();
// 		std::string strPid = m_deviceInfo->productId.toStdString();
// 		stuRecordInfo.pid = strPid.c_str();
// 		stuRecordInfo.channel = m_recordInfo->channelId;
// 		std::string strPSK = decryptKey.toStdString();
// 		stuRecordInfo.psk = strPSK.c_str();
// 		std::string strPlayToken = m_deviceInfo->playToken.toStdString();
// 		stuRecordInfo.playToken = strPlayToken.c_str();
// 		std::string strFileName = m_recordInfo->name.toStdString();
// 		stuRecordInfo.fileName = strFileName.c_str();
// 		stuRecordInfo.offsetTime = 0;
// 		stuRecordInfo.isTls = m_deviceInfo->tlsEnable;
//		videoPlayReset();
// 		ret = m_videoPlay->playDeviceRecordByFileNameEx(&stuRecordInfo);
		//ret = m_videoPlay->playDeviceRecordByFileName(OpenApiCtrl::getInstance()->getToken().toStdString().c_str(), m_recordInfo->deviceId.toStdString().c_str(), decryptKey.toStdString().c_str(), m_recordInfo->name.toStdString().c_str(), 0, true);

		/* playDeviceRecordByUtcTime */
		LCOpenSDK_ParamDeviceRecordUTCTime stuRecordInfo;
		std::string strAccessToken = OpenApiCtrl::getInstance()->getToken().toStdString();
		stuRecordInfo.accessToken = strAccessToken.c_str();
		std::string strDeviceID = m_recordInfo->deviceId.toStdString();
		stuRecordInfo.deviceID = strDeviceID.c_str();
		std::string strPid = m_deviceInfo->productId.toStdString();
		stuRecordInfo.pid = strPid.c_str();
		stuRecordInfo.channel = m_recordInfo->channelId;
		stuRecordInfo.beginTime = beginTimeTmp;
		stuRecordInfo.defiMode = DEFINITION_MODE::STREAM_MAIN;
		stuRecordInfo.endTime = endTimeTmp;
		std::string strPSK = decryptKey.toStdString();
		stuRecordInfo.psk = strPSK.c_str();
		std::string strPlayToken = m_deviceInfo->playToken.toStdString();
		stuRecordInfo.playToken = strPlayToken.c_str();
		stuRecordInfo.isTls = m_deviceInfo->tlsEnable;
		stuRecordInfo.offsetTime = 0.0;
		videoPlayReset();
		ret = m_videoPlay->playDeviceRecordByUtcTimeEx(&stuRecordInfo);
		//ret = m_videoPlay->playDeviceRecordByUtcTime(OpenApiCtrl::getInstance()->getToken().toStdString().c_str(), m_recordInfo->deviceId.toStdString().c_str(), decryptKey.toStdString().c_str(), m_recordInfo->channelId, beginTimeTmp, endTimeTmp, 0, true);
	} while (0);

	DLOG("RecordPlayCtrl::playDeviceRecord>[%d]\n", ret);
	emit sgnPlayerStatusChanged(0 == ret ? STATUS_LOADING : STATUS_FAIL);
	return ret;
}

int RecordPlayCtrl::stopPlay()
{
	int ret = 0;
	do
	{
		if (!m_isInit)
		{
			DLOG("please call init() first!!!\n");
			ret = -1;
			break;
		}

		if (DEVICE_RECORD == m_recordType)
		{
			ret = m_videoPlay->stopDeviceRecord();
		}
		else
		{
			ret = m_videoPlay->stopCloud();
		}
	} while (0);

	m_isPause = false;
	DLOG("RecordPlayCtrl::stopPlay>[%d]\n", ret);
	return ret;
}

int RecordPlayCtrl::setPlayBackSpeed(int speed)
{
	int ret = 0;
	do
	{
		if (!m_isInit)
		{
			DLOG("please call init() first!!!\n");
			ret = -1;
			break;
		}
		ret = m_videoPlay->setPlaySpeed((float)speed);
	} while (0);

	DLOG("RecordPlayCtrl::setPlaySpeed>[%d]  [%f]\n", ret, (float)speed);
	return ret;
}

int RecordPlayCtrl::seek(long seconds)
{
	int ret = 0;
	do
	{
		if (!m_isInit)
		{
			DLOG("please call init() first!!!\n");
			ret = -1;
			break;
		}
		ret = m_videoPlay->seek(seconds);
	} while (0);

	DLOG("RecordPlayCtrl::seek>[%d]\n", ret);
	return ret;
}

int RecordPlayCtrl::pause()
{
	int ret = 0;
	do
	{
		if (!m_isInit)
		{
			DLOG("please call init() first!!!\n");
			ret = -1;
			break;
		}

		ret = m_videoPlay->pause();
		if (0 == ret)
		{
			emit sgnPlayerStatusChanged(STATUS_PAUSE);
		}
	} while (0);

	DLOG("RecordPlayCtrl::pause>[%d]\n", ret);
	m_isPause = (0 == ret);
	return ret;
}

int RecordPlayCtrl::resume()
{
	int ret = 0;
	do
	{
		if (!m_isInit)
		{
			DLOG("please call init() first!!!\n");
			ret = -1;
			break;
		}

		ret = m_videoPlay->resume();
		if (0 == ret)
		{
			emit sgnPlayerStatusChanged(STATUS_RESUME);
		}
	} while (0);

	DLOG("RecordPlayCtrl::resume>[%d]\n", ret);
	m_isPause = !(0 == ret);
	return ret;
}

void RecordPlayCtrl::onPlayCloudRecordResult(int index, int code, int resultSource)
{
	if (0 == code)
	{
		DLOG("onPlayCloudRecordResult[HLS_DOWNLOAD_FAILD]\n");
	}
	else if (1 == code)
	{
		DLOG("onPlayCloudRecordResult[HLS_DOWNLOAD_BEGIN]\n");
		return;
	}
	else if (2 == code)
	{
		DLOG("onPlayCloudRecordResult[HLS_DOWNLOAD_END]\n");
		return;
	}
	else if (3 == code)
	{
		emit sgnPlayerStatusChanged(STATUS_SEEK_SUCCESS);
		DLOG("onPlayCloudRecordResult[HLS_SEEK_SUCCESS]\n");
		return;
	}
	else if (4 == code)
	{
		emit sgnPlayerStatusChanged(STATUS_SEEK_FAILD);
		DLOG("onPlayCloudRecordResult[HLS_SEEK_FAILD]\n");
	}
	else if (5 == code)
	{
		DLOG("onPlayCloudRecordResult[HLS_ABORT_DONE]\n");
	}
	else if (6 == code)
	{
		DLOG("onPlayCloudRecordResult[HLS_RESUME_DONE]\n");
		return;
	}
	else if (code == 11 || code == 14)
	{
		emit sgnPlayerError(code);
		DLOG("onPlayCloudRecordResult[HLS_KEY_ERROR]\n");
	}
	else
	{
		DLOG("onPlayCloudRecordResult[%d]\n", code);
	}

	m_isPlaying = false;
	emit sgnPlayerStatusChanged(STATUS_FAIL);
}

void RecordPlayCtrl::onPlayFinished(int index)
{
	DLOG("RecordPlayCtrl::onPlayFinished\n");
	m_isPlaying = false;
	emit sgnPlayerStatusChanged(STATUS_STOP);
}

void RecordPlayCtrl::onPlayerTime(int index, long time)
{
	//DLOG("RecordPlayCtrl::onPlayerTime-%d\n", time);
	emit sgnPlayerTime(time);
}
