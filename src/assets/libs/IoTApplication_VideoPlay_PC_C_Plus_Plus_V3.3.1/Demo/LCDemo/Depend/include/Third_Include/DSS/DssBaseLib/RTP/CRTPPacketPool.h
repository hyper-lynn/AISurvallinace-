/*
* Copyright (c) 2008, 杭州安谐软件有限公司
* All rights reserved.
*
* 文件名称：CRTPPacketPool.h
* 文件标识：
* 摘　　要：RTP 缓存沲，实现rtp packet的循环利用。
*
* 当前版本：1.0
* 作　　者：林坚彦
* 完成日期：2008年5月30日
* 修订记录：创建
*/

#ifndef __FE_RTP_PACKET_POOL_H__
#define __FE_RTP_PACKET_POOL_H__

#include "TPLayer/ThreadMutex.h"
#include "RTP/CRTPPacket.h"

#define CRTPPACKETPOOL_MAX_POOL_SIZE_DEFAULT 10000

class CRTPPacketPool
{
public:
	~CRTPPacketPool();

	static CRTPPacketPool* Instance();
	static int UnInstance();

	CRTPPacket*			CreatePacket();


	void SetMaxPoolSize(size_t maxPoolSize);

protected:
	//user should not call this function
	friend class CRTPPacket;
	int					Recycle(CRTPPacket* packet);

protected:
	CRTPPacketPool(); //singleton

	static CRTPPacketPool *_this;
	BufferQueue _pool;
	CThreadMutex _mutex;
	size_t _maxPoolSize;
};

#endif
