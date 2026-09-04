/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_squareVideo_GetSquareBanner_H_
#define _HSVIEW_CLIENT_API_squareVideo_GetSquareBanner_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
查询视频广场Banner消息。
deviceId是直播源为摄像头时默认直播封面地址的解码秘钥
【使用平台账号签名】
 */

typedef struct squareVideo_GetSquareBannerRequest 
{
	HsviewRequest base;

	struct squareVideo_GetSquareBannerRequestData
	{
		
		/** [int]需要查的条数 */
		int count;
		/** 设备访问权限码 */
		CSTR accessKey;

	} data;

} squareVideo_GetSquareBannerRequest;

C_API squareVideo_GetSquareBannerRequest *HSAPI_INIT(squareVideo_GetSquareBannerRequest);

typedef struct squareVideo_GetSquareBannerResponse 
{
	HsviewResponse base;

	struct squareVideo_GetSquareBannerResponseData
	{
		
		/** define a list with struct of squareVideo_GetSquareBannerResponseData_BannersElement */
		DECLARE_LIST(struct squareVideo_GetSquareBannerResponseData_BannersElement
		{
			/** [int]banner类型,1表示实时视频分享,2表示网页H5消息 */
			int type;
			/** [long]banner的ID */
			int64 bannerId;
			/** 消息对应的封面图url */
			CSTR coverPicUrl;
			/** 标题 */
			CSTR title;
			/** [O]设备ID */
			CSTR deviceId;
		}) banners;
 
	} data;

} squareVideo_GetSquareBannerResponse;

C_API squareVideo_GetSquareBannerResponse *HSAPI_INIT(squareVideo_GetSquareBannerResponse);

#endif
