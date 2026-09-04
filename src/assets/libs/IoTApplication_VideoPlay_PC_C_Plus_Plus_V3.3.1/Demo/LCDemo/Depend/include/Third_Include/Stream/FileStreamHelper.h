//
//  "$Id$"
//
//  Copyright (c)1992-2012, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef STREAM_UNISTREAM_MEDIA_FILE_STREAM_HELPER_H__
#define STREAM_UNISTREAM_MEDIA_FILE_STREAM_HELPER_H__

#include <Json/value.h>
#include <Infra/Time.h>
#include <Infra/Signal.h>
#include <Stream/StreamSource.h>


namespace Dahua {
namespace Stream {

/// 文件流统一接口
class IFileStreamHelper : public Component::IUnknown
{
public:	// 工厂

	/// 组件工厂
	class IFactory : public Component::IFactoryUnknown
	{
	public:
		/// 创建 IFileStreamHelper 数据源对象
		/// 打开文件数据源
		/// \param [in] filename 文件名称
		/// \param [in] device 设备详细信息, 格式同RemoteDevice的设备信息; 取本地流, 必须为 null
		virtual IFileStreamHelper* create(std::string const& filename,
		Json::Value const& device = Json::Value::null) = 0;

		/// 组件接口ID定义
		static const char* iid() {return "FileStreamHelper";}
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
		statePaused,			///< 已暂停
	};

	/// 定义事件观察者
	/// 参数为事件值
	/// 返回值为 void
	typedef	Infra::TSignal1<State>	StateSignal;
	typedef StateSignal::Proc		StateProc;

public:	// 操作

	/// 设置码流源的策略参数
	/// \param [in] config 码流源参数, 定义如下：
	/// \code
	///	{
	///		"KeyFrameSpeed": 2,	// speed 不小于此值时跳 I 帧, 为 0 表示都不跳 I 帧
	///	}
	/// \endcode
	virtual bool config(Json::Value const& config)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 绑定数据接收者
	virtual bool attach(Proc)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 解除绑定
	virtual bool detach(Proc, bool wait = true)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 恢复播放
	virtual bool play()
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 暂停播放
	virtual bool pause()
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 设置速率
	virtual bool setSpeed(float speed)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 取当前速率
	virtual bool getSpeed(float& speed)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 定位到参考位置开始处偏移offset后的位置
	virtual bool seek(int offset, IStreamSource::SeekPosition)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 定位到指定时间附件的I帧
	virtual bool seekByTime(Infra::CTime const&)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 跳帧; num 为负数表示向前跳帧, isIFrame 表示是否跳I帧
	virtual bool stepFrame(int num, bool isIFrame = true)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 取当前流的时间
	virtual bool getTime(Infra::CTime&)
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
	virtual bool getError(int& eno) const
		COMPONENT_UNIMPLEMENTED_OPERATION

    DAHUA_COMPONENT_FUNCTION_REVSERVED(17)
};

} // namespace Stream
} // namespace Dahua

#endif// STREAM_UNISTREAM_MEDIA_FILE_STREAM_HELPER_H__

