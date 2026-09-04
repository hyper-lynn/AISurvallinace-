/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_sightRecommend_GetBannerList_H_
#define _HSVIEW_CLIENT_API_sightRecommend_GetBannerList_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取发现模块banner列表
【默认鉴权】
 */

typedef struct sightRecommend_GetBannerListRequest 
{
	HsviewRequest base;

	struct sightRecommend_GetBannerListRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} sightRecommend_GetBannerListRequest;

C_API sightRecommend_GetBannerListRequest *HSAPI_INIT(sightRecommend_GetBannerListRequest);

typedef struct sightRecommend_GetBannerListResponse 
{
	HsviewResponse base;

	struct sightRecommend_GetBannerListResponseData
	{
		
		/** define a list with struct of sightRecommend_GetBannerListResponseData_BannersElement */
		DECLARE_LIST(struct sightRecommend_GetBannerListResponseData_BannersElement
		{
			/** [long]bannerid */
			int64 bannerId;
			/**  banner封面图地址 */
			CSTR imgUrl;
			/**  banner标题 */
			CSTR title;
			/**  banner链接url */
			CSTR contentUrl;
		}) banners;
 
	} data;

} sightRecommend_GetBannerListResponse;

C_API sightRecommend_GetBannerListResponse *HSAPI_INIT(sightRecommend_GetBannerListResponse);

#endif
