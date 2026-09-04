#ifndef __INCLUDED_DAHUA_STREAMAPP_IHTTPDHSVR_H__
#define __INCLUDED_DAHUA_STREAMAPP_IHTTPDHSVR_H__

#include "Json/value.h"
#include "Component/Unknown.h"
#include "Component/Defs.h"
#include "StreamApp/Defs.h"
#include "StreamApp/HttpDh/HttpDhUtil.h"
#include "NetFramework/Sock.h"
#include "Memory/SharedPtr.h"

namespace Dahua{
namespace StreamApp{


///\brief HTTP-DH服务组件
class STREAMAPP_API IHttpDhSvr: public Component::IUnknown
{
public:
	/// 组件工厂
	class IFactory : public Component::IFactoryUnknown
	{
	public:
		// 取IHttpDhSvr 对象实例
		virtual IHttpDhSvr* instance() = 0;

		// 组件接口ID定义
		static const char* iid() {return "StreamApp::HttpDhSvr";}
	};
		
protected:

	/// 析构函数
	virtual ~IHttpDhSvr(){}

public:

	///\brief  开启HTTP-DH服务
	///\param  [in] port-开启服务的端口
	///\return true-ok, false-failed
	virtual bool startSvr(unsigned short port = 8086)
		COMPONENT_UNIMPLEMENTED_OPERATION

	///\brief 停止HTTP-DH 服务
	///\param [in] force-是否强制断开所有会话
	///\return true-ok, false-failed
	virtual bool stopSvr(bool force = true)
		COMPONENT_UNIMPLEMENTED_OPERATION

	///\brief 设置HTTP-DH服务端的配置
	///\param [in] name-配置枚举
	///\param [in] value-配置值
	///\param [in] value-配置值的长度
	///\return true-ok, false-failed
	virtual bool setConfig(httpDhServerConfig name, void *value, int len)
		COMPONENT_UNIMPLEMENTED_OPERATION

	///\brief 获得HTTP-DH服务端的配置
	///\param [in] name-配置枚举
	///\param [in] value-配置值
	///\return true-ok, false-failed
	virtual bool getConfig(httpDhServerConfig name, void *value)
		COMPONENT_UNIMPLEMENTED_OPERATION

	///\brief 添加新的连接, 只要是以CSock为基类的套接字都可以通过该接口添加
	///\param [in] newSock 新的连接套接字
	///\param [in] buf 请求缓冲
	///\param [in] len 缓冲长度 
	///\param [in] option 连接配置
	///\return true-ok, false-failed
	virtual bool addNewConnect(Memory::TSharedPtr<NetFramework::CSock> &newSock, const char * buf, int len, AddDhSessionOption* option)
		COMPONENT_UNIMPLEMENTED_OPERATION

	///\brief 开启HTTP-DH服务,可以选择监听端口类型或者不开启端口监听
	///\param [in] type 监听套接字类型
	///\param [in] port  监听端口
	///\param [in] param 监听端口用到的配置, 目前只有TLS 监听端口用到
	///\		     config["Ssl"]["PemPath"]        	   = path(string)	根证书路径
	///\		     config["Ssl"]["KeyAlgorithm"]         = key(string)	根证书解密秘钥(如根证书未被加密, 则不需要该字段)
	///\return true-ok, false-failed
	virtual bool startServer(httpDhServerType type, unsigned short port = 8086, const Json::Value param = Json::Value())
		COMPONENT_UNIMPLEMENTED_OPERATION

	///\brief 判断缓存数据是否是HttpPrivate请求
	///\param [in] buf-缓存数据, 必须包含"\r\n\r\n"分界符
	///\param [in] len-缓存数据长度
	///\return true-是HttpPrivate请求, false-不是HttpPrivate请求
	virtual bool isHttpPrivateRequest(const char *buf, int len)
		COMPONENT_UNIMPLEMENTED_OPERATION

	///\brief HTTPDH服务端端组件保留虚接口扩展数量,每增加一个必须减1
	DAHUA_COMPONENT_FUNCTION_REVSERVED(25)
};

typedef Component::TComPtr<IHttpDhSvr> IHttpDhSvrPtr;

}//namespace StreamApp
}//namespace Dahua

#endif //__INCLUDED_DAHUA_STREAMAPP_IHTTPFLVSVR_H__

