/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_PanoLocationToPtz_H_
#define _HSVIEW_CLIENT_API_PanoLocationToPtz_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
根据全景图位置控制PTZ，定位到某个方位。
【使用平台账号签名】
 */

typedef struct PanoLocationToPtzRequest 
{
	HsviewRequest base;

	struct PanoLocationToPtzRequestData
	{
		
		/** [int]全景图Y坐标，单位为像素，Y轴从上往下 */
		int panoY;
		/** [int]全景图X坐标，单位为像素，X轴从左往右 */
		int panoX;
		/** 设备ID */
		CSTR deviceId;

	} data;

} PanoLocationToPtzRequest;

C_API PanoLocationToPtzRequest *HSAPI_INIT(PanoLocationToPtzRequest);

typedef struct PanoLocationToPtzResponse 
{
	HsviewResponse base;

	struct PanoLocationToPtzResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} PanoLocationToPtzResponse;

C_API PanoLocationToPtzResponse *HSAPI_INIT(PanoLocationToPtzResponse);

#endif
