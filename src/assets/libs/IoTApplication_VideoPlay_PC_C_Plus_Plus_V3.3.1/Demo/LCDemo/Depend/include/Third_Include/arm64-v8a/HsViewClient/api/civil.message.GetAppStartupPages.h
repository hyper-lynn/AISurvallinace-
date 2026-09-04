/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetAppStartupPages_H_
#define _HSVIEW_CLIENT_API_GetAppStartupPages_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取启动页数组。
advertUrls：默认的定向广告信息列表
logoUrls：logo广告信息列表
【无需账号签名】
 */

typedef struct GetAppStartupPagesRequest 
{
	HsviewRequest base;

	struct GetAppStartupPagesRequestData
	{
		
		/** app类型。andriodPhone 安卓手机；andriodBox 安卓盒子；iosPhone ios手机；pcClient 表示pc Web */
		CSTR appType;

	} data;

} GetAppStartupPagesRequest;

C_API GetAppStartupPagesRequest *HSAPI_INIT(GetAppStartupPagesRequest);

typedef struct GetAppStartupPagesResponse 
{
	HsviewResponse base;

	struct GetAppStartupPagesResponseData
	{
		
		/** 表示启动页版本 */
		CSTR version;
		/** 数组，每个元素为启动页的URL */
		DECLARE_LIST(CSTR) startupPagesUrls;
		/** define a list with struct of GetAppStartupPagesResponseData_AdvertsElement */
		DECLARE_LIST(struct GetAppStartupPagesResponseData_AdvertsElement
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

} GetAppStartupPagesResponse;

C_API GetAppStartupPagesResponse *HSAPI_INIT(GetAppStartupPagesResponse);

#endif
