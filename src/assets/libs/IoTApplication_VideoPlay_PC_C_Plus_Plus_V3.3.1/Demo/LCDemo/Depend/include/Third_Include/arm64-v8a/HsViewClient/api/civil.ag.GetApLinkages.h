/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetApLinkages_H_
#define _HSVIEW_CLIENT_API_GetApLinkages_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取配件的联动列表，preset为空则代表不使用预置点

【需要使用平台账号签名】
 */

typedef struct GetApLinkagesRequest 
{
	HsviewRequest base;

	struct GetApLinkagesRequestData
	{
		
		/** 配件ID */
		CSTR apId;
		/** 网关的设备ID */
		CSTR deviceId;

	} data;

} GetApLinkagesRequest;

C_API GetApLinkagesRequest *HSAPI_INIT(GetApLinkagesRequest);

typedef struct GetApLinkagesResponse 
{
	HsviewResponse base;

	struct GetApLinkagesResponseData
	{
		
		/** define a list with struct of GetApLinkagesResponseData_LinkagesElement */
		DECLARE_LIST(struct GetApLinkagesResponseData_LinkagesElement
		{
			/** 关联的设备id */
			CSTR linkDeviceId;
			/** struct of GetApLinkagesResponseData_LinkagesElement_Preset */
			struct GetApLinkagesResponseData_LinkagesElement_Preset {
				/** [double]水平位置：归一化到-1~1，表示水平经度-180°到180° */
				double H;
				/** [double]变倍倍数：归一化到0~1，其中0表示缩到最小，1表示放到最大 */
				double Z;
				/** [double]垂直位置：归一化到-1~1，表示垂直维度-90°到90° */
				double V;
			} preset;
			/** 关联的设备通道id */
			CSTR linkChannelId;
		}) linkages;
 
	} data;

} GetApLinkagesResponse;

C_API GetApLinkagesResponse *HSAPI_INIT(GetApLinkagesResponse);

#endif
