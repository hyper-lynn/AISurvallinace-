/*
* Copyright (c) 2007, 浙江大华技术股份有限公司
* All rights reserved.
*
* 文件名称：CLinuxRTPServer.h
* 文件标识：参见配置管理计划书
* 摘　　要：RTP linux高性能服务器类，采用epoll模型实现。
*
*/
#ifndef __FE_RTP_LINUX_SERVER_H__
#define __FE_RTP_LINUX_SERVER_H__

#if !defined(_WIN32) && !defined(_WIN64) && !defined(WINCE) && !defined(MAC)	//windows 不支持epoll

#define MAX_EPOLL_SESSION_NUM	4096

#define EPOLL_EVENTS_EACH_WAIT	10

#include "RTP/CRTPServerBase.h"
#include "RTP/RTPEpollDefs.h"
#include "AX_API/AX_Mutex.h"

#include <sys/epoll.h>

class CLinuxRTPServer : public CRTPServerBase
{
public:
	CLinuxRTPServer();
	virtual ~CLinuxRTPServer();

	virtual int addSession(CRTPSession* session);
	virtual int delSession(int id);
	virtual int updateSession(int id);
	virtual int heartbeat(void);

	virtual int setSelectTimeout(int sec, int usec);
	virtual int setTPBufferSize(TPType type, int size);

private:
	typedef struct
	{
		CRTPSession* rtpSession;
		CRTPEpollSocketData*  epSocketData_remoteRTP;
		CRTPEpollSocketData*  epSocketData_localRTP;
		CRTPEpollSocketData*  epSocketData_remoteRTCP;
		CRTPEpollSocketData*  epSocketData_localRTCP;
	}EpollRtpSession;

	EpollRtpSession	_epRtpSessions[MAX_EPOLL_SESSION_NUM];
	AX_Mutex		_mutexRtpSessions;
	int				_highRtpSessionIdx;

	//my epoll fd
	int _epFd;
	epoll_event	_evs[EPOLL_EVENTS_EACH_WAIT];

	int	addSocketIntoEpollFd(int sessionIdx, int socket);

	int dealOneEvent(epoll_event& ev);
};

#endif //#ifndef WIN32

#endif//__FE_RTP_LINUX_SERVER_H__

