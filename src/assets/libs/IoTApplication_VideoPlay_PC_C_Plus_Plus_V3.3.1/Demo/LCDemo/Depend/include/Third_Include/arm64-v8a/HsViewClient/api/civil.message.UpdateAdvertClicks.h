/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_UpdateAdvertClicks_H_
#define _HSVIEW_CLIENT_API_UpdateAdvertClicks_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
更新广告页面的点击打开次数
【使用平台账号签名】
 */

typedef struct UpdateAdvertClicksRequest 
{
	HsviewRequest base;

	struct UpdateAdvertClicksRequestData
	{
		
		/** 广告的id */
		CSTR id;

	} data;

} UpdateAdvertClicksRequest;

C_API UpdateAdvertClicksRequest *HSAPI_INIT(UpdateAdvertClicksRequest);

typedef struct UpdateAdvertClicksResponse 
{
	HsviewResponse base;

	struct UpdateAdvertClicksResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} UpdateAdvertClicksResponse;

C_API UpdateAdvertClicksResponse *HSAPI_INIT(UpdateAdvertClicksResponse);

#endif
