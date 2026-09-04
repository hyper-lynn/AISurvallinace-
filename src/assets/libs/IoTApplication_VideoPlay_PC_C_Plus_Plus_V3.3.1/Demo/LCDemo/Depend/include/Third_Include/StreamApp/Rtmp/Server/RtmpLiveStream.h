//
//  "$Id: RtmpLiveStream.h 47583 2016-10-24 05:50:36Z tang_bin $"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef __DAHUA_STREAMAPP_RTMP_LIVESTREAM_H__
#define __DAHUA_STREAMAPP_RTMP_LIVESTREAM_H__

#include "Component/Unknown.h"
#include "StreamSvr/Media/MediaUtil.h"
#include "Infra/Signal.h"
#include "RtmpUtil.h"

namespace Dahua{
namespace StreamApp{

/// \brief RTMP 直播流源类
class IRtmpLiveStream : public Component::IUnknown
{
public:
	///\brief RTMP 直播源数据回调
    ///\param [in] 媒体索引
    ///\param [in] 完整的一帧大华媒体帧数据
	typedef Infra::TSignal2<int, StreamSvr::CMediaFrame&>Signal;
	typedef	Signal::Proc Proc;

	/// 组件工厂
	class IFactory : public Component::IFactoryUnknown
	{
	public:
		virtual IRtmpLiveStream* instance(const std::string &url) = 0;

		/// 组件接口ID定义
		static const char* iid(){return "StreamApp.IRtmpLiveStream";};
	};

public:
	virtual ~IRtmpLiveStream(){};

	///\brief 启动捕获，开始取数据
	///\param [in] proc-回调函数
	///\return true-ok, false-failed
	virtual bool start(Proc proc)
		COMPONENT_UNIMPLEMENTED_OPERATION;

	///\brief 停止捕获，关闭取数据
	///\param [in] proc-回调函数
	///\return true-ok, false-failed
	virtual bool stop(Proc proc)
		COMPONENT_UNIMPLEMENTED_OPERATION;

	///\brief 强制I 帧
	///\return true-ok, false-failed
	virtual bool setIFrame()
		COMPONENT_UNIMPLEMENTED_OPERATION;

	///\brief 注册初始化sdp 信息的回调函数, 该接口注册成功说明sdp 信息由上层
	///\         通过回调传出,  本地编码码流可以不需要实现本函数
	///\param [in] proc-回调函数
	///\return true-ok, false-failed
	virtual bool registerIniteventproc(InitREventProc proc)
		COMPONENT_UNIMPLEMENTED_OPERATION
	
	///类中总函数中个数上限为7，包括虚析函数;以后每增加一个函数，预留的函数个数相应地减一个。
	DAHUA_COMPONENT_FUNCTION_REVSERVED(7);
};

typedef Component::TComPtr<IRtmpLiveStream> IRtmpLiveStreamPtr;

} // namespace StreamApp
} //namespace Dahua

#endif// __DAHUA_STREAMAPP_RTMP_LIVESTREAM_H__

