#ifndef __COMSELECTOR_SERVER_INFO_QUERYER_HELPER_H__
#define __COMSELECTOR_SERVER_INFO_QUERYER_HELPER_H__
#include "Component/Unknown.h"
#include "../ServerInfoQueryer.h"
namespace Dahua{
namespace Component{

class CServerInfoQueryerHelper
{
	
public:
	static CServerInfoQueryerHelper* instance();

	/// 设置查询句柄，组件选择器用此句柄查询通道和远程设备信息
	/// \param [in] queryerPtr 查询句柄智能指针
	bool setQueryerHandler(const IServerInfoQueryerPtr & queryerPtr);

	/// 根据通道号获取协议类型和ServerInfo
	/// \param [in]  channel 通道号
	/// \param [out] protocol 协议类型，如"Dahua2、Dahua3、Onvif等协议类型"
	/// \param [out] si ServerInfo信息，如果为模拟通道,ServerInfo为空
	/// \return false表示通道错误或者远程通道无效（未配置或Enable为false)
	///			true 表示返回成功（包括模拟通道ServerInfo为空）
	bool getServerInfoByChannel(int32_t channel, Infra::CString & protocol, Dahua::Component::ServerInfo &si);


	/// 根据DeviceID获取协议类型和ServerInfo
	/// \param [in]  deviceId
	/// \param [out] protocol 协议类型，如"Dahua2、Dahua3、Onvif等协议类型"
	/// \param [out] si ServerInfo信息，如果为模拟通道,ServerInfo为空
	/// \return false表示设备号错误（未配置或Enable为false)
	///			true 表示返回成功
	bool getServerInfoByDeviceId(const char* deviceId, Infra::CString & protocol, Dahua::Component::ServerInfo &si);

private:
     CServerInfoQueryerHelper();
	~CServerInfoQueryerHelper();
	IServerInfoQueryerPtr m_queryerPtr;
};

}
}

#endif//__COMSELECTOR_SERVER_INFO_QUERYER_HELPER_H__

