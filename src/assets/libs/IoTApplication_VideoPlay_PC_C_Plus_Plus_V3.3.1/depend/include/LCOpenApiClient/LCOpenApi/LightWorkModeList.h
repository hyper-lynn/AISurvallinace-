/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_LightWorkModeList_H_
#define _LC_OPENAPI_CLIENT_LightWorkModeList_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取灯类设备所有工作模式和当前的工作模式
 */

typedef struct LightWorkModeListRequest 
{
	LCOpenApiRequest base;

	struct LightWorkModeListRequestData
	{
		
		/** 为空或floodlight表示查询探照灯的工作模式和当前的工作模式 */
		CSTR type;
		/** 通道。为空为设备级操作（需要设备支持通道探照灯能力 ChanSearchLight）；不为空则为通道级操作 */
		CSTR channelId;
		/** 授权的token(userToken或accessToken) */
		CSTR token;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} LightWorkModeListRequest;

C_API LightWorkModeListRequest *LCOPENAPI_INIT(LightWorkModeListRequest);

typedef struct LightWorkModeListResponse 
{
	LCOpenApiResponse base;

	struct LightWorkModeListResponseData
	{
		
		/** 模式对应的索引值，有效值大于等于0 */
		CSTR index;
		/** define a list with struct of LightWorkModeListResponseData_ValuesElement */
		DECLARE_LIST(struct LightWorkModeListResponseData_ValuesElement
		{
			/** 探照灯模式对应的索引值，有效值大于等于0，从0顺序递增 */
			CSTR index;
			/** 探照灯模式: manual：通用模式,motion activation：PIR联动模式,dusk to dawn：光敏联动模式 */
			CSTR mode;
		}) values;
 
	} data;

} LightWorkModeListResponse;

C_API LightWorkModeListResponse *LCOPENAPI_INIT(LightWorkModeListResponse);

#endif
