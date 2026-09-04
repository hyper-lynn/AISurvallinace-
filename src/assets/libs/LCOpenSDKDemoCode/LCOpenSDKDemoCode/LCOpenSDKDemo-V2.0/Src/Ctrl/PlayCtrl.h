#ifndef PLAYCTRL_H
#define PLAYCTRL_H

#include <QWidget>
#include "lcopensdk_videoplay/LCOpenSDK_PlayerListener.h"
#include "Src/Model/ChannelsListInfo.h"
#include "Src/Utils/global.h"

enum RtspPlayerResultCode {
	/* 组帧失败 */
	STATE_LCPACKET_FRAME_ERROR = 0,
	STATE_LCRTSP_TEARDOWN_ERROR = 1,
	STATE_LCRTSP_DESCRIBE_READY = 2,
	STATE_LCRTSP_AUTHORIZATION_FAIL = 3,
	STATE_LCRTSP_PLAY_READY = 4,
	STATE_LCRTSP_FILE_PLAY_OVER = 5,

	/* 收到PAUSE响应 */
	STATE_LCRTSP_PAUSE_READY = 6,
	STATE_LCRTSP_DECRYPT_KEY_ERROR = 7,
};

enum HttpPlayerResultCode {
	STATE_LCHTTP_COMPONENT_ERROR = -1,     //调流媒体失败
	STATE_LCHTTP_START = 0,                //开始拉流
	STATE_LCHTTP_OK = 1000,                //开启播放成功
	STATE_LCHTTP_PLAY_FILE_OVER = 2000,    //回放当前文件播放完毕
	STATE_LCHTTP_PAUSE_OK = 4000,          //子链路正常关闭
	STATE_LCHTTP_BAD_REQUEST = 400000,     //非法请求,关闭客户端
	STATE_LCHTTP_UNAUTHORIZED = 401000,     //未授权,用户名密码错误
	STATE_LCHTTP_FORBIDDEN = 403000, //禁止访问，关闭客户端
	STATE_LCHTTP_NOTFOUND = 404000, //未找到，关闭客户端
	STATE_LCHTTP_REQ_TIMEOUT = 408000, //请求超时，指拉流成功，但后续网络异常，导致拉流断开
	STATE_LCHTTP_SERVER_ERROR = 500000, //服务器内部错误，关闭客户端
	STATE_LCHTTP_SERVER_UNVALILABLE = 503000,  //服务不可用
	STATE_LCHTTP_FLOWLIMIT = 503006, //mts限流
	STATE_LCHTTP_P2P_MAXCONNECT = 503007,        //p2p达到最大链接数
	STATE_LCHTTP_CHECK_FAILED = 503008,      //对讲错误
	STATE_LCHTTP_BUSY_LINE = 503009,      //对讲忙线
	STATE_LCHTTP_GATEWAY_TIMEOUT = 504000,  //网络不通
	STATE_LCHTTP_CLIENT_ERROR = 1000000, //客户端内部错误，一般代码逻辑错误
	STATE_LCHTTP_KEY_ERROR = 1000005, //客户端密钥和服务端密钥不一致
};

typedef enum PlayStatus
{
	STATUS_LOADING,
	STATUS_START,
	STATUS_STOP,
	STATUS_FAIL,
	STATUS_PAUSE,
	STATUS_RESUME,

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

	inline int stopPlay() { return -1; };
	int snapShot();
	int startRecord();
	int stopRecord();
	int playAudio();
	int stopAudio();
	void videoPlayReset();

	inline bool isPlaying() { return m_isPlaying; };
	inline bool isRecording() { return m_isRecording; };
	inline bool isAudioPlay() { return m_isAudioPlay; };
	inline bool isSupportTalk() { return m_deviceAbility.supportAudioTalk; };
	inline bool isSupportPTZ() { return m_deviceAbility.supportPTZ; };
	inline bool isPause() { return m_isPause; };

private:
	QWidget				*m_videoBase;

protected:
	bool m_isInit;
	LCOpenSDK_VideoPlay *m_videoPlay;
	int            m_deviceIndex;
	ChannelInfo   *m_deviceInfo;
	DEVICE_ABILITY m_deviceAbility;
	QString        m_snapPicPath;
	QString        m_recordPath;

	bool          m_isPlaying;
	bool          m_isRecording;
	bool          m_isAudioPlay;
	bool          m_isPause;

	PLAYCTRL_TYPE_E m_playCtrlType;
	void setPlayCtrlType(PLAYCTRL_TYPE_E type) { m_playCtrlType = type; };

	QString getSnapShotPath();
	QString getRecordPath();
	bool parseDeviceAbility(const QString &abilityArray, const QString &channelAbilityArray, OUT DEVICE_ABILITY* abilityInfo);
	bool isNumber(const char* src);

	virtual void onPlayCloudRecordResult(int index, int code, int resultSource) {};
	virtual void onPlayDeviceRecordResult(int index, int code, int resultSource) {};

protected:
	//LCOpenSDK_WindowListener回调
	virtual void onPlayerResult(int index, const char* code, int resultSource);
	virtual void onResolutionChanged(int index, int width, int height);
	virtual void onReceiveData(int index, int len);
	virtual void onStreamCallback(int index, const unsigned char* data, unsigned int dataLen);
	virtual void onPlayBegan(int index);
	virtual void onPlayFinished(int index);
	virtual void onPlayerTime(int index, long time);
	virtual void onIVSInfo(int index, char* pBuf, long lType, long lLen, long lReallen);

signals:
	void sgnPlayerStatusChanged(int status);
	void sgnRecorderStatusChanged(int status);
	void sgnGetCurrentStreamMode(int streamMode);
};

#endif // PLAYCTRL_H
