/*
* Copyright (c) 2007, 浙江大华技术股份有限公司
* All rights reserved.
*
* 文件名称：CRTPPacket.h
* 文件标识：参见配置管理计划书
* 摘　　要：RTP PDU封装类，实现RFC中定义的RTP PDU。
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

#ifndef __FE_RTP_PACKET_H__
#define __FE_RTP_PACKET_H__

#ifdef WIN32
#pragma warning(disable : 4201)		/* Nameless struct/union */
#endif

#include <vector>
#include <deque>

#include "RTP/RTPProtocol.h"
#include "AX_API/AX_IAddRefAble.h"

/* 
 * RFC3550.txt
 * RTP: A Transport Protocol for Real-Time Applications
 *
 * The RTP header has the following format:
    0                   1                   2                   3
    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |V=2|P|X|  CC   |M|     PT      |       sequence number         |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                           timestamp                           |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |           synchronization source (SSRC) identifier            |
   +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
   |            contributing source (CSRC) identifiers             |
   |                             ....                              |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * version (V): 2 bits
 * padding (P): 1 bit
 * extension (X): 1 bit
 * CSRC count (CC): 4 bits
 * marker (M): 1 bit
 * payload type (PT): 7 bits
 * sequence number: 16 bits
 * timestamp: 32 bits
 * SSRC: 32 bits
 * CSRC list: 0 to 15 items, 32 bits each
 */
class CRTPPacket;
typedef std::deque<CRTPPacket*> BufferQueue;

#define RTP_BUFFER_LENGTH 1024*5	//9192

class CRTPSession;
class CRTPServerBase;
class CRTPPacketPool;
class CWin32RTPServer;
class CLinuxRTPServer;

class CRTPPacket:public AX_IAddRefAble
{
public:
	friend class CRTPSession;
	friend class CRTPSessStdTcp;
	friend class CRTPServerBase;
	friend class CWin32RTPServer;
	friend class CLinuxRTPServer;

	CRTPPacket(int size);
// 	CRTPPacket(const CRTPPacket& packet);
	CRTPPacket(char* data, int len);
	virtual ~CRTPPacket();

	void AddCSRC(int csrc);

	/* 版本号, 根据RFC3550定义, 版本号为2 */
	int  GetVersion() ;
	void SetVersion(int version);

	bool GetPadding();
	void SetPadding(bool pad);

	/* RTP头部扩展, 目前不支持 */
	bool GetExtension() ;
	void SetExtension(bool ext);

	/* 标记, 用来标记I帧 */ 
	bool GetMarker() ;
	void SetMarker(bool mark);

	/* 包体数据类型, DVR的流媒体数据类型设为DynamicBase */
	PayloadTypes GetPayloadType() ;
	void SetPayloadType(PayloadTypes t);

	/* 包序号 */
	unsigned short GetSequenceNumber() ;
	void SetSequenceNumber(unsigned short n);

	/* 包时戳 */
	unsigned long GetTimestamp() ;
	void SetTimestamp(unsigned long time);

	/* SSRC, 同步源标识 */
	unsigned long GetSyncSource() ;
	void SetSyncSource(unsigned long ssrc);

	/* CSRC, 可选同步源标识	 */
	int  GetContribSrcCount() ;
	unsigned long GetContribSource(int index) ;
	void SetContribSource(int index, unsigned long csrc) ;

	/* RTP头长度 */
	int GetHeaderSize() ;

	/* RTP头部扩展, 目前不支持 */
	unsigned short GetExtensionType() ;
	void SetExtensionType(unsigned short type);
	void SetExtensionSize(unsigned short len);
	unsigned short GetExtensionSize() ;
	char* GetExtensionPtr() ;

	/* 添加负载数据 */
	int AddPayload(char* data, int len);
	/* 向负载尾部添加数据 */
	int AppendPayload(char* data, int len);	
	/* 读取负载数据,不包括RTP头数据. */
	char* ReadPayload(int& len);
	int GetPayloadLen(void);

	char* ReadPadding(int& len);
	int GetPaddingLen();

	int Copy(CRTPPacket* packet);

	int SetBuffer(char* data, int len);
	char* GetBufferPtr(void);
	int GetBufferMaxLen(void);
	int GetBufferLen(void);

	int SetPool(CRTPPacketPool* pool);

	char* GetRtspBufferPtr();
	int SetRtspHead(int channel);
	int GetRtspPacketLen();

	virtual int release();

protected:
	union
	{
		struct
		{
			char _pgspPacket[4 + RTP_BUFFER_LENGTH];
		};
		struct{
		char _pgspHeader[4]; //
		char _buffer[RTP_BUFFER_LENGTH];
		};
	};

	int _bufferLen;	// total size = sizeof(header) + sizeof(payload) + sizeof(padding)

	CRTPPacketPool* _pool;
};

class IRTPListener
{
public:
	virtual ~IRTPListener() {}
	/* 返回值为0表示由底层删除packet，上层自行拷贝。如果为非0值表示由上层管理Packet
	 * 底层不管理
	 */
	virtual int onRTPPacket(int /*session*/, int /*connId*/, CRTPPacket* /*packet*/) = 0;
	virtual int onConnect(int /*engineId*/, int /*connId*/, const char* /*ip*/, int /*port*/) = 0;
	virtual int onClose(int /*engineId*/, int /*connId*/) {return 0;}

	// 原始数据回调接口  return > 0 则不触发onRTPPacket 
	virtual int onOrgDate(int /*session*/, int /*connId*/, const char * /*data*/, int /*dataLen*/){return 0;};
};


#endif
