#ifndef __INCLUDE_DAHUA_STREAMSVR_LIVESTREAMSOURCE_H__
#define __INCLUDE_DAHUA_STREAMSVR_LIVESTREAMSOURCE_H__

#include "StreamSvr/Defs.h"
#include "StreamSvr/Media/MediaUtil.h"
#include "Infra/Function.h"
#include "Infra/Error.h"
#include "Component/Defs.h"

namespace Dahua{
namespace StreamSvr{

///\brief 实时流源
class STREAMSVR_API ILiveStreamSource
{
public:
	///\brief 虚析构函数
	virtual ~ILiveStreamSource() {} 
	
	///\brief 初始化流源
	///\param [in] proc-SDP信息回调
	///\return 0-成功，-1-失败
	virtual int init(EventProc proc) = 0;
	
	///\brief 开始取实时流
	///\param [in] proc-接收流回调
	///\return 0-成功，-1-失败
	virtual int start(DataProc proc) = 0;
		
	///\brief 停止取实时流
	virtual void stop() = 0;
	
	///\brief 强制I帧
	///\return 0-成功，-1-失败
	virtual int setIFrame() {return -1;};
	
	///\brief 获取流源打包类型
	///\return 参考 @see 枚举MediaPacketType
	virtual int getPacketType() = 0;

    ///\brief 获取流源SSRC
    ///\param [in/out] ssrc-流源SSRC数组
    ///\param [in] ssrcNum-数组长度
    ///\note 为了方便实现，先这么搞一下，后面如果想修改，可以把这个接口做的通用一些
    virtual void getSSRC(uint32_t *ssrc, int &ssrcNum) {ssrcNum = 0;};

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

	///\brief 配置流源信息
	///\param [in] opt-流源信息配置枚举, 见SourceOpt
	///\param [in] optvalue-流源信息配置值的地址
	///\param [in] valuelen-流源信息配置值的地址长度
	///\return 0-ok, -1-failed
	virtual int setOption(int opt, const void *optvalue, uint32_t valuelen) {return -1;};
	
	DAHUA_COMPONENT_FUNCTION_REVSERVED(11);
};

}//StreamSvr
}//Dahua

#endif  //__INCLUDE_DAHUA_STREAMSVR_LIVESTREAMSOURCE_H__
