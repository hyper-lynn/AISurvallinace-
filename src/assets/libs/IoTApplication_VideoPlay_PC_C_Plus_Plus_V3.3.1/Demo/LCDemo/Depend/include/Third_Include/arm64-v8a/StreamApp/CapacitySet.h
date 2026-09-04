#ifndef __INCLUDED_DAHUA_STREAMAPP_ICAPACITYSET_H__
#define __INCLUDED_DAHUA_STREAMAPP_ICAPACITYSET_H__

#include "Component/Unknown.h"
#include "Component/Defs.h"
#include "StreamApp/Defs.h"
#include "Memory/SharedPtr.h"
#include "Json/value.h"

namespace Dahua{
namespace StreamApp{


///\brief CAPACITYSET流媒体服务能力集组件
class STREAMAPP_API ICapacitySet: public Component::IUnknown
{
public:
	/// 组件工厂
	class IFactory : public Component::IFactoryUnknown
	{
	public:
		// 取ICapacitySet 对象实例
		virtual ICapacitySet* instance() = 0;

		// 组件接口ID定义
		static const char* iid() {return "StreamApp::CapacitySet";}
	};
		
protected:

	/// 析构函数
	virtual ~ICapacitySet(){}

public:
	///\brief 通过Json配置设置流媒体服务协议能力集信息
	///\            config["协议名"]["功能"]       = 是否支持(true或者false), 获取流媒体服务能力集, 目前只支持以下能力设置
	///\            config["httpPrivate"]["live"]  = false(bool), 默认不支持私有协议直播能力, 是否支持依赖于应用IHttpLiveStream组件是否实现
	///\            config["httpPrivate"]["vod"]   = false(bool), 默认不支持私有协议回放能力, 是否支持依赖于应用IHttpVodStream组件是否实现
	///\            config["httpPrivate"]["talk"]  = false(bool), 默认不支持私有协议对讲能力, 是否支持依赖于应用IHttpStreamSink组件是否实现
	///\param [in] config 应用设置的流媒体能力配置
	///\return true-ok, false-failed
	virtual bool setConfigCaps(Json::Value& config)
		COMPONENT_UNIMPLEMENTED_OPERATION

	///\brief 通过Json配置获取流媒体服务协议能力集信息
	///\            config["协议名"]["功能"]       = 是否支持(true或者false), 获取流媒体服务能力集, 目前只支持以下能力获取
	///\            config["httpPrivate"]["live"]  = false(bool), 默认不支持私有协议直播能力, 是否支持依赖于应用IHttpLiveStream组件是否实现
	///\            config["httpPrivate"]["vod"]   = false(bool), 默认不支持私有协议回放能力, 是否支持依赖于应用IHttpVodStream组件是否实现
	///\            config["httpPrivate"]["talk"]  = false(bool), 默认不支持私有协议对讲能力, 是否支持依赖于应用IHttpStreamSink组件是否实现
	///\            config["httpPrivate"]["reusedRtspPort"] = true(bool), 默认支持复用Rtsp监听端口, 是否支持复用Rtsp监听端口
	///\param [out] config 应用获取的流媒体能力配置
	///\return true-ok, false-failed
	virtual bool getConfigCaps(Json::Value& config)
		COMPONENT_UNIMPLEMENTED_OPERATION

	///\brief CAPACITYSET流媒体能力集组件保留虚接口扩展数量,每增加一个必须减1
	DAHUA_COMPONENT_FUNCTION_REVSERVED(30)
};

typedef Component::TComPtr<ICapacitySet> ICapacitySetPtr;

}//namespace StreamApp
}//namespace Dahua

#endif //__INCLUDED_DAHUA_STREAMAPP_ICAPACITYSET_H__

