/*
* Copyright (c) 2008, 杭州安谐软件有限公司
* All rights reserved.
*
* 文件名称：CRTCPPacketPool.h
* 文件标识：
* 摘　　要：RTCP 缓存沲，实现rtcp packet的循环利用。
*
* 当前版本：1.0
* 作　　者：林坚彦
* 完成日期：2008年8月1日
* 修订记录：创建
*/

#ifndef __FE_RTCP_PACKET_POOL_H__
#define __FE_RTCP_PACKET_POOL_H__

#include "TPLayer/ThreadMutex.h"
#include "RTP/CRTCPPacket.h"

#define CRTCPPACKETPOOL_MAX_POOL_SIZE_DEFAULT 10000

class CRTCPPacketPool
{
public:
	~CRTCPPacketPool();

	static CRTCPPacketPool* Instance();
	static int UnInstance();

	CRTCPPacket*			CreatePacket();

	void SetMaxPoolSize(size_t maxPoolSize);

protected:
	//user should not call this function
	friend class CRTCPPacket;
	int					Recycle(CRTCPPacket* packet);

protected:
	CRTCPPacketPool(); //singleton

	static CRTCPPacketPool *_this;
	RtcpBufferQueue _pool;
	CThreadMutex _mutex;
	size_t _maxPoolSize;
};

#endif
