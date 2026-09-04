#ifndef __INCLUDE_DAHUA_STREAMAPP_MULTICASTSTREAMCLIENT_H__
#define __INCLUDE_DAHUA_STREAMAPP_MULTICASTSTREAMCLIENT_H__

#include <list>
#include "Infra/Function.h"
#include "Component/Unknown.h"
#include "StreamSvr/Media/MediaUtil.h"

namespace Dahua{

namespace StreamSvr{ class CMediaFrame; }
namespace StreamApp{

///\brief 客户端配置选项
enum UdpStreamReceiverConfig
{
	UdpStreamReceiverConfigUnknown = 0, 		///< 非法配置
	UdpStreamReceiverConfigRecvBuff,			///< 设置快速组播接收缓冲大小，单位字节
	UdpStreamReceiverConfigMulticastSF,         ///< 设置组播源地址过滤，opt值为IP地址，如 "192.168.1.1"
	UdpStreamReceiverConfigDisorderWindow,		///< 设备RTP包乱序重排接收窗口参数
	UdpStreamReceiverConfigMax,
};

/**
	change IMulticastStreamClient into IUdpStreamReceiver
*/

///> UDP流接收器接口类
class IUdpStreamReceiver
{
public:
	///> 客户端类型
	enum StreamType
	{
		StreamTypeTs	= 0,
		StreamTypeRtp 	= 1,
		StreamTypeOther	= 2
	};

	struct EncodeConfig
	{
		int			encode;		//音视频编码配置信息。
		int 		sample;    	//视频默认为90000，可不设置;  音频需要设置采样率.
		int			pt;			//载荷类型
		int			mediaIndex;	//媒体索引，即trackID值
		EncodeConfig()
        {
            encode = -1;
            sample = 90000;
			pt	   = 0;
			mediaIndex = StreamSvr::MaxTrackNum;
        }
	};

	///> 码流回调函数原型
	typedef Infra::TFunction2<void, int, StreamSvr::CMediaFrame const&> Proc;

	//创建对象
	//返回值：成功返回对象指针，失败返回NULL
	static IUdpStreamReceiver* create(StreamType type = StreamTypeTs);

	//销毁对象
	virtual void destory() = 0;

	//注册回调，目前只允许注册一个回调函数
	virtual int attach(const IUdpStreamReceiver::Proc &proc) = 0;

	//启动组播客户端进行接收
	//参数：
	//ip:本地地址，组播时填组播地址
	//port:本地端口，组播时填组播端口
	//mediaIndex:媒体索引，trackID值
	//encCfg:编码配置
	//remoteip:远端地址，组播不用填
	//remoteport:远端端口，组播不用填
	//返回值： 成功 >= 0 ， 失败 < 0
	virtual int start(const char *ip, int port, int mediaIndex, const EncodeConfig *encode_config = NULL, const char *remoteip = NULL, int remoteport = 0){return -1;}

	//启动组播客户端进行接收
	//参数：
	//fd:外部配置好的fd
	//mediaIndex:媒体索引，trackID值
	//encCfg:编码配置
	//remoteip:远端地址，组播不用填
	//remoteport:远端端口，组播不用填
	//返回值： 成功 >= 0 ， 失败 < 0
	virtual int start(int fd, int mediaIndex, const EncodeConfig *encCfg = NULL, const char *remoteip = NULL, int remoteport = 0, bool needClose = true){return -1;}

	//关闭对应的媒体
	//参数：
	//mediaIndex:媒体索引，trackID值
	//返回值： 成功 >= 0 ， 失败 < 0
	virtual int stop(int mediaIndex) = 0;

	///\brief 设置UdpStreamReceiver的配置
	///\param [in] name-配置枚举
	///\param [in] value-配置值
	///\param [in] value-配置值的长度
	///\return 0-ok, -1-failed
	virtual int setConfig(UdpStreamReceiverConfig name, void *value, int len) = 0;

	struct StreamInfo
	{
		StreamType 	 type;
		EncodeConfig enc; // while type is StreamTypeTs enc is invalid!
	};

	typedef std::list<StreamInfo> StreamInfoList;
	//从sdp文本上提取StreamInfo项，并放入output List中
	//参数：
	//sdp:媒体信息
	//output:保存解析出来的媒体编码信息
	static bool extraStreamInfoFromSdp(const char *sdp, StreamInfoList &output);

protected:
	virtual ~IUdpStreamReceiver(){};

public:

	//启动组播客户端进行接收
	//参数：
	//fd:外部配置好的fsock对象
	//mediaIndex:媒体索引，trackID值
	//encCfg:编码配置
	//remoteip:远端地址，组播不用填
	//remoteport:远端端口，组播不用填
	//返回值： 成功 >= 0 ， 失败 < 0
	virtual int start(Memory::TSharedPtr<NetFramework::CSock>& sock, int mediaIndex, const EncodeConfig *encCfg = NULL, const char *remoteip = NULL, int remoteport = 0, bool needClose = true){return -1;}
	
	DAHUA_COMPONENT_FUNCTION_REVSERVED(25)

};

}
}

#endif

