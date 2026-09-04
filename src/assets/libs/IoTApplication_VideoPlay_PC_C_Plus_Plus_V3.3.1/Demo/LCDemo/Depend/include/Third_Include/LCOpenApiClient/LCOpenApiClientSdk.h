/************************************************************************/
/*                                                                      */
/*        华视微讯客户端SDK                dahuatech, 2014              */
/*                                                                      */
/************************************************************************/
#ifndef _LC_OPENAPI_CLIENT_SDK_H_
#define _LC_OPENAPI_CLIENT_SDK_H_

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

// 请求结构体基类
typedef struct LCOpenApiRequest
{
	CSTR apiname;
	CSTR fullname;
	CSTR method;
	CSTR uri;
	CSTR content_type;
	CSTR body;

	CSTR params;
	CSTR messageId;
	CSTR time;
	CSTR nonce;
	CSTR signMd5;
	CSTR signSaas4Dcloud;
	CSTR signSaas4Cos;
	CSTR contentMd5;
    CSTR signPaasAuth;

	void *metainfo;
	//for doLynk
	CSTR dolynk_deviceId;

    //for paas
    CSTR paasAccessToken;
    CSTR paasDeviceId;
    CSTR paasChannelId;
    
    // for iot-pgw
    CSTR iotAccessToken;

	//platform
	CSTR sourceType; //paas,lc
	CSTR host;
	int port;
	CSTR uriPrefix;
	int protoType;

	int (*build)(struct LCOpenApiRequest *p);
	int (*sign)(struct LCOpenApiRequest *p, const char *appId, const char *appSecret, const char *time);
	int (*signSaas)(struct LCOpenApiRequest *p, const char *username, const char *pwd, const char *uaInfo);
    int (*signPaas)(struct LCOpenApiRequest *p, const char *appId, const char *appSecret, const char *time);
	void (*destroy)(struct LCOpenApiRequest *p);
	int  iUseKeepAlive;
} LCOpenApiRequest;

// 响应结构体基类
typedef struct LCOpenApiResponse
{
	CSTR headers;
	int code;
	CSTR date;
	CSTR desc;
	int content_length;
	CSTR content;

	CSTR id;
	CSTR ret_code;
	CSTR ret_msg;
	int  ret_success;

	//platform
	CSTR sourceType; //paas,lc

	void *metainfo;

	int (*parse)(struct LCOpenApiResponse *p);
	void (*copy)(struct LCOpenApiResponse *p, struct LCOpenApiResponse *src);
	void (*destroy)(struct LCOpenApiResponse *p);
} LCOpenApiResponse;

// 【全局】设置客户端类型
C_API void lcopenapi_client_set_client(const char *type, const char *mac);
C_API void lcopenapi_client_set_os_version(const char *version);
C_API void lcopenapi_client_set_sdk_version(const char *version);
C_API void lcopenapi_client_set_safe_code(const char *bundleId);
C_API void lcopenapi_client_set_api_version(const char *version);
C_API void lcopenapi_client_set_ca_path(int isDisableCA,const char *caPath);

C_API void lcopenapi_client_set_uri_prefix(const char *prefix);
C_API void lcopenapi_client_set_appId(const char *appId);
C_API void lcopenapi_client_set_appSecret(const char *appSecret);

C_API void lcopenapi_client_set_open_user_id(const char *openUserId);
C_API void lcopenapi_client_set_app_source(const char *appSource);
C_API void lcopenapi_client_set_username(const char *username);
C_API void lcopenapi_client_set_pwd(const char *pwd);
C_API void lcopenapi_client_set_client_ua_info(const char *clientUaInfo);
C_API void lcopenapi_client_set_cos_auth(const char *cosAuth);
C_API void lcopenapi_client_set_cos_request_version(const char *cosReqVer);
C_API void lcopenapi_client_set_cos_signKey(const char *signKey);
C_API void lcopenapi_client_set_terminal_auth(const char *authorization);
C_API void lcopenapi_client_set_terminal_companyId(const char *companyId);

/*物联中控协议增加设置token字段*/
C_API void lcopenapi_client_set_dolynk_token(const char* token);
C_API void lcopenapi_client_set_dolynk_deviceId(const char* deviceId);

C_API void lcopenapi_client_set_phoneId(const char* phoneId);
C_API void lcopenapi_client_set_appVersion(const char* appVersion);

// for paas
C_API void lcopenapi_client_set_paas_appId(const char *appId);
C_API void lcopenapi_client_set_paas_appSecret(const char *appSecret);
C_API void lcopenapi_client_set_paas_deviceId(const char* deviceId);
C_API void lcopenapi_client_set_paas_channelId(const char* channelId);

C_API CSTR lcopenapi_client_get_client_type();
C_API CSTR lcopenapi_client_get_client_mac();
C_API CSTR lcopenapi_client_get_os_version();
C_API CSTR lcopenapi_client_get_sdk_version();
C_API CSTR lcopenapi_client_get_safe_code();
C_API CSTR lcopenapi_client_get_api_version();
C_API CSTR lcopenapi_client_get_ca_path();
C_API int  lcopenapi_client_get_isDisableCa();

C_API CSTR lcopenapi_client_get_version();
C_API CSTR lcopenapi_client_get_uri_prefix();
C_API CSTR lcopenapi_client_get_appId();
C_API CSTR lcopenapi_client_get_appSecret();
C_API CSTR lcopenapi_client_get_username();
C_API CSTR lcopenapi_client_get_pwd();
C_API CSTR lcopenapi_client_get_client_ua_info();
C_API CSTR lcopenapi_client_get_cos_auth();
C_API CSTR lcopenapi_client_get_cos_request_version();
C_API CSTR lcopenapi_client_get_cos_signKey();
C_API CSTR lcopenapi_client_get_terminal_auth();
C_API CSTR lcopenapi_client_get_terminal_companyId();

/*物联中控协议增加获取token字段*/
C_API CSTR lcopenapi_client_get_dolynk_token();
C_API CSTR lcopenapi_client_get_dolynk_deviceId();

C_API CSTR lcopenapi_client_get_appVersion();
C_API CSTR lcopenapi_client_get_phoneId();

// for paas
C_API CSTR lcopenapi_client_get_paas_appId();
C_API CSTR lcopenapi_client_get_paas_appSecret();
C_API CSTR lcopenapi_client_get_paas_deviceId();
C_API CSTR lcopenapi_client_get_paas_channelId();

C_API unsigned int lcopenapi_client_get_serialNo();

// 日志输出函数原型
typedef void (*LCOpenApiClientLogger)(int level, const char *str);
// 【全局】设置自定义的日志输出函数
C_API void lcopenapi_client_set_logger(LCOpenApiClientLogger logger);

// 客户端句柄
typedef void *LCOpenApiClient;

// 创建
C_API LCOpenApiClient lcopenapi_client_create(const char *host, int port, const char* sourceType);

// 销毁
C_API void lcopenapi_client_destroy(LCOpenApiClient hc);

C_API CSTR lcopenapi_client_get_access_source(LCOpenApiClient hc);


//C_API void lcopenapi_client_set_domain_auth(LCOpenApiClient hc, const char *domain, const char *account, const char *key);

// 发送请求，得到响应，timeout超时时间，单位秒
// 成功返回0，失败返回-1
C_API int lcopenapi_client_request(LCOpenApiClient hc, LCOpenApiRequest *req, LCOpenApiResponse *resp, int timeout);

C_API int lcopenapi_client_requestEx(LCOpenApiClient hc, char *url, char *method, char *contentType, char *headers, char *body, int isUseGzip,char **rspCode, char **rspMsg, char **rspHeaders, char **rspBody, int timeout, int isUseAlive, int nReqIndex, int nPriority);

C_API char* lcopenapi_client_get_os_versionEx(char* osVersion, int len);
C_API char* lcopenapi_client_get_client_ua_infoEx(char* uaInfo, int len);
C_API char* lcopenapi_client_get_cos_request_versionEx(char* requestVersion, int len);
C_API char* lcopenapi_client_get_sdk_versionEx(char* sdkVersion, int len);
C_API char* lcopenapi_client_get_api_versionEx(char* apiVersion, int len);
C_API char* lcopenapi_client_get_terminal_companyIdEx(char* terminalCompanyId, int len);
C_API char* lcopenapi_client_get_appVersionEx(char* appVersion, int len);
C_API char* lcopenapi_client_get_phoneIdEx(char* phoneId, int len);
C_API char* lcopenapi_client_get_usernameEx(char* userName, int len);
C_API char* lcopenapi_client_get_pwdEx(char* pwd, int len);
C_API char* lcopenapi_client_get_ca_pathEx(char* caPath, int len);
C_API char* lcopenapi_client_get_appIdEx(char* appId, int len);
C_API char* lcopenapi_client_get_appSecretEx(char* appSecret, int len);
C_API char* lcopenapi_client_get_safe_codeEx(char* safeCode, int len);
C_API char* lcopenapi_client_get_cos_signKeyEx(char* signKey, int len);
C_API char* lcopenapi_client_get_cos_authEx(char* cosAuth, int len);
C_API char* lcopenapi_client_get_uri_prefixEx(char* uriPrefix, int len);
C_API char* lcopenapi_client_get_terminal_authEx(char* terminalAuth, int len);
C_API char* lcopenapi_client_get_dolynk_tokenEx(char* dolynkToken, int len);
C_API char* lcopenapi_client_get_dolynk_deviceIdEx(char* dolynkDeviceId, int len);

// 建议使用下列宏
#define LCOPENAPI_INIT(name)		lcopenapi_api_init_##name()
#define LCOPENAPI_COPY(dst, src)	(dst)->base.copy(&(dst)->base, &(src)->base)
#define LCOPENAPI_DESTROY(ptr)		(ptr)->base.destroy(&(ptr)->base)

#define LCOPENAPI_REQUEST(hc, req, resp, timeout)	lcopenapi_client_request(hc, (LCOpenApiRequest *)req, (LCOpenApiResponse *)resp, timeout)

#endif
