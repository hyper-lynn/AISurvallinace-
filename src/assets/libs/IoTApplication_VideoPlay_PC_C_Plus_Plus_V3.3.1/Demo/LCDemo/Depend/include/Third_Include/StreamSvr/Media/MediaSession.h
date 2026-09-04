#ifndef __INCLUDE_DAHUA_STREAMSVR_MEDIASESSION_H__
#define __INCLUDE_DAHUA_STREAMSVR_MEDIASESSION_H__

#include "StreamSvr/Defs.h"
#include "StreamSvr/Media/MediaUtil.h"
#include "StreamSvr/Transport/MediaAdapter.h"
#include "Memory/SharedPtr.h"


namespace Dahua{
namespace NetFramework{class CMediaStreamSender;}
namespace StreamSvr{

///\brief 媒体事件观察者接口
///\note 媒体会话事件信息回调，如创建媒体过程返回的SDP信息等
class STREAMSVR_API IMediaEventObserver
{
public:
	///\brief 虚析构函数
	virtual ~IMediaEventObserver(){};
	
public:
	///\brief 媒体描述更新事件上报接口
	///\param [in] type-事件类型，参见StreamEventType中关于sdp更新事件定义
	///\param [in] data-事件内容描述
	///\param [in] len-事件内容描述长度
	///\return -1-处理失败，0-处理成功
	virtual int onSdpEvent(int type, const TransformatParameterEx* data=NULL){return -1;}

	///\brief 媒体事件(如文件播放完成，流源错误等事件)上报接口
	///\param [in]type-事件类型，参见StreamEventType中关于其他非sdp更新事件定义
	///\param [in]parameter-事件描述，参见EventParameter@MediaUtil.cpp
	///\return -1-处理失败，0-处理成功
	virtual int onOtherEvent(int type,  const EventParameter* parameter = NULL){return -1;}

};

class CMediaSessionImpl;
class CTransportChannel;
///\brief 媒体会话类，作为媒体层的统一入口
class STREAMSVR_API CMediaSession
{
public:
	///\brief 创建接口
	///\param [in] observer-事件观察者对象
	///\return :返回创建好的session句柄-成功，NULL-失败
	static CMediaSession* create(IMediaEventObserver* observer=NULL);

	///\brief 获取流引用计数
	///\param [in] content-流源内容
	///\return >0 - 引用计数 -1 失败
	static long GetDataSrcRef(const char* content);

	///\brief 销毁接口，释放该对象资源
	void destroy();

public:
	///\brief 初始化传输通道，用于发送媒体之用，限定用户值传入一个
	///\param [in] transportChannel-传输通道
	///\param [in] sender-网络框架的发送工具
	///\return 0-成功，-1-失败
	virtual int setTransport(CTransportChannel *transportChannel, NetFramework::CMediaStreamSender* sender = NULL);
	
	///\brief 创建媒体请求
	///\param [in] createInfo,媒体创建请求，见mediaUtils.h相关定义
	///\return 0-成功，-1-失败
	virtual int createMedia(const MediaCreateInfoRequest &createInfo);

	///\brief 配置媒体请求,该接口为同步接口
	///\param [in] configRequest,媒体配置请求，见mediaUtils.h相关定义
	///\param [in] configResponse,配置响应内容
	///\return 0-成功，-1-失败
	virtual int configMedia(const MediaConfigInfoRequest &configRequest, MediaConfigInfoResponse &configResponse);

	///\brief 播放媒体请求,该接口为同步接口
	///\param [in] playRequest,媒体播放请求，见mediaUtils.h相关定义
	///\param [in] configResponse,媒体播放响应内容
	///\return 0-成功，-1-失败
	virtual int playMedia(const MediaPlayInfoRequest &playRequest, MediaPlayInfoResponse &playResponse);

	///\brief 暂停媒体请求,该接口为同步接口，暂时没有响应返回，调用方可以通过返回值判断是否成功
	///\return 0-成功，-1-失败
	virtual int pauseMedia();

	///\brief 停止媒体流请求，该接口为同步接口，没有响应返回，调用方可以通过返回值判断是否成功
	///\param [in] createInfo,媒体流停止请求，见mediaUtils.h相关定义
	///\return 0-成功，-1-失败
	virtual int stopMedia(const MediaStopInfoRequest &stopInfo);

	///\brief 注册外部回调进来取流
	///\param [in] dstPktType-目的包类型，见mediaUtils.h中MediaPacketType定义
	///\param [in] proc-外部回调
	///\return 0-成功，-1-失败
	virtual int attach(int dstPktType, DataProc proc);

	///\brief 注销外部回调
	///\param [in] dstPktType-目的包类型，见mediaUtils.h中MediaPacketType定义
	///\return 0-成功，-1-失败
	virtual int detach(int dstPktType);
	
	///\brief 开始发流
	///\param [in] proc-回调数据的钩子函数
	///\return 0-成功，-1-失败
	virtual int startStreaming(DataProc proc = DataProc());

    ///\brief 如果媒体已经播放，可调用该接口获取play回放信息
	///\param [in] proc-回调数据的钩子函数
	///\return 0-成功，-1-失败
	virtual int getPlayResponseInfo(const MediaPlayInfoRequest &playRequest, MediaPlayInfoResponse &playResponse);

	///\brief 获取媒体配置参数
	///\param [in] name-配置名称
	///\param [in] value-配置的值
	///\param [in] len	- 配置参数值的长度
	///\return 0-ok, -1-failed
	virtual int setOption(MediaSessionConfigSet name, void *value, int len);

	///\brief 获取媒体流量统计信息
	///\param [in] datasrctype-数据源类型, 见DataSourceType
	///\param [in] lengthsend-上一次调用本接口到此次调用间的发送数据长度
	///\param [in] lengthreceive-暂未实现,  外部传入NULL
	virtual void GetStatisticInfo(int &datasrctype, uint64_t *lengthsend, uint64_t *lengthreceive);

	///\brief 设置媒体适配的接口
	///\param [in] mediaAdapter: 媒体适配句柄
	///\return -1: 设置失败，0: 设置成
	virtual int setMediaAdapter(Memory::TSharedPtr<IMediaAdapter> mediaAdapter);

	///\brief 获取标识流源的唯一信息
	///\param [out] stStreamSourceInfo
	///\return -1: 设置失败，0: 设置成
	virtual int GetStreamSourceInfo(StreamSourceInfo &stStreamSourceInfo);

	///\brief 更新媒体信息
	///\param [in] parameter 转码参数信息
	///\return -1: 设置失败，0: 设置成功
	virtual int updateMedia(const TransformatParameterEx& parameter);

	///\brief 创建SRTP加密器 
	///\param [in] config 密钥配置信息
	///\param [in] mediaIndex  通道号
	///\return 0-ok, -1-failed
	virtual int createSrtpEncrypt(const SrtpEncryptConfig & config, int mediaIndex);
protected:
	///\brief 构造
	///\param [in] observer-事件观察者对象
	CMediaSession(IMediaEventObserver* observer);
	
	///\brief 析构
	virtual ~CMediaSession();
	
public:
	///\brief 开启指定通道媒体传输
	///\param [in] trackid_flags- 媒体索引；-1代表所有媒体；否则代表对应的媒体
	///\param [in] dataDirection- 数据传输方向
	///\return -1-fail, 0-success
	virtual int enableMedia(int mediaIndex, int dataDirection);
	
	///\brief 关闭指定通道媒体传输
	///\param [in] trackid_flags- 媒体索引；-1代表所有媒体；否则代表对应的媒体
	///\param [in] dataDirection- 数据传输方向
	///\return -1-fail, 0-success
	virtual int disableMedia(int mediaIndex, int dataDirection);

private:

	CMediaSessionImpl *m_impl;
};
}
}
#endif//__INCLUDE_DAHUA_STREAMSVR_MEDIASESSION_H__

