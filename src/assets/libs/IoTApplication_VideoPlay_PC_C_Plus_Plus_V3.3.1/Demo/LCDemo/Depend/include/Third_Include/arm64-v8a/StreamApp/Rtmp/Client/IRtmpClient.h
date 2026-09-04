#ifndef __INCLUDE__STREAMAPP_IRTMPCLIENT_H
#define __INCLUDE__STREAMAPP_IRTMPCLIENT_H

#include "StreamSvr/Util/MediaFrame.h"
#include "Component/Unknown.h"
#include "StreamApp/Defs.h"

namespace Dahua{
namespace StreamApp{


///\brief RTMP 客户端对象, 封装一层不需要继承网络框架的客户端适配层
class STREAMAPP_API IRtmpClient
{
public:
	///\brief 设置使用方式
	enum RTMP_METHODS
	{
		RTMP_PUSH_STREAM = 0,	///< 由设备向FMS服务器推流的工作方式
		RTMP_PULL_STREAM,		///< 从FMS拉流的工作方式
	};

	enum RTMP_EVENT_TYPE
	{
		RTMP_EVENT_FAIL = 0,	///< RTMP 客户端异常
	};

	///\brief RTMP 客户端事件回调函数
	///\param [in] int:  事件类型, 见RTMP_EVENT_TYPE
	///\param [in] void *:  事件类型对应的事件信息
	typedef Infra::TFunction2<void, int, void *> EventProc;

	///\brief 定义回调函数类型，接收帧数据，RTMP_PULL_STREAM设置需要使用该回调
	typedef Infra::TFunction2<void, StreamSvr::CMediaFrame const&, int> Proc;

protected:
	///\brief 虚析构函数, 不允许delete , 请调用Destory 接口销毁
	virtual ~IRtmpClient() {}

public:	
	///\brief 创建RTMP客户端对象, rtmp://192.168.1.100:1935/live/livestream1, ip为192.168.1.100, port 为1935, live/livestream1为ch_url,
	///\param [in] ip:  RTMP 服务器的地址, 可以为域名
	///\param [in] port:  RTMP 服务器的监听端口,  如果ip 为域名时, port 填0
	///\param [in] ch_url:  通道的url 信息
	///\param [in] type:  客户端类型
	///\return : 0-成功, -1 失败
	static IRtmpClient* Create(const char* ip, int port, const char* ch_url, RTMP_METHODS type = RTMP_PUSH_STREAM);
	
	///\brief 添加视频或者音频, 从FMS 拉流不需要使用此方法
	///\           当stream_type 为RTMP_STREAM_VIDEO, frame_meta 传入NULL
	///\           当stream_type 为RTMP_STREAM_AUDIO, frame_meta 传入AUDIO_META 类型指针, 
	///\           也可以传入空指针, 将会从帧里面提取编码信息
	///\param [in] stream_type:  媒体类型, 见RTMP_STREAM_TYPE
	///\param [in] frame_meta:   媒体类型对应的媒体信息
	///\return : 0-成功, -1 失败
	virtual int AddMedia(int stream_type, void *frame_meta) = 0;
	
	///\brief : 删除视频或者音频, 该接口已废弃, 从FMS 拉流不需要此方法
	///\param [in] stream_type:  媒体类型
	///\return : 0-成功, -1 失败
	virtual int DelMedia(int stream_type) = 0;
	
	///\brief :  创建开始传输流, 调用该接口后，方能调用InputData接口传输数据
	///\param [in] proc:  收数据回调, 对于推流, 该参数暂未使用
	///\return : 0-成功, -1 失败, 返回-1 直接调用Destroy释放资源
	virtual int StartStream(Proc proc = NULL) = 0;
	
	///\brief :  销毁传输流,解除码流回调,
	///\             对于推流, 该接口已废弃, 调用Destory 函数即停止推流和销毁资源
	///\param [in] proc:  收数据回调, 对于推流, 该参数暂未使用
	///\return : 0-成功, -1 失败
	virtual int StopStream(Proc proc = NULL) = 0;
	
	///\brief :  发送音视频流, 从FMS 拉流不需,用此方法
	///\param [in] mediaframe: 要发送的音视频大华帧
	///\return : 0-成功, -1 失败
	virtual int InputData(StreamSvr::CMediaFrame &mediaframe) = 0;
	
	///\brief :  停止推流并销毁IRtmpClient 客户端对象
	///\return : 0-成功, -1 失败
	virtual int Destory() = 0;

	///\brief 设置RTMP推流客户端配置参数
	///\param [in] option: 配置的枚举
	///\param [in] opt: 配置的值的指针
	///\param [in] opt: 配置的值的指针长度
	///\return : 0-成功, -1 失败
	virtual int SetConfig(int option, const void *opt, int optLen) = 0;

	///\brief 注册RTMP推流客户端事件回调
	///\param [in] proc: 事件回调函数
	///\return : 0-成功, -1 失败
	virtual int AttachEvent(EventProc proc) = 0;
	
	DAHUA_COMPONENT_FUNCTION_REVSERVED(8)
};

}//StreamApp
}//Dahua
#endif

