#ifndef __INCLUDE_DAHUA_STREAMAPP_UDPMEDIASENDER_H_
#define __INCLUDE_DAHUA_STREAMAPP_UDPMEDIASENDER_H_

#include "StreamApp/Defs.h"
#include "Component/Unknown.h"

// using namespace Dahua;

namespace Dahua{
namespace StreamApp{

typedef enum
{
	AUDIO_ONLY = 0,  	//仅指定音频
	VIDEO_ONLY,			//仅指定视频
	AUDIO_VIDEO,		//指定音视频	
}MEDIA_TYPE;

typedef struct {
	char 			ip[64];		//远端IP
	int				port;		//远端端口
	int				ttl;		//ttl值
	MEDIA_TYPE		type;		//媒体类型
}ADDRESS_INFO;

typedef enum 
{
	ONVIF,			//Onvif
	OTHER,			//Other
}MODULE_TYPE;

typedef enum 
{
	RTP_PACKET = 0,
	TS_PACKET,
	UNKNOW_PACKET,
}PACKET_TYPE;

///\brief 快速组播发送端配置
enum mediasender_config_t
{
	mediaSendStrategy,			///< 发送策略，参数见ConfigUdpSendStrategy@RtspUtil.h
	mediaSendRtpLen,            ///< RTP封包大小(RTP头+载荷)，默认值1456字节
	mediaSendNaaSendPolicy,     ///< NAA发送策略，目前适用于UDP均匀发送，参数见PolicyParam@RtspUtil.h
	mediaSendAddMembership,     ///< 发送端加入组播组，特殊场景才使用,参数true-false
	mediaSendBuff,				///< 发送缓存大小，单位字节
};
	
class STREAMAPP_API IUdpMediaSender: public Component::IUnknown
{
public:
	/// 组件工厂
	class IFactory : public Component::IFactoryUnknown
	{
	public:
		/// 取 IUdpMediaSender 对象实例
		/// 打开实时数据源
		/// \param [in] channle 媒体通道号[in] stream_type 媒体码流类型		
		virtual IUdpMediaSender* instance(int channel, int stream_type, PACKET_TYPE packet_type, MODULE_TYPE attr) = 0;

		/// 组件接口ID定义
		static const char* iid() {return "StreamApp.UdpMediaSender";};
	};	
public:	
	//析构函数
	virtual ~IUdpMediaSender() {};

	//使能音视频组播传输
	//返回值: true成功 false失败
	virtual bool Start(MEDIA_TYPE type)
		COMPONENT_UNIMPLEMENTED_OPERATION

	//停止音视频组播传输
	//返回值: true成功 false失败
	virtual bool Stop(MEDIA_TYPE type)
		COMPONENT_UNIMPLEMENTED_OPERATION

	//添加传输目的地址。
	//如果同时需向多个出口ip发送，每个出口ip都必须制定；
	//如果只是向一个出口ip发送，则出口ip可不填，则向默认出口ip发送。
	//参数：addr_info：目的地址数组指针。
	//		size:		数组大小
	//		local_ip：出口ip。
	//返回值：0成功，-1失败。
	virtual int AddTransfDst(const ADDRESS_INFO* addr_info, int size, const char* local_ip = NULL )
		COMPONENT_UNIMPLEMENTED_OPERATION

	//删除传输目的地址。
	//删除时，参数必须与添加时的参数一致。
	//参数：addr_info：目的地址数组指针。
	//		size:	数组大小
	//			local_ip：出口ip。
	//返回值：0成功，-1失败。
	virtual int DelTransfDst(const ADDRESS_INFO* addr_info, int size, const char* local_ip = NULL )
		COMPONENT_UNIMPLEMENTED_OPERATION
	
	//修正传输的目的地址
	//参数：[in] new_info 新的传输地址
	//		[in] old_info 老的传输地址
	//返回值：-1失败 0成功
	virtual int Modify(const ADDRESS_INFO& new_info, const ADDRESS_INFO& old_info)
		COMPONENT_UNIMPLEMENTED_OPERATION

	//删除的就是对应的地址信息 同时会取消发送
	virtual int Clean(MEDIA_TYPE type)
		COMPONENT_UNIMPLEMENTED_OPERATION
	
	enum 
	{
		AudioVideoDisable = -1,
		VideoEnable = 1,
		AudioEnable,
		AudioVideoEnable,
	};
	//获取该通道以及对应码流类型的状态信息
	//返回值：>0 工作状态  <0 非工作状态
	//		  1:视频使能 2：音频使能 3：音视频使能
	virtual int GetStatus()
		COMPONENT_UNIMPLEMENTED_OPERATION

	///\brief 用户设置快速组播配置参数
	///\param [in] name-配置名称
	///\param [in] value-配置的值
	///\return 0-ok, -1-failed
	virtual int SetConfig(mediasender_config_t name, void *value)
		COMPONENT_UNIMPLEMENTED_OPERATION

	///\brief 设置多播发送的本地接口,必须先SetConfig开启mediaSendAddMembership
	///\param [in] addr_info-AddTransfDst接口添加过的媒体地址
	///\param [in] ip_h，绑定组播本地接口,一般传入INADDR_ANY
	///return 0-ok, -1-failed
	virtual int SetMulticastIF( const ADDRESS_INFO* addr_info, uint32_t ip_h )
	    COMPONENT_UNIMPLEMENTED_OPERATION_RETURN_INT

	DAHUA_COMPONENT_FUNCTION_REVSERVED(23)
};

}//StreamApp
}//Dahua

#endif //__INCLUDE_DAHUA_STREAMAPP_UDPMEDIASENDER_H_
