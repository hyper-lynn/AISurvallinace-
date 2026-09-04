#ifndef PLAYCTRL_H
#define PLAYCTRL_H

#include <QWidget>
#include "LCOpenSDK_PlayerListener.h"
#include "LCOpenSDK_VideoPlay.h"
#include "LCOpenSDK_Define.h"
#include "Model/ChannelsListInfo.h"
#include "Utils/global.h"

enum PlayerResultCode{
	// RTSP
    /* 组帧失败 */
    STATE_PACKET_FRAME_ERROR = 0,
    STATE_RTSP_TEARDOWN_ERROR = 1,
    STATE_RTSP_DESCRIBE_READY = 2,
    STATE_RTSP_AUTHORIZATION_FAIL = 3,
    STATE_RTSP_PLAY_READY = 4,
    STATE_RTSP_FILE_PLAY_OVER = 5,

    /* 收到PAUSE响应 */
    STATE_RTSP_PAUSE_READY = 6,
    STATE_RTSP_DECRYPT_KEY_ERROR = 7,

	// DHHTTP
	STATE_DHHTTP_OK = 1000,
	STATE_DHHTTP_PLAY_FILE_OVER = 2000,

};

typedef enum PlayStatus
{
    STATUS_LOADING,
    STATUS_START,
    STATUS_STOP,
    STATUS_FAIL,
    STATUS_PAUSE,
    STATUS_RESUME,
	STATUS_SPEEDPLAY,

    STATUS_SEEK_SUCCESS,
    STATUS_SEEK_FAILD,
}PLAY_STATUS_E;

typedef enum
{
    PLAYCTRL_REALPLAY,
    PLAYCTRL_CLOUDPLAY,
    PLAYCTRL_DEVICEPLAY,
}PLAYCTRL_TYPE_E;

class LCOpenSDK_VideoPlay;
class PlayCtrl : public QObject, public LCOpenSDK_PlayerListener
{
	Q_OBJECT

public:
    PlayCtrl(PLAYCTRL_TYPE_E type);
	virtual ~PlayCtrl();

    virtual int init(QWidget *videoBase);

    inline int stopPlay(){ return -1; };
    int snapShot();
    int startRecord();
    int stopRecord();
    int playAudio();
    int stopAudio();

    QString getCurrentStreamMode();
    int rewake();

    inline bool isPlaying(){ return m_isPlaying; };
    inline bool isRecording(){ return m_isRecording; };
    inline bool isAudioPlay(){ return m_isAudioPlay; };
    inline bool isSupportTalk(){ return m_deviceAbility.supportAudioTalk; };
    inline bool isSupportPTZ(){ return m_deviceAbility.supportPTZ; };
    inline bool isPause(){ return m_isPause; };

protected:
    bool m_isInit;
    LCOpenSDK_VideoPlay *m_videoPlay;
	/*LCOpenSDK_VideoPlay *m_videoPlay1;
	LCOpenSDK_VideoPlay *m_videoPlay2;
	LCOpenSDK_VideoPlay *m_videoPlay3;
	LCOpenSDK_VideoPlay *m_videoPlay4;*/

    int            m_deviceIndex;
    ChannelInfo   *m_deviceInfo;
	IOTDeviceList *m_iotDeviceList;
    DEVICE_ABILITY m_deviceAbility;
    QString        m_snapPicPath;
    QString        m_recordPath;

    bool          m_isPlaying;
    bool          m_isRecording;
    bool          m_isAudioPlay;
    bool          m_isPause;
	bool		  m_isSpeedPlay;

    PLAYCTRL_TYPE_E m_playCtrlType;
    void setPlayCtrlType(PLAYCTRL_TYPE_E type){ m_playCtrlType = type; };

    QString getSnapShotPath();
    QString getRecordPath();
    bool parseDeviceAbility(const QString &abilityArray, const QString &channelAbilityArray, OUT DEVICE_ABILITY* abilityInfo);
    bool isNumber(const char* src);

    virtual void onPlayCloudRecordResult(int index, int code, int resultSource){};
    virtual void onPlayDeviceRecordResult(int index, int code, int resultSource){};

protected:
    //LCOpenSDK_WindowListener回调
    virtual void onPlayerResult(int index, const char* code, int resultSource);
    virtual void onResolutionChanged(int index, int width, int height);
    virtual void onReceiveData(int index, int len);
    virtual void onStreamCallback(int index, const unsigned char* data, unsigned int dataLen);
    virtual void onPlayBegan(int index);
    virtual void onPlayFinished(int index);
    virtual void onPlayerTime(int index, long time);


	virtual void onIVSInfo(int index, char* pBuf, long lType, long lLen, long lReallen) {}
	virtual void onProgressStatus(int index, const char* status) {}
	virtual void onFrameLost(const char* context) {}
	virtual void onRecordStop(const char* context, int error) {}
	virtual void onFileTime(const char* context, long beginTime, long endTime) {}
	virtual void onNetworkDisconnected(const char* context) {}
	virtual void onBadFile(const char* context) {}
	virtual void onDraw(const char* context, void *hdc) {}
	virtual void onPlayerTimeAndStamp(const char* context, long time, long stampTime) {}
	virtual void onAudioTimeAndStamp(const char* context, long time, long stampTime, bool isDetach) {}
	virtual void onStreamLogInfo(const char* context, const char* message, unsigned int length) {}
	virtual void onIPFrameTimeOver(const char* context, long timeInterval) {}
	virtual void onConnectInfoConfig(const char* context, const char* message, int msgLen, const char* ip, int ipLen, int localPort, int remotePort, const char* deviceSn, int snLen) {}


signals:
    void sgnPlayerStatusChanged(int status);
    void sgnRecorderStatusChanged(int status);
    void sgnStreamModeChanged(QString mode);
    void sgnSleepCountdown(int seconds);
    void sgnDeviceSleeping();
};

#endif // PLAYCTRL_H
