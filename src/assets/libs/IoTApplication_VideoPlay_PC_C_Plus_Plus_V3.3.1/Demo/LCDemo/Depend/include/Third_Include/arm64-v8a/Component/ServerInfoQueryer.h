#ifndef __COMSELECTOR_SERVER_INFO_QUERYER_H__
#define __COMSELECTOR_SERVER_INFO_QUERYER_H__
#include "Unknown.h"

namespace Dahua{
namespace Component{

class IServerInfoQueryer: public Component::IUnknown
{
public:
	/// 组件工厂
	class IFactory : public Component::IFactoryUnknown
	{

	public:
		/// 获取组件选择器单件实例
		virtual IServerInfoQueryer* instance() = 0;

		/// 组件接口ID定义
		static char const* iid() {return "ComSelector::IServerInfoQueryer";}

	};
	
public:
	
	/// 根据通道获取协议类型和ServerInfo
	/// \param [in]  ch 通道号
	/// \param [out] protocol 协议类型，如"Dahua2、Dahua3、onvif等协议类型"
	/// \param [out] si ServerInfo信息，如果为模拟通道,ServerInfo为空
	/// \return false表示通道错误或者远程通道无效（未配置或Enable为false)
	///			true 表示返回成功（包括模拟通道ServerInfo为空）
	virtual bool getServerInfoByChannel(int ch, Infra::CString &protocol, Dahua::Component::ServerInfo &si)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 根据deviceId获取协议类型和ServerInfo
	/// \param [in] deviceId 设备ID
	/// \param [out] protocol 协议类型，如"Dahua2、Dahua3、onvif等协议类型"
	/// \param [out] si ServerInfo信息
	/// \return false 表示设备Id无效,true 表示返回成功 
	virtual bool getServerInfoByDevId(const char * deviceId, Infra::CString  &protocol, Dahua::Component::ServerInfo &si)
		COMPONENT_UNIMPLEMENTED_OPERATION
};

typedef Component::TComPtr<IServerInfoQueryer> IServerInfoQueryerPtr;
}
}

#endif

