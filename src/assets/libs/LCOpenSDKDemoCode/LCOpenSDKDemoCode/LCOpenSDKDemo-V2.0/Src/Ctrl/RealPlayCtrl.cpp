#include <QDir>
#include <QDateTime>
#include "lcopensdk_videoplay/LCOpenSDK_VideoPlay.h"
#include "lcopensdk_audiotalk/LCOpenSDK_AudioTalk.h"
#include "Src/Utils/global.h"
#include "Src/Ctrl/OpenApiCtrl.h"
#include "Src/Ctrl/DevicesListCtrl.h"
#include "Src/Model/threadinfo.h"
#include "Src/Ctrl/ThreadCtrl.h"
#include "RealPlayCtrl.h"

RealPlayCtrl::RealPlayCtrl()
	: PlayCtrl(PLAYCTRL_REALPLAY)
	, m_audioTalk(NULL)
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
		m_audioTalk->stopTalk();
	}

	if (m_threadCtrl)
	{
		m_threadCtrl->quit();
		m_threadCtrl->deleteLater();
	}
}

int RealPlayCtrl::init(QWidget *videoBase)
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
	/* 最好先调用一下停止播放 */
	stopPlay();

	int ret = 0;
	do
	{
		if (!m_isInit)
		{
			DLOG("please call init() first!!!\n");
			ret = -1;
			break;
		}

		/* 查询设备详细信息 */
		m_deviceInfo = DevicesListCtrl::getInstance()->getChannelInfo(deviceIndex);
		if (NULL == m_deviceInfo)
		{
			ret = -4;
			break;
		}

		/* 解析设备能力集 */
		if (false == parseDeviceAbility(m_deviceInfo->deviceAbility, m_deviceInfo->channelAbility, &m_deviceAbility))
		{
			ret = -5;
			break;
		}
		if (m_deviceInfo->accessType == "Easy4IP")
		{
			m_deviceAbility.supportPTZ = true;
		}


		LCOpenSDK_ParamReal stParamReal;
		std::string strAccessToken = OpenApiCtrl::getInstance()->getToken().toStdString();
		stParamReal.accessToken = strAccessToken.c_str();
		std::string strDeviceID = m_deviceInfo->deviceId.toStdString();
		stParamReal.deviceID = strDeviceID.c_str();
		std::string strPid = m_deviceInfo->productId.toStdString();
		stParamReal.pid = strPid.c_str();
		std::string strPlayToken = m_deviceInfo->playToken.toStdString();
		stParamReal.playToken = strPlayToken.c_str();
		std::string strPSK = m_deviceInfo->decryptKey.toStdString();
		stParamReal.psk = strPSK.c_str();
		stParamReal.channel = m_deviceInfo->channelId;
		stParamReal.defiMode = (DEFINITION_MODE)definitionMode;
		stParamReal.assistStreamEnable = true;
		//根据设备TLS判断是否走TLS
		stParamReal.isTls = m_deviceInfo->tlsEnable;

		/* 播放实时视频 */
		videoPlayReset();
		ret = m_videoPlay->playRtspRealEx(&stParamReal);

		/* 播放实时视频 */
		/*ret = m_videoPlay->playRtspReal(OpenApiCtrl::getInstance()->getToken().toStdString().c_str(),
			m_deviceInfo->deviceId.toStdString().c_str(), m_deviceInfo->decryptKey.toStdString().c_str(), m_deviceInfo->channelId, definitionMode, true);*/
	} while (0);

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

		/* 关闭对讲、录像、音频 */
		ret = stopTalk();
		ret = stopRecord();
		ret = stopAudio();

		/* 关闭实时预览 */
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
	int ret = 0;
	do
	{
		if (!m_isInit)
		{
			DLOG("please call init() first!!!\n");
			ret = -1;
			break;
		}
		LCOpenSDK_ParamTalk stuTalk;
		std::string strAccessToken = OpenApiCtrl::getInstance()->getToken().toStdString();
		stuTalk.accessToken = strAccessToken.c_str();
		std::string strDeviceID = m_deviceInfo->deviceId.toStdString();
		stuTalk.deviceID = strDeviceID.c_str();
		std::string strPid = m_deviceInfo->productId.toStdString();
		stuTalk.pid = strPid.c_str();
		std::string strPlayToken = m_deviceInfo->playToken.toStdString();
		stuTalk.playToken = strPlayToken.c_str();
		if (m_deviceInfo->catalog == "IPC" || m_deviceInfo->catalog == "ARC")
		{
			//NVR IPC设备级对讲传-1
			stuTalk.channel = -1;
		}
		else if(m_deviceInfo->catalog == "NVR" || m_deviceInfo->multiFlag)
		{
			//通道级对讲
			stuTalk.channel = m_deviceInfo->channelId;
		}
		else
		{
			stuTalk.channel = -1;
		}

		std::string strPSK = m_deviceInfo->decryptKey.toStdString();
		stuTalk.psk = strPSK.c_str();
		stuTalk.isTls = m_deviceInfo->tlsEnable;
		ret = m_audioTalk->playTalkEx(&stuTalk);
	} while (0);

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

		ret = m_audioTalk->stopTalk();
		if (0 == ret)
		{
			m_isTalking = false;

			/* 恢复音频状态 */
			if (m_isAudioPlay)
			{
				playAudio();
			}
		}
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
	/* param变量由线程执行完成后负责释放 */
	PTZ_CONTROL_THREAD_PARAM *param = new PTZ_CONTROL_THREAD_PARAM;
	param->deviceId = m_deviceInfo->deviceId;
	param->channelId = m_deviceInfo->channelId;
	param->productId = m_deviceInfo->productId;
	param->direction = direction;
	param->type = type;
	param->user = this;

	m_threadCtrl->setParamter(param, NULL);
	m_threadCtrl->start();

	return 0;
}

int RealPlayCtrl::ptzSingleStepControl(QString deviceId, QString productId, int channelId, PTZ_CONTROL_DIRECTION_E direction)
{
	QString operation = "";
	long duration = 100;

	switch (direction)
	{
	case PTZ_CONTROL_LEFT:
		operation = "2";
		break;
	case PTZ_CONTROL_RIGHT:
		operation = "3";
		break;
	case PTZ_CONTROL_UP:
		operation = "0";
		break;
	case PTZ_CONTROL_DOWN:
		operation = "1";
		break;
	case PTZ_CONTROL_LEFTUP:
		operation = "4";
		break;
	case PTZ_CONTROL_LEFTDOWN:
		operation = "5";
		break;
	case PTZ_CONTROL_RIGHTUP:
		operation = "6";
		break;
	case PTZ_CONTROL_RIGHTDOWN:
		operation = "7";
		break;
	}

	LCOpenSDK_ParamControlPTZ parameters;
	std::string strAccessToken = OpenApiCtrl::getInstance()->getToken().toStdString().c_str();
	parameters.accessToken = strAccessToken.c_str();
	std::string strDeviceID = deviceId.toStdString().c_str();
	parameters.deviceID = strDeviceID.c_str();
	std::string strProductID = productId.toStdString().c_str();
	parameters.pid = strProductID.c_str();
	parameters.channel = channelId;
	parameters.duration = duration;
	std::string strOperation = operation.toStdString().c_str();
	parameters.operation = strOperation.c_str();
	std::string strPlayToken = m_deviceInfo->playToken.toStdString().c_str();
	parameters.playToken = strPlayToken.c_str();
	return m_videoPlay->controlMovePTZ(&parameters);
}

int RealPlayCtrl::ptzLongPressBeginControl(QString deviceId, QString productId, int channelId, PTZ_CONTROL_DIRECTION_E direction)
{
	QString operation = "";
	long duration = 30000;

	switch (direction)
	{
	case PTZ_CONTROL_LEFT:
		operation = "2";
		break;
	case PTZ_CONTROL_RIGHT:
		operation = "3";
		break;
	case PTZ_CONTROL_UP:
		operation = "0";
		break;
	case PTZ_CONTROL_DOWN:
		operation = "1";
		break;
	case PTZ_CONTROL_LEFTUP:
		operation = "4";
		break;
	case PTZ_CONTROL_LEFTDOWN:
		operation = "5";
		break;
	case PTZ_CONTROL_RIGHTUP:
		operation = "6";
		break;
	case PTZ_CONTROL_RIGHTDOWN:
		operation = "7";
		break;
	}

	LCOpenSDK_ParamControlPTZ parameters;
	std::string strAccessToken = OpenApiCtrl::getInstance()->getToken().toStdString().c_str();
	parameters.accessToken = strAccessToken.c_str();
	std::string strDeviceID = deviceId.toStdString().c_str();
	parameters.deviceID = strDeviceID.c_str();
	std::string strProductID = productId.toStdString().c_str();
	parameters.pid = strProductID.c_str();
	parameters.channel = channelId;
	parameters.duration = duration;
	std::string strOperation = operation.toStdString().c_str();
	parameters.operation = strOperation.c_str();
	std::string strPlayToken = m_deviceInfo->playToken.toStdString().c_str();
	parameters.playToken = strPlayToken.c_str();
	return m_videoPlay->controlMovePTZ(&parameters);
}

int RealPlayCtrl::ptzLongPressEndControl(QString deviceId, QString productId, int channelId, PTZ_CONTROL_DIRECTION_E direction)
{
	LCOpenSDK_ParamControlPTZ parameters;
	std::string strAccessToken = OpenApiCtrl::getInstance()->getToken().toStdString().c_str();
	parameters.accessToken = strAccessToken.c_str();
	std::string strDeviceID = deviceId.toStdString().c_str();
	parameters.deviceID = strDeviceID.c_str();
	std::string strProductID = productId.toStdString().c_str();
	parameters.pid = strProductID.c_str();
	parameters.channel = channelId;
	parameters.duration = 0;
	parameters.operation = "10";
	std::string strPlayToken = m_deviceInfo->playToken.toStdString().c_str();
	parameters.playToken = strPlayToken.c_str();
	return m_videoPlay->controlMovePTZ(&parameters);
}

void RealPlayCtrl::onTalkResult(const char* error, int type)
{
	DLOG("onTalkResult-%s-%d\n", error, type);
	if (!isNumber(error))
	{
		/* 返回值不为数字则表示业务出错,code即为业务错误代码 */
		DLOG("business error[%s]!!!\n", error);
		emit sgnTalkerStatusChanged(STATUS_FAIL);
		return;
	}

	int nError = atoi(error);
	if (0 == type) {
		if (STATE_RTSP_DESCRIBE_READY == nError)
		{
			DLOG("talk ready\n");
			return;
		}
		else if (STATE_RTSP_PLAY_READY == nError)
		{
			DLOG("start to talk\n");
			m_isTalking = true;
		}
		else
		{
			DLOG("talk rtsp connection closed\n");
			stopTalk();
		}
	}
	else if (5 == type)
	{
		if (STATE_DHHTTP_OK == nError)
		{
			DLOG("start to talk\n");
			m_isTalking = true;
		}
		else
		{
			DLOG("talk http connection closed\n");
			stopTalk();
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

void RealPlayCtrl::slotPlayerStatusChanged(int status)
{
	if (status == STATUS_FAIL)
	{
		stopPlay();
	}
}
