/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_devicePano_PanoLocationToPtz_H_
#define _HSVIEW_CLIENT_API_devicePano_PanoLocationToPtz_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
根据全景图位置控制PTZ，定位到某个方位。

【使用平台账号签名】
 */

typedef struct devicePano_PanoLocationToPtzRequest 
{
	HsviewRequest base;

	struct devicePano_PanoLocationToPtzRequestData
	{
		
		/** [int]全景图Y坐标，单位为像素，Y轴从上往下 */
		int panoY;
		/** [int]全景图X坐标，单位为像素，X轴从左往右 */
		int panoX;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} devicePano_PanoLocationToPtzRequest;

C_API devicePano_PanoLocationToPtzRequest *HSAPI_INIT(devicePano_PanoLocationToPtzRequest);

typedef struct devicePano_PanoLocationToPtzResponse 
{
	HsviewResponse base;

	struct devicePano_PanoLocationToPtzResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} devicePano_PanoLocationToPtzResponse;

C_API devicePano_PanoLocationToPtzResponse *HSAPI_INIT(devicePano_PanoLocationToPtzResponse);

#endif
