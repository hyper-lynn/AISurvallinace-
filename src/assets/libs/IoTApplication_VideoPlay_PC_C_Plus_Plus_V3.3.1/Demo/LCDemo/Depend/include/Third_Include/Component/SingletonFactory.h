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

#ifndef DAHUA_COMPONENT_SINGLETON_FACTORY_H__
#define DAHUA_COMPONENT_SINGLETON_FACTORY_H__

#include <Infra/Assert.h>
#include "Detail/SingletonFactory.h"


namespace Dahua {
namespace Component {


class IUnknown;


////////////////////////////////////////////////////////////////////////////////

/// 组件单件工厂模板类
template <class Tag, class T, class Key>
class TSingletonFactory
{
public:
	typedef Tag tag;
	typedef T object_type;
	typedef Key key_type;
	typedef Detail::CObjectTable object_table;

private:
	struct singleton_tag {};
	typedef Detail::singleton_default<singleton_tag, object_table> singleton;

	TSingletonFactory();

public:
	/// 创建单件对象，如果 key 对应的对象已经创建，返回已存在的对象
	static object_type* create(key_type const& key)
	{
		object_table& table = singleton::instance();
		table.lock();

		// 查找已创建的实例
		IUnknown* obj = table.find(Detail::key_wrapper<object_type, key_type>(key));
		if (obj == NULL)
		{
			// 实例不存在, 则创建实例并插入对象表中
			obj = object_type::create(key);
			if (obj != NULL)
			{
				table.insert(obj);
			}
		}

		table.unlock();

		if (obj == NULL)
		{
			return NULL;
		}

		DAHUA_ASSERT(dynamic_cast<object_type*>(obj));
		return static_cast<object_type*>(obj);
	}

	/// 根据序号取已经创建的对象
	/// \param index 对象在列表中的序号，从0开始递增，取不到表示已经取完
	static object_type* get(int index)
	{
		object_table& table = singleton::instance();
		table.lock();

		IUnknown* obj = NULL;
		if ((size_t)index < table.count())
		{
			obj = table.get(index);
		}

		table.unlock();

		if (obj == NULL)
		{
			return NULL;
		}

		DAHUA_ASSERT(dynamic_cast<object_type*>(obj));
		return static_cast<object_type*>(obj);
	}

public:

	/// 取 key 值助手类，取所有 key 值的集合
	class Keys
	{
		Keys(Keys const&);
		Keys& operator=(Keys const&);

	public:
		/// 构造函数
		Keys() : m_keys(NULL), m_count(0)
		{
			object_table& table = singleton::instance();
			table.lock();

			size_t count = table.count();
			if (count > 0)
			{
				m_keys = new key_type[count];
				int i = 0;
				for (size_t index = 0; index < count; ++index)
				{
					IUnknown* obj = table.get(index);
					DAHUA_ASSERT(dynamic_cast<object_type*>(obj));
					m_keys[i++] = static_cast<object_type*>(obj)->key();
				}
				m_count = i;
			}

			table.unlock();
		}

		/// 析构函数
		~Keys()
		{
			delete[] m_keys;
		}

		/// key 值数量
		size_t count() const
		{
			return m_count;
		}

		/// 最 key 值
		key_type const& operator[](size_t index) const
		{
			DAHUA_ASSERT(index < m_count);
			return m_keys[index];
		}

	private:
		key_type* m_keys;
		size_t m_count;
	};
};


} // namespace Component
} // namespace Dahua

#endif // DAHUA_COMPONENT_SINGLETON_FACTORY_H__

