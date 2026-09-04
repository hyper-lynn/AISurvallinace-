/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_advertisementInfo_GetAdvertisement_H_
#define _HSVIEW_CLIENT_API_advertisementInfo_GetAdvertisement_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取平台广告
【需要使用平台账号签名】
 */

typedef struct advertisementInfo_GetAdvertisementRequest 
{
	HsviewRequest base;

	struct advertisementInfo_GetAdvertisementRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} advertisementInfo_GetAdvertisementRequest;

C_API advertisementInfo_GetAdvertisementRequest *HSAPI_INIT(advertisementInfo_GetAdvertisementRequest);

typedef struct advertisementInfo_GetAdvertisementResponse 
{
	HsviewResponse base;

	struct advertisementInfo_GetAdvertisementResponseData
	{
		
		/** define a list with struct of advertisementInfo_GetAdvertisementResponseData_BouncedElement */
		DECLARE_LIST(struct advertisementInfo_GetAdvertisementResponseData_BouncedElement
		{
			/** [long]弹框广告id */
			int64 bouncedAdvertId;
			/** 跳转链接地址 */
			CSTR url;
			/** 广告标题 */
			CSTR title;
			/** 图片链接地址 */
			CSTR picUrl;
		}) bounced;
		/** define a list with struct of advertisementInfo_GetAdvertisementResponseData_FreshElement */
		DECLARE_LIST(struct advertisementInfo_GetAdvertisementResponseData_FreshElement
		{
			/** 图片链接地址 */
			CSTR picUrl;
			/** 跳转链接地址 */
			CSTR url;
			/** 广告标题 */
			CSTR title;
			/** [long]新人优惠广告id */
			int64 freshAdvertId;
		}) fresh;
		/** define a list with struct of advertisementInfo_GetAdvertisementResponseData_MineElement */
		DECLARE_LIST(struct advertisementInfo_GetAdvertisementResponseData_MineElement
		{
			/** [long]我的页面广告 */
			int64 advertisementId;
			/** 跳转链接地址 */
			CSTR url;
			/** 广告标题 */
			CSTR title;
			/** 图片链接地址 */
			CSTR picUrl;
		}) mine;
		/** define a list with struct of advertisementInfo_GetAdvertisementResponseData_AdvertisementElement */
		DECLARE_LIST(struct advertisementInfo_GetAdvertisementResponseData_AdvertisementElement
		{
			/** [long]广告id */
			int64 advertisementId;
			/** 跳转链接地址 */
			CSTR url;
			/** 广告标题 */
			CSTR title;
			/** 图片链接地址 */
			CSTR picUrl;
		}) advertisement;
 
	} data;

} advertisementInfo_GetAdvertisementResponse;

C_API advertisementInfo_GetAdvertisementResponse *HSAPI_INIT(advertisementInfo_GetAdvertisementResponse);

#endif
