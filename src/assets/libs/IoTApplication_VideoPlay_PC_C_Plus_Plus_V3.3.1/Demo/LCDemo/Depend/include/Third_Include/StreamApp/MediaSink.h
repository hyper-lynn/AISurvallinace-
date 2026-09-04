#ifndef __INCLUDE_DAHUA_STREAMAPP_MEDIASINK_H__
#define __INCLUDE_DAHUA_STREAMAPP_MEDIASINK_H__


#include "StreamSink.h"
#include "Component/Unknown.h"
#include "Json/json.h" 

namespace Dahua{
namespace StreamApp{

/// 流数据槽, 用于远程对讲功能, 在url 中含有level = 2 或者更多级对讲时会调用该类
class STREAMAPP_API IMediaSink : public Component::IUnknown
{
public:
	/// 组件工厂
	class IFactory : public Component::IFactoryUnknown
	{
	public:
		/// \brief	创建IMediaSink组件
		/// \param	[in] url-当前数据流的URL
		/// \return	非NULL-成功，NULL-失败
		virtual IMediaSink* create(const std::string &url) = 0;

		/// 组件接口ID定义
		static const char* iid(){return "StreamApp::MediaSink";};
	};

protected:

	virtual ~IMediaSink() {};

public:

	/// \brief	初始化数据槽
	/// \param	[in] proc-槽事件回调函数
	/// \return	0-成功, -1 失败
	virtual int init(SinkEventProc proc)
		COMPONENT_UNIMPLEMENTED_OPERATION_RETURN_INT

	/// \brief 向数据槽填充数据
	/// \param [in]-mediaIndex 当前数据所在的RTSP会话通道号
	/// \param [in]-frame 数据
	/// \return	0-成功, -1 失败
	virtual int put(int mediaIndex, StreamSvr::CMediaFrame& frame)
		COMPONENT_UNIMPLEMENTED_OPERATION_RETURN_INT

	/// \brief 获取音频解码格式能力级
	/// \param [out] formats 传出一个数组，格式详见《DVR信息交换格式》文档
	/// \param [out] recommend 优先推荐格式, 为formats数组中的其中一个单元素值, 可用于媒体格式协商时的推荐或建议值
	virtual bool getCaps(Json::Value &formats, Json::Value &recommend)
		COMPONENT_UNIMPLEMENTED_OPERATION

	DAHUA_COMPONENT_FUNCTION_REVSERVED(29);
};


typedef Component::TComPtr<IMediaSink> IMediaSinkPtr;

} // StreamApp
} // Dahua


#endif //__INCLUDE_DAHUA_STREAMAPP_MEDIASINK_H__
