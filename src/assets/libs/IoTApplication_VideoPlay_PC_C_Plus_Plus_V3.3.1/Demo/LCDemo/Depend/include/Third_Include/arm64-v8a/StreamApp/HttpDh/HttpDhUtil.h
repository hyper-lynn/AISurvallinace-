#ifndef __DAHUA_STREAMAPP_HTTPDH_UTIL_H__
#define __DAHUA_STREAMAPP_HTTPDH_UTIL_H__

#include <string>
#include <string.h>
#include "Infra/Function.h"
#include "Component/Unknown.h"
#include "Component/Defs.h"
#include "StreamApp/Defs.h"
#include "NetFramework/Sock.h"
#include "Memory/SharedPtr.h"
#include "StreamSvr/Media/MediaUtil.h"
#include "StreamApp/Defs.h"

namespace Dahua{
namespace StreamApp{

/////////////////////////////////////公共配置/////////////////////////////////////////

///\brief HTTP-DH 请求信息
struct httpDhReqInfo
{
	const char* url;									///< httpDh 请求的url信息
	const char* request;								///< httpDh请求

	httpDhReqInfo(): url(NULL), request(NULL)
	{}

	httpDhReqInfo(const char *httpurl, const char *httpreq) : url(httpurl), request(httpreq)
	{}
};

///\brief 系统所支持的全部HttpDh方法, 注意新增方法则g_httppri_method_str 也需要修改
enum HttpDhMethod
{
	HttpDhMethodPlay = 0, 	///< PLAY命令	
	HttpDhMethodPause,		///< PAUSE命令
	HttpDhMethodKeepAlive,	///< 信令 保活
	HttpDhMethodStop,		///< 停止请求
	HttpDhMethodMax,		///< 未知命令
};

///\brief 回放格式类型
enum HttpDhPlaybackType
{
	HttpDhplaybackTypeFileName,		///< 按文件名回放
	HttpDhplaybackTypeTimeSection,	///< 时间段录像回放
	HttpDhplaybackTypeUnknown,		///<未知类型
};

struct HttpDhPlaybackInfo
{
	///> 按时间段回放信息 
	struct timesection
	{
		Infra::CTime playbackInfoStarttime; ///< 回放开始时间
		Infra::CTime playbackInfoEndtime;	///< 回放结束时间
	};

	HttpDhPlaybackType 	playbackType;		///< 录像回放Url类型，参考 @see HttpDhPlaybackType
	std::string 		fileName;			///< 录像回放文件名称
	timesection			time_section;		///< 录像回放时间信息
	
	HttpDhPlaybackInfo() 
	{
		playbackType = HttpDhplaybackTypeUnknown;

		time_section.playbackInfoStarttime = Infra::CTime(0);
		time_section.playbackInfoEndtime   = Infra::CTime(0);
	}
};

///\brief 位置/时间 间隔信息
struct httpDhRangeInfo
{ 
	///\brief 时间/位置  间隔类型定义
	enum RangeType
	{
		rangeTypeNpt,		///> NPT时间类型
		rangeTypeUnknow,	///> 未知格式
	};

	///\brief 时间范围
	struct rangeNpt
	{
		double start;		///> 开始时间
		double end;			///> 结束时间

		rangeNpt(): start(0.0), end(-1.0)
		{}
	};

	RangeType 			rangeType;		///< 间隔格式,目前只支持npt方式
	rangeNpt	        range;			///< 间隔范围			
	bool 				only_i_frame;	///< 只播放I帧标志, 目前不支持
	float 				speed;			///< 播放速度, 目前不支持
	int             	reserve1[24];	///< 保留参数1
	void			   *reserve2[8];	///< 保留参数2

	httpDhRangeInfo():rangeType(rangeTypeUnknow), only_i_frame(false), speed(1.0)
	{
		memset(reserve1, 0, sizeof(reserve1));
		memset(reserve2, 0, sizeof(reserve2));
	}
};

///\brief 流源运行模式
enum httpDhSessionMode
{
	httpDhSessionModePull = 0,	//拉流模式,默认
	httpDhSessionModePush = 1,  //推流模式,暂不支持
	httpDhSessionModeBoth = 2,  //同时拉流和推流双向模式, 暂只支持语音对讲和可视对讲两种业务
	httpDhSessionModeUnknown,
};

///\ 提供给外部接口的媒体使能标志位
enum httpDhMediaCode
{
	HTTPDH_MEDIA_NONE				= 0x00,	///< 所有媒体使能无效
	HTTPDH_MEDIA_VEDIO				= 0x01, ///< 视频使能位有效
	HTTPDH_MEDIA_AUDIO_ONE			= 0x02,	///< 第一路音频使能位有效
	HTTPDH_MEDIA_AUDIO_SEC			= 0x04,	///< 第二路音音频使能位有效
	HTTPDH_MEDIA_ASSIST				= 0x08,	///< 辅助帧使能位有效
	HTTPDH_MEDIA_META_DATA			= 0x10,	///< 元数据使能位有效
	HTTPDH_MEDIA_TALK				= 0x40,	///< 对讲语音使能位有效
	HTTPDH_MEDIA_DEFAULT			= 0x1F,	///< 视频、第一路音频、第二路音频、辅助帧和元数据使能位有效, 默认值
	HTTPDH_MEDIA_ALL				= 0x7F,	///< 所有媒体使能位有效
	HTTPDH_MEDIA_MAX						///< 非法使能位
};

///\brief HTTP-DH 请求解析的url信息，参数填写错误将导致拉流失败
struct httpDhUrlInfo
{
	///\brief 请求的url类型
	enum UrlType
	{
		UrlTypeLive,									///< 直播
		UrlTypeVod,										///< 点播
		UrlTypeTalk,									///< 语音对讲
		UrlTypeVisualTalk,								///< 可视对讲, 复用同一个连接进行直播和语音对讲
		UrlTypeUnknown,									///< 未知类型
	};

	///\brief 流源媒体打包类型定义
	enum MediaPacketType
	{
		mediaPacketTypeDHInterleaved,	///> 交织的大华帧打包格式
		mediaPacketTypeRtpDH,			///> RTP封装DHAV帧
		mediaPacketTypeNumber,			///> 支持的最大打包个数
	};

	UrlType 			urltype; 		//url类型	
	int  				channel;		//channel信息, 从1开始
	std::string			sourceid;		//流源id, 比如"channel=1&subtype=0"
	MediaPacketType		packettpye;		//打包类型	
	int					encrypttype; 	//加密类型 , 暂时只支持encrypt=2, 填2
	HttpDhMethod 		method;			//对应的请求类型 
	HttpDhPlaybackInfo	playback_info;	//对应的回放请求参数
	uint32_t			trackidFlags;	//媒体trackid标志位
	int					level;			//本地远程通道标志信息, 本地通道不填，远程通道填写2或者大于2的值
	int             	reserve1[22];	//保留参数1
	void			    *reserve2[8];	//保留参数2

	httpDhUrlInfo() : urltype(UrlTypeUnknown), channel(-1), packettpye(mediaPacketTypeNumber), encrypttype(-1), method(HttpDhMethodMax),
		trackidFlags(HTTPDH_MEDIA_MAX), level(-1)
	{
		memset(reserve1, 0, sizeof(reserve1));
		memset(reserve2, 0, sizeof(reserve2));
	}
};


/////////////////////////////////////客户端配置/////////////////////////////////////////

///\brief 客户端配置选项,参见IHttpStreamClient::setConfig()
enum httpDhClientConfig
{
	HttpdhclientConfigUnknown = 0,				///> 未知格式
	HttpdhclientConfigSetServerInfo,			///> 设置连接服务端IP和port,暂只支持IPv4点分形式IP, @see httpDhHostInfo，必须在init之前设置
	HttpdhclientConfigAuthorization,			///> 设置账号信息, @see httpDhClientAuthInfo，必须在init之前设置
	HttpdhclientConfigDataProc,					///> 设置数据回调, @see httpDhDataProcConfig，必须在init之前设置
	HttpdhclientConfigPacketType,				///> 设置打包类型, @see httpDhUrlInfo::MediaPacketType
	HttpdhclientConfigSetKeepAliveInterval,		///> 设置客户端保活时间，默认30S; 配置时opt的值以微秒为单位, int类型
	HttpdhclientConfigRecvBufSize,				///> 设置客户端接收媒体数据的缓冲区大小.opt配置以Byte为单位
	HttpdhclientConfigUsePrivateMethod,         ///> 设置客户端是否使用自定义方法发送请求，opt为bool值，该值默认为false
    HttpdhclientConfigAppendHeaher,             ///> 设置客户端在发送请求时添加指定的字段，opt使用httpDhAppendHeaherConfig
	httpdhclientConfigPlayParam,                ///> 设置客户端录像回放请求参数配置, opt使用httpDhRangeInfo
	HttpdhclientConfigSendBufSize,				///> 设置客户端发送媒体数据的缓冲区大小.opt配置以Byte为单位
	HttpdhclientConfigStreamInfo,				///> 设置客户端流信息配置, @see httpDhStreamInfo, 必须在init之前设置
	HttpdhclientConfigHHYEncrypt,				///> 设置大华帧头0x95字段加密配置, 只允许设置一次 @see StreamSvr::HHYEncryptConfigExt
	HttpdhclientConfigDHEncrypt3,				///> 设置大华帧头0xB5字段码流加密, 只允许设置一次 @see StreamSvr::DHEncrypt3Config
	HttpdhclientConfigMax,
};

///\brief 客户端接收媒体数据回调配置
struct httpDhDataProcConfig
{
	StreamSvr::MediaPacketType dstPacketType;	//目的转码类型，目前只支持转为大华帧, 填StreamSvr::mediaPacketTypeDH，
	StreamSvr::DataProc proc;					//数据回调接口
	httpDhDataProcConfig()
	{
		dstPacketType = StreamSvr::mediaPacketTypeDH;
	}
};

///\brief 设置客户端在发送请求时添加指定的字段，opt使用httpDhAppendHeaherConfig
struct httpDhAppendHeaherConfig
{
	std::string     name;
	std::string     value;
};

///\brief HTTP-DH协议拉流服务端的IP和port
struct httpDhHostInfo
{
	std::string ip;       ///< 目的IP, 暂时只支持IPv4
	uint16_t	port;	  ///< 目的端口
	httpDhHostInfo():port(0)
	{}
};

///\brief 客户端鉴权配置
struct httpDhClientAuthInfo
{
	std::string username;				///< 用户名
	std::string password;				///< 用户密码

	bool		need_wsse;				///< 可选, 是否主动使用WSSE 进行鉴权
	std::string	wsse_password;			///< WSSE认证密码
	std::string wsse_created_time;		///< WSSE认证时间戳，需要填写UTC时间，精确到秒，格式如 "2018-07-24T19:20:30Z"

	httpDhClientAuthInfo()
	{
		need_wsse = true;
	}
};

///\brief 客户端流信息处理配置, HttpdhclientConfigStreamInfo
struct httpDhStreamInfo
{
	StreamApp::StreamEventProc		stream_info_proc;	///< StreamInfoProc, streamInfo回调处理函数配置
	std::string						request_id;			///< 全链路唯一标示request_id
	uint32_t						eventmask;			///< 流信息事件不同功能使能位选项, @see enum StreamEvent
	uint32_t 						lostduration;		///< 丢帧的周期性检测时间, 单位秒, 表明丢帧的开始后会进行多长时间的检测, 由应用配置
	int             				reserved1[8];		///< 保留字节, 后续扩展使用
	void             				*reserved2[4];		///< 保留字节, 后续扩展使用
	httpDhStreamInfo()
	{
		eventmask	  = 0;
		lostduration  = DEFAULT_CHECKLOSTFRAME_DURATION;
		memset(reserved1, 0, sizeof(reserved1));
		memset(reserved2, 0, sizeof(reserved2));
	}
};

///\brief HTTP-DH协议拉流客户端连接的信息
struct httpDhConnectInfo
{
	const char		*request_id;	///< 全链路唯一标示request_id
	uint32_t    	requestid_len; 	///< 全链路唯一标示request_id长度

	const char		*localip;		///< 本地ip
	uint32_t    	localip_len; 	///< 本地ip字符串长度
	uint16_t		localport;	  	///< 本地端口

	const char		*remoteip;		///< 远端ip
	uint32_t    	remoteip_len; 	///< 远端ip字符串长度
	uint16_t		remoteport;	  	///< 远端端口
	
	uint32_t		reserve1[4];
	void		   *reserve2[4];
	
	httpDhConnectInfo(): request_id(NULL), requestid_len(0),         localip(NULL), localip_len(0),
		localport(0), remoteip(NULL), remoteip_len(0), remoteport(0)
	{
		memset(reserve1, 0, sizeof(reserve1));
		memset(reserve2, 0, sizeof(reserve2));
	}
};
	
/////////////////////////////////////服务端配置/////////////////////////////////////////


///\brief 服务端配置选项,参见CHttpDhSvr::setConfig()
enum httpDhServerConfig
{
	HttpDhSvrConfigUnknown = 0,					///< 非法配置
	HttpDhSvrConfigUrlProc,						///< HttpDh url处理函数, 回调函数原型@see HttpDhUrlMapProc
	HttpDhSvrConfigHttpDhAuthType,				///< HttpDh认证方法配置, @see httpDhAuthTypeConfig, 默认httpDhAuthTypeWSSE
	HttpDhSvrConfigHHYEncrypt,					///< 配置大华帧头0x95字段加密配置, @see StreamSvr::HHYEncryptConfigExt
	HttpDhSvrConfigMaxConns,					///< 最大连接数配制, @see httpDhMaxConnsConfig
	HttpDhSvrConfigTcpSndBufLen,				///< 配置TCP套接字发送缓冲大小，参数单位:字节
	HttpDhSvrConfigMaxRtpLen,					///< 配置RTP包最大数据长度(RTP头+载荷，Tcp再加4个字节头),默认1460字节,范围(500, 2000)
	HttpDhSvrConfigPlaybackBlock,				///< 录像回放阻塞发送策略, 默认开启, 如果配置不开启, 上层需配套实现控制送帧的频率
	HttpDhSvrConfigSessionEvent,				///< 会话信息事件配置, @see HttpSessionEvent
	HttpDhSvrConfigDHEncrypt3,					///< 配置大华帧头0xB5字段码流加密, @see StreamSvr::DHEncrypt3Config
	HttpDhSvrConfigMax,
};

///\brief Httpdh 服务类型
enum httpDhServerType
{
	httpDhServerNoSock = 0,                     ///< 不开启套接字监听,套接字连接由外部传入
	httpDhServerSockStream,						///< 非加密套接字传输
	httpDhServerSSlStream,						///< TLS 加密套接字传输
};

///\brief 认证类型
enum httpDhAuthTypeConfig
{
	httpDhAuthTypeNull = 0,		///< 不需要认证
	httpDhAuthTypeDigest,	    ///< Digest和WSSE双选认证方式
	httpDhAuthTypeNum,
};

///\brief 托管套接字认证类型
enum httpDhConnnectConfig
{
	DHSESSION_CONFIG_AUTH  = 0,	//默认配置
	DHSESSION_CONFIG_AUTH_NONE,	//不进行权限认证
};

///\brief 会话传输加密码流校验
enum httpDhCheckencrypt
{
	httpDhEncrtptNocheck = 0,	///< 不进行加密码流传输校验
	httpDhEncrtptcheck,			///< 进行加密码流传输校验
};

struct AddDhSessionOption
{
	int						    	session_type;	///< httpDhConnnectConfig枚举，由外部设置鉴权类型
	int								checkencrypt;	///< 会话进行码流加密传输校验
	int             			    reserved1[7];	///< 保留字节, 后续扩展使用
	void             			   *reserved2[4];	///< 保留字节, 后续扩展使用
	AddDhSessionOption()
	{
		session_type = DHSESSION_CONFIG_AUTH;
		checkencrypt = httpDhEncrtptNocheck;
		memset(reserved1, 0, sizeof(reserved1));
		memset(reserved2, 0, sizeof(reserved2));
	}
};

///\brief 客户端鉴权配置
struct httpDhMaxConnsConfig
{
    int         sessions_max;           ///< 服务器会话连接数量限制，默认限制20路
    int         p2p_max;                ///< p2p连接限制
    int         reserved[8];            ///< 预留字段
    httpDhMaxConnsConfig()
    {
        sessions_max = 20;
        p2p_max = -1;

		// 考虑到负数为不限制连接数, 容易前向兼容
        memset(reserved, -1, sizeof(reserved));
    }
};


///\brief URL 处理函数
///\param [in]  httpDhReqInfo*-原始的请求信息
///\param [out] std::string&-存放应用修改后的URL内容指针, 如果字符串为0, 则表示不进行修改, 传入值为空字符串
///\param [out] httpDhUrlInfo*-url解析的信息
///\param [in]  void*-保留参数
///\return 0: url 合法, -1: 非法的url, 返回400错误
typedef Dahua::Infra::TFunction4<int, httpDhReqInfo &, std::string &, httpDhUrlInfo &, void *> HttpDhUrlProc;


///\brief HTTP会话消息回调函数原型, 包括 request & response
///\param [in]	const char*-会话消息指针
///\return	void
typedef Infra::TFunction1<void, const char*> HttpMsgCallBack;


///\biref  流媒体回调给应用的消息事件详细信息
struct EventHttpDhSessionState
{
	enum		statusConfig{NormalDisConnected = 0, AbnormalDisConnected =1, Connect = 2, Paused = 3, StatusUnknown};						
	statusConfig		state;			///< 会话状态，正常断开，异常断开，请求连接，暂停播放状态
	enum		streamType{StreamTypeLive = 0, StreamTypeVod = 1, StreamTypeTalk = 2, StreamTypeVisualTalk = 3, StreamTypeUnknown,};	
	streamType     		type;			///< 会话类型, 包括直播, 点播, 对讲, 可视对讲(对讲+视频业务组成)
	std::string 		sessionId;		///< 会话ID
	int             	reserved1[32];	///< 保留参数1
	void			    *reserved2[4];	///< 保留参数2
	EventHttpDhSessionState()
	{
        state = StatusUnknown;
		type = StreamTypeUnknown;
		memset(reserved1, 0, sizeof(reserved1));
		memset(reserved2, 0, sizeof(reserved2));
	}
};

///\biref  流媒体回调给应用的消息信息
struct InHttpDhMsg
{
	const char *httpdhReqmsg; 						///< httpdh请求的消息
	const char *httpdhRspmsg; 						///< httpdh请求对应的回复消息,暂时不用填NULL
	const struct EventHttpDhSessionState *detail; 	///< httpdh请求的消息的消息事件详细信息
	InHttpDhMsg(): httpdhReqmsg(NULL), httpdhRspmsg(NULL), detail(NULL)
	{}
};

///\biref  应用返回操作结果的错误码给流媒体
enum OperateResult
{
	OPERATE_SUCCESS = 0,  		///< 操作成功
	OPERATE_CHECK_FAILED, 		///< 不符合操作条件
	OPERATE_DEVICE_BUSY,		///< 设备忙线中
	OPERATE_UNKNOWN,			///< 未知结果
};

///\biref  应用返回给流媒体的回复消息结构体
struct OutHttpDhMsg
{
	int		errorcode;   	///< 如果该错误码不等于OPERATE_UNKNOWN,          流媒体会根据该错误码进行组装标准的错误回复, 错误码填写@see enum OperateResult
	int		reserved1[32];	///< 保留参数1
	void	*reserved2[4];	///< 保留参数2
	OutHttpDhMsg()
	{
		errorcode = OPERATE_UNKNOWN;
		memset(reserved1, 0, sizeof(reserved1));
		memset(reserved2, 0, sizeof(reserved2));
	}
};

///\biref 会话信息事件配置
struct HttpSessionEvent
{
	uint32_t  eventmask;				///< 订阅的事件掩码, 按位进行订阅, 见StreamApp::StreamEvent
	uint32_t  lostduration;				///< 丢帧的周期性检测时间, 单位秒, 表明丢帧的开始后会进行多长时间的检测, 由应用配置
	uint32_t  delayduration;			///< 延时的周期性检测时间, 单位秒, 表明丢帧的开始后会进行多长时间的检测, 由应用配置
	uint32_t  delaythreshold;			///< 视频帧延时阈值, 单位毫秒, 延时超过该阈值时会进行统计
	uint32_t  streamtimeoutthreshold;	///< 取流超时阈值, 单位毫秒, 重新取流耗时超过该阈值时会进行上报, 由应用配置
	uint32_t  audiodelaythreshold;		///< 音频帧延时阈值, 单位毫秒, 延时超过该阈值时会进行统计

	int       reserve[6];				///< 保留字节, 后续扩展使用
	void     *reservep[4];				///< 保留字节, 后续扩展使用	

	HttpSessionEvent()
	{
		eventmask	  = 0;
		lostduration  = DEFAULT_CHECKLOSTFRAME_DURATION;
		delayduration = DEFAULT_CHECKFRAMEDELAY_DURATION;
		delaythreshold = DEFAULT_CHECKFRAMEDELAY_VIDEOTHRESHOLD;
		streamtimeoutthreshold = DEFAULT_CHECKSTREAMTIMEOUT_THRESHOLD;
		audiodelaythreshold = DEFAULT_CHECKFRAMEDELAY_AUDIOTHRESHOLD;

		memset(reserve, 0, sizeof(reserve));
		memset(reservep, 0, sizeof(reservep));
	}
};	

///\服务端会话退出原因
enum httpStreamExitMain
{
	// 0 代码逻辑异常导致拉流失败或断开
	dhexitServerError = 0,			///< 服务端逻辑错误, 指走入了不应该走入的逻辑

	// 1-49 网络原因或者客户端主动断开导致拉流失败或断开
	dhexitRecvStopCmd = 1,			///< 收到对方结束请求
	dhexitRecvError,				///< 网络recv错误, 子错误码参照Linux系统定义的错误码
	dhexitSendError,				///< 网络发送错误, 子错误码参照Linux系统定义的错误码
	dhexitSendTimeout,				///< 发送超时	
	dhexitKeepLiveFail,				///< 流源异常，上报了空包	

	// 50-99 客户端请求异常导致拉流失败或断开
	dhexitSeparatorFailed = 50,		///< 码流分离失败
	dhexitBadRequest,				///< 错误的请求
	dhexitUnauthorized,				///< 鉴权失败	

	// 100-149 数据源相关错误导致拉流失败或断开
	dhexitMediaSourceNotFound = 100, 	///< 创建流源失败,常见于上层组件创建失败
	dhexitMediaSourceInitFailed,		///< 初始化流源失败, 常见于上层应用的媒体数据存在异常
	dhexitMediaPlayFailed,				///< 播放失败,常见于回放时客户端请求超出上层返回给流媒体的录像范围, 或者可视对讲流源状态异常
	dhexitMediaPauseFailed,				///< 暂停播放失败,常见于可视对讲流源状态异常
	dhexitMediaSourceDataError,       	///< 上层的数据源上报了空包,且未实现getPacketType 接口指明播放完毕
	dhexitMediaSinkFailed,				///< 上层应用的对讲插槽创建或初始化失败
	dhexitMediaNotEncrypt,				///< 服务端只支持传输加密码流导致失败

	// 150-199 设备配置变更导致拉流失败或断开
	dhexitServerDown = 150,				///< 流媒体服务关闭导致所有会话断开
	dhexitForbidden,					///< 禁止访问, 无通道权限或者密码未初始化
	
};


}
}

#endif // __DAHUA_STREAMAPP_HTTPDH_UTIL_H__

