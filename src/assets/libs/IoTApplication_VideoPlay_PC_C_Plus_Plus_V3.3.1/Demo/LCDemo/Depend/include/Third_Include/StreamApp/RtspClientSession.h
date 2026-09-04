#ifndef __INCLUDED_DAHUA_STREAM_SVR_RTSP_CLIENT_SESSION_H__
#define __INCLUDED_DAHUA_STREAM_SVR_RTSP_CLIENT_SESSION_H__

#include "Infra/Function.h"
#include "StreamSvr/Protocol/RtspUtil.h"
#include "StreamSvr/Util/MediaFrame.h"
#include "StreamSvr/Media/MediaUtil.h"
#include "StreamSvr/Protocol/SdpParser.h"
#include "StreamApp/Defs.h"
#include "NetFramework/Sock.h"
#include "Memory/SharedPtr.h"
#include "StreamApp/Defs.h"


namespace Dahua{
namespace StreamApp{

///\brief 内嵌类前向声明
class CRtspClientSessionImpl;

struct ConfigData
{
	unsigned int udp_buf_size;			//udp的缓冲区大小, 单位字节
	unsigned int tcp_buf_size;			//tcp的缓冲区大小, 单位字节

	ConfigData():udp_buf_size(0), tcp_buf_size(0)
	{
	}
};

///\biref 客户端发送的第一条请求配置, 暂时只支持配置Anounce 信令,后续可扩展
struct ClientConfigFirsetCmd
{
	StreamSvr::RtspMethod method;     ///< 配置的信令
	int seq;			 			  ///< 请求的序号	
	char reserved[32];       		  ///< 保留字段
	
	ClientConfigFirsetCmd(): method(StreamSvr::rtspMethodOptions), seq(0)
	{
		memset(reserved, 0, sizeof(reserved));
	}
};

//网络自适应缓冲策略
enum NAA_BUFFER_STRATEGY
{
	NAA_BUFFER_DEFAULT = 0,
	NAA_BUFFER_FLUENCY,
	NAA_BUFFER_REALTIME,
};

///\brief 缓冲策略配置结构，
struct stClientConfigNaaStrategy
{
	int buffer_strategy;		//取值见NAA_BUFFER_STRATEGY

	stClientConfigNaaStrategy():buffer_strategy(NAA_BUFFER_DEFAULT)
	{}
};

#define MINIMUM_BUF_SIZE		(8 * 1024)

///\brief 客户端会话接口类
class STREAMAPP_API CRtspClientSession
{
	///\brief 构造函数
	///\param [in] transProtocol-客户端连接方式@see TransProtocol	
	///\param [in] stardand-打包类型是否强制标准型，默认否，表示私有协议(DH Over RTSP、DH Over UDP)优先
	CRtspClientSession(int transProtocol, bool stardand);

	///\brief 析构函数
	~CRtspClientSession();

public:
	///\brief 传输方式
	enum TransProtocol
	{
		transProtocolUdp,			///> UDP单播
		transProtocolTcp,			///> TCP方式
		transProtocolMulticast,		///> UDP组播方式
		transProtocolDhts,			///> Dhts方式, 已废弃
		transProtocolRtspOverHttp,	///> Rtsp Over Http方式
		transProtocolUnknown,		///> 未知格式
	};

	///\brief 客户端发起连接的套接字类型
	enum SockType
	{
		sslStream  = 0,			///> 加密流套接字
		sockStream,				///> 普通流套接字
	};

	///\brief 客户端配置选项,参见CRtspClientSession::setConfig()
	enum ClientConfig
	{
		clientConfigSetSendRtcp,			///> 设置是否发送RTCP; opt值： 1:开启rtcp， 0:关闭rtcp
		clientConfigSetKeepAliveMethod,		///> 设置保活方法, opt的值参见enum RtspMethod
		clientConfigSetKeepAliveInterval,	///> 设置客户端保活时间，默认30S; 配置时opt的值以微秒为单位
		clientConfigSetBackChannel,			///> 设置反向通道，调应用该配置选项，即打开反向通道
		clientConfigEncryptDHFrame,			///> 设置加密大华帧选项. opt的值参见StreamSvr::DHEncryptConfig
		clientConfigRecvBufSize,			///>设置客户端接收媒体数据的缓冲区大小.opt配置以Byte为单位
		clientConfigSetOptimizingFlag,		///>设置是否优化选项， 优化后大华帧头中的媒体校验位等会被去除. opt值： 1:优化,0:不优化
		clientConfigSetPacketType,			///>设置打包类型,详见enum MediaPacketType
		clientConfigFirsetCmd,				///> 设置客户端发送的第一条请求, 详见ClientConfigFirsetCmd
		clientConfigPushFrameEventProc,		///> 订阅推流发送帧事件
		clientConfigNaaStrategy,			///>设置Naa库的传输策略,值结构见stClientConfigNaaStrategy
		clientConfigRedirDisable,			///> 禁止重定向功能配置, 用于上层自己实现重定向功能				
		clientConfigSetRtpNonstandard,	    ///> 设置不标准RTP标示，当该字段为true时，rtp解析时不解析时间戳、marker、payload等值
		clientConfigSetRtpDisorderWindow,	///> 设置RTP滑动窗口配置,适用于UDP传输方式RTP包乱序场景
		clientConfigMessageAliveTime,		///> 设置信令保活时间, 默认10 S
		clientConfigExtraError,             ///> 设置获取扩展错误码使能，类型bool
		clientConfigSendBufSize,			///> 设置客户端发送媒体数据的缓冲区大小.opt配置以字节为单位
		clientConfigMulticastSrcFilter,     ///> 设置开启组播源地址过滤，opt值 true-开启过滤，false-不开启过滤，默认为false
		clientConfigStreamInfo,				///> 设置客户端流信息配置, @see RtspStreamInfo, 必须在init之前设置
		clientConfigSetInitFrameUtc,  		///> 设置帧起始UTC时间,uint64_t, 从GMT 1970-1-1 00:00:00 到某个时刻经过的秒数(CTime.makeTime())
		clientConfigTOS,					///> 设置IP头的TOS信息, int参数, 取整[0, 255], 必须在init之前设置
		clientConfigCheckTransChannel,		///> 设置校验传输通道,opt值 true-开启校验，false-不开启校验，默认为false）软件平台定制需求兼容三方IPC
		clientConfigDHEncrypt3,				///> 设置大华帧头0xB5字段码流加密, 只允许设置一次 @see StreamSvr::DHEncrypt3Config
		clientConfigUnknown,				///> 未知格式
	};

	///\brief RTSP会话消息回调函数原型, 包括 request & response
	///\param [in]	const char*-会话消息指针
	///\return  void
	typedef Infra::TFunction1<void, const char*> MsgCallBack;


	///\brief 对讲信息回调函数原型
	///\param [in]	const TalkInfo&-对讲数据
	///\return  int 0表示成功，非0表示失败
	typedef Infra::TFunction1<int, const StreamSvr::TalkInfo&> TalkInfoCallBack;

	///\brief RTCP包回调函数原型	
	///\param [in]	int-RTCP消息的通道号	
	///\param [in]	const uint8_t*-RTCP消息指针	
	///\param [in]	int-RTCP消息的长度	
	///\return  void
	typedef Infra::TFunction3<void, int, const uint8_t*, int> RtcpCallBack;

	///\brief 客户端流信息处理配置
	struct RtspStreamInfo
	{
		StreamApp::StreamEventProc	stream_info_proc;	///< RtspStreamInfoProc, streamInfo回调处理函数配置
		std::string					request_id;			///< 全链路唯一标示request_id
		uint32_t					eventmask;			///< 流信息事件不同功能使能位选项, @see 见StreamApp::StreamEvent
		uint32_t 					lostduration;		///< 丢帧的周期性检测时间, 单位秒, 表明丢帧的开始后会进行多长时间的检测, 由应用配置
		int             			reserved1[8];		///< 保留字节, 后续扩展使用
		void             			*reserved2[4];		///< 保留字节, 后续扩展使用	
		RtspStreamInfo()
		{
			eventmask	  = 0;
			lostduration = DEFAULT_CHECKLOSTFRAME_DURATION;
			memset(reserved1, 0, sizeof(reserved1));
			memset(reserved2, 0, sizeof(reserved2));
		}
	};

	///\brief Rtsp协议拉流客户端连接的本地IP和port
	struct RtspConnectInfo
	{
		const char		*request_id;	///< 全链路唯一标示request_id
		uint32_t    	requestid_len; 	///< 全链路唯一标示request_id长度

		const char		*localip;		///< 本地ip
		uint32_t    	localip_len; 	///< ip字符串长度
		uint16_t		localport;	  	///< 本地端口

		const char		*remoteip;		///< 远端ip
		uint32_t    	remoteip_len; 	///< 远端ip 字符串长度
		uint16_t		remoteport;	  	///< 远端端口
		
		uint32_t		reserve1[4];
		void		   *reserve2[4];
		
		RtspConnectInfo(): request_id(NULL), requestid_len(0),         localip(NULL), localip_len(0),
			localport(0), remoteip(NULL), remoteip_len(0), remoteport(0)
		{
			memset(reserve1, 0, sizeof(reserve1));
			memset(reserve2, 0, sizeof(reserve2));
		}
	};

public:
	///\brief 创建客户端
	///\param [in] transProtocol-客户端连接方式@see TransProtocol
	///\param [in] stardand-打包类型是否强制标准型，默认否，表示私有协议(DH Over RTSP、DH Over UDP)优先
	///\return 客户端对象-ok, NULL-failed	
	static CRtspClientSession* create(int transProtocol, bool stardand = false);

	///\brief 关闭客户端
	void close();	

public:	
	///\brief 设置客户端为推流模式	
	///\return -1-fail,	0-success
	int setPushMode();

	///\brief 推流模式下设置SDP信息,每次初始化一个媒体
	///\param [in] frame-初始化的码流数据
	///\param [in] stream-媒体号	
	///\return -1-fail,	0-success
	int initSdp(const StreamSvr::CMediaFrame& frame, int stream);

	///\brief 初始化客户端
	///\param [in] rtspUrl-包含ip & port的rtsp url
	///\param [in] ownerID-网络框架分配的ID号 
	///\param [in] sockHandle-已建立连接的TCP套接字
	///\param [in] needClose-是否关闭sockHandle, true-关闭 false-不关闭
	///\param [in] msgCallBack-消息回调
	///\return -1-fail,	0-success
	int init(const char *rtspUrl, long ownerID, int sockHandle = 0, bool needClose = true, MsgCallBack msgCallBack = MsgCallBack());

	///\brief 初始化客户端
	///\param [in] rtspUrl-包含ip & port的rtsp url
	///\param [in] ownerID-网络框架分配的ID号 
	///\param [in] socktype-要发起连接的套接字类型
	///\param [in] newSock-已连接上的套接字
	///\param [in] param-套接字需要的一些参数指针
	///\param [in] needClose-是否由流媒体关闭newSock 所带的套接字句柄, true-关闭 false-不关闭
	///\param [in] msgCallBack-消息回调
	///\return -1-fail,	0-success
	int init(const char *rtspUrl, long ownerID, NetFramework::CSock::SOCKET_TYPE socktype, Memory::TSharedPtr<NetFramework::CSock> &newSock, void *param = NULL, bool needClose = true, CRtspClientSession::MsgCallBack msgCallBack = MsgCallBack());

	///\brief 注册对应目的类型的数据回调
	///\param [in] dstPacketType-对应的转码类型，参考@see MediaUtil.h里面的MediaPacketType
	///\param [in] proc-数据回调
	///\return 0-ok, -1-failed
	int attachDataProc(int dstPacketType, StreamSvr::DataProc proc);

	///\brief 卸载对应目的类型的数据回调
	///\param [in] dstPacketType-对应的转码类型，参考@see MediaUtil.hh里面的MediaPacketType
	///\return 0-ok, -1-failed
	int detachDataProc(int dstPackeyType);

	///\brief 播放媒体
	///\param [in] mediaIndex:媒体索引(0,1,2...)，-1表示所有媒体
	///\return -1-fail,	0-success
	int play(int mediaIndex = -1);

	///\brief 录制媒体
	///\param [in] mediaIndex:媒体索引(0,1,2...)，-1表示所有媒体
	///\return -1-fail,	0-success
	int record(int mediaIndex = -1);

	///\brief 暂停媒体
	///\return -1-fail,	0-success
	int pause();

	///\brief 停止媒体
	///\param [in] mediaIndex:媒体索引(0,1,2...)，-1表示所有媒体
	///\return -1-fail,	0-success
	int stop(int mediaIndex = -1);

	///\brief 设置工作选项
	///\param [in]	option-工作选项,参考@see ClientConfig
	///\param [in]	opt-选项参数指针
	///\param [in]	optLen-选项参数指针所指区域的可访问长度
	///\return -1-fail,	0-success
	int setConfig( int option, const void *opt=NULL, int optLen=0);

	///\brief 设置鉴权信息
	///\param [in]	username-用户名
	///\param [in]	password-密码,无密码可以不填这个参数
	void setAuthorization( const char *username, const char *password=NULL);

	///\brief 设置Rtsp消息头域
	///\param [in]	method-指定要设置的RTSP方法,参考@see RtspUtil.h RtspMethod
	///\param [in]	key-关键字
	///\param [in]	value-值
	///\return -1-fail,	0-success
	int setRtspMsgHeadField( int method, const char *key, const char *value, char policy='r' );

	///\brief 发送自定义的RTSP消息体
	///\param [in]	method-指定要发送的RTSP方法,参考@see RtspUtil.h RtspMethod
	///\param [in]	body-rtsp消息体
	///\return -1-fail,	0-success
	int sendRtspUserMsg( int method, const char *body );

	///\brief 设置发起Setup的媒体，默认发起所有媒体
	///\param [in]	mediaIndex-媒体索引，SDP中所有媒体块的顺序编号(0,1,2,...)
	///\return -1-fail,	0-success
	int setSetupInfo(int mediaIndex);

	///\brief 设置播放信息
	///\param [in] info-时间范围
	///\param [in] speed-播放速度
	///\param [in] iFrameOnly-只播放I帧标志
	///\return -1-fail,	0-success
	int setPlayInfo(const StreamSvr::RangeInfo&info, float speed = 1.0, bool IFrameOnly = false );

	///\brief 获取播放信息
	///\param [in] info-时间范围
	///\return -1-fail,	0-success
	int getPlayInfo(StreamSvr::RangeInfo &info);

	///\brief 获取SDP信息,前向兼容，接口保留
	///\param [in] buf-buffer
	///\param [in/out] bufSize-Buffer的最大长度以及SDP的长度
	///\return -1-fail,	0-success
	int getSdpInfo(char *buf, int &bufSize);

	///\brief 获取SDP信息
	///\return NULL-fail, CSdpParser对象-success
	const StreamSvr::CSdpParser* getSdpParser();

	///\brief 发送对讲数据包, 上层收到MSG_RTSP_PLAY后才可调用该接口
	///\param [in] frame-对讲数据包 
	///\return -1-fail,	0-success
	int put(StreamSvr::CMediaFrame &frame);

	///\brief 发送媒体数据包, 上层收到MSG_RTSP_PLAY后才可调用该接口
	///\param [in] frame-对讲数据包 
	///\param [in] stream-媒体索引
	///\return -1-fail,	0-success
	int put(StreamSvr::CMediaFrame &frame, int stream);

	///\brief 注册对讲信息回调接口
	///\param[in] talkCallBack 对讲信息回调函数
	void regTalkInfoCallBack(TalkInfoCallBack talkCallBack);

	///\brief 注册RTCP回调接口
	///\param[in] rtcpCallBack RTCP信息回调函数
	void regRtcpCallBack(RtcpCallBack rtcpCallBack);

	///\breif onvif对讲时， 客户端须将通道号设置给流媒体，以区分不同的对讲
	///\param[in] channelId 通道号
	void setChannelId(int channel_id);
	
	///\brief 强制I 帧
	///\return true-ok, false-failed
	bool setIFrame();
	
	///\brief 获取媒体的SSRC
	///\param[in] 需要获取SSRC的媒体
	///\return -1-fail, >0 SSRC
	uint32_t getSsrc(int trackid);

	///\brief 查询服务端直播是否支持PAUSE,该接口在setSetupInfo后调用
	///\return -1-fail,	0-success
	int inquirePause();

	///\brief 流媒体在PLAY信令处理时会开启保活，如果上层不发送PLAY信令，需要手动开启保活定时器
	///\return -1-fail,	0-success
	int startAliveTimer();

	///\brief 获取对象的ID
	///\return -1:失败; 其他:对象ID
	long getId();

	///\brief 客户端获取连接信息
	///\param[out] 保存客户端连接信息的地址
	///\return 0-ok, -1-failed
	int getConnectInfo(RtspConnectInfo &connectInfo);
		
private:
	CRtspClientSessionImpl * m_impl;
};

}//StreamSvr
}//Dahua

#endif //__INCLUDED_DAHUA_STREAM_SVR_RTSP_CLIENT_SESSION_H__
