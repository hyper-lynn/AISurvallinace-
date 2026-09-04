//
//  "$Id: StreamApp.h 126042 2013-07-10 12:08:39Z shu_wang $"
//
//  Copyright (c)1992-2010, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//  Description:    
//  Revisions:      Year-Month-Day  SVN-Author  Modification
//                  2012-01-12        huang_xiaojin Create
//
#ifndef DAHUA_STREAMAPP_STREAMAPP_H
#define DAHUA_STREAMAPP_STREAMAPP_H

#include <Json/value.h>
#include <Component/Unknown.h>
#include <Stream/Defs.h>
#include "Defs.h"
#include "StreamSvr/Protocol/RtspUtil.h"
#include "NetFramework/Sock.h"
#include "Memory/SharedPtr.h"

namespace Dahua{
namespace StreamApp{

class STREAMAPP_API IStreamApp: public Component::IUnknown
{
public:
	/// 组件工厂
	class IFactory : public Component::IFactoryUnknown
	{
	public:
		/// 获取组件实例
		virtual IStreamApp* instance() = 0;

		/// 组件接口ID定义
		static const char* iid() {return "StreamApp";};
	};	
public:
	/// 析构函数
	virtual ~IStreamApp(){};
	
public:
//RtspSvr相关接口	
	//启动Rtsp服务器
	//参数：default_port 默认监听端口。有些定制化平台要求默认启动端口可定制。
	//返回值： >= 0 成功， < 0失败
	virtual int StartSvr( int default_port = 554 )
		COMPONENT_UNIMPLEMENTED_OPERATION
	
	//追加Url别名，可设置指定通道指定码流类型的url别名，需要'/'开头，如"/h264/0/1"
	//参数：channel 通道号（从1开始）， subtype 码流类型（主码流为0，辅码流1为1等等），url url路径名称， option 选项参数
	//返回值： >= 0 成功， < 0失败
	virtual int AddUrlAlias( int channel, int subtype, const char* url, long option = 0 )
		COMPONENT_UNIMPLEMENTED_OPERATION
	//验证请求是否为rtsp请求
	//参数：buf：请求缓冲，len：缓冲长度
	//返回值 0验证通过，-1验证未通过，-2缓冲区长度不够
	virtual int IsRtspRequest(const char * buf,int len)
		COMPONENT_UNIMPLEMENTED_OPERATION
	//添加新的连接
	//参数:sock:套接字句柄。buf:请求缓冲 len:缓冲长度 
	//返回值:-1:失败,0:成功
	virtual int AddNewConnect(int sock, const char * buf, int len )
		COMPONENT_UNIMPLEMENTED_OPERATION
	//添加新的连接
	//参数:sock:套接字句柄。buf:请求缓冲 len:缓冲长度 
	//option:连接配置，参见StreamSvr::RtspUtil.h中ReuseSessionOption
	//返回值:-1:失败,0:成功
	virtual int AddNewConnect(int sock, const char * buf, int len, StreamSvr::ReuseSessionOption* option)
		COMPONENT_UNIMPLEMENTED_OPERATION
	//获取统计信息
	//参数:statisticInfo:媒体传输统计信息	
	//返回值:-1:失败,0:成功
	virtual int GetStatisticInfo(Json::Value& statisticInfo)
		COMPONENT_UNIMPLEMENTED_OPERATION
	
	/// 获取实时码流的 URI
	virtual bool getStreamUri(int32_t channel, std::string& uri)
		COMPONENT_UNIMPLEMENTED_OPERATION
		
	/// 获取文件流的 URI
	/// \param [in] fileName 文件名
	/// \param [out] 返回此文件的 URI 路径
	virtual bool getStreamUriByFileName(const std::string& fileName, std::string& uri)
		COMPONENT_UNIMPLEMENTED_OPERATION
		
	/// 配置rtsp_server
	/// name 配置名称,参见StreamSvr::RtspUtil.h中rtsp_svr_config_t
	/// value 配置值
	virtual bool setConfig(StreamSvr::rtsp_svr_config_t name, void *value)
		COMPONENT_UNIMPLEMENTED_OPERATION
	//	设置延迟调试信息
	//	参数:argc：参数个数
	//	参数:argv：预警阈值等信息
	//  返回值:0:设置成功，非零:设置失败
	virtual int SetFrameStatParm(int argc, char **argv)
		COMPONENT_UNIMPLEMENTED_OPERATION
		
	///获取rtsp_server配置
	///\param [in]  name 配置名称,参见StreamSvr::RtspUtil.h中rtsp_svr_config_t
	///\param [in] value 配置值
	///\return 获取是否成功
	virtual bool getConfig(StreamSvr::rtsp_svr_config_t name, void *value)
		COMPONENT_UNIMPLEMENTED_OPERATION

	//停止Rtsp服务器, 其会关闭所有会话, 但是不会等待会话资源的销毁, 
	//后续推荐使用StopSvrEx 接口
	//参数：force: 是否强制关闭所有会话
	//返回值： >= 0 成功， < 0失败
	virtual int StopSvr(bool force = true)
		COMPONENT_UNIMPLEMENTED_OPERATION

	///\brief 启动SSL Rtsp 服务器
	///\param [in] pempath 证书文件的路径
	///\param [in] port 监听的端口号
	///\return  ： >= 0 成功， < 0失败
	virtual int StartSSLSvr(char *pempath, int port)
		COMPONENT_UNIMPLEMENTED_OPERATION

	///\brief 添加新的连接, 只要是以CSock 为基类的套接字都可以通过该接口添加
	///\param [in] newSock 新的连接套接字
	///\param [in] buf 请求缓冲
	///\param [in] len 缓冲长度 
	///\param [in] option 连接配置
	///\return  ： >= 0 成功， < 0失败
	virtual int AddNewConnect(Memory::TSharedPtr<NetFramework::CSock> &newSock, const char * buf, int len, StreamSvr::AddSessionOption* option)
		COMPONENT_UNIMPLEMENTED_OPERATION

	///\brief 停止SSL Rtsp 服务器
	///\param [in] force: 是否强制关闭所有会话
	///\return  ：true 成功， false 失败
	virtual bool StopSSLSvr(bool force = true)
		COMPONENT_UNIMPLEMENTED_OPERATION

	///\brief 关闭指定的会话, 该接口仅支持Closesessionid, 其他功能请使用StopSessionEx接口
	///\param [in] type:  关闭会话的依据类型, 见 CloseType
	///\param [in] value: 关闭会话依据的值
	///\param [in] reserve: 保留参数,暂未使用
	///\return  ：true 成功， false 失败
	virtual bool StopSession(int type, long value, void *reserve = NULL)
		COMPONENT_UNIMPLEMENTED_OPERATION

	///\brief 获取指定流源的引用计数
	///\param [in] config: 获取流源类型枚举定义
	///\param [in] inParam: 流源内容，char*指针
	///\param [out] outParam: 流源的引用计数值，long*指针
	///\return  ：true 成功， false 失败
	virtual bool GetStaticInfo(StreamSvr::rtsp_static_config_t config, void* inParam, void* outParam)
		COMPONENT_UNIMPLEMENTED_OPERATION

	///\brief 停止Rtsp服务器, 和StopSvr 相比, 新增一个参数等待所有会话都异步销毁后才返回
	///\param [in] force: 是否强制关闭所有会话
	///\param [in] wait: 是否等待所有会话都销毁, 该参数只有在force 为true时才有效
	///\return  ：true 成功， false 失败
	virtual bool StopSvrEx(bool force = true, bool wait = true)
		COMPONENT_UNIMPLEMENTED_OPERATION

	///\brief 关闭指定的会话
	///\param [in] type:  关闭会话的依据类型, 见 CloseType
	///\param [in] value: 关闭会话依据的值
	///\param [in] len: 值的长度
	///\return  ：true 成功， false 失败
	virtual bool StopSessionEx(int type, void *value, int len)
		COMPONENT_UNIMPLEMENTED_OPERATION

	///\brief 通过Json配置启动SSL Rtsp 服务器, 常见配置项如下
	///\         config["Ssl"]["Listen"]              = port(int)
	///\         config["Ssl"]["PemPath"]         = path(string)	
	///\         config["Ssl"]["KeyAlgorithm"] = key(string)
	///\param [in] config Tls Rtsp 服务的配置
	///\return  ： true 成功， false 失败
	virtual bool StartSSLSvr(const Json::Value& config)
		COMPONENT_UNIMPLEMENTED_OPERATION

	///\brief 启动Dhts Rtsp 服务器
	///\param [in] port 监听的端口号
	///\return  ： true 成功， false 失败
	virtual bool StartDhtsSvr(int port)
		COMPONENT_UNIMPLEMENTED_OPERATION
		
	///\brief 停止Dhts Rtsp 服务器
	///\param [in] force: 是否强制关闭所有会话
	///\return  ： >= 0 成功， < 0失败
	virtual bool StopDhtsSvr(bool force = true)
		COMPONENT_UNIMPLEMENTED_OPERATION
		
	DAHUA_COMPONENT_FUNCTION_REVSERVED(9)
};

}//namespace StreamApp
}//namespace Dahua
#endif //DAHUA_STREAMAPP_STREAMAPP_H
