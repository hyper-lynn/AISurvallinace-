/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_sightRecommend_UpdatePrizeCount_H_
#define _HSVIEW_CLIENT_API_sightRecommend_UpdatePrizeCount_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
更新点赞数
【使用平台账号签名】
 */

typedef struct sightRecommend_UpdatePrizeCountRequest 
{
	HsviewRequest base;

	struct sightRecommend_UpdatePrizeCountRequestData
	{
		
		/** [long]资源id */
		int64 resourceId;

	} data;

} sightRecommend_UpdatePrizeCountRequest;

C_API sightRecommend_UpdatePrizeCountRequest *HSAPI_INIT(sightRecommend_UpdatePrizeCountRequest);

typedef struct sightRecommend_UpdatePrizeCountResponse 
{
	HsviewResponse base;

	struct sightRecommend_UpdatePrizeCountResponseData
	{
		
		/** [long]当前点赞数 */
		int64 prizeCount;
 
	} data;

} sightRecommend_UpdatePrizeCountResponse;

C_API sightRecommend_UpdatePrizeCountResponse *HSAPI_INIT(sightRecommend_UpdatePrizeCountResponse);

#endif
