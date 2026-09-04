/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_agOperate_DelApLinkages_H_
#define _HSVIEW_CLIENT_API_agOperate_DelApLinkages_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
删除配件的联动规则

linkages不能为空。
【需要使用平台账号签名】
 */

typedef struct agOperate_DelApLinkagesRequest 
{
	HsviewRequest base;

	struct agOperate_DelApLinkagesRequestData
	{
		
		/** 配件ID */
		CSTR apId;
		/** define a list with struct of agOperate_DelApLinkagesRequestData_LinkagesElement */
		DECLARE_LIST(struct agOperate_DelApLinkagesRequestData_LinkagesElement
		{
			/** 关联的设备通道id */
			CSTR linkChannelId;
			/** 关联的设备id */
			CSTR linkDeviceId;
		}) linkages;
		/** 网关的设备ID */
		CSTR deviceId;

	} data;

} agOperate_DelApLinkagesRequest;

C_API agOperate_DelApLinkagesRequest *HSAPI_INIT(agOperate_DelApLinkagesRequest);

typedef struct agOperate_DelApLinkagesResponse 
{
	HsviewResponse base;

	struct agOperate_DelApLinkagesResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} agOperate_DelApLinkagesResponse;

C_API agOperate_DelApLinkagesResponse *HSAPI_INIT(agOperate_DelApLinkagesResponse);

#endif
