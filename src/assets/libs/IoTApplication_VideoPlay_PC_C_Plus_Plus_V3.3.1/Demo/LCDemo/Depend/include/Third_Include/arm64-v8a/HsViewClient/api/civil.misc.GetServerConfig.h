/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetServerConfig_H_
#define _HSVIEW_CLIENT_API_GetServerConfig_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取其他服务的访问地址，type 传空或者不传，代表查询所有平台配置的服务列表
【需要使用平台账号签名】
 */

typedef struct GetServerConfigRequest 
{
	HsviewRequest base;

	struct GetServerConfigRequestData
	{
		
		/** 服务类型：p2p-p2p服务，pss-统计服务，chat-橙聊服务，pns-PC客户端推送服务 */
		CSTR type;

	} data;

} GetServerConfigRequest;

C_API GetServerConfigRequest *HSAPI_INIT(GetServerConfigRequest);

typedef struct GetServerConfigResponse 
{
	HsviewResponse base;

	struct GetServerConfigResponseData
	{
		
		/** define a list with struct of GetServerConfigResponseData_ServersElement */
		DECLARE_LIST(struct GetServerConfigResponseData_ServersElement
		{
			/** 服务的访问地址 */
			CSTR host;
			/** 服务类型：p2p-p2p服务，pss-统计服务，chat-橙聊服务，pns-PC客户端推送服务 */
			CSTR type;
			/** [int]服务的访问端口 */
			int port;
		}) servers;
 
	} data;

} GetServerConfigResponse;

C_API GetServerConfigResponse *HSAPI_INIT(GetServerConfigResponse);

#endif
