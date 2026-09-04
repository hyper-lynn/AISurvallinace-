#ifndef __INCLUDED_DAHUA_STREAMSVR_RTSPUTIL_H__
#define __INCLUDED_DAHUA_STREAMSVR_RTSPUTIL_H__

#include <string.h>
#include "Infra/IntTypes.h"
#include "Infra/Function.h"
#include "StreamSvr/Defs.h"
#include "StreamSvr/Protocol/Mikey.h"
#include "Infra/Function.h"
#include "Memory/SharedPtr.h"
#include "Infra/Time.h"


namespace Dahua{
namespace StreamSvr{

///\brief 最大的URL长度
#define MaxUrlLength 1024

///\brief Rtsp回应代码，及文本串。用于快速生成回应。
struct ResponseText
{
	uint32_t 		code;		///> RTSP响应码
	const char 	*textInfo;	///> 响应信息
};

///\brief RTSP方法状态
struct RtspMethodStatus
{
	const char*	method;	///> 方法名
	bool			valid;	///> 是否有效
};

///\brief 系统所支持的全部Rtsp方法
enum RtspMethod
{
	rtspMethodOptions,	///> OPTION命令,支持做保活信令
	rtspMethodDescribe,	///> DESCRIBE命令
	rtspMethodAnnounce,	///> ANNOUNCE命令
	rtspMethodSetUp,		///> SETUP命令
	rtspMethodPlay,		///> PLAY命令	
	rtspMethodRecord,	///> RECORD命令
	rtspMethodPause,		///> PAUSE命令
	rtspMethodTeardown,	///> TEARDOWN命令
	rtspMethodSetParameter,	///> SET_PARAMETER命令
	rtspMethodGetParameter,	///> GET_PARAMETER命令，支持做保活信令
	rtspMethodMax,		///> 未知命令
};

///\brief Rtsp请求RTP传输时采用的传输层协议
enum RtpProtocol
{
	rtpProtocolRtpOverRtsp,	///> 交织方式
	rtpProtocolRtpOverUdp,		///> UDP单播方式
	rtpProtocolRtpOverDHTP,	///> 软件线打包方式
	rtpProtocolTranportAuto,	///> 自动传输
	rtpProtocolMulticast,		///> 组播方式
	rtpProtocolNum,			///> 未知格式
};

///\brief UTC时间格式
struct UtcTime
{
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
	int millisec;
};

///\brief SMPTE格式定义
struct SmpteTime
{
	int smpteTimeHour;		///> 相对文件的相对小时
	int smpteTimeMinute;	///> 相对文件的相对分钟
	int smpteTimeSecond;	///> 相对文件的相对秒
};

///\brief 时间/位置  间隔类型定义
enum RangeType
{
	rangeTypeNpt,		///> NPT时间类型
	rangeTypeClock,		///> Clock时间类型
	rangeTypeByte,		///> 字节位置偏移信息
	rangeTypeSmpte,		///> Smpte时间格式
	rangeTypeSlice,		///> 分片偏移信息, 主要HLS 协议使用
	rangeTypeUnknow,	///> 未知格式
};

///\brief 设置套接字缓冲的场景枚举
enum SendBufScene
{
	SceneSendVodTcp = 0,		///< TCP 回放
	SceneBufNum,
};

///\ breif 定义支持的传输方式
enum TransportType
{
	dhOverTcp = 1 << 0, 	// 6字节+大华帧的传输方式
	rtpOverTcp = 1 << 1,	// TCP传输RTP的方式
	dhOverUdp = 1 << 2,		// UDP传输RTP打包大华帧的方式
	rtpOverUdp = 1 << 3,	// UDP传输标准RTP包的方式
};

///\ breif 定义支持的时间戳同步类型
enum SyncPtsType
{
	NoSyncframe = 0,	///< 不进行时间戳同步
	SyncVXframe,		///< 同步视频帧和辅助帧, 元数据的时间戳
};

///\brief 设置不同场景下套接字缓冲的结构体
struct SceneBuf
{
	int scene;			///< 设置套接字缓冲的场景, 见enum SendBufScene
	int bufflen;		///< 设置的套接字缓冲大小
	int reserver[2];	///< 保留参数

	SceneBuf()
	{
		scene = -1;
		bufflen = 0;
		memset(reserver, 0, sizeof(reserver));
	}
};

//////////////////////////////////////////////服务器相关/////////////////////
enum rtsp_svr_config_t
{
	RtspSvrConfigUnknown,						///< 非法配置
	RtspSvrConfigRtspAuthType,					///< Rtsp认证方法配置
	RtspSvrConfigRtspOverHttpAuthType,			///< RtspOverHttp认证方法配置
	RtspSvrConfigQosDSCP,						///< Qos DSCP配置
	RtspSvrConfigKeepAliveSeconds,				///< 保活超时时间配置，单位:秒
	RtspSvrConfigRtpPortRange,					///< RTP端口范围配置
	RtspSvrConfigUrlMapProc,					///< url映射函数配置
	RtspSvrConfigLiveStreamSourceCreateProc,	///< 直播数据源创建函数配置
	RtspSvrConfigVodStreamSourceCreateProc,		///< 点播数据源创建函数配置
	RtspSvrConfigAuthProc,						///< 设置认证模块创建函数配置	
	RtspSvrConfigSessionsEventProc,				///< Rtsp Session会话事件(如上线，下线)处理接口
	RtspSvrConfigOnvifPlaybackSdpProc,			///< Onvif录像回放sdp获取接口
	RtspSvrConfigMaxConns,						///< 最大连接数配制
	RtspSvrConfigStartChannel,					///< 通道号起始值，填1表示Storage模块接口要求的通道号从1开始。默认通道号从0开始
	RtspSvrConfigHSWXEncrypt,                   ///< 华视微讯大华码流I帧加密配置定义
	RtspSvrConfigNeedRtcp,						///< 是否需要发送Rtcp报文，true-表示发送rtcp， false-表示不发送rtcp
	RtspSvrConfigTcpSndBufLen,					///< 配置TCP套接字发送缓冲大小，参数单位:字节
	RtspSvrConfigTcpRcvBufLen,					///< 配置TCP套接字接收缓冲大小，参数单位:字节
	RtspSvrConfigRtspMsgProc,					///< 设置rtsp消息处理后的回调接口
	RtspSvrConfigExtUrlMapProc,                 ///< 当返回NULL时，交由流媒体默认处理
	RtspSvrConfigOnvifAuthType,                 ///< Onvif接入时认证配置方法
	RtspSvrConfigUdpSendStrategy,               ///< Udp发送策略, 默认普通发送, 一般推荐用均匀发送,见ConfigUdpSendStrategy
	RtspSvrConfigPlaybackBlock,					///< 录像回放阻塞发送策略, 默认开启, 如果配置不开启, 上层需配套实现控制送帧的频率
	RtspSvrConfigHandleLostFrame,			    ///< 订阅TCP发送方式下丢帧事件配置
	RtspSvrConfigOnvifRecvInterval,				///< Onvif语音对讲开启后的接收时间间隔,用以小数据量接收情况下的性能优化
	RtspSvrConfigSubcribeRtspState,				///< 按业务订阅rtsp 状态信息
	RtspSvrConfigChannelAuth,                   ///< 通道认证方法配置
	RtspSvrConfigAuthHookProc,					///< 鉴权钩子函数配置
	RtspSvrConfigSRTPEncrypt,					///< SRTP加密配置
	RtspSvrConfigStreamSendStrategy,			///< 码流发送策略naa参数用户自配置
	RtspSvrConfigSceneBuf,						///< 通过struct SceneBuf设置不同场景的套接字缓冲,该配置优先于RtspSvrConfigTcpSndBufLen
	RtspSvrConfigAuthCreateProc,				///< 用户注册自己的鉴权器创建函数
	RtspSvrConfigMtsWorkMode,					///< 流媒体运行模式，如果走MTS，则流程与通用模式有区别
	RtspSvrConfigSrcTypeProc,					///< URL映射函数，返回值是请求的流源类型	
	RtspSvrConfigStreamSinkCreateProc,			///< 设置Onvif语音对讲数据源创建函数
	RtspSvrConfigRtspMsgPreProc,				///< 设置rtsp消息处理前的回调接口
	RtspSvrConfigTransportCapicity,				///< 设置rtsp支持的传输方式，不设置则都支持
    RtspSvrConfigSendKeepAliveEnable,           ///< 服务器主动发送保活信令使能
    RtspSvrConfigMediaFlowCalc,					///< 服务器流量统计配置, 配置类型为MediaFlowConfig
    RtspSvrConfigUdpSndBufLen,                  ///< 配置UDP套接字发送缓冲大小，参数单位:字节
    RtspSvrConfigUdpRcvBufLen,                  ///< 配置UDP套接字接收缓冲大小，参数单位:字节
	RtspSvrConfigHHYEncrypt,					///< 配置和慧眼项目大华帧头0x95字段加密
	RtspSvrConfigUrlParserProc,					///< 解析URL函数配置
	RtspSvrConfigSendFrameEventProc,			///< 用户注册自己的帧发送事件函数
	RtspSvrConfigListenAddr,                    ///< 配置监听地址
	RtspSvrConfigtransCreateProc,				///< 码流打包器创建函数配置, 用于上层注册自定义打包器
	RtspSvrConfigLowLatency,					///< 画面显示低延时
	RtspSvrConfigSyncPts,						///< 同步时间戳配置, 用于对接开放平台项目
	RtspSvrConfigPushStreamSinkCreateProc,		///< 设置RTSP推流数据槽创建函数
	RtspSvrConfigMaxRtpLen,			            ///< RTP包最大数据长度(RTP头+载荷), MTU的范围是在[576，1500]，请参考MTU范围设置该配置值, 建议默认值1460字节
    RtspSvrConfigNaaSendPolicy,                 ///< NAA发送策略配置，目前适用UDP均匀发送，参见PolicyParam
	RtspSvrConfigRtspOverHttpReqProc,			///< Rtsp Over Http请求解析回调
	RtspSvrConfigMulticastRtcpEnable,			///< 设置RTSP组播时是否开启rtcp, true表示使能，false表示关闭
	RtspSvrConfigMediaCacheEnable,				///< 数据缓冲使能，用于直播出流速度优化，参数类型:int, 值参见MediaCacheEnableByStreamType
	RtspSvrConfigRtpExtraNtp,					///< RTP扩展NTP使能，类型bool
	RtspSvrConfigSdpInitSpeed,					///< 回放初始化sdp 时读数据的速度,默认8 倍速
	RtspSvrConfigSdpConfig,						///< SDP配置,用于设置SDP相关信息
	RtspSvrConfigTcpSendStrategy,               ///< Tcp发送策略，是否开启均匀发送，参数见PolicyParam
	RtspSvrConfigLiveNoreuse,					///< 实时流同一通道数据不复用,使每个客户端拉流的ssrc不一致，用于对接特定的平台
	RtspSvrConfigScaleDropFrame,				///< 用户在Scale回放时，可配置是否丢帧回放, 默认为true
	RtspSvrConfigLowLatencyEx,					///< 画面显示低延时配置，与RtspSvrConfigLowLatency配置相比，扩展性更高
	RtspSvrConfigSessionEvent,					///< 订阅拉流事件信息配置, 配置见RtspSessionEvent
	RtspSvrConfigClockTime,						///< 使能PLAY回复Range字段使用Clock时间，目前只适用Onvif直播拉流，类型为bool
	RtspSvrConfigCharMap,						///< 转义字符映射，类型bool
	RtspSvrConfigDHEncrypt3,					///< 配置大华帧头0xB5字段码流加密 @see StreamSvr::DHEncrypt3Config
};

///< 服务器端静态统计信息枚举，和GetStaticInfo配套使用
enum rtsp_static_config_t
{
	RtspStaticInfoStreamCount,					///< 获取流源的计数，inParam-char*指针，直播流源的content;  outParam-long*指针，外部申请空间
};

///\brief URL映射函数
///\param [in] const char* -原始的URL内容指针
///\param [out] char* -存放映射后的URL 内容地址
///\param [out] int -存放映射后的URL 内容地址长度
///\return const char* 指针转换后的Url(即第2  个参数指针)，转换失败则返回NULL
typedef Dahua::Infra::TFunction3< char*, const char*, char*, int> UrlMapProc;

///\brief URL映射函数
///\param [in] const char* -原始的URL内容指针
///\return const char* URL对应的流源类型，失败则返回dataSourceTypeNumber @see enum DataSourceType
typedef Dahua::Infra::TFunction3< int, const char*, char*, int> SrcTypeProc;

#define PLAY_COUNT_INVALID    0        // Count字段无效
#define PLAY_COUNT_VALID      1        // Count字段有效
struct UrlParserInfo
{
	///\brief Url类型
	enum UrlType
	{
		urlTypeLive,	///> 直播Url
		urlTypeVod, 	///> 点播Url
		urlTypeUnknown, ///> 未知
	};

	///\brief url回放格式类型
	enum UrlPlaybackType
	{
		playbackTypeFileName,	///> 按文件名回放
		playbackTypeToken,		///> 令牌回放
		playbackTypeTimeSection,///> 时间段录像回放
		playbackTypeUnknown,
	};
	
	
	///\brief URL直播信息
	struct LiveInfo
	{
		int	LiveInfoChannel;	///> 通道号, 起始从1 开始
		int	LiveInfoSubtype;	///> 码流类型, 起始从0 开始
		LiveInfo()
		{
			LiveInfoChannel = -1;
			LiveInfoSubtype = -1;
		}
	};


	///\brief 回放信息
	///\note 因语音无法支持有构造的函数包含在联合中，故仅用结构体
	struct PlaybackInfo
	{		
		UrlPlaybackType playbackType;		///> 录像回放Url类型
		int				playbackchannel;	///> 录像回放通道号, 起始从1开始

		///> 按时间段回放信息 
		struct ST_TimeSection
		{
			int 		 playbackInfoSubtype;	///> 码流类型, 起始从0 开始
			Infra::CTime playbackInfoStarttime; ///> 回放开始时间
			Infra::CTime playbackInfoEndtime;	///> 回放结束时间
			int 		 count; 				///> 在没有结束时间的情况下,是否播放完整个文件
		}time_section;

		///> 按令牌回放信息
		struct ST_Token
		{
			char playbackInfoToken[256];
		}token;

		///> 按文件名回放
		struct ST_FileName
		{
			std::string fileName;
		}FileName;
					
		PlaybackInfo() 
		{
			memset(token.playbackInfoToken, 0, sizeof(token.playbackInfoToken));
			
			time_section.playbackInfoStarttime = Infra::CTime(0);
			time_section.playbackInfoEndtime = Infra::CTime(0);
			time_section.count = PLAY_COUNT_INVALID;
			time_section.playbackInfoSubtype = -1;
			
			playbackType = playbackTypeUnknown;
			playbackchannel = -1;
		}

	};

	UrlType 		urltype; 		//url类型	
	LiveInfo 		liveinfo;		//直播信息
	PlaybackInfo	playbackinfo;	//回放信息
	int             reserve[48];	//保留字段

	UrlParserInfo()
	{
		urltype = urlTypeUnknown;
		memset(reserve,0,sizeof(reserve));
	}
	
};

///\biref 会话信息事件配置
struct RtspSessionEvent
{
	uint32_t  eventmask;				///< 订阅的事件掩码, 按位进行订阅,见fstatStreamInfoEvent
	uint32_t  lostduration;				///< 丢帧的周期性检测时间, 单位秒, 表明丢帧的开始后会进行多长时间的检测, 由应用配置
	uint32_t  delayduration;			///< 延时的周期性检测时间, 单位秒, 表明丢帧的开始后会进行多长时间的检测, 由应用配置
	uint32_t  delaythreshold;			///< 视频延时阈值, 单位毫秒, 延时超过该阈值时会进行统计
	uint32_t  streamtimeoutthreshold;	///< 取流超时阈值, 单位毫秒, 重新取流耗时超过该阈值时会进行上报, 由应用配置
	uint32_t  audiodelaythreshold;		///< 音频帧延时阈值, 单位毫秒, 延时超过该阈值时会进行统计

	int       reserve[6];				///< 保留字节, 后续扩展使用
	void     *reservep[4];				///< 保留字节, 后续扩展使用	

	RtspSessionEvent()
	{
		eventmask	   = 0;
		lostduration   = DEFAULT_CHECKLOSTFRAME_DURATION;
		delayduration  = DEFAULT_CHECKFRAMEDELAY_DURATION;
		delaythreshold = DEFAULT_CHECKFRAMEDELAY_VIDEOTHRESHOLD;
		streamtimeoutthreshold = DEFAULT_CHECKSTREAMTIMEOUT_THRESHOLD;
		audiodelaythreshold = DEFAULT_CHECKFRAMEDELAY_AUDIOTHRESHOLD;

		memset(reserve, 0, sizeof(reserve));
		memset(reservep, 0, sizeof(reservep));
	}
};	

///\brief URL解析函数
///\param [in] const char* -原始的URL内容指针
///\param [in] UrlParserInfo& -转换后的url信息
///\param [in] void *  -保留参数
///\param [in] void *  -保留参数

///\return int 转换成功返回0失败返回非0
typedef	Dahua::Infra::TFunction4<int, const char*, UrlParserInfo &, void *, void *> UrlParserProc;



///>brief rtsp 请求的流业务类型
typedef enum{
	streamTalk = 0,		///< rtsp 语音对讲
	streamLive,			///< rtsp 直播
	streamVod,			///< rtsp 点播
}rtsp_stream_type;

///>brief 流量统计配置
struct MediaFlowConfig
{
	int streamtype; ///< 需要进行流量统计的流业务类型, 按位进行订阅, 每一位的意义见rtsp_stream_type
	int loopNocalc;	///< 环回流量是否不纳入统计, 0则统计, 非0则不统计
	int reserve[2]; ///< 保留字段,暂未使用

	MediaFlowConfig()
	{
		streamtype = 0;
		loopNocalc = 0;
		memset(reserve, 0, sizeof(reserve));
	}
};

///>brief 平台接入鉴权方式配置
typedef enum{
	CONFIG_NONE = 0,	//默认配置
	CONFIG_AUTH_NONE,	//不进行权限认证
	CONFIG_UNKNOW,		//未知类型
}rtsp_connect_config_t;

///\brief 认证类型
typedef enum 
{
	authTypeNull,		///< 不需要认证
	authTypeBasic,		///< Basic认证方式
	authTypeDigest,		///< Digest认证方式(摘要)
	authTypeAlter,		///< Digest 和Basic 双选认证方式
	authTypeNum,
}ConfigAuthType;

///\brief 鉴权钩子函数指针
///\param [in] authtype-当前的鉴权类型, 暂未用到,以后扩展使用
///\param [in] request  - RTSP 请求
///\param [in] remoteip- 请求的远程客户端IP
///\param [in] reserve  - 保留参数,以后扩展使用
///\return true: 继续流媒体模块进行鉴权, false: 免鉴权处理
typedef bool (*AuthHookProc) (ConfigAuthType &authtype, const char *request, const char *remoteip, const char *reserve);

///\brief UDP发送策略
typedef enum 
{
	StrategyNone = 0,		///> 普通发送
	StrategyUniform,    	///> 均匀发送
	StrategyNum,
}ConfigUdpSendStrategy;

///\brief 传输策略类型
enum StrategyType
{
	STRATEGY_BEGIN = 0,
	STRATEGY_NONE,			///> 默认策略
	STRATEGY_FLUENCY,		///> 流畅优先
	STRATEGY_REAL,			///> 实时优先
	STRATEGY_QUALITY,		///> 画质优先
	STRATEGY_USEROPTIONS,	///> 用户自配参数
	STRATEGY_END = 9999
};

///\brief 内部策略类型
enum StrategyPolicy
{
	PolicyNone 			= 0,	///> 无策略
	PolicyBitrate 		= 1<<0,	///> 动态调整码率
	PolicyQuality 		= 1<<1,	///> 未实现
	PolicyGOP 			= 1<<2,	///> 未实现
	PolicyFPS 			= 1<<3,	///> 未实现
	PolicyResolution 	= 1<<4,	///> 未实现
	PolicyDropFrame 	= 1<<8,	///> 允许丢帧策略，现在一般采用该策略
};

///\brief NAA码流缓存策略配置
struct ConfigStreamSendStrategy
{
	StrategyType optionStrategy;	///<用户选择采用默认策略，内部提供策略或者自定义策略，详细定义见StrategyType；
	int 	policy; 				///< [AdjustDropFrame],可"|"操作，自适应策略，意义见StrategyPolicy结构体定义
	int 	maxQueueDelay; 			///< [,3*1000,][ms]帧队列最大延迟，丢帧最大延时时间，超过该时间后开始丢帧
	int 	maxDataLength;			///< [,3*1024,][Kbyte]帧队列数据最大长度，表示缓存中能存放的最大数据量 
	int 	threshold; 				///< [,400,maxQueueDelay/2][ms]延迟阈值，丢帧相关参数，该值越大，丢帧越少 
	int 	reserve[20]; 			///< 保留字段
	ConfigStreamSendStrategy()
	{
		optionStrategy = STRATEGY_NONE;
		policy = PolicyNone;
		maxQueueDelay = 0;
		maxDataLength = 8 * 1024;	///<0:采用均分策略;!0:非均分策略时的缓冲区大小; Naa均分策略前的默认值是8M
		threshold = 0;
		memset(reserve, 0, sizeof(reserve));
	}
};

/// \brief 发送策略配置项
enum PolicyItem
{
	HandleNone				= 0, ///< 无策略
	FlowControlByCount 		= 1, ///< 根据包数量来计算控制
	FlowControlByBitrate 	= 2, ///< 根据数据量来计算控制
};

/// \brief 发送策略配置项参数
struct PolicyParam
{
	PolicyItem policy;
	union ParamInfo
	{
		///< FlowControlByCount
		struct CountParam
		{
			int maxDelay;	///< 最大延时(ms), 除特殊场景外，采用默认值即可
			int slot;		///< 系统睡眠精度(ms) 默认20ms
		}countParam;
		
		///< FlowControlByBitrate
		struct BitrateParam
		{
			int maxDelay;	///< 最大延时(ms),除特殊场景外，采用默认值即可
		}bitrateParam;
		int reserve[8];
	} paramInfo;

	PolicyParam()
	{
	    memset(paramInfo.reserve, 0, sizeof(paramInfo.reserve));
        policy = FlowControlByBitrate;
        paramInfo.bitrateParam.maxDelay = 120;
	}
};

///\brief 关闭会话的依据类型
enum CloseType
{
	Closesessionid   = 0,			///> 依据会话id 进行关闭
	CloseUserSession = 1,			///> 依据用户名称进行关闭
};

struct ReuseSessionOption
{
	int				session_type;			///> rtsp_connect_config_t枚举，由外部设置鉴权类型
	ReuseSessionOption()
	{
		session_type = CONFIG_UNKNOW;
	}
};

///\brief 会话校验加密选项
enum SessionOptCheckencrypt
{
	SessionOptNocheck = 0,		///< 不校验码流加密
	SessionOptEncrtptcheck,		///< 进行码流加密校验
};

///\brief 会话连接选项, 由于 ReuseSessionOption 不好扩展, 
///  后续推荐使用AddSessionOption 的AddNewConnect 接口
struct AddSessionOption
{
	int						    	session_type;	///< rtsp_connect_config_t枚举，由外部设置鉴权类型
	Memory::TSharedPtr<long>	    sessionid;		///< 保存会话id 的地址, 由外部传入， 当会话生成时，由流媒体库负责写入
	int								checkencrypt;	///< 会话码流加密校验, 校验表明只允许传输加密流
	int								reserved[7];	///< 保留字节, 后续扩展使用
	AddSessionOption()
	{
		session_type = CONFIG_UNKNOW;
		checkencrypt = SessionOptNocheck;
		memset(reserved, 0, sizeof(reserved));
	}
};

///\brief 位置/时间 间隔信息
struct RangeInfo
{ 
	RangeType rangeType;	///> 间隔格式
	
	union
	{
		struct npt_t
		{
			double start;
			double end;
		}npt;
		struct utc_t
		{
			struct UtcTime start;
			struct UtcTime end;
		}utc;
		struct byte_t
		{
			int64_t start;
			int64_t end;
		}byte;
		struct smpte_t
		{
			struct SmpteTime start;
			struct SmpteTime end;
		}smpte;
		struct slice_t
		{
			int32_t start;
			int32_t end;
		}slice;
	}rangeInfo;		///> 间隔信息
};

///\brief 视频类型
enum VideoType
{
	videoTypeH264,	///> H264类型
	videoTypeMPEG4,	///> MPEG4类型
	videoTypeH265,	///> H265类型
	videoTypeSVAC,	///> SVAC类型
	videoTypeMPEG2,	///> MPEG2类型
	videoTypeSVAC2,	///> SVAC2类型
	videoTypeUnknow,	///> 未知类型
};

///\brief 音频类型
enum AudioType
{
     audioTypePCMU,
     audioTypePCMA,
     audioTypeAAC,
     audioTypeMP3,
     audioTypeUnknown
};

///\brief 对讲信息
struct TalkInfo
{
     AudioType type;	///> 音频类型
     int       sample; 	///> 采样率
     int       track; 	///> 声道数
};

///\brief 监听地址配置
struct ListenAddrConfig
{
	char addrV4[32];            ///>监听IPV4地址
	char addrV6[128];           ///>监听IPV6地址
	char sslAddrV4[32];         ///>监听SSL加密的IPV4地址
	char sslAddrV6[128];        ///>监听SSL加密的IPV6地址
	char reserved[24];          ///>保留字段

	ListenAddrConfig()
	{
		memset(addrV4, 0 , sizeof(addrV4));
		strncpy(addrV4, "0.0.0.0", sizeof(addrV4));
		memset(addrV6, 0 , sizeof(addrV6));
		strncpy(addrV6, "::", sizeof(addrV6));
		memset(sslAddrV4, 0 , sizeof(sslAddrV4));
		strncpy(sslAddrV4, "0.0.0.0", sizeof(sslAddrV4));
		memset(sslAddrV6, 0 , sizeof(sslAddrV6));
		strncpy(sslAddrV6, "::", sizeof(sslAddrV6));
		memset(reserved, 0, sizeof(reserved));
		
	}
};

///\brief 视频rtp payload配置
struct sdpVideopt
{
	char		h264[8];				///< h264载荷值
	char		h265[8];				///< h265载荷值
	char   		reserve[48];

	sdpVideopt()
	{
		memset(h264, 0 , sizeof(h264));
		strncpy(h264, "96", sizeof(h264));
		memset(h265, 0 , sizeof(h265));
		strncpy(h265, "98", sizeof(h265));
		memset(reserve, 0, sizeof(reserve));
	}	
};

///\brief 音频对讲配置
struct AudioTalkInfo
{
	uint32_t 		encode;		///< 编码类型,类型参考枚举AudioEncodeType	
	uint32_t 		freq;		///< 采样率,真实的采样率, 非枚举值
	int    		reserve1[4];	///< 保留字段
	void       *reserve2[2];	///< 保留字段
	
	AudioTalkInfo()
	{
		encode 	= 0;
		freq	= 0;
		memset(reserve1, 0, sizeof(reserve1));
		memset(reserve2, 0, sizeof(reserve2));
	}
};

///\brief SDP配置信息
struct SdpInfoConfig
{
	uint32_t 		config_mask;		///< 配置掩码
	bool			*fishEyeEnable;		///< 鱼眼描述信息使能标志
	sdpVideopt		*sdpvideopt;		///< 视频rtp pt值信息，目前只支持设置h264和h265的pt值
	AudioTalkInfo	*talkinfo;			///< 音频对讲信息，目前支持设置编码类型和采样率

	void       		*reserve[29];		///< 保留字段

	SdpInfoConfig()
	{
		config_mask 	= 0;
		fishEyeEnable 	= NULL;
		sdpvideopt 		= NULL;
		talkinfo 		= NULL;
		memset(reserve, 0, sizeof(reserve));
	}
};

///\brief 低延时显示策略
enum LowLatency
{
	RealEncodeEx 	= 0x01,			///> 通过上层提供的扩展编码配置进行sdp信息的初始化,用于快速回复sdp 信息
	RealTimeRecv 	= 0x02,			///> 实时接收数据策略, 用于实时接收请求, 而不是轮询接收请求，以快速回复响应	
	DataSrcBuffer	= 0x04,			///> 流源缓存策略, 用于快速回复sdp 信息 ,如果使用了该策略, 则无需设置RealEncodeEx配置
	DataCache		= 0x08,			///> 数据缓存策略, 用于缓存上一个GOP数据，用于快速发送数据给客户端
	SendModeSync	= 0x10,			///> 同步发送策略, 拿到数据先进行一次同步发送,用于快速发送数据给客户端
};

///\brief 低延时配置
struct LowLatencyConfig
{
	int   configmask;				///< 配置掩码，参考LowLatency配置
	int   cachenum;					///< 数据缓存的帧数，与DataCache策略配套使用
	int	  reserve1[4];				///< 保留字段
	void *reserve2[4];				///< 保留字段

	LowLatencyConfig()
	{
		configmask 	= 0;
		cachenum 	= 0;
		memset(reserve1, 0, sizeof(reserve1));
		memset(reserve2, 0, sizeof(reserve2));
	}
};

///\brief Rtsp Over Http请求解析回调
///\param [in] const char* -原始的HTTP请求内容指针
///\param [in] bool * - 是否是长连接
///\param [in] void *  -保留参数
///\param [in] void *  -保留参数
///\return int 成功返回0失败返回非0
typedef	Dahua::Infra::TFunction4<int, const char*, bool &, void*, void*> RtspOverHttpReqProc;

///\brief Rtsp外部模块错误码
enum RtspExtErrno
{
	ErrnoTalkBusyLine = 0,			///< 对讲忙线
	ErrnoTalkCheckFailed,			///< 对讲不满足操作条件
	ErrnoKmsUnavailable,			///< Kms密钥无效
	ErrnoNum,	
};

///\brief Rtsp外部模块错误类型
struct RtspExtErr
{
	RtspExtErrno 		errcode;			///< 错误码，参考RtspExtErrno配置
	std::string			errstr;				///< 与错误码对应的字符串，参考INTER_RTSP_EXTAR_ERROR_TALKBUSYLINE等
};

STREAMSVR_API extern struct RtspExtErr rtspExtErrStr[ErrnoNum];	///< 错误码信息数组

/////////////////////////////////  加密方式定义开始 ///////////////////////////////////////////
///\brief 加密等级
enum DHEncryptLevel
{
    dhEncrtptLevelNoEncrypt,    ///> 不进行加密
    dhEncrtptLevelIFrame256,    ///> 简单加密，只加密I帧前256个字节
    dhEncrtptLevelIFrameWhole,  ///> 整个I帧加密
    dhEncrtptLevelIAXFrame,  	///> 对I帧, 音频帧及其他辅助帧进行加密
    dhEncrtptLevelUnknown,      ///> 未知类型等级
};

///\brief 加密使用的算法
enum DHEncryptAlg
{
    dhEncryptAlgAES,    	///> AES128-ECB 加密方式
    dhEncryptAlgDES,    	///> DES 加密方式
    dhEncryptAlg3DES,   	///> 3DES 加密方式
    dhEncryptAlgAES256_OFB, ///> AES256-OFB 加密方式
    dhEncryptAlgUnknown,	///> 未知加密方式
};

///\biref 大华帧加密相关配置
struct DHEncryptConfig
{
	int encryptLevel;       ///> 参考 @see DHEncryptLevel,暂时未用到
	int dhEncryptAlg;       ///> 参考 @see DHEncryptAlg,暂时未用到
	int keyExchangeType;    ///> Mikey密钥交换方式，参考StreamSvr-Mikey.h中的 @seeKeyExchangeType。默认为KeyExchangePSK
	char psk[1024];         ///> 预共享密钥
	int  pskLen;            ///> 预共享密钥长度
	bool dataUnvarnished;	///> MTS使用场景，true为交互MIKEY后让数据不进行加/解密

    DHEncryptConfig()
	{	
		encryptLevel = dhEncrtptLevelUnknown;
		dhEncryptAlg = dhEncryptAlgUnknown;
		keyExchangeType = StreamSvr::KeyExchangeUnknown;
		memset(psk, 0, sizeof(psk));
		pskLen = 0;
		dataUnvarnished = false;///> 默认是需要加密的
	}
};

///< biref 和慧眼加密媒体类型
enum HHYEncMediaType
{
	EncMediaTypeNoFrame  = 0,	///> 所有帧数据都不进行加密
	EncMediaTypeIFrame   = 1,	///> 只对I帧进行加密
	EncMediaTypeIAFrame  = 2,	///> 对视频关键帧和音频帧加密
	EncMediaTypeALLFrame = 3,	///> 对音视频帧都进行加密
    EncMediaTypeExceptPFrame = 4,	///> 除了P帧，其他类型帧都进行加密
};

///\biref 大华帧头0x95字段加密相关配置，本方案只支持一个0x95字段，即不支持对一帧的多个地方加密
struct HHYEncryptConfig
{
	DHEncryptAlg	enctype;		///> 参考 @see @DHEncryptAlg,加密算法
	HHYEncMediaType	mediatype;		///> 加密数据的媒体类型，只对需要加密的帧进行加密
	uint16_t		offset;			///> 加密字段的起始偏移，从裸数据的起始开始算起
	uint32_t		encLen;			///> 加密数据的长度，要求是16的整数倍
	char			encKey[256];	///> 加密密钥,密钥最长支持256字节
	int 			keyLen;			///> 密钥长度

	HHYEncryptConfig()
	{
		enctype = dhEncryptAlgAES;
		mediatype = EncMediaTypeNoFrame;
		offset = 0;
		encLen = 0;
		memset(encKey, 0, sizeof(encKey));
		keyLen = 0;
	}
};

///\biref 大华帧头0x95字段加密相关配置，本方案只支持一个0x95字段，即不支持对一帧的多个地方加密
struct HHYEncryptConfigExt
{
	DHEncryptAlg	enctype;		///> 参考 @see @DHEncryptAlg,加密算法
	HHYEncMediaType	mediatype;		///> 加密数据的媒体类型，只对需要加密的帧进行加密
	uint16_t		offset;			///> 加密字段的起始偏移，从裸数据的起始开始算起
	uint32_t		encLen;			///> 加密数据的长度，要求是16的整数倍
	char			encKey[256];	///> 加密密钥,密钥最长支持256字节
	int 			keyLen;			///> 密钥长度
    bool            pwdCheck;       ///> 是否需要密钥检验
    int             reserve[8];     ///> 保留字段

	HHYEncryptConfigExt()
	{
		enctype = dhEncryptAlgAES;
		mediatype = EncMediaTypeNoFrame;
		offset = 0;
		encLen = 0;
		memset(encKey, 0, sizeof(encKey));
		keyLen = 0;
        pwdCheck = false;
        memset(reserve, 0, sizeof(reserve));
	}
};

///< biref 大华帧加密策略
enum DHEncryptStrategy
{
	EncStrategyNoFrame  = 0,		///< 所有帧数据都不进行加密
	EncStrategyIFrame   = 1,		///< 只对I帧进行加密
	EncStrategyIAFrame  = 2,		///< 对视频关键帧和音频帧加密
	EncStrategyALLFrame = 3,		///< 对音视频帧都进行加密
    EncStrategyExceptPFrame = 4,	///< 除了P帧, 其他类型帧都进行加密
};

///\biref 大华帧头0xB5字段加密相关配置，本方案只支持一个0xB5字段，即不支持对一帧的多个地方加密
struct DHEncrypt3Config
{
	DHEncryptAlg		enctype;		///< 参考 @see @DHEncryptAlg,加密算法
	DHEncryptStrategy	strategy;		///< 加密数据的媒体类型，只对需要加密的帧进行加密, @see DHEncryptStrategy
	uint32_t			offset;			///< 加密字段的起始偏移，从裸数据的起始开始算起
	uint32_t			encLen;			///< 加密数据的长度
	char				encKey[256];	///< 加密密钥,密钥最长支持256字节
	int 				keyLen;			///< 密钥长度
    int             	reserve[16];    ///< 保留字段

	DHEncrypt3Config()
	{
		enctype = dhEncryptAlgUnknown;
		strategy = EncStrategyNoFrame;
		offset = 0;
		encLen = 0;
		memset(encKey, 0, sizeof(encKey));
		keyLen = 0;
        memset(reserve, 0, sizeof(reserve));
	}
};

///\brief SRTP加密类型
enum SrtpEncryptType
{
	SRTP_NOT_ENCRYPT				= 0,		///> SRTP不使用加密
	AES_CM_128_HMAC_SHA1_80			= 1,		///>AES(128位)加密，HMAC-SHA1(80位) 认证，参考RFC4568 
	AES_CM_128_HMAC_SHA1_32			= 2,		///>AES(128位)加密，HMAC-SHA1(32位) 认证，参考RFC4568 
};

///\brief SRTP加密配置
struct SrtpEncryptConfig
{
	SrtpEncryptType 	enctype;			 ///< 加密类型, 见SrtpEncryptType
	uint8_t    		 	key[128];			 ///< 原始密钥
	uint32_t    		keyLen;				 ///< 密钥长度
	uint32_t			reserved[10];		 ///< 保留字段

	SrtpEncryptConfig()
	{
		enctype = SRTP_NOT_ENCRYPT;
		memset(key, 0, sizeof(key));
		keyLen = 0;
		memset(reserved, 0, sizeof(reserved));
	}
	
	bool operator==(const SrtpEncryptConfig& other)const
	{
		if(enctype != other.enctype || keyLen != other.keyLen)
			return false;
		if(memcmp(key, other.key, keyLen) != 0)
			return false;
		if(memcmp(reserved, other.reserved, sizeof(reserved)) != 0)
			return false;
		
		return true;
	}

	SrtpEncryptConfig& operator=(const SrtpEncryptConfig& other)
	{
		if(this == &other)
			return *this;
		enctype = other.enctype;
		if(other.keyLen > sizeof(key))
		{
			keyLen = sizeof(key);
		}
		else
		{
			keyLen = other.keyLen;
		}
		memcpy(key, other.key, keyLen);
		memcpy(reserved, other.reserved, sizeof(reserved));
		return *this;
	}
};

/////////////////////////////////  加密方式定义结束 ///////////////////////////////////////////

///\会话退出原因
enum exitCauseMain
{
	// 0 代码逻辑异常导致拉流失败或断开
	exitServerError = 0,			///< 服务端逻辑错误, 指走入了不应该走入的逻辑

	// 1-49 网络原因或者客户端主动断开导致拉流失败或断开
	exitTeardown = 1,				///< 客户端主动断开
	exitRecvError,					///< 网络recv错误
	exitSendError,					///< 网络发送错误
	exitSendTimeout,				///< 发送超时
	exitRtcpbye,					///< 收到rtcpBye包	
	exitKeepLiveFail,				///< 客户端长久没有发心跳命令断开

	// 50-99 客户端请求异常导致拉流失败或断开
	exitSeparatorFailed = 50,		///< 码流分离失败
	exitBadRequest,					///< 请求的命令异常
	
	// 100-149 数据源相关错误导致拉流失败或断开
	exitMediaSourceNotFound = 100,	///< 创建流源失败,常见于上层组件创建失败
	exitMediaSourceInitFailed,		///< 初始化流源失败, 常见于上层应用的媒体数据存在异常
	exitMediaPlayFailed,			///< 播放失败,常见于回放时客户端请求超出上层返回给流媒体的录像范围
	exitMediaSourceDataError,       ///< 上层的数据源上报了空包,且未实现getPacketType 接口指明播放完毕
	exitMediaSourceDataOver,		///< 录像播放完毕或者设备因为休眠监视流播放完毕
	exitMediaSinkFailed,			///< 接收数据槽创建失败，可能是开启多路多讲导致或其他异常
	exitMediaSdpChanged,			///< 流源的编码配置或使能信息变更导致sdp 信息信息变更断开

	// 150-199 设备配置变更导致拉流失败或断开
	exitServerDown = 150,			///< 流媒体服务关闭导致所有会话断开
	exitCheckTransportFailed,		///< 设备测配置不允许特定的打包方式拉流
	exitReCheckAuthFailed,			///< 因为在多合一画面监视时, 因画面分隔变更无某通道权限而失败
	exitForbidden,					///< 没有业务权限,如无监视权限
	exitForceClose,					///< 外部强制关闭，可能是用户名或密码变更导致
	exitMulticastConfigUpdate,		///< 组播配置更新导致拉流断开
	exitConfigDisable,				///< 流媒体业务相关配置未使能, 例如组播配置

	// 200-249 加密相关配置异常或变更导致拉流失败或断开
	exitSrtpFailed = 200,			///< 创建srtp 秘钥失败 
	exitEncryptkeyChanged,			///< 加密秘钥变更
};


///\客户端会话关闭原因
enum closeCauseMain
{
	// 0-99 代码逻辑异常或者上层业务强制关闭,导致拉流失败或断开	
	closeClientError = 0,		 	 ///< 客户端逻辑错误, 指走入了不应该走入的逻辑
	closeForceClose,     			 ///< 外部强制关闭, 上层业务异常主动断开拉流	
	closeTransChannelError,      	 ///< 客户端传输通道异常
	closeGetComponentFailed,		 ///< 获取组件失败，常见于该组件未实现或者未初始化

	// 100-199 网络原因或者服务端主动断开导致拉流失败或断开
	closeTeardown = 100,			 ///< 服务端主动断开
	closeConnectFailed,				 ///< TCP连接建立失败
	closeConnectTimeout,			 ///< TCP连接建立超时
	closeSockError,			 		 ///< socket异常,原因未知
	closeRecvError,					 ///< 网络recv错误
	closeSendError,				 	 ///< 网络发送错误
	closeSendTimeout,				 ///< 发送超时
	closeRtcpbye,					 ///< 收到服务端rtcpBye包	
	closeKeepLiveFail,				 ///< 服务端长久没有回复心跳命令断开
	closeMessageLiveFail,			 ///< 服务端长久没有回复请求命令断开
	
	// 200-299 服务端响应与请求或客户端请求url异常导致拉流失败或断开
	closeSeparatorFailed = 200,		 ///< 码流分离失败
	closeBadResponse,				 ///< 响应的命令异常
	closeBadSendRequest,			 ///< 发送请求的命令异常
	closeBadRecvRequest,			 ///< 接收请求的命令异常
	closeBadRedirect,				 ///< 302重定向异常
	closeBadUrl, 			 	 	 ///< 客户端url异常

	// 300-399 服务端异常导致拉流失败或断开
	closeServerError = 300,			 ///< 服务内部错误
	closeServerUnavailable,			 ///< 服务不可用
	closeServerP2PMaxConnect,    	 ///< 服务p2p连接达到上限
	closeServerTalkBusyline, 		 ///< 服务对讲忙线
	closeServerTalkCheckfailed, 	 ///< 服务对讲不满足操作条件
	
	// 400-499 数据源或槽相关错误导致拉流失败或断开
	closeMediaSourceNotFound = 400,	 ///< 创建流源失败,常见于上层组件创建失败
	closeMediaSourceInitFailed,		 ///< 初始化流源失败, 常见于上层应用的媒体数据存在异常
	closeMesiaSourceInterException,	 ///> 流源内部异常, 常见于应用数据帧异常
	closeMediaSinkFailed,			 ///< 接收数据槽创建失败
	closeMediaSdpChanged,			 ///< 流源的编码配置或使能信息变更导致sdp 信息信息变更断开
	closeMediaAdapterFailed,		 ///< 媒体适配器创建失败,常见于加密组件或者websocket, rtmp, http-flv等组件没有初始化

	// 500-599 配置校验异常或者不支持的业务导致拉流失败或断开
	closeCheckTransportFailed = 500, ///< 设备测配置不允许特定的打包方式拉流
	closeReCheckAuthFailed,			 ///< 因为在多合一画面监视时, 因画面分隔变更无某通道权限而失败
	closeUnauthorized, 				 ///< 未授权, 用户名或密码错误
	closeForbidden,					 ///< 没有业务权限,如无监视权限
	closeUnsupport,					 ///< 客户端不支持的业务导致断开

	// 600-699 加密相关配置异常或变更导致拉流失败或断开
	closeEncryptUnsupport = 600,	 ///< 加密不支持导致的拉流失败
	closeEncryptKeyMismatch,		 ///< Mikey密钥协商失败
};


///\biref  流媒体消息事件的详细信息
struct EventRtspSessionState
{
	char		remoteIp[32];															///< 对端IP地址
	int			channel;																///< 通道号, 从1开始
	int			streamType;																///< 码流类型
	enum		status{NormalDisConnected=0, AbnormalDisConnected =1, Connected=2,};	///< 会话状态，是连接上还是断开
	status		state;																	///< 断开还是连接上
	long		sessionId;																///< 会话ID
	char 		userAgent[512];															///< 客户端会话代理
	char 		username[512];															///< 用户名信息
	char        urltype[24];															///< url 会话类型, 包括直播,点播,对讲
	char        url[256];																///< 请求的url		
	char        rtspstate[24];															///< rtsp 当前的信令状态
	uint16_t	port;																	///< 端口信息
	uint32_t	exitReason;																///< 会话退出原因(exitCauseMain(16b)|errno(16b))
	char        reserved[14];															///< 保留字段

	EventRtspSessionState()
	{
	    channel = 0;
        streamType = 0;
        state = NormalDisConnected;
        sessionId = 0;
		port = 0;
		exitReason = 0;
		
		memset(remoteIp, 0 , sizeof(remoteIp));
		memset(userAgent, 0 , sizeof(userAgent));
		memset(username, 0 , sizeof(username));
		memset(urltype, 0 , sizeof(urltype));
		memset(url, 0 ,sizeof(url));
		memset(rtspstate, 0 ,sizeof(rtspstate));
	}
};

class CFrameInfo;

///\biref  流媒体回调帧信息消息事件的详细信息
struct EventSendFrameInfo
{
	CFrameInfo* frameinfo;            ///< 发送的帧信息
	long		sessionId;            ///< 会话的ID
	char        reserved[32];         ///< 保留字节
	
	EventSendFrameInfo()
	{
		frameinfo   = NULL;
		sessionId   = 0;
		reserved[0] = 0;
	}	
};

///\brief 事件回调函数原型	
///\param [in]	int -事件枚举, 见IFrameState::fstatevent
///\param [in]	void *-事件信息, 不同的事件类型回调不同的事件信息
///\param [in]	void *-保留参数
typedef Infra::TFunction3<void, int, void *, void *> FrameEventCallBack;

///\brief 发送帧事件配置
struct ConfigFrameEvent
{
	int eventmask;                 ///< 使能的事件掩码, 见IFrameState::fstatevent 
	FrameEventCallBack	proc;      ///< 事件回调函数
	char reserve[32];			   ///< 保留参数	

	ConfigFrameEvent()
	{
		eventmask = 0; 
		memset(reserve, 0, sizeof(reserve));
	}
};

///\biref  流媒体回调给上层的回复消息结构体
struct RtspRspmsgInfo
{
	int  errorcode;   	 ///< 如果该错误码不为0,  流媒体会根据该错误码进行组装标准的错误回复, 错误码见 RtspStatusCode 中的数字部分, 如401等错误码
	char title[24];      ///< 在errorcode 为0 的情况下，通过GET_PARAMETER  请求消息通知对方信息, 暂时只支持"OffLine",  表示通知对方下线
	int  usercode;       ///< title 对应的客户信息码(要求范围为[0-999] ), 媒体负责把该信息码通知对方, 由两边的应用上层约定好进行处理
	char reserved[20];   ///< 保留字段

	RtspRspmsgInfo()
	{
		errorcode = 0;
		usercode = 0;
		memset(title, 0, sizeof(title));
	}
};

///\biref  流媒体回调给上层的消息信息
struct InRtspMsg
{
	const char *rtspReqmsg; 					///< rtsp请求的消息
	const char *rtspRspmsg; 					///< rtsp请求对应的回复消息, 如果为"" , 表示是服务端主动请求, 此时detail 信息无效	
	const struct EventRtspSessionState *detail; ///< rtsp请求的消息的详细解析信息
};

///\biref 上层返回给流媒体的消息信息 
struct OutRtspMsg
{
	char *rtspRspmsg;	///< rtsp 消息的回复缓冲, 由外部对该缓冲进行填充, 注意不要修改该指针指向, 流媒体使用该消息替换原来的请求回复
	int   bufferLen;	///< 缓冲的长度
	struct RtspRspmsgInfo msgInfo; ///< 在rtspRspmsg 为空字符串即"" 的情况下, 流媒体根据其中信息组装响应的回复
	OutRtspMsg()
	{
		rtspRspmsg = NULL;
		bufferLen = 0;
	}
};

///\brief Rtsp消息回调接口
///\param [in] InRtspMsg--输入Rtsp消息
///\param [out] OutRtspMsg--输出修改后的Rtsp响应消息
///\return 0 成功, 按OutRtspMsg进行回复，-1 按原消息进行回复, 相当于仅通知上层流媒体消息
typedef Infra::TFunction2<int, const struct InRtspMsg &, struct OutRtspMsg &> RtspMsgProc;

///\biref rtsp 消息应用预处理结构体
struct PreMsgInfo
{
	uint32_t errorcode;	///< errorcode, 该值应用修改不为200 后, 进行断开,可以和RtspMsgProc 搭配使用, 进行自定义的返回
	char *realreq;      ///< errorcode 为200的情况下，流媒体处理该请求替换老的请求
	int   len;			///< 输入为realreq 的内存大小, 该值传出为0 ,表示不修改请求,否则表示修改后的请求长度
};

///\brief Rtsp消息应用预处理回调接口
///\param [in] InRtspMsg--输入Rtsp消息, 流媒体暂不解析信令, detail 为空
///\param [out] PreMsgInfo--输出修改后的Rtsp 请求
typedef Infra::TFunction2<void, const struct InRtspMsg &, struct PreMsgInfo &> RtspMsgPreProc;

///\brief rtp乱序窗口类型选项
enum DisorderWindowType
{
	DisorderWindowPacketNumber = 0, 	//0:数据包数量
	DisorderWindowDataDelay,			//1:数据延时(ms)
	DisorderWindowMemerySize,			//2:内存大小(KB)
	DisorderWindowUnknown,				///> 未知格式
};


///\brief 待排序rtp乱序窗口配置定义
struct DisorderWindow
{
	int type;			//窗口类型
	int value;			// 窗口大小
	int reserved[20];   ///< 保留字段
	DisorderWindow():type(0), value(0)
	{
		memset(reserved, 0, sizeof(reserved));
	}
};

//\brief 支持数据缓冲的几种码流类型，可以同时支持，如DHInterleaved|RtpRawStream等
enum MediaCacheEnableByStreamType
{
	NoneCache 		= 0,	///> 无缓存,默认
	DHInterleaved	= 1<<0, ///> 交织头+大华帧 
	RtpRawStream	= 1<<1,	///> 标准RTP流，像VLC
	RtpDHStream		= 1<<2, ///> RTP封装大华帧
};

///\ 提供给外部接口的错误码， 对应 RtspUtil.cpp 中的错误码字符串
enum RtspStatusCode{
		HTTP_ERROR_BASE 							= 0x10090000 ,				///< Http 基准错误码
		RTSP_ERROR_BASE								= 0x110a0000 ,				///< Rtsp 基准错误码
		RTSP_ERROR_PARSE_FAILED						= RTSP_ERROR_BASE+1 ,		///< 解析失败
		RTSP_ERROR_NET_EXCEPTION 					= RTSP_ERROR_BASE+2 ,		///< 网络异常
		RTSP_ERROR_INTER 							= RTSP_ERROR_BASE+3 ,		///< 内部异常
		RTSP_ERROR_ALIVE_TIMEOUT					= RTSP_ERROR_BASE+4 ,		///< 保活超时
		RTSP_ERROR_KEY_MISMATCH						= RTSP_ERROR_BASE+5 ,		///< Mikey密钥协商失败
		RTSP_ERROR_TALK_BUSYLINE                    = RTSP_ERROR_BASE+6 ,		///< 对讲忙线
		RTSP_ERROR_TALK_CHECKFAILED                 = RTSP_ERROR_BASE+7 ,		///< 对讲不满足操作条件
		RTSP_ERROR_CREATE     						= HTTP_ERROR_BASE + 201 ,	///< 创建失败    
		RTSP_ERROR_LOW_STORAGESPACE                 = HTTP_ERROR_BASE + 250 ,   ///< 存储空间不足 
		RTSP_ERROR_MULTIPLE_CHOICES                 = HTTP_ERROR_BASE + 300 ,	///< 多个选择
		RTSP_ERROR_MOVED_PERMANENTLY                = HTTP_ERROR_BASE + 301 ,   ///< 已永久移除不可用
		RTSP_ERROR_MOVED_TEMPORARILY                = HTTP_ERROR_BASE + 302 ,	///< 临时移除不可用
		RTSP_ERROR_SEE_OTHER                        = HTTP_ERROR_BASE + 303 ,	///<  
		RTSP_ERROR_NOT_MODIFIED                     = HTTP_ERROR_BASE + 304 ,	///< 未修改
		RTSP_ERROR_USE_PROXY	                    = HTTP_ERROR_BASE + 305 ,	///< 使用代理
		
		RTSP_ERROR_BAD_REQUEST                      = HTTP_ERROR_BASE + 400 ,	///< 非法请求
		RTSP_ERROR_UNAUTHORIZED                     = HTTP_ERROR_BASE + 401 ,	///< 未授权
		RTSP_ERROR_PAYMENT_REQUIRED                 = HTTP_ERROR_BASE + 402 ,	///< 
		RTSP_ERROR_FORBIDDEN	                    = HTTP_ERROR_BASE + 403 ,	///< 禁止访问
		RTSP_ERROR_NOT_FOUND	                    = HTTP_ERROR_BASE + 404 ,	///< 未找到相关资源
		RTSP_ERROR_METHOD_NOT_ALLOWED               = HTTP_ERROR_BASE + 405 ,	///< 禁止的请求
		RTSP_ERROR_NOT_ACCEPTABLE                   = HTTP_ERROR_BASE + 406 ,	///< 不支持的请求
		RTSP_ERROR_PROXY_AUTH_REQUIRED              = HTTP_ERROR_BASE + 407 ,	///< 需要代理鉴权
		RTSP_ERROR_REQUEST_TIME_OUT                 = HTTP_ERROR_BASE + 408 ,	///< 请求超时
		RTSP_ERROR_GONE			                    = HTTP_ERROR_BASE + 410 ,	///< 请求的资源失效
		RTSP_ERROR_LENGTH_REQUIRED                  = HTTP_ERROR_BASE + 411 ,	///< 需要长度信息,content-length
		RTSP_ERROR_PRECONDITION_FAILED              = HTTP_ERROR_BASE + 412 ,	///< 预处理失败
		RTSP_ERROR_REQUEST_ENTITY_TOO_LARGE         = HTTP_ERROR_BASE + 413 ,	///< 请求body太大了
		RTSP_ERROR_REQUEST_URI_TOO_LARGE            = HTTP_ERROR_BASE + 414 ,	///< 请求的URI太长
		RTSP_ERROR_UNSUPPORTED_MEDIA_TYPE           = HTTP_ERROR_BASE + 415 ,	///< 不支持的媒体类型
		RTSP_ERROR_PARAMETER_NOT_UNDERSTOOD         = HTTP_ERROR_BASE + 451 ,	///< 无法识别的参数
		RTSP_ERROR_CONFERENCE_NOT_FOUND             = HTTP_ERROR_BASE + 452 ,	///< 未找到的协商
		RTSP_ERROR_NOT_ENOUGH_BANDWIDTH             = HTTP_ERROR_BASE + 453 ,	///< 带宽不足
		RTSP_ERROR_SESSION_NOT_FOUND                = HTTP_ERROR_BASE + 454 ,	///< 会话未找到(已失效)
		
		RTSP_ERROR_METHOD_NOT_VALID_IN_STATE        = HTTP_ERROR_BASE + 455 ,	///< 无效方法
		RTSP_ERROR_HEADER_FIELD_NOT_VALID     	    = HTTP_ERROR_BASE + 456 ,	///< 无效头域
		RTSP_ERROR_INVALID_RANGE     			    = HTTP_ERROR_BASE + 457 ,	///< 无效区域
		RTSP_ERROR_PARAMETER_IS_READONLY      		= HTTP_ERROR_BASE + 458 ,	///< 参数只读
		RTSP_ERROR_AGGREGATE_OPERATION_NOT_ALLOWED  = HTTP_ERROR_BASE + 459 ,	///< 禁止的协商
		RTSP_ERROR_ONLY_AGGREGATE_OPERATION_ALLOWED = HTTP_ERROR_BASE + 460 ,	///< 只允许协商
		RTSP_ERROR_UNSUPPORTED_TRANSPORT    		= HTTP_ERROR_BASE + 461 ,	///< 不支持的传输方式
		RTSP_ERROR_DESTINATION_UNREACHABLE          = HTTP_ERROR_BASE + 462 , 	///< 目标不可达
		
		RTSP_ERROR_INTERNAL_SERVER_ERROR            = HTTP_ERROR_BASE + 500 ,	///< 服务内部错误
		RTSP_ERROR_NOT_IMPLEMENTED                  = HTTP_ERROR_BASE + 501 ,	///< 未实现
		RTSP_ERROR_BAD_GATEWAY                      = HTTP_ERROR_BASE + 502 ,	///< 非法网关
		RTSP_ERROR_SERVICE_UNAVAILABLE              = HTTP_ERROR_BASE + 503 ,	///< 服务不可用
		RTSP_ERROR_GATEWAY_TIMEOUT                 	= HTTP_ERROR_BASE + 504 ,	///< 网关超时
		RTSP_ERROR_RTSP_VERSION_NOT_SUPPORTED       = HTTP_ERROR_BASE + 505 ,	///< 不支持的Rtsp版本
		RTSP_ERROR_OPTION_NOT_SUPPORTED            	= HTTP_ERROR_BASE + 551 ,	///< 不支持的选项
		RTSP_ERROR_KMS_UNAVAILABLE					= HTTP_ERROR_BASE + 552 ,	///< 服务端流源获取kms密钥失败
		RTSP_ERROR_UNKNOWN							= HTTP_ERROR_BASE + 1000,	///< 
};
}//namespace StreamSvr
}//namespace Dahua

#endif //__INCLUDED_DAHUA_STREAMSVR_RTSPUTIL_H__

