/*
* Copyright (c) 2008, 杭州安谐软件有限公司
* All rights reserved.
*
* 文件名称：Singleton.h
* 文件标识：
* 摘　　要：单件模版类
*

* 当前版本：1.0
* 原作者　：高圩
* 完成日期：2008年5月22日
* 修订记录：创建

* 当前版本：1.1
* 原作者　：高圩
* 完成日期：2010年01月07日
* 修订记录：增加多线程的安全性

* 当前版本：2.0
* 原作者　：高圩
* 完成日期：2010年02月01日
* 修订记录：增加SingletonStatic，此单件类可以不用担心内存释放，不必调用unInstance来释放内存
*/

#ifndef SINGLETON_H
#define SINGLETON_H

//////////////////////////////////////////////////////////////////////////
// class Singleton 
//////////////////////////////////////////////////////////////////////////
#include "AX_API/AX_Mutex.h"

template <class T> 
class Singleton  
{
public:
	static T* instance()
	{ 
		if ( 0 == s_instance )
		{
			s_mutex.acquire();
			if ( 0 == s_instance )
			{
				s_instance = new T;
			}
			s_mutex.release();
		}

		return s_instance;
	}

	static void unInstance()
	{
		if ( 0 != s_instance )
		{
			s_mutex.acquire();
			if ( 0 != s_instance )
			{
				delete s_instance;
				s_instance = 0;
			}
			s_mutex.release();
		}
	}

protected:
	Singleton() {}
	virtual ~Singleton() {}

private:
	Singleton(const Singleton<T> &); //不实现 
	Singleton<T>& operator= (const Singleton<T> &); //不实现

	static T* s_instance;
	static AX_Mutex s_mutex;
};

template <class T>
T* Singleton<T>::s_instance = 0;

template <class T>
AX_Mutex Singleton<T>::s_mutex;

//////////////////////////////////////////////////////////////////////////
// class SingletonStatic
//////////////////////////////////////////////////////////////////////////
template <class T> 
class SingletonStatic  
{
public:
	static T* instance()
	{
		return &s_instance;
	}

protected:
	SingletonStatic() {}
	virtual ~SingletonStatic() {}

private:
	SingletonStatic(const SingletonStatic<T> &); //不实现 
	SingletonStatic<T>& operator= (const SingletonStatic<T> &); //不实现

	static T s_instance;
};

template <class T>
T SingletonStatic<T>::s_instance;

//////////////////////////////////////////////////////////////////////////

#endif
