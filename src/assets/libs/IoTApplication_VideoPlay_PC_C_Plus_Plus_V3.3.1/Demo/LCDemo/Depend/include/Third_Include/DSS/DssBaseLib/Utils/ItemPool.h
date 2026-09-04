/*
* Copyright (c) 2009, 浙江大华
* All rights reserved.
*
* 文件名称：ItemPool.h
* 文件标识：
* 摘　　要：管理内存对象的缓冲模板，多线程安全
*			可以配合Singleton模板使用，创建单间类对象，如下：
*			Struct A;
*			typedef CItemPool<A> APool;
*			typedef Singleton<APool> APoolSingleton;
*

* 当前版本：1.0
* 原作者　：高圩
* 完成日期：2009年10月27日
* 修订记录：创建
*/

#ifndef __ITEM_POOL_H__
#define __ITEM_POOL_H__

#include <list>
#include "AX_API/AX_Mutex.h"

template<class T>
class DOAX_DEPRECATED CItemPool
{	
public:
	//默认是多线程使用，创建锁
	CItemPool(bool isMultiThreadUse = true);
	~CItemPool();

public:
	T* createItem(void);

	void recycleItem(T* obj);

	void clear(void);

protected:
	std::list<T*> _pool;
	AX_Mutex*	  _mutex;

private: //不实现
	CItemPool(const CItemPool<T>&);
	CItemPool<T>& operator=(const CItemPool<T>&);
};


/*
*  实现
*/
template<class T>
inline CItemPool<T>::CItemPool(bool isMultiThreadUse /* = true */)
{
	if ( isMultiThreadUse )
	{
		_mutex = new AX_Mutex;
	}
	else
	{
		_mutex = NULL;
	}
}

template<class T>
inline CItemPool<T>::~CItemPool()
{
	clear();

	if ( NULL != _mutex )
	{
		delete _mutex;
		_mutex = NULL;
	}
}

template<class T>
inline T* CItemPool<T>::createItem(void)
{
	T* obj = NULL;

	if ( NULL != _mutex )
		_mutex->acquire();

	if (_pool.empty())
	{
		obj = new T;
	}
	else
	{
		obj = _pool.front();
		_pool.pop_front();
	}

	if ( NULL != _mutex )
		_mutex->release();

	return obj;
}

template<class T>
inline void CItemPool<T>::recycleItem(T* obj)
{
	if ( NULL != _mutex )
		_mutex->acquire();

	_pool.push_back(obj);

	if ( NULL != _mutex )
		_mutex->release();
}

template<class T>
inline void CItemPool<T>::clear(void)
{
	if ( NULL != _mutex )
		_mutex->acquire();

	while ( !_pool.empty() )
	{
		T* obj = _pool.front();
		_pool.pop_front();
		delete obj;
	}

	if ( NULL != _mutex )
		_mutex->release();
}

#endif
