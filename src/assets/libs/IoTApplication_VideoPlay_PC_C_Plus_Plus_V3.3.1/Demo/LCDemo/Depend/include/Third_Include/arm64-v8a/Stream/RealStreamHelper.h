//
//  "$Id$"
//
//  Copyright (c)1992-2012, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef STREAM_UNISTREAM_MEDIA_REAL_STREAM_HELPER_H__
#define STREAM_UNISTREAM_MEDIA_REAL_STREAM_HELPER_H__


#include <Infra/Signal.h>
#include <Component/Unknown.h>
#include <Stream/MediaFrame.h>
#include <Json/value.h>


namespace Dahua {
namespace Stream {

/// 实时流助手类；支持断线重连，循环队列
class IRealStreamHelper : public Component::IUnknown
{
public:	// 工厂

	/// 组件工厂
	class IFactory : public Component::IFactoryUnknown
	{
	public:
		/// 取 IRealStreamHelper 数据源对象实例
		/// 打开实时数据源
		/// \param [in] source 通道号
		///	\code
		///	{
		///		"DeviceInfo" : {},		// 设备详细信息，格式同RemoteDevice的设备信息
		///		"VideoChannel" : 0,		// 视频通道号
		///		"VideoStream" : "Main",	// 视频码流类型，"Main"-主码流, "Extra1"-辅码流1, "Extra2"-辅码流2, "Extra3"-辅码流3, "Talkback"-对讲流
		///	}
		///	\endcode
		virtual IRealStreamHelper* instance(Json::Value const& source) = 0;

		/// 组件接口ID定义
		static const char* iid() {return "RealStreamHelper";}
	};

public:	// 类型

	/// 定义回调函数类型，接收帧数据
	/// 返回值是void
	/// 参数是帧数据对象
	typedef	Infra::TSignal1<Stream::CMediaFrame const&> Signal;
	typedef Signal::Proc Proc;

	/// 状态定义
	enum State
	{
		stateError = -1,		///< 有错误发生
		stateStandby = 0,		///< 已停止
		stateRunning,			///< 运行中
	};

	/// 定义事件观察者
	/// 参数为事件值
	/// 返回值为 void
	typedef	Infra::TSignal1<State>	StateSignal;
	typedef StateSignal::Proc		StateProc;

public:	// 操作

	/// 设置码流源的策略参数
	/// \param [in] config 码流源参数, 保留
	/// \endcode
	virtual bool config(Json::Value const& config)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 绑定数据接收观察者
	virtual bool attach(Proc)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 解除绑定数据接收观察者
	virtual bool detach(Proc, bool wait = true)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 从缓冲队列中获取包，数据包取走后并不出列。推荐使用此接口来
	/// 统一使用包数据，使用者不使用自有缓冲。
	/// \b 只有在观察者绑定成功后才有数据。
	/// \param [in, out] sn 包的序列号，最新的数据包的序列号是依次增加的：-1表示
	///   取最新数据包；0 或者序号偏小则取最老的数据包；取其他值表示如果队列中存
	///   在该数据包，则返回对应的数据包，否则返回空包。sn传出的值是下一个数据包
	///   的序号：如果原序号存在并且而取到了有效的数据包，该值会递增 1；如果偏小
	///   而取到了最老的数据包，该值会被设置为最老数据包的下一个包的序号；如果偏
	///   大而没有取到数据，则维持不变。
	/// \param [out] lostNum 相对 sn 值丢失的帧数，为 0 表示没有丢帧。
	/// \return 取到的数据包，内部数据包可能为空，需要使用valid判断。
	virtual bool getFrame(int64_t& sn, int64_t& lostNum, CMediaFrame& frame)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 根据预录时间获取包序号
	virtual bool getPreFrameSn(int seconds, int64_t& sn)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 设置缓冲区预录队列帧数
	virtual bool adjustPreCount(int count)
		COMPONENT_UNIMPLEMENTED_OPERATION

public:	// 状态

	/// 注册状态观察者
	virtual bool attachState(StateProc)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 解除状态观察者
	virtual bool detachState(StateProc, bool wait = true)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 取当前码流源状态
	virtual bool getState(State& state)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 取错误号
	virtual bool getError(int& eno)
		COMPONENT_UNIMPLEMENTED_OPERATION

    DAHUA_COMPONENT_FUNCTION_REVSERVED(22)
};

} // namespace Stream
} // namespace Dahua

#endif// STREAM_UNISTREAM_MEDIA_REAL_STREAM_HELPER_H__

