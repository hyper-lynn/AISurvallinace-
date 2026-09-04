/*
* Copyright (c) 2007, 浙江大华技术股份有限公司
* All rights reserved.
*
* 文件名称：CRTCPPacket.h
* 文件标识：参见配置管理计划书
* 摘　　要：RTCP PDU封装类，实现RFC中定义的RTCPPDU。
*
* 当前版本：1.0
* 作　　者：李明江
* 完成日期：2007年7月15日
* 修订记录：稳定，标准RTP及带重发的RTP会话都完成了。

*
* 取代版本：0.1
* 原作者　：李明江
* 完成日期：2007年7月1日
* 修订记录：创建
*/

#ifndef __FE_RTCP_PACKET_H__
#define __FE_RTCP_PACKET_H__

#include <deque>
#include "RTP/RTPProtocol.h"
#include "AX_API/AX_IAddRefAble.h"

class CRTCPPacket;
typedef std::deque<CRTCPPacket*> RtcpBufferQueue;

class CRTCPPacketPool;

class CRTCPPacket:public AX_IAddRefAble
{
public:
	CRTCPPacket(int size);
	CRTCPPacket(RTCPTYPE type);
	CRTCPPacket(char* data, int len);
	virtual ~CRTCPPacket();

	virtual int release();

	int GetVersion();
	void SetVersion(int version);

	int GetPadding();
	void SetPadding(int padding);

	int GetRC();
	void SetRC(int RC);

	RTCPTYPE GetPayloadType();
	void SetPayloadType(RTCPTYPE payload);

	unsigned short GetLength();
	void SetLength(unsigned short length);

	unsigned long GetSenderSSRC();
	void SetSenderSSRC(unsigned long ssrc);
//数据体部分。

	//SR和RR使用
	int GetSenderInfo(SSenderInfo* info);
	int SetSenderInfo(SSenderInfo* info);

	//SR和RR使用。index从1开始。第一个block索引是1.
	int AddReportBlock(int index, SReportBlock* block);
	int GetReportBlock(int index, SReportBlock* block);

	//SDES使用
	int AddChunk(int index, SChunk* chunk);
	int GetChunk(int index, SChunk* chunk);

	//APP 重发使用，其它的App不支持
	int GetAppResend(SAppResend* info);
	int SetAppResend(SAppResend* info);

	int SetBuffer(char* data, int len);

//二进制流处理	
	unsigned char* GetStream();
	int GetStreamLen();

	int SetPool(CRTCPPacketPool* pool);

private:
	unsigned char* _data;
	int _length;

	CRTCPPacketPool* _pool;
};

class IRTCPListener
{
public:
	virtual ~IRTCPListener() {}
	virtual int onRTCPPacket(int session, int connId, CRTCPPacket* packet) = 0;
	virtual int onConnect(int engineId, int connId, const char* ip, int port) = 0;
};

#endif

