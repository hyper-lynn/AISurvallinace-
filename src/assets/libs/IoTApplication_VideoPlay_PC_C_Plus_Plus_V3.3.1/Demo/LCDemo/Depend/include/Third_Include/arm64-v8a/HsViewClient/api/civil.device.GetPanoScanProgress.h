/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetPanoScanProgress_H_
#define _HSVIEW_CLIENT_API_GetPanoScanProgress_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取全景扫描的进度。
若当前设备正处于全景扫描中，返回进度百分比；否则返回错误码。
【使用平台账号签名】
 */

typedef struct GetPanoScanProgressRequest 
{
	HsviewRequest base;

	struct GetPanoScanProgressRequestData
	{
		
		/** 设备ID */
		CSTR deviceId;

	} data;

} GetPanoScanProgressRequest;

C_API GetPanoScanProgressRequest *HSAPI_INIT(GetPanoScanProgressRequest);

typedef struct GetPanoScanProgressResponse 
{
	HsviewResponse base;

	struct GetPanoScanProgressResponseData
	{
		
		/** [int]进度百分比 */
		int percent;
 
	} data;

} GetPanoScanProgressResponse;

C_API GetPanoScanProgressResponse *HSAPI_INIT(GetPanoScanProgressResponse);

#endif
