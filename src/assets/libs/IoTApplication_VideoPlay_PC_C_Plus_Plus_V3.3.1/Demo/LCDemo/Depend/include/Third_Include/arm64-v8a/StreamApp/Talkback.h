//
//  "$Id: Talkback.h 131664 2013-08-13 06:14:36Z hao_shiming $"
//
//  Copyright (c)1992-2012, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef __INCLUDE_DAHUA_STREAM_APP_TALKBACK_H__
#define __INCLUDE_DAHUA_STREAM_APP_TALKBACK_H__

#include "Component/Unknown.h"
#include "StreamApp/Defs.h"
#include "Stream/MediaFrame.h"

namespace Dahua{
namespace StreamApp{

class STREAMAPP_API ITalkback : public Component::IUnknown
{
public:
	// 对讲选项
	enum TalkBackOpt
	{
		SockStream = 0,     // 非加密对讲
		SSLSockStream,		// TLS 加密对讲
	};

	// 对讲客户端配置参数设置
	enum HttpTalkClientConfig
	{
		HttpTalkClientSendBuf = 0,		///> 发送缓存大小，单位字节
		HttpTalkClientRecvBuf,			///> 接收缓存大小，单位字节
		HttpTalkClientConfigNum,				
	};

	
	/// 组件工厂
	class IFactory : public Component::IFactoryUnknown
	{
	public:
		/// 获取组件实例
		virtual ITalkback* create() = 0;

		/// 组件接口ID定义
		static const char* iid() {return "Talkback";};
	};

	///码流回调函数原型
	typedef Infra::TFunction1< void, Stream::CMediaFrame const&> Proc;

	/// 析构函数
	virtual ~ITalkback(){};

	/// 关闭接口
	virtual bool close()
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 连接远端
	/// \param [in] remote_ip 远端ip
	/// \param [in] port 远端监听端口
	/// \param [in] option 配置选项, 见TalkBackOpt
	/// \return true 成功, false 失败
	virtual bool start(const char* remote_ip, int port, int option = 0)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 接收回调注册接口
	/// \param [in] proc 回调接口
	/// \return true 成功, false 失败
	virtual bool attach(Proc proc)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 发送接口
	/// \param [in] buffer 音频数据缓冲
	/// \param [in] size 缓冲大小
	/// \return true 成功, false 失败
	virtual bool put(const signed char* buffer, size_t size)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 设置用户信息
	/// \param [in] username 用户名信息
	/// \param [in] password  密码信息
	/// \return true 成功, false 失败
	virtual bool setAuthorization(const char *username, const char *password)
		COMPONENT_UNIMPLEMENTED_OPERATION
		
	///\brief 设置用户配置参数
	///\param [in]	name-配置名称
	///\param [in]	value-配置参数指针
	///\param [in]	len-配置参数指针所指区域的可访问长度
	/// \return true 成功, false 失败
	virtual bool setconfig(HttpTalkClientConfig name, const void *value, int len)
		COMPONENT_UNIMPLEMENTED_OPERATION
	
	DAHUA_COMPONENT_FUNCTION_REVSERVED(25)
};

/// 定义ITalkback智能指针
typedef Component::TComPtr<ITalkback> ITalkbackPtr;

}//StreamApp
}//Dahua

#endif //__INCLUDE_DAHUA_STREAM_APP_TALKBACK_H__

