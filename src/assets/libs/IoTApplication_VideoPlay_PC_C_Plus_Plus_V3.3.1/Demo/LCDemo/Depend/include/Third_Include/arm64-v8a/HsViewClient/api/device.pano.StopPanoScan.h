/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_devicePano_StopPanoScan_H_
#define _HSVIEW_CLIENT_API_devicePano_StopPanoScan_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
停止全景云台扫描。

【使用平台账号签名】
 */

typedef struct devicePano_StopPanoScanRequest 
{
	HsviewRequest base;

	struct devicePano_StopPanoScanRequestData
	{
		
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} devicePano_StopPanoScanRequest;

C_API devicePano_StopPanoScanRequest *HSAPI_INIT(devicePano_StopPanoScanRequest);

typedef struct devicePano_StopPanoScanResponse 
{
	HsviewResponse base;

	struct devicePano_StopPanoScanResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} devicePano_StopPanoScanResponse;

C_API devicePano_StopPanoScanResponse *HSAPI_INIT(devicePano_StopPanoScanResponse);

#endif
