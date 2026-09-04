/*
* Copyright (c) 2008, 浙江大华
* All rights reserved.
*
* 文件名称：RTPCommUnit.h
* 文件标识：
* 摘　　要：RTP通讯单元，提供UDP和TCP两种方式
*

* 当前版本：1.0
* 原作者　：高圩
* 完成日期：2008年10月28日
* 修订记录：创建
*/
#ifndef _RTP_COMM_UNIT_H_
#define _RTP_COMM_UNIT_H_

#include "RTP/CRTPSession.h"
#include "Utils/ThreadBase.h"
#include "DPSDKDefine.h"
#include "MulticastSession.h"

BEGIN_NAMESPACE_DPSDK

class IRTPCommListener;

class CRTPCommUnit	: public IRTPListener, public IRTCPListener, public IMulticastSessionListener, public ThreadBase
{
public:
	CRTPCommUnit(uint32 nId, IRTPCommListener* pListener);
	virtual ~CRTPCommUnit(void);

	int CreateMulticastSession();
	int CreateRTPSession(int nType);
	int SetDistAddress(const char* szIp, int nRtpPort, int nRtcpPort);
	int CreateRTPSessionForSender(int nType, CNewMutex* mutex);

	void SendTunnel(char* szTunnel, int nLen);
	void SetMulticastFlag( bool bMulticastFlag );
	void SetMulticastToUnicastFlag( bool bMulticastToUnicastFlag );

public:
	CRTPSession*		m_pRTPSession;
	MulticastSession*	m_pMulticastSession;
	int					m_nIdInBase;	//在serverbase里的ID
	int					m_nType;    //TCP或UDP传输 0udp 1tcp 2stdtcp

	bool				m_bMulticastFlag;	//组播标志 true组播，false单播
	bool				m_bMulticastToUnicast;

protected:
	virtual int run(); //线程执行体

protected://RTP回调操作
	virtual int onRTPPacket(int session, int connId, CRTPPacket* packet);
	virtual int onRTCPPacket(int session, int connId, CRTCPPacket* packet);
	virtual int onConnect(int engineId, int connId, const char* ip, int port);
	virtual int onClose(int engineId, int connId);

protected:
	virtual int OnMulticastData(int sessionid, char* data, int len);

private:
	uint32			  m_nId;
	IRTPCommListener* m_pListener;
	
	bool m_bConnect; //TCP模式下，该变量才有效

	uint64_t				m_nLastReciveTime;		//记录上一次接收时间
	uint64_t				m_nDownloadSpeed;			//当前下载速度 KB/s
	
#ifdef TEST_LOSE_PACKET
	int  m_nLastSeq; //上次接收到的包序号
	FILE* m_pFile;
#endif
};

class IRTPCommListener
{
public:
	virtual ~IRTPCommListener() {}
	virtual int onRTPData(int id, char* data, int len, CRTPPacket *packet = NULL) = 0;
	virtual int onRTPClose(int id) = 0;

	//TODO：放在这里不太合适，都是RTP回调，但为了减少的继承/回调量，暂时先放这
	//组播数据回调
	virtual int onMulticastData(int id, char* data, int len) = 0;
};


END_NAMESPACE_DPSDK



#endif
