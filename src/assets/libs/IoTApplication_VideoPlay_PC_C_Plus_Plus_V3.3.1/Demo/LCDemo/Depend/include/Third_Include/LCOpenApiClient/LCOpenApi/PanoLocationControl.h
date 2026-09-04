/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_PanoLocationControl_H_
#define _LC_OPENAPI_CLIENT_PanoLocationControl_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
根据全景图位置控制PTZ，定位到某个方位
 */

typedef struct PanoLocationControlRequest 
{
	LCOpenApiRequest base;

	struct PanoLocationControlRequestData
	{
		
		/** 全景图Y坐标，单位为像素，Y轴从上往下 */
		CSTR y;
		/** 全景图X坐标，单位为像素，X轴从左往右 */
		CSTR x;
		/** xxx */
		CSTR token;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} PanoLocationControlRequest;

C_API PanoLocationControlRequest *LCOPENAPI_INIT(PanoLocationControlRequest);

typedef struct PanoLocationControlResponse 
{
	LCOpenApiResponse base;

	struct PanoLocationControlResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} PanoLocationControlResponse;

C_API PanoLocationControlResponse *LCOPENAPI_INIT(PanoLocationControlResponse);

#endif
