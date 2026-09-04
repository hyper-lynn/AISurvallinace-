/*
* Copyright (c) 2007, 浙江大华技术股份有限公司
* All rights reserved.
*
* 文件名称：RTSPServer.h
* 文件标识：参见配置管理计划书
* 摘　　要：RTSP服务端框架类。实现RTSP服务的监听功能，提供发送接口，支持IRTSPListener管理与回调功能。
*
* 当前版本：1.0
* 作　　者：李明江
* 完成日期：2007年7月20日
* 修订记录：稳定版本

*
* 取代版本：0.1
* 原作者　：李明江
* 完成日期：2007年7月1日
* 修订记录：创建
*/
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RTSPSERVER_H__D08B8F57_7675_46B9_8CC8_78A97194D9F4__INCLUDED_)
#define AFX_RTSPSERVER_H__D08B8F57_7675_46B9_8CC8_78A97194D9F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RTSP/RTSPBase.h"
#include "RTSP/IRTSPListener.h"
#include "RTSP/RTSPBuffer.h"
#include "TPLayer/ITPObject.h"
#include "TPLayer/TPTCPServer.h"

class CRTSPServer : public CRTSPBase, ITPListener
{
public:
	CRTSPServer(IRTSPListener* listener, int id = 0);
	virtual ~CRTSPServer();

	virtual int start(char* ip, int port);
	virtual int sendPacket(int clientId, CRTSPPdu* pdu);
	virtual int sendBinaryData( int clientId, char * data, int len, AX_IAddRefAble* pdu );;

	virtual int connect(char* ip, int port);
	virtual int close(void);
	virtual int closeClient(int connId);

	virtual int SetSelectTimeout(long sec, long usec);

	virtual int heartbeat(void);
public:
	virtual int onData(int engineId, int connId, const char* data, int len);
	virtual int onClose(int engineId, int connId);
	virtual int onConnect(int engineId, int connId, const char* ip, int port);
	virtual int onSendDataAck(int engineId, int connId, int id, int sendLen);
	virtual int onSendStatus(int engineId, int connId, int statusType, int param);
	virtual int onTimeout(int id, int context);

protected:
	std::map<int, CRTSPBuffer*>	_pduBuffers;
	AX_Mutex					_bufferMutex;

	std::map<int, PduMap> _queueJitt;
	CNewMutex*	_queueMutex;
};

#endif // !defined(AFX_RTSPSERVER_H__D08B8F57_7675_46B9_8CC8_78A97194D9F4__INCLUDED_)
