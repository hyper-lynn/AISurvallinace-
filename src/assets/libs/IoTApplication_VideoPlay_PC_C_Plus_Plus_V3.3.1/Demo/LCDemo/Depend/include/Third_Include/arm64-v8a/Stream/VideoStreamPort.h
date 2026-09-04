#ifndef DAHUA_STREAM_VIDEO_STREAM_PORT_H__
#define DAHUA_STREAM_VIDEO_STREAM_PORT_H__

#include <Component/Unknown.h>
#include <Json/json.h>
#include "Defs.h"
#include "Infra/Signal.h"
#include "Memory/Packet.h"

namespace Dahua {
namespace Stream {

///动态监听取流接口类
class IVideoStreamPort : public Component::IUnknown
{
public:
	/// 组件工厂
	class IFactory : public Component::IFactoryUnknown
	{
	public:
		virtual IVideoStreamPort* instance(int channel, Stream::GroupMode group, Stream::StreamType stream) = 0;

		/// 组件接口ID定义
		static const char* iid(){return "Stream::VideoStreamPort";};
	};

	/// const void* 包的头部数据
	/// int 头部数据长度
	/// CPacket& 视频数据内容
	typedef TSignal3<const void*, int, const Memory::CPacket&> Signal1;
	typedef Signal1::Proc Proc;

protected:
	~IVideoStreamPort() {};

public:
	/// \获取拉流端口和授权信息
	/// \param[out] port 拉流端口
	/// \param[out] auth 授权信息，客户端取流时需要携带此授权信息，一致才能得到流
	virtual bool getAuth(int session, int& port, Infra::CString& auth)
		COMPONENT_UNIMPLEMENTED_OPERATION;

	/// \客户端主动请求断开取流接口
	/// \由于stop协议不支持断开session上的某个拉流连接，因此主动发送stop接口会断开该session上的所有连接
	/// \param[in] session 主动请求断开流的session号
	virtual bool stop(int session)
		COMPONENT_UNIMPLEMENTED_OPERATION;

	/// \断开主连接上的某一路经过授权的取流连接
	/// \param[in] auth 取流时分配的授权信息，不影响同一个session上的其它拉流连接
	virtual bool stopSub(const char* auth)
		COMPONENT_UNIMPLEMENTED_OPERATION;

	/// \获取媒体帧头信息类型，getAuth之后调用
	/// \仅为兼容ITC老设备，流数据帧帧头为ITC自定义结构体时返回"binary"
	/// \默认返回""，流解析时通过该字段来适配
	virtual bool getMediaInfoType(Infra::CString& type)
		COMPONENT_UNIMPLEMENTED_OPERATION;

	/// \开启RPC拉流，使用devVideoEncode.start协议
	/// \param[in] session 连接会话
	/// \param[in] auth    子链接验证信息
	/// \param[in] object  组件对象
	/// \param[in] proc    码流回调函数
	virtual bool startSub(int session, const char* auth, uint32_t object, Proc proc)
		COMPONENT_UNIMPLEMENTED_OPERATION;

	///类中总函数中个数上限为32，包括虚析函数;以后每增加一个函数，预留的函数个数相应地减一个。
	DAHUA_COMPONENT_FUNCTION_REVSERVED(27);
};

typedef Component::TComPtr<IVideoStreamPort> IVideoStreamPortPtr;

} // namespace Stream
} // namespace Dahua

#endif // DAHUA_STREAM_VIDEO_STREAM_PORT_H__
