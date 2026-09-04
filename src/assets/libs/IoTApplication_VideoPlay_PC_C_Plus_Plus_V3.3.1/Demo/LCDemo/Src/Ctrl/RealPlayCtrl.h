#ifndef REALPLAYCTRL_H
#define REALPLAYCTRL_H
#include <QObject>

#include "LCOpenSDK_TalkerListener.h"
#include "Ctrl/PlayCtrl.h"
#include "Model/PtzControlInfo.h"
#include <thread>

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
    inline bool isTalking(){ return m_isTalking; };

    inline void setTalkStatusBak(bool isTalking){ m_isTalkingBak = isTalking; };
    inline bool getTalkStatusBak(){ return m_isTalkingBak; };

    /**
    * Async PTZ control
    * @param   [in] PTZ_CONTROL_DIRECTION direction Control direction
    * @param   [in] PTZ_CTRL_TYPE_E type            Control type (single step, long press start, long press end)
    * @return  int 0 on success
    */
    int ptzControlAsyn(PTZ_CONTROL_DIRECTION_E direction, PTZ_CTRL_TYPE_E type);

    /**
    * PTZ control - single step mode
    * @param   [in] QString deviceId
    * @param   [in] int channelId
    * @param   [in] PTZ_CONTROL_DIRECTION direction
    * @return  int 0 on success
    */
	int ptzSingleStepControl(QString deviceId, int channelId, std::string playInfo, PTZ_CONTROL_DIRECTION_E direction);

    /**
    * PTZ control - long press begin
    * @param   [in] QString deviceId
    * @param   [in] int channelId
    * @param   [in] PTZ_CONTROL_DIRECTION direction
    * @return  int
    */
    int ptzLongPressBeginControl(QString deviceId, int channelId, std::string playInfo, PTZ_CONTROL_DIRECTION_E direction);

    /**
    * PTZ control - long press end
    * @param   [in] QString deviceId
    * @param   [in] int channelId
    * @param   [in] PTZ_CONTROL_DIRECTION direction
    * @return  int
    */
    int ptzLongPressEndControl(QString deviceId, int channelId, std::string playInfo, PTZ_CONTROL_DIRECTION_E direction);

protected:
    /* LCOpenSDK_TalkerListener callbacks */
    virtual void onTalkResult(const char* error, int type);
	void audioSampletreadFunc();
	void stopTalkThreadFunc();
	virtual void onTalkPlayReady() {}
	virtual void onProgressStatus(const char* status) {}
	virtual void onAudioRecord(unsigned char* pData, int dataLen, int audioFormat, int sampleRate, int sampleDepth) {}
	virtual void onAudioReceive(unsigned char* pData, int dataLen, int audioFormat, int sampleRate, int sampleDepth) {}
	virtual bool onRealAudioInfo(int realSampleRate, int realSampleDepth) { return false; }
	virtual void onStreamLogInfo(const char* message, unsigned int length) {}
	virtual void onConnectInfoConfig(const char* message, int msgLen, const char* ip, int ipLen, int localPort, int remotePort, const char* deviceSn, int snLen) {}

private:
    LCOpenSDK_AudioTalk *m_audioTalk;
    bool                 m_isTalking;
	std::thread			m_thread;
	std::thread			m_stopTalkThread;

    /* Talk status backup */
    bool                 m_isTalkingBak;
    ThreadCtrl          *m_threadCtrl;
	int					m_index;

signals:
    void sgnTalkerStatusChanged(int status);

private slots:
    void slotPlayerStatusChanged(int status);
};

#endif // REALPLAYCTRL_H
