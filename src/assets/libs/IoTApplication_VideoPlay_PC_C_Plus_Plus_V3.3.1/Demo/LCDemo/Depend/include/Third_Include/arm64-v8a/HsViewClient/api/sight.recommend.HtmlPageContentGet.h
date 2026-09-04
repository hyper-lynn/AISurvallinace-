/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_sightRecommend_HtmlPageContentGet_H_
#define _HSVIEW_CLIENT_API_sightRecommend_HtmlPageContentGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取微信页面数据
【不鉴权】
 */

typedef struct sightRecommend_HtmlPageContentGetRequest 
{
	HsviewRequest base;

	struct sightRecommend_HtmlPageContentGetRequestData
	{
		
		/** 微信url，不包含域名 */
		CSTR url;

	} data;

} sightRecommend_HtmlPageContentGetRequest;

C_API sightRecommend_HtmlPageContentGetRequest *HSAPI_INIT(sightRecommend_HtmlPageContentGetRequest);

typedef struct sightRecommend_HtmlPageContentGetResponse 
{
	HsviewResponse base;

	struct sightRecommend_HtmlPageContentGetResponseData
	{
		
		/** 页面内容 */
		CSTR content;
 
	} data;

} sightRecommend_HtmlPageContentGetResponse;

C_API sightRecommend_HtmlPageContentGetResponse *HSAPI_INIT(sightRecommend_HtmlPageContentGetResponse);

#endif
