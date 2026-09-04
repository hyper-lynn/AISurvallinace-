/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_sightRecommend_GetResourceById_H_
#define _HSVIEW_CLIENT_API_sightRecommend_GetResourceById_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取发现模块资源详情
【不需要鉴权】
 */

typedef struct sightRecommend_GetResourceByIdRequest 
{
	HsviewRequest base;

	struct sightRecommend_GetResourceByIdRequestData
	{
		
		/** [long]资源id */
		int64 resourceId;

	} data;

} sightRecommend_GetResourceByIdRequest;

C_API sightRecommend_GetResourceByIdRequest *HSAPI_INIT(sightRecommend_GetResourceByIdRequest);

typedef struct sightRecommend_GetResourceByIdResponse 
{
	HsviewResponse base;

	struct sightRecommend_GetResourceByIdResponseData
	{
		
		/** [int]点赞状态，1点赞，0未点赞 */
		int prizeStatus;
		/** 资源简介 */
		CSTR resourceIntro;
		/** define a list with struct of sightRecommend_GetResourceByIdResponseData_AttributeListElement */
		DECLARE_LIST(struct sightRecommend_GetResourceByIdResponseData_AttributeListElement
		{
			/** [O]商品id或标签id */
			CSTR attributeId;
			/** [O]属性类型：商品：GOODS，标签：LABEL */
			CSTR type;
		}) attributeList;
		/** [long]浏览数 */
		int64 browseCount;
		/** 视频url */
		CSTR audioUrl;
		/** 音频url */
		CSTR videoUrl;
		/** [O]文章内视频封面图列表，内容类型为自定义且内部有视频时携带 */
		DECLARE_LIST(CSTR) videoImgUrls;
		/** 资源类型，graphic:图文类型 */
		CSTR resourceType;
		/** 封面图片地址；oms2.5.8版本后该字段表示横图图片地址 */
		CSTR imgUrl;
		/**  资源链接url */
		CSTR contentUrl;
		/** [bool]是否显示大转盘跳转 */
		BOOL hasRotateTable;
		/**  资源标题 */
		CSTR title;
		/** [long]点赞数 */
		int64 prizeCount;
		/** 封面图片地址；表示竖图图片地址 */
		CSTR riserImgUrl;
 
	} data;

} sightRecommend_GetResourceByIdResponse;

C_API sightRecommend_GetResourceByIdResponse *HSAPI_INIT(sightRecommend_GetResourceByIdResponse);

#endif
