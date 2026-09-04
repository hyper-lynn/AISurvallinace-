//
//  "$Id: DevVideoEnc.h 47583 2012-01-11 05:50:36Z qin_fenglin $"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef __DAHUA_STREAMAPP_RTMP_VODSTREAM_H__
#define __DAHUA_STREAMAPP_RTMP_VODSTREAM_H__

#include "Json/value.h"
#include "Infra/Signal.h"
#include "Infra/Time.h"
#include "Infra/String.h"
#include "Component/Unknown.h"
#include "StreamSvr/Util/MediaFrame.h"
#include "RtmpUtil.h"


namespace Dahua{
namespace StreamApp{

/// \brief RTMP 点播流源类
class IRtmpVodStream : public Component::IUnknown
{
public:
	typedef	Infra::TSignal2<int, StreamSvr::CMediaFrame&> Signal;
	typedef	Signal::Proc Proc;
	
	/// 组件工厂
	class IFactory : public Component::IFactoryUnknown
	{
	public:
		virtual IRtmpVodStream* create(const std::string &url) = 0;

		/// 组件接口ID定义
		static const char* iid(){return "StreamApp.IRtmpVodStream";};
	};

public:
	///\brief 析构函数
	virtual ~IRtmpVodStream(){};
	
	///\brief 开始取流,用于初始化sdp 信息
	///\param [in]proc -取流的回调函数
	/// \return true -成功, false -失败
	virtual bool start(Proc proc)
		COMPONENT_UNIMPLEMENTED_OPERATION
	
	///\brief 停止取流
	///\param [in]proc -取流的回调函数
	/// \return true -成功, false -失败
	virtual bool stop(Proc proc)
		COMPONENT_UNIMPLEMENTED_OPERATION

	///\brief 从文件开始位置开始传输数据,调用该接口后开始传输数据
	///\return true-ok, false-failed
	virtual bool restart()
		COMPONENT_UNIMPLEMENTED_OPERATION
	
	///\brief 暂停取流, 该接口需要支持在回调中暂停取流
	/// \return true -成功, false -失败
	virtual bool pause()
		COMPONENT_UNIMPLEMENTED_OPERATION
	
	///\brief 恢复取流, 该接口从暂停的地方恢复取流
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
	virtual bool getTime(Infra::CTime &time) const
		COMPONENT_UNIMPLEMENTED_OPERATION
		
	///\brief  定位到指定时间附近的I帧
	///\param [in] time -定位到的指定时间并播放
	///\return true -成功, false -失败
	virtual bool seekByTime(Infra::CTime const &time)
		COMPONENT_UNIMPLEMENTED_OPERATION
	
	///\brief  获 取文件的时间范围
	///\param [out]startTime -开始时间
	///\param [out]endTime  - 结束时间
	///\return true -成功, false -失败
	virtual bool getFileRange(Infra::CTime& startTime, Infra::CTime& endTime) const
		COMPONENT_UNIMPLEMENTED_OPERATION
	
	///\brief 文件数据是否已传输完成
	///\return true-已传输完成, false-未传输完成
	virtual bool isFilePlayover()
		COMPONENT_UNIMPLEMENTED_OPERATION

	///\brief 注册初始化sdp 信息的回调函数, 该接口注册成功说明sdp 信息由上层
	///\          通过回调传出, 此时不需要回调数据, 直到调用restart 接口开始传输数据  
	///\          本地录像码流可以不需要实现本函数
	///\param [in] proc-回调函数
	///\return true -成功, false -失败
	virtual bool registerIniteventproc(InitREventProc proc)
		COMPONENT_UNIMPLEMENTED_OPERATION

	///类中总函数中个数上限为15, 包括虚析函数, 以后每增加一个函数, 预留的函数个数相应地减一个.
	DAHUA_COMPONENT_FUNCTION_REVSERVED(14);
};

typedef Component::TComPtr<IRtmpVodStream> IRtmpVodStreamPtr;

} // namespace StreamApp
} //namespace Dahua

#endif// __DAHUA_STREAMAPP_RTMP_VODSTREAM_H__

