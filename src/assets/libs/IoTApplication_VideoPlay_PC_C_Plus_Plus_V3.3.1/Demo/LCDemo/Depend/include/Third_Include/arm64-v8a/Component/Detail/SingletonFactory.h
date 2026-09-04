//
//  "$Id$"
//
//  Copyright (c)1992-2012, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//
//

#ifndef DAHUA_COMPONENT_DETAIL_SINGLETON_FACTORY_H__
#define DAHUA_COMPONENT_DETAIL_SINGLETON_FACTORY_H__

#include <stddef.h>		// for size_t
#include <Infra/Assert.h>
#include "../Defs.h"


namespace Dahua {
namespace Component {


class IUnknown;

namespace Detail {

////////////////////////////////////////////////////////////////////////////////


// T must be: no-throw default constructible and no-throw destructible
template <typename Tag, typename T>
class singleton_default
{
#if defined(_MSC_VER) && (_MSC_VER < 1300)
public:
#endif

	struct object_creator
	{
		// This constructor does nothing more than ensure that instance()
		//  is called before main() begins, thus creating the static
		//  T object before multithreading issues can come up.
		object_creator() { singleton_default<Tag, T>::instance(); }
		inline void do_nothing() const { }
	};

	static object_creator create_object;

	singleton_default();

public:

	typedef T object_type;

	// If, at any point (in user code), singleton_default<T>::instance()
	//  is called, then the following function is instantiated.
	static object_type & instance()
	{
		// This is the object that we return a reference to.
		// It is guaranteed to be created before main() begins because of
		//  the next line.
		static object_type obj;

		// The following line does nothing else than force the instantiation
		//  of singleton_default<T>::create_object, whose constructor is
		//  called before main() begins.
		create_object.do_nothing();

		return obj;
	}
};

template <typename Tag, typename T>
typename singleton_default<Tag, T>::object_creator
singleton_default<Tag, T>::create_object;


////////////////////////////////////////////////////////////////////////////////


/// 对象键值基类接口
struct key_base
{
	virtual ~key_base() {}
	virtual bool same_as(IUnknown* object) const = 0;
};

/// 对象键值泛型包装类
template<class T, class Key>
struct key_wrapper : public Detail::key_base
{
	Key key_;

	key_wrapper(Key key) : key_(key) {}

	bool same_as(IUnknown* object) const
	{
		DAHUA_ASSERT(dynamic_cast<T*>(object));
		return static_cast<T*>(object)->key() == key_;
	}
};


////////////////////////////////////////////////////////////////////////////////


/// 对象实例表管理类
class COMPONENT_API CObjectTable
{
public:
	CObjectTable();
	~CObjectTable();
	void lock();
	void unlock();
	IUnknown* find(key_base const& key) const;
	void insert(IUnknown* obj);
	void erase(IUnknown* obj);
	size_t count() const;
	IUnknown* get(size_t index) const;

private:
	struct ObjectTableInternal;
	ObjectTableInternal* m_internal;
};


} // namespace Detail
} // namespace Component
} // namespace Dahua

#endif // DAHUA_COMPONENT_DETAIL_SINGLETON_FACTORY_H__

