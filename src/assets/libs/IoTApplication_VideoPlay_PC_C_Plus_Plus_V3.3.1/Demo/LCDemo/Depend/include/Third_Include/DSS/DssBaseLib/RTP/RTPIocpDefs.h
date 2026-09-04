/*
* Copyright (c) 2007, 浙江大华技术股份有限公司
* All rights reserved.
*
* 文件名称：CRTPIocpDefs.h
* 文件标识：参见配置管理计划书
* 摘　　要：RTP win32完成端口数据结构定义
*
*/
#ifndef __FE_RTP_IOCP_DEFS_H__
#define __FE_RTP_IOCP_DEFS_H__

#if defined(_WIN32) || defined(_WIN64)	//linux 不支持完成端口

#include <deque>
#include "AX_API/AX_IAddRefAble.h"
#include "AX_API/AX_Mutex.h"

class CRTPPacket;

typedef enum
{
	op_none = 0,
	op_recv,
	op_send,
}OP_TYPE;

class CRTPPerHandleData : public AX_IAddRefAble
{
public:
	CRTPPerHandleData();

	virtual ~CRTPPerHandleData();

	int					_sessionIdx;
	int					_socket;
};

class CRTPPerIoDataPool;
class CRTPPerIoData : public AX_IAddRefAble
{
public:
	friend class CRTPPerIoDataPool;
	virtual ~CRTPPerIoData();
	int SetPool(CRTPPerIoDataPool* pool);
	virtual int release();

	OVERLAPPED	_ol;
	OP_TYPE		_operationType;

	//serves recv.
	char		_buf[8*1024];	//at most 8k.
	int			_bufLen;
	int			_recvLen;
	struct sockaddr_in	_recvAddr;
	int			_addrSize;

	//serves send
	CRTPPacket*	_sendPacket;		//只发送RTP包
	LONG		_totalBytes;	//总字节数
	LONG		_sentBytes;	//已发送字节数

	//为了适应WSA系统接口的参数要求
	WSABUF		_wsabuf;
protected:
	int Reset();
	CRTPPerIoData();	//direct new not allowed
	CRTPPerIoDataPool* _pool;
};

class CRTPPerIoDataPool
{
public:
	~CRTPPerIoDataPool();

	static CRTPPerIoDataPool* Instance();
	static int UnInstance();

	CRTPPerIoData*			CreateRTPPerIoData();

	//user should not call this function
	int					Recycle(CRTPPerIoData* packet);

protected:
	CRTPPerIoDataPool(); //singleton

	static CRTPPerIoDataPool *_this;
	std::deque<CRTPPerIoData*> _dataQueue;
	AX_Mutex _mutex;

private:
};

#endif //WIN32

#endif//__FE_RTP_IOCP_DEFS_H__

