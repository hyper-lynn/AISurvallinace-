/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetShareGuide_H_
#define _HSVIEW_CLIENT_API_GetShareGuide_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取h5弹框提示

【不鉴权】
 */

typedef struct GetShareGuideRequest 
{
	HsviewRequest base;

	struct GetShareGuideRequestData
	{
		
		/** 文案配置标识 */
		CSTR name;

	} data;

} GetShareGuideRequest;

C_API GetShareGuideRequest *HSAPI_INIT(GetShareGuideRequest);

typedef struct GetShareGuideResponse 
{
	HsviewResponse base;

	struct GetShareGuideResponseData
	{
		
		/** [O]跳转详情 */
		CSTR detailUrl;
		/** 描述 */
		CSTR desc;
		/** 标题 */
		CSTR title;
		/** 弹框图片 */
		CSTR coverUrl;
 
	} data;

} GetShareGuideResponse;

C_API GetShareGuideResponse *HSAPI_INIT(GetShareGuideResponse);

#endif
