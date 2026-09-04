#pragma once
#include "CRTPSession.h"
class CRTSPBase;
class CRTPSessStdTcp : public CRTPSession
{
public:
	/* type用于设置RTP会话的类型，0：RTP over UDP，1：RTP over TCP，2：RTP over RTSP */
	CRTPSessStdTcp(int id, Model model, int type = 2);
	CRTPSessStdTcp(int id, Model model, CNewMutex* mutex, int type = 2);
	CRTPSessStdTcp();
	virtual ~CRTPSessStdTcp();

	int setRtspBase(int connId, CRTSPBase* rtspBase);


	/* 用于发送RTP包。RTP分组由应用层生成，下层只负责发送，不负责打包工作。一般出现在转发的情况下。
	 * CRTPPacket对象可以使用指针的构造函数生成，可以避免内存拷贝。
	 */
	virtual int sendData(char* data, int len);
	virtual int sendData(int chn, char* data, int len);
	virtual int sendPacket(CRTPPacket* packet);


	/* 生命心跳 */
	int heartbeat(void);

	bool isDetach();
	void setDetach();

public:
	virtual int onData(int engineId, int connId, const char* data, int len);
protected:
	//virtual int onRTPPacketInside(int session, int connId, CRTPPacket* packet);
	//virtual int onRTCPPacketInside(int session, int connId, CRTCPPacket* packet);

	int onDataInside(int engineId, int connId, const char* data, int len);

	CRTSPBase* _rtspBase;
	int		_rtspConnID;
	bool _isDetach;
};
