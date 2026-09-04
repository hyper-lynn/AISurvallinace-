/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetClientConfig_H_
#define _HSVIEW_CLIENT_API_GetClientConfig_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取app的配置文件，用于app动态更新本地的配置文件
如果配置文件app和pc等使用的不一致，则通过clientType进行区分处理；

【不需要签名】
 */

typedef struct GetClientConfigRequest 
{
	HsviewRequest base;

	struct GetClientConfigRequestData
	{
		
		/** 配置文件类型：remind-提醒配置 */
		CSTR type;

	} data;

} GetClientConfigRequest;

C_API GetClientConfigRequest *HSAPI_INIT(GetClientConfigRequest);

typedef struct GetClientConfigResponse 
{
	HsviewResponse base;

	struct GetClientConfigResponseData
	{
		
		/** [long]文件最后更新的时间戳 */
		int64 ts;
		/** 配置文件的下载地址 */
		CSTR url;
 
	} data;

} GetClientConfigResponse;

C_API GetClientConfigResponse *HSAPI_INIT(GetClientConfigResponse);

#endif
