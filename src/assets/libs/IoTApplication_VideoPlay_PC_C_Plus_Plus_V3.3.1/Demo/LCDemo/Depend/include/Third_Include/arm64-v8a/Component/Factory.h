//
//  "$Id: Unknown.h 21790 2011-03-24 06:14:18Z wang_haifeng $"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef _COMPONENT_FACTORY_H_
#define _COMPONENT_FACTORY_H_

#include "Defs.h"
#include "Unknown.h"
#include "Detail/Factory.h"


// 判断编译器是否完全支持默认参数重载识别

// VC6 编译器不设置参数的默认值
#if (defined(_MSC_VER) && (_MSC_VER < 1300))
#  define DAHUA_COMPILER_UNCOMPLETE_DEFAULT_ARGUMENT

// arm-linux-uclibc-gcc 3.4.3 也不支持, 这里只根据 GCC 版本识别
#elif (defined(__GNUC__) && (__GNUC__ == 3) && (__GNUC_MINOR__ == 4))
#  define DAHUA_COMPILER_UNCOMPLETE_DEFAULT_ARGUMENT

#endif

// 编译器不完全支持默认参数重载识别
#ifdef DAHUA_COMPILER_UNCOMPLETE_DEFAULT_ARGUMENT

#define DAHUA_DEFAULT_CLASS_ID
#define DAHUA_DEFAULT_SERVER_INFO

#else

#define DAHUA_DEFAULT_CLASS_ID		= ClassID::local
#define DAHUA_DEFAULT_SERVER_INFO	= ServerInfo::none

#endif

namespace Dahua {
namespace Component {


////////////////////////////////////////////////////////////////////////////////
//////////////////////  获取或创建组件

/// 获取组件创建时的参数范围
template<class T, class R>
inline bool getComponentCollect(
	R& result,
	ClassID const & clsid DAHUA_DEFAULT_CLASS_ID,
	ServerInfo const & si DAHUA_DEFAULT_SERVER_INFO)
{
	IClient* client = NULL;
	typename T::IFactory* cf = Detail::getComponentFactory<T>(clsid, si, client);

	bool ret =  cf ? cf->getCollect(result) : false;
	if (client)
	{
		Detail::CComponentHelper::release((IUnknown*)client);
	}
	return ret;
}


/// 获取组件单一实例，带四个组件构造参数
template<class T, class A1, class A2, class A3, class A4>
inline TComPtr<T> getComponentInstance(
	A1 const & a1,
	A2 const & a2,
	A3 const & a3,
	A4 const & a4,
	ClassID const & clsid DAHUA_DEFAULT_CLASS_ID,
	ServerInfo const & si DAHUA_DEFAULT_SERVER_INFO)
{
	IClient* client = NULL;
	typename T::IFactory* cf = Detail::getComponentFactory<T>(clsid, si, client);
	if (cf != NULL)
	{
		T* instance = cf->instance(a1, a2, a3, a4);
		return Detail::makeComponentInstance<T>(instance, client);
	}
	return NULL;
}


/// 获取组件单一实例，带三个组件构造参数
template<class T, class A1, class A2, class A3 >
inline TComPtr<T> getComponentInstance(
	A1 const & a1,
	A2 const & a2,
	A3 const & a3,
	ClassID const & clsid DAHUA_DEFAULT_CLASS_ID,
	ServerInfo const & si DAHUA_DEFAULT_SERVER_INFO)
{
	IClient* client = NULL;
	typename T::IFactory* cf = Detail::getComponentFactory<T>(clsid, si, client);
	if (cf != NULL)
	{
		T* instance = cf->instance(a1, a2, a3);
		return Detail::makeComponentInstance<T>(instance, client);
	}
	return NULL;
}


/// 获取组件单一实例，带两个组件构造参数
template<class T, class A1, class A2 >
inline TComPtr<T> getComponentInstance(
	A1 const & a1,
	A2 const & a2,
	ClassID const & clsid DAHUA_DEFAULT_CLASS_ID,
	ServerInfo const & si DAHUA_DEFAULT_SERVER_INFO)
{
	IClient* client = NULL;
	typename T::IFactory* cf = Detail::getComponentFactory<T>(clsid, si, client);
	if (cf != NULL)
	{
		T* instance = cf->instance(a1, a2);
		return Detail::makeComponentInstance<T>(instance, client);
	}

	return NULL;
}


/// 获取组件单一实例，带一个组件构造参数
template<class T, class A1>
inline TComPtr<T> getComponentInstance(
	A1 const & a1,
	ClassID const & clsid DAHUA_DEFAULT_CLASS_ID,
	ServerInfo const & si DAHUA_DEFAULT_SERVER_INFO)
{
	IClient* client = NULL;
	typename T::IFactory* cf = Detail::getComponentFactory<T>(clsid, si, client);
	if (cf != NULL)
	{
		T* instance = cf->instance(a1);
		return Detail::makeComponentInstance<T>(instance, client);
	}

	return NULL;
}



/// 获取组件单一实例，无组件构造参数
template<class T>
inline TComPtr<T> getComponentInstance(
	ClassID const & clsid = ClassID::local,
	ServerInfo const & si = ServerInfo::none)
{
	IClient* client = NULL;
	typename T::IFactory* cf = Detail::getComponentFactory<T>(clsid, si, client);
	if (cf != NULL)
	{
		T* instance = cf->instance();
		return Detail::makeComponentInstance<T>(instance, client);
	}

	return NULL;
}


/// 创建组件对象，带四个组件构造参数
template<class T, class A1, class A2, class A3, class A4>
inline TComPtr<T> createComponentObject(
	A1 const & a1,
	A2 const & a2,
	A3 const & a3,
	A4 const & a4,
	ClassID const & clsid DAHUA_DEFAULT_CLASS_ID,
	ServerInfo const & si DAHUA_DEFAULT_SERVER_INFO)
{
	IClient* client = NULL;
	typename T::IFactory* cf = Detail::getComponentFactory<T>(clsid, si, client);
	if (cf != NULL)
	{
		T* object = cf->create(a1, a2, a3, a4);
		return Detail::makeComponentObject<T>(object, client);
	}

	return NULL;
}


/// 创建组件对象，带三个组件构造参数
template<class T, class A1, class A2, class A3 >
inline TComPtr<T> createComponentObject(
	A1 const & a1,
	A2 const & a2,
	A3 const & a3,
	ClassID const & clsid DAHUA_DEFAULT_CLASS_ID,
	ServerInfo const & si DAHUA_DEFAULT_SERVER_INFO)
{
	IClient* client = NULL;
	typename T::IFactory* cf = Detail::getComponentFactory<T>(clsid, si, client);
	if (cf != NULL)
	{
		T* object = cf->create(a1, a2, a3);
		return Detail::makeComponentObject<T>(object, client);
	}

	return NULL;
}


/// 创建组件对象，带两个组件构造参数
template<class T, class A1, class A2 >
inline TComPtr<T> createComponentObject(
	A1 const & a1,
	A2 const & a2,
	ClassID const & clsid DAHUA_DEFAULT_CLASS_ID,
	ServerInfo const & si DAHUA_DEFAULT_SERVER_INFO)
{
	IClient* client = NULL;
	typename T::IFactory* cf = Detail::getComponentFactory<T>(clsid, si, client);
	if (cf != NULL)
	{
		T* object = cf->create(a1, a2);
		return Detail::makeComponentObject<T>(object, client);
	}

	return NULL;
}


/// 创建组件对象，带一个组件构造参数
template<class T, class A1>
inline TComPtr<T> createComponentObject(
	A1 const & a1,
	ClassID const & clsid DAHUA_DEFAULT_CLASS_ID,
	ServerInfo const & si DAHUA_DEFAULT_SERVER_INFO)
{
	IClient* client = NULL;
	typename T::IFactory* cf = Detail::getComponentFactory<T>(clsid, si, client);
	if (cf != NULL)
	{
		T* object = cf->create(a1);
		return Detail::makeComponentObject<T>(object, client);
	}

	return NULL;
}


/// 创建组件对象，无组件构造参数
template<class T>
inline TComPtr<T> createComponentObject(
	ClassID const & clsid = ClassID::local,
	ServerInfo const & si = ServerInfo::none)
{
	IClient* client = NULL;
	typename T::IFactory* cf = Detail::getComponentFactory<T>(clsid, si, client);
	if (cf != NULL)
	{
		T* object = cf->create();
		return Detail::makeComponentObject<T>(object, client);
	}

	return NULL;
}

/// 获取组件单一实例，带四个组件构造参数（通过UserID）
template<class T, class A1, class A2, class A3, class A4>
inline TComPtr<T> getComponentInstance(
	A1 const & a1,
	A2 const & a2,
	A3 const & a3,
	A4 const & a4,
	ClassID const & clsid,
	int uid)
{
	IClient* client = NULL;
	typename T::IFactory* cf = Detail::getComponentFactory<T>(clsid, uid, client);
	if (cf != NULL)
	{
		T* instance = cf->instance(a1, a2, a3, a4);
		return Detail::makeComponentInstance<T>(instance, client);
	}
	return NULL;
}


/// 获取组件单一实例，带三个组件构造参数（通过UserID）
template<class T, class A1, class A2, class A3 >
inline TComPtr<T> getComponentInstance(
	A1 const & a1,
	A2 const & a2,
	A3 const & a3,
	ClassID const & clsid,
	int uid)
{
	IClient* client = NULL;
	typename T::IFactory* cf = Detail::getComponentFactory<T>(clsid, uid, client);
	if (cf != NULL)
	{
		T* instance = cf->instance(a1, a2, a3);
		return Detail::makeComponentInstance<T>(instance, client);
	}
	return NULL;
}


/// 获取组件单一实例，带两个组件构造参数（通过UserID）
template<class T, class A1, class A2 >
inline TComPtr<T> getComponentInstance(
	A1 const & a1,
	A2 const & a2,
	ClassID const & clsid,
	int uid)
{
	IClient* client = NULL;
	typename T::IFactory* cf = Detail::getComponentFactory<T>(clsid, uid, client);
	if (cf != NULL)
	{
		T* instance = cf->instance(a1, a2);
		return Detail::makeComponentInstance<T>(instance, client);
	}

	return NULL;
}


/// 获取组件单一实例，带一个组件构造参数（通过UserID）
template<class T, class A1>
inline TComPtr<T> getComponentInstance(
	A1 const & a1,
	ClassID const & clsid,
	int uid)
{
	IClient* client = NULL;
	typename T::IFactory* cf = Detail::getComponentFactory<T>(clsid, uid, client);
	if (cf != NULL)
	{
		T* instance = cf->instance(a1);
		return Detail::makeComponentInstance<T>(instance, client);
	}

	return NULL;
}



/// 获取组件单一实例，无组件构造参数（通过UserID）
template<class T>
inline TComPtr<T> getComponentInstance(
	ClassID const & clsid,
	int uid)
{
	IClient* client = NULL;
	typename T::IFactory* cf = Detail::getComponentFactory<T>(clsid, uid, client);
	if (cf != NULL)
	{
		T* instance = cf->instance();
		return Detail::makeComponentInstance<T>(instance, client);
	}

	return NULL;
}


/// 创建组件对象，带四个组件构造参数（通过UserID）
template<class T, class A1, class A2, class A3, class A4>
inline TComPtr<T> createComponentObject(
	A1 const & a1,
	A2 const & a2,
	A3 const & a3,
	A4 const & a4,
	ClassID const & clsid,
	int uid)
{
	IClient* client = NULL;
	typename T::IFactory* cf = Detail::getComponentFactory<T>(clsid, uid, client);
	if (cf != NULL)
	{
		T* object = cf->create(a1, a2, a3, a4);
		return Detail::makeComponentObject<T>(object, client);
	}

	return NULL;
}


/// 创建组件对象，带三个组件构造参数（通过UserID）
template<class T, class A1, class A2, class A3 >
inline TComPtr<T> createComponentObject(
	A1 const & a1,
	A2 const & a2,
	A3 const & a3,
	ClassID const & clsid,
	int uid)
{
	IClient* client = NULL;
	typename T::IFactory* cf = Detail::getComponentFactory<T>(clsid, uid, client);
	if (cf != NULL)
	{
		T* object = cf->create(a1, a2, a3);
		return Detail::makeComponentObject<T>(object, client);
	}

	return NULL;
}


/// 创建组件对象，带两个组件构造参数（通过UserID）
template<class T, class A1, class A2 >
inline TComPtr<T> createComponentObject(
	A1 const & a1,
	A2 const & a2,
	ClassID const & clsid,
	int uid)
{
	IClient* client = NULL;
	typename T::IFactory* cf = Detail::getComponentFactory<T>(clsid, uid, client);
	if (cf != NULL)
	{
		T* object = cf->create(a1, a2);
		return Detail::makeComponentObject<T>(object, client);
	}

	return NULL;
}


/// 创建组件对象，带一个组件构造参数（通过UserID）
template<class T, class A1>
inline TComPtr<T> createComponentObject(
	A1 const & a1,
	ClassID const & clsid,
	int uid)
{
	IClient* client = NULL;
	typename T::IFactory* cf = Detail::getComponentFactory<T>(clsid, uid, client);
	if (cf != NULL)
	{
		T* object = cf->create(a1);
		return Detail::makeComponentObject<T>(object, client);
	}

	return NULL;
}


/// 创建组件对象，无组件构造参数（通过UserID）
template<class T>
inline TComPtr<T> createComponentObject(
	ClassID const & clsid,
	int uid)
{
	IClient* client = NULL;
	typename T::IFactory* cf = Detail::getComponentFactory<T>(clsid, uid, client);
	if (cf != NULL)
	{
		T* object = cf->create();
		return Detail::makeComponentObject<T>(object, client);
	}

	return NULL;
}

////////////////////////////////////////////////////////////////////////////////
// 以下接口是为兼容原组件接口而保留, 请不要使用，原有的将逐渐替换

/// 组件创建函数原型定义
typedef IUnknown* (*ComponentCreator)(const ServerInfo* server);

///  注册组件创建和销毁函数，在静态链接时使用。
///  \param iid 组件接口ID
///  \param creator 创建函数，由各个组件提供。
///  \note 如果是动态连接，创建函数的导出符号必须为固定为
/// 		"create$(iid)Object"，$(iid)表示组件接口ID
COMPONENT_API bool registerComponent(const char* iid, ComponentCreator creator);

/// 获取组件单一实例，如果不存在就创建之
/// \param iid 组件接口ID
/// \param server 远程服务器信息，本地组件需填NULL
COMPONENT_API IUnknown* getComponentInstance(const char* iid, const ServerInfo* server = NULL);

/// 创建组件新实例
/// \param iid 组件接口ID
/// \param server 远程服务器信息，本地组件需填NULL
COMPONENT_API IUnknown* createComponentObject(const char* iid, const ServerInfo* server = NULL);

} // namespace Component
} // namespace Dahua

#endif // _COMPONENT_FACTORY_H_


