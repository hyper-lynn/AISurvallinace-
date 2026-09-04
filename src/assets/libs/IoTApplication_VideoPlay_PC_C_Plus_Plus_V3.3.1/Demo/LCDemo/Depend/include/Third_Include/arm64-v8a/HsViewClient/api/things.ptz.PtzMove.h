/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_thingsPtz_PtzMove_H_
#define _HSVIEW_CLIENT_API_thingsPtz_PtzMove_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
云台相对移动
当horizontal,vertical,zoom 三个参数分别为0,0,0 表示停止

【需要使用平台账号签名】
 */

typedef struct thingsPtz_PtzMoveRequest 
{
	HsviewRequest base;

	struct thingsPtz_PtzMoveRequestData
	{
		
		/** [double]垂直移动速度，范围-1~1，负数向下，正数向上 */
		double vertical;
		/** [long]持续移动的时间，单位为毫秒 */
		int64 duration;
		/** [double]变倍倍数：范围-1~1，小于0表示缩小，大于0表示放大 */
		double zoom;
		/** [double] 水平移动速度，范围-1~1，负数向左，正数向右 */
		double horizontal;
		/** 通道号 */
		CSTR channelId;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} thingsPtz_PtzMoveRequest;

C_API thingsPtz_PtzMoveRequest *HSAPI_INIT(thingsPtz_PtzMoveRequest);

typedef struct thingsPtz_PtzMoveResponse 
{
	HsviewResponse base;

	struct thingsPtz_PtzMoveResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} thingsPtz_PtzMoveResponse;

C_API thingsPtz_PtzMoveResponse *HSAPI_INIT(thingsPtz_PtzMoveResponse);

#endif
