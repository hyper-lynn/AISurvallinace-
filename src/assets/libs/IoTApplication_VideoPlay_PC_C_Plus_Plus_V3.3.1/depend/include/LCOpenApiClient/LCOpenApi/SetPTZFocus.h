/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 227286, Author: 251672, Date: 2024-09-02 17:23:07 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_SetPTZFocus_H_
#define _LC_OPENAPI_CLIENT_SetPTZFocus_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
设备对焦控制

 */

typedef struct SetPTZFocusRequest 
{
	LCOpenApiRequest base;

	struct SetPTZFocusRequestData
	{
		
		/** struct of SetPTZFocusRequestData_RealData */
		struct SetPTZFocusRequestData_RealData {
			/** [int]通道号 */
			int chan;
			/** [double]归一化到-1~1 */
			double change;
		} realData;
		/** [cstr]/device/ptz/focus/config */
		#define _STATIC_SetPTZFocusRequestData_method "/device/ptz/focus/config"
		CSTR method;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备ID */
		CSTR deviceId;

	} data;

} SetPTZFocusRequest;

C_API SetPTZFocusRequest *LCOPENAPI_INIT(SetPTZFocusRequest);

typedef struct SetPTZFocusResponse 
{
	LCOpenApiResponse base;

	struct SetPTZFocusResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} SetPTZFocusResponse;

C_API SetPTZFocusResponse *LCOPENAPI_INIT(SetPTZFocusResponse);

#endif
