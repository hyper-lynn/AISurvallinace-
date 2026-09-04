#ifndef __COMSELECTOR_COMPONENTSELECTOR_H__
#define __COMSELECTOR_COMPONENTSELECTOR_H__
#include "Defs.h"
#include "Infra/String.h"
#include "ServerInfoQueryer.h"
#include "LocalComSelectManager.h"
#include "Detail/ServerInfoQueryerHelper.h"
#include "Infra/PrintLog.h"

namespace Dahua{
namespace Component{

//32位系统下64字节
struct COMPONENT_API ComSelChannelInfo
{
	int32_t channel;                //通道号,大于等于0才有效
	int32_t userid;         //模拟通道 可指定client，用于组件实例进行获取当前local的client使用，数字通道不能指定
	const char* subClassID; //子id,传入空指针表示无效
	/// 为同时兼容32位和64位, 使用以下计算方法预留保留位数, 增加指针和整数时修改相应的乘数
	int8_t resv2[sizeof(void*)*16 -sizeof(int32_t)  - sizeof(int8_t) * 4 - sizeof(char*) ];
	static const ComSelChannelInfo local;
	ComSelChannelInfo()
	:channel(-1)
	,userid(-1)
	,subClassID(NULL)
	{
	
	}

	explicit ComSelChannelInfo(int32_t ch, const char* subClsId, int uid = -1)
	{
		channel = ch;
		subClassID = subClsId;
		userid = uid;
	}
};

//32位系统下64字节
struct COMPONENT_API ComSelDeviceIdInfo
{
	const char* deviceID;      //远程设备被分配的ID,传入空指针表示无效
	const char* subClassID; //子id,传入空指针表示无效
	int8_t resv[sizeof(void*)*16 - sizeof(char*) * 2 ];
	ComSelDeviceIdInfo()
	:deviceID(NULL)
	,subClassID(NULL)
	{

	}
};


/// 设置查询接口，用此句柄查询通道和远程ServerInfo
/// \param [in] queryerPtr 查询句柄智能指针
COMPONENT_API bool setQueryerHandler(IServerInfoQueryerPtr queryerPtr);

COMPONENT_API Dahua::Infra::CString  getClassId(Infra::CString &protocolClassId, Infra::CString &subClassId);

/// 设置某个业务组件本地组件服务默认classid
template<class T> bool setLocalDefaultComponent(const char* clsid)
{
	return CLocalComSelectManager::setDefaultComponent(T::IFactory::iid(),clsid);
}

/// 获取组件单一实例，带三个组件构造参数
/// 没有设置过查询接口或者传入的参数为默认本地组件参数，获取到的是Local组件
/// \param [in] 
///	info.channel 小于0表示无效，-1为默认的无效通道ID
///	info.subClassID 传入空指针，表示无效
template<class T, class A1, class A2, class A3>
inline Dahua::Component::TComPtr<T> getComponentInstance(
	A1 const & a1,
	A2 const & a2,
	A3 const & a3,
	ComSelChannelInfo const& info )
	{
		Infra::CString  subClassID;
		Infra::CString  protocolClassId;
		Infra::CString newClassId;
		Component::ServerInfo si = {0,};
		
		if(NULL == CServerInfoQueryerHelper::instance())
		{
			Infra::logError("getComponentInstance--->get instance fail!!!\r\n");
			return NULL;
		}
		
		if(!CServerInfoQueryerHelper::instance()->getServerInfoByChannel(info.channel, protocolClassId, si))
		{
			Infra::logError("getComponentInstance--->getServerInfoByChannel fail! !channel= %d.\r\n", info.channel);
			return NULL;
		}
		
		//传入了有效的subClassID
		if(NULL != info.subClassID)
		{
			subClassID = info.subClassID;
		}
		
		ComSelChannelInfo const& localref=ComSelChannelInfo::local;
		// protocolClassId = "Local"或者传入的是默认的本地参数，则表示本地通道
		if((0 == protocolClassId.compare("Local"))
			|| (&localref == &info))
		{
			Infra::CString defaultclassId = CLocalComSelectManager::getDefaultClassID(T::IFactory::iid());
			newClassId = getClassId(defaultclassId, subClassID);
			TComPtr<T> tempPtr = Component::getComponentInstance<T>(a1,a2, a3,Component::ClassID(newClassId.c_str()), Component::ServerInfo::none);
			// 自定义的client
			if(info.userid != -1 && tempPtr.get())
			{
				// 获取到自定义的client
				IClientPtr clientPtr =  getComponentInstance<IClient>(info.userid, ClassID("Local"),Component::ServerInfo::none);
				// client 加引用计数
				Detail::CComponentHelper::addRef((Component::IUnknown*)clientPtr.get());
				Detail::CComponentHelper::addRef((Component::IUnknown*)tempPtr.get());
				// 重新组成新的client的智能指针
				return TComPtr<T>(tempPtr.get(), clientPtr.get());
			}
			return tempPtr;
			
		}
		
		newClassId = getClassId(protocolClassId, subClassID);
		return Component::getComponentInstance<T>(a1,a2, a3,Component::ClassID(newClassId.c_str()), si);
	}

/// 获取组件单一实例，带二个组件构造参数
/// 没有设置过查询接口或者传入的参数为默认本地组件参数，获取到的是Local组件
/// \param [in] 
///	info.channel 小于0表示无效，-1为默认的无效通道ID
///	info.subClassID 传入空指针，表示无效
template<class T, class A1, class A2>
inline Dahua::Component::TComPtr<T> getComponentInstance(
	A1 const & a1,
	A2 const & a2,
	ComSelChannelInfo const& info )
	{
		Infra::CString subClassID;
		Infra::CString  protocolClassId;
		Infra::CString newClassId;
		Component::ServerInfo si = {0,};
		
		if(NULL == CServerInfoQueryerHelper::instance())
		{
			Infra::logError("getComponentInstance--->get instance fail!!!\r\n");
			return NULL;
		}
		
		if(!CServerInfoQueryerHelper::instance()->getServerInfoByChannel(info.channel, protocolClassId, si))
		{
			Infra::logError("getComponentInstance--->getServerInfoByChannel fail! !channel= %d.\r\n", info.channel);
			return NULL;
		}
		
		//传入了有效的subClassID
		if(NULL != info.subClassID)
		{
			subClassID = info.subClassID;
		}
		
		ComSelChannelInfo const& localref=ComSelChannelInfo::local;
		// protocolClassId = "Local"或者传入的是默认的本地参数，则表示本地通道
		if((0 == protocolClassId.compare("Local"))
			|| (&localref == &info))
		{	
			Infra::CString defaultclassId = CLocalComSelectManager::getDefaultClassID(T::IFactory::iid());
			newClassId = getClassId(defaultclassId, subClassID);
			TComPtr<T> tempPtr = Component::getComponentInstance<T>(a1,a2, Component::ClassID(newClassId.c_str()), Component::ServerInfo::none);
			
			//有自定义的client
			if(info.userid != -1)
			{
				// 获取到自定义的client
				IClientPtr clientPtr =  getComponentInstance<IClient>(info.userid, ClassID("Local"),Component::ServerInfo::none);
				// client 加引用计数
				Detail::CComponentHelper::addRef((Component::IUnknown*)clientPtr.get());
				Detail::CComponentHelper::addRef((Component::IUnknown*)tempPtr.get());
				// 重新组成新的client的智能指针
				return TComPtr<T>(tempPtr.get(), clientPtr.get());

			}
			return tempPtr;
		}
		
		newClassId = getClassId(protocolClassId, subClassID);
		return Component::getComponentInstance<T>(a1,a2,Component::ClassID(newClassId.c_str()), si);
	}

/// 获取组件单一实例，带一个组件构造参数
/// 没有设置过查询接口或者传入的参数为默认本地组件参数，获取到的是Local组件
/// \param [in] 
///	info.channel 小于0表示无效，-1为默认的无效通道ID
///	info.subClassID 传入空指针，表示无效
template<class T, class A1>
inline Dahua::Component::TComPtr<T> getComponentInstance(
	A1 const & a1,
	ComSelChannelInfo const& info )
	{
		Infra::CString subClassID;
		Infra::CString  protocolClassId;
		Infra::CString newClassId;
		Component::ServerInfo si = {0,};

		if(NULL == CServerInfoQueryerHelper::instance())
		{
			Infra::logError("getComponentInstance--->get instance fail!!!\r\n");
			return NULL;
		}
		
		if(!CServerInfoQueryerHelper::instance()->getServerInfoByChannel(info.channel, protocolClassId, si))
		{
			Infra::logError("getComponentInstance--->getServerInfoByChannel fail! !channel= %d.\r\n", info.channel);
			return NULL;
		}
		
		//传入了有效的subClassID
		if(NULL != info.subClassID)
		{
			subClassID = info.subClassID;
		}
		
		ComSelChannelInfo const& localref=ComSelChannelInfo::local;
		// protocolClassId = "Local"或者传入的是默认的本地参数，则表示本地通道
		if((0 == protocolClassId.compare("Local"))
			|| (&localref == &info))
		{	
			Infra::CString defaultclassId = CLocalComSelectManager::getDefaultClassID(T::IFactory::iid());
			newClassId = getClassId(defaultclassId, subClassID);
			TComPtr<T> tempPtr = Component::getComponentInstance<T>(a1,Component::ClassID(newClassId.c_str()), Component::ServerInfo::none);
			//有自定义的client
			if(info.userid != -1)
			{
				// 获取到自定义的client
				IClientPtr clientPtr =  getComponentInstance<IClient>(info.userid, ClassID("Local"),Component::ServerInfo::none);
				// client 加引用计数
				Detail::CComponentHelper::addRef((Component::IUnknown*)clientPtr.get());
				Detail::CComponentHelper::addRef((Component::IUnknown*)tempPtr.get());
				// 重新组成新的client的智能指针
				return TComPtr<T>(tempPtr.get(), clientPtr.get());

			}
			return tempPtr;
		}
		
		newClassId = getClassId(protocolClassId, subClassID);
		return Component::getComponentInstance<T>(a1,Component::ClassID(newClassId.c_str()), si);
	}

/// 获取组件单一实例，无组件构造参数
/// 没有设置过查询接口或者传入的参数为默认本地组件参数，获取到的是Local组件
/// \param [in] 
///	info.channel 小于0表示无效，-1为默认的无效通道ID
///	info.subClassID 传入空指针，表示无效
template<class T>
inline Component::TComPtr<T> getComponentInstance(
	ComSelChannelInfo const& info )
	{
		Infra::CString subClassID;
		Infra::CString  protocolClassId;
		Infra::CString newClassId;
		Component::ServerInfo si = {0,};
		
		if(NULL == CServerInfoQueryerHelper::instance())
		{
			Infra::logError("getComponentInstance--->get instance fail!!!\r\n");
			return NULL;
		}
		
		if(!CServerInfoQueryerHelper::instance()->getServerInfoByChannel(info.channel, protocolClassId, si))
		{
			Infra::logError("getComponentInstance--->getServerInfoByChannel fail! !channel= %d.\r\n", info.channel);
			return NULL;
		}
		
		//传入了有效的subClassID
		if(NULL != info.subClassID)
		{
			subClassID = info.subClassID;
		}
		
		ComSelChannelInfo const& localref=ComSelChannelInfo::local;
		// protocolClassId = "Local"或者传入的是默认的本地参数，则表示本地通道
		if((0 == protocolClassId.compare("Local"))
			|| (&localref == &info))
		{	
			Infra::CString defaultclassId = CLocalComSelectManager::getDefaultClassID(T::IFactory::iid());
			newClassId = getClassId(defaultclassId, subClassID);
			TComPtr<T> tempPtr = Component::getComponentInstance<T>(Component::ClassID(newClassId.c_str()), Component::ServerInfo::none);
			// 自定义的client
			if(info.userid != -1 && tempPtr.get())
			{
				// 获取到自定义的client
				IClientPtr clientPtr =  getComponentInstance<IClient>(info.userid, ClassID("Local"),Component::ServerInfo::none);
				// client 加引用计数
				Detail::CComponentHelper::addRef((Component::IUnknown*)clientPtr.get());
				Detail::CComponentHelper::addRef((Component::IUnknown*)tempPtr.get());
				// 重新组成新的client的智能指针
				return TComPtr<T>(tempPtr.get(), clientPtr.get());

			}
			return tempPtr;
		}
		
		newClassId = getClassId(protocolClassId, subClassID);
		return Component::getComponentInstance<T>(Component::ClassID(newClassId.c_str()), si);
	}
	
/// 创建组件对象，带三个组件构造参数
/// 没有设置过查询接口或者传入的参数为默认本地组件参数，创建的是Local组件
/// \param [in] 
///	info.channel 小于0表示无效，-1为默认的无效通道ID
///	info.subClassID 传入空指针，表示无效
template<class T, class A1, class A2, class A3>
inline Component::TComPtr<T> createComponentObject(
	A1 const & a1,
	A2 const & a2,
	A3 const & a3,
	ComSelChannelInfo const& info )
	{
		Infra::CString subClassID;
		Infra::CString  protocolClassId;
		Infra::CString newClassId;
		Component::ServerInfo si = {0,};
		
		if(NULL == CServerInfoQueryerHelper::instance())
		{
			Infra::logError("createComponentObject--->get instance fail!!!\r\n");
			return NULL;
		}
		
		if(!CServerInfoQueryerHelper::instance()->getServerInfoByChannel(info.channel, protocolClassId, si))
		{
			Infra::logError("getComponentInstance--->getServerInfoByChannel fail! !channel= %d.\r\n", info.channel);
			return NULL;
		}
		
		//传入了有效的subClassID
		if(NULL != info.subClassID)
		{
			subClassID = info.subClassID;
		}
		
		ComSelChannelInfo const& localref=ComSelChannelInfo::local;
		// protocolClassId = "Local"或者传入的是默认的本地参数，则表示本地通道
		if((0 == protocolClassId.compare("Local"))
			|| (&localref == &info))
		{	
			Infra::CString defaultclassId = CLocalComSelectManager::getDefaultClassID(T::IFactory::iid());
			newClassId = getClassId(defaultclassId, subClassID);
			TComPtr<T> tempPtr =  Component::createComponentObject<T>(a1,a2, a3,Component::ClassID(newClassId.c_str()), Component::ServerInfo::none);
			// 自定义的client
			if(info.userid != -1 && tempPtr.get())
			{
				// 获取到自定义的client
				IClientPtr clientPtr =  getComponentInstance<IClient>(info.userid, ClassID("Local"),Component::ServerInfo::none);
				// client 加引用计数
				Detail::CComponentHelper::addRef((Component::IUnknown*)clientPtr.get());
				Detail::CComponentHelper::addRef((Component::IUnknown*)tempPtr.get());
				// 重新组成新的client的智能指针
				return TComPtr<T>(tempPtr.get(), clientPtr.get());

			}
			return tempPtr;
		}
		
		newClassId = getClassId(protocolClassId, subClassID);
		return Component::createComponentObject<T>(a1,a2, a3,Component::ClassID(newClassId.c_str()), si);
	}

/// 创建组件对象，带二个组件构造参数
/// 没有设置过查询接口或者传入的参数为默认本地组件参数，创建的是Local组件
/// \param [in] 
///	info.channel 小于0表示无效，-1为默认的无效通道ID
///	info.subClassID 传入空指针，表示无效
template<class T, class A1, class A2>
inline Component::TComPtr<T> createComponentObject(
	A1 const & a1,
	A2 const & a2,
	ComSelChannelInfo const& info)
	{
		Infra::CString subClassID;
		Infra::CString protocolClassId;
		Infra::CString newClassId;
		Component::ServerInfo si = {0,};
		
		if(NULL == CServerInfoQueryerHelper::instance())
		{
			Infra::logError("createComponentObject--->get instance fail!!!\r\n");
			return NULL;
		}
		
		if(!CServerInfoQueryerHelper::instance()->getServerInfoByChannel(info.channel, protocolClassId, si))
		{
			Infra::logError("createComponentObject--->getServerInfoByChannel fail! !channel= %d.\r\n", info.channel);
			return NULL;
		}
		
		//传入了有效的subClassID
		if(NULL != info.subClassID)
		{
			subClassID = info.subClassID;
		}
		
		ComSelChannelInfo const& localref=ComSelChannelInfo::local;
		// protocolClassId = "Local"或者传入的是默认的本地参数，则表示本地通道
		if((0 == protocolClassId.compare("Local"))
			|| (&localref == &info))
		{	
			Infra::CString defaultclassId = CLocalComSelectManager::getDefaultClassID(T::IFactory::iid());
			newClassId = getClassId(defaultclassId, subClassID);
			TComPtr<T> tempPtr =  Component::createComponentObject<T>(a1,a2,Component::ClassID(newClassId.c_str()), Component::ServerInfo::none);
			// 自定义的client
			if(info.userid != -1 && tempPtr.get())
			{
				// 获取到自定义的client
				IClientPtr clientPtr =  getComponentInstance<IClient>(info.userid, ClassID("Local"),Component::ServerInfo::none);
				// client 加引用计数
				Detail::CComponentHelper::addRef((Component::IUnknown*)clientPtr.get());
				Detail::CComponentHelper::addRef((Component::IUnknown*)tempPtr.get());
				// 重新组成新的client的智能指针
				return TComPtr<T>(tempPtr.get(), clientPtr.get());

			}
			return tempPtr;
		}
		
		newClassId = getClassId(protocolClassId, subClassID);
		return Component::createComponentObject<T>(a1,a2,Component::ClassID(newClassId.c_str()), si);
	}

/// 创建组件对象，带一个组件构造参数
/// 没有设置过查询接口或者传入的参数为默认本地组件参数，创建的是Local组件
/// \param [in] 
///	info.channel 小于0表示无效，-1为默认的无效通道ID
///	info.subClassID 传入空指针，表示无效
template<class T, class A1>
inline Component::TComPtr<T> createComponentObject(
	A1 const & a1,
	ComSelChannelInfo const& info )
	{
		Infra::CString subClassID;
		Infra::CString  protocolClassId;
		Infra::CString newClassId;
		Component::ServerInfo si = {0,};
		
		if(NULL == CServerInfoQueryerHelper::instance())
		{
			Infra::logError("createComponentObject--->get instance fail!!!\r\n");
			return NULL;
		}
		
		if(!CServerInfoQueryerHelper::instance()->getServerInfoByChannel(info.channel, protocolClassId, si))
		{
			Infra::logError("createComponentObject--->getServerInfoByChannel fail! !channel= %d.\r\n", info.channel);
			return NULL;
		}
		
		//传入了有效的subClassID
		if(NULL != info.subClassID)
		{
			subClassID = info.subClassID;
		}
		
		ComSelChannelInfo const& localref=ComSelChannelInfo::local;
		// protocolClassId = "Local"或者传入的是默认的本地参数，则表示本地通道
		if((0 == protocolClassId.compare("Local"))
			|| (&localref == &info))
		{	
			Infra::CString defaultclassId = CLocalComSelectManager::getDefaultClassID(T::IFactory::iid());
			newClassId = getClassId(defaultclassId, subClassID);
			TComPtr<T> tempPtr = Component::createComponentObject<T>(a1,Component::ClassID(newClassId.c_str()), Component::ServerInfo::none);
			// 自定义的client
			if(info.userid != -1 && tempPtr.get())
			{
				// 获取到自定义的client
				IClientPtr clientPtr =  getComponentInstance<IClient>(info.userid, ClassID("Local"),Component::ServerInfo::none);
				// client 加引用计数
				Detail::CComponentHelper::addRef((Component::IUnknown*)clientPtr.get());
				Detail::CComponentHelper::addRef((Component::IUnknown*)tempPtr.get());
				// 重新组成新的client的智能指针
				return TComPtr<T>(tempPtr.get(), clientPtr.get());

			}
			return tempPtr;
		}
		
		newClassId = getClassId(protocolClassId, subClassID);
		return Component::createComponentObject<T>(a1,Component::ClassID(newClassId.c_str()), si);
	}

/// 创建组件对象，无组件构造参数
/// 没有设置过查询接口或者传入的参数为默认本地组件参数，创建的是Local组件
/// \param [in] 
///	info.channel 小于0表示无效，-1为默认的无效通道ID
///	info.subClassID 传入空指针，表示无效
template<class T>
inline Component::TComPtr<T> createComponentObject(
	ComSelChannelInfo const& info )
	{
		Infra::CString subClassID;
		Infra::CString  protocolClassId;
		Infra::CString newClassId;
		Component::ServerInfo si = {0,};
		
		if(NULL == CServerInfoQueryerHelper::instance())
		{
			Infra::logError("createComponentObject--->get instance fail!!!\r\n");
			return NULL;
		}
		
		if(!CServerInfoQueryerHelper::instance()->getServerInfoByChannel(info.channel, protocolClassId, si))
		{
			Infra::logError("createComponentObject--->getServerInfoByChannel fail! !channel= %d.\r\n", info.channel);
			return NULL;
		}
		
		//传入了有效的subClassID
		if(NULL != info.subClassID)
		{
			subClassID = info.subClassID;
		}
		
		ComSelChannelInfo const& localref=ComSelChannelInfo::local;
		// protocolClassId = "Local"或者传入的是默认的本地参数，则表示本地通道
		if((0 == protocolClassId.compare("Local"))
			|| (&localref == &info))
		{	
			Infra::CString defaultclassId = CLocalComSelectManager::getDefaultClassID(T::IFactory::iid());
			newClassId = getClassId(defaultclassId, subClassID);
			TComPtr<T> tempPtr = Component::createComponentObject<T>(Component::ClassID(newClassId.c_str()), Component::ServerInfo::none);
			// 自定义的client
			if(info.userid != -1 && tempPtr.get())
			{
				// 获取到自定义的client
				IClientPtr clientPtr =  getComponentInstance<IClient>(info.userid, ClassID("Local"),Component::ServerInfo::none);
				// client 加引用计数
				Detail::CComponentHelper::addRef((Component::IUnknown*)clientPtr.get());
				Detail::CComponentHelper::addRef((Component::IUnknown*)tempPtr.get());
				// 重新组成新的client的智能指针
				return TComPtr<T>(tempPtr.get(), clientPtr.get());

			}
			return tempPtr;
		}
		
		newClassId = getClassId(protocolClassId, subClassID);
		return Component::createComponentObject<T>(Component::ClassID(newClassId.c_str()), si);
	}

/// 获取组件创建时的参数范围
/// \param [in] 
///	info.channel 小于0表示无效，-1为默认的无效通道ID
///	info.subClassID 传入空指针，表示无效
template<class T, class R>
inline bool getComponentCollect(
	R& result,
	ComSelChannelInfo const& info )
	{
		Infra::CString subClassID;
		Infra::CString  protocolClassId;
		Infra::CString newClassId;
		Component::ServerInfo si = {0,};
		
		if(NULL == CServerInfoQueryerHelper::instance())
		{
			Infra::logError("getComponentCollect--->get instance fail!!!\r\n");
			return false;
		}
		
		if(!CServerInfoQueryerHelper::instance()->getServerInfoByChannel(info.channel, protocolClassId, si))
		{
			Infra::logError("getComponentCollect--->getServerInfoByChannel fail! !channel= %d.\r\n", info.channel);
			return false;
		}
		
		//传入了有效的subClassID
		if(NULL != info.subClassID)
		{
			subClassID = info.subClassID;
		}
		
		ComSelChannelInfo const& localref=ComSelChannelInfo::local;
		// protocolClassId = "Local"或者传入的是默认的本地参数，则表示本地通道
		if((0 == protocolClassId.compare("Local"))
			|| (&localref == &info))
		{	
			Infra::CString defaultclassId = CLocalComSelectManager::getDefaultClassID(T::IFactory::iid());
			newClassId = getClassId(defaultclassId, subClassID);
			return  Component::getComponentCollect<T>(result,Component::ClassID(newClassId.c_str()), Component::ServerInfo::none);
		}
		
		newClassId = getClassId(protocolClassId, subClassID);
		return  Component::getComponentCollect<T>(result,Component::ClassID(newClassId.c_str()), si);
	}


/// 获取组件单一实例，带三个组件构造参数
/// 通过deviceId获取远程组件，必须先调用setQueryerHandler接口设置查询句柄
/// \param [in] 
///	info.deviceID   远程设备被分配的ID,传入空指针表示无效
///	info.subClassID 传入空指针，表示无效
template<class T, class A1, class A2, class A3>
inline Dahua::Component::TComPtr<T> getComponentInstance(
	A1 const & a1,
	A2 const & a2,
	A3 const & a3,
	ComSelDeviceIdInfo const& deviceIdInfo )
	{
		Infra::CString subClassID;
		Infra::CString  protocolClassId;
		Infra::CString newClassId;
		Component::ServerInfo si = {0,};
		
		if(NULL == CServerInfoQueryerHelper::instance())
		{
			Infra::logError("getComponentInstance--->get instance fail!!!\r\n");
			return NULL;
		}
		
		if(!CServerInfoQueryerHelper::instance()->getServerInfoByDeviceId(deviceIdInfo.deviceID, protocolClassId, si))
		{
			Infra::logError("getComponentInstance--->getServerInfoByDeviceId fail! !deviceID= %s.\r\n", deviceIdInfo.deviceID);
			return NULL;
		}
		
		//传入了有效的subClassID
		if(NULL != deviceIdInfo.subClassID)
		{
			subClassID = deviceIdInfo.subClassID;
		}
		
		newClassId = getClassId(protocolClassId, subClassID);
		return Component::getComponentInstance<T>(a1,a2, a3,Component::ClassID(newClassId.c_str()), si);
	}

/// 获取组件单一实例，带二个组件构造参数
/// 通过deviceId获取远程组件，必须先调用setQueryerHandler接口设置查询句柄
/// \param [in] 
///	info.deviceID   远程设备被分配的ID,传入空指针表示无效
///	info.subClassID 传入空指针，表示无效
template<class T, class A1, class A2>
inline Dahua::Component::TComPtr<T> getComponentInstance(
	A1 const & a1,
	A2 const & a2,
	ComSelDeviceIdInfo const& deviceIdInfo)
	{
		Infra::CString subClassID;
		Infra::CString  protocolClassId;
		Infra::CString newClassId;
		Component::ServerInfo si = {0,};
		
		if(NULL == CServerInfoQueryerHelper::instance())
		{
			Infra::logError("getComponentInstance--->get instance fail!!!\r\n");
			return NULL;
		}
		
		if(!CServerInfoQueryerHelper::instance()->getServerInfoByDeviceId(deviceIdInfo.deviceID, protocolClassId, si))
		{
			Infra::logError("getComponentInstance--->getServerInfoByDeviceId fail! !deviceID= %s.\r\n", deviceIdInfo.deviceID);
			return NULL;
		}
		
		//传入了有效的subClassID
		if(NULL != deviceIdInfo.subClassID)
		{
			subClassID = deviceIdInfo.subClassID;
		}
				
		newClassId = getClassId(protocolClassId, subClassID);
		return Component::getComponentInstance<T>(a1,a2,Component::ClassID(newClassId.c_str()), si);
	}

/// 获取组件单一实例，带一个组件构造参数
/// 通过deviceId获取远程组件，必须先调用setQueryerHandler接口设置查询句柄
/// \param [in] 
///	info.deviceID   远程设备被分配的ID,传入空指针表示无效
///	info.subClassID 传入空指针，表示无效
template<class T, class A1>
inline Dahua::Component::TComPtr<T> getComponentInstance(
	A1 const & a1,
	ComSelDeviceIdInfo const& deviceIdInfo)
	{
		Infra::CString subClassID;
		Infra::CString  protocolClassId;
		Infra::CString newClassId;
		Component::ServerInfo si = {0,};

		if(NULL == CServerInfoQueryerHelper::instance())
		{
			Infra::logError("getComponentInstance--->get instance fail!!!\r\n");
			return NULL;
		}
		
		if(!CServerInfoQueryerHelper::instance()->getServerInfoByDeviceId(deviceIdInfo.deviceID, protocolClassId, si))
		{
			Infra::logError("getComponentInstance--->getServerInfoByDeviceId fail! !deviceID= %s.\r\n", deviceIdInfo.deviceID);
			return NULL;
		}
		
		//传入了有效的subClassID
		if(NULL != deviceIdInfo.subClassID)
		{
			subClassID = deviceIdInfo.subClassID;
		}
				
		newClassId = getClassId(protocolClassId, subClassID);
		return Component::getComponentInstance<T>(a1,Component::ClassID(newClassId.c_str()), si);
	}

/// 获取组件单一实例，无组件构造参数
/// 通过deviceId获取远程组件，必须先调用setQueryerHandler接口设置查询句柄
/// \param [in] 
///	info.deviceID   远程设备被分配的ID,传入空指针表示无效
///	info.subClassID 传入空指针，表示无效
template<class T>
inline Component::TComPtr<T> getComponentInstance(
	ComSelDeviceIdInfo const& deviceIdInfo)
	{
		Infra::CString subClassID;
		Infra::CString  protocolClassId;
		Infra::CString newClassId;
		Component::ServerInfo si = {0,};
		
		if(NULL == CServerInfoQueryerHelper::instance())
		{
			Infra::logError("getComponentInstance--->get instance fail!!!\r\n");
			return NULL;
		}
		
		if(!CServerInfoQueryerHelper::instance()->getServerInfoByDeviceId(deviceIdInfo.deviceID, protocolClassId, si))
		{
			Infra::logError("getComponentInstance--->getServerInfoByDeviceId fail! !deviceID= %s.\r\n", deviceIdInfo.deviceID);
			return NULL;
		}
		
		//传入了有效的subClassID
		if(NULL != deviceIdInfo.subClassID)
		{
			subClassID = deviceIdInfo.subClassID;
		}
		
		newClassId = getClassId(protocolClassId, subClassID);		
		return Component::getComponentInstance<T>(Component::ClassID(newClassId.c_str()), si);
	}
	
/// 创建组件对象，带三个组件构造参数
/// 通过deviceId获取远程组件，必须先调用setQueryerHandler接口设置查询句柄
/// \param [in] 
///	info.deviceID   远程设备被分配的ID,传入空指针表示无效
///	info.subClassID 传入空指针，表示无效
template<class T, class A1, class A2, class A3>
inline Component::TComPtr<T> createComponentObject(
	A1 const & a1,
	A2 const & a2,
	A3 const & a3,
	ComSelDeviceIdInfo const& deviceIdInfo)
	{
		Infra::CString subClassID;
		Infra::CString  protocolClassId;
		Infra::CString newClassId;
		Component::ServerInfo si = {0,};
		
		if(NULL == CServerInfoQueryerHelper::instance())
		{
			Infra::logError("createComponentObject--->get instance fail!!!\r\n");
			return NULL;
		}
		
		if(!CServerInfoQueryerHelper::instance()->getServerInfoByDeviceId(deviceIdInfo.deviceID, protocolClassId, si))
		{
			Infra::logError("createComponentObject--->getServerInfoByDeviceId fail! !deviceID= %s.\r\n", deviceIdInfo.deviceID);
			return NULL;
		}
		
		//传入了有效的subClassID
		if(NULL != deviceIdInfo.subClassID)
		{
			subClassID = deviceIdInfo.subClassID;
		}
				
		newClassId = getClassId(protocolClassId, subClassID);
		return Component::createComponentObject<T>(a1,a2, a3,Component::ClassID(newClassId.c_str()), si);
	}

/// 创建组件对象，带二个组件构造参数
/// 通过deviceId获取远程组件，必须先调用setQueryerHandler接口设置查询句柄
/// \param [in] 
///	info.deviceID   远程设备被分配的ID,传入空指针表示无效
///	info.subClassID 传入空指针，表示无效
template<class T, class A1, class A2>
inline Component::TComPtr<T> createComponentObject(
	A1 const & a1,
	A2 const & a2,
	ComSelDeviceIdInfo const& deviceIdInfo)
	{
		Infra::CString subClassID;
		Infra::CString  protocolClassId;
		Infra::CString newClassId;
		Component::ServerInfo si = {0,};
		
		if(NULL == CServerInfoQueryerHelper::instance())
		{
			Infra::logError("createComponentObject--->get instance fail!!!\r\n");
			return NULL;
		}
		
		if(!CServerInfoQueryerHelper::instance()->getServerInfoByDeviceId(deviceIdInfo.deviceID, protocolClassId, si))
		{
			Infra::logError("createComponentObject--->getServerInfoByDeviceId fail! !deviceID= %s.\r\n", deviceIdInfo.deviceID);
			return NULL;
		}
		
		//传入了有效的subClassID
		if(NULL != deviceIdInfo.subClassID)
		{
			subClassID = deviceIdInfo.subClassID;
		}
				
		newClassId = getClassId(protocolClassId, subClassID);
		return Component::createComponentObject<T>(a1,a2,Component::ClassID(newClassId.c_str()), si);
	}

/// 创建组件对象，带一个组件构造参数
/// 通过deviceId获取远程组件，必须先调用setQueryerHandler接口设置查询句柄
/// \param [in] 
///	info.deviceID   远程设备被分配的ID,传入空指针表示无效
///	info.subClassID 传入空指针，表示无效
template<class T, class A1>
inline Component::TComPtr<T> createComponentObject(
	A1 const & a1,
	ComSelDeviceIdInfo const& deviceIdInfo)
	{
		Infra::CString subClassID;
		Infra::CString  protocolClassId;
		Infra::CString newClassId;
		Component::ServerInfo si = {0,};
		
		if(NULL == CServerInfoQueryerHelper::instance())
		{
			Infra::logError("createComponentObject--->get instance fail!!!\r\n");
			return NULL;
		}
		
		if(!CServerInfoQueryerHelper::instance()->getServerInfoByDeviceId(deviceIdInfo.deviceID, protocolClassId, si))
		{
			Infra::logError("createComponentObject--->getServerInfoByDeviceId fail! !deviceID= %s.\r\n", deviceIdInfo.deviceID);
			return NULL;
		}
		
		//传入了有效的subClassID
		if(NULL != deviceIdInfo.subClassID)
		{
			subClassID = deviceIdInfo.subClassID;
		}
				
		newClassId = getClassId(protocolClassId, subClassID);
		return Component::createComponentObject<T>(a1,Component::ClassID(newClassId.c_str()), si);
	}

/// 创建组件对象，不带组件构造参数
/// 通过deviceId获取远程组件，必须先调用setQueryerHandler接口设置查询句柄
/// \param [in] 
///	info.deviceID   远程设备被分配的ID,传入空指针表示无效
///	info.subClassID 传入空指针，表示无效
template<class T>
inline Component::TComPtr<T> createComponentObject(
	ComSelDeviceIdInfo const& deviceIdInfo)
	{
		Infra::CString subClassID;
		Infra::CString  protocolClassId;
		Infra::CString newClassId;
		Component::ServerInfo si = {0,};
		
		if(NULL == CServerInfoQueryerHelper::instance())
		{
			Infra::logError("createComponentObject--->get instance fail!!!\r\n");
			return NULL;
		}
		
		if(!CServerInfoQueryerHelper::instance()->getServerInfoByDeviceId(deviceIdInfo.deviceID, protocolClassId, si))
		{
			Infra::logError("createComponentObject--->getServerInfoByDeviceId fail! !deviceID= %s.\r\n", deviceIdInfo.deviceID);
			return NULL;
		}
		
		//传入了有效的subClassID
		if(NULL != deviceIdInfo.subClassID)
		{
			subClassID = deviceIdInfo.subClassID;
		}
				
		newClassId = getClassId(protocolClassId, subClassID);
		return Component::createComponentObject<T>(Component::ClassID(newClassId.c_str()), si);
	}

/// 获取组件创建时的参数范围
/// 必须先调用setQueryerHandler接口设置查询句柄
/// \param [in] 
///	info.deviceID   远程设备被分配的ID,传入空指针表示无效
///	info.subClassID 传入空指针，表示无效
template<class T, class R>
inline bool getComponentCollect(
	R& result,
	ComSelDeviceIdInfo const& deviceIdInfo)
	{
		Infra::CString subClassID;
		Infra::CString  protocolClassId;
		Infra::CString newClassId;
		Component::ServerInfo si = {0,};
		
		if(NULL == CServerInfoQueryerHelper::instance())
		{
			Infra::logError("getComponentCollect--->get instance fail!!!\r\n");
			return false;
		}
		
		if(!CServerInfoQueryerHelper::instance()->getServerInfoByDeviceId(deviceIdInfo.deviceID, protocolClassId, si))
		{
			Infra::logError("getComponentCollect--->getServerInfoByDeviceId fail! !deviceID= %s.\r\n", deviceIdInfo.deviceID);
			return false;
		}
		
		//传入了有效的subClassID
		if(NULL != deviceIdInfo.subClassID)
		{
			subClassID = deviceIdInfo.subClassID;
		}
		
		newClassId = getClassId(protocolClassId, subClassID);
		return Component::getComponentCollect<T>(result,Component::ClassID(newClassId.c_str()), si);
	}


}
}

#endif
