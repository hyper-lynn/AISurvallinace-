/************************************************************************/
/*                                                                      */
/*        华视微讯客户端SDK                dahuatech, 2014              */
/*                                                                      */
/************************************************************************/
#ifndef _HSVIEW_CLIENT_SDK_H_
#define _HSVIEW_CLIENT_SDK_H_

#include "basedef.h"
#include "FreeBuffer.h"
#include "ConstString.h"

// HTTP状态码
#define HTTP_OK						200
#define HTTP_BAD_REQUEST			400
#define HTTP_UNAUTHORIZED			401
#define HTTP_FORBIDDEN				403
#define HTTP_NOT_FOUND				404
#define HTTP_PRECONDITION_FAILED	412

// API返回错误号
#define APICODE_SUCCESS		1000
#define SAAS_APICODE_SUCCESS		10000
// 请求结构体基类
typedef struct HsviewRequest
{
	
	CSTR apiname;
	CSTR fullname;
	CSTR method;
	CSTR uri;
	CSTR sign_headers;
	CSTR content_type;
	CSTR body;
	CSTR svnRev;
	void *metainfo;
	int (*build)(struct HsviewRequest *p);
	int (*sign)(struct HsviewRequest *p, const char *username, const char *password, const char *datetime,const char *sessionId);
	void (*destroy)(struct HsviewRequest *p);
	int  iUseKeepAlive;

} HsviewRequest;

// 响应结构体基类
typedef struct HsviewResponse
{
	CSTR headers;
	CSTR sessionId;
	CSTR date;
	int code;
	CSTR desc;
	int  api_ret_code;
	CSTR str_api_ret_code;
	CSTR api_ret_desc;
	int content_length;
	CSTR content;
	void *metainfo;
	int (*parse)(struct HsviewResponse *p);
	void (*copy)(struct HsviewResponse *p, struct HsviewResponse *src);
	void (*destroy)(struct HsviewResponse *p);
	CSTR api_ret_ext_desc; // 接口返回的扩展描述信息，可用于具体错误信息用
} HsviewResponse;

// 【全局】设置客户端类型
C_API void hsview_client_set_client(const char *type, const char *mac);
C_API void hsview_client_set_client_pushid(const char *pushid);
C_API void hsview_client_set_client_version(const char *version);
C_API void hsview_client_set_project(const char *project);
C_API void hsview_client_set_oldv_appid(const char *appid);
C_API void hsview_client_set_oldv_project(const char *project);


C_API void hsview_client_set_uri_prefix(const char *prefix); //注意: prefix以'/'结束, 如/x/api/
C_API void hsview_client_set_saas_uri_prefix(const char *prefix);
C_API void hsview_client_set_api_version(const char *version);
C_API void hsview_client_set_client_timezone(const char *timezone);
C_API void hsview_client_set_client_OSBits(const char *osBits);
C_API void hsview_client_set_client_ua_info(const char* uaClientType,const char* uaClientVersion,const char* uaClientOV,const char* uaClientOS,const char* uaTerminalModel,const char* uaTerminalId,const char *appId,const char *project,const char *language, const char *uaClientProtocolVersion, const char*uaTimezoneOffset);
C_API void hsview_client_set_saasuri_suffix(const char *suffix);

C_API void hsview_client_set_open_user_id(const char *openUserId);
C_API void hsview_client_set_app_source(const char *appSource);
C_API void hsview_client_set_cos_auth(const char *cosAuth);
C_API void hsview_client_set_cos_request_version(const char *cosReqVer);
C_API void hsview_client_set_cos_signKey(const char *signKey);
C_API void hsview_client_set_Authorization(const char *authorization);

C_API void hsview_client_set_appVersion(const char*appVersion);
C_API void hsview_client_set_phoneId(const char* phoneId);
C_API void hsview_client_set_dolynk_deviceId(const char* dolynkDeviceId);
C_API void hsview_client_set_dolynk_token(const char* dolynkToken);


C_API CSTR hsview_client_get_client_type();
C_API CSTR hsview_client_get_client_mac();
C_API CSTR hsview_client_get_client_pushid();
C_API CSTR hsview_client_get_client_version();
C_API CSTR hsview_client_get_project();
C_API CSTR hsview_client_get_language();
C_API CSTR hsview_client_get_uri_prefix();
C_API CSTR hsview_client_get_saasuri_prefix();
C_API CSTR hsview_client_get_api_version();
C_API CSTR hsview_client_get_client_timezone();
C_API CSTR hsview_client_get_oldv_appid();
C_API CSTR hsview_client_get_oldv_project();
C_API CSTR hsview_client_get_saasuri_suffix();

C_API CSTR hsview_client_get_client_ua_clientType();
C_API CSTR hsview_client_get_client_ua_clientVersion();
C_API CSTR hsview_client_get_client_ua_clientOV();
C_API CSTR hsview_client_get_client_ua_clientOS();
C_API CSTR hsview_client_get_client_ua_terminalModel();
C_API CSTR hsview_client_get_client_ua_terminalId();
C_API CSTR hsview_client_get_client_ua_appid();
C_API CSTR hsview_client_get_client_ua_project();
C_API CSTR hsview_client_get_client_ua_language();
C_API CSTR hsview_client_get_client_ua_clientProtocolVersion();
C_API CSTR hsview_client_get_client_ua_timezoneOffset();
C_API CSTR hsview_client_get_client_ua_OSBits();

C_API CSTR hsview_client_get_open_user_id();
C_API CSTR hsview_client_get_app_source();
C_API CSTR hsview_client_get_cos_auth();
C_API CSTR hsview_client_get_cos_request_version();
C_API CSTR hsview_client_get_cos_signKey();
C_API CSTR hsview_client_get_terminal_Auth();

//new Cos
C_API CSTR hsview_client_get_appVersion();
C_API CSTR hsview_client_get_phoneId();
C_API CSTR hsview_client_get_dolynk_deviceId();
C_API CSTR hsview_client_get_dolynk_token();

// 日志输出等级
//enum
//{
//	LOG_ERROR = 0,
//	LOG_WARN,
//	LOG_INFO,
//	LOG_DEBUG,
//	LOG_VERBOSE
//};
// 日志输出函数原型
typedef void (*HsviewClientLogger)(int level, const char *str);
// 【全局】设置自定义的日志输出函数
C_API void hsview_client_set_logger(HsviewClientLogger logger);

// 客户端句柄
typedef void *HsviewClient;

/* 创建,protoType = 0,http;
		protoType = 1,https.
*/
C_API HsviewClient hsview_client_create(const char *host, int port,int protoType);

// 销毁
C_API void hsview_client_destroy(HsviewClient hc);

// 设置鉴权信息
C_API void hsview_client_set_auth(HsviewClient hc, const char *username, const char *password);

// 设置会话ID
C_API void hsview_client_set_sessionid(HsviewClient hc, const char *sessionId);

/*	设置鉴权信息
	hc			: 客户端实例
	username	: 用户名
	password_md5: 用户密码,经md5加密后的值(32位,小写)
*/
C_API void hsview_client_set_auth_base_md5(HsviewClient hc, const char *username, const char *password_md5);

/* 设置带域账号的签名，如使用appkey+secret签名，使用weixin账号+accesstoken签名
	domain : 当前支持的domain：appkey、weixin和taobao
	account: 域账号
	key	   : 域提供的鉴权key
*/
C_API void hsview_client_set_domain_auth(HsviewClient hc, const char *domain, const char *account, const char *key);

/* set ca switch and path.
*/
C_API void hsview_client_set_ca_info(int bSwitch, const char *sPath);

/* 添加CA证书
	@param sPath : 证书路径
	@return :
		0: 添加成功
	   -1: 添加失败 
*/
C_API int hsview_client_add_ca(const char *sPath);

// 设置REST网络代理：
// enble:启用代理设置正确的代理地址proxyAddr（IP地址：172.25.1.141 或则url）和端口proxyPort（int型数据：例如8001）
C_API void hsview_client_set_proxy(const char *proxyAddr,int proxyPort);
// 清除REST网络代理
C_API void hsview_client_clear_proxy();
// 发送请求，得到响应，timeout超时时间，单位秒
// 成功返回0，失败返回-1

C_API int hsview_client_request(HsviewClient hc, HsviewRequest *req, HsviewResponse *resp, int timeout);
// 建议使用下列宏
C_API int hsview_client_request_with_cost(HsviewClient hc, HsviewRequest *req, HsviewResponse *resp, int timeout, int* sslCost, int* apiCost, const char *requestId, int compress);
C_API int compressGzip(void *dest, int *destLen, const void *source, int sourceLen);
C_API int uncompressGzip (void *dest, int *destLen,const void * source, int *sourceLen);

/// 通过传入uri、body进行请求
/// @param hc 请求句柄
/// @param uri 协议完整路径，如：/pcs/v1/user.account.GetToken
/// @param body json格式请求体，如："{"data":{"gpsInfo":{"longitude":0,"latitude":0}}}"
/// @param resp 请求响应体
/// @param timeout 超时时间
/// @param sslCost ssl耗时
/// @param apiCost api耗时
/// @param requestId 请求id
/// @param compress 是否采用压缩方式请求
C_API int hsview_client_request_with_uri(HsviewClient hc, char *uri, char *body, HsviewResponse *resp, int timeout, int* sslCost, int* apiCost, const char *requestId, int compress);

C_API int hsview_client_request_with_url_body(HsviewClient hc, char *url, char *method, char *contentType, char *headers, char *body, int isUseGzip, char **rspCode, char **rspMsg, char **rspHeaders, char **rspBody, int timeout, int* sslCost, int* apiCost, int isUseAlive);

C_API void hsview_client_clear_all();
// 网络切换时原长连接失效，可使用此接口快速恢复，而不必等心跳超时恢复 
C_API void hsview_client_refresh_longlives();

C_API int hmac_sha256_base64_encrypt(const char* srcBuf, int srcLen, const char* key, int keyLen, char* outBuf, int* outLen);

#define HSAPI_INIT(name)		hsview_api_init_##name()
#define HSAPI_COPY(dst, src)	(dst)->base.copy(&(dst)->base, &(src)->base)
#define HSAPI_DESTROY(ptr)		(ptr)->base.destroy(&(ptr)->base)

#define HSAPI_REQUEST(hc, req, resp, timeout)	hsview_client_request(hc, (HsviewRequest *)req, (HsviewResponse *)resp, timeout)
#define HSAPI_REQUEST_WITH_COST(hc, req, resp, timeout,sslCost,apiCost,requestId,compress) hsview_client_request_with_cost(hc, (HsviewRequest *)req, (HsviewResponse *)resp, timeout,&sslCost,&apiCost,requestId,compress)
#define HSAPI_REQUEST_WITH_URI(hc, uri, body, resp, timeout, sslCost, apiCost, requestId, compress) hsview_client_request_with_uri(hc, (char *)uri, (char *)body, (HsviewResponse *)resp, timeout, &sslCost, &apiCost, requestId, compress)

#endif
