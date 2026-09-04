/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 227286, Author: 251672, Date: 2024-09-02 17:23:07 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_ControlMovePTZ2_H_
#define _LC_OPENAPI_CLIENT_ControlMovePTZ2_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
云台移动控制接口2
备注：云台相关功能需要设备拥有PT或PTZ云台能力集
 */

typedef struct ControlMovePTZ2Request 
{
	LCOpenApiRequest base;

	struct ControlMovePTZ2RequestData
	{
		
		/** [double] 移动持续时间，单位毫秒 */
		double duration;
		/** [double] 垂直移动速度，范围-1~1，负数向下，正数向上 */
		double verticalSpeed;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** [double] 变倍倍速，范围-1~1，小于0表示缩小，大于0表示放大 */
		double zoom;
		/** [cstr]controlMovePTZ */
		#define _STATIC_ControlMovePTZ2RequestData_method "controlMovePTZ"
		CSTR method;
		/** 通道ID */
		CSTR channelId;
		/** [double] 水平移动速度，范围-1~1，负数向左，正数向右 */
		double horizontalSpeed;
		/** 设备ID */
		CSTR deviceId;

	} data;

} ControlMovePTZ2Request;

C_API ControlMovePTZ2Request *LCOPENAPI_INIT(ControlMovePTZ2Request);

typedef struct ControlMovePTZ2Response 
{
	LCOpenApiResponse base;

	struct ControlMovePTZ2ResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} ControlMovePTZ2Response;

C_API ControlMovePTZ2Response *LCOPENAPI_INIT(ControlMovePTZ2Response);

#endif
