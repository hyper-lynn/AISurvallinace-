/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 227286, Author: 251672, Date: 2024-09-02 17:23:07 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_GetDeviceAlarmParam_H_
#define _LC_OPENAPI_CLIENT_GetDeviceAlarmParam_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取设备动检参数
 */

typedef struct GetDeviceAlarmParamRequest 
{
	LCOpenApiRequest base;

	struct GetDeviceAlarmParamRequestData
	{
		
		/** 设备来源，lc：乐橙设备，paas：大华设备 */
		CSTR sourceType;
		/** 通道,不存在默认为设备 */
		CSTR channelId;
		/** 授权的token(userToken或accessToken) */
		CSTR token;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} GetDeviceAlarmParamRequest;

C_API GetDeviceAlarmParamRequest *LCOPENAPI_INIT(GetDeviceAlarmParamRequest);

typedef struct GetDeviceAlarmParamResponse 
{
	LCOpenApiResponse base;

	struct GetDeviceAlarmParamResponseData
	{
		
		/** [int][O]表示档位，0表示设备不支持，未返回该字段 */
		int stall;
		/** 4194303, 3216384 */
		CSTR region;
		/** [int]动态检测区域的列数（只读，设备能力） */
		int column;
		/** [int] */
		int threshold;
		/** [int]动态检测区域的行数（只读，设备能力） */
		int row;
		/** [int]灵敏度,目前支持5个档位 1灵敏度最低 5灵敏度最高 */
		int sensitive;
 
	} data;

} GetDeviceAlarmParamResponse;

C_API GetDeviceAlarmParamResponse *LCOPENAPI_INIT(GetDeviceAlarmParamResponse);

#endif
