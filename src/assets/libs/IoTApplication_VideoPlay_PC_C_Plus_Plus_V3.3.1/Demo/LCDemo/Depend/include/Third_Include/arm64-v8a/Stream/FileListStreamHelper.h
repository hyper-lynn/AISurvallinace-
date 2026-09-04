//
//  "$Id$"
//
//  Copyright (c)1992-2011, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef DAHUA_STREAM_UNISTREAM_FILE_LIST_STREAM_HELPER_H__
#define DAHUA_STREAM_UNISTREAM_FILE_LIST_STREAM_HELPER_H__


#include <Infra/IntTypes.h>
#include <Infra/Time.h>
#include <Infra/Signal.h>
#include <Infra/String.h>
#include <Component/Unknown.h>
#include <Json/value.h>
#include "MediaFrame.h"


namespace Dahua {
namespace Stream {


/// 前置声明
class IFileListStreamHelper;

/// 组件接口智能指针声明
typedef Component::TComPtr<IFileListStreamHelper> IFileListStreamHelperPtr;

/// 可同步回放的多文件码流助手类
class IFileListStreamHelper : public Component::IUnknown
{
public:	// 工厂

	/// 文件列表信息结构, 80 字节
	struct MediaFileInfo
	{
		const char*			filename; 		///< 文件名称
		Infra::SystemTime	startTime;		///< 文件开始时间
		Infra::SystemTime	endTime;		///< 文件结束时间
		int					reserved[3];
	};

	/// 组件工厂类
	class IFactory : public Component::IFactoryUnknown
	{
	public:
		/// 创建 IFileListStreamHelper 文件列表流助手对象
		/// \param [in] filelist 文件名数组首地址
		/// \param [in] count 文件信息数组元素个数
		/// \param [in] device 设备详细信息, 格式同RemoteDevice的设备信息; 取本地流, 必须为 null
		virtual IFileListStreamHelper* create(MediaFileInfo const* filelist, int count,
					Json::Value const& device = Json::Value::null) = 0;

		/// 组件接口ID定义
		static const char* iid() {return "FileListStreamHelper";}
	};

public:	// 类型

	/// 定义回调函数类型，接收帧数据
	/// 返回值是void
	/// 参数是帧数据对象
	typedef	Infra::TSignal1<CMediaFrame const&> Signal;
	typedef Signal::Proc Proc;

	/// 状态定义
	enum State
	{
		stateError = -1,		///< 有错误发生
		stateStandby = 0,		///< 已停止
		stateRunning,			///< 运行中
		statePaused,			///< 已暂停
	};

	/// 事件通知定义
	enum Notice
	{
		noticeStateChanged,		///< 状态已变更
		noticeFileChanged,		///< 码流源文件已切换
		noticeSynchronized,		///< 已与其它源同步
		noticeUnsynchronized,	///< 已取消与其它源同步
	};

	/// 定义事件通知观察者
	/// 参数为事件通知值
	/// 返回值为 void
	typedef	Infra::TSignal1<Notice>		NoticeSignal;
	typedef NoticeSignal::Proc			NoticeProc;

	/// 时间区间结构体定义
	struct TimeRange
	{
		Infra::SystemTime	begin;		///< 开始时间
		Infra::SystemTime	end;		///< 结束时间
	};

public:	// 操作

	/// 设置码流源的策略参数
	/// \param [in] config 码流源参数, 定义如下：
	/// \code
	///	{
	///		"StepFrameParam" : {		// 跳I帧控制参数, 仅对本地文件流有效, 目前只支持 "Auto"
	/// 		"Mode" : "Auto",		// 跳I帧模式, "Auto"-自动模块, "Speed" : 根据回放速度选择
	///			"KeyFrameSpeed": 2.0,	// 回放速度绝对值超过此值时跳I帧回放，0 表示永远不跳I帧，"Mode" 为 "Speed" 时有效
	///		}
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

	/// 限制回放时间, 只回放时间区间数组内的视频片段
	/// \param [in] ranges 时间区间数组
	/// \param [in] count 时间区间数组元素个数
	virtual bool limitPlayTime(const TimeRange ranges[], size_t count)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 设置速率
	virtual bool setSpeed(float speed)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 取当前速率
	virtual bool getSpeed(float& speed)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 恢复播放
	virtual bool play()
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 暂停播放
	virtual bool pause()
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 跳帧; num 为负数表示向前跳帧, isIFrame 表示是否跳I帧
	virtual bool stepFrame(int num, bool isIFrame = true)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 跳转到指定时间回放
	virtual bool playTime(Infra::CTime const& time)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 跳转到列表中的特定文件
	virtual bool playFile(char const* filename)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 跳转到列表中当前文件的下一个文件
	virtual bool playNextFile()
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 跳转到列表中当前文件的前一个文件
	virtual bool playPrevFile()
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 取得当前正在播放的文件名
	/// \param filename [out] 文件名
	virtual bool getPlayFileName(Infra::CString& filename)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 取当前流的时间
	virtual bool getTime(Infra::CTime&)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 设置或取消同步
	virtual bool syncTo(IFileListStreamHelperPtr other)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 取同步组ID
	/// \param [out] sync 同步组ID, -1 表示没有和其它对象同步
	virtual bool getSyncState(int& sync)
		COMPONENT_UNIMPLEMENTED_OPERATION

public:	// 状态

	/// 注册事件通知观察者
	virtual bool attachNotice(NoticeProc)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 解除事件通知观察者
	virtual bool detachNotice(NoticeProc, bool wait = true)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 取当前码流源状态
	virtual bool getState(State& state)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 取错误号
	virtual bool getError(int& eno) const
		COMPONENT_UNIMPLEMENTED_OPERATION

    DAHUA_COMPONENT_FUNCTION_REVSERVED(11)
};


} // namespace Stream
} // namespace Dahua


#endif	//DAHUA_STREAM_UNISTREAM_FILE_LIST_STREAM_HELPER_H__

