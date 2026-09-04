/*
* Copyright (c) 2007, 浙江大华技术股份有限公司
* All rights reserved.
*
* 文件名称：TPTCPServer.h
* 文件标识：参见配置管理计划书
* 摘　　要：TCP服务器功能类

* 当前版本：1.1
* 作    者：林坚彦
* 完成日期：2008年4月28日

* 当前版本：1.0
* 作　　者：李明江
* 完成日期：2007年4月28日

*
* 取代版本：1.0
* 原作者　：
* 完成日期：
* 修订记录：
*/
#ifndef TPTCPSERVER
#define TPTCPSERVER

#ifdef __linux__
#pragma GCC system_header	// 声明为系统头文件，防止协议库因为警告编译不过
#endif

#include "TPLayer/ITPListener.h"
#include "TPLayer/ITPObject.h"
#include "AX_API/AX_Mutex.h"

#include <deque>

class TPTCPServer : public ITPObject
{
public:
    TPTCPServer(ITPListener* tcpserverapp, int engineId = 0);
	TPTCPServer(int engineId, ITPListener* listener, CNewMutex* mutex);
    virtual ~TPTCPServer();

public: 
    virtual int CloseClient(int id);

    virtual int Close();
    
	virtual int Listen(char* ip, int port, bool enableReuseAddr = true);
    
    virtual int Send(int id, char *pBuf, unsigned int iBufLen);

    virtual int Heartbeat();
	virtual int HeartbeatWithoutSelect() { return Heartbeat(); }

	virtual Queue_List* GetSendQueue(int connId);

	virtual int SetMaxDataQueueLength(size_t maxDataQueueLength);

protected:
	int sendInside(int id, char* pBuf, unsigned int iBufLen);
	int closeInside();
	virtual int clearSendBuffer();	
	virtual int fillFds(int& maxfd, fd_set* readfds, fd_set* writefds);
	virtual int dealFDResult(int& fds,fd_set* readfds, fd_set* writefds,bool& fdsChange);


protected:
	size_t	_maxDataQueueLength;

protected:
	void addPendingCloseClient(int id);
	int dealPendingCloseClients();
	void pendingCloseClient(int id);
	std::deque<int> _pendingCloseClients;
	// AX_Thread_Mutex _pendingCloseClientsMutex;
	AX_Mutex _pendingCloseClientsMutex;
};

#endif

