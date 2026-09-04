/**
 * Copyright (c) 2012, 浙江大华
 * All rights reserved.
 *
 * 文件名称：MulticastSession.h
 * 文件标识：
 * 摘　　要：组播网络交互会话
 *
 * 当前版本：1.0
 * 原作者　：
 * 完成日期：2014年3月14日
 * 修订记录：创建、简单封装UDP SERVER功能
 */

#ifndef INCLUDED_DPSDK_MULTICASTSESSION_H
#define INCLUDED_DPSDK_MULTICASTSESSION_H

#include "DPSDKDefine.h"
#include "libdsl/DMutex.h"
#include "TPLayer/ITPListener.h"

class ITPObject;

BEGIN_NAMESPACE_DPSDK
////////////////////////////////////////////////////////////////////////////////////////////
#define RECV_DATA_LEN					5*1024
class IMulticastSessionListener;

class MulticastSession: public ITPListener
{
public:
	MulticastSession(int sessionId = 0);
	virtual ~MulticastSession();

public:
	int AddMulticastSessionListener(IMulticastSessionListener *pMulticastSessionListener);
	int DelMulticastSessionListener();

	// 设置侦听信息
	int SetListenAddress(char* ip, int port);
	// 设置超时信息
	int SetTPSelectTimeout(long nSecond, long nUSecord);

	// 设置缓存区的大小 bRecvFlag为true是设置接收缓冲区,为false是设置发送缓冲区
	int	SetBufferSize(int nBufferSize, bool bRecvFlag = true);

	// 线程驱动函数
	int heartbeat(void);

	void LockData();
	void UnLockData();
	
	ITPObject* GetListenObject();

public:
	// TODO:考虑到该类是通过外部线程去驱动，这里的回调就先不处理了，后面用到时再完善
	virtual int onData(int engineId, int connId, const char* data, int len);
	virtual int onClose(int engineId, int connId);
	virtual int onConnect(int engineId, int connId, const char* ip, int port);
	virtual int onSendDataAck(int engineId, int connId, int id, int sendLen);
	virtual int onSendStatus(int engineId, int connId, int statusType, int param);
	virtual int onTimeout(int id, int context);

public:
	virtual int OnServerData(char* data, int len);
	
protected:
	/////////////////////////////受m_mtxData锁保护/////////////////////////////
	ITPObject							*m_pListenObject;				//监听对象
	dsl::DMutex							m_mtxData;						//数据锁
	int									m_nSessionId;					//会话ID，由外部传入
	char								m_szListenIp[DPSDK_IP_LEN];		//监听IP
	int									m_nListenPort;					//监听端口

	IMulticastSessionListener			*m_pCallbackListener;			//上层回调模块

	long								m_nSecond;						//超时参数：秒
	long								m_nUSecond;						//超时参数：毫秒

	int									m_nSendBufferSize;				//发送缓冲大小
	int									m_nRecvBufferSize;				//接收缓冲大小

	char								*m_pRecvPacket;					//数据包
	int									m_nRecvPacketWhole;				//数据包大小
	int									m_nRecvPacketed;				//已接收的长度
	
	////////////////////////////////////////////////////////////////////////////////////////
};

class IMulticastSessionListener
{
public:
	virtual ~IMulticastSessionListener(){}
	
	virtual int OnMulticastData(int sessionid, char* data, int len) = 0;
};
////////////////////////////////////////////////////////////////////////////////////////////
END_NAMESPACE_DPSDK

#endif
