#ifndef __INCLUDED_DAHUA_STREAM_APP_RTMP_PUSH_CLIENT_H__
#define __INCLUDED_DAHUA_STREAM_APP_RTMP_PUSH_CLIENT_H__

#include "NetFramework/Sock.h"
#include "Memory/SharedPtr.h"
#include "StreamApp/Defs.h"
#include "StreamSvr/Util/MediaFrame.h"

namespace Dahua{
namespace StreamApp{

///\brief 媒体类型
enum RTMP_STREAM_TYPE{
	RTMP_STREAM_VIDEO = 1 << 0,      ///< 视频帧
	RTMP_STREAM_AUDIO = 1 << 1,		 ///< 音频帧
};

///\brief 媒体编码类型
enum RTMP_ENCODE{
	RTMP_ENCODE_AAC = 1,            ///< AAC类型
};

///\brief 音频编码信息
typedef struct _AUDIO_META
{
   int	sound_channel;			///< 单声道为1 , 双声道为2, 暂时只支持单声道
   int	sound_format; 			///< 媒体编码类型, 见RTMP_ENCODE_AAC
   int	sound_bytes;			///< 音频采样位数, 填入8 或16 分别表示8 位采样或16位采样
   int	sound_rate;				///< 音频采样率，单位是HZ
}AUDIO_META;

/*---------------------------------------------------------------------------------------------------------
客户端接口调用的流程如下
									CRtmpPushClient::create
											    |			
									CRtmpPushClient::setConfig
											    |						                  
								         CRtmpPushClient::init
								                            |
								     CRtmpPushClient::addMedia(视频)
				 (handle_message函数中收到MSG_RTMP_READY 消息后调用)		     
						                        		    |
								    CRtmpPushClient::addMedia(音频)
				 (handle_message函数中收到MSG_RTMP_READY 消息后调用)		     				    
								                            |
						                    CRtmpPushClient::InputData				 
											    |
								   CRtmpPushClient::close
        (handle_message函数中收到MSG_RTMP_FAIL消息后或者init失败, 或者上层主动停止推流调用)    
---------------------------------------------------------------------------------------------------------*/

///\brief 内嵌类前向声明
class CRtmpPushClientImpl;

///\brief 客户端会话接口类
class STREAMAPP_API CRtmpPushClient
{
public:
	///\brief 客户端配置选项,参见CRtmpPushClient::setConfig()
	enum ClientConfig
	{	
		clientConfigChunkSize = 0,			///< Rtmp 块大小, 设置的值为uint32_t
		clientConfigSendBufSize,			///< 设置推流客户端发送媒体数据的缓冲区大小.opt配置以字节为单位
		clientConfigMessageTimeout,			///< 信令超时时间，默认值为10秒(精度10-20秒)，单位为秒
		clientConfigNumber,
	};

public:
	///\brief 创建客户端
	///\return 客户端对象-ok, NULL-failed	
	static CRtmpPushClient* create();

	///\brief 关闭客户端
	void close();	

	///\brief 初始化客户端
	///\param [in] rtmpUrl-包含ip & port的rtmp url
	///\param [in] ownerID-CRtmpPushClient 所属对象的网络框架的ID号 
	///\param [in] socktype-要发起连接的套接字类型, 暂时只支持SOCK_TYPE_STREAM
	///\param [in] param-套接字需要的一些参数
	///\param [in] newSock-暂不支持, 以后扩展使用
	///\param [in] needClose-是否由流媒体关闭newSock 所带的套接字句柄, true-关闭 false-不关闭	
	///\return : 0-成功, -1 失败
	int init(const char *rtmpUrl, long ownerID, NetFramework::CSock::SOCKET_TYPE socktype, void *param = NULL, Memory::TSharedPtr<NetFramework::CSock> newSock = Memory::TSharedPtr<NetFramework::CSock>(), bool needClose = true);

	///\brief 添加推流的视频或者音频, 如果需要推送多种媒体,需要调用多次
	///\           当stream_type 为RTMP_STREAM_VIDEO, frame_meta 传入NULL
	///\           当stream_type 为RTMP_STREAM_AUDIO, frame_meta 传入AUDIO_META 类型指针, 
	///\           也可以传入空指针, 将会从帧里面提取编码信息
	///\           上层收到MSG_RTMP_READY后才可调用该接口
	///\param [in] stream_type:  媒体类型, 见RTMP_STREAM_TYPE
	///\param [in] frame_meta:   媒体类型对应的媒体信息
	///\return : 0-成功, -1 失败
	int addMedia(int stream_type, void* frame_meta);

	///\brief 设置推流客户端的配置
	///\param [in]	option-工作选项,参考@see ClientConfig
	///\param [in]	opt-选项参数指针
	///\param [in]	optLen-选项参数指针所指区域的可访问长度
	///\return : 0-成功, -1 失败
	int setConfig(int option, const void *opt, int optLen);

	///\brief :  发送音视频数据帧, 
	///\param [in] frame: 要发送的音视频完整的一个大华帧
	///\return : 0-成功, -1 失败
	int InputData(StreamSvr::CMediaFrame &frame);

private:
	///\brief 构造函数
	CRtmpPushClient();

	///\brief 析构函数
	~CRtmpPushClient();
	
private:
	CRtmpPushClientImpl *m_impl;
};

}//StreamApp
}//Dahua

#endif //__INCLUDED_DAHUA_STREAM_APP_RTMP_PUSH_CLIENT_H__
