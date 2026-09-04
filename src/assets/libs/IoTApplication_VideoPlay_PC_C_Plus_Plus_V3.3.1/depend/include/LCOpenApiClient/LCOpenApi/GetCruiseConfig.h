/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_GetCruiseConfig_H_
#define _LC_OPENAPI_CLIENT_GetCruiseConfig_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取设备的定时巡航配置，只支持具有TimedCruise能力的单通道IPC设备

 */

typedef struct GetCruiseConfigRequest 
{
	LCOpenApiRequest base;

	struct GetCruiseConfigRequestData
	{
		
		/** [cstr]getCruiseConfig */
		#define _STATIC_GetCruiseConfigRequestData_method "getCruiseConfig"
		CSTR method;
		/** 通道ID */
		CSTR channelId;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备ID */
		CSTR deviceId;

	} data;

} GetCruiseConfigRequest;

C_API GetCruiseConfigRequest *LCOPENAPI_INIT(GetCruiseConfigRequest);

typedef struct GetCruiseConfigResponse 
{
	LCOpenApiResponse base;

	struct GetCruiseConfigResponseData
	{
		
		/** 通道ID */
		CSTR channelId;
		/** struct of GetCruiseConfigResponseData_CruisePlan */
		struct GetCruiseConfigResponseData_CruisePlan {
			/** [可选][String]巡航路径，当mode=collection时必填，可选值如下：default：默认路径，由设备端决定;custom：自定义路径，即collection中收藏点的顺序 */
			CSTR cruisePath;
			/** define a list with struct of GetCruiseConfigResponseData_CruisePlan_CollectionElement */
			DECLARE_LIST(struct GetCruiseConfigResponseData_CruisePlan_CollectionElement
			{
				/** [String]收藏点名称，收藏点的唯一标示符，当mode为collection，cruisePath为custom时必填 */
				CSTR name;
				/** [int]收藏点参数，每个收藏点的停留时间，单位为秒，当mode为collection，cruisePath为custom时必填 */
				int stayTime;
			}) collection;
			/** [必选][String] default：默认模式，即全景巡航; collection：定制模式，即收藏点巡航 */
			CSTR mode;
			/** define a list with struct of GetCruiseConfigResponseData_CruisePlan_CruisesElement */
			DECLARE_LIST(struct GetCruiseConfigResponseData_CruisePlan_CruisesElement
			{
				/** [String]结束时间。时间格式为：THHMMSS */
				CSTR endTime;
				/** [String]开始时间。时间格式为：THHMMSS */
				CSTR beginTime;
				/** [String]巡航周期:Monday每周一;Tuesday每周二;Wednesday每周三;Thursday每周四;Friday每周五;Saturday每周六;Sunday每周日 */
				CSTR period;
			}) cruises;
			/** 巡航计划唯一标示符，可选 */
			CSTR cruiseName;
		} cruisePlan;
		/** 设备ID */
		CSTR deviceId;
 
	} data;

} GetCruiseConfigResponse;

C_API GetCruiseConfigResponse *LCOPENAPI_INIT(GetCruiseConfigResponse);

#endif
