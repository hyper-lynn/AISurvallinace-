/*
* Copyright (c) 2007, 浙江大华技术股份有限公司
* All rights reserved.
*
* 文件名称：CRTSPBase.h
* 文件标识：参见配置管理计划书
* 摘　　要：RTSP协议基础类。定义了RTSP服务的接口。一般有两个子类：Server和Client。本类为协议栈的框架类，会
			处理RTSP的监听、远程连接，自动完成数据的接收、反序列化，并调用IRTSPListener对象。
*
* 当前版本：1.0
* 作　　者：李明江
* 完成日期：2007年7月20日
* 修订记录：稳定。

*
* 取代版本：0.1
* 原作者　：李明江
* 完成日期：2007年7月1日
* 修订记录：创建
*/
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RTSPBASE_H__35B1CB0B_4FCF_47AF_AF2D_7B4D5BF96886__INCLUDED_)
#define AFX_RTSPBASE_H__35B1CB0B_4FCF_47AF_AF2D_7B4D5BF96886__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TPLayer/ITPObject.h"
#include "RTSP/RTSPPdu.h"
#include "RTSP/IRTSPListener.h"

enum BinaryStat
{
	BINARY_Not_Embedded = -1, 
	BINARY_Continue, //未收全
	BINARY_Whole, //完整包
};

#include <map>

typedef std::map<int, AX_IAddRefAble*> PduMap;

class CRTSPBase  
{
public:
	CRTSPBase()
		: _connection(NULL), _listener(NULL), _id(0)
	{
	}
	virtual ~CRTSPBase()
	{
	}

	virtual int sendPacket(int clientId, CRTSPPdu* pdu) = 0;
	virtual int sendBinaryData(int clientId, char * data, int len, AX_IAddRefAble* pdu) = 0;

	virtual int connect(char* ip, int port) = 0;
	virtual int start(char* ip, int port) = 0;

	virtual int close(void) = 0;
	virtual int closeClient(int connId) = 0;
	virtual int heartbeat(void) = 0;
public:
	BinaryStat checkBinary(char* data, int len, int& readlen)
	{
		if(data[0] != '$') return BINARY_Not_Embedded;
		unsigned short packetLen =  htons(*(unsigned short *)(data + 2));
		if (len < (packetLen + 4))
		{
			return BINARY_Continue;
		}
		readlen =  packetLen + 4;
		return BINARY_Whole;
	}
	void addListener(IRTSPListener* listener)
	{
		_listener = listener;
	}

	ITPObject* _connection;
	IRTSPListener* _listener;
	int _id;
};

#endif // !defined(AFX_RTSPBASE_H__35B1CB0B_4FCF_47AF_AF2D_7B4D5BF96886__INCLUDED_)
