//
//  "$Id: Unknown.h 21790 2011-03-24 06:14:18Z wang_haifeng $"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef _COMPONENT_DETAIL_FACTORY_H_
#define _COMPONENT_DETAIL_FACTORY_H_

#include "Helper.h"
#include "../ComPtr.h"
#include "../Unknown.h"
namespace Dahua {
namespace Component {


class IUnknown;
class IClient;
struct ClassID;
struct ServerInfo;

namespace Detail {

////////////////////////////////////////////////////////////////////////////////

/// 获取组件工厂函数模板，仅供内部使用
template<class T>
	inline typename T::IFactory* getComponentFactory(ClassID const& clsid, ServerInfo const& si, IClient*& client)
{
	return dynamic_cast<typename T::IFactory*>(
		Detail::CComponentHelper::getComponentFactory(T::IFactory::iid(), clsid, si, client));
}

/// 获取组件工厂函数模板，仅供内部使用（通过UserID）
template<class T>
	inline typename T::IFactory* getComponentFactory(ClassID const& clsid, int uid, IClient*& client)
{
	return dynamic_cast<typename T::IFactory*>(
		Detail::CComponentHelper::getComponentFactory(T::IFactory::iid(), clsid, uid, client));
}

/// 生成对象智能指针函数模板，仅供内部使用
template<class T>
	inline TComPtr<T> makeComponentInstance(IUnknown* instance, IClient* client)
{
	IUnknown* inst = Detail::CComponentHelper::makeComponentInstance(instance);
	
	return TComPtr<T>(inst, client);
}

/// 生成对象智能指针函数模板，仅供内部使用
template<class T>
	inline TComPtr<T> makeComponentObject(IUnknown* object, IClient* client)
{
	IUnknown* obj = Detail::CComponentHelper::makeComponentObject(object);
	
	return TComPtr<T>(obj, client);
}

} // namespace Detail
} // namespace Component
} // namespace Dahua

#endif // _COMPONENT_DETAIL_FACTORY_H_


