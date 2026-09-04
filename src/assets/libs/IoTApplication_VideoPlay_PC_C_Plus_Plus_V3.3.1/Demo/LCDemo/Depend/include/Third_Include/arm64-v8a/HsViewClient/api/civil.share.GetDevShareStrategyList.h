/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetDevShareStrategyList_H_
#define _HSVIEW_CLIENT_API_GetDevShareStrategyList_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取设备购买的分享授权套餐列表
【使用平台账号签名】
 */

typedef struct GetDevShareStrategyListRequest 
{
	HsviewRequest base;

	struct GetDevShareStrategyListRequestData
	{
		
		/** 通道号 */
		CSTR channelId;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} GetDevShareStrategyListRequest;

C_API GetDevShareStrategyListRequest *HSAPI_INIT(GetDevShareStrategyListRequest);

typedef struct GetDevShareStrategyListResponse 
{
	HsviewResponse base;

	struct GetDevShareStrategyListResponseData
	{
		
		/** define a list with struct of GetDevShareStrategyListResponseData_StrategiesElement */
		DECLARE_LIST(struct GetDevShareStrategyListResponseData_StrategiesElement
		{
			/** 套餐描述 */
			CSTR description;
			/** [long]结束时间，unix时间戳 */
			int64 endTime;
			/** 背景图片url */
			CSTR backgroudPicUrl;
			/** 套餐名称 */
			CSTR name;
			/** [int]购买的授权分享人数 */
			int shareNum;
			/** 套餐状态，-1：未使用；1：正在使用；0：过期 */
			CSTR status;
			/** [long]开始时间,unix时间戳 */
			int64 beginTime;
			/** [long]套餐列表id */
			int64 strategyListId;
			/** [int]默认的授权分享人数 */
			int defaultNum;
		}) strategies;
 
	} data;

} GetDevShareStrategyListResponse;

C_API GetDevShareStrategyListResponse *HSAPI_INIT(GetDevShareStrategyListResponse);

#endif
