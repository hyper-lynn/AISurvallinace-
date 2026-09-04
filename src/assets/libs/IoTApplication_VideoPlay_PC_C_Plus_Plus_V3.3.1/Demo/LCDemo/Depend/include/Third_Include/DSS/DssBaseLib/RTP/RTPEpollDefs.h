/*
* Copyright (c) 2007, 浙江大华技术股份有限公司
* All rights reserved.
*
* 文件名称：CRTPIocpDefs.h
* 文件标识：参见配置管理计划书
* 摘　　要：RTP win32完成端口数据结构定义
*
*/
#ifndef __FE_RTP_EPOLL_DEFS_H__
#define __FE_RTP_EPOLL_DEFS_H__

#include "AX_API/AX_IAddRefAble.h"

class CRTPEpollSocketData : public AX_IAddRefAble
{
public:
	CRTPEpollSocketData();

	virtual ~CRTPEpollSocketData();

	int					_sessionIdx;
	int					_socket;
};


#endif//__FE_RTP_IOCP_DEFS_H__

