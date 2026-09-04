
//
//  "$Id$"
//
//  Copyright (c)1992-2012, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef __STREAM_UNISTREAM_FILE_STREAM_H__
#define __STREAM_UNISTREAM_FILE_STREAM_H__

#include "Component/Unknown.h"
#include <Json/value.h>
#include "Infra/Signal.h"
#include "Stream/MediaFrame.h"

namespace Dahua {
namespace Stream {
	
class IFileStream : public Component::IUnknown
{
public:	// 工厂

	/// 组件工厂
	class IFactory : public Component::IFactoryUnknown
	{
	public:
		/// 创建 IFileStream 文件流对象
		/// 打开文件数据源		
		/// \param [in] condition 文件流条件
		virtual IFileStream* create(Json::Value const& condition) = 0;
		
		/// 创建 IFileStream 文件流对象
		/// \param [in] filename 文件名	
		virtual IFileStream* create(const char* filename) = 0;	

		/// 组件接口ID定义
		static const char* iid() {return "FileStream";}
	};	
public:
	/// 定义数据观察者类型，接收帧数据
	/// 返回值是void
	/// 参数是帧数据对象，视频帧和图片帧都包括大华帧头。如果有错误发生，观察者会
	/// 收到无效包，可以用 getError 取出错误号。
	/// 如果文件结束，回调无效包，且 getError 取出的错误号为 0
	typedef	Infra::TSignal1<CMediaFrame const&> Signal;
	typedef Signal::Proc Proc;
		
	virtual ~ IFileStream (void) {};
	
	/// 查询文件流媒体信息
	/// \param [in] info 文件信息
	virtual bool getFileStreamInfo(Json::Value& info)
		COMPONENT_UNIMPLEMENTED_OPERATION
	
	/// 获取时间段信息
	virtual bool getTimeSections(Json::Value& timeSections)	
		COMPONENT_UNIMPLEMENTED_OPERATION
	
	/// 获取文件流关联的事件信息
	/// \param [in] type 事件类型，默认type = NULL为全部事件
	/// \param [out] events 事件信息列表	
	virtual bool getEvents(Json::Value& events, const char* type = NULL)
		COMPONENT_UNIMPLEMENTED_OPERATION
	
	/// 获取文件流关联的标签信息
	/// \param [out] tags 标签列表
	virtual bool getTags(Json::Value& tags)
		COMPONENT_UNIMPLEMENTED_OPERATION
	
	/// 获取文件流关联的字幕信息
	/// \param [out] caption 字幕信息	
	virtual bool getCaption(Json::Value& caption)
		COMPONENT_UNIMPLEMENTED_OPERATION
	
	/// 查询文件流内动检时间段信息
	/// \param [in] region 窗口信息 Polygon数组
	/// \param [out] timeSections 时间段信息	是否跨天
	virtual bool motionMatch(Json::Value& region, Json::Value& timeSections)
		COMPONENT_UNIMPLEMENTED_OPERATION	
	
	/// 设置播放时间段
	/// \param [in] timeSections
	virtual bool setPlayTimeSections(Json::Value& timeSections)
		COMPONENT_UNIMPLEMENTED_OPERATION
	
	/// 绑定数据接收者
	virtual bool attach(Proc proc)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 解除绑定
	virtual bool detach(Proc proc, bool wait = true)
		COMPONENT_UNIMPLEMENTED_OPERATION
	
	/// 跳转到指定时间附近的I帧
	/// \param [in] time 时间
	virtual bool seekByTime(Infra::CTime const& time)
		COMPONENT_UNIMPLEMENTED_OPERATION
	
	/// 设置速率
	/// \param [in] speed 速度，负数表示倒放
	/// \param [in] isIFrame 是否只传I帧
	virtual bool setSpeed(float speed, bool isIFrame = false)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 恢复播放
	virtual bool play()
		COMPONENT_UNIMPLEMENTED_OPERATION	

	/// 暂停播放
	virtual bool pause()
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 查找指定帧信息
	/// \param [in] condition 需要获取帧的限制条件，参加《大华信交换格式-存储分册》
    /// \param [out] infos 帧信息，参加《大华信息交换格式-存储分册》
    /// \return true 成功 false 失败
	virtual bool getFrameInfo(Json::Value condition, Json::Value& infos)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 设置标签信息
	/// \param [in] tags 标签，详见大华信息交换格式
	virtual bool setTags(const Json::Value& tags)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 清除标签信息
	/// \param [in] tags 标签，详见大华信息交换格式
	virtual bool clearTags(const Json::Value& tags)
		COMPONENT_UNIMPLEMENTED_OPERATION
		
    DAHUA_COMPONENT_FUNCTION_REVSERVED(15)
};
/// 定义 IFileStream 的智能指针
typedef Component::TComPtr<IFileStream> IFileStreamPtr;
	
}//namespace Stream
}//namespace Dahua

#endif //__STREAM_UNISTREAM_FILE_STREAM_H__
