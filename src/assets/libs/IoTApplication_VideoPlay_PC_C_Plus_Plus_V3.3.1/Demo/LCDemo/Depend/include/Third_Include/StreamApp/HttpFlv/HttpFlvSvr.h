#ifndef __INCLUDED_DAHUA_STREAMAPP_IHTTPFLVSVR_H__
#define __INCLUDED_DAHUA_STREAMAPP_IHTTPFLVSVR_H__

#include "Component/Unknown.h"
#include "Component/Defs.h"
#include "StreamApp/Defs.h"
#include "StreamApp/HttpFlv/HttpFlvUtil.h"


namespace Dahua{
namespace StreamApp{

///\brief HTTP-FLV服务组件
class STREAMAPP_API IHttpFlvSvr: public Component::IUnknown
{
public:
	/// 组件工厂
	class IFactory : public Component::IFactoryUnknown
	{
	public:
		// 取IHttpFlvSvr 对象实例
		virtual IHttpFlvSvr* instance() = 0;

		// 组件接口ID定义
		static const char* iid() {return "StreamApp.HttpFlvSvr";}
	};	
public:
	/// 析构函数
	virtual ~IHttpFlvSvr(){}

	///\brief 开启HTTP-FLV 服务
	///\param [in] port -开启服务的端口
	///\return true-ok, false-failed
	virtual bool startSvr(unsigned short port = 8082)
		COMPONENT_UNIMPLEMENTED_OPERATION

	///\brief 停止HTTP-FLV 服务
	///\param [in] force -是否强制断开所有会话
	///\return true-ok, false-failed
	virtual bool stopSvr(bool force = true)
		COMPONENT_UNIMPLEMENTED_OPERATION

	///\brief 设置HTTP-FLV 服务端的配置
	///\param [in] name -配置枚举
	///\param [in] value -配置值
	///\param [in] value -配置值的长度
	///\return true-ok, false-failed
	virtual bool setConfig(httpflv_svr_config_t name, void *value, int len)
		COMPONENT_UNIMPLEMENTED_OPERATION

	///\brief 获得HTTP-FLV 服务端的配置
	///\param [in] name -配置枚举
	///\param [in] value -配置值
	///\param [in] value -配置值的长度
	///\return true-ok, false-failed
	virtual bool getConfig(httpflv_svr_config_t name, void *value, int len)
		COMPONENT_UNIMPLEMENTED_OPERATION

	///\brief 开启HTTP-FLV 服务,支持开启非加密和加密服务
	///\param [in] type - 监听套接字类型
	///\param [in] port - 监听端口
	///\param [in] param 监听端口用到的配置, 目前只有TLS 监听端口用到
	///\		     config["Ssl"]["PemPath"]        	   = path(string)	根证书路径
	///\		     config["Ssl"]["KeyAlgorithm"]         = key(string)	根证书解密秘钥(如根证书未被加密, 则不需要该字段)
	///\return true-ok, false-failed
	virtual bool startServer(httpFlvSvrType type, unsigned short port = 8082, const Json::Value param = Json::Value())
		COMPONENT_UNIMPLEMENTED_OPERATION

	///\brief 停止HTTP-FLV 服务
	///\param [in] type - 监听套接字类型,关闭所有会话使用httpFlvSvrNoSock
	///\param [in] force -是否强制断开所有会话
	///\param [in] wait - 是否等待所有会话都销毁, 该参数只有在force 为true时才有效
	///\return true-ok, false-failed
	virtual bool stopServer(httpFlvSvrType type, bool force = true, bool wait = true)
		COMPONENT_UNIMPLEMENTED_OPERATION

	///\brief 停止HTTP-FLV服务的所有资源,进程退出时调用
	///\return true-ok, false-failed
	virtual bool destroyServer()
		COMPONENT_UNIMPLEMENTED_OPERATION
		
	DAHUA_COMPONENT_FUNCTION_REVSERVED(25)
};

typedef Component::TComPtr<IHttpFlvSvr> IHttpFlvSvrPtr;

}//namespace StreamApp
}//namespace Dahua

#endif //__INCLUDED_DAHUA_STREAMAPP_IHTTPFLVSVR_H__

