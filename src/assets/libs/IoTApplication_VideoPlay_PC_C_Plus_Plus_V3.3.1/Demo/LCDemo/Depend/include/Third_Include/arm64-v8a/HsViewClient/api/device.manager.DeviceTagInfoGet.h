/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceManager_DeviceTagInfoGet_H_
#define _HSVIEW_CLIENT_API_deviceManager_DeviceTagInfoGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 

查询设备的安全码和IMEI号。

code计算值的公式为，Base64(AES256_CBC(MD5(密码)))。
加密规则如下：
采用CBC分组加密的方式，且固定的初始化向量（iv）；
密匙（key）为：MD5(toUpperCase(deviceCode) + 'DAHUAKEY')
说明：(1) 密匙为（设备Id+固定字符串）后的MD5值;
 (2) MD5后的值为小写
加密算法为：Base64(AES256_CBC(password，key[]，iv[]))
说明：(1) password为新、旧密码，
 (2) key[]为密匙的二进制数组，
(3) iv[]为初始化向量的二进制数组
加密算法测试用例：
iv=0a52uuEvqTTTTTTT
deviceCode=123456789
password=123456789abc
结果为 W8UNXMWbHHRz2vOaYCpQhw==


【需要使用平台账号签名】
 */

typedef struct deviceManager_DeviceTagInfoGetRequest 
{
	HsviewRequest base;

	struct deviceManager_DeviceTagInfoGetRequestData
	{
		
		/** 设备ID */
		CSTR deviceId;

	} data;

} deviceManager_DeviceTagInfoGetRequest;

C_API deviceManager_DeviceTagInfoGetRequest *HSAPI_INIT(deviceManager_DeviceTagInfoGetRequest);

typedef struct deviceManager_DeviceTagInfoGetResponse 
{
	HsviewResponse base;

	struct deviceManager_DeviceTagInfoGetResponseData
	{
		
		/** [O]设备安全码 */
		CSTR code;
		/** [O]设备IMEL */
		CSTR imei;
		/** 设备序列号 */
		CSTR deviceId;
 
	} data;

} deviceManager_DeviceTagInfoGetResponse;

C_API deviceManager_DeviceTagInfoGetResponse *HSAPI_INIT(deviceManager_DeviceTagInfoGetResponse);

#endif
