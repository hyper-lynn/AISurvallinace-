#ifdef DP_REST_PLATFORM_SDK

/*
 *@file   Singleton.h
 *@brief  单件类
 * 
 *@author cc
 *@date   2014-07-19
 *
 */

#ifndef __COMMON_SINGLETON_H__
#define __COMMON_SINGLETON_H__

#include "Mutex.h"
#include <memory.h>
#include <stdlib.h>
#include <string>

#ifdef ANDROID_NDK

namespace std
{
	template<class Y>  
	struct auto_ptr_ref {  
		Y* yp;  
		auto_ptr_ref (Y* rhs)  
		 : yp(rhs) {  
		}  
	};  

	template<class T>  
	class auto_ptr {  
	  private:  
		T* ap;    // refers to the actual owned object (if any)  
	  public:  
		typedef T element_type;  

		// constructor  
		explicit auto_ptr (T* ptr = 0) throw()  
		 : ap(ptr) {  
		}  

		// copy constructors (with implicit conversion)  
		// - note: nonconstant parameter  
		auto_ptr (auto_ptr& rhs) throw()  
		 : ap(rhs.release()) {  
		}  
		template<class Y>  
		auto_ptr (auto_ptr<Y>& rhs) throw()  
		 : ap(rhs.release()) {  
		}  
		  
		// assignments (with implicit conversion)  
		// - note: nonconstant parameter  
		auto_ptr& operator= (auto_ptr& rhs) throw() {  
			reset(rhs.release());  
			return *this;  
		}  
		template<class Y>  
		auto_ptr& operator= (auto_ptr<Y>& rhs) throw() {  
			reset(rhs.release());  
			return *this;  
		}  
		  
		// destructor  
		~auto_ptr() throw() {  
			delete ap;  
		}  

		// value access  
		T* get() const throw() {  
			return ap;  
		}  
		T& operator*() const throw() {  
			return *ap;  
		}  
		T* operator->() const throw() {  
			return ap;  
		}  

		// release ownership  
		T* release() throw() {  
			T* tmp(ap);  
			ap = 0;  
			return tmp;  
		}  

		// reset value  
		void reset (T* ptr=0) throw() {  
			if (ap != ptr) {  
				delete ap;  
				ap = ptr;  
			}  
		}  

		/* special conversions with auxiliary type to enable copies and assignments 
		 */  
		auto_ptr(auto_ptr_ref<T> rhs) throw()  
		 : ap(rhs.yp) {  
		}  
		auto_ptr& operator= (auto_ptr_ref<T> rhs) throw() {  // new  
			 reset(rhs.yp);  
			 return *this;  
		}  
		template<class Y>  
		operator auto_ptr_ref<Y>() throw() {  
			return auto_ptr_ref<Y>(release());  
		}  
		template<class Y>  
		operator auto_ptr<Y>() throw() {  
			return auto_ptr<Y>(release());  
		}  
	};
}

#endif

namespace Common
{
	/**  类名：CSingleton
	  *  说明：单件类
	 **/
	template <class T>
	class CSingleton
	{
	public:
		// 获取单件
		static T& GetInstance();

	protected:
		// 构造
		CSingleton() {}
		// 析够
		virtual ~CSingleton() {}
	};

	/** @fn	    inline T& CSingleton<T>::GetInstance()
	 *  @brief	获取单件
	 *  @param	void
	 *  @return	T 返回单件
	 */
	template <class T>
	inline T& CSingleton<T>::GetInstance()
	{
        static std::auto_ptr<T> s_ptrInstance;
		static DSMutex m_mutexInstance;

		if (s_ptrInstance.get() == NULL)
		{
            // 避免创建两个
			DSMutexLock locker(&m_mutexInstance);
            // 多线程保护
			if (s_ptrInstance.get() == NULL)
			{
				s_ptrInstance = std::auto_ptr<T>(new T);
			}
		}

		return *s_ptrInstance.get();
	}
}

#endif // __COMMON_SINGLETON_H__

#endif
