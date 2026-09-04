#ifndef __DAHUA_STREAMAPP_HTTPFLV_UTIL_H__
#define __DAHUA_STREAMAPP_HTTPFLV_UTIL_H__

#include <string.h>
#include "Infra/Function.h"
#include <string>

namespace Dahua{
namespace StreamApp{

///\brief 请求的url类型
enum httpUrlType
{
	httpUrlTypeLive,									///< 直播Url
	httpUrlTypeVod,										///< 点播Url
	httpUrlTypeUnknown,									///< 未知类型
};

///\brief HTTP-FLV 请求信息
struct httpReqInfo
{
	const char* url;									///< http-flv 请求的url信息
	const char* request;								///< http-flv 请求

	httpReqInfo(): url(NULL), request(NULL)
	{}
	
	httpReqInfo(const char *httpurl, const char *httpreq):url(httpurl), request(httpreq)
	{}
};

///\brief HTTP-FLV 请求解析的url信息
struct httpUrlInfo
{
	httpUrlType			type;							///< http-flv url类型
	int					channel;						///< http-flv url对应的通道号
	int					subtype;						///< http-flv url对应的码流类型	
	int					reserve1[8];					///< 保留参数1
	void   				*reserve2[4];					///< 保留参数2

	httpUrlInfo(): type(httpUrlTypeUnknown), channel(-1), subtype(-1)
	{
		memset(reserve1, 0, sizeof(reserve1));
		memset(reserve2, 0, sizeof(reserve2));
	}
};

///\brief URL 处理函数
///\param [in] httpReqInfo*  -原始的请求信息
///\param [out] std::string& -存放应用修改后的URL内容指针, 如果字符串为0, 则表示不进行修改, 传入值为空字符串
///\param [out] httpUrlInfo*-url 解析的信息
///\param [in] void*             -保留参数
///\return 0: url 合法, -1: 非法的url, 返回404错误
typedef Dahua::Infra::TFunction4<int, httpReqInfo &, std::string &, httpUrlInfo &, void *> HttpUrlMapProc;

enum httpflv_svr_config_t
{
	HttpFlvConfigUrlProc = 0,							///< http-flv url处理函数
	HttpFlvConfigSendBufSize,							///< http-flv 发送缓存区配置, 单位字节
	HttpFlvConfigListenAddr,							///< 配置监听地址
	HttpFlvSvrConfigMax = 100,
};

///\brief http-flv服务监听地址配置
struct httpListenAddrConfig
{
	char addrV4[32];            ///< 监听IPV4地址
	char addrV6[128];           ///< 监听IPV6地址
	char sslAddrV4[32];			///< 监听SSL IPV4地址
	char sslAddrV6[128];		///< 监听SSL IPV6地址
	char reserved[32];          ///< 保留字段

	httpListenAddrConfig()
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

///\brief HTTP-FLV服务类型
enum httpFlvSvrType
{
	httpFlvSvrNoSock,		///< 托管套接字
	httpFlvSvrStream,		///< 非加密套接字
	httpFlvSvrSsl,			///< SSL加密套接字
	httpFlvSvrNum,			///< 未知套接字
};

///\brief sdp 初始化SDP 回调函数
///\param [in] bool                  -初始化成功或者失败
///\param [in] const char *   		-初始化sdp 信息
///\param [in] void *              	-保留参数,暂无作用
typedef Dahua::Infra::TFunction3<void, bool, const char *, void *> InitFlvProc;


}
}

#endif
