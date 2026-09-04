/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_thingsPtz_GetPtzLocation_H_
#define _HSVIEW_CLIENT_API_thingsPtz_GetPtzLocation_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取云台位置

【需要使用平台账号签名】
 */

typedef struct thingsPtz_GetPtzLocationRequest 
{
	HsviewRequest base;

	struct thingsPtz_GetPtzLocationRequestData
	{
		
		/** 通道号 */
		CSTR channelId;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} thingsPtz_GetPtzLocationRequest;

C_API thingsPtz_GetPtzLocationRequest *HSAPI_INIT(thingsPtz_GetPtzLocationRequest);

typedef struct thingsPtz_GetPtzLocationResponse 
{
	HsviewResponse base;

	struct thingsPtz_GetPtzLocationResponseData
	{
		
		/** [double]变倍倍数：归一化到0~1，其中0表示缩到最小，1表示放到最大 */
		double zoom;
		/** [double][O], 水平视场角近似值 */
		double fov;
		/** [double]水平位置：归一化到-1~1, 表示水平经度-180°到180° */
		double horizontal;
		/** [double][O], 焦距，以mm毫米为单位 */
		double focal;
		/** [double]垂直位置：归一化到-1~1, 表示垂直维度-90°到90° */
		double vertical;
 
	} data;

} thingsPtz_GetPtzLocationResponse;

C_API thingsPtz_GetPtzLocationResponse *HSAPI_INIT(thingsPtz_GetPtzLocationResponse);

#endif
