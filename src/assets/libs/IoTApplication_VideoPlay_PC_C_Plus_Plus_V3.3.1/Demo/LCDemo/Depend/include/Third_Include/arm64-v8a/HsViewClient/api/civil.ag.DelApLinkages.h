/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_DelApLinkages_H_
#define _HSVIEW_CLIENT_API_DelApLinkages_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
删除配件的联动规则
如果linkages集合为空，则代表删除配件下的所有关联
【需要使用平台账号签名】
 */

typedef struct DelApLinkagesRequest 
{
	HsviewRequest base;

	struct DelApLinkagesRequestData
	{
		
		/** 配件ID */
		CSTR apId;
		/** define a list with struct of DelApLinkagesRequestData_LinkagesElement */
		DECLARE_LIST(struct DelApLinkagesRequestData_LinkagesElement
		{
			/** 关联的设备通道id */
			CSTR linkChannelId;
			/** 关联的设备id */
			CSTR linkDeviceId;
		}) linkages;
		/** 网关的设备ID */
		CSTR deviceId;

	} data;

} DelApLinkagesRequest;

C_API DelApLinkagesRequest *HSAPI_INIT(DelApLinkagesRequest);

typedef struct DelApLinkagesResponse 
{
	HsviewResponse base;

	struct DelApLinkagesResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} DelApLinkagesResponse;

C_API DelApLinkagesResponse *HSAPI_INIT(DelApLinkagesResponse);

#endif
