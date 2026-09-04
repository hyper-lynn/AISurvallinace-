#ifndef __DAHUA_STREAMAPP_HLSUTIL_H__
#define __DAHUA_STREAMAPP_HLSUTIL_H__

#include <string.h>
#include "Infra/Function.h"
#include "StreamSvr/Protocol/RtspUtil.h"
#include "NetFramework/Sock.h"

namespace Dahua{
namespace StreamApp{

///\brief  hls Ts 流的出流处理策略
enum streamstrategy
{
	optimizedisplay = 0,    ///< 图像显示速度优化策略
	optimizedelay,			///< 图像画面延时优化策略
};

///\brief HLS 协议支持的分片类型
enum SegmentsType
{	
	UnkonwnSegments = -1,	///< 未知
	TsSegments 		= 0,	///< ts分片
	Fmp4Segments,			///< fmp4分片
};

///\brief  hls Ts 流的切片配置
struct tsSliceConfig
{
	int liveduration;              	///< 直播流切片长度, 单位秒
	int vodduration;			   	///< 点播流源切片长度, 单位秒, 该值已废弃	
	int tslivenum;				   	///< ts 直播流切片缓冲数目
	int livedelay;				   	///< 直播流源未引用时的存活时间, 单位为秒
	int voddelay;				   	///< 录像流源未引用时的存活时间, 单位为秒
	int initlivetsnum;			   	///<  直播时返回m3u8列表要求的分片缓冲数目, 该配置应小于或等于tslivenum, 默认3个分片
	int transportstrategy;		   	///<  直播优化策略, 图像显示速度优化策略或者图像画面延时优化策略
	int fmp4livenum;				///< fmp4 直播切片缓冲数目
	int reserve[1];			  		///< 保留数据
	
	tsSliceConfig()
	{
		liveduration = 10;
		vodduration = 10;
		tslivenum = 3;
		livedelay = 300;
		voddelay = 600;
		initlivetsnum = 3;
		transportstrategy = optimizedisplay;     ///< 直播传输策略默认是图像显示速度优化策略
		fmp4livenum	= 3;
		memset(reserve, 0, sizeof(reserve));
	}
};

///\brief hls 会话长时间未收到请求的保活时间配置 
struct aLiveConfig
{
	int live;     // 直播请求会话超时时间, 单位为秒
	int vod;      // 点播请求会话超时时间, 单位为秒
	aLiveConfig()
	{
		live = 300;   
		vod = 600;
	}
};

///\brief hls 请求信息
struct hlsReqInfo 
{
	const char* url;       ///< hls 请求提取的url 信息
	const char* request;   ///< hls 请求

	hlsReqInfo():url(NULL), request(NULL)
	{}

	hlsReqInfo(const char *hlsurl, const char *hlsreq):url(hlsurl), request(hlsreq)
	{}
};

///\brief hls 解析的url 信息
struct hlsUrlInfo 
{
	int   channel;			///< hls url 对应的通道号
	int   reserve1[8];		///< 保留参数1
	void *reserve2[4];      ///< 保留参数2
	hlsUrlInfo():channel(-1)
	{
		memset(reserve1, 0, sizeof(reserve1));
		memset(reserve2, 0, sizeof(reserve2));
	}
};

///\brief hls 标准鉴权配置
struct hlsAuth
{
	int  authtype;			///< hls 鉴权类型
	bool checkchn;			///< 是否开启按通道鉴权
	int  reserve[4];		///< 保留参数

	hlsAuth():authtype(StreamSvr::authTypeNum), checkchn(false)
	{
		memset(reserve, 0, sizeof(reserve));
	}
};

///\brief hls服务类型
enum hlsServerType
{
	streamServer = 0,     ///< hls非加密服务
	streamSslServer,      ///< hls ssl加密服务
};

///\brief hls流量统计配置
struct hlsMediaFlowConfig
{
	bool liveflowenable;          ///< 是否开启hls 直播流量统计
	bool vodflowenable;           ///< 是否开启hls 点播流量统计
	int  reserve[4];              ///< 保留字段,暂未使用

	hlsMediaFlowConfig():liveflowenable(false), vodflowenable(false)
	{
		memset(reserve, 0, sizeof(reserve));
	}
};

///\brief 统计类型
enum hlsStatisticType
{
	FlowStatistic,              ///< 流量统计
};

///\brief hls流量统计信息
struct hlsFlowInfo
{
	uint64_t liveflow;          ///< hls直播流量, 单位KB
	uint64_t vodflow;           ///< hls点播流量, 单位KB
	int reserve[4];             ///< 保留字段，暂未使用

	hlsFlowInfo()
	{
		liveflow         = 0;
		vodflow          = 0;
		memset(reserve, 0, sizeof(reserve));
	}	
};

#define HLSKBLEN 1024

///\brief URL 处理函数
///\param [in] hlsReqInfo*  -原始的请求信息
///\param [out] std::string& -存放应用修改后的URL内容指针, 如果字符串为0, 则表示不进行修改, 传入值为空字符串
///\param [out] hlsUrlInfo*-url 解析的信息
///\param [in] void*             -保留参数
///\return 0: url 合法, -1: 非法的url, 返回404错误
typedef Dahua::Infra::TFunction4<int, hlsReqInfo&, std::string&, hlsUrlInfo&, void *> HlsUrlMapProcEx;

///\brief 外部鉴权函数
///\param [in] StreamSvr::ConfigAuthType -当前的鉴权类型
///\param [in] const char* -url 信息
///\param [in] const char* -远端的ip 信息
///\param [in] const char* -全部的请求信息
///\param [in] void *           -保留参数
///\return 0 鉴权通过, -1 鉴权失败
typedef Dahua::Infra::TFunction5<int, StreamSvr::ConfigAuthType &, const char *, const char *, const char *, void *> HlsAuthProc;

///\brief 分片更新回调函数
///\param [in] char* 	   -分片url 指针
///\param [in] int                 -保留参数
///\param [in] void*            -保留参数
///\return true-成功, false-上层认为异常,需要断开会话
typedef Dahua::Infra::TFunction3<bool, const char*, int, void *> TsSegProc;

// m3u8 列表初始化事件
enum TsEvent
{
	m3u8listok = 0,
	m3u8listerror,
};

///\brief m3u8列表初始化事件回调函数
///\param [in] const char* -m3u8 列表对应的分片url
///\param [in] int 	           -初始化结果, 见TsEvent
///\param [in] void *           -保留参数,暂无作用
typedef	Dahua::Infra::TFunction3<void, const char*, int, void *> TsEventProc;

///\brief sdp 初始化SDP 回调函数
///\param [in] bool                  -初始化成功或者失败
///\param [in] const char *   -初始化sdp 信息
///\param [in] void *              -保留参数,暂无作用
typedef Dahua::Infra::TFunction3<void, bool, const char *, void *> InitEventProc;	

///\brief 基于端口复用的回调处理函数
///\param [in] Memory::TSharedPtr<NetFramework::CSock> & 	-连接套接字 ,调用该函数后该套接字由上层管理
///\param [in] const char *									-收到的HTTP消息
///\param [in] int											-收到消息的长度
///\return 0 成功, -1 失败
typedef Infra::TFunction3<int, Memory::TSharedPtr<NetFramework::CSock> &, const char*, int> HlsPortReuseProc;

///\brief 基于端口复用的过滤函数 
///\param [in] const char *									-收到的HTTP消息
///\param [in] int											-收到消息的长度
///\return 0 成功, -1 失败，表示该请求不是上层应用所需要的请求
typedef Infra::TFunction2<int, const char *, int> HlsPortReuseFilterProc;


// hls 支持切片的初始化方式
enum InitTsType
{
	InitTsAuto   = (1 << 0),		///< 收到请求自动初始化切片
	InitTsManual = (1 << 1), 		///< 上层通过Initm3u8list 接口进行切片的初始化, 暂时总是支持
};

// hls 支持的端口连接类型
enum HlsPortService
{
	HlsPortListen = (1 << 0),		///< 独立使用端口进行监听
	HlsPortReuse  = (1 << 1), 		///< 使用webapp 的端口复用功能进行监听
};

enum hls_svr_config_t
{
	HlsConfigSlice = 0,			///<  hls 切片配置
	HlsConfigUrlOldProc,		///<  hls url 映射函数, 该配置已废弃, 请不要设置, 如需要请采用HlsConfigUrlProcEx
	HlsConfigDomainxml,			///<  hls 跨域字符串配置, 本来是读文件的,简化处理,由外部传入字符串
	HlsConfigTsEventProc,		///<  hls m3u8列表初始化回调函数
	HlsConfigInitTsType,		///<  hls 切片初始化方式, 根据InitTsType 按位进行设置, 默认都支持
	HlsConfigAlive,				///<  hls 会话长时间没有信令请求的保活时间配置,配置为aLiveConfig
	HlsConfigCharMap,			///<  是否映射http 特殊字符, 由于仅在低版本vlc中遇见,为了提高效率,使用配置控制
	HlsConfigm3u8EndSingChar,	///<  m3u8列表以单个\n字符换行,解决某些客户端不识别\r\n 换行的问题
	HlsConfigMaxConns,			///<  HLS 会话长连接最大连接数目
	HlsConfigTssegProc,			///<  HLS 分片更新回调配置
	HlsConfigVodSegUnique,		///<  HLS 回放url 对应的分片唯一化配置
	HlsConfigHttpHead,          ///<  HLS Http 回复头部字段配置
	HlsConfigPortService,       ///<  HLS 端口监听类型配置, 见	HlsPortService, 默认只支持独立端口监听
	HlsConfigAuthProc,          ///<  HLS 鉴权回调配置, 配置为HlsAuthProc, 该配置优先于HlsConfigAuthType
	HlsConfigUrlProcEx,         ///<  HLS url 处理函数, 配置为HlsUrlMapProcEx
	HlsConfigAuthType,          ///<  HLS 标准鉴权类型, 配置见hlsAuthType
	HlsConfigMediaFlowCalc,     ///<  HLS服务流量统计配置,配置见hlsMediaFlowConfig
	HlsConfigDisConnect,        ///<  编码配置发生变化时，服务端是否主动断开HLS 会话
	HlsConfigVodSpeed,			///<  HLS 回放请求流源速率配置
	HlsConfigHostInfo,			///<  HLS服务器的主机地址信息，配置为string类型，如果该信息不为空，则ts分片地址信息使用绝对地址，否则使用相对地址
	HlsConfigConnectionClose,	///<  HLS服务器只支持短连接使能配置，配置为bool类型，如果不设置则为false，HLS服务发送的Connection字段以客户端请求为准
	HlsConfigSendBufSize,		///<  HLS服务器发送媒体数据的缓冲区大小.opt配置以字节为单位
	HlsConfigDelayReplyTsNum,	///<  HLS 直播时第一次回复m3u8 后由异步回复转为同步回复需要的分片数目, 默认为1 ,如果需要立刻返回m3u8 可以配置为0
};

}
}

#endif

