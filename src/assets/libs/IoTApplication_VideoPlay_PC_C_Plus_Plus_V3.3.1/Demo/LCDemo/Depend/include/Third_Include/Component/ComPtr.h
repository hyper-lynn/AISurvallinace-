//
//  "$Id: ComPtr.h 23677 2011-04-18 07:37:15Z wang_haifeng $"
//
//  Copyright (c)1992-2011, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:	组件智能指针类
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef _COMPONENT_POINTER_H_
#define _COMPONENT_POINTER_H_


#include <stddef.h>
#include "Infra/Assert.h"
#include "Defs.h"
#include "Detail/Helper.h"

namespace Dahua {
namespace Component {

class IUnknown;
class IClient;

namespace Detail {

// 使用SFINAE规则管理重载决议
template<class T> struct enable_if_IUnknown {};
template<> struct enable_if_IUnknown<IUnknown> {typedef int type;};
template<class T> struct disable_if_IUnknown {typedef int type;};
template<> struct disable_if_IUnknown<IUnknown> {};

struct static_cast_tag {};
struct const_cast_tag {};
struct dynamic_cast_tag {};
struct polymorphic_cast_tag {};

} // namespace Detail


/// 管理组件指针的智能指针类模板
template<class T> class TComPtr
{
#if defined(_MSC_VER) && (_MSC_VER < 1300)
public:
#else
	template<class Y> friend class TComPtr;
#endif

	T* m_ptr;

	IClient* m_client;

	typedef TComPtr<T> this_type;

	class null_type;

public:
	typedef T	element_type;
	typedef T	value_type;
	typedef T*	pointer;

#if defined(_MSC_VER) && (_MSC_VER < 1300)

	/// 空构造函数; 实现从 NULL 到 TComPtr 的隐式转换
	TComPtr(int zero = NULL)
		: m_ptr(NULL), m_client(NULL)
	{
		DAHUA_ASSERT(zero == NULL);
	}

	/// 构造函数; 非IUnknown接口指针的构造函数
	template<class Y> explicit TComPtr(Y* ptr, IClient* client = NULL)
		: m_ptr(dynamic_cast<element_type*>(ptr)),m_client(client)
	{
	}

#else

	/// 空构造函数; 实现从 NULL 到 TComPtr 的隐式转换
	/// \param [in] ptr 当且仅当ptr为NULL时, 该构造函数才会被调用
	TComPtr(null_type* ptr = NULL)
		: m_ptr(NULL), m_client(NULL)
	{
	}

	/// 构造函数; 非IUnknown接口指针的构造函数
	template<class Y> explicit TComPtr(Y* ptr, IClient* client = NULL, typename Detail::disable_if_IUnknown<Y>::type = 0)
		: m_ptr(ptr), m_client(client)
	{
	}

	/// 构造函数; 实现从 IUnknown 接口指针构造对象
	template<class Y> explicit TComPtr(Y* ptr, IClient* client = NULL, typename Detail::enable_if_IUnknown<Y>::type = 0)
		: m_ptr(dynamic_cast<element_type*>(ptr)), m_client(client)
	{
	}

#endif

	template<class Y> TComPtr(TComPtr<Y> const& rhs)
		: m_ptr(rhs.m_ptr), m_client(rhs.m_client)
	{
		Detail::CComponentHelper::addRef(m_ptr);
		Detail::CComponentHelper::addRef((IUnknown*)m_client);
	}

	TComPtr(TComPtr const& rhs)
		: m_ptr(rhs.m_ptr), m_client(rhs.m_client)
	{
		Detail::CComponentHelper::addRef(m_ptr);
		Detail::CComponentHelper::addRef((IUnknown*)m_client);
	}

	template<class Y> TComPtr(TComPtr<Y> const& rhs, Detail::static_cast_tag)
		: m_ptr(static_cast<T*>(rhs.m_ptr)), m_client(rhs.m_client)
	{
		Detail::CComponentHelper::addRef(m_ptr);
		Detail::CComponentHelper::addRef((IUnknown*)m_client);
	}

	template<class Y> TComPtr(TComPtr<Y> const& rhs, Detail::const_cast_tag)
		: m_ptr(const_cast<T*>(rhs.m_ptr)), m_client(rhs.m_client)
	{
		Detail::CComponentHelper::addRef(m_ptr);
		Detail::CComponentHelper::addRef((IUnknown*)m_client);
	}

	template<class Y> TComPtr(TComPtr<Y> const& rhs, Detail::dynamic_cast_tag)
		: m_ptr(dynamic_cast<T*>(rhs.m_ptr)), m_client(rhs.m_client)
	{
		Detail::CComponentHelper::addRef(m_ptr);
		Detail::CComponentHelper::addRef((IUnknown*)m_client);
	}

	~TComPtr()
	{
		Detail::CComponentHelper::release(m_ptr);
		Detail::CComponentHelper::release((IUnknown*)m_client);
	}

	void swap(TComPtr& rhs)
	{
		if (&rhs != this)
		{
			element_type* p = rhs.m_ptr;
			rhs.m_ptr = m_ptr;
			m_ptr = p;

			IClient* pc = rhs.m_client;
			rhs.m_client = m_client;
			m_client = pc;
		}
	}

	void reset()
	{
		this_type().swap(*this);
	}

	template<class Y> void reset(Y* ptr)
	{
		this_type(ptr).swap(*this);
	}

	template<class Y> void reset(TComPtr<Y> const& rhs)
	{
		this_type(rhs).swap(*this);
	}

	TComPtr& operator=(TComPtr const& rhs)
	{
		if (&rhs != this) this_type(rhs).swap(*this);
		return *this;
	}

	element_type* operator->() const
	{
		Detail::CComponentHelper::setAsCurrentUser(m_client);
		DAHUA_ASSERT(m_ptr != NULL);
		return m_ptr;
	}

	element_type& operator*() const
	{
		Detail::CComponentHelper::setAsCurrentUser(m_client);
		DAHUA_ASSERT(m_ptr != NULL);
		return *m_ptr;
	}

	element_type* get() const
	{
		return m_ptr;
	}

	// implicit conversion to "bool"

	typedef T* this_type::*unspecified_bool_type;

	operator unspecified_bool_type() const // never throws
	{
		return m_ptr == NULL ? 0 : &this_type::m_ptr;
	}

	bool operator!() const // never throws
	{
		return m_ptr == NULL;
	}

	// client

	TComPtr<IClient> client() const
	{
		Detail::CComponentHelper::addRef((IUnknown*)m_client);
		return TComPtr<IClient>(m_client);
	}
};	// TComPtr

} // namespace Component

// 比较

template<class T, class U> inline bool operator==(Component::TComPtr<T> const& a, Component::TComPtr<U> const& b)
{
	return a.get() == b.get();
}

template<class T, class U> inline bool operator!=(Component::TComPtr<T> const& a, Component::TComPtr<U> const& b)
{
	return a.get() != b.get();
}

template<class T, class U> inline bool operator<(Component::TComPtr<T> const& a, Component::TComPtr<U> const& b)
{
	return a.get() < b.get();
}

template<class T, class U> inline bool operator<=(Component::TComPtr<T> const& a, Component::TComPtr<U> const& b)
{
	return a.get() <= b.get();
}

template<class T, class U> inline bool operator>(Component::TComPtr<T> const& a, Component::TComPtr<U> const& b)
{
	return a.get() > b.get();
}

template<class T, class U> inline bool operator>=(Component::TComPtr<T> const& a, Component::TComPtr<U> const& b)
{
	return a.get() >= b.get();
}

// 交换

template<class T> inline void swap(Component::TComPtr<T>& a, Component::TComPtr<T>& b)
{
	a.swap(b);
}

// 转型

template<class T, class U>  inline Component::TComPtr<T>   static_pointer_cast(Component::TComPtr<U> const& r)
{
	return Component::TComPtr<T>(r, Component::Detail::static_cast_tag());
}

template<class T, class U> inline Component::TComPtr<T>  const_pointer_cast(Component::TComPtr<U> const& r)
{
	return Component::TComPtr<T>(r, Component::Detail::const_cast_tag());
}

template<class T, class U> inline Component::TComPtr<T>  dynamic_pointer_cast(Component::TComPtr<U> const& r)
{
	return Component::TComPtr<T>(r, Component::Detail::dynamic_cast_tag());
}

// get_pointer(p) is a generic way to say p.get()

template<class T> inline T * get_pointer(Component::TComPtr<T> const & p)
{
	return p.get();
}

} // namespace Dahua

#endif // _COMPONENT_POINTER_H_

