#ifndef __INCLUDED_DAHUA_STREAMAPP_IMESSAGENOTIFIER_H__
#define __INCLUDED_DAHUA_STREAMAPP_IMESSAGENOTIFIER_H__

#include "Component/Unknown.h"
#include "Component/Defs.h"
#include "StreamApp/Defs.h"
#include "StreamApp/HttpDh/HttpDhUtil.h"

namespace Dahua{
namespace StreamApp{


///\brief MESSAGENOTIFIER流媒体服务消息处理通知组件
class STREAMAPP_API IMessageNotifier: public Component::IUnknown
{
public:
	/// 组件工厂
	class IFactory : public Component::IFactoryUnknown
	{
	public:
		// 创建IMessageNotifier多例组件
		/// \param [in]  sessionId - 会话ID
		/// \return	非NULL-成功，NULL-失败
		virtual IMessageNotifier* create(const std::string &sessionId) = 0;

		// 组件接口ID定义
		static const char* iid() {return "StreamApp::MessageNotifier";}
	};
		
protected:

	/// 析构函数
	virtual ~IMessageNotifier(){}

public:
	///\brief 流媒体服务消息处理通知正在处理状态, 处理非结束业务通知状态
	/// \param	[in]  inMsg  - 流媒体回调给应用的消息信息 @see struct InHttpDhMsg
	/// \param	[out] outMsg - 应用返回给流媒体的回复消息结构体 @see struct OutHttpDhMsg
	///\return	0-成功, -1 失败
	virtual int notifyProcess(const struct InHttpDhMsg &inMsg, struct OutHttpDhMsg &outMsg)
		COMPONENT_UNIMPLEMENTED_OPERATION_RETURN_INT
		
	///\brief 流媒体服务消息处理通知处理结束状态,包括正常结束和异常结束
	/// \param	[in]  inMsg  - 流媒体回调给应用的消息信息 @see struct InHttpDhMsg
	/// \param	[out] outMsg - 应用返回给流媒体的回复消息结构体 @see struct OutHttpDhMsg
	///\return	0-成功, -1 失败
	virtual int notifyEnd(const struct InHttpDhMsg &inMsg, struct OutHttpDhMsg &outMsg)
		COMPONENT_UNIMPLEMENTED_OPERATION_RETURN_INT
		
	///\brief MESSAGENOTIFIER流媒体服务消息处理通知组件保留虚接口扩展数量,每增加一个必须减1
	DAHUA_COMPONENT_FUNCTION_REVSERVED(30)
};

typedef Component::TComPtr<IMessageNotifier> IMessageNotifierPtr;

}//namespace StreamApp
}//namespace Dahua

#endif //__INCLUDED_DAHUA_STREAMAPP_IMESSAGENOTIFIER_H__

