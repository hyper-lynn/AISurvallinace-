/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_sightRecommend_UpdateBrowseCount_H_
#define _HSVIEW_CLIENT_API_sightRecommend_UpdateBrowseCount_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
更新浏览量
【不需要鉴权】
 */

typedef struct sightRecommend_UpdateBrowseCountRequest 
{
	HsviewRequest base;

	struct sightRecommend_UpdateBrowseCountRequestData
	{
		
		/** [long]资源id */
		int64 resourceId;

	} data;

} sightRecommend_UpdateBrowseCountRequest;

C_API sightRecommend_UpdateBrowseCountRequest *HSAPI_INIT(sightRecommend_UpdateBrowseCountRequest);

typedef struct sightRecommend_UpdateBrowseCountResponse 
{
	HsviewResponse base;

	struct sightRecommend_UpdateBrowseCountResponseData
	{
		
		/** [long]当前浏览数 */
		int64 browseCount;
 
	} data;

} sightRecommend_UpdateBrowseCountResponse;

C_API sightRecommend_UpdateBrowseCountResponse *HSAPI_INIT(sightRecommend_UpdateBrowseCountResponse);

#endif
