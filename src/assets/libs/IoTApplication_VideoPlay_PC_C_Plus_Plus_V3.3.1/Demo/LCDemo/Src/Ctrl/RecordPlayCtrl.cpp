#include <QDateTime>
#include "LCOpenSDK_VideoPlay.h"
#include "Utils/global.h"
#include "Ctrl/OpenApiCtrl.h"
#include "Ctrl/RecordListCtrl.h"
#include "Ctrl/DevicesListCtrl.h"
//#include <Third_Include/Json/json.h>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include "RecordPlayCtrl.h"

RecordPlayCtrl::RecordPlayCtrl()
    : PlayCtrl(PLAYCTRL_CLOUDPLAY)
    , m_recordInfo(NULL)
{

}

RecordPlayCtrl::~RecordPlayCtrl()
{

}

int RecordPlayCtrl::playCloudRecord(int deviceIndex,int recordIndex)
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

/* Query record detail info */
        m_recordInfo = RecordListCtrl::getInstance()->getRecordInfoByIndex(recordIndex);
        if (NULL == m_recordInfo)
        {
            ret = -2;
            break;
        }

		m_iotDeviceList = DevicesListCtrl::getInstance()->getIOTChannelInfo(deviceIndex);
		if (NULL == m_iotDeviceList)
		{
			ret = -4;
			break;
		}

		// playInfo
		std::string playInfo = m_iotDeviceList->playInfo;
		qDebug() << "record playInfo: " << playInfo.c_str();

		QJsonParseError jsonError;
		QJsonDocument json = QJsonDocument::fromJson(playInfo.c_str(), &jsonError);
		if (jsonError.error != QJsonParseError::NoError)
		{
			QString strError = jsonError.errorString();
			break;
		}
		if (!json.isObject())
		{
			break;
		}
		std::string token = "";
		token = json.object().value("userToken").toString().toStdString();

		QDateTime beginTime = QDateTime::fromString(m_recordInfo->beginTime, "yyyy-MM-dd HH:mm:ss");
		QDateTime endTime = QDateTime::fromString(m_recordInfo->endTime, "yyyy-MM-dd HH:mm:ss");




        QString decryptKey = DevicesListCtrl::getInstance()->getDecryptKeyByDeviceID(m_recordInfo->deviceId);


        //ret = m_videoPlay->playCloud(OpenApiCtrl::getInstance()->getToken().toStdString().c_str(), m_recordInfo->deviceId.toStdString().c_str(), m_recordInfo->channelId, decryptKey.toStdString().c_str(),
			//m_recordInfo->recId.toStdString().c_str(), 0, 1000, 86400);

		//by file
		ret = m_videoPlay->playCloud(m_recordInfo->deviceId.toStdString().c_str(), m_recordInfo->channelId, m_recordInfo->deviceId.toStdString().c_str(),m_recordInfo->recId.toStdString().c_str(),
			0, playInfo.c_str(), m_recordInfo->signatureUrl.toStdString().c_str(), m_recordInfo->recordPath.toStdString().c_str(), m_recordInfo->recordRegionId.toStdString().c_str());

		// by time
		/*ret = m_videoPlay->playCloud(token.c_str(), m_recordInfo->deviceId.toStdString().c_str(), m_recordInfo->channelId, decryptKey.toStdString().c_str(), "",
			0, playInfo.c_str(), m_recordInfo->signatureUrl.toStdString().c_str(), m_recordInfo->recordPath.toStdString().c_str(), m_recordInfo->recordRegionId.toStdString().c_str(), 1000);*/

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

/* Query record detail info */
        m_recordInfo = RecordListCtrl::getInstance()->getRecordInfoByIndex(recordIndex);
        if (NULL == m_recordInfo)
        {
            ret = -2;
            break;
        }

		m_iotDeviceList = DevicesListCtrl::getInstance()->getIOTChannelInfo(deviceIndex);
		if (NULL == m_iotDeviceList)
		{
			ret = -4;
			break;
		}

		// playInfo
		std::string playInfo = m_iotDeviceList->playInfo;
	//	Json::Reader reader;
	//	Json::Value root;
        QJsonParseError jsonError;
        QJsonDocument json = QJsonDocument::fromJson(playInfo.c_str(), &jsonError);
        if (jsonError.error != QJsonParseError::NoError)
        {
            QString strError = jsonError.errorString();
            break;
        }

        if (!json.isObject())
        {
            break;
        }
        std::string token = "";
        token = json.object().value("userToken").toString().toStdString();
	

		//if (reader.parse(playInfo, root)) {
		//	token = root["userToken"].asString();
		//}

        QDateTime beginTime = QDateTime::fromString(m_recordInfo->beginTime, "yyyy-MM-dd HH:mm:ss");
        QDateTime endTime = QDateTime::fromString(m_recordInfo->endTime, "yyyy-MM-dd HH:mm:ss");

		ret = m_videoPlay->playDeviceRecord(token.c_str(), m_recordInfo->deviceId.toStdString().c_str(), m_iotDeviceList->decryptKey.c_str(),
			m_recordInfo->channelId, m_recordInfo->name.toStdString().c_str(), beginTime.toTime_t(), endTime.toTime_t(), 0, playInfo.c_str(), true);
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

int RecordPlayCtrl::setPlaySpeed(float speed)
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
		ret = m_videoPlay->setPlaySpeed(speed);
		if (ret == 0)
		{
			m_isSpeedPlay = (speed != 1.0f);
			emit sgnPlayerStatusChanged(STATUS_SPEEDPLAY);
		}
	} while (0);

	DLOG("RecordPlayCtrl::setPlaySpeed>[%d], speed[%.1f]\n", ret, speed);
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
    if(0 == code)
    {
        DLOG("onPlayCloudRecordResult[HLS_DOWNLOAD_FAILD]\n");
    }
    else if(1 == code)
    {
        DLOG("onPlayCloudRecordResult[HLS_DOWNLOAD_BEGIN]\n");
        return;
    }
    else if(2 == code)
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
    else if(4 == code)
    {
        emit sgnPlayerStatusChanged(STATUS_SEEK_FAILD);
        DLOG("onPlayCloudRecordResult[HLS_SEEK_FAILD]\n");
    }
    else if(5 == code)
    {
        DLOG("onPlayCloudRecordResult[HLS_ABORT_DONE]\n");
    }
    else if (6 == code)
    {
        DLOG("onPlayCloudRecordResult[HLS_RESUME_DONE]\n");
        return;
    }
	else if (9 == code)
	{
		DLOG("onPlayCloudRecordResult[HLS_SLICE_DONE]\n");
		return;
	}
	else if (10 == code)
	{
		DLOG("onPlayCloudRecordResult[HLS_PAUSE_DONE]\n");
		return;
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
