#ifndef __INCLUDE_DAHUA_STREAMSVR_MEDIAUTILS_H__
#define __INCLUDE_DAHUA_STREAMSVR_MEDIAUTILS_H__

#include <string.h>
#include "Infra/Function.h"
#include "StreamSvr/Util/MediaFrame.h"
#include "StreamSvr/Protocol/RtspUtil.h"
#include "StreamSvr/Util/PrintLog.h"

namespace Dahua{
namespace StreamSvr{

/////////////////////            流源              //////////////////////////////
///\brief 流源事件类型
enum StreamEventType
{
	streamEventInitSdpSuccess,		///> 初始化流源描述成功
	streamEventInitSdpFailed,		///> 初始化流源描述失败
	streamEventSdpChange,			///> 流源发生变更
	streamEventFilePlayComplete,	///> 单个文件播放完毕
	streamEventInterException,		///> 流源内部异常
	streamEventReceiveRtcpBYE,		///> 收到rtcp bye 报文
	streamEventReceiveRtcpRR,		///> 收到RTCP 接收报告
	streamEventReceiveRtcpSR,		///> 收到RTCP 发送报告
	streamEventEncryptChange,       ///> 加密秘钥发生变更
	streamEventLostFrame,			///> 发送数据丢帧事件
	streamEventRecevieFrame,		///> 收到数据事件
	streamEventStreamSourceComplete,///> 数据源播放完毕(一个数据源可能会包含有多个文件)
	streamEventSrcReady,			///> 数据源准备完成
	streamEventSinkReady,			///> 数据槽准备完成
	streamEventSdpChanging,         ///> 流源正在改变
	streamEventCallBackFrameInfo,   ///> 帧信息回调事件
	streamEventContentChange,		///> 码流内容改变(需要重新鉴权)
	streamEventLiveOver,			///> 直播流结束
	streamEventFirstIframe,			///> 发送第一个I 帧通知
	streamEventFirstIframeRecv,		///> 接收到第一个I 帧通知
	streamEventDropFrameCalc,		///> 发送数据丢帧事件统计
	streamEventLostFrameCalc,		///> 接收数据丢帧统计事件
	streamEventFrameDelayCalc,		///> 发送缓冲数据延时统计事件	
	streamEventFirstAframe,			///> 发送第一个对讲音频帧通知
	streamEventFirstAframeRecv,		///> 接收到第一个A 帧通知
};

///\breif用户配置到媒体层的操作集合
enum MediaSessionConfigSet
{
	MEDIA_SESSION_OPTIMIZING,		///< 优化选项, 用于打包大华帧头时， 是否需要打包校验信息
	MEDIA_SESSION_FLOW_ENALBE,		///< 流量统计使能配置
	MEDIA_SESSION_FRAMESTATE,		///< 帧发送事件配置
	MEIDA_SESSION_TIME_ZONE,		///< 设置本地时区
	MEDIA_SESSION_RTP_NONSTANDARD,	///< 设置透传模式下转码模块解析RTP数据时的策略，当为true时，不考虑时间戳、marker、payload值
	MEDIA_SESSION_RTP_SYNCPTS,		///< 设置RTP 同步时间戳配置
	MEDIA_SESSION_CACHE_ENABLE,		///< 数据缓冲使能，优化出流速度
	MEIDA_SESSION_RTP_EXTRA_NTP,    ///< 设置RTP扩展NTP
	MEIDA_SESSION_DYN_SEPERATEBUFF, ///< 设置动态调整分离缓冲策略, 用于减少拷贝次数
	MEDIA_SESSION_FRAME_RECV_STATE,	///< 设置帧接收事件配置
	MEDIA_SESSION_FRAME_SEND_STATE,	///< 设置帧发送事件配置
	MEIDA_SESSION_FRAME_INIT_UTC,   ///< 设置帧起始UTC时间
};

///\brief 流源媒体打包类型定义
///\note 若存在用户自定义的码流封装格式，
///\note 填充的值需大于mediaPacketTypeNumber，基础模块内部会调用外部转码插件进行转码
enum MediaPacketType
{
	mediaPacketTypeDH,				///> DHAV帧
	mediaPacketTypeDHInterleaved,	///> 交织的大华打包格式
	mediaPacketTypeRtpRaw,			///> RTP封装裸码流
	mediaPacketTypeRtpTs,			///> RTP封装TS包
	mediaPacketTypeRtpPs,			///> RTP封装PS包
	mediaPacketTypeRtpDH,			///> RTP封装DHAV帧
	mediaPacketTypePS,				///> PS包
	mediaPacketTypeTS,				///> TS包
	mediaPacketTypeRaw, 			///> 裸码流
	mediaPacketTypeDHRtpTcp,		///> 将大华帧打包成rtp标准包
	mediaPacketTypeRtmpFlv,			///> Rtmp 荷载flv 码流
	mediaPacketTypeFlv,				///> flv 码流
	mediaPacketTypeFmp4,			///> fmp4码流
	mediaPacketTypeNumber,			///> 支持的最大打包个数
};

///\brief Rtp 打包支持的荷载类型
enum MediaRtpPayloadType
{
	mediaPayloadTypeRtpRaw,         ///< 标准RTP 打包
	mediaPayloadTypeDH,				///< 基于大华帧的私有RTP打包
};

///\brief Tcp 交织头类型
enum TcpHeadParam
{
	NoTcpHead  = 0,				///< 无TCP 交织头
	TcpRtpInterleavedHead,			///< Rtp 交织通道头, 4 字节
	TcpRtpInterleavedLenHead,		///< Rtp 包长度交织头, 2 字节
};	
	 
///\brief 流源属性枚举
enum SourceOpt
{
	SourceRealSdp = 0,				///< 是否需要真实的sdp 信息, 只有false时才进行配置
	SourceSegmentduration,			///< 分片时长，目前用于表示HLS分片的时长
};	

///\brief MediaFrame数据回调
///\param [in] mediaIndex-该帧是由哪个媒体索引上来的，索引从0开始
///\param [in] CMediaFrame类型数据
///\return void
typedef	Infra::TFunction2<void, int, CMediaFrame& > DataProc;

///\brief 事件信息回调
///\param [in] 事件类型，参考 @see StreamEventType
///\param [in] 转码参数，参考TransformatParameter结构体
///\return void
struct TransformatParameter;	///> 前向声明
typedef	Infra::TFunction2<void, int, TransformatParameter&> EventProc;	

struct TransformatParameterEx;
typedef	Infra::TFunction2<void, int, TransformatParameterEx&> EventProcEx;	


///\brief 直播数据源创建接口原型
///\param [in] const char*-源标识，业务根据特定的规则进行解析该标识
///\return 成功-数据源指针，该指针通过destroy释放; 失败-NULL指针
class ILiveStreamSource;
typedef Infra::TFunction1<ILiveStreamSource*, const char* > LiveCreateProc;

///\brief 点播数据源创建接口原型
///\param [in] const char*-源标识，业务根据特定的规则进行解析该标识
///\return 成功-数据源指针，该指针通过destroy释放; 失败-NULL指针
class IVodStreamSource;
typedef Infra::TFunction1<IVodStreamSource*, const char* > VodCreateProc;

/////////////////////            数据源              //////////////////////////////
///\brief 数据源类型
enum DataSourceType
{
	dataSourceTypeLive,		///> 直播
	dataSourceTypeVod,		///> 点播
	dataSourceTypeNumber,  	///> 数据源未知类型
};

/////////////////////////////////////////  转码  ///////////////////////////////////////////
class ITransformat;
///\brief 创建转码对象回调模型
///\param [in] int-转码前，数据的类型，参见 @see  MediaPacketType
///\param [in] int-转码后，数据的类型，参见 @see  MediaPacketType
///\return ITransformat:转码对象指针，若无对应转码对象，则返回NULL
typedef Infra::TFunction2<ITransformat*, int, int> TransformatCreateProc;

///\brief 支持的每个源最大的媒体个数
enum MaxTrack
{	
	// 由上层设置的媒体TrackID, 注意后续新增枚举要小于MaxTrackNum,否则会越界, 音频只支持2路(AUDIO_SOURCE)
    TrackVideo = 0,       // 视频
	TrackAudioOne,		  // 第一路音频 	
	TrackAudioSec,        // 第二路音频
	TrackAssist,          // 辅助帧
	TrackOnvifMetaData,   // 元数据
	TrackBackAudioChan,   // 反向语音
	TrackTalkAudioChan,   // 正向语音
	MaxTrackNum = 8	///> 目前支持8个track
};

///\brief RTP打包时，对应的当前打包信息
struct TrackInfo 
{
	int		interleaveChannelId;///> 交织的通道号
	int		mediaIndex;			///> 用于标识media的ID号

	///> 用于发送端统计
	uint32_t	ts;				///> 当前数据包时间戳
	uint32_t	bufLen;			///> 从会话开始到现在成功发送的流媒体数据长度。
	uint32_t	totalPackets;	///> 从会话开始到现在成功发送的数据包个数

	///> 用于接收端统计
	uint32_t	ssrc;			///> 该路媒体的ssrc
	uint32_t  	curPacketLost; 	///> 本次丢失的RTP包个数
	uint32_t	totalPacketLost;///> 总共丢失的RTP包个数
	uint16_t	seq;			///> 当前数据包序列号
	TrackInfo()
	{
		interleaveChannelId = 0;
		mediaIndex = 0;
		ts = 0;
		bufLen = 0;
		totalPackets = 0;
		ssrc = 0;
		curPacketLost = 0;
		totalPacketLost = 0;
		seq = 0;
	}
};

///\brief 描述SDP最大长度
enum MaxSdpLength
{
	maxSdpLength = 5*1024,	///> 暂时不需要这么大的SDP信息，5K够用了，二期流媒体是2K
};

///\brief 文件信息指针
struct FileDetailinfo
{
	std::vector<uint64_t> sliceinfo;  ///< 每一个分片的时间长度, 单位ms
	std::string filestarttime;        ///< 文件的起始时间字符串, 按2010-02-19T14:54:23.031+08:00(时区) 提供
};

///\brief 转码参数定义，支持打包成RTP，PS，TS三种标准类型
struct TransformatParameter
{	
	typedef	enum{
		RtspSvr = 0,            ///< 按照媒体收发属性参数结合服务端属性进行转码参数设置
		RtspClient ,			///< 按照媒体收发属性参数结合客户端属性进行转码参数设置
		TrackID,      			///< 按照trackID方式设置转码参数, 不区分服务端和客户端
		Index,      			///< 按照index索引方式设置转码参数, 不区分服务端和客户端
	}WorkMode;
	typedef enum
	{
		TransTypeNormal,
		TransTypeSmartH264,
		TransTypeMax = (1 << 8),
	}TransType;
	WorkMode mode;
	char sdp[maxSdpLength];		///> 会话描述信息, 当事件为streamEventInitSdpFailed 时，存放流源错误码信息, 见RtspUtil.h中RtspExtErrno 枚举对应的字符串
	uint32_t ssrc;				///> 用于MTS场景下获取StreamSink的ssrc, 加密对讲ssrc需要透传
	TransType type;				///> 需要定制处理的特殊码流，比如smartH264，see@TransType
	struct FileDetailinfo *fileinfo;  ///< 注意指针所指内存的有效性, 文件信息指针,  使用I帧进行分片时组装m3u8列表使用
	uint64_t ts;				///> 转码时间戳信息
	
	TransformatParameter()
		:mode(RtspSvr)
		,type(TransTypeNormal)
	{
		memset(sdp, 0, sizeof(sdp));
		ssrc = 0;
		fileinfo = NULL;
		ts = (uint64_t)-1;
	}
	TransformatParameter(const char *sdpStr, uint32_t Ssrc = 0)
		:mode(RtspSvr)
		,type(TransTypeNormal)
		,fileinfo(NULL)
		,ts((uint64_t)-1)
	{
		if(sdpStr){
			strncpy(sdp, sdpStr, maxSdpLength - 1);
            sdp[maxSdpLength - 1] = '\0';
		}else{
			memset(sdp, 0, sizeof(sdp));
		}
		ssrc = Ssrc;
	}
	TransformatParameter & operator= (const TransformatParameter & rhs)
	{
		if(this==&rhs) return *this;
		mode = rhs.mode;
		strncpy(sdp, rhs.sdp, maxSdpLength);
		ssrc = rhs.ssrc;
		type = rhs.type;
		fileinfo = rhs.fileinfo; // 这里是指针的引用, 注意内存的时效性
		ts = rhs.ts;
		return *this;
	}
};

///\brief 异常的sdp 信息标志
#define SDP_INVALID  	"realsdp:false"		

///\brief 录像播放状态，用于onvif录像回放打RTP扩展头E位
enum FileState
{
	FileStateStart,		///< 文件开始播放
	FileStateEnd,		///< 文件结尾
};

///\brief 转码参数定义，流媒体内部使用
struct TransformatParameterEx
{
	TransformatParameter::WorkMode mode;
	std::string sdp;					  ///< sdp信息
	uint32_t ssrc;						  ///< 用于MTS场景下获取StreamSink的ssrc, 加密对讲ssrc需要透传
	TransformatParameter::TransType type; ///< 需要定制处理的特殊码流，比如smartH264，see@TransType
	struct FileDetailinfo *fileinfo; 	  ///< 注意指针所指内存的有效性, 文件信息指针,  使用I帧进行分片时组装m3u8列表使用
	uint64_t ts;						  ///< 转码时间戳信息 ，目前rtmp点播在用
	bool     realsdp;					  ///< 是否需要真实的sdp 信息
	uint32_t playCSeq;					  ///< play信令序号，用于onvif回放打包
	FileState fileStat;					  ///< 录像播放状态，用于onvif回放打包

	TransformatParameterEx & operator= (const TransformatParameterEx & rhs)
	{
		if(this==&rhs) return *this;
		mode = rhs.mode;
		sdp = rhs.sdp;
		ssrc = rhs.ssrc;
		type = rhs.type;
		fileinfo = rhs.fileinfo; // 这里是指针的引用, 注意内存的时效性
		ts = rhs.ts;
		realsdp = rhs.realsdp;
		playCSeq = rhs.playCSeq;
		fileStat = rhs.fileStat;
		return *this;
	}
	
	TransformatParameterEx(const char * sdpStr, uint32_t Ssrc = 0)
		:mode(TransformatParameter::RtspSvr)
		,type(TransformatParameter::TransTypeNormal)
		,fileinfo(NULL)
		,ts((uint64_t)-1)
		,realsdp(true)
		,playCSeq(0)
		,fileStat(FileStateStart)
	{
		if (sdpStr)
		{
			sdp = std::string(sdpStr);
		}
		ssrc = Ssrc;
	}

	TransformatParameterEx()
		:mode(TransformatParameter::RtspSvr)
		,type(TransformatParameter::TransTypeNormal)
		,realsdp(true)
		,playCSeq(0)
		,fileStat(FileStateStart)
	{
		ssrc = 0;
		fileinfo = NULL;
		ts = (uint64_t)-1;
		sdp = "";
	}

	TransformatParameterEx(const TransformatParameter & parameter)
	{
		mode = parameter.mode;
		sdp = std::string(parameter.sdp);
		ssrc = parameter.ssrc;
		type = parameter.type;
		fileinfo = parameter.fileinfo; // 这里是指针的引用, 注意内存的时效性
		ts = parameter.ts;

		// 如果外部传入的sdp 信息中包含SDP_INVALID 信息,则认为是异常的sdp 
		realsdp = ((std::string::npos != sdp.find(SDP_INVALID))? false: true);
		
		playCSeq = 0;
		fileStat = FileStateStart;
	}
};
class CFrameInfo;

///\brief 描述事件消息的最大长度
enum MaxDescLength
{
	MaxDescLength = 1*1024,
};

///< 流通道事件标志位, 流媒体内部使用
enum StreamTrackEvent
{
	TrackEventVideo			= (1<< TrackVideo), 		 ///< 视频使能位有效
	TrackEventAudioOne		= (1<< TrackAudioOne),		 ///< 第一路音频使能位有效
	TrackEventBackAudio		= (1<< TrackBackAudioChan),  ///< 反向语音使能位有效
	TrackEventTalkAudio		= (1<< TrackTalkAudioChan),	 ///< 正向语音使能位有效
};

///\brief 接收流信息事件配置
enum RecvStreamInfoEvent
{
	StreamRecvframe		= 0x01,		///< 上报收到的帧事件
	StreamRecvLostframe = 0x02,		///< 上报收到的码流丢帧统计事件
};

///< 接收流信息事件, 流媒体内部使用
struct RecvStreamInfo
{
	uint32_t recvInfomask;			 ///< 接收流信息事件掩码, @see RecvStreamInfoEvent
	uint32_t lostduration;			 ///< 接收丢帧的周期性检测时间, 单位毫秒, 表明丢帧的开始后会进行多长时间的检测, 由应用配置	
	uint32_t trackEventmask;		 ///< StreamRecvframe帧事件媒体掩码, @see StreamTrackEvent
	int      reserve[7];
	void    *reservep[4];

	RecvStreamInfo()
	{
		recvInfomask  = 0;		
		lostduration  = DEFAULT_CHECKLOSTFRAME_DURATION * 1000;
		trackEventmask = 0;
		memset(reserve, 0, sizeof(reserve));
		memset(reservep, 0, sizeof(reservep));
	}
};

// 丢帧事件, 指一旦丢帧则进行上报
struct LostFrameInfo
{
	int channelid;				///< 丢帧的媒体trackID
	int lastIndex;				///< 丢帧前的上一帧帧序号
	int newIndex;				///< 丢帧后的第一帧帧序号
	int reserve[4];				///< 保留字段

	LostFrameInfo():channelid(0), lastIndex(0), newIndex(0)
	{
		memset(reserve, 0, sizeof(reserve));
	}
};

// 丢帧事件统计, 指一旦丢帧则统计一段时间内的丢帧,一次性上报
struct LostFrameCalc
{
	int       channelid;		///< 丢帧的媒体trackID
	char     *loststart;		///< 丢帧的起始时间
	uint32_t  calcduration;		///< 丢帧的统计周期, 单位毫秒
	uint32_t  lostNum;			///< 统计周期内总的丢帧数目
	uint32_t  inBandwidth;		///< 丢帧前待发送数据的码流,单位b/s
	uint32_t  outBandwidth;		///< 丢帧前已发送数据的码流, 单位b/s
	uint32_t  lostCount;		///< 统计周期内总的丢帧次数
	int 	  reserve[3];		///< 保留字段

	LostFrameCalc():channelid(0), loststart(NULL), calcduration(0), lostNum(0), inBandwidth(0), outBandwidth(0), lostCount(0)
	{
		memset(reserve, 0, sizeof(reserve));
	}
};

// 帧延时事件统计, 指一旦缓冲超过阈值, 则统计一段时间内的延时, 一次性上报
struct FrameDelayCalc
{
	int       channelid;		///< 帧延时的媒体trackID
	char     *delaystart;		///< 延时的起始时间
	uint32_t  threshold;		///< 丢帧的阈值, 发送队列的数据超过该值则认为延时
	uint32_t  calcduration;		///< 延时的统计周期, 单位毫秒
	uint32_t  maxdelay;			///< 统计周期内的最大延时
	uint32_t  inBandwidth;		///< 延时前待发送数据的码流,单位b/s
	uint32_t  outBandwidth;		///< 延时前已发送数据的码流,单位b/s
	int 	  reserve[4];		///< 保留字段

	FrameDelayCalc():channelid(0), delaystart(NULL), threshold(0), calcduration(0), maxdelay(0), inBandwidth(0), outBandwidth(0)
	{
		memset(reserve, 0, sizeof(reserve));
	}
};

///< 发送流信息事件, 流媒体内部使用
struct SendStreamInfo
{
	uint32_t trackEventmask;		 ///< 发送的媒体事件掩码, @see StreamTrackEvent
	int      reserve[8];
	void    *reservep[4];

	SendStreamInfo()
	{
		trackEventmask  = 0;
		memset(reserve, 0, sizeof(reserve));
		memset(reservep, 0, sizeof(reservep));
	}
};


///\brief description 描述事件类型
enum DescriptionType
{
	DescriptionRtcpBye = 0,    	// description 为char  *
	DescriptionRtcpSR,			// description 为uint8_t *
	DescriptionRtcpRR,		 	// description 为uint8_t *
	DescriptionInterException,	// description 为char *
	DescriptionFrameInfo,		// description 为CFrameInfo* 
	DescriptionLostFrameInfo,	// description 为LostFrameInfo*
	DescriptionLostFrameCalc,	// description 为LostFrameCalc*
	DescriptionFrameDelayCalc,	// description 为FrameDelayCalc*	
};

///\brief 转码参数定义，支持打包成RTP，PS，TS三种标准类型
/// 注意指针都是内存直接引用, 只支持同步调用
struct EventParameter
{	
	DescriptionType descriptype;			///< 事件参数类型
	int 		    mediaIndex;				///< 指示那个对应哪个媒体的事件
	void 		   *description;	    	///< 描述信息, 指针类型对应MediaEventType
	int 		    descLen;				///< description 指针的长度
	
	EventParameter()
	{
		descriptype = DescriptionRtcpBye;
		mediaIndex  = 0;
		description = NULL;
		descLen     = 0;		
	}

	EventParameter(DescriptionType type, int index, void *desc, int len)
	{
		descriptype = type;
		mediaIndex  = index;
		description = desc;
		descLen     = len;				
	}

	EventParameter& operator= (const EventParameter& rhs)
	{
		if(this==&rhs) return *this;
		descriptype = rhs.descriptype;
		mediaIndex  = rhs.mediaIndex;
		descLen     = rhs.descLen;
		description = rhs.description;
		return *this;
	}
};

/////////////////////////////////////////  媒体会话  ///////////////////////////////////////

enum DataDirection
{
	dataIn		= 1 << 0, 			///> 接收数据方向
	dataOut		= 1 << 1, 			///> 发送数据方向
	dataInOut	= dataIn|dataOut,	///> 同时发送和接收数据
};

///\brief 媒体创建请求
struct  MediaCreateInfoRequest
{
	///> Global 参数
	int		sessionDirection;	///> 参考@see DataDirection, dataIn-收流, dataout-发流 ,dataInOut-收发	
	bool	enableRtcp;			///> 是否使能RTCP功能(true-使能打开，false-使能关闭), 该字段废弃, 后续使用MediaConfigInfoRequest 中的字段

	///> dataOut 方向使用参数
	int					dataSourceType;		///> 数据源类型 @see DataSourceType
	const char* 		dataSourceId;		///> 数据源的ID号，例如"cam/realmonitor?channel=1&subtype=0"
	LiveCreateProc		liveStreamProc;  	///> 直播流源创建接口
	VodCreateProc		vodStreamProc;  	///> 点播流源创建接口	
	bool				realsdp;			///> 是否需要真实的sdp 信息	
	uint32_t			segmentduration;	///> 分片时长，目前用于表示HLS分片时长

	MediaCreateInfoRequest()
	{
		sessionDirection = 0;
		enableRtcp       = false;
		dataSourceType   = 0;
		dataSourceId     = NULL;
		realsdp          = true;
		segmentduration	 = 0;
	}	
};


///\brief 媒体配置数据结构请求
struct MediaConfigInfoRequest
{
	int		mediaIndex;			///> 媒体对应的索引号(如SDP信息中的媒体域顺序，该顺序从0开始)
	int		dataDirection;		///> 参考DataDirection定义，针对整个media index的数据流向
	int		transChannel;		///> 该路媒体数据对应的发送通道(在传输通道中使用)
	int		rtcpTransChannel;	///> RTCP使能时，对应的RTCP发送通道
	
	///> 若会话有dataIn属性，标示数据源的打包类型；若会话有dataOut属性，表示目的打包类型
	int		dataPacketType;		///> 打包类型 @see MediaPacketType
	int 		packetSize;			///> 包的大小, 通常这个参数和用户MTU大小一致
	TransformatCreateProc	dataSrcTransformatProc; ///> 数据源转码接口(供发送方使用)
	
	TransformatCreateProc	dataSinkTransformatProc; 	///> 数据槽转码创建接口(供接收方使用)
	TransformatParameterEx dataSinkTranformatParam;	///> 转码参数可能在ConfigMedia时候才知道，CreateMedia就明确转码参数的不必理会该字段
	bool	enableRtcp;                             ///> RTCP 是否使能
};

///\brief 媒体配置响应
struct MediaConfigInfoResponse
{
	int		mediaIndex;			///> 媒体对应的索引号(如SDP信息中的媒体域顺序，该顺序从0开始)
	int		ssrc;				///> 源描述标识, ssrc == 0时，标示为无效标识
};

///\brief 媒体播放数据结构
struct MediaPlayInfoRequest
{
	int 		mediaIndex;	///> 若为-1，则代表已配置的媒体都要进行播放。否则，仅播放mediaIndx代表的这里媒体
	double		speed;		///> 录像回放播放速度
	RangeInfo	rangeInfo;	///> 点播时，表示播放的位置, @see RangeInfo
	bool		only_i_frame;///>点播时，只要求发送I 帧
};

///\brief 媒体播放响应
struct MediaPlayInfoResponse
{
	int 		mediaIndex;				///> 若为-1，则代表已配置的媒体都要进行播放。否则，仅播放mediaIndx代表的这里媒体
	RangeInfo	rangeInfo;				///> 点播时，表示播放的位置
	TrackInfo	trackInfo[MaxTrackNum];	///> 媒体RtpInfo信息,若mediaIndex出现-1情况，代表此为无效值
	bool		clockTimeEnable;		///> 回复clock时间使能配置，目前只有onvif直播拉流回复clock时间
};

///\brief 媒体停止数据结构
struct MediaStopInfoRequest
{
	int		mediaIndex;		///> 媒体索引；-1代表所有媒体；否则代表对应的媒体
};

///\brief流源信息
struct StreamSourceInfo
{
	uint64_t	identifier;
};

}//StreamSvr
}//Dahua
	
#endif //__INCLUDE_DAHUA_STREAMSVR_MEDIAUTILS_H__
