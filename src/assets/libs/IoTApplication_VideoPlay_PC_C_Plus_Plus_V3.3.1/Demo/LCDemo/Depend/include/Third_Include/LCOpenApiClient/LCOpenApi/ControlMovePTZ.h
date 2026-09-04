/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 227286, Author: 251672, Date: 2024-09-02 17:23:07 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_ControlMovePTZ_H_
#define _LC_OPENAPI_CLIENT_ControlMovePTZ_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
云台移动控制接口

 */

typedef struct ControlMovePTZRequest 
{
	LCOpenApiRequest base;

	struct ControlMovePTZRequestData
	{
		
		/** [cstr]controlMovePTZ */
		#define _STATIC_ControlMovePTZRequestData_method "controlMovePTZ"
		CSTR method;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 操作行为；0-上，1-下，2-左，3-右，4-左上，5-左下，6-右上，7-右下，8-放大，9-缩小，10-停止 */
		CSTR operation;
		/** 通道号 */
		CSTR channelId;
		/** 移动持续时间，单位为毫秒 */
		CSTR duration;
		/** 设备ID */
		CSTR deviceId;

	} data;

} ControlMovePTZRequest;

C_API ControlMovePTZRequest *LCOPENAPI_INIT(ControlMovePTZRequest);

typedef struct ControlMovePTZResponse 
{
	LCOpenApiResponse base;

	struct ControlMovePTZResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} ControlMovePTZResponse;

C_API ControlMovePTZResponse *LCOPENAPI_INIT(ControlMovePTZResponse);

#endif
