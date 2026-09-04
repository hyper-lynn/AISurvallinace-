/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_SetPreparation_H_
#define _LC_OPENAPI_CLIENT_SetPreparation_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
设置预案

 */

typedef struct SetPreparationRequest 
{
	LCOpenApiRequest base;

	struct SetPreparationRequestData
	{
		
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 预案，Normal：通用  FaceDetection：人脸智能  NumberStat：客流统计  HeatMap：热度分析 */
		CSTR selecting;
		/** 通道ID */
		CSTR channelId;
		/** [cstr]setPreparation */
		#define _STATIC_SetPreparationRequestData_method "setPreparation"
		CSTR method;
		/** 设备ID */
		CSTR deviceId;

	} data;

} SetPreparationRequest;

C_API SetPreparationRequest *LCOPENAPI_INIT(SetPreparationRequest);

typedef struct SetPreparationResponse 
{
	LCOpenApiResponse base;

	struct SetPreparationResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} SetPreparationResponse;

C_API SetPreparationResponse *LCOPENAPI_INIT(SetPreparationResponse);

#endif
