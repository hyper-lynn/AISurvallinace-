#ifndef __DAHUA_STREAMAPP_HTTP_VODSTREAM_H__
#define __DAHUA_STREAMAPP_HTTP_VODSTREAM_H__

#include "Infra/Signal.h"
#include "Infra/Time.h"
#include "Component/Unknown.h"
#include "StreamSvr/Util/MediaFrame.h"
#include "StreamApp/SdpMaker.h"


namespace Dahua{
namespace StreamApp{

/// \brief HTTP-DH 点播流源类
class IHttpVodStream : public Component::IUnknown
{
public:
	///\brief HTTP 点播源数据回调
    ///\param [in] 媒体索引
    ///\param [in] 完整的一帧大华媒体帧数据
	typedef Infra::TSignal2<int, StreamSvr::CMediaFrame&>Signal;
	typedef	Signal::Proc Proc;

	///\brief 通过sdp 字符串进行编码信息异步初始化回调函数
	///\param [in] bool 			-初始化成功或者失败
	///\param [in] const char * 	-初始化sdp 信息
	///\param [in] void *	       -保留参数,暂无作用
	typedef Infra::TFunction3<void, bool, const char *, void *> InitMediaEncodeProc;
	
	/// 组件工厂
	class IFactory : public Component::IFactoryUnknown
	{
	public:

		///\brief 创建文件点播流源
		///\param [in] url-客户端请求的url流源,包括两种按时间和文件名路径url形式:
		///\  "channel=1&subtype=0&starttime=2018_06_14_22_27_05&endtime=2018_06_14_22_27_50"
		///\  "/mnt/sd/2018-06-14/001/dav/22/22.27.05-22.27.50[M][0@0][0].mp4"
		///\return 文件点播流对象指针
		virtual IHttpVodStream* create(const std::string &url) = 0;

		/// 组件接口ID定义
		static const char* iid(){return "StreamApp::HttpVodStream";};
	};

public:
	///\brief 析构函数
	virtual ~IHttpVodStream(){};
	
	///\brief 启动捕获，开始取数据,保证首帧数据为I帧
	///\param [in]proc -取流的回调函数
	/// \return true -成功, false -失败
	virtual bool start(Proc proc)
		COMPONENT_UNIMPLEMENTED_OPERATION
	
	///\brief 停止取流
	///\param [in]proc -取流的回调函数
	/// \return true -成功, false -失败
	virtual bool stop(Proc proc)
		COMPONENT_UNIMPLEMENTED_OPERATION
	
	///\brief 暂停取流, 该接口需要支持在回调中暂停取流
	/// \return true -成功, false -失败
	virtual bool pause()
		COMPONENT_UNIMPLEMENTED_OPERATION
	
	///\brief 恢复取流, 该接口从暂停的地方恢复取流,调用该接口后开始传输数据
	/// \return true -成功, false -失败
	virtual bool resume()
		COMPONENT_UNIMPLEMENTED_OPERATION
	
	///\brief 设置速率
	///\param [in]speed -取流的速度
	/// \return true -成功, false -失败
	virtual bool setSpeed(float speed)
		COMPONENT_UNIMPLEMENTED_OPERATION

	///\brief 获取当前流的时间
	///\param [out] time -当前流的时间
	/// \return true -成功, false -失败
	virtual bool getTime(Infra::CTime &time)
		COMPONENT_UNIMPLEMENTED_OPERATION
		
	///\brief  定位到指定时间附近的I帧,调用该接口后开始传输数据,保证首帧数据为I帧
	///\param [in] time -定位到的指定时间并播放
	///\return true -成功, false -失败
	virtual bool seekByTime(Infra::CTime const &time)
		COMPONENT_UNIMPLEMENTED_OPERATION
	
	///\brief  获 取文件的时间范围
	///\param [out]startTime -开始时间
	///\param [out]endTime  - 结束时间
	///\return true -成功, false -失败
	virtual bool getFileRange(Infra::CTime& startTime, Infra::CTime& endTime)
		COMPONENT_UNIMPLEMENTED_OPERATION
	
	///\brief 文件数据是否已传输完成, 流源先将该接口设置为true, 再回调空包通知文件播放结束,支持跨文件播放
	///\return true-已传输完成, false-未传输完成
	virtual bool isFilePlayOver()
		COMPONENT_UNIMPLEMENTED_OPERATION

	///\brief 同步获取音视频编码配置参数
	///\param [in] videoEncInfo-视频编码配置,配置参照VideoEncodeInfo
	///\param [in] audioEncInfo-音频编码配置,配置参照AudioEncodeInfo
	///\return true-ok, false-failed
	virtual bool getMediaEncode(VideoEncodeInfo &videoEncInfo, AudioEncodeInfo &audioEncInfo)
		COMPONENT_UNIMPLEMENTED_OPERATION

	///\brief 异步获取音视频编码配置参数
	///\param [in] proc-编码信息的sdp 回调函数
	///\return true-ok, false-failed
	virtual bool getMediaEncode(InitMediaEncodeProc proc)
		COMPONENT_UNIMPLEMENTED_OPERATION

	///类中总函数中个数上限为18, 包括虚析函数, 以后每增加一个函数, 预留的函数个数相应地减一个.
	DAHUA_COMPONENT_FUNCTION_REVSERVED(18);
};

typedef Component::TComPtr<IHttpVodStream> IHttpVodStreamPtr;

} // namespace StreamApp
} //namespace Dahua

#endif// __DAHUA_STREAMAPP_HTTP_VODSTREAM_H__

