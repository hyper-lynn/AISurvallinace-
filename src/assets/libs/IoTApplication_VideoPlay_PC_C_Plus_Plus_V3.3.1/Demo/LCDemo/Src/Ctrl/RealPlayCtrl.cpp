#include <QDir>
#include <QDateTime>
#include "LCOpenSDK_VideoPlay.h"
#include "LCOpenSDK_AudioTalk.h"
#include "LCOpenSdk_Utils.h"
#include "Utils/global.h"
#include "Ctrl/OpenApiCtrl.h"
#include "Ctrl/DevicesListCtrl.h"
#include "Model/threadinfo.h"
#include "Ctrl/ThreadCtrl.h"
#include "RealPlayCtrl.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iterator>

RealPlayCtrl::RealPlayCtrl()
    : PlayCtrl(PLAYCTRL_REALPLAY)
    , m_audioTalk(NULL)
	, m_index(-1)
    , m_isTalking(false)
    , m_threadCtrl(NULL)
    , m_isTalkingBak(false)
{
    connect(this, SIGNAL(sgnPlayerStatusChanged(int)), this, SLOT(slotPlayerStatusChanged(int)));
}

RealPlayCtrl::~RealPlayCtrl()
{
    if (m_audioTalk)
    {
		m_audioTalk->stopSound();
        m_audioTalk->stopTalk();
    }

    if (m_threadCtrl)
    {
        m_threadCtrl->quit();
        m_threadCtrl->deleteLater();
    }
}

int RealPlayCtrl::init(QWidget* videoBase)
{
    int ret = 0;
    do 
    {
        ret = PlayCtrl::init(videoBase);
        m_isInit = false;
        if (0 != ret)
        {
            ret = -3;
            break;
        }

        m_audioTalk = LCOpenSDK_AudioTalk::GetInstance();
        if (NULL == m_audioTalk)
        {
            ret = -1;
            break;
        }
        m_audioTalk->setTalkerListener(this);

        m_threadCtrl = new ThreadCtrl(this, PROTO_PTZ_CTRL);
        if (NULL == m_audioTalk)
        {
            ret = -1;
            break;
        }

        m_isInit = true;
    } while (0);

    return ret;
}

int RealPlayCtrl::play(int deviceIndex, int definitionMode)
{
	/* Stop previous playback first */
	stopPlay();
	int ret = 0;
	m_deviceIndex = deviceIndex;

	/* Look up the device and channel info by view index */
	ViewDeviceInfo viewInfo = DevicesListCtrl::getInstance()->getViewDeviceInfo(deviceIndex);
	if (viewInfo.deviceListIndex < 0)
	{
		return -4;
	}

	m_iotDeviceList = DevicesListCtrl::getInstance()->getIOTChannelInfo(viewInfo.deviceListIndex);
	if (NULL == m_iotDeviceList)
	{
		ret = -4;
		return ret;
	}

	// playInfo
	std::string playInfo = m_iotDeviceList->playInfo;
	qDebug() << "playInfo: " << playInfo.c_str();

	// Parse playInfo JSON to get token
	QJsonParseError jsonError;
	QJsonDocument json = QJsonDocument::fromJson(playInfo.c_str(), &jsonError);
	if (jsonError.error != QJsonParseError::NoError)
	{
		QString strError = jsonError.errorString();
		return -1;
	}

	if (!json.isObject())
	{
		return -1;
	}

	std::string token = json.object().value("userToken").toString().toStdString();

	/* Determine channelId based on multi-channel or single-channel device */
	int channlID = 0;
	if (viewInfo.channelIndex >= 0)
	{
		/* Multi-channel device: use the channel's channelId from iotChannel */
		std::string chanID = m_iotDeviceList->iotChannel[viewInfo.channelIndex]->channelId;
		qDebug() << "channelId str: " << chanID.c_str();
		channlID = atoi(chanID.c_str());

		/* Parse device ability */
		if (false == parseDeviceAbility(
			QString::fromStdString(m_iotDeviceList->deviceAbility),
			QString::fromStdString(m_iotDeviceList->iotChannel[viewInfo.channelIndex]->channelAbility),
			&m_deviceAbility))
		{
			ret = -5;
		}
	}
	else
	{
		/* Single-channel device: channelId = 0 */
		channlID = 0;

		/* Parse device ability */
		if (m_iotDeviceList->iotChannel.size() > 0)
		{
			if (false == parseDeviceAbility(
				QString::fromStdString(m_iotDeviceList->deviceAbility),
				QString::fromStdString(m_iotDeviceList->iotChannel[0]->channelAbility),
				&m_deviceAbility))
			{
				ret = -5;
			}
		}
	}

	ret = m_videoPlay->playRtspReal(token.c_str(), m_iotDeviceList->deviceId.c_str(), m_iotDeviceList->decryptKey.c_str(), channlID, definitionMode, true, playInfo.c_str(), true);

	DLOG("playRtspReal ret: %d\n", ret);
	
    emit sgnPlayerStatusChanged(0 == ret ? STATUS_LOADING : STATUS_FAIL);
    DLOG("RealPlayCtrl::play>[%d]\n", ret);
    return ret;
}

int RealPlayCtrl::stopPlay()
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

/* Close talk, recording, audio */
        ret = stopTalk();
        ret = stopRecord();
        ret = stopAudio();

/* Close real-time preview */
        ret = m_videoPlay->stopRtspReal();
        if (0 == ret)
        {
            m_isPlaying = false;
        }
    } while (0);

    DLOG("RealPlayCtrl::stopPlay>[%d]\n", ret);
    return ret;
}

int RealPlayCtrl::playTalk()
{
	if(0)
	{
		std::string filePath = "D:\\decryptedPlayInfo.txt";
		std::ifstream file(filePath);
		if (!file.is_open()) {
			throw std::runtime_error("Unable to open file: " + filePath);
		}

// Read file content into string using iterator
		std::string content((std::istreambuf_iterator<char>(file)),
			std::istreambuf_iterator<char>());

		file.close();

		std::string deviceId = "AA07D26PAJ00162";
	}
	


	std::string playInfo = m_iotDeviceList->playInfo;

	/* Determine channelId for talk based on the current view's mapping */
	int channID = 0;
	ViewDeviceInfo viewInfo = DevicesListCtrl::getInstance()->getViewDeviceInfo(m_deviceIndex);
	if (viewInfo.channelIndex >= 0 && viewInfo.channelIndex < m_iotDeviceList->iotChannel.size())
	{
		/* Multi-channel device: use the specific channel's channelId */
		std::string channelID = m_iotDeviceList->iotChannel[viewInfo.channelIndex]->channelId;
		channID = atoi(channelID.c_str());
	}
	else if (m_iotDeviceList->iotChannel.size() > 0)
	{
		/* Single-channel device: use channel 0 */
		std::string channelID = m_iotDeviceList->iotChannel[0]->channelId;
		channID = atoi(channelID.c_str());
	}
	
	QJsonParseError jsonError;
	QJsonDocument json = QJsonDocument::fromJson(playInfo.c_str(), &jsonError);
	if (jsonError.error != QJsonParseError::NoError)
	{
		QString strError = jsonError.errorString();
		return -1;
	}

	if (!json.isObject())
	{
		return -1;
	}

	std::string token = json.object().value("userToken").toString().toStdString();
	string sourceType = json.object().value("sourceType").toString().toStdString();
	std::string deviceId = json.object().value("deviceId").toString().toStdString();
	//if (sourceType == "paas") //deviceTalk for dhpaas device 
	//{
	//	channID = -1;
	//}

/* Open talk */
	int ret = m_audioTalk->playTalk(token.c_str(), deviceId.c_str(), channID, deviceId.c_str(), true, playInfo.c_str(), true);
	// ret = m_audioTalk->playTalk(token.c_str(), m_iotDeviceList->deviceId.c_str(), channID, m_iotDeviceList->decryptKey.c_str(), false, playInfo.c_str());
	DLOG("playTalk ret[%d]\n", ret);

	emit sgnTalkerStatusChanged(0 == ret ? STATUS_LOADING : STATUS_FAIL);
	DLOG("RealPlayCtrl::playTalk>[%d]\n", ret);
	return ret;
}

int RealPlayCtrl::stopTalk()
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

		/* Close talk: first close talk sound, then close talk */
		m_audioTalk->stopSound();
        ret = m_audioTalk->stopTalk();
        if (0 == ret)
        {
            m_isTalking = false;

            /* Restore audio status */
            if (m_isAudioPlay)
            {
                playAudio();
            }
        }
		int stopSampleAudioRet = m_audioTalk->stopSampleAudio();
		DLOG("stopSampleAudio ret[%d]\n", stopSampleAudioRet);
    } while (0);

    DLOG("RealPlayCtrl::stopTalk>[%d]\n", ret);
    return ret;
}

int RealPlayCtrl::ptzControlAsyn(PTZ_CONTROL_DIRECTION_E direction, PTZ_CTRL_TYPE_E type)
{
    if (!m_isPlaying)
    {
        DLOG("video not playing!!!\n");
        return -2;
    }

    if (false == m_deviceAbility.supportPTZ)
    {
        DLOG("does not support PTZ!!!\n");
        return -3;
    }


	/* param variable is freed by the thread after execution */
	PTZ_CONTROL_THREAD_PARAM *param = new PTZ_CONTROL_THREAD_PARAM;

	/* Get channelId from view index mapping */
	int channel = 0;
	ViewDeviceInfo viewInfo = DevicesListCtrl::getInstance()->getViewDeviceInfo(m_deviceIndex);
	if (viewInfo.channelIndex >= 0 && viewInfo.channelIndex < m_iotDeviceList->iotChannel.size())
	{
		std::string chanID = m_iotDeviceList->iotChannel[viewInfo.channelIndex]->channelId;
		channel = atoi(chanID.c_str());
	}
	else if (m_iotDeviceList->iotChannel.size() > 0)
	{
		std::string chanID = m_iotDeviceList->iotChannel[0]->channelId;
		channel = atoi(chanID.c_str());
	}

	param->deviceId = QString::fromStdString(m_iotDeviceList->deviceId);
	param->channelId = channel;
		param->direction = direction;
		param->type = type;
		param->user = this;
		param->playInfo = m_iotDeviceList->playInfo;

		m_threadCtrl->setParamter(param, NULL);
		m_threadCtrl->start();
	//}
	

    return 0;
}

int RealPlayCtrl::ptzSingleStepControl(QString deviceId, int channelId, std::string playInfo, PTZ_CONTROL_DIRECTION_E direction)
{

	QJsonParseError jsonError;
	QJsonDocument json = QJsonDocument::fromJson(playInfo.c_str(), &jsonError);
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
		double iH, iV, iZ;
		int duration = 1000;
		iH = iV = 0;
		iZ = 1;

		switch (direction)
		{
		case PTZ_CONTROL_LEFT:
			iH = -0.5;
			iV = 0;
			break;
		case PTZ_CONTROL_RIGHT:
			iH = 0.5;
			iV = 0;
			break;
		case PTZ_CONTROL_UP:
			iH = 0;
			iV = 0.5;
			break;
		case PTZ_CONTROL_DOWN:
			iH = 0;
			iV = -0.5;
			break;
		case PTZ_CONTROL_LEFTUP:
			iH = -0.5;
			iV = 0.5;
			break;
		case PTZ_CONTROL_LEFTDOWN:
			iH = -0.5;
			iV = -0.5;
			break;
		case PTZ_CONTROL_RIGHTUP:
			iH = 0.5;
			iV = 0.5;
			break;
		case PTZ_CONTROL_RIGHTDOWN:
			iH = 0.5;
			iV = -0.5;
			break;
		}

		PTZ_CONTROL_PARAMETERS parameters;
		parameters.deviceId = deviceId;
		parameters.channelId = channelId;
		parameters.playInfo = playInfo;
		parameters.duration = duration;
		parameters.operate = "move";
		parameters.horizon = iH;
		parameters.vertical = iV;
		parameters.zoom = iZ;

		return OpenApiCtrl::getInstance()->controlPaaSPTZ(parameters);
	}
	else
	{
		double iH, iV, iZ;
		int duration = 100;
		iH = iV = 0;
		iZ = 1;

		switch (direction)
		{
		case PTZ_CONTROL_LEFT:
			iH = -5;
			iV = 0;
			break;
		case PTZ_CONTROL_RIGHT:
			iH = 5;
			iV = 0;
			break;
		case PTZ_CONTROL_UP:
			iH = 0;
			iV = 5;
			break;
		case PTZ_CONTROL_DOWN:
			iH = 0;
			iV = -5;
			break;
		case PTZ_CONTROL_LEFTUP:
			iH = -5;
			iV = 5;
			break;
		case PTZ_CONTROL_LEFTDOWN:
			iH = -5;
			iV = -5;
			break;
		case PTZ_CONTROL_RIGHTUP:
			iH = 5;
			iV = 5;
			break;
		case PTZ_CONTROL_RIGHTDOWN:
			iH = 5;
			iV = -5;
			break;
		}

		PTZ_CONTROL_PARAMETERS parameters;
		parameters.deviceId = deviceId;
		parameters.channelId = channelId;
		parameters.playInfo = playInfo;
		parameters.duration = duration;
		parameters.operate = "move";
		parameters.horizon = iH;
		parameters.vertical = iV;
		parameters.zoom = iZ;

		return OpenApiCtrl::getInstance()->controlPTZ(parameters);
	}
}

int RealPlayCtrl::ptzLongPressBeginControl(QString deviceId, int channelId, std::string playInfo, PTZ_CONTROL_DIRECTION_E direction)
{
	QJsonParseError jsonError;
	QJsonDocument json = QJsonDocument::fromJson(playInfo.c_str(), &jsonError);
	if (jsonError.error != QJsonParseError::NoError)
	{
		QString strError = jsonError.errorString();
	}

	if (!json.isObject())
	{
		return -1;
	}

	std::string sourceType = json.object().value("sourceType").toString().toStdString();
	if (sourceType == "paas") //adapter for DHPaaS
	{
		double iH, iV, iZ;
		int duration = -1;
		iH = iV = 0;
		iZ = 1;

		switch (direction)
		{
		case PTZ_CONTROL_LEFT:
			iH = -0.5;
			iV = 0;
			break;
		case PTZ_CONTROL_RIGHT:
			iH = 0.5;
			iV = 0;
			break;
		case PTZ_CONTROL_UP:
			iH = 0;
			iV = 0.5;
			break;
		case PTZ_CONTROL_DOWN:
			iH = 0;
			iV = -5;
			break;
		case PTZ_CONTROL_LEFTUP:
			iH = -0.5;
			iV = 0.5;
			break;
		case PTZ_CONTROL_LEFTDOWN:
			iH = -0.5;
			iV = -0.5;
			break;
		case PTZ_CONTROL_RIGHTUP:
			iH = 0.5;
			iV = 0.5;
			break;
		case PTZ_CONTROL_RIGHTDOWN:
			iH = 0.5;
			iV = -0.5;
			break;
		}

		PTZ_CONTROL_PARAMETERS parameters;
		parameters.deviceId = deviceId;
		parameters.channelId = channelId;
		parameters.playInfo = playInfo;
		parameters.duration = duration;
		parameters.operate = "move";
		parameters.horizon = iH;
		parameters.vertical = iV;
		parameters.zoom = iZ;

		return OpenApiCtrl::getInstance()->controlPaaSPTZ(parameters);
	}
	else
	{
		double iH, iV, iZ;
		int duration = -1;
		iH = iV = 0;
		iZ = 1;

		switch (direction)
		{
		case PTZ_CONTROL_LEFT:
			iH = -5;
			iV = 0;
			break;
		case PTZ_CONTROL_RIGHT:
			iH = 5;
			iV = 0;
			break;
		case PTZ_CONTROL_UP:
			iH = 0;
			iV = 5;
			break;
		case PTZ_CONTROL_DOWN:
			iH = 0;
			iV = -5;
			break;
		case PTZ_CONTROL_LEFTUP:
			iH = -5;
			iV = 5;
			break;
		case PTZ_CONTROL_LEFTDOWN:
			iH = -5;
			iV = -5;
			break;
		case PTZ_CONTROL_RIGHTUP:
			iH = 5;
			iV = 5;
			break;
		case PTZ_CONTROL_RIGHTDOWN:
			iH = 5;
			iV = -5;
			break;
		}

		PTZ_CONTROL_PARAMETERS parameters;
		parameters.deviceId = deviceId;
		parameters.channelId = channelId;
		parameters.playInfo = playInfo;
		parameters.duration = duration;
		parameters.operate = "move";
		parameters.horizon = iH;
		parameters.vertical = iV;
		parameters.zoom = iZ;

		return OpenApiCtrl::getInstance()->controlPTZ(parameters);
	}
}

int RealPlayCtrl::ptzLongPressEndControl(QString deviceId, int channelId, std::string playInfo, PTZ_CONTROL_DIRECTION_E direction)
{
	QJsonParseError jsonError;
	QJsonDocument json = QJsonDocument::fromJson(playInfo.c_str(), &jsonError);
	if (jsonError.error != QJsonParseError::NoError)
	{
		QString strError = jsonError.errorString();
	}

	if (!json.isObject())
	{
		return -1;
	}

	std::string sourceType = json.object().value("sourceType").toString().toStdString();
	if (sourceType == "paas") //adapter for DHPaaS
	{
		double iH, iV, iZ;
		int duration = 0;
		iH = iV = 0;
		iZ = 0;

		PTZ_CONTROL_PARAMETERS parameters;
		parameters.deviceId = deviceId;
		parameters.channelId = channelId;
		parameters.playInfo = playInfo;
		parameters.duration = duration;
		parameters.operate = "move";
		parameters.horizon = iH;
		parameters.vertical = iV;
		parameters.zoom = iZ;
		return OpenApiCtrl::getInstance()->controlPaaSPTZ(parameters);
	}
	else
	{
		double iH, iV, iZ;
		int duration = 0;
		iH = iV = 0;
		iZ = 0;

		PTZ_CONTROL_PARAMETERS parameters;
		parameters.deviceId = deviceId;
		parameters.channelId = channelId;
		parameters.playInfo = playInfo;
		parameters.duration = duration;
		parameters.operate = "move";
		parameters.horizon = iH;
		parameters.vertical = iV;
		parameters.zoom = iZ;

		return OpenApiCtrl::getInstance()->controlPTZ(parameters);
	}
}

void RealPlayCtrl::onTalkResult(const char* error, int type)
{
    DLOG("onTalkResult-%s-%d\n", error, type);
    if (!isNumber(error))
    {
/* Non-numeric return value indicates business error, code is the business error code */
        DLOG("business error[%s]!!!\n", error);
        emit sgnTalkerStatusChanged(STATUS_FAIL);
        return;
    }

    int nError = atoi(error);
    if(0 == type){
        if (STATE_RTSP_DESCRIBE_READY == nError)
        {
            DLOG("talk ready\n");
            return;
        }
        else if (STATE_RTSP_PLAY_READY == nError)
        {
/* Talk start success: first close audio, then open talk sound */
			stopAudio();
			// start sample audio 
			m_thread = std::thread(&RealPlayCtrl::audioSampletreadFunc, this);
			m_thread.detach();
            DLOG("start to talk\n");
            m_isTalking = true;
        }
        else
        {
			m_stopTalkThread = std::thread(&RealPlayCtrl::stopTalkThreadFunc, this);
			m_stopTalkThread.detach();
			m_isTalking = false;
            DLOG("talk rtsp connection closed\n");
        }
    }

	if (5 == type) { //dhhttp talk
		if (STATE_DHHTTP_OK == nError)
		{
/* Talk start success: first close audio, then open talk sound */
			stopAudio();
			// start sample audio 
			m_thread = std::thread(&RealPlayCtrl::audioSampletreadFunc, this);
			m_thread.detach();
			DLOG("start to talk\n");
			m_isTalking = true;
		}
		else if(0 == nError)
		{
			return;
		}
		else
		{
			m_stopTalkThread = std::thread(&RealPlayCtrl::stopTalkThreadFunc, this);
			m_stopTalkThread.detach();
			m_isTalking = false;
			DLOG("talk http connection closed\n");
		}
	}

    if (REST_ERR == type)
    {
        if (HTTP_ERR == nError)
        {
            DLOG("rest timeout\n");
        }
        else
        {
            DLOG("rest errcode[%d]\n", nError);
        }
    }

    emit sgnTalkerStatusChanged(m_isTalking ? STATUS_START : STATUS_FAIL);
}

void RealPlayCtrl::audioSampletreadFunc()
{
	int sampleAudioRet = m_audioTalk->startSampleAudio();
	DLOG("startSampleAudio ret[%d]\n", sampleAudioRet);
	int playSoundRet = m_audioTalk->playSound();   // Open the sound from the device side, if playAudio() is used as talk sound, this interface does not need to be called
}

void RealPlayCtrl::stopTalkThreadFunc()
{
	m_audioTalk->stopTalk();
}

void RealPlayCtrl::slotPlayerStatusChanged(int status)
{
	DLOG("1RealPlayCtrl::slotPlayerStatusChanged\n");
    if (status == STATUS_FAIL)
    {
		DLOG("2RealPlayCtrl::slotPlayerStatusChanged: %d\n", status);
        stopPlay();
    }
}
