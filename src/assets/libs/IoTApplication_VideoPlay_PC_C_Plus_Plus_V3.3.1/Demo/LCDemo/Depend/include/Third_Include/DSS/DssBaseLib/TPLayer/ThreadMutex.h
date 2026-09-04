/*
* Copyright (c) 2006, 浙江大华安防科技有限公司
* All rights reserved.
*
* 文件名称：ThreadMutex.h
* 文件标识：共享锁助手类
* 摘要：提供共享锁封装，为上层提供平台无关的助手类。
*		使用时，只需要在需要加锁的地方声明一个静态对象
*		就可以了，构造函数自动试图获得锁。而使用完毕
*		析构函数自动释放锁并释放使用资源。
*
*
* 历史：创建，2006年7月26日，李明江(li_mingjiang@dahuatech.com)
*
*/
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_THREADMUTEX_H__51105975_377E_4223_970C_574251793AE2__INCLUDED_)
#define AFX_THREADMUTEX_H__51105975_377E_4223_970C_574251793AE2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#if defined(_WIN32)||defined(WINCE)||defined(_WIN64)
	#include "AX_API/winsock2i.h"
#else
	#include <pthread.h> 
#endif

#include "AX_API/AX_IAddRefAble.h"

class CNewMutex : public AX_IAddRefAble
{
public:
	CNewMutex() {}
	virtual ~CNewMutex() {}

	virtual int lock(void) = 0;
	virtual int unlock(void) = 0;
};

class CNullMutex : public CNewMutex
{
public:
	CNullMutex() {}
	virtual ~CNullMutex() {}

	virtual int lock(void) { return 0; }
	virtual int unlock(void) { return 0; }
};


class CThreadMutex : public CNewMutex
{
public:
	CThreadMutex (void);
	virtual ~CThreadMutex (void);

	virtual int lock(void);
	virtual int unlock(void);
#if defined(_WIN32) || defined(_WIN64)
	CRITICAL_SECTION mutex_;
#else
	pthread_mutex_t mutex_;
#endif
};

#endif // !defined(AFX_THREADMUTEX_H__51105975_377E_4223_970C_574251793AE2__INCLUDED_)
