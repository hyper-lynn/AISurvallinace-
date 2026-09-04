/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_SetCruiseConfig_H_
#define _LC_OPENAPI_CLIENT_SetCruiseConfig_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
设置设备的定时巡航配置，只支持具有TimedCruise能力的单通道IPC设备

 */

typedef struct SetCruiseConfigRequest 
{
	LCOpenApiRequest base;

	struct SetCruiseConfigRequestData
	{
		
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** struct of SetCruiseConfigRequestData_CruisePlan */
		struct SetCruiseConfigRequestData_CruisePlan {
			/** [可选][String]巡航路径，当mode=collection时必填，可选值如下：default：默认路径，由设备端决定;custom：自定义路径，即collection中收藏点的顺序 */
			CSTR cruisePath;
			/** define a list with struct of SetCruiseConfigRequestData_CruisePlan_CollectionElement */
			DECLARE_LIST(struct SetCruiseConfigRequestData_CruisePlan_CollectionElement
			{
				/** [可选][String]收藏点名称，收藏点的唯一标示符，当mode为collection，cruisePath为custom时必填 */
				CSTR name;
				/** [可选][int]收藏点参数，每个收藏点的停留时间，单位为秒，当mode为collection，cruisePath为custom时必填 */
				CSTR stayTime;
			}) collection;
			/** [必选][String] default：默认模式，即全景巡航; collection：定制模式，即收藏点巡航 */
			CSTR mode;
			/** define a list with struct of SetCruiseConfigRequestData_CruisePlan_CruisesElement */
			DECLARE_LIST(struct SetCruiseConfigRequestData_CruisePlan_CruisesElement
			{
				/** [必选][String]结束时间。时间格式为：THHMMSS */
				CSTR endTime;
				/** [必选][String]开始时间。时间格式为：THHMMSS */
				CSTR beginTime;
				/** [必选][String]巡航周期:Monday每周一;Tuesday每周二;Wednesday每周三;Thursday每周四;Friday每周五;Saturday每周六;Sunday每周日 */
				CSTR period;
			}) cruises;
			/** 巡航计划唯一标示符，可选 */
			CSTR cruiseName;
		} cruisePlan;
		/** 通道ID */
		CSTR channelId;
		/** [cstr]setCruiseConfig */
		#define _STATIC_SetCruiseConfigRequestData_method "setCruiseConfig"
		CSTR method;
		/** 设备ID */
		CSTR deviceId;

	} data;

} SetCruiseConfigRequest;

C_API SetCruiseConfigRequest *LCOPENAPI_INIT(SetCruiseConfigRequest);

typedef struct SetCruiseConfigResponse 
{
	LCOpenApiResponse base;

	struct SetCruiseConfigResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} SetCruiseConfigResponse;

C_API SetCruiseConfigResponse *LCOPENAPI_INIT(SetCruiseConfigResponse);

#endif
