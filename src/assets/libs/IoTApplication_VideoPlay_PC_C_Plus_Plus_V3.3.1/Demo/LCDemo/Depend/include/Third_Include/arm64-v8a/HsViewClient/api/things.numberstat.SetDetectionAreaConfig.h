/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_thingsNumberstat_SetDetectionAreaConfig_H_
#define _HSVIEW_CLIENT_API_thingsNumberstat_SetDetectionAreaConfig_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置TD2设备检测区域及客流方向。
检测区域为用户绘制横折线自动补全的四边形
pointA为横折线的起点，pointB为折点，pointC为终点
pointA：点位A，分别表示X、Y坐标。
pointB：点位B。 
pointC：点位C。 
direction：
	检测方向:
	AB-CD：检测AB->CD方向； 
	CD-AB：检测CD->AB方向
	设备通道号0
参考paas协议
http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E5%AE%A2%E6%B5%81%E9%87%8F%E7%9B%91%E6%B5%8B%E5%8C%BA%E5%9F%9F%2F%E8%AE%BE%E7%BD%AE%E5%AE%A2%E6%B5%81%E9%87%8F%E7%9B%91%E6%B5%8B%E5%8C%BA%E5%9F%9F.md&s=pd
 */

typedef struct thingsNumberstat_SetDetectionAreaConfigRequest 
{
	HsviewRequest base;

	struct thingsNumberstat_SetDetectionAreaConfigRequestData
	{
		
		/** 通道号 */
		CSTR channelId;
		/** struct of thingsNumberstat_SetDetectionAreaConfigRequestData_DetectionArea */
		struct thingsNumberstat_SetDetectionAreaConfigRequestData_DetectionArea {
			/** 检测区域横向线起点A坐标 */
			CSTR pointA;
			/** 检测区域监控人流量方向 */
			CSTR direction;
			/** 检测区域横向线终点B坐标 */
			CSTR pointB;
			/** 检测区域竖向线终点C坐标 */
			CSTR pointC;
		} detectionArea;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} thingsNumberstat_SetDetectionAreaConfigRequest;

C_API thingsNumberstat_SetDetectionAreaConfigRequest *HSAPI_INIT(thingsNumberstat_SetDetectionAreaConfigRequest);

typedef struct thingsNumberstat_SetDetectionAreaConfigResponse 
{
	HsviewResponse base;

	struct thingsNumberstat_SetDetectionAreaConfigResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} thingsNumberstat_SetDetectionAreaConfigResponse;

C_API thingsNumberstat_SetDetectionAreaConfigResponse *HSAPI_INIT(thingsNumberstat_SetDetectionAreaConfigResponse);

#endif
