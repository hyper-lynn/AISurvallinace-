#ifndef REALPLAYCTRL_H
#define REALPLAYCTRL_H
#include <QObject>

#include "lcopensdk_audiotalk/LCOpenSDK_TalkerListener.h"
#include "Src/Ctrl/PlayCtrl.h"
#include "Src/Model/PtzControlInfo.h"

class LCOpenSDK_AudioTalk;
class ThreadCtrl;
class RealPlayCtrl : public PlayCtrl, LCOpenSDK_TalkerListener
{
	Q_OBJECT

public:
	RealPlayCtrl();
	~RealPlayCtrl();

	int init(QWidget *videoBase);

	int play(int deviceIndex, int definitionMode);
	int stopPlay();

	int playTalk();
	int stopTalk();
	inline bool isTalking() { return m_isTalking; };

	inline void setTalkStatusBak(bool isTalking) { m_isTalkingBak = isTalking; };
	inline bool getTalkStatusBak() { return m_isTalkingBak; };

	/**
	* 异步云台控制
	* @param   [in] PTZ_CONTROL_DIRECTION direction 控制方向
	* @param   [in] PTZ_CTRL_TYPE_E type            控制类型(单步、开始长按、结束长按)
	* @return  int 0表示成功
	*/
	int ptzControlAsyn(PTZ_CONTROL_DIRECTION_E direction, PTZ_CTRL_TYPE_E type);

	/**
	* 云台控制-单步模式
	* @param   [in] QString deviceId
	* @param   [in] QString productId
	* @param   [in] int channelId
	* @param   [in] PTZ_CONTROL_DIRECTION direction
	* @return  int 0表示成功
	*/
	int ptzSingleStepControl(QString deviceId, QString productId, int channelId, PTZ_CONTROL_DIRECTION_E direction);

	/**
	* 云台控制-长按开始
	* @param   [in] QString deviceId
	* @param   [in] QString productId
	* @param   [in] int channelId
	* @param   [in] PTZ_CONTROL_DIRECTION direction
	* @return  int
	*/
	int ptzLongPressBeginControl(QString deviceId, QString productId, int channelId, PTZ_CONTROL_DIRECTION_E direction);

	/**
	* 云台控制-长按结束
	* @param   [in] QString deviceId
	* @param   [in] QString productId
	* @param   [in] int channelId
	* @param   [in] PTZ_CONTROL_DIRECTION direction
	* @return  int
	*/
	int ptzLongPressEndControl(QString deviceId, QString productId, int channelId, PTZ_CONTROL_DIRECTION_E direction);

protected:
	/* LCOpenSDK_TalkerListener回调 */
	virtual void onTalkResult(const char* error, int type);

private:
	LCOpenSDK_AudioTalk *m_audioTalk;
	bool                 m_isTalking;

	/*对讲状态备份*/
	bool                 m_isTalkingBak;
	ThreadCtrl          *m_threadCtrl;

signals:
	void sgnTalkerStatusChanged(int status);

private slots:
	void slotPlayerStatusChanged(int status);
};

#endif // REALPLAYCTRL_H
