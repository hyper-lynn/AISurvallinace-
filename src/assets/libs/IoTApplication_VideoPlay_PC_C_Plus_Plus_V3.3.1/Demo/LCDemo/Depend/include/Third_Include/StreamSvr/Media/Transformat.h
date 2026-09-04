#ifndef __INCLUDE_DAHUA_STREAMSVR_TRANSFORMAT_H__
#define __INCLUDE_DAHUA_STREAMSVR_TRANSFORMAT_H__

#include "StreamSvr/Defs.h"
#include "StreamSvr/Media/MediaUtil.h"
#include "StreamSvr/Util/MediaFrame.h"
#include "StreamSvr/Transport/MediaAdapter.h"
#include "Memory/SharedPtr.h"
#include "Component/Unknown.h"

namespace Dahua{
namespace StreamSvr{

///\brief 转码接口类
class STREAMSVR_API ITransformat
{
public:
	///\brief 析构函数
	virtual ~ITransformat(){};
	
public:
	///\brief 设置参数接口
	///\param [in] parameter-转码参数
	///\return 0-成功，-1-失败
	virtual int setParameter(const TransformatParameterEx& parameter){return -1;}
	
	///\brief 输入一帧或一包，用于转码
	///\param [in] mediaIndex-媒体的索引号
	///\param [in] frame-待转码的数据包
	///\return 1-转码完成，可以调用getPacket提取数据，0-转码未完成，数据不足，-1-错误
	virtual int putPacket(int mediaIndex, CMediaFrame &frame) = 0;
	
	///\brief 获取转码好的数据
	///\param [in] mediaIndex-媒体的索引号
	///\param [in/out] frame-转码完成的帧/数据包
	///\return 0-获取成功， -1-获取失败
	virtual int getPacket(int mediaIndex, CMediaFrame &frame) = 0;
	
	///\brief 获取转码好的数据
	///\param [in] mediaIndex-媒体的索引号
	///\param [in/out] trackInfo-媒体track信息，主要用于RTP统计
	///\return 0-获取成功， -1-获取失败,参数trackId无效
	virtual int getTrackInfo(int mediaIndex, TrackInfo &trackInfo){return -1;}
	
	///\brief 设置媒体track对应的交织头中的channel号
	///\param [in] mediaIndex-媒体的索引号
	///\param [in] sendChannelId-该track对应的交织头中的channel号
	virtual int setTrack2Channel(int mediaIndex, uint8_t interleavedChannel){return -1;}

	///\brief 释放资源接口
	virtual void destroy() = 0 ;
	
	///\brief 重置转码参数
	///\param [in] mediaIndex-媒体的索引号
	///\return 0-获取成功， -1-获取失败,参数trackId无效
	virtual int setTrackInfo(int mediaIndex){return -1;}

	///\brief 设置转码对象参数
	///\param [in] type-参数类型,支持{"PKTSIZE"}选项
	///\param [in] value-参数值
	///\param [in] len-参数长度
	///\return 0-ok, -1-failed
	virtual int setOption(const char* optName, void* value,int len){return -1;}

	///\brief 设置媒体适配的接口
	///\param [in] mediaAdapter: 媒体适配句柄
	///\return -1: 设置失败，0: 设置成
	virtual int setMediaAdapter(Memory::TSharedPtr<IMediaAdapter> mediaAdapter){return -1;};

	///\brief 设置帧媒体信息
	///\param [in] inFrame:原始帧
	///\param [out]outFrame:转码后的帧
	virtual void setFrameInfo(CMediaFrame &inFrame, CMediaFrame &outFrame){COPY_MEDIA_FRAME_INFO(outFrame, inFrame);}

	DAHUA_COMPONENT_FUNCTION_REVSERVED(22)
};

/// RTP, TS, PS 码流解封包组件
class IStreamParseCreater: public Component::IUnknown
{
public:
	/// 组件工厂
	class IFactory : public Component::IFactoryUnknown
	{
	public:
		/// 取 IEncryptCreater 对象实例
		virtual IStreamParseCreater* create() = 0;

		/// 组件接口ID定义
		static const char* iid() {return "IStreamSvrStreamParseCreater";}
	};	
public:
	/// 析构函数
	virtual ~IStreamParseCreater(){}
	
public:
	///\brief 创建转码器
	///\param [in] srcPacketType-源码流类型
	///\param [in] dstPacketType-目的码流类型
	///\return 转码器指针
	virtual ITransformat* create(int srcPacketType, int dstPacketType)
		COMPONENT_UNIMPLEMENTED_OPERATION_RETURN_NULL
	
	DAHUA_COMPONENT_FUNCTION_REVSERVED(30)
};

typedef Component::TComPtr<IStreamParseCreater> IStreamParseCreaterPtr;

}//StreamSvr
}//Dahua

#endif  //__INCLUDE_DAHUA_STREAMSVR_TRANSFORMAT_H__
