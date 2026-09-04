#ifndef __INCLUDE_DAHUA_STREAMSVR_TRANSPORTCHANNEL_H__
#define __INCLUDE_DAHUA_STREAMSVR_TRANSPORTCHANNEL_H__

#include "StreamSvr/Defs.h"
#include "NetAutoAdaptor/MediaFrame.h"
#include "StreamSvr/Util/MediaFrame.h"
#include "Infra/Function.h"
#include "StreamSvr/Util/FrameState.h"

namespace Dahua{
namespace StreamSvr{

class IStreamSeparator;
class IMediaAdapter;
class CTransportStrategy;

///\brief 信令回调接口
///\param [in] CMediaFrame
typedef Infra::TFunction1<void, CMediaFrame const&> CmdCallback;	

///\brief 数据回调接口
///\param [in] 通道号
///\param [in] CMediaFrame
typedef Infra::TFunction2<void, int, CMediaFrame const&> MediaCallback;

///\brief 异常回调接口
///\param [in] 错误码
typedef Infra::TFunction1<void, int> ExceptionCallBack;

///\brief 发送缓冲信息回调接口
///\param [in] NAA库的缓冲帧数目
///\param [in] 发送的媒体帧
///\param [in] 保留参数
typedef Infra::TFunction3<void, int, CMediaFrame const&, void *> SendCallback;

///\brief 传输通道，负责数据的流转
class STREAMSVR_API CTransportChannel
{
public:
	///> 传输方式
	enum TransMode
	{
		transModeBegin = 0,
		transModeInterleaved,		///> 交织方式
		transModeIndependent,		///> UDP方式
		transModeEnd = 9999
	};

	///> 流媒体传输策略
	enum TransStrategy
	{
		transAlgorithm = 0,			///> NAA发送算法设置
		transBlock,					///> 录像阻塞不丢帧策略设置
		transBufferStrategy,		///>设置Naa发送缓冲策略
		transChannelStrategy,		///> NAA通道发送策略，目前主要是均匀发送策略
		transEnd = 9999
	};
	
protected:
	///\brief 构造接口
	CTransportChannel():m_trans_mode(transModeBegin){};
	///\brief 析构函数
	virtual ~CTransportChannel(){};
public:
	///\brief 获取当前传输对象的传输模式
	///\return TransMode枚举值
	TransMode getTransMode() {return m_trans_mode;}

	///\brief 设置传输策略类型的接口(比如实时，流畅)
	///\param [in] strategyObj: 传输策略对象
	///\return -1: 设置失败，0: 设置成功
	virtual int setTransStrategyProcessor(CTransportStrategy * strategyObj) = 0;
	
	///\brief 设置媒体适配的接口
	///\param [in] mediaAdapter: 媒体适配句柄
	///\return -1: 设置失败，0: 设置成功
	virtual int setMediaAdapter(IMediaAdapter *mediaAdapter) = 0;

	///\brief 设置媒体数据回调接口
	///\param [in] callback: 媒体数据回调接口
	///\return -1: 设置失败，0: 设置成功
	virtual int setMediaCallback(MediaCallback callback) = 0;

	///\brief 发送媒体数据
	///\param [in] frame-数据承载体
	///\param [in] channel_id-传输通道标识
	///\param [in] mark-标志位，若当前包是帧的最后一个包，则mark == 1,否则mark == 0
	///\return >0-填充字节数, -1-failed
	virtual int sendMedia(const CMediaFrame &frame, int channelId, int mark = 1) = 0;

	///\brief 停止接收码流
	virtual void stop() = 0;

	///|breif 设置流媒体层发送策略
	///\param [in] optname-选项名,参考 @see TransStrategy
	///\param [in] optvalue-选项值
	///\return -1-失败，0-成功
	virtual int setStrategy(int optName, void *optValue) = 0;

	///|breif 注册帧发送状态类, 传输通道不会管理 注册的状态类内存,该内存由上层释放
	///\param [in] framestate-要注册的帧发送状态类指针
	virtual void setFrameState(IFrameStatePtr framestate){return;}

	///|breif 获得流媒体层发送策略
	///\param [in] optname-选项名,参考 @see TransStrategy
	///\param [in] optvalue-选项值
	///\return -1-失败，0-成功
	virtual int getStrategy(int optName, void *optValue){return -1;};

	///\brief 设置媒体数据回调接口
	///\param [in] callback: 媒体数据回调接口
	///\return -1: 设置失败，0: 设置成功
	virtual int setSendCallback(SendCallback callback){return -1;}
protected:
	TransMode			m_trans_mode;			///> 传输模式
};

}//StreamSvr
}//Dahua

#endif //__INCLUDE_DAHUA_STREAMSVR_TRANSPORTCHANNEL_H
