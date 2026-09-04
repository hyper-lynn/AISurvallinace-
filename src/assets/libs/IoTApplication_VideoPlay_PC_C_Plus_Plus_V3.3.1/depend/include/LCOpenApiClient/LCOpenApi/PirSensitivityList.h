/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_PirSensitivityList_H_
#define _LC_OPENAPI_CLIENT_PirSensitivityList_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取PIR灵敏度
 */

typedef struct PirSensitivityListRequest 
{
	LCOpenApiRequest base;

	struct PirSensitivityListRequestData
	{
		
		/** xxx */
		CSTR token;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} PirSensitivityListRequest;

C_API PirSensitivityListRequest *LCOPENAPI_INIT(PirSensitivityListRequest);

typedef struct PirSensitivityListResponse 
{
	LCOpenApiResponse base;

	struct PirSensitivityListResponseData
	{
		
		/** define a list with struct of PirSensitivityListResponseData_ShapedEnableElement */
		DECLARE_LIST(struct PirSensitivityListResponseData_ShapedEnableElement
		{
			/** [int]小扇形的索引值，从0开始 */
			int index;
			/** on-开启 off-关闭 */
			CSTR enable;
		}) shapedEnable;
		/** [int]取值范围[0,100]，检测半径的百分比 */
		int sensitivity;
 
	} data;

} PirSensitivityListResponse;

C_API PirSensitivityListResponse *LCOPENAPI_INIT(PirSensitivityListResponse);

#endif
