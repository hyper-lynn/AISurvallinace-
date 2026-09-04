//
//  "$Id$"
//
//  Copyright (c)1992-2011, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef _COMPONENT_DETAIL_HELPER_H_
#define _COMPONENT_DETAIL_HELPER_H_

#include "../Defs.h"

namespace Dahua {
namespace Component {


class IUnknown;
class IFactoryUnknown;
class IClient;
struct ClassID;
struct ServerInfo;

namespace Detail {


////////////////////////////////////////////////////////////////////////////////

/// 组件对象助手类，仅供内部使用
class CComponentHelper
{
public:
	/// 获取组件工厂，仅供内部使用
	COMPONENT_API static IFactoryUnknown* getComponentFactory(
		const char* iid, ClassID const & clsid, ServerInfo const & si, IClient* & client);

	/// 获取组件工厂，仅供内部使用（通过UserID）
	COMPONENT_API static IFactoryUnknown* getComponentFactory(
		const char* iid, ClassID const & clsid, int uid, IClient* & client);

	/// 处理引用计数, 生成对象指针, for getComponentInstance
	COMPONENT_API static IUnknown* makeComponentInstance(IUnknown*);

	/// 处理引用计数, 生成对象指针, for createComponentObject
	COMPONENT_API static IUnknown* makeComponentObject(IUnknown*);

	/// 增加引用计数，仅供内部使用
	COMPONENT_API static int addRef(IUnknown*);

	/// 减少引用计数，仅供内部使用
	COMPONENT_API static int release(IUnknown*);

	/// 设置client为当前线程用户，仅供内部使用
	COMPONENT_API static bool setAsCurrentUser(IClient* client);
};


} // namespace Detail
} // namespace Component
} // namespace Dahua

#endif // _COMPONENT_DETAIL_HELPER_H_


