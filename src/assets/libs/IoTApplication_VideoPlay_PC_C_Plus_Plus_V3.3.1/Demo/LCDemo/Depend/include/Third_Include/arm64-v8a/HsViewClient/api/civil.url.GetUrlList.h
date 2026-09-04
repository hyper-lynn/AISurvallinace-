/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetUrlList_H_
#define _HSVIEW_CLIENT_API_GetUrlList_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
私有云定制接口：获取视频广场url

【平台账号鉴权】
 */

typedef struct GetUrlListRequest 
{
	HsviewRequest base;

	struct GetUrlListRequestData
	{
		
		/** [int]直播类型，0:直播活动页面（其他类型待扩展） */
		int type;

	} data;

} GetUrlListRequest;

C_API GetUrlListRequest *HSAPI_INIT(GetUrlListRequest);

typedef struct GetUrlListResponse 
{
	HsviewResponse base;

	struct GetUrlListResponseData
	{
		
		/** define a list with struct of GetUrlListResponseData_ListElement */
		DECLARE_LIST(struct GetUrlListResponseData_ListElement
		{
			/** 活动页面地址 */
			CSTR url;
			/** [int]直播活动页面（其他类型待扩展） */
			int type;
		}) list;
 
	} data;

} GetUrlListResponse;

C_API GetUrlListResponse *HSAPI_INIT(GetUrlListResponse);

#endif
