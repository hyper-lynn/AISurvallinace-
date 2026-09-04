/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_StopPanoScan_H_
#define _HSVIEW_CLIENT_API_StopPanoScan_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
停止全景云台扫描。
【使用平台账号签名】
 */

typedef struct StopPanoScanRequest 
{
	HsviewRequest base;

	struct StopPanoScanRequestData
	{
		
		/** 设备ID */
		CSTR deviceId;

	} data;

} StopPanoScanRequest;

C_API StopPanoScanRequest *HSAPI_INIT(StopPanoScanRequest);

typedef struct StopPanoScanResponse 
{
	HsviewResponse base;

	struct StopPanoScanResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} StopPanoScanResponse;

C_API StopPanoScanResponse *HSAPI_INIT(StopPanoScanResponse);

#endif
