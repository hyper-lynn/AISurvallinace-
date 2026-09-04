#ifndef __INCLUDE_DAHUA_STREAMSVR_TRANSPORTDEF_H__
#define __INCLUDE_DAHUA_STREAMSVR_TRANSPORTDEF_H__

#include "NetFramework/SockAddrStorage.h"

#include <string.h> // memset()

namespace Dahua{
namespace StreamSvr{

///\brief 传输选项
enum TransportOpt
{
	transportOptSndBuffer,			///> 发送缓冲选项
	transportOptRecvBuffer, 		///> 接收缓冲选项
	transportOptRemoteAddr, 		///> 设置对端地址选项，UDP专用
	transportOptMulticastIF,		///> 设置组播地址，UDP专用
	transportOptTTL,				///> 设置time-to-live，UDP专用
	transportOptLowSpeedRecv,		///> 设置低速接收模式
	transportOptMediaSsrc,			///> 设置有效媒体的SSRC
	TransportRtpPacketOptimizing,	///>设置是否使用rtp优化接收略， 只对tcp有用
	TransportRtpDisorderWindow,		///>设置RTP乱序窗口配置,只对UDP有用
	transportOptRealTimeRecv,		///> 设置实时接收选项，利用handle_input来接收数据
	transportOptMulticastSF,		///> 设置组播源地址过滤，UDP专用
	transportOptDynMemSize,			///> 设置动态分配策略为IFrameSizePolicy 时的最大I 帧大小
	transportOptUdpConnect,			///> 设置udp socket是否需要connect
	transportOptSsrcVerify,			///> 设置ssrc校验选项
	transportOptTOS,				///> 设置IP头的TOS属性
	transportOptChannelInfo,		///> 设置传输通道信息，TCP专用（定制需求使用）
	transportOptNumber, 			///> 未知
};

///\brief 网络传输错误
enum transError
{
	UnKnown = 0,			///> 未知错误
	RecvError,				///> 接收错误
	SendError,				///> 发送错误
	SendTimeout,			///> 发送超时
	SeparatorFailed,		///> 码流分离失败
};

struct RemoteSockeInfo
{
	NetFramework::CSockAddrStorage remoteAddr;		///< 远端地址
	bool needConnect;								///< udp socket是否需要connect
	
	RemoteSockeInfo(): needConnect(true)
	{}
};

///\brief 传输通道信息
struct TransChInfo
{
	uint32_t ssrc;			///> ssrc
	int32_t  channel;		///> 交织通道
	int      reserve[2];	///> 保留字段
	
	TransChInfo():ssrc(0), channel(0)
	{
		memset(reserve, 0, sizeof(reserve));
	}
};


}//StreamSvr
}//Dahua

#endif //__INCLUDE_DAHUA_STREAMSVR_TRANSPORTDEF_H__
