#ifndef __INCLUDED_DAHUA_STREAMAPP_IHTTPSTREAMCLIENT_H__
#define __INCLUDED_DAHUA_STREAMAPP_IHTTPSTREAMCLIENT_H__

#include "Component/Unknown.h"
#include "Component/Defs.h"
#include "StreamApp/Defs.h"
#include "StreamApp/HttpDh/HttpDhUtil.h"
#include "NetFramework/Sock.h"
#include "Memory/SharedPtr.h"
#include "StreamApp/SdpMaker.h"

namespace Dahua{
namespace StreamApp{


/*---------------------------------------------------------------------------------------------------------
								拉流客户端接口调用的流程如下
			Dahua::Component::createComponentObject<Dahua::StreamApp::IHttpStreamClient>();
											    |			
									IHttpStreamClient::setConfig
	(在初始化之前必须设置中HttpdhclientConfigSetServerInfo, HttpdhclientConfigAuthorization, HttpdhclientConfigDataProc)
											    |			                  
									IHttpStreamClient::init  
											    |
								    IHttpStreamClient::close
        (handle_message函数中收到MSG_HTTPDH_FAIL消息后或者init失败, 或者上层主动停止拉流调用)    
---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------
								语音对讲和可视对讲客户端接口调用的流程如下
			Dahua::Component::createComponentObject<Dahua::StreamApp::IHttpStreamClient>();
											    |			
									IHttpStreamClient::setConfig
	(在初始化之前必须设置中HttpdhclientConfigSetServerInfo, HttpdhclientConfigAuthorization, HttpdhclientConfigDataProc)
											    |
									IHttpStreamClient::initStreamMode
												|
									IHttpStreamClient::initSdp
												|
									IHttpStreamClient::init
												|
									IHttpStreamClient::enableMedia(可视对讲调用)
												|
									IHttpStreamClient::put_frame
		(客户端收到MSG_HTTPDH_READY消息回调后开始推送手机到设备的正向对讲音频帧)
											    |
									IHttpStreamClient::disableMedia(可视对讲调用)
												|
								    IHttpStreamClient::close
        (handle_message函数中收到MSG_HTTPDH_FAIL消息后或者init失败, 或者上层主动停止语音对讲调用)    
---------------------------------------------------------------------------------------------------------*/


///\brief HTTPDH拉流客户端服务组件
class STREAMAPP_API IHttpStreamClient: public Component::IUnknown
{
public:
	/// 组件工厂
	class IFactory : public Component::IFactoryUnknown
	{
	public:
		// 取IHttpStreamClient 对象实例
		virtual IHttpStreamClient* create() = 0;

		// 组件接口ID定义
		static const char* iid() {return "StreamApp::HttpStreamClient";}
	};
	

protected:
	/// 析构函数
	virtual ~IHttpStreamClient(){}
	
public:
	///\brief 初始化客户端 (由流媒体创建连接)
	///\param [in] httpUrl-GET 请求后面的url
	///\param [in] ownerID-网络框架分配的ID号 
	///\param [in] socktype-连接的套接字类型, 目前只支持SOCK_TYPE_STREAM类型
	///\param [in] msgCallBack-消息回调
	///\param [in] param-套接字需要的参数路径
	///\return -1-fail,	0-success
	virtual int init(const char *httpUrl, long ownerID, NetFramework::CSock::SOCKET_TYPE socktype, HttpMsgCallBack msgCallBack = HttpMsgCallBack(), void *param = NULL)
		COMPONENT_UNIMPLEMENTED_OPERATION_RETURN_INT

	///\brief 初始化客户端（复用已经建立的连接）
	///\param [in] httpUrl-GET 请求后面的url
	///\param [in] ownerID-网络框架分配的ID号 
	///\param [in] sock-已连接上的套接字
	///\param [in] msgCallBack-套接字需要的一些参数指针
	///\param [in] needClose-是否由流媒体关闭newSock 所带的套接字句柄, true-关闭 false-不关闭
	///\return -1-fail,	0-success
	virtual int init(const char *httpUrl, long ownerID, Memory::TSharedPtr<NetFramework::CSock> &sock, HttpMsgCallBack msgCallBack = HttpMsgCallBack(), bool needClose = true)
		COMPONENT_UNIMPLEMENTED_OPERATION_RETURN_INT

	///\brief 设置客户端配置选项
	///\param [in] name-工作选项,参考@see httpDhClientConfig
	///\param [in] value-选项参数指针
	///\param [in] len-选项参数指针所指区域的可访问长度
	///\return -1-fail,	0-success
	virtual int setConfig(httpDhClientConfig name, void *value, int len)
		COMPONENT_UNIMPLEMENTED_OPERATION_RETURN_INT

	///\brief 客户端获取配置参数,暂不支持
	///\param [in] name-配置名称,参考@see httpDhClientConfig
	///\param [in] value-配置的值
	///\return 0-ok, -1-failed
	virtual int getConfig(httpDhClientConfig name, void *value, int len)
		COMPONENT_UNIMPLEMENTED_OPERATION_RETURN_INT

	///\brief 关闭客户端
	///\return -1-fail,	0-success
	virtual int close()
		COMPONENT_UNIMPLEMENTED_OPERATION_RETURN_INT

	///\brief 暂停媒体
	///\return -1-fail,	0-success
	virtual int pause()
		COMPONENT_UNIMPLEMENTED_OPERATION_RETURN_INT

	///\brief 客户端再次请求播放, 主要用于回放, 主要用于跳转, 暂停后的继续播放等操作
	///\param [in] info-时间范围
	///\return -1-fail,	0-success
	virtual int play(const httpDhRangeInfo &info)
		COMPONENT_UNIMPLEMENTED_OPERATION_RETURN_INT

	///\brief 获取客户端盐值信息
	///\param [in] Authsalt-存放盐值信息的地址
	///\param [out] reserve-保留参数
	///\return -1-fail,	0-success
	virtual int getAuthsalt(const char **authsalt, void *reserve = NULL)
		COMPONENT_UNIMPLEMENTED_OPERATION_RETURN_INT

	///\brief 初始化客户端流模式和拉流需要获取的媒体
	///\param [in] httpUrl-GET 请求后面的url
	///\param [in] mode-客户端流模式，@see  httpDhSessionMode
	///\param [in] stream_type-客户端业务类型，@see 	 httpDhUrlInfo::UrlType
	///\param [in] trackid_flags-拉流需要获取的媒体，指定媒体通道号对应位(共32位，暂使用低7位); 该参数仅提供给httpDhUrlInfo::UrlTypeVisualTalk使用; 视频为第0位，第一路音频为第1位，对讲为第6位
	/* 
	//	 高位 							 低位
	//	 保留字段					   已使用字段
	//	  xxxxxxxx xxxxxxxx xxxxxxxx XXXXXXXX
	//								  |||||||
	//正向对讲语音--------------------|||||||
	//反向对讲语音---------------------||||||
	//元数据 		  ----------------------|||||
	//辅助帧 		  -----------------------||||
	//第二路音频       ------------------------|||
	//第一路音频       -------------------------||
	//视频		  --------------------------|
	*/
	///\param [in] reserve -保留参数
	///\return -1-fail, 0-success
	virtual int initStreamMode(const char *httpUrl, int mode, int stream_type, unsigned int trackid_flags, void *reserve = NULL)
		COMPONENT_UNIMPLEMENTED_OPERATION_RETURN_INT

	///\brief 同步获取对讲编码配置参数初始化SDP, 用于客户端向服务端推送媒体数据时使用, 目前只供语音对讲和可视对讲使用
	///\param [in] private_sdp-是否使用私有SDP, 默认填true
	///\param [in] talkEncInfo	-语音对讲编码配置,对讲音频暂只支持一路音频，,配置参照AudioEncodeInfo
	///\param [in] reserve-保留参数
	///\return -1-fail, 0-success
	virtual int initSdp(bool private_sdp, AudioEncodeInfo &talkEncInfo, void *reserve = NULL)
		COMPONENT_UNIMPLEMENTED_OPERATION_RETURN_INT

	///\brief 从设备回复SDP中提取对讲编码配置参数, 上层收到MSG_HTTPDH_READY后才可调用该接口, 目前只供语音对讲和可视对讲使用
	///\param [out] talkEncInfo -语音对讲编码配置,对讲音频暂只支持一路音频，,配置参照AudioEncodeInfo
	///\param [in/out] reserve-保留参数
	///\return -1-fail, 0-success
	virtual int getMediaEncode(AudioEncodeInfo &talkEncInfo, void *reserve = NULL)
		COMPONENT_UNIMPLEMENTED_OPERATION_RETURN_INT

	///\brief 开启指定通道媒体传输, 主要用于直播开始后操作, 目前只供可视对讲UrlTypeVisualTalk使用
	///\param [in] handler-句柄
	///\param [in] trackid_flags-拉流需要获取的媒体，指定媒体通道号对应位(共32位，暂使用低7位);; 视频为第0位，第一路音频为第1位，对讲为第6位
	/* 
	//	 高位 							 低位
	//	 保留字段					   已使用字段
	//	  xxxxxxxx xxxxxxxx xxxxxxxx XXXXXXXX
	//								  |||||||
	//正向对讲语音--------------------|||||||
	//反向对讲语音---------------------||||||
	//元数据 		  ----------------------|||||
	//辅助帧 		  -----------------------||||
	//第二路音频       ------------------------|||
	//第一路音频       -------------------------||
	//视频		  --------------------------|
	*/
	///\param [in] httpUrl-GET 请求后面的url, 默认设置为NULL; 如果设置为NULL则不变更httpUrl
	///\param [in] reserve		-保留参数
	///\return -1-fail, 0-success
	virtual int enableMedia(uint32_t trackidFlags, const char *httpUrl = NULL, void *reserve = NULL)
		COMPONENT_UNIMPLEMENTED_OPERATION_RETURN_INT
		
	///\brief 关闭指定通道媒体传输, 主要用于直播开始后操作, 目前只供可视对讲UrlTypeVisualTalk使用
	///\param [in] handler-句柄
	///\param [in] trackid_flags-拉流需要获取的媒体，指定媒体通道号对应位(共32位，暂使用低7位);; 视频为第0位，第一路音频为第1位，对讲为第6位
	/* 
	//	 高位 							 低位
	//	 保留字段					   已使用字段
	//	  xxxxxxxx xxxxxxxx xxxxxxxx XXXXXXXX
	//								  |||||||
	//正向对讲语音--------------------|||||||
	//反向对讲语音---------------------||||||
	//元数据 		  ----------------------|||||
	//辅助帧 		  -----------------------||||
	//第二路音频       ------------------------|||
	//第一路音频       -------------------------||
	//视频		  --------------------------|
	*/
	///\param [in] httpUrl-GET 请求后面的url, 默认设置为NULL; 如果设置为NULL则不变更httpUrl
	///\param [in] reserve		-保留参数
	///\return -1-fail, 0-success
	virtual int disableMedia(uint32_t trackidFlags, const char *httpUrl = NULL, void *reserve = NULL)
		COMPONENT_UNIMPLEMENTED_OPERATION_RETURN_INT

	///\brief 发送媒体数据包, 上层收到MSG_HTTPDH_READY后才可调用该接口, 目前只供语音对讲和可视对讲使用
	///\param [in] trackid-媒体通道
	///\param [in] frame-媒体数据帧,暂只支持音频 
	///\param [in] reserve		-保留参数
	///\return -1-fail, 0-success
	virtual int put_frame(int trackid, StreamSvr::CMediaFrame &frame, void *reserve = NULL)
		COMPONENT_UNIMPLEMENTED_OPERATION_RETURN_INT

	///\brief 客户端获取连接信息
	///\param[out] 保存客户端连接信息的地址
	///\return 0-ok, -1-failed
	virtual int getConnectInfo(httpDhConnectInfo &connectInfo)
		COMPONENT_UNIMPLEMENTED_OPERATION_RETURN_INT

	///\brief HTTPDH客户端组件保留虚接口扩展数量,每增加一个必须减1
	DAHUA_COMPONENT_FUNCTION_REVSERVED(17)
};

/// 定义IHttpStreamClient智能指针
typedef Component::TComPtr<IHttpStreamClient> IHttpStreamClientPtr;

}//namespace StreamApp
}//namespace Dahua

#endif //__INCLUDED_DAHUA_STREAMAPP_IHTTPSTREAMCLIENT_H__
