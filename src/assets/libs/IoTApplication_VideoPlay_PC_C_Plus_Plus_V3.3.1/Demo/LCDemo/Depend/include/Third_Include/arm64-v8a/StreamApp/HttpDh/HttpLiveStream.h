#ifndef __DAHUA_STREAMAPP_HTTP_DH_LIVESTREAM_H__
#define __DAHUA_STREAMAPP_HTTP_DH_LIVESTREAM_H__

#include "Component/Unknown.h"
#include "Infra/Signal.h"
#include "StreamApp/SdpMaker.h"


namespace Dahua{
namespace StreamApp{

/// \brief HTTP-DH 直播流源类
class IHttpLiveStream : public Component::IUnknown
{
public:
	///\brief HTTP 直播源数据回调
    ///\param [in] 媒体索引, 取值参考@MediaUtil.h  @see MaxTrack
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
		virtual IHttpLiveStream* create(const std::string &url) = 0;

		/// 组件接口ID定义
		static const char* iid(){return "StreamApp::HttpLiveStream";};
	};

protected:

	virtual ~IHttpLiveStream(){};
	
public:

	///\brief 启动捕获，开始取数据
	///\param [in] proc-回调函数
	///\return true-ok, false-failed
	virtual bool start(Proc proc)
		COMPONENT_UNIMPLEMENTED_OPERATION;

	///\brief 停止捕获，关闭取数据
	///\param [in] proc -回调函数
	///\return true-ok, false-failed
	virtual bool stop(Proc proc)
		COMPONENT_UNIMPLEMENTED_OPERATION;

	///\brief 强制I 帧
	///\return true-ok, false-failed
	virtual bool setIFrame()
		COMPONENT_UNIMPLEMENTED_OPERATION;

	///\brief 同步获取音视频编码配置参数
	///\param [in] videoEncInfo-视频编码配置,配置参照VideoEncodeInfo
	///\param [in] audioEncInfo-音频编码配置,配置参照AudioEncodeInfo
	///\return true-ok, false-failed
	virtual bool getMediaEncode(VideoEncodeInfo &videoEncInfo, AudioEncodeInfo &audioEncInfo)
		COMPONENT_UNIMPLEMENTED_OPERATION;

	///\brief 异步获取音视频编码配置参数
	///\param [in] proc-编码信息的sdp 回调函数
	///\return true-ok, false-failed
	virtual bool getMediaEncode(InitMediaEncodeProc proc)
		COMPONENT_UNIMPLEMENTED_OPERATION;

	///\brief 同步获取对讲音频编码配置参数
	///\param [in] talkEncInfo-音频编码配置,配置参照AudioEncodeInfo, 对讲必须填写,默认使用通道0作为对讲音频
	///\           audioChannelEncodeInfo数组下标0表示对讲反向音频编码配置,下标1表示对讲正向音频编码配置
	///\return true-ok, false-failed
	virtual bool getMediaEncode(AudioEncodeInfo &talkEncInfo)
		COMPONENT_UNIMPLEMENTED_OPERATION;

	///\brief 开启指定索引媒体数据回调
	///\param [in] mediaIndex -媒体索引
	///\param [in] reserve -保留参数
	///\return true-ok, false-failed
	virtual bool enableOneMedia(int mediaIndex, void *reserve)
		COMPONENT_UNIMPLEMENTED_OPERATION;

	///\brief 关闭指定索引媒体数据回调
	///\param [in] mediaIndex -媒体索引
	///\param [in] reserve -保留参数
	///\return true-ok, false-failed
	virtual bool disableOneMedia(int mediaIndex, void *reserve)
		COMPONENT_UNIMPLEMENTED_OPERATION;

	///类中总函数中个数上限为32，包括虚析函数;以后每增加一个函数，预留的函数个数相应地减一个。
	DAHUA_COMPONENT_FUNCTION_REVSERVED(24);
};

typedef Component::TComPtr<IHttpLiveStream> IHttpLiveStreamPtr;

} // namespace StreamApp
} //namespace Dahua

#endif// __DAHUA_STREAMAPP_HTTP_DH_LIVESTREAM_H__

