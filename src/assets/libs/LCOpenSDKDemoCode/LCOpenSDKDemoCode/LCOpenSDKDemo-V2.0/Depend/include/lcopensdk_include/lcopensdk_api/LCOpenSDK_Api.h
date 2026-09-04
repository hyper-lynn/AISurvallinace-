#ifndef _LCOPENSDK_API_H_
#define _LCOPENSDK_API_H_

#include "lcopensdk_global.h"
#include <string.h>

class LCOPENSDK_EXPORT LCOpenSDK_Api
{
private:
	LCOpenSDK_Api();
	~LCOpenSDK_Api();

public:
	static LCOpenSDK_Api* GetInstance();

	/*****************************************************************************
	* @函数功能: 初始化OpenSDK（后续废弃）
	* @返 回 值: 无
	*****************************************************************************/
	void initOpenApi(const char* host, int port, const char* caPath);

	/*****************************************************************************
	* @函数功能: 初始化OpenSDK(建议使用此接口)
	* @返 回 值: 无
	*****************************************************************************/
	void initOpenApiEx(const char* host, int port, const char* caPath, const char* token,const char *appId,const char *appSecret);
	/*****************************************************************************
	* @函数功能: 拉流优化接口，减少出流耗时
	* @参数 1  : token(userToken或accessToken)
	* @参数 2  : 添加设备信息deviceJson[in] json数组格式 [{"PlayToken":string,  "Sn":string}]
	* @返 回 值: 无
	*****************************************************************************/
	void loginStreamServers(const char* token,const char* deviceJson);

	/*****************************************************************************
	* @函数功能: api库请求方式(结构体方式,后续不在维护)
	* @返 回 值: true/false
	*****************************************************************************/
	int request(void* req, void* resp, int timeout, void* pOpenApiClient = 0);

	/*****************************************************************************
	* @函数功能: api库请求方式(URL方式)
	* @返 回 值: true/false
	*****************************************************************************/
	int requestWithURL(const char* url,const char* body,void* resp,int timeout,int isKeepAlive);

	/*****************************************************************************
	* @函数功能: 反初始化OpenSDK(销毁时使用)
	* @返 回 值: 无
	*****************************************************************************/
	void uninitOpenApi();

	void resetToken(const char* token);
	
private:
	void* m_hLCOpenSDK_Api_Inside;
	static LCOpenSDK_Api* sm_instance;

};

#endif /* _LCOPENSDK_API_H_ */
