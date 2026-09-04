/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_chargeInfo_GetStorageStrategyAdvert_H_
#define _HSVIEW_CLIENT_API_chargeInfo_GetStorageStrategyAdvert_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取客户端购买云存储页面中介绍的图片，用于OMS后台动态控制，可以控制图片的张数以及图片里面的内容。
h5Url为空时表示固定云存储购买链接，不为空时表示第三方链接

暂用于国内云存储购买。
请求结果与oms平台排序结果一致
【使用平台账号签名】
 */

typedef struct chargeInfo_GetStorageStrategyAdvertRequest 
{
	HsviewRequest base;

	struct chargeInfo_GetStorageStrategyAdvertRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} chargeInfo_GetStorageStrategyAdvertRequest;

C_API chargeInfo_GetStorageStrategyAdvertRequest *HSAPI_INIT(chargeInfo_GetStorageStrategyAdvertRequest);

typedef struct chargeInfo_GetStorageStrategyAdvertResponse 
{
	HsviewResponse base;

	struct chargeInfo_GetStorageStrategyAdvertResponseData
	{
		
		/** define a list with struct of chargeInfo_GetStorageStrategyAdvertResponseData_AdvertElement */
		DECLARE_LIST(struct chargeInfo_GetStorageStrategyAdvertResponseData_AdvertElement
		{
			/** 云存储介绍类型，pic表示图片类型， video表示视频类型 */
			CSTR advertType;
			/** [O][int]是否有链接，图片类型时为必选；0表示无，1表示有 */
			CSTR isHaveUrl;
			/** 图片地址 */
			CSTR picUrl;
			/** [O]h5地址 */
			CSTR h5Url;
		}) advert;
 
	} data;

} chargeInfo_GetStorageStrategyAdvertResponse;

C_API chargeInfo_GetStorageStrategyAdvertResponse *HSAPI_INIT(chargeInfo_GetStorageStrategyAdvertResponse);

#endif
