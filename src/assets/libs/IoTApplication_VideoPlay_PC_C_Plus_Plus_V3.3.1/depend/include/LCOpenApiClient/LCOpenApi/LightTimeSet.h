/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_LightTimeSet_H_
#define _LC_OPENAPI_CLIENT_LightTimeSet_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
设置探照灯亮灯时长
 */

typedef struct LightTimeSetRequest 
{
	LCOpenApiRequest base;

	struct LightTimeSetRequestData
	{
		
		/** 探照灯时长对应的索引值，有效值大于等于0 */
		CSTR index;
		/** 为空或floodlight表示查询探照灯的工作模式和当前的工作模式 */
		CSTR type;
		/** 授权的token(userToken或accessToken) */
		CSTR token;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} LightTimeSetRequest;

C_API LightTimeSetRequest *LCOPENAPI_INIT(LightTimeSetRequest);

typedef struct LightTimeSetResponse 
{
	LCOpenApiResponse base;

	struct LightTimeSetResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} LightTimeSetResponse;

C_API LightTimeSetResponse *LCOPENAPI_INIT(LightTimeSetResponse);

#endif
