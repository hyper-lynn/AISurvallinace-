/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 227286, Author: 251672, Date: 2024-09-02 17:23:07 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_SetPTZIris_H_
#define _LC_OPENAPI_CLIENT_SetPTZIris_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
设备光圈大小

 */

typedef struct SetPTZIrisRequest 
{
	LCOpenApiRequest base;

	struct SetPTZIrisRequestData
	{
		
		/** struct of SetPTZIrisRequestData_RealData */
		struct SetPTZIrisRequestData_RealData {
			/** [int]通道号 */
			int chan;
			/** [double]归一化到-1~1 */
			double change;
		} realData;
		/** [cstr]/device/ptz/iris/config */
		#define _STATIC_SetPTZIrisRequestData_method "/device/ptz/iris/config"
		CSTR method;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备ID */
		CSTR deviceId;

	} data;

} SetPTZIrisRequest;

C_API SetPTZIrisRequest *LCOPENAPI_INIT(SetPTZIrisRequest);

typedef struct SetPTZIrisResponse 
{
	LCOpenApiResponse base;

	struct SetPTZIrisResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} SetPTZIrisResponse;

C_API SetPTZIrisResponse *LCOPENAPI_INIT(SetPTZIrisResponse);

#endif
