#ifndef DH_DSS_POOL_OBJECT_H_INCLUDED
#define DH_DSS_POOL_OBJECT_H_INCLUDED
/*
* Copyright (c) 2010, 浙江大华
* All rights reserved.
*
* 文件名称：poolobj.h
* 文件标识：
* 摘　　要：封装使用AX_IAddRefAble的类对象以及其对象池
*

* 当前版本：1.0
* 原作者　：杨震
* 完成日期：2010年03月31日
* 修订记录：创建
*/

/*
使用 创建CTestPacket对象

class CTestPacket;
typedef AX_RefPtr<CTestPacket> CTestPacketPtr;
typedef CPoolObjectPool<CTestPacket> CTestPacketPool;
class CTestPacket:public CPoolObject<CTestPacket>
{

};

配合单件类,使用
#include "Singleton.h"
typedef Singleton<CTestPacketPool> CTestPacketPoolSingleton;

void test_function()
{
	//程序中间使用
	CTestPacketPtr ptr=CTestPacketPoolSingleton::instance()->createObject();
}

int main(int argc,char* argv[])
{
	test_function();
	//程序最后清理
	CTestPacketPoolSingleton::unInstance();
}
*/

#include <list>
#include "AX_API/AX_IAddRefAble.h"
#include "AX_API/AX_Mutex.h"
#include "AX_API/AX_Thread_Guard.h"


// 使用时，要求T继承自CPoolObject<T>

template<class T>
class CPoolObject;

template<class T>
class CPoolObjectPool
{
public:
	typedef AX_RefPtr<T> ObjectPtr;
	typedef CPoolObject<T> PoolObjectType;
public:
	CPoolObjectPool(){}
	~CPoolObjectPool()
	{
		typename std::list<ObjectPtr>::iterator iter=_list.begin();
		for(;_list.end()!=iter;++iter)
		{
			ObjectPtr& ptr=*iter;
			ptr->setPool(NULL);   // T是CPoolObject<T>的子类
		}
		_list.clear();
	}
public:
	ObjectPtr createObject()
	{
		AX_Guard<AX_Mutex> guard(_mutex);
		if(!_list.empty())
		{
			ObjectPtr ptr=_list.front();
			_list.pop_front();
			return ptr;
		}
		ObjectPtr ptr= new T;
		ptr->setPool(this);
		return ptr;
	}
protected:
	void recycle(T* obj)
	{
		AX_Guard<AX_Mutex> guard(_mutex);
		_list.push_back(obj);
	}
protected:
	std::list<ObjectPtr>	_list;
	AX_Mutex				_mutex;
	// friend class PoolObjectType; // old standard not support friend with typedef
	friend class CPoolObject<T>;
};

template<class T>
class CPoolObject:public AX_IAddRefAble
{
public:
	typedef CPoolObjectPool<T> poolType;
	// typedef CPoolObject<T> thisType;
	// typedef AX_RefPtr<thisType> thisTypePtr;
protected:
	CPoolObject()
	{
		_pool=NULL;
	}
public:
	virtual int release(void)
	{
		// _mutex.acquire();
		// int ret = (--_ref);
		// _mutex.release();

		int ret = release_without_delete();

		if (ret == 0)
		{
			if(NULL==_pool)
				delete this;
			else
				_pool->recycle((T*)this);  // T是CPoolObject<T>的子类
			return 0;
		}

		return ret;
	}
protected:
	// friend class poolType;
	friend class CPoolObjectPool<T>;
	void setPool(poolType* pool)
	{
		_pool=pool;
	}
	poolType* _pool; 
};

#endif//DH_DSS_POOL_OBJECT_H_INCLUDED

