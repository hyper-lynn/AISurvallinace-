#ifndef __INCLUDE_DAHUA_STREAMAPP_STREAM_MODIFY_H__
#define __INCLUDE_DAHUA_STREAMAPP_STREAM_MODIFY_H__

#include <Component/Unknown.h>
#include "StreamApp/Defs.h"
#include "StreamSvr/Protocol/SdpParser.h"
#include "StreamSvr/Util/MediaFrame.h"

namespace Dahua {
namespace StreamApp {

///\brief StreamSource 数据源大华帧码流修改器组件
class STREAMAPP_API IStreamModifier:public Component::IUnknown
{
public:
	/// 组件工厂
	class IFactory : public Component::IFactoryUnknown
	{
	public:
		///\brief 取 IStreamModifier 对象实例
		///\param [in] 流源的id
		///\return IStreamModifier 对象实例
		virtual IStreamModifier* create(const char *srcId) = 0;

		/// 组件接口ID定义
		static const char* iid() {return "IStreamModifier";}
	};	

	///\brief  码流修改回调的事件类型
	enum EventType
	{
		EventDisconect = 0, ///< 通知流源断开
		EventNum,
	};

	///\brief 流源注册到码流修改器的事件回调
	typedef	Infra::TFunction2<void, EventType, void *> EventProc;
public:
	///\brief 析构函数
	virtual ~IStreamModifier(){}

public:	
	///\brief 码流修改器的初始化函数, 在流源初始化时会调用该函数
	///\param [in] Proc-流源接收码流修改器的事件回调函数
	///\return true 成功, false 失败, 如果失败, 会导致流源初始化失败
	virtual bool init(EventProc Proc)
		COMPONENT_UNIMPLEMENTED_OPERATION

	///\brief 流源的sdp 成功通知函数
	///\param [in/out] sdpparse-流源的sdp 信息,如果码流修改器需要修改sdp 可以在此修改
	///\return true 成功, false 失败, 如果失败, 会导致流源初始化失败
	virtual bool initSdp(StreamSvr::CSdpParser &sdpparse)
		COMPONENT_UNIMPLEMENTED_OPERATION

	///\brief 由流源指定ssrc , 如果加密算法需要用到ssrc , 可以在此指定,
	///\         如不需要可以空实现并返回false			
	///\param [in] ssrc-指定的ssrc 数组地址
	///\param [in/out] ssrcNum-传入ssrc 数组的数目, 传出为实际指定的ssrc 数目
	///\return true 成功, false 失败
	virtual bool getSsrc(uint32_t *ssrc, int &ssrcNum)
		COMPONENT_UNIMPLEMENTED_OPERATION
	
	///\brief 将码流进行二次编码修改, 经过编码或者读文件或者转发的流
	///\          通过该接口转换后将送给流媒体库进行打包发送
	///\param [in] mediaindex-传入的媒体帧track , 和sdp 中的track 值一致
	///\param [in] inframe -原始媒体帧, 为大华帧
	///\param [out] outframe-经过二次编码修改后的帧, 如果为空包, 将会丢弃该帧
	///\return true 成功, false 失败
	virtual bool encode(int mediaindex, const StreamSvr::CMediaFrame &inframe, StreamSvr::CMediaFrame &outframe)
		COMPONENT_UNIMPLEMENTED_OPERATION

	///\brief 将码流进行初次解码修改, 通过该接口转换后, 该帧将被流媒体库送去解码
	///\param [in] mediaindex-传入的媒体帧track , 和sdp 中的track 值一致
	///\param [in] inframe -原始媒体帧, 为大华帧
	///\param [out] outframe-经过二次解码修改后的帧, 如果为空包, 将会丢弃该帧
	///\return true 成功, false 失败
	virtual bool decode(int mediaindex, const StreamSvr::CMediaFrame &inframe, StreamSvr::CMediaFrame &outframe)
		COMPONENT_UNIMPLEMENTED_OPERATION
	
	///\brief 停止接口, 流源停止传输码流后通知码流加密器
	///\          该接口需要外部保证可以重复调用
	///\return true 成功, false 失败
	virtual bool stop()
		COMPONENT_UNIMPLEMENTED_OPERATION
	
	///\brief 由上层设置秘钥初始化函数
	///\param [in] config-配置结构指向的内存
	///\param [in] len    -配置结构的大小
	///\return true 成功, false 失败
	virtual bool init(void *config, int len)
		COMPONENT_UNIMPLEMENTED_OPERATION

	///\brief 检验设置的密钥与帧信息中的密钥信息是否匹配
	///\param [in] mediaindex-传入的媒体帧track , 和sdp 中的track 值一致
	///\param [in] inframe -原始媒体帧, 为大华帧
	///\return  -1 密钥校验不匹配， 0 密钥校验匹配 ， 1 未进行密钥校验
	virtual int checkKey(int mediaindex, const StreamSvr::CMediaFrame &inframe)
		COMPONENT_UNIMPLEMENTED_OPERATION_RETURN_INT

	DAHUA_COMPONENT_FUNCTION_REVSERVED(6)
};

typedef Component::TComPtr<IStreamModifier> IStreamModifierPtr;

}//StreamApp
}//Dahua

#endif //__INCLUDE_DAHUA_STREAMAPP_STREAM_MODIFY_H__