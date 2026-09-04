/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_PirSensitivitySet_H_
#define _LC_OPENAPI_CLIENT_PirSensitivitySet_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
设置PIR灵敏度
 */

typedef struct PirSensitivitySetRequest 
{
	LCOpenApiRequest base;

	struct PirSensitivitySetRequestData
	{
		
		/** define a list with struct of PirSensitivitySetRequestData_ShapedEnableElement */
		DECLARE_LIST(struct PirSensitivitySetRequestData_ShapedEnableElement
		{
			/** [int]小扇形的索引值 */
			int index;
			/** on-开启 off-关闭 */
			CSTR enable;
		}) shapedEnable;
		/** [int]取值范围[0,100]，检测半径的百分比 */
		int sensitivity;
		/** 授权token */
		CSTR token;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} PirSensitivitySetRequest;

C_API PirSensitivitySetRequest *LCOPENAPI_INIT(PirSensitivitySetRequest);

typedef struct PirSensitivitySetResponse 
{
	LCOpenApiResponse base;

	struct PirSensitivitySetResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} PirSensitivitySetResponse;

C_API PirSensitivitySetResponse *LCOPENAPI_INIT(PirSensitivitySetResponse);

#endif
