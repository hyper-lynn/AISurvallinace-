/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetPublicPages_H_
#define _HSVIEW_CLIENT_API_GetPublicPages_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取页面的入口地址url，type 传空或者不传，代表查询所有平台配置的服务列表

type 页面类型：lcnews-乐橙资讯页面，sysmsg-系统消息页面，activitymsg-活动消息页面 。。。。
【不需要鉴权】
 */

typedef struct GetPublicPagesRequest 
{
	HsviewRequest base;

	struct GetPublicPagesRequestData
	{
		
		/** 页面类型,为空代表查询所有的页面列表 */
		CSTR type;

	} data;

} GetPublicPagesRequest;

C_API GetPublicPagesRequest *HSAPI_INIT(GetPublicPagesRequest);

typedef struct GetPublicPagesResponse 
{
	HsviewResponse base;

	struct GetPublicPagesResponseData
	{
		
		/** define a list with struct of GetPublicPagesResponseData_PagesElement */
		DECLARE_LIST(struct GetPublicPagesResponseData_PagesElement
		{
			/** 页面的访问地址url */
			CSTR url;
			/** 页面类型 */
			CSTR type;
			/** [O]图标名称 */
			CSTR name;
			/** [O]图标url */
			CSTR logoUrl;
		}) pages;
 
	} data;

} GetPublicPagesResponse;

C_API GetPublicPagesResponse *HSAPI_INIT(GetPublicPagesResponse);

#endif
