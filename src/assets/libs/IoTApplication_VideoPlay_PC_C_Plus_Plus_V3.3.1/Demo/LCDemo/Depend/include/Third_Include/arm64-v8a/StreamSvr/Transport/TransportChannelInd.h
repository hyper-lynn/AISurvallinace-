#ifndef __INCLUDE_DAHUA_STREAMSVR_TRANSPORTCHANNEL_IND_H__
#define __INCLUDE_DAHUA_STREAMSVR_TRANSPORTCHANNEL_IND_H__

#include "StreamSvr/Defs.h"
#include "StreamSvr/Transport/TransportChannel.h"

namespace Dahua{
namespace StreamSvr{


class CTransportChannelIndImpl;
class STREAMSVR_API CTransportChannelIndepent : public CTransportChannel
{
public:
	///> 非交织传输通道工作模式
	enum  WorkMode
	{
		workModeSendRecv,	//收发
		workModeSendOnly,	//只发
		workModeRecvOnly	//只收
	};

	///\brief 创建独立传输通道对象
	///\param [in] multicast: CTransportChannelIndepent 作为组播用途
	///\return 对象指针
	static CTransportChannelIndepent* create(WorkMode mode = workModeSendRecv);

	///\brief 释放对象
	void destroy();
	
public:
	//====================== 重载基类方法 =========================
	///\brief 设置传输策略类型的接口(比如实时，流畅)
	///\param [in] strategyObj: 传输策略对象
	///\return -1: 设置失败，0: 设置成功
	int setTransStrategyProcessor(CTransportStrategy * strategyObj);

	///\brief 设置媒体适配的接口
	///\param [in] mediaAdapter: 媒体适配句柄
	///\return -1: 设置失败，0: 设置成功
	int setMediaAdapter(IMediaAdapter *mediaAdapter);

	///\brief 设置媒体数据回调接口
	///\param [in] proc: 媒体数据回调接口
	int setMediaCallback(MediaCallback callback);

	///\brief 发送媒体数据
	///\param [in] frame-数据承载体
	///\param [in] channel_id-传输通道标识
	///\param [in] mark-标志位，若当前包是帧的最后一个包，则mark == 1,否则mark == 0
	///\param >0-填充字节数, -1-failed
	int sendMedia(const CMediaFrame &frame, int channelId, int mark = 1);

	///\brief 停止接收码流
	void stop();

	///|breif 重写基类设置流媒体发送策略
	///\param [in] optname-选项名,参考 @see TransStrategy
	///\param [in] optvalue-选项值
	///\return -1-失败，0-成功
	int setStrategy(int optName, void *optValue);

	//====================== 派生类方法 =========================
	///\brief 设置媒体数据传输通道(RTP、RTCP etc.)
	///\param [in] sock-套接字
	///\param [in] sockType句柄类型 @see CTransport::SockType
	///\param [in] id-TrackID
	///\param [in] remoteIp-远端IP
	///\param [in] remotePort-远端端口
	///\param [in] needClose-套接字是否关闭
	///\return 0-ok, -1-failed	
	int addDataChannel(Memory::TSharedPtr<NetFramework::CSock> &sock, int channelId, const char* remoteIp = NULL, int remotePort = 0, bool needClose = true);

	///\brief 取消媒体数据发送通道
	///\param [in] channelId-发送通道
	///\return 0-ok, -1-failed
	int removeDataChannel(int channelId);

	///\brief 处理udp传输特有的选项
	///\param [in] optName-选项名,目前支持{"PKTSIZE", "PKTHDR","MTU"} 这两种参数
	///\param [in] optValue-选项值
	///\param [in] len-选项长度
	///\return -1-失败，0-成功
	int setOption(const char* optionName, void* value, int len);

	///\breif处理udp传输通道相关的选项
	///\param[in] channelId-通道号
	///\param[in] optionName - 选项名，目前支持{transportOptRecvBuffer}
	///\param[in] value -选项值 
	///\return -1-失败，0-成功
	int setDataChannelOption(int channelId, int optionName, int value);

	///\breif 注册帧发送状态类, 传输通道不会管理 注册的状态类内存,该内存由上层释放
	///\param [in] framestate-要注册的帧发送状态类指针
	void setFrameState(IFrameStatePtr framestate);

	///\brief 设置媒体异常回调接口
	///\param [in] callback: 异常回调接口
	///\return -1-失败,0-成功
	int setExceptionCallback(ExceptionCallBack callback);

	///\breif处理udp传输通道相关的选项
	///\param[in] channelId-通道号
	///\param[in] optionName - 选项名，目前支持{TransportRtpDisorderWindow}
	///\param[in] value -选项值 
	///\param[in] len-选项长度
	///\return -1-失败，0-成功
	int setDataChannelOption(int channelId, int optionName, const void* value, int len);

	///\brief 获取udp传输选项
	///\param[in] channelId-通道号
	///\param [in] optname-选项名,参考 @see TransportOpt, 目前只支持transportOptSndBuffer和transportOptRecvBuffer和
	///\param [out] optvalue-选项值所保存的地址
	///\param [in] len-选项值所保存的地址长度
	///\return -1-失败，0-成功
	int getDataChannelOption(int channelId, int optName, void *optValue, int len);
	
private:
	///\brief 构造接口
	CTransportChannelIndepent(WorkMode mode);

	///\brief 析构接口
	~CTransportChannelIndepent();

	CTransportChannelIndImpl * m_impl;
};

}
}

#endif

