/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_agOperate_GetApLinkages_H_
#define _HSVIEW_CLIENT_API_agOperate_GetApLinkages_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取配件的联动列表

【需要使用平台账号签名】
 */

typedef struct agOperate_GetApLinkagesRequest 
{
	HsviewRequest base;

	struct agOperate_GetApLinkagesRequestData
	{
		
		/** 配件ID */
		CSTR apId;
		/** 网关的设备ID */
		CSTR deviceId;

	} data;

} agOperate_GetApLinkagesRequest;

C_API agOperate_GetApLinkagesRequest *HSAPI_INIT(agOperate_GetApLinkagesRequest);

typedef struct agOperate_GetApLinkagesResponse 
{
	HsviewResponse base;

	struct agOperate_GetApLinkagesResponseData
	{
		
		/** define a list with struct of agOperate_GetApLinkagesResponseData_LinkagesElement */
		DECLARE_LIST(struct agOperate_GetApLinkagesResponseData_LinkagesElement
		{
			/** 关联的设备id */
			CSTR linkDeviceId;
			/** [int]是否设置过摄像机云台位置，0-否，1-是 */
			int hasPreset;
			/** 关联的设备通道id */
			CSTR linkChannelId;
		}) linkages;
 
	} data;

} agOperate_GetApLinkagesResponse;

C_API agOperate_GetApLinkagesResponse *HSAPI_INIT(agOperate_GetApLinkagesResponse);

#endif
