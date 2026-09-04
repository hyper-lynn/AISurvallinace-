/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_SearchLightTimeSectionSet_H_
#define _LC_OPENAPI_CLIENT_SearchLightTimeSectionSet_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
探照灯时间段设置,需要在ScheduleMode（时间段模式下）有效
 */

typedef struct SearchLightTimeSectionSetRequest 
{
	LCOpenApiRequest base;

	struct SearchLightTimeSectionSetRequestData
	{
		
		/** define a list with struct of SearchLightTimeSectionSetRequestData_ChannelsElement */
		DECLARE_LIST(struct SearchLightTimeSectionSetRequestData_ChannelsElement
		{
			/** define a list with struct of SearchLightTimeSectionSetRequestData_ChannelsElement_RulesElement */
			DECLARE_LIST(struct SearchLightTimeSectionSetRequestData_ChannelsElement_RulesElement
			{
				/** 生效的结束时间,时间格式为THHMMSS,如T010000 */
				CSTR endTime;
				/** 生效的起始时间,时间格式为THHMMSS,如T000000 */
				CSTR beginTime;
				/** 计划周期,如Monday */
				CSTR period;
			}) rules;
			/** [int]通道号 */
			int channelId;
		}) channels;
		/** 授权的token(userToken或accessToken) */
		CSTR token;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} SearchLightTimeSectionSetRequest;

C_API SearchLightTimeSectionSetRequest *LCOPENAPI_INIT(SearchLightTimeSectionSetRequest);

typedef struct SearchLightTimeSectionSetResponse 
{
	LCOpenApiResponse base;

	struct SearchLightTimeSectionSetResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} SearchLightTimeSectionSetResponse;

C_API SearchLightTimeSectionSetResponse *LCOPENAPI_INIT(SearchLightTimeSectionSetResponse);

#endif
