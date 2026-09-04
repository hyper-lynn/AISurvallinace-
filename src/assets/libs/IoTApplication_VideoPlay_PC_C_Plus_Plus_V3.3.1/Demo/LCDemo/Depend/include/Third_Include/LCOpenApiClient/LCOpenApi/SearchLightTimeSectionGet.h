/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_SearchLightTimeSectionGet_H_
#define _LC_OPENAPI_CLIENT_SearchLightTimeSectionGet_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
探照灯时间段计划获取,需要在ScheduleMode（时间段模式下）有效
 */

typedef struct SearchLightTimeSectionGetRequest 
{
	LCOpenApiRequest base;

	struct SearchLightTimeSectionGetRequestData
	{
		
		/** [int]通道号 */
		DECLARE_LIST(int) channels;
		/** 授权的token */
		CSTR token;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} SearchLightTimeSectionGetRequest;

C_API SearchLightTimeSectionGetRequest *LCOPENAPI_INIT(SearchLightTimeSectionGetRequest);

typedef struct SearchLightTimeSectionGetResponse 
{
	LCOpenApiResponse base;

	struct SearchLightTimeSectionGetResponseData
	{
		
		/** define a list with struct of SearchLightTimeSectionGetResponseData_ChannelsElement */
		DECLARE_LIST(struct SearchLightTimeSectionGetResponseData_ChannelsElement
		{
			/** define a list with struct of SearchLightTimeSectionGetResponseData_ChannelsElement_RulesElement */
			DECLARE_LIST(struct SearchLightTimeSectionGetResponseData_ChannelsElement_RulesElement
			{
				/** 生效的结束时间,时间格式为THHMMSS,如T010000 */
				CSTR endTime;
				/** 生效的起始时间,时间格式为THHMMSS,如T000000 */
				CSTR beginTime;
				/** 计划周期,如Monday */
				CSTR period;
			}) rules;
			/** [int]通道ID */
			int channelId;
		}) channels;
		/** 设备序列号 */
		CSTR deviceId;
 
	} data;

} SearchLightTimeSectionGetResponse;

C_API SearchLightTimeSectionGetResponse *LCOPENAPI_INIT(SearchLightTimeSectionGetResponse);

#endif
