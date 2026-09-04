/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_agOperate_GetDeviceChnLinkNum_H_
#define _HSVIEW_CLIENT_API_agOperate_GetDeviceChnLinkNum_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取已经关联配件的设备通道列表关联的配件数量

【需要使用平台账号签名】
 */

typedef struct agOperate_GetDeviceChnLinkNumRequest 
{
	HsviewRequest base;

	struct agOperate_GetDeviceChnLinkNumRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} agOperate_GetDeviceChnLinkNumRequest;

C_API agOperate_GetDeviceChnLinkNumRequest *HSAPI_INIT(agOperate_GetDeviceChnLinkNumRequest);

typedef struct agOperate_GetDeviceChnLinkNumResponse 
{
	HsviewResponse base;

	struct agOperate_GetDeviceChnLinkNumResponseData
	{
		
		/** define a list with struct of agOperate_GetDeviceChnLinkNumResponseData_LinkagesElement */
		DECLARE_LIST(struct agOperate_GetDeviceChnLinkNumResponseData_LinkagesElement
		{
			/** [int]单个设备通道关联配件的最大限制数 */
			int maxNum;
			/** 关联的设备通道id */
			CSTR channelId;
			/** [int]通道已经关联的配件数量 */
			int num;
			/** 关联的设备id */
			CSTR deviceId;
		}) linkages;
 
	} data;

} agOperate_GetDeviceChnLinkNumResponse;

C_API agOperate_GetDeviceChnLinkNumResponse *HSAPI_INIT(agOperate_GetDeviceChnLinkNumResponse);

#endif
