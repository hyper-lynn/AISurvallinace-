/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_devicePano_GetPanoScanProgress_H_
#define _HSVIEW_CLIENT_API_devicePano_GetPanoScanProgress_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取全景扫描的进度。
若当前设备正处于全景扫描中，返回进度百分比；否则返回错误码。

【使用平台账号签名】
 */

typedef struct devicePano_GetPanoScanProgressRequest 
{
	HsviewRequest base;

	struct devicePano_GetPanoScanProgressRequestData
	{
		
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} devicePano_GetPanoScanProgressRequest;

C_API devicePano_GetPanoScanProgressRequest *HSAPI_INIT(devicePano_GetPanoScanProgressRequest);

typedef struct devicePano_GetPanoScanProgressResponse 
{
	HsviewResponse base;

	struct devicePano_GetPanoScanProgressResponseData
	{
		
		/** [int]进度百分比 */
		int percent;
 
	} data;

} devicePano_GetPanoScanProgressResponse;

C_API devicePano_GetPanoScanProgressResponse *HSAPI_INIT(devicePano_GetPanoScanProgressResponse);

#endif
