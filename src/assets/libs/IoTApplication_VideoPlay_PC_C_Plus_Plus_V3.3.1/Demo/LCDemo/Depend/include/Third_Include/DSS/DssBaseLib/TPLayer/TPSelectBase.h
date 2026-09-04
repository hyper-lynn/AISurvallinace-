/*
* Copyright (c) 2010, 浙江大华技术股份有限公司
* All rights reserved.
*
* 文件名称：TPSelectBase.h
* 文件标识：
* 摘　　要：TPLayer的统一Select实现
*
*/
#ifndef __TP_SELECT_BASE_H__
#define __TP_SELECT_BASE_H__

#include "TPLayer/ITPObject.h"
#include "TPLayer/ThreadMutex.h"

#define TP_OBJECT_NUM 1024

#define TP_OBJECT_GROUP 1
#define TP_OBJECT_PIECE 1024

class TPSelectBase
{
public:
	TPSelectBase(CNewMutex* mutex,bool rtpOverTcp=false);
	virtual ~TPSelectBase();

	virtual int addTPObject(ITPObject* session);
	virtual int delTPObject(int id);
	virtual int updateTPObject(int id);
	virtual int heartbeat(void);

	virtual int setSelectTimeout(int sec, int usec);
	virtual int setTPBufferSize(TPType type, int size);

private:
	struct timeval _timeout;

	ITPObject* _sessions[TP_OBJECT_NUM];
	CNewMutex* _mutex;

	int _sessionNum;
	int _highSessionIdx;	//_sessions当前被使用的最高下标

	fd_set* _readfds[TP_OBJECT_GROUP];
	fd_set* _writefds[TP_OBJECT_GROUP];
	int _maxfd[TP_OBJECT_GROUP];

	int createFds();
protected:
	bool _rtpOverTcp;

private:
	int heartBeatTcp();
	int createFdsTcp();
};

#endif//__FE_RTP_SERVER_BASE_H__
