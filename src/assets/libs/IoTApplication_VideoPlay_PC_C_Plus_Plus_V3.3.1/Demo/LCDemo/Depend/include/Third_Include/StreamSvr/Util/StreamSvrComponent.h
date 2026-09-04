#ifndef __INCLUDE_DAHUA_STREAMSVR_COMPONENT_H__
#define __INCLUDE_DAHUA_STREAMSVR_COMPONENT_H__

#include <Component/Unknown.h>
#include "StreamSvr/Defs.h"
#include "NetFramework/Sock.h"
#include "NetFramework/SockAddrStorage.h"

namespace Dahua {
namespace StreamSvr {

///\brief RTP 组装大华帧内容修改器组件
class STREAMSVR_API IDhframeModify:public Component::IUnknown
{
public:
	/// 组件工厂
	class IFactory : public Component::IFactoryUnknown
	{
	public:
		/// 取 IDhframeModify 对象实例
		virtual IDhframeModify* instance() = 0;

		/// 组件接口ID定义
		static const char* iid() {return "IDhframeModify";}
	};	
	
public:
	/// 析构函数
	virtual ~IDhframeModify(){}

public:	
	///\brief 设置osd 字符串长度配置, osd 内容由上层写入
	///\param [in] len-osd长度
	///\return true 成功, false 失败
	virtual bool setOsdConfig(unsigned char len)
		COMPONENT_UNIMPLEMENTED_OPERATION

	///\brief 获得osd 字符串在大华扩展帧头中的长度空间
	///\param [out] len-osd长度
	///\return true 成功, false 失败
	virtual bool getOsdConfig(unsigned char &len)
		COMPONENT_UNIMPLEMENTED_OPERATION

	///\brief 设置是否需要增加大华扩展字段"绝对毫秒时间"
	///\param [in] flag-标记true表示需要增加扩展字段，flase表示不需要
	virtual bool SetMsFlag(bool flag = true)
		COMPONENT_UNIMPLEMENTED_OPERATION
	
	///\brief 获得是否需要增加大华扩展字段"绝对毫秒时间"标记
	///\return true 需要增加,false 不需要
	virtual bool GetMsFlag()
		COMPONENT_UNIMPLEMENTED_OPERATION
		
	///\brief 设置是否需要增加大华丢帧扩展字段
	///\param [in] flag-标记true表示需要增加大华丢帧扩展字段，false表示不需要
	///\return true 成功, false 失败
	virtual bool SetFrameErrorFlag(bool flag = true)
		COMPONENT_UNIMPLEMENTED_OPERATION
	
	///\brief 获取是否需要增加大华丢帧扩展字段
	///\return true :需要增加, false :不需要
	virtual bool GetFrameErrorFlag()
		COMPONENT_UNIMPLEMENTED_OPERATION	

	DAHUA_COMPONENT_FUNCTION_REVSERVED(2)
};


///\brief Dhts 套接字组件封装类
class STREAMSVR_API IDhtsSockConvert:public Component::IUnknown
{
public:
	/// 组件工厂
	class IFactory : public Component::IFactoryUnknown
	{
	public:
		/// 取 IDhtsSockConvert 对象实例
		virtual IDhtsSockConvert* instance() = 0;

		/// 组件接口ID定义
		static const char* iid() {return "StreamSvr.DhtsSockConvert";}
	};	
	
public:
	/// 析构函数
	virtual ~IDhtsSockConvert(){};

public:	
	///\brief 创建dhts 套接字
	///\param [in] sock-套接字指针
	///\return  CDhtsSockConvert 指针, NULL 创建失败
	virtual NetFramework::CSock *createDhtsSock()
		COMPONENT_UNIMPLEMENTED_OPERATION_RETURN_NULL

	///\brief 发起dhts 套接字连接
	///\param [in] sock -dhts套接字
	///\param [in] ip  -连接的ip
	///\return: -1 失败, 0不表示成功, 要在稍后的GetConnectStatus中判断是否成功
	virtual int connect(NetFramework::CSock *sock, NetFramework::CSockAddrStorage ip)
		COMPONENT_UNIMPLEMENTED_OPERATION_RETURN_INT

	///\brief 获取连接的状态，返回值为CDhtsStream::CONNECT_STATUS
	///\param [in] sock - dhts 套接字指针
	///\return CDhtsStream::CONNECT_STATUS
	virtual int getConnectStatus(NetFramework::CSock *sock)
		COMPONENT_UNIMPLEMENTED_OPERATION_RETURN_INT
	
	///\brief DHTS流式数据接收
	///\param [in] sock - dhts 套接字指针
	///\param [out] buf -接收数据缓冲
	///\param [in] len   -接收数据缓冲的长度
	///\param [in] flags-暂时无用
	///\return:  -1 失败, 0 未接收下次再试, 大于0表示接收到的长度
	virtual int Recv(NetFramework::CSock *sock, char *buf, uint32_t len, int flags = 0)
		COMPONENT_UNIMPLEMENTED_OPERATION_RETURN_INT

	///\brief DHTS流式数据发送
	///\param [in] sock-dhts 套接字指针
	///\param [in] buf -原始媒体帧, 为大华帧
	///\param [in] len -发送数据的缓冲
	///\param [in] flags-暂时无用
	///\return:  -1 失败, 0 未发送下次再试, 大于0表示发送的长度
	virtual int Send(NetFramework::CSock *sock, const char * buf, uint32_t len, int flags = 0)
		COMPONENT_UNIMPLEMENTED_OPERATION_RETURN_INT

	DAHUA_COMPONENT_FUNCTION_REVSERVED(26)
};

typedef Component::TComPtr<IDhtsSockConvert> IDhtsSockConvertPtr;


}//StreamSvr
}//Dahua

#endif //__INCLUDE_DAHUA_STREAMSVR_COMPONENT_H__
