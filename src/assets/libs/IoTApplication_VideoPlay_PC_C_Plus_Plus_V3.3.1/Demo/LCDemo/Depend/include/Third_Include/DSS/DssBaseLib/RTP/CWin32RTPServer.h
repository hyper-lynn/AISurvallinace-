/*
* Copyright (c) 2007, 浙江大华技术股份有限公司
* All rights reserved.
*
* 文件名称：CWin32RTPServer.h
* 文件标识：参见配置管理计划书
* 摘　　要：RTP win32高性能服务器类，采用IOCP模型实现。
*
*/
#ifndef __FE_RTP_WIN32_SERVER_H__
#define __FE_RTP_WIN32_SERVER_H__

#if defined(_WIN32) ||	defined(_WIN64)//linux 不支持完成端口

#define MAX_THREAD_NUM_FOR_WIN32_RTP_SERVER		10
#define MAX_IOCP_SESSION_NUM	4096

#include "RTP/CRTPServerBase.h"
#include "RTP/RTPIocpDefs.h"
#include "AX_API/AX_Mutex.h"

class CWin32RTPServer : public CRTPServerBase
{
public:
	CWin32RTPServer();
	virtual ~CWin32RTPServer();

	virtual int addSession(CRTPSession* session);
	virtual int delSession(int id);
	virtual int updateSession(int id);
	virtual int heartbeat(void);

	virtual int setSelectTimeout(int sec, int usec);
	virtual int setTPBufferSize(TPType type, int size);

	static void* iocpRoutineThreadFunc(void* param);
	int	iocpRoutineThreadFunc_Imp();

private:

	typedef struct
	{
		CRTPSession* rtpSession;
		CRTPPerHandleData*  perHandleData_remoteRTP;
		bool				recvPosted_remoteRTP;		//记录是否已发送request请求。remote socket在发送数据之前不一定执行bind操作，所以在发送数据完成之后可能需要补发request请求
		CRTPPerHandleData*  perHandleData_localRTP;
		bool				recvPosted_localRTP;
		CRTPPerHandleData*  perHandleData_remoteRTCP;
		bool				recvPosted_remoteRTCP;
		CRTPPerHandleData*  perHandleData_localRTCP;
		bool				recvPosted_localRTCP;
	}IocpRtpSession;

	IocpRtpSession	_iocpRtpSessions[MAX_IOCP_SESSION_NUM];
	AX_Mutex		_mutexRtpSessions;
	int				_highRtpSessionIdx;

	HANDLE			_completionPort;
	AX_hthread_t	_iocpThreads[MAX_THREAD_NUM_FOR_WIN32_RTP_SERVER];
	int				_threadNum;
	bool			_threadsExit;

	int	addSocketIntoCompletionPort(int sessionIdx, int socket);
	int PostRecvRequest(int sessionIdx, int socket);

	typedef struct  
	{
		CRTPPerIoData*	ioData;
		int				sessionIdx;	//session数组下标
		int				socket;		//socket
	}IocpRtpData;
	std::deque<IocpRtpData>	_recvIoDatas;
	AX_Mutex		_mutexRecvIoData;

	std::deque<IocpRtpData>	_sentIoDatas;
	AX_Mutex		_mutexSentIoData;
};

#endif //WIN32

#endif//__FE_RTP_WIN32_SERVER_H__

