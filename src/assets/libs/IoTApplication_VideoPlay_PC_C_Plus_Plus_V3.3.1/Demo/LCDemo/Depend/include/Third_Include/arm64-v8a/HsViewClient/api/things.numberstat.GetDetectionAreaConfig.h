/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_thingsNumberstat_GetDetectionAreaConfig_H_
#define _HSVIEW_CLIENT_API_thingsNumberstat_GetDetectionAreaConfig_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取TD2设备客流检测区域配置。
设备没绘制区域返回detectionArea为空
参考paas协议http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E5%AE%A2%E6%B5%81%E9%87%8F%E7%9B%91%E6%B5%8B%E5%8C%BA%E5%9F%9F%2F%E8%8E%B7%E5%8F%96%E5%AE%A2%E6%B5%81%E9%87%8F%E7%9B%91%E6%B5%8B%E5%8C%BA%E5%9F%9F.md&s=pd
 */

typedef struct thingsNumberstat_GetDetectionAreaConfigRequest 
{
	HsviewRequest base;

	struct thingsNumberstat_GetDetectionAreaConfigRequestData
	{
		
		/** 设备通道号 */
		CSTR channelId;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} thingsNumberstat_GetDetectionAreaConfigRequest;

C_API thingsNumberstat_GetDetectionAreaConfigRequest *HSAPI_INIT(thingsNumberstat_GetDetectionAreaConfigRequest);

typedef struct thingsNumberstat_GetDetectionAreaConfigResponse 
{
	HsviewResponse base;

	struct thingsNumberstat_GetDetectionAreaConfigResponseData
	{
		
		/** struct of thingsNumberstat_GetDetectionAreaConfigResponseData_DetectionArea */
		struct thingsNumberstat_GetDetectionAreaConfigResponseData_DetectionArea {
			/** 检测区域横向线起点A坐标 */
			CSTR pointA;
			/** 检测区域监控人流量方向 */
			CSTR direction;
			/** 检测区域横向线终点B坐标 */
			CSTR pointB;
			/** 检测区域竖向线终点C坐标 */
			CSTR pointC;
		} detectionArea;
 
	} data;

} thingsNumberstat_GetDetectionAreaConfigResponse;

C_API thingsNumberstat_GetDetectionAreaConfigResponse *HSAPI_INIT(thingsNumberstat_GetDetectionAreaConfigResponse);

#endif
