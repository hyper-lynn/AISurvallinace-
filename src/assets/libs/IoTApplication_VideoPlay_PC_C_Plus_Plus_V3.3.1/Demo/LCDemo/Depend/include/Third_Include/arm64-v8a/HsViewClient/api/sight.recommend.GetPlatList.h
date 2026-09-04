/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_sightRecommend_GetPlatList_H_
#define _HSVIEW_CLIENT_API_sightRecommend_GetPlatList_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取发现板块列表
【默认鉴权】
 */

typedef struct sightRecommend_GetPlatListRequest 
{
	HsviewRequest base;

	struct sightRecommend_GetPlatListRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} sightRecommend_GetPlatListRequest;

C_API sightRecommend_GetPlatListRequest *HSAPI_INIT(sightRecommend_GetPlatListRequest);

typedef struct sightRecommend_GetPlatListResponse 
{
	HsviewResponse base;

	struct sightRecommend_GetPlatListResponseData
	{
		
		/** define a list with struct of sightRecommend_GetPlatListResponseData_PlatsElement */
		DECLARE_LIST(struct sightRecommend_GetPlatListResponseData_PlatsElement
		{
			/** [long]模块id */
			int64 platId;
			/**  模块名称 */
			CSTR name;
			/** define a list with struct of sightRecommend_GetPlatListResponseData_PlatsElement_RecommendLimitElement */
			DECLARE_LIST(struct sightRecommend_GetPlatListResponseData_PlatsElement_RecommendLimitElement
			{
				/** 资源简介 */
				CSTR resourceIntro;
				/** 资源详情的h5地址 */
				CSTR h5Url;
				/** 资源id */
				CSTR resourceId;
				/** 资源类型，graphic:图文类型 */
				CSTR resourceType;
				/** 资源封面图地址；oms2.5.8版本后该字段表示横图图片地址 */
				CSTR imgUrl;
				/** [long]浏览数 */
				int64 browseCount;
				/**  资源标题 */
				CSTR title;
				/** [long]点赞数 */
				int64 prizeCount;
				/** 封面图片地址；表示竖图图片地址 */
				CSTR riserImgUrl;
			}) recommendLimit;
			/** [O]更多页面h5地址 */
			CSTR h5Url;
			/** [int]更多标识，0，无更多项；1，有更多项 */
			int moreFlag;
			/** 版块类型，graphic:图文类型；live:直播类型 */
			CSTR platType;
			/** 版块样式，图文：lImgRText:表示左图右文；lTextRImg:表式左文右图；aImgbText:表示上图下文；直播：gridView表示网格 */
			CSTR platStyle;
		}) plats;
 
	} data;

} sightRecommend_GetPlatListResponse;

C_API sightRecommend_GetPlatListResponse *HSAPI_INIT(sightRecommend_GetPlatListResponse);

#endif
