/*
* Copyright (c) 2007, 浙江大华技术股份有限公司
* All rights reserved.
*
* 文件名称：CRTCPSession.h
* 文件标识：参见配置管理计划书
* 摘　　要：RTP基本会话类。这是RTP会话的最上层类，实现RTP会话，封装了RTCP会话，自动完成。发送方支持缓冲。
*
*/
#ifndef __FE_RTP_SERVER_BASE_H__
#define __FE_RTP_SERVER_BASE_H__

#include "RTP/RTPProtocol.h"
#include "RTP/CRTPPacket.h"
#include "RTP/CRTCPPacket.h"
#include "RTP/CRTPSession.h"

#include "TPLayer/ThreadMutex.h"

#define SESSION_NUM 1024 
//#define SESSION_GROUP 4
//#define SESSION_PIECE 256

#define SESSION_GROUP 1
#define SESSION_PIECE 1024

class CRTPServerBase
{
public:
	CRTPServerBase(CNewMutex* mutex,bool rtpOverTcp=false);
	virtual ~CRTPServerBase();

	virtual int addSession(CRTPSession* session);
	virtual int delSession(int id);
	virtual int updateSession(int id);
	virtual int heartbeat(void);

	virtual int setSelectTimeout(int sec, int usec);
	virtual int setTPBufferSize(TPType type, int size);

private:
	struct timeval _timeout;

	CRTPSession* _sessions[SESSION_NUM];
	CNewMutex* _mutex;

	CRTPPacket* _rtpPacket;

	int _sessionNum;
	int _highSessionIdx;	//_sessions当前被使用的最高下标

	fd_set* _readfds[SESSION_GROUP];
	fd_set* _writefds[SESSION_GROUP];
	int _maxfd[SESSION_GROUP];

	int createFds();
protected:
	bool _rtpOverTcp;

private:
	int heartBeatTcp();
	int createFdsTcp();
};

#endif//__FE_RTP_SERVER_BASE_H__
