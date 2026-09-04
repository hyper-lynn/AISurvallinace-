//
//  "$Id: DevVideoEnc.h 47583 2012-01-11 05:50:36Z qin_fenglin $"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef __DAHUA_STREAMAPP_REMOTE_FILE_H__
#define __DAHUA_STREAMAPP_REMOTE_FILE_H__

#include "Component/Unknown.h"
#include "StreamSvr/Media/MediaUtil.h"
#include "Infra/Signal.h"
#include "Infra/String.h"
#include "HlsUtil.h"

namespace Dahua{
namespace StreamApp{

/// \brief HLS 点播流源基类
class IRemoteFile : public Component::IUnknown
{
public:
	typedef Infra::TSignal2<int, StreamSvr::CMediaFrame&>Signal;
	typedef	Signal::Proc Proc;
	
	/// 组件工厂
	class IFactory : public Component::IFactoryUnknown
	{
	public:
		virtual IRemoteFile* create(const std::string &url) = 0;

		/// 组件接口ID定义
		static const char* iid(){return "RemoteFile";};
	};

public:
	virtual ~IRemoteFile(){};

	///\brief 文件流源初始化函数
	///\param [in] proc-传输数据的回调函数
	///\return true-ok, false-failed
	virtual bool start(Proc proc)
		COMPONENT_UNIMPLEMENTED_OPERATION;

	///\brief  停止取码流, 关闭取数据,如果有注册InitEventProc 函数则该接口
	///\           也需要停止InitEventProc 的回调
	///\param [in] proc-回调函数
	///\return true-ok, false-failed
	virtual bool stop(Proc proc)
		COMPONENT_UNIMPLEMENTED_OPERATION;

	///\brief  暂停取码流
	///\return true-ok, false-failed
	virtual bool pause()
		COMPONENT_UNIMPLEMENTED_OPERATION;

	///\brief  设置传输速度,开始取码流
	///\param [in] speed-传输的速度
	///\return true-ok, false-failed
	virtual bool setSpeed(float speed)
		COMPONENT_UNIMPLEMENTED_OPERATION;

	///\brief 文件数据是否已传输完成
	///\return true-已传输完成, false-未传输完成
	virtual bool isFilePlayover()
		COMPONENT_UNIMPLEMENTED_OPERATION

	///\brief 获得文件的分片信息
	///\param [out] sliceinfo-每一个分片的时间长度信息, 单位ms
	///\param [out] starttime-文件的起始时间, 按2010-02-19T14:54:23.031+08:00(时区) 提供,
	///\                                          该值有效则填入m3u8列表中, m3u8 列表不需要该字段传入空字符串即可
	///\param [out] reserve-保留字段
	///\return true-成功, false-失败
	virtual bool getSliceinfo(std::vector<uint64_t> &sliceinfo, std::string &starttime, void *reserve)
		COMPONENT_UNIMPLEMENTED_OPERATION

	///\brief 注册初始化sdp 信息的回调函数, 该接口注册成功说明sdp 信息由上层
	///\          通过回调传出, 此时不需要回调数据, 直到调用restart 接口开始传输数据  
	///\          本地录像码流可以不需要实现本函数
	///\param [in] proc-回调函数
	///\return true-ok, false-failed
	virtual bool registerIniteventproc(InitEventProc proc)
		COMPONENT_UNIMPLEMENTED_OPERATION

	///\brief 从文件开始位置开始传输数据
	///\return true-ok, false-failed
	virtual bool restart()
		COMPONENT_UNIMPLEMENTED_OPERATION

	///\brief 定位到指定索引分片附近的I帧
	///\return true-ok, false-failed
	virtual bool seekByIndex(int32_t index)
	    COMPONENT_UNIMPLEMENTED_OPERATION

	///\brief 从当前的回放位置继续点播
	///\return true-ok, false-failed
	virtual bool resume()
	    COMPONENT_UNIMPLEMENTED_OPERATION

	///类中总函数中个数上限为15，包括虚析函数;以后每增加一个函数，预留的函数个数相应地减一个。
	DAHUA_COMPONENT_FUNCTION_REVSERVED(15);
};

typedef Component::TComPtr<IRemoteFile> IRemoteFilePtr;

} // namespace StreamApp
} //namespace Dahua

#endif// __DAHUA_STREAMAPP_REMOTE_FILE_H__

