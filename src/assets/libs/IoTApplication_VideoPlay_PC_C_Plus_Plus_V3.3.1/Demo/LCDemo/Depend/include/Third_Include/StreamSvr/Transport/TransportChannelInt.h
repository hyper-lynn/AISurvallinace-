#ifndef __INCLUDE_DAHUA_STREAMSVR_TRANSPORTCHANNEL_INT_H__
#define __INCLUDE_DAHUA_STREAMSVR_TRANSPORTCHANNEL_INT_H__

#include "StreamSvr/Defs.h"
#include "StreamSvr/Transport/TransportChannel.h"
#include "NetFramework/Sock.h"

namespace Dahua{
namespace StreamSvr{

class CTransportChannelIntImpl;
class STREAMSVR_API CTransportChannelInterleave : public CTransportChannel
{

	///\brief 构造接口
	CTransportChannelInterleave();
	///\brief 析构接口
	~CTransportChannelInterleave();

public:
	///\brief 创建交织传输通道
	///\return 交织通道对象指针
	static CTransportChannelInterleave* create();

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
	///\param [in] callback: 媒体数据回调接口
	int setMediaCallback(MediaCallback callback);

	///\brief 发送媒体数据
	///\param [in] frame-数据承载体
	///\param [in] channel_id-传输通道标识
	///\param [in] mark-标志位，若当前包是帧的最后一个包，则mark == 1,否则mark == 0
	///\return >0-填充字节数, -1-failed
	int sendMedia(const CMediaFrame &frame, int channelId, int mark = 1);

	///\brief 停止接收码流
	void stop();
	
	///\brief 设置传输选项参数
	///\param [in] option-选项值,目前暂时没有用到
	///\param [in] value-选项值所在的内存地址
	///\param [in] len-选项值的长度
	///\return 0-ok,-1-failed
	int setOption(const char* optionName, void* value, int len);
	
	///|breif 重写基类设置流媒体发送策略
	///\param [in] optname-选项名,参考 @see TransStrategy
	///\param [in] optvalue-选项值
	///\return -1-失败，0-成功
	int setStrategy(int optName, void *optValue);

	//====================== 派生类方法 =========================
	///\brief 设置交织套接字
	///\param [in] sock-句柄
	///\param [in] needClose-套接字是否关闭
	///\return 0-ok, -1-failed
	int setInterleaveChannelSock(int sock, bool needClose = true);

	///\brief 设置码流分离对象
	///\param [in] streamSeparator: 传输策略对象
	///\return -1: 设置失败，0: 设置成功
	int setStreamSeparator(IStreamSeparator *streamSeparator, bool needClose = true);

	///\brief 设置信令数据回调接口
	///\param [in] proc: 信令数据回调接口
	int setCommandCallback(CmdCallback callback);

	///\brief 设置媒体异常回调接口
	///\param [in] callback: 异常回调接口
	int setExceptionCallback(ExceptionCallBack callback);

	///\brief 绑定信令传输句柄
	///\param [in] channelId 通道标示符
	///\return 0-ok, -1-failed
	int addInterleaveChannel(int channelId);

	///\brief 取消媒体数据发送通道
	///\param [in] channelId 通道标示符
	///\return 0-ok, -1-failed
	int removeInterleaveChannel(int channelId);

	///\brief 发送非流媒体数据
	///\param [in] cmdData-CMediaFrame
	int sendCommand(const CMediaFrame &cmdData);

	///\breif 注册帧发送状态类, 传输通道不会管理 注册的状态类内存,该内存由上层释放
	///\param [in] framestate-要注册的帧发送状态类指针
	void setFrameState(IFrameStatePtr framestate);

	///\brief 设置传输套接字
	///\param [in] sock-要设置的套接字智能指针
	///\param [in] needClose-套接字是否关闭
	///\return -1: 设置失败，0: 设置成功
	int setInterleaveChannelSock(Memory::TSharedPtr<NetFramework::CSock> &sock, bool needClose = true);

	///\brief 发送媒体数据
	///\param [in] frame-数据承载体
	///\param [in] channel_id-传输通道标识
	///\param [in] len-待发送的数据长度
	///\param [in] beginpos -要发送的数据在frame 中的起始偏移
	///\return >=0-发送的字节数, -1-failed
	int sendMedia(const CMediaFrame &frame, int channelId, uint32_t len, uint32_t beginpos);

	///\brief 发送信令数据
	///\param [in] cmdData-信令数据
	///\param [in] len-待发送的信令长度
	///\param [in] beginpos -要发送的信令数据在cmdData 中的起始偏移
	///\return >=0-发送的字节数, -1-failed
	int sendCommand(const CMediaFrame &cmdData, uint32_t len, uint32_t beginpos);

	///|breif 获得流媒体层发送策略
	///\param [in] optname-选项名,参考 @see TransStrategy
	///\param [in] optvalue-选项值
	///\return -1-失败，0-成功
	int getStrategy(int optName, void *optValue);

	///\brief 设置媒体数据回调接口
	///\param [in] callback: 媒体数据回调接口
	///\return -1: 设置失败，0: 设置成功
	int setSendCallback(SendCallback callback);

	///\brief 获取tcp传输选项
	///\param [in] optname-选项名,参考 @see TransportOpt, 目前只支持transportOptSndBuffer和transportOptRecvBuffer和
	///\param [out] optvalue-选项值所保存的地址
	///\param [in] len-选项值所保存的地址长度
	///\return -1-失败，0-成功
	int getOption(int optName, void *optValue, int len);
private:
	CTransportChannelIntImpl * m_impl;
};

	}
}


#endif
