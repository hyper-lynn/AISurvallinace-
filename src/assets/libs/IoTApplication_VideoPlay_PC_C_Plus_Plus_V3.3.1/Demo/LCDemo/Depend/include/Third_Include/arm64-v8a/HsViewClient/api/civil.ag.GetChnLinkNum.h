/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetChnLinkNum_H_
#define _HSVIEW_CLIENT_API_GetChnLinkNum_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取通道列表关联的配件数量

【需要使用平台账号签名】
 */

typedef struct GetChnLinkNumRequest 
{
	HsviewRequest base;

	struct GetChnLinkNumRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} GetChnLinkNumRequest;

C_API GetChnLinkNumRequest *HSAPI_INIT(GetChnLinkNumRequest);

typedef struct GetChnLinkNumResponse 
{
	HsviewResponse base;

	struct GetChnLinkNumResponseData
	{
		
		/** define a list with struct of GetChnLinkNumResponseData_LinkagesElement */
		DECLARE_LIST(struct GetChnLinkNumResponseData_LinkagesElement
		{
			/** [bool]true-达到限制  false-未达到限制 */
			BOOL isExceed;
			/** 关联的设备通道id */
			CSTR channelId;
			/** [int]通道已经关联的配件数量 */
			int num;
			/** 关联的设备id */
			CSTR deviceId;
		}) linkages;
 
	} data;

} GetChnLinkNumResponse;

C_API GetChnLinkNumResponse *HSAPI_INIT(GetChnLinkNumResponse);

#endif
