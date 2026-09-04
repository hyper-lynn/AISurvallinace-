#ifndef __INCLUDE_DAHUA_STREAMAPP_UDPSENDRECV_H__
#define __INCLUDE_DAHUA_STREAMAPP_UDPSENDRECV_H__

#include "StreamSvr/Media/MediaUtil.h"
#include "UdpStreamSender.h"
#include "UdpStreamReceiver.h"

namespace Dahua{

namespace StreamSvr{ class CMediaFrame; }
namespace StreamApp{


///> UDP流发送接收器接口类
class IUdpSendRecver
{
public:
	///\brief UdpSendRecv配置选项
	enum UdpSendRecverConfig
	{
		UdpSendRecverConfigUnknown = 0, 		///< 非法配置
		UdpSendRecverConfigSendBuff, 			///< 设置快速组播发送缓冲大小，单位字节
		UdpSendRecverConfigRecvBuff, 			///< 设置快速组播接收缓冲大小，单位字节
		UdpSendRecverConfigMax,
	};

public:

	///\brief 对象构造函数
	///\param [in] dstPacketType-参考@see dstPacketType定义
	IUdpSendRecver(int dstPacketType){}
	
	///\brief 创建发送接收对象接口
	///\param [in] dstPacketType-参考@see dstPacketType定义
	///\return 发送接收对象指针-成功，NULL-失败
	static IUdpSendRecver *create(int dstPacketType = StreamSvr::mediaPacketTypeRtpRaw);

	///\brief 对象销毁接口
	virtual void destroy();

	///\brief 回调函数绑定接口
	///\param [in] proc - 设定的回调函数
	///\return 0-成功，-1-失败
	virtual int attach(const IUdpStreamReceiver::Proc &proc);

	///\brief sdp解析接口
	///\param [in] sdp - 待解析的sdp媒体
	///\param [out] output - recver中保存解析的媒体信息
	///\param [out] info - sender中保存解析的媒体信息
	///\return 0-成功，-1-失败
	virtual int setSendRecvSdp(const char *sdp, IUdpStreamReceiver::StreamInfoList &output, IUdpStreamSender::mediaInfo &info);

	///\brief 发送功能绑定接口
	///\param [in] fd-套接字句柄
	///\param [in] mediaIndex-媒体索引
	///\param [in] remoteip-远端IP 地址
	///\param [in] remoteport-远端端口
	///\param [in] needClose-套接字是否需要内部关闭
	///\return 0-成功，-1-失败
	virtual int start_send(int fd, int mediaIndex, const char *remoteip, int remoteport, bool needClose = true);

	///\brief 接收功能绑定接口
	///\param [in] fd-套接字句柄
	///\param [in] mediaIndex-媒体索引
	///\param [in] encCfg-媒体配置信息
	///\param [in] remoteip-远端IP 地址
	///\param [in] remoteport-远端端口
	///\param [in] needClose-套接字是否需要内部关闭
	///\return 0-成功，-1-失败
	virtual int start_recv(int fd, int mediaIndex, const IUdpStreamReceiver::EncodeConfig *encCfg, const char *remoteip, int remoteport, bool needClose = true);

	///\brief 数据发送接口
	///\param [in] mediaIndex-媒体索引
	///\param [in] frame-媒体数据
	///\return true-成功，false-失败
	virtual bool send_frame(int mediaIndex, StreamSvr::CMediaFrame const& frame);

	///\brief 数据接收接口
	///\param [in] chn-媒体索引
	///\param [in] frame-媒体数据
	///\return 0-成功，-1-失败
	virtual int recv_frame(int chn, const StreamSvr::CMediaFrame & frame);

	///\brief 停止数据发送接收接口
	///\param [in] mediaIndex-媒体索引
	///\return 0-成功，-1-失败
	virtual int stop_sendrecv(int mediaIndex);

	///\brief 设置UdpSendRecv的配置
	///\param [in] name-配置枚举
	///\param [in] value-配置值
	///\param [in] value-配置值的长度
	///\return 0-ok, -1-failed
	virtual int setConfig(UdpSendRecverConfig name, void *value, int len);

	DAHUA_COMPONENT_FUNCTION_REVSERVED(23)
	
protected:
	///\brief 对象析构函数
	virtual ~IUdpSendRecver(){}
};

}
}

#endif

