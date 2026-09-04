#include <QDir>
#include <QDateTime>
#include <thread>
#include "LCOpenSDK_VideoPlay.h"

#include "Utils/global.h"
#include "Ctrl/OpenApiCtrl.h"
#include "Ctrl/DevicesListCtrl.h"
#include <iostream>
#include <string>
#include <sstream>
#include <QDebug>
//#include <libdsl/DPrintLog.h>
#include "PlayCtrl.h"

PlayCtrl::PlayCtrl(PLAYCTRL_TYPE_E type)
    : m_videoPlay(NULL)
	/*, m_videoPlay1(NULL)
	, m_videoPlay2(NULL)
	, m_videoPlay3(NULL)
	, m_videoPlay4(NULL)*/
    , m_isInit(false)
    , m_deviceInfo(NULL)
    , m_isRecording(false)
    , m_isAudioPlay(false)
    , m_isPlaying(false)
    , m_playCtrlType(type)
    , m_isPause(false)
	, m_isSpeedPlay(false)
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
		////1
		//m_videoPlay1 = new LCOpenSDK_VideoPlay();
		//if (NULL == m_videoPlay1)
		//{
		//	ret = -1;
		//	break;
		//}

		//if (0 != m_videoPlay1->initVideoPlay(0, (void*)(videoBase->winId())))
		//{
		//	DLOG("LCOpenSDK_VideoPlay init fail!!!\n");
		//	ret = -2;
		//	break;
		//}
		//else
		//{
		//	m_videoPlay1->setPlayerListener(this);
		//}
		////2
		//m_videoPlay2 = new LCOpenSDK_VideoPlay();
		//if (NULL == m_videoPlay2)
		//{
		//	ret = -1;
		//	break;
		//}

		//if (0 != m_videoPlay2->initVideoPlay(0, (void*)(videoBase->winId())))
		//{
		//	DLOG("LCOpenSDK_VideoPlay init fail!!!\n");
		//	ret = -2;
		//	break;
		//}
		//else
		//{
		//	m_videoPlay2->setPlayerListener(this);
		//}
		////3
		//m_videoPlay3 = new LCOpenSDK_VideoPlay();
		//if (NULL == m_videoPlay3)
		//{
		//	ret = -1;
		//	break;
		//}

		//if (0 != m_videoPlay3->initVideoPlay(0, (void*)(videoBase->winId())))
		//{
		//	DLOG("LCOpenSDK_VideoPlay init fail!!!\n");
		//	ret = -2;
		//	break;
		//}
		//else
		//{
		//	m_videoPlay3->setPlayerListener(this);
		//}
		////4
		//m_videoPlay4 = new LCOpenSDK_VideoPlay();
		//if (NULL == m_videoPlay4)
		//{
		//	ret = -1;
		//	break;
		//}

		//if (0 != m_videoPlay4->initVideoPlay(0, (void*)(videoBase->winId())))
		//{
		//	DLOG("LCOpenSDK_VideoPlay init fail!!!\n");
		//	ret = -2;
		//	break;
		//}
		//else
		//{
		//	m_videoPlay4->setPlayerListener(this);
		//}
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
	if (NULL == m_iotDeviceList)
		{
			DLOG("please get deviceinfo first!!!\n");
			return ret;
		}

	if (!QDir(m_snapPicPath).exists())
	{
		QDir dir;
		dir.mkpath(m_snapPicPath);
	}
	ret.sprintf("%s/%s_%s_real.jpg", m_snapPicPath.toStdString().c_str(),
		QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss-zzz").toStdString().c_str(),
		m_iotDeviceList->deviceId.c_str());

    /* Convert relative path to absolute path */
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

        ret = m_videoPlay->startRecord(getRecordPath().toLocal8Bit().data(), 1);
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
        if (NULL == m_iotDeviceList)
        {
            DLOG("please get m_iotDeviceList first!!!\n");
            break;
        }
			if (!QDir(m_recordPath).exists())
			{
				QDir dir;
				dir.mkpath(m_recordPath);
			}

    /* timestamp_serialNumber_deviceModel_channelNumber.mp4 */
			ret.sprintf("%s/%s_%s_%s.mp4", m_recordPath.toStdString().c_str(),
				QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss-zzz").toStdString().c_str(),
				m_iotDeviceList->deviceId.c_str());
    } while (0);

    /* Convert relative path to absolute path */
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

QString PlayCtrl::getCurrentStreamMode()
{
    QString mode = "";
    if (m_isInit && m_videoPlay)
    {
        Dahua::LCOpenSDK::E_STREAM_MODE streamMode = m_videoPlay->getCurrentStreamMode();
        if (Dahua::LCOpenSDK::E_STREAM_MODE_P2P == streamMode)
        {
            mode = "p2p";
        }
        else if (Dahua::LCOpenSDK::E_STREAM_MODE_MTS == streamMode)
        {
            mode = "mts";
        }
    }
    return mode;
}

int PlayCtrl::rewake()
{
    int ret = 0;
    do
    {
        if (!m_isInit || !m_videoPlay)
        {
            DLOG("rewake: not initialized\n");
            ret = -1;
            break;
        }

        ret = m_videoPlay->rewake();
    } while (0);

    DLOG("rewake>[%d]\n", ret);
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

        if (abilityArray.contains("PTZ") || channelAbilityArray.contains("PTZ") || channelAbilityArray.contains("PT1") || channelAbilityArray.contains("PT") || channelAbilityArray.contains("PT2"))
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
        /* Negative number */
            continue;
        }

        if (asc < '0' || asc > '9')
        {
        /* Not a number */
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
        /* Non-numeric return value indicates business error, code is the business error code */
        DLOG("business error[%s]!!!\n", code);
        emit sgnPlayerStatusChanged(STATUS_FAIL);
        return;
    }

    /* Convert string type code to int, convenient for subsequent error code handling */
    int nCode = atoi(code);

    if (PLAYCTRL_CLOUDPLAY == m_playCtrlType)
    {
    /* Cloud record playback does not use RTSP protocol, requires special handling */
        onPlayCloudRecordResult(index, nCode, resultSource);
        return;
    }
    else
    {
        if (0 == resultSource)// E_RESULT_PROTO_TYPE_RTSP = 0, RTSP business (real-time preview, local record playback, talk)
        {
            if (STATE_RTSP_DESCRIBE_READY == nCode)
            {
                DLOG("describe ready\n");
                return;
            }
            else if (STATE_RTSP_PLAY_READY == nCode)
            {
                DLOG("start to play\n");
                return;
            }
            else if (STATE_RTSP_PAUSE_READY == nCode)
            {
                DLOG("pause success\n");
                return;
            }
            else if (STATE_RTSP_DECRYPT_KEY_ERROR == nCode)
            {
                DLOG("decrypt key error\n");
            }
            else
            {
                DLOG("rtsp connection closed\n");
            }
		} 
        else if (5 == resultSource) {// E_RESULT_PROTO_TYPE_DHHTTP = 5, HTTP optimized streaming business (including Dahua Meeting)
			if (STATE_DHHTTP_OK == nCode) {
				DLOG("start to play dhhttp\n");
				return;
			}
			else if (STATE_DHHTTP_PLAY_FILE_OVER == nCode) {
				DLOG("start to play file over\n");
				return;
			}
			else if(0 == nCode){
				DLOG("onplayerResult code: %d \n", nCode);
				return;
			}
			else if (nCode >= 8000 && nCode <= 9000) {
				/* Low-power device sleep countdown: code - 8000 = seconds until device enters sleep */
				int sleepSeconds = nCode - 8000;
				DLOG("low-power device sleep countdown: %d seconds\n", sleepSeconds);
				emit sgnSleepCountdown(sleepSeconds);
				return;
			}
			else if (603038 == nCode) {
				/* Low-power device is about to enter sleep state */
				DLOG("low-power device entering sleep state\n");
				emit sgnDeviceSleeping();
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

    /* If recording, need to call stop record interface, otherwise recording file will not be saved */
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
    /* Calculate rate */
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

    /* Open audio in a separate thread, cannot call SDK interface directly in SDK callback */
    std::thread audioThread([this]() {
        playAudio();
    });
    audioThread.detach();

    /* Get current stream mode and notify View (must call SDK in separate thread) */
    std::thread streamModeThread([this]() {
        QString mode = getCurrentStreamMode();
        if (!mode.isEmpty())
        {
            emit sgnStreamModeChanged(mode);
        }
    });
    streamModeThread.detach();

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
