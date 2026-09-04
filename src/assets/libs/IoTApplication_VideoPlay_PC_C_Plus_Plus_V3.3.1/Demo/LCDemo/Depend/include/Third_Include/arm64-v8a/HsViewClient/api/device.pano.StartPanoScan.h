/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_devicePano_StartPanoScan_H_
#define _HSVIEW_CLIENT_API_devicePano_StartPanoScan_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
开始全景云台扫描。

secretKey计算值的公式为，Base64(AES256_CBC(LowerCase(md5(sourceStr))，key[]，iv[]))
加密规则如下：
1. 采用CBC分组加密的方式，且固定的初始化向量（iv）；
2. 密匙（key）为：LowerCase(MD5(UPPER(deviceId+"DAHUAKEY")))
3. 加密算法说明：
	(1) 用户未开启加密时，sourceStr为设备序列号，用户开启设备加密时，sourceStr为明文自定义密钥
	(2) key[]为密匙的二进制数组
	(3) iv[]为初始化向量的二进制数组，iv真实值开发时需要向平台取

【使用平台账号签名】
 */

typedef struct devicePano_StartPanoScanRequest 
{
	HsviewRequest base;

	struct devicePano_StartPanoScanRequestData
	{
		
		/** 密钥 */
		CSTR secretKey;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} devicePano_StartPanoScanRequest;

C_API devicePano_StartPanoScanRequest *HSAPI_INIT(devicePano_StartPanoScanRequest);

typedef struct devicePano_StartPanoScanResponse 
{
	HsviewResponse base;

	struct devicePano_StartPanoScanResponseData
	{
		
		/** [int]是否支持三码合一能力，0-否，1-是, 该字段PaaS返回后，SaaS去除 */
		int isTCM;
 
	} data;

} devicePano_StartPanoScanResponse;

C_API devicePano_StartPanoScanResponse *HSAPI_INIT(devicePano_StartPanoScanResponse);

#endif
