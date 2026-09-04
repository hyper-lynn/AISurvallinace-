#ifndef __INCLUDED_DAHUA_STREAM_APP_UDPSTREAMSENDER_H__
#define __INCLUDED_DAHUA_STREAM_APP_UDPSTREAMSENDER_H__

#include "StreamSvr/Media/MediaUtil.h"
#include "Component/Unknown.h"

namespace Dahua{
namespace StreamApp{

///\brief 快速组播配置
struct QuickSendConfig
{
	int		sendstrategy;		///< 传输策略
	int     sendRtpLen;         ///< rtp封包大小
	int		reserved[7];		///< 保留字段
	QuickSendConfig()
	{
		sendstrategy = StreamSvr::StrategyNone;
		sendRtpLen = 1456; //使rtp载荷数据长度与之前一致，1440字节
		memset(reserved, 0, sizeof(reserved));
	}
};

///\brief 快速组播均匀发送策略配置
struct QuickSendNaaUniformPolicy
{
    StreamSvr::PolicyParam  param;          ///< NAA发送策略配置
    int                     bitrate;        ///< 码流值，均匀发送必须填正确的码流大小
    int                     bitrateCtrl;    ///< 0-CBR固定码流 1-VBR可变码流
    uint32_t                reserved[6];    ///< 保留字段

    QuickSendNaaUniformPolicy()
    {
        bitrate = 0;
        bitrateCtrl= 0;
        memset(reserved, 0, sizeof(reserved));
    }
};

///\brief 服务端配置选项,参见IUdpStreamSender::setConfig()
enum UdpStreamSenderConfig
{
	UdpStreamSenderConfigUnknown = 0,			///< 非法配置
	UdpStreamSenderConfigWorkMode,				///< 设置转码工作模式，@see StreamSvr::TransformatParameter::WorkMode
	UdpStreamSenderConfigSndBuff,				///< 设置快速组播发送缓冲大小，单位字节
	UdpStreamSenderConfigConnect,				///< 设置udp socket是否需要connect，参数为bool
	UdpStreamSenderConfigTOS,					///< 设置IP头中的tos属性，参数为int, 取整[0, 255]
	UdpStreamSenderConfigMax,
};

class IUdpStreamSender
{
public:

	///\mediaIndex保存sdp中有效媒体的trackID，数组下标表示 sdp中有效的媒体个数
	struct mediaInfo
	{
		struct mediaEnableInfo
		{
			int    mediaIndex;
		}enableinfo[StreamSvr::MaxTrackNum];
		mediaInfo()
		{
			for(int i = 0;i<StreamSvr::MaxTrackNum;i++)
			{
				enableinfo[i].mediaIndex = StreamSvr::MaxTrackNum;
			}
		}
	};

	struct EncodeConfig
	{
		struct EncodeOpt
		{
			int 		mediaIndex; 	//trackID，根据mediaUtil中MaxTrack定义
			char		encode[16]; 	//编码name
			int 		sample; 		//视频默认为90000，可不设置;.
			int 		framerate;		//帧率
			bool		onlyIframe; 	//只发I帧
			int 		frequency;		//音频采样率
		}EncOpt[StreamSvr::MaxTrackNum];
		EncodeConfig()
		{
			for(int i=0;i< StreamSvr::MaxTrackNum;i++)
			{
				EncOpt[i].mediaIndex = StreamSvr::MaxTrackNum;
				memset(EncOpt [i].encode, 0, sizeof(EncOpt [i].encode));
				EncOpt[i].sample = 90000;
				EncOpt[i].framerate = 25;
				EncOpt[i].onlyIframe = false;
				EncOpt[i].frequency = 0;
			}
		}
	};
	

	///\ 对象创建接口
	///\返回一个静态对象
	///\参数：
	///\dstPacketType:打包类型
	static IUdpStreamSender* create(int dstPacketType = StreamSvr::mediaPacketTypeRtpRaw);
	
	///\对象资源释放接口
	virtual void destroy()=0;
	
	///\套接字、媒体、与传输接收端地址绑定
	///\参数：
	///\sock:外部配置好的fd
	///\mediaIndex:媒体索引
	///\remoteIp:远端地址
	///\remotePort:远端端口
	virtual bool attach( int sock, int mediaIndex, const char* remoteIp, const int remotePort, bool needClose = true)=0;
	
	///\移除绑定的传输通道
	///\参数：
	///\mediaIndex:媒体索引
	virtual bool detach(int mediaIndex)=0;
	
	///\获取转码后数据并发送
	///\参数：
	///\mediaIndex:媒体索引
	///\frame:帧数据
	virtual bool put( int mediaIndex, StreamSvr::CMediaFrame const& frame )=0;
	
	///\解析sdp媒体数据
	///\参数：
	///\sdp:媒体信息
	///\info:保存有效媒体索引
	///\retunn -1  解析失败
	///\retunn 非零  解析成功，返回解析到的媒体数
	virtual int getMediaNumFromSdp(const char* sdp, mediaInfo &info)=0;
	
	///\配置转换媒体信息
	///\参数：
	///\enc:配置信息
	///\info:保存有效媒体索引
	///\retunn -1  解析失败
	///\retunn 非零  解析成功，返回解析到的媒体数
	virtual int setEncodeConfigToPackpacket (EncodeConfig &enc, mediaInfo &info)=0;

	///\brief 初始化通道信息
	///\param [in] channel-通道号
	///\param [in] streamtype-码流类型
	///\return 0-ok, -1-failed
	virtual int initChannelInfo(int channel, int streamtype)=0;

	///\brief 用户设置快速组播配置参数
	///\param [in] cfg-配置名称
	///\return 0-ok, -1-failed
	virtual int setConfig(QuickSendConfig& cfg)=0;
	
protected:
	virtual ~IUdpStreamSender(){}

public:

    ///\brief 用户设置快速组播NAA均匀发送配置
	///\param [in] policy-策略配置
	///\return 0-ok, -1-failed
	virtual int setNaaUniformPolicy(QuickSendNaaUniformPolicy& policy)
	    COMPONENT_UNIMPLEMENTED_OPERATION_RETURN_INT

	///\brief 设置UdpStreamSender的配置
	///\param [in] name-配置枚举
	///\param [in] value-配置值
	///\param [in] value-配置值的长度
	///\return 0-ok, -1-failed
	virtual int setConfig(UdpStreamSenderConfig name, void *value, int len)
		COMPONENT_UNIMPLEMENTED_OPERATION_RETURN_INT

	///\套接字、媒体、与传输接收端地址绑定
	///\参数：
	///\sock:外部配置好的fd
	///\mediaIndex:媒体索引
	///\remoteIp:远端地址
	///\remotePort:远端端口
	virtual bool attach( Memory::TSharedPtr<NetFramework::CSock>& sock, int mediaIndex, const char* remoteIp, const int remotePort, bool needClose = true)
		COMPONENT_UNIMPLEMENTED_OPERATION

	DAHUA_COMPONENT_FUNCTION_REVSERVED(20)

};

}//namespace StreamApp
}//namespace Dahua

#endif
