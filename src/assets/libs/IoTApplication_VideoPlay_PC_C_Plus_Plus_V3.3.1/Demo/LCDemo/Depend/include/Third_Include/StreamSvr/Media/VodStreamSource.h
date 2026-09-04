#ifndef __INCLUDE_DAHUA_STREAMSVR_VODSTREAMSOURCE_H__
#define __INCLUDE_DAHUA_STREAMSVR_VODSTREAMSOURCE_H__

#include "StreamSvr/Defs.h"
#include "StreamSvr/Media/MediaUtil.h"
#include "Infra/Function.h"
#include "Infra/Time.h"
#include "Infra/Error.h"
#include "Component/Defs.h"

namespace Dahua{
namespace StreamSvr{

///\brief 点播流源
class STREAMSVR_API IVodStreamSource
{
public:
	///\brief  录像流源的设置属性选项
	enum opiontype
	{
		onlyIframe = 0,	    ///<只传输I帧,  value 将会是一个bool 型指针,存储是否使能仅传输I 帧
	};
	
	///\brief 虚析构函数
	virtual ~IVodStreamSource() {}
	
	///\brief 初始化流源
	///\param [in] proc-SDP信息回调
	///\return 0-成功，-1-失败
	virtual int init(EventProc proc) = 0;	
	
	///\brief 开始取点播流
	///\param [in] proc-接收流回调
	///\return 0-成功，-1-失败
	virtual int start(DataProc proc) = 0;
		
	///\brief 停止取点播流
	virtual void stop() = 0;
	
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

    ///\brief 获取流源SSRC
    ///\param [in/out] ssrc-流源SSRC数组
    ///\param [in] ssrcNum-数组长度
    ///\note 为了方便实现，先这么搞一下，后面如果想修改，可以把这个接口做的通用一些
    virtual void getSSRC(uint32_t *ssrc, int &ssrcNum) {ssrcNum = 0;};
    
	///\brief 暂停点播
	///\return 0-成功，-1-失败
	virtual int pause() {return -1;}
	
	///\brief  继续点播
	///\return 0-成功，-1-失败
	virtual int resume(){ return -1;}
	
	///\brief 设置速率
	///\param [in] speed-速率
	///\return 0-成功，-1-失败
	virtual int setSpeed(float speed){ return -1;}
	
	///\brief 定位到指定时间
	///\param [in] time-跳转的时间
	///\return 0-成功，-1-失败	
	virtual int seekByTime(Infra::CTime const& time){ return -1;}
	
	///\brief 跳帧
	///\param [in] direction-为负数表示向前跳帧
	///\param [in] isIFrame-表示是否跳I帧
	///\return 0-成功，-1-失败
	virtual int stepFrame(int direction, bool isIFrame = true){ return -1;}
	
	///\brief 取当前流的时间
	///\param [in/out] time-流时间 
	///\return 0-成功，-1-失败
	virtual int getTime(Infra::CTime& time){ return -1;}
	
	///\brief 取当前速率
	///\param [in/out] speed-获取的当前速率
	///\return 0-成功，-1-失败
	virtual int getSpeed(float& speed){ return -1;}
	
	///\brief 获取文件范围
	///\param [in/out] duration-文件持续时间
	///\return 0-成功，-1-失败
	virtual int getFileRange(uint64_t &duration){ return -1;}
	
	///\brief 获取文件范围
	///\param [in/out] beginTime-文件起始时间
	///\param [in/out] endTime-文件结束时间
	///\return 0-成功，-1-失败
	virtual int getFileRange(Infra::CTime& beginTime, Infra::CTime& endTime){ return -1;}
	
	///\brief 限定流数据的时间，只取流数据的一部分
	///\param [in] startTime-限制的起始时间
	///\param [in] endTime-限制的结束时间
	///\return 0-成功，-1-失败
	virtual int limit(const Infra::CTime &startTime, const Infra::CTime &endTime){ return -1;}

	
	///\brief 获取流源打包类型
	///\return 参考 @see 枚举MediaPacketType
	virtual int getPacketType() = 0;

	///\brief Onvif多play回放场景下，用来处理第二个及后面的play请求,设置limit时间后调用即可发送数据
	///\return true-ok,false-failed
	virtual bool newPlay(){return false;}

	///\brief 获取文件范围
	///\param [in/out] beginPos-文件起始位置
	///\param [in/out] endPos-文件结束位置
	///\return 0-成功，-1-失败
	virtual int getFileRange(int64_t &beginPos, int64_t &endPos){ return -1;}

	///\brief 取当前流的时间
	///\param [in/out] cur_pos-流位置
	///\return 0-成功，-1-失败
	virtual int getCurPos(int64_t &cur_pos){ return -1;}

	///\brief 定位到指定位置
	///\param [in] offsetinbyte-从文件的开头计算的偏移量
	///\return 0-成功，-1-失败	
	virtual int seekByByte(int64_t offsetinbyte){ return -1;}

	///\brief 限定流数据的起始与终止位置，只取流数据的一部分
	///\param [in] startPos-限制的起始位置
	///\param [in] endPos-限制的结束位置
	///\return 0-成功，-1-失败
	virtual int limit(const int64_t &startPos, const int64_t &endPos){return -1;}

	///\brief 向录像流源里设置属性选项,  扩展的流源按需实现
	///\param [in] type- 见opiontype
	///\param [in] value-见opiontype 描述
	///\return 0-成功，-1-失败
	virtual int setOption(opiontype type, void *value){return -1;};

	///\brief 定位到指定分片位置
	///\param [in] index-从文件开头计算的分片索引, 起始值从0 开始
	///\return 0-成功，-1-失败	
	virtual int seekByIndex(int32_t index){ return -1;}

	///\brief 发送缓冲信息通知函数, 每发送完一个帧会回调该接口, 
	///            注意该接口对于数据回调可能会同步调用上来, 网络不好时则进行异步调用
	///\param [in] bufferframeSize- NAA库的缓冲帧数目
	///\param [in] frame- 发送的媒体帧
	///\param [in] reserve- 保留参数
	virtual void sendProc(int bufferframeSize, const CMediaFrame &frame, void *reserve){return;}
	
	DAHUA_COMPONENT_FUNCTION_REVSERVED(12);
};

}//StreamSvr
}//Dahua

#endif  //__INCLUDE_DAHUA_STREAMSVR_VODSTREAMSOURCE_H__
