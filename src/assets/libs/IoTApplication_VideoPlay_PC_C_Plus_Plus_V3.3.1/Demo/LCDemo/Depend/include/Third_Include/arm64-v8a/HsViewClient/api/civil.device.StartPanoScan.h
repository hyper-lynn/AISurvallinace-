/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_StartPanoScan_H_
#define _HSVIEW_CLIENT_API_StartPanoScan_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
开始全景云台扫描。
客户端要求生成全景图时先调用此接口。

secretKey：用户未开启加密时，secretKey为Base64（设备序列号）；
用户开启设备加密时，Base64（自定义密钥）作为请求密钥。

错误码：
1、1327 : 设备密钥错误
【使用平台账号签名】
 */

typedef struct StartPanoScanRequest 
{
	HsviewRequest base;

	struct StartPanoScanRequestData
	{
		
		/** 密钥，Base64（deviceId/customKey） */
		CSTR secretKey;
		/** 设备ID */
		CSTR deviceId;

	} data;

} StartPanoScanRequest;

C_API StartPanoScanRequest *HSAPI_INIT(StartPanoScanRequest);

typedef struct StartPanoScanResponse 
{
	HsviewResponse base;

	struct StartPanoScanResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} StartPanoScanResponse;

C_API StartPanoScanResponse *HSAPI_INIT(StartPanoScanResponse);

#endif
