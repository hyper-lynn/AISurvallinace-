#ifndef __INCLUDED_DAHUA_STREAM_APP_ITCP_STREAM_SENDER_H__
#define __INCLUDED_DAHUA_STREAM_APP_ITCP_STREAM_SENDER_H__

#include "Component/Unknown.h"
#include "Component/Defs.h"
#include "NetFramework/SockAddr.h"
#include "StreamApp/Defs.h"
#include "StreamSvr/Util/MediaFrame.h"
#include "StreamApp/SdpMaker.h"


namespace Dahua{
namespace StreamApp{

/*---------------------------------------------------------------------------------------------------------
				  		TCP 流发送工具接口调用的流程如下
			Dahua::Component::createComponentObject<Dahua::StreamApp::ITcpStreamSender>();
											        |			
									ITcpStreamSender::init
												|
					在handle_message 收到MSG_TCP_SENDER_READY 消息时调用
							       ITcpStreamSender::initMedia(可视对讲调用)
												|
									ITcpStreamSender::put_frame
												|
									  ITcpStreamSender::close
			       注意调用close 函数前必须保证上层没有调用put 接口传输数据
        (handle_message函数中收到MSG_TCP_SENDER_FAIL 消息后或者init失败也需要调用 ITcpStreamSender::close)    
---------------------------------------------------------------------------------------------------------*/

// TCP 发送工具异常通知消息
#define MSG_TCP_SENDER_FAIL         0x6000

// TCP 发送工具网络连接成功消息
#define MSG_TCP_SENDER_READY        0x6001


///\brief TCP 发流工具接口类
class STREAMAPP_API ITcpStreamSender: public Component::IUnknown
{
public:
	///\brief TCP 工具发送模式
	enum TcpSenderMode
	{
		TcpSendNaa = 0,  ///< 采用NAA发送, 会进行丢帧, 一般监视流采用
		TcpSendBlock,	 ///< 阻塞式发送, 保证不会丢帧，会阻塞线程, 一般回放流采用
	};	

	///\brief TCP 工具初始化信息
	struct InitInfo
	{
		int   sendmode;			///< 发送模式
		char *senderid;			///< 发送器ID , 不同的发送器应保证id 不冲突,用于问题定位
		int   reserve1[8];		///< 保留字段
		void *reverse2[4];		///< 保留字段
		
		InitInfo():sendmode(TcpSendNaa), senderid(NULL)
		{
			memset(reserve1, 0, sizeof(reserve1));
			memset(reserve1, 0, sizeof(reverse2));
		}
	};

	///\brief TCP 发流工具配置选项
	enum TcpSenderConfig
	{	
		TcpSenderConfigSendBufSize = 0,		///< 配置系统套接字的发送缓冲
		TcpSenderConfigNumber,				///< 配置的数目
	};

public:
	///\brief 组件工厂
	class IFactory : public Component::IFactoryUnknown
	{
	public:
		///\brief 取ITcpStreamSender 对象实例
		virtual ITcpStreamSender* create() = 0;

		///\brief 组件接口ID定义
		static const char* iid() {return "StreamApp::TcpStreamSender";}
	};

protected:
	
	///\brief 析构函数
	virtual ~ITcpStreamSender(){}

public:
	///\brief 初始化TCP 发送工具
	///\param [in] remote	-要连接的对端地址
	///\param [in] socktype-要发起连接的套接字类型, 暂时只支持SOCK_TYPE_STREAM
	///\param [in] owerid	 -TCP 发送工具所属者id
	///\param [in] initinfo    -初始化参数信息
	///\return : 0-成功, -1 失败
	virtual int init(const NetFramework::CSockAddr *remote, NetFramework::CSock::SOCKET_TYPE socktype, long owerid, ITcpStreamSender::InitInfo &initinfo)
		COMPONENT_UNIMPLEMENTED_OPERATION_RETURN_INT

	///\brief 关闭发流工具对象
	virtual int close()
		COMPONENT_UNIMPLEMENTED_OPERATION_RETURN_INT		

	///\brief 初始化TCP 流媒体信息
	///\param [in] dstPacketType	-目的码流的打包类型, @see StreamSvr::MediaPacketType
	///\param [in] videoinfo   -视频的编码信息
	///\param [in] audioinfo	 -音频的编码信息
	///\return : 0-成功, -1 失败
	virtual int initMedia(int dstPacketType, VideoEncodeInfo &videoinfo, AudioEncodeInfo &audioinfo)
		COMPONENT_UNIMPLEMENTED_OPERATION_RETURN_INT

	///\brief 发送音视频数据帧
	///\param [in] frame: 要发送的音视频完整的一个大华帧
	///\return : 0-成功, -1 失败
	virtual int put(int mediaindex, StreamSvr::CMediaFrame &frame)
		COMPONENT_UNIMPLEMENTED_OPERATION_RETURN_INT

	///\brief 配置TCP 发送工具
	///\param [in]	option-工作选项,参考@see TcpSenderConfig
	///\param [in]	opt-选项参数指针
	///\param [in]	optLen-选项参数指针所指区域的可访问长度
	///\return : 0-成功, -1 失败
	virtual int setConfig(int option, const void *opt, int optLen)
		COMPONENT_UNIMPLEMENTED_OPERATION_RETURN_INT

	DAHUA_COMPONENT_FUNCTION_REVSERVED(27)
};

/// 定义ITcpStreamSender 智能指针
typedef Component::TComPtr<ITcpStreamSender> TcpStreamSenderPtr;

}//StreamApp
}//Dahua

#endif //__INCLUDED_DAHUA_STREAM_APP_ITCP_STREAM_SENDER_H__


