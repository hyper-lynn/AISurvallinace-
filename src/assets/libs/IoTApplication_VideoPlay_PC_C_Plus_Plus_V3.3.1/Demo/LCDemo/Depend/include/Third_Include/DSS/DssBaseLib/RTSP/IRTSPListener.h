/*
* Copyright (c) 2007, 浙江大华技术股份有限公司
* All rights reserved.
*
* 文件名称：IRTSPListener.h
* 文件标识：参见配置管理计划书
* 摘　　要：RTSP监听器接口。实现RTSP协议的服务需要实现本接口，并在相应的server和client实现上注册自己，以便相应的
			操作发生时会被回调。
			回调会传RTSP的PDU。所有的应答操作会被回调在onResponse中。因为HTTP和RTSP应答包中无操作数据，所以协议
			栈无法识别对应的请求，需要由上层应用自己实现，将应答和请求进行匹配，一般地，cseq用来匹配操作。
*
* 当前版本：1.0
* 作　　者：李明江
* 完成日期：2007年7月10日
* 修订记录：1. 增加GetParameter、SetParameter的对应回调。
			2. 增加onResponse接口。

*
* 取代版本：0.1
* 原作者　：李明江
* 完成日期：2007年7月1日
* 修订记录：创建
*/
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IRTSPLISTENER_H__F43DB502_9331_49DC_BE03_9C6EA09CDE58__INCLUDED_)
#define AFX_IRTSPLISTENER_H__F43DB502_9331_49DC_BE03_9C6EA09CDE58__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RTSPPdu.h"

class IRTSPListener  
{
public:
	virtual ~IRTSPListener() {}
	virtual int onClientConnect(int engineId, int clientId, char* ip, int port) = 0;
	virtual int onClientDisconnect(int engineId, int clientId) = 0;
	virtual int onSetup(int engineId, int clientId, CRTSPPdu* pdu) = 0;
	virtual int onAnnounce(int engineId, int clientId, CRTSPPdu* pdu) = 0;
	virtual int onTeardown(int engineId, int clientId, CRTSPPdu* pdu) = 0;
	virtual int onOptions(int engineId, int clientId, CRTSPPdu* pdu) = 0;
	virtual int onDescribe(int engineId, int clientId, CRTSPPdu* pdu) = 0;
	virtual int onPlay(int engineId, int clientId, CRTSPPdu* pdu) = 0;
	virtual int onPause(int engineId, int clientId, CRTSPPdu* pdu) = 0;
	virtual int onRecord(int engineId, int clientId, CRTSPPdu* pdu) = 0;
	virtual int onBinaryData(int engineId, int clientId, char* data, int len) = 0;
	virtual int onGetParameter(int engineId, int clientId, CRTSPPdu* pdu) = 0;
	virtual int onSetParameter(int engineId, int clientId, CRTSPPdu* pdu) = 0;

	virtual int onResponse(int engineId, int clientId, CRTSPPdu* pdu) = 0;
};

#endif // !defined(AFX_IRTSPLISTENER_H__F43DB502_9331_49DC_BE03_9C6EA09CDE58__INCLUDED_)
