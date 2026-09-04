/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 227363, Author: 426167, Date: 2024-09-14 11:05:19 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_ControlMovePTZyunlian_H_
#define _LC_OPENAPI_CLIENT_ControlMovePTZyunlian_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
云台移动控制接口

 */

typedef struct ControlMovePTZyunlianRequest 
{
	LCOpenApiRequest base;

	struct ControlMovePTZyunlianRequestData
	{
		
		/** [cstr]controlMovePTZ */
		#define _STATIC_ControlMovePTZyunlianRequestData_method "controlMovePTZ"
		CSTR method;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 操作行为；0-上，1-下，2-左，3-右，4-左上，5-左下，6-右上，7-右下，8-放大，9-缩小，10-停止 */
		CSTR operation;
		/** 通道号 */
		CSTR channelId;
		/** [long]移动持续时间，单位为毫秒 */
		int64 duration;
		/** 设备ID */
		CSTR deviceId;

	} data;

} ControlMovePTZyunlianRequest;

C_API ControlMovePTZyunlianRequest *LCOPENAPI_INIT(ControlMovePTZyunlianRequest);

typedef struct ControlMovePTZyunlianResponse 
{
	LCOpenApiResponse base;

	struct ControlMovePTZyunlianResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} ControlMovePTZyunlianResponse;

C_API ControlMovePTZyunlianResponse *LCOPENAPI_INIT(ControlMovePTZyunlianResponse);

#endif
