#ifndef __INCLUDE_DAHUA_STREAMAPP_HTTPSTREAMSINK_H__
#define __INCLUDE_DAHUA_STREAMAPP_HTTPSTREAMSINK_H__


#include "StreamApp/StreamSink.h"
#include "Component/Unknown.h"
#include "Json/value.h"

namespace Dahua{
namespace StreamApp{

/// 流数据槽, 用于HttpDh私有协议收流功能
class STREAMAPP_API IHttpStreamSink : public Component::IUnknown
{
public:
	/// 组件工厂
	class IFactory : public Component::IFactoryUnknown
	{
	public:
		/// \brief	创建IHttpStreamSink组件
		/// \param	[in] url-当前数据流的URL
		/// \return	非NULL-成功，NULL-失败
		virtual IHttpStreamSink* create(const std::string &url) = 0;

		/// 组件接口ID定义
		static const char* iid(){return "StreamApp::HttpStreamSink";};
	};

protected:

	virtual ~IHttpStreamSink() {};

public:

	/// \brief	启动数据槽，开始填充数据
	/// \param	[in] proc-槽事件回调函数
	/// \return	0-成功, -1 失败
	virtual int start(SinkEventProc proc)
		COMPONENT_UNIMPLEMENTED_OPERATION_RETURN_INT

	/// \brief 向数据槽填充数据
	/// \param [in]-mediaIndex 媒体索引
	/// \param [in]-frame 完整的一帧大华帧数据
	/// \return	0-成功, -1 失败
	virtual int put(int mediaIndex, StreamSvr::CMediaFrame& frame)
		COMPONENT_UNIMPLEMENTED_OPERATION_RETURN_INT

	///\brief 通过Json配置获取媒体配置信息
	///\            config["needDecrypt"]  = true(bool), 获取对应媒体是否需要进行解密, 默认会进行数据解密
	///\param [out] config 服务端接收数据的配置
	///\return	0-成功, -1 失败
	virtual int getConfig(Json::Value& config)
		COMPONENT_UNIMPLEMENTED_OPERATION_RETURN_INT
	
	///\brief 停止向数据槽填充数据, 组件内部资源可以释放但组件不释放, 由上层释放, 保证可以再次start
	///\brief 该接口供需要解码播放的设备使用
	///\return	0-成功, -1 失败
	virtual int stop()
		COMPONENT_UNIMPLEMENTED_OPERATION_RETURN_INT

	DAHUA_COMPONENT_FUNCTION_REVSERVED(28);
};


typedef Component::TComPtr<IHttpStreamSink> IHttpStreamSinkPtr;

} // StreamApp
} // Dahua


#endif //__INCLUDE_DAHUA_STREAMAPP_HTTPSTREAMSINK_H__
