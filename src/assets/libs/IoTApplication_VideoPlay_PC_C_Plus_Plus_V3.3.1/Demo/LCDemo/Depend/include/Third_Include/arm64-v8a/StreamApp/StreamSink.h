#ifndef __INCLUDE_DAHUA_STREAMAPP_STREAMSINK_H__
#define __INCLUDE_DAHUA_STREAMAPP_STREAMSINK_H__

#include "StreamApp/Defs.h"
#include "StreamSvr/Util/MediaFrame.h"
#include "StreamSvr/Media/MediaUtil.h"
#include "Component/Unknown.h"
#include "StreamSvr/Protocol/SdpParser.h"

namespace Dahua{
	namespace StreamApp{

///\brief 数据槽创建接口原型
///\param [in] const char*-槽标识，业务根据特定的规则进行解析该标识
///\return 成功-数据槽指针，该指针通过destroy释放; 失败-NULL指针
class IStreamSink;
typedef Infra::TFunction1<IStreamSink*, const char* > SinkCreateProc;
typedef Infra::TFunction2<int, int, const StreamSvr::TransformatParameter*> SinkEventProc;

///\brief 流数据槽
class STREAMAPP_API IStreamSink
{
public:
	///\brief 虚析构函数
	virtual ~IStreamSink(){};
public:
	///\brief 初始化数据槽
	///\param [in] proc-槽事件回调函数
	virtual int init(SinkEventProc proc) = 0;

	///\brief 向数据槽填充数据
	virtual int put(int mediaIndex, StreamSvr::CMediaFrame& frame) = 0;

	///\brief 获取该数据槽要求填入的包类型
	///\return 参考 @see 枚举MediaPacketType
	virtual int getPacketType() = 0;

	///\brief 使能对应的媒体索引
	///\param [in] mediaIndex-媒体对应的索引号
	///\return 0-ok, -1-failed
	virtual int enableOneMedia(int mediaIndex) = 0;

	///\brief 注销对应的索引的媒体
	///\param [in] mediaIndex-媒体对应的索引号
	///\return 0-ok, -1-failed
	virtual int disableOneMedia(int mediaIndex) = 0;		

	///\brief 释放资源
	virtual void destroy() = 0;

	///\ 获取反向对讲的SSRC信息
	///\ return 返回对讲的SSRC信息
	virtual uint32_t getSSRC(){return 0;};

	///\brief 初始化对讲SDP信息,在流源处初始化的sdp对讲信息，可以在此处进行新增或修改
	///\param [out] sdpparser-传入修改前的sdp信息，传出最终响应的sdp信息
	virtual void initTalkSdp(StreamSvr::CSdpParser &sdpparser){return;};

	DAHUA_COMPONENT_FUNCTION_REVSERVED(24);
};

	}
}
#endif