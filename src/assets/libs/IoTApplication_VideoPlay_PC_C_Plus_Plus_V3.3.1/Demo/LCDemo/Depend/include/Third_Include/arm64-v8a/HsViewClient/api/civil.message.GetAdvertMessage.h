/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetAdvertMessage_H_
#define _HSVIEW_CLIENT_API_GetAdvertMessage_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取定向发布的广告信息和logo信息。

如果橙商有自定义信息，同步返回

这里的时间格式为UNIX时间戳（1970年开始的秒数）。
【使用平台账号签名】
 */

typedef struct GetAdvertMessageRequest 
{
	HsviewRequest base;

	struct GetAdvertMessageRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} GetAdvertMessageRequest;

C_API GetAdvertMessageRequest *HSAPI_INIT(GetAdvertMessageRequest);

typedef struct GetAdvertMessageResponse 
{
	HsviewResponse base;

	struct GetAdvertMessageResponseData
	{
		
		/** struct of GetAdvertMessageResponseData_CsInfo */
		struct GetAdvertMessageResponseData_CsInfo {
			/** 页面底部未选中logourl */
			CSTR uncheckedLogo;
			/** 页面底部选中logourl */
			CSTR checkedLogo;
			/** 橙商名称 */
			CSTR name;
			/** 橙商logo的url */
			CSTR logo;
		} csInfo;
		/** define a list with struct of GetAdvertMessageResponseData_AdvertsElement */
		DECLARE_LIST(struct GetAdvertMessageResponseData_AdvertsElement
		{
			/** [long]广告id */
			int64 advertId;
			/** 广告图片Url地址 */
			CSTR advertPicUrl;
			/** 跳转网页Url地址 */
			CSTR logoUrl;
			/** 标题 */
			CSTR title;
			/** [long]logo活动的id */
			int64 logoId;
			/** [long]更新时间，UNIX时间 */
			int64 time;
			/** 广告网页Url地址 */
			CSTR advertUrl;
			/** logo图片Url地址 */
			CSTR logoPicUrl;
			/** [int]广告展示的倒计时时间，单位秒 */
			int countDown;
		}) adverts;
 
	} data;

} GetAdvertMessageResponse;

C_API GetAdvertMessageResponse *HSAPI_INIT(GetAdvertMessageResponse);

#endif
