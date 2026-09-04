#include <QDir>
#include <QDateTime>
#include "lcopensdk_videoplay/LCOpenSDK_VideoPlay.h"
#include "Src/Utils/global.h"
#include "Src/Ctrl/DevicesListCtrl.h"
#include "PlayCtrl.h"

PlayCtrl::PlayCtrl(PLAYCTRL_TYPE_E type)
	: m_videoPlay(NULL)
	, m_isInit(false)
	, m_deviceInfo(NULL)
	, m_isRecording(false)
	, m_isAudioPlay(false)
	, m_isPlaying(false)
	, m_playCtrlType(type)
	, m_isPause(false)
{

}

PlayCtrl::~PlayCtrl()
{
	if (m_videoPlay)
	{
		m_videoPlay->uninitVideoPlay();
		SAFE_DELETE(m_videoPlay);
	}
}

void PlayCtrl::videoPlayReset()
{
	int ret = 0;
	if (m_videoPlay)
	{
		m_videoPlay->uninitVideoPlay();
		SAFE_DELETE(m_videoPlay);
	}

	if (NULL == m_videoBase)
	{
		return;
	}

	m_videoPlay = new LCOpenSDK_VideoPlay();
	if (NULL == m_videoPlay)
	{
		return;
	}

	if (0 != m_videoPlay->initVideoPlay(0, (void*)(m_videoBase->winId())))
	{
		DLOG("LCOpenSDK_VideoPlay init fail!!!\n");
		return;
	}
	else
	{
		m_videoPlay->setPlayerListener(this);
	}

	m_isInit = true;
}

int PlayCtrl::init(QWidget *videoBase)
{
	int ret = 0;
	do
	{
		if (NULL == videoBase)
		{
			ret = -1;
			break;
		}

		m_videoBase = videoBase;
		m_videoPlay = new LCOpenSDK_VideoPlay();
		if (NULL == m_videoPlay)
		{
			ret = -1;
			break;
		}

		if (0 != m_videoPlay->initVideoPlay(0, (void*)(videoBase->winId())))
		{
			DLOG("LCOpenSDK_VideoPlay init fail!!!\n");
			ret = -2;
			break;
		}
		else
		{
			m_videoPlay->setPlayerListener(this);
		}

		m_snapPicPath.sprintf("./data/pictures");
		m_recordPath.sprintf("./data/records");
		m_isInit = true;
	} while (0);

	return ret;
}

int PlayCtrl::snapShot()
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

		ret = m_videoPlay->snapShot(getSnapShotPath().toLocal8Bit().data());
	} while (0);

	DLOG("snapShot>[%d]\n", ret);
	return ret;
}

QString PlayCtrl::getSnapShotPath()
{
	QString ret = "";
	do
	{
		if (NULL == m_deviceInfo)
		{
			DLOG("please get deviceinfo first!!!\n");
			break;
		}

		if (!QDir(m_snapPicPath).exists())
		{
			QDir dir;
			dir.mkpath(m_snapPicPath);
		}

		/* 时间戳_序列号_设备型号_通道号_real.jpg */
		ret.sprintf("%s/%s_%s_%s_%d_real.jpg", m_snapPicPath.toStdString().c_str(),
			QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss-zzz").toStdString().c_str(),
			m_deviceInfo->deviceId.toStdString().c_str(), m_deviceInfo->deviceModel.toStdString().c_str(), m_deviceInfo->channelId);
	} while (0);

	/* 相对路径转为绝对路径 */
	ret = QDir(ret).absolutePath();
	DLOG("getSnapShotPath[%s]\n", ret.toLocal8Bit().data());
	return ret;
}

int PlayCtrl::startRecord()
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

		ret = m_videoPlay->startRecord(getRecordPath().toLocal8Bit().data());
		if (0 == ret)
		{
			m_isRecording = true;
		}
	} while (0);

	DLOG("startRecord>[%d]\n", ret);
	return ret;
}

QString PlayCtrl::getRecordPath()
{
	QString ret = "";
	do
	{
		if (NULL == m_deviceInfo)
		{
			DLOG("please get deviceinfo first!!!\n");
			break;
		}

		if (!QDir(m_recordPath).exists())
		{
			QDir dir;
			dir.mkpath(m_recordPath);
		}

		/* 时间戳_序列号_设备型号_通道号.mp4 */
		ret.sprintf("%s/%s_%s_%s_%d.mp4", m_recordPath.toStdString().c_str(),
			QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss-zzz").toStdString().c_str(),
			m_deviceInfo->deviceId.toStdString().c_str(), m_deviceInfo->deviceModel.toStdString().c_str(), m_deviceInfo->channelId);
	} while (0);

	/* 相对路径转为绝对路径 */
	ret = QDir(ret).absolutePath();
	DLOG("getRecordPath[%s]\n", ret.toLocal8Bit().data());
	return ret;
}

int PlayCtrl::stopRecord()
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

		ret = m_videoPlay->stopRecord();
		if (0 == ret)
		{
			m_isRecording = false;
		}
	} while (0);

	DLOG("stopRecord>[%d]\n", ret);
	return ret;
}

int PlayCtrl::playAudio()
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

		ret = m_videoPlay->playAudio();
		if (0 == ret)
		{
			m_isAudioPlay = true;
		}
	} while (0);

	DLOG("playAudio>[%d]\n", ret);
	return ret;
}

int PlayCtrl::stopAudio()
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

		ret = m_videoPlay->stopAudio();
		if (0 == ret)
		{
			m_isAudioPlay = false;
		}
	} while (0);

	DLOG("stopAudio>[%d]\n", ret);
	return ret;
}

bool PlayCtrl::parseDeviceAbility(const QString &abilityArray, const QString &channelAbilityArray, OUT DEVICE_ABILITY* abilityInfo)
{
	bool ret = false;
	do
	{
		if (NULL == abilityInfo)
		{
			break;
		}
		memset(abilityInfo, 0, sizeof(DEVICE_ABILITY));

		if (abilityArray.contains("AudioTalk") || channelAbilityArray.contains("AudioTalk"))
		{
			abilityInfo->supportAudioTalk = true;
		}
		else
		{
			abilityInfo->supportAudioTalk = false;
		}

		if (abilityArray.contains("PTZ") || channelAbilityArray.contains("PTZ") || abilityArray.contains("PT") || channelAbilityArray.contains("PT"))
		{
			abilityInfo->supportPTZ = true;
		}
		else
		{
			abilityInfo->supportPTZ = false;
		}

		ret = true;
	} while (0);

	return ret;
}

bool PlayCtrl::isNumber(const char* src)
{
	QString src1 = QString(QLatin1String(src));
	bool ret = !src1.isEmpty();
	for (int i = 0; i < src1.count(); ++i)
	{
		char asc = src1.at(i).toLatin1();
		if ('-' == asc && 0 == i)
		{
			/* 负数 */
			continue;
		}

		if (asc < '0' || asc > '9')
		{
			/* 非数字 */
			ret = false;
			break;
		}
	}

	return ret;
}

void PlayCtrl::onPlayerResult(int index, const char* code, int resultSource)
{
	DLOG("onPlayerResult-%s-%d\n", code, resultSource);

	if (!isNumber(code))
	{
		/* 返回值不为数字则表示业务出错, code即为业务错误代码 */
		DLOG("business error[%s]!!!\n", code);
		emit sgnPlayerStatusChanged(STATUS_FAIL);
		return;
	}

	/* 字符串类型code转成int类型, 方便接下来的错误码处理 */
	int nCode = atoi(code);

	if (PLAYCTRL_CLOUDPLAY == m_playCtrlType)
	{
		/* 云录像播放不走RTSP协议, 需要特殊处理 */
		onPlayCloudRecordResult(index, nCode, resultSource);
		return;
	}
	else
	{
		if (0 == resultSource)
		{
			if (STATE_LCRTSP_DESCRIBE_READY == nCode)
			{
				DLOG("describe ready\n");
				return;
			}
			else if (STATE_LCRTSP_PLAY_READY == nCode)
			{
				DLOG("start to play\n");
				return;
			}
			else if (STATE_LCRTSP_PAUSE_READY == nCode)
			{
				DLOG("pause success\n");
				return;
			}
			else if (STATE_LCRTSP_DECRYPT_KEY_ERROR == nCode)
			{
				DLOG("decrypt key error\n");
			}
			else
			{
				DLOG("rtsp connection closed\n");
			}
		}

		if (5 == resultSource)
		{
			if (STATE_LCHTTP_START == nCode)
			{
				DLOG("start private protocol!\n");
				return;
			}
			else if (STATE_LCHTTP_OK == nCode)
			{
				DLOG("play private protocol succeed!\n");
				return;
			}
			else if (STATE_LCHTTP_PAUSE_OK == nCode)
			{
				DLOG("pause private protocol succeed!\n");
				return;
			}
		}

		if (7 == resultSource)
		{
			if (StreamSourceSwitchToP2P == nCode)
			{
				DLOG("start mts to p2p  play!\n");
				return;
			}
		}

		if (REST_ERR == resultSource)
		{
			if (HTTP_ERR == nCode)
			{
				DLOG("rest timeout\n");
			}
			else
			{
				DLOG("rest errcode[%d]\n", nCode);
			}
		}

		/* 正在录像则需要调用停止录像接口, 否则录像文件不会存储 */
		if (m_isRecording)
		{
			stopRecord();
		}

		m_isPlaying = false;
		m_isAudioPlay = false;
		emit sgnPlayerStatusChanged(STATUS_FAIL);
	}
}

void PlayCtrl::onResolutionChanged(int index, int width, int height)
{
	DLOG("onResolutionChanged-%d-%d\n", width, height);
}

//void PlayCtrl::onRecordStop(int error)
//{
//    DLOG("onRecordStop-%d\n", error);
//    emit sgnOnRecorderStatusChanged(STATUS_STOP);
//}

void PlayCtrl::onReceiveData(int index, int len)
{
	/* 计算速率 */
	//DLOG("onReceiveData-%d\n", len);
}

void PlayCtrl::onStreamCallback(int index, const unsigned char* data, unsigned int dataLen)
{

}

void PlayCtrl::onPlayBegan(int index)
{
	DLOG("onPlayBegan\n");
	m_isPlaying = true;
	m_isPause = false;
	//获取当前流模式
	int currentStreamMode = m_videoPlay->getCurrentStreamMode();
	DLOG("onPlayBegan P2P[0] MTS[1]  %d\n", currentStreamMode);

	emit sgnGetCurrentStreamMode(currentStreamMode);
	emit sgnPlayerStatusChanged(STATUS_START);
}

void PlayCtrl::onPlayFinished(int index)
{
	DLOG("onPlayFinished\n");
	emit sgnPlayerStatusChanged(STATUS_STOP);
}

void PlayCtrl::onPlayerTime(int index, long time)
{
	//DLOG("onPlayerTime-%d\n", time);
}

void PlayCtrl::onIVSInfo(int index, char* pBuf, long lType, long lLen, long lReallen)
{
	DLOG("PlayCtrl::onIVSInfo\n");
	return;
}