/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_sightRecommend_GetResourceByPlat_H_
#define _HSVIEW_CLIENT_API_sightRecommend_GetResourceByPlat_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取发现模块“更多”h5页面展示
【不需要鉴权】
 */

typedef struct sightRecommend_GetResourceByPlatRequest 
{
	HsviewRequest base;

	struct sightRecommend_GetResourceByPlatRequestData
	{
		
		/** [long]（当前查询的页次序-1）*count。若要从最新开始查，填0 */
		int64 start;
		/** [int]需要查的最大条数 */
		int count;
		/** [long]模块id */
		int64 platId;

	} data;

} sightRecommend_GetResourceByPlatRequest;

C_API sightRecommend_GetResourceByPlatRequest *HSAPI_INIT(sightRecommend_GetResourceByPlatRequest);

typedef struct sightRecommend_GetResourceByPlatResponse 
{
	HsviewResponse base;

	struct sightRecommend_GetResourceByPlatResponseData
	{
		
		/** 模块名称 */
		CSTR name;
		/** define a list with struct of sightRecommend_GetResourceByPlatResponseData_ResourcesElement */
		DECLARE_LIST(struct sightRecommend_GetResourceByPlatResponseData_ResourcesElement
		{
			/** [int]点赞状态，1点赞，0未点赞 */
			int prizeStatus;
			/** 资源简介 */
			CSTR resourceIntro;
			/** [long]浏览数 */
			int64 browseCount;
			/** 视频url */
			CSTR audioUrl;
			/** 资源id */
			CSTR resourceId;
			/** 资源类型，graphic:图文类型 */
			CSTR resourceType;
			/** 资源封面图地址；oms2.5.8版本后该字段表示横图图片地址 */
			CSTR imgUrl;
			/**  资源链接url */
			CSTR contentUrl;
			/** 音频url */
			CSTR videoUrl;
			/**  资源标题 */
			CSTR title;
			/** [long]点赞数 */
			int64 prizeCount;
			/** 封面图片地址；表示竖图图片地址 */
			CSTR riserImgUrl;
		}) resources;
 
	} data;

} sightRecommend_GetResourceByPlatResponse;

C_API sightRecommend_GetResourceByPlatResponse *HSAPI_INIT(sightRecommend_GetResourceByPlatResponse);

#endif
