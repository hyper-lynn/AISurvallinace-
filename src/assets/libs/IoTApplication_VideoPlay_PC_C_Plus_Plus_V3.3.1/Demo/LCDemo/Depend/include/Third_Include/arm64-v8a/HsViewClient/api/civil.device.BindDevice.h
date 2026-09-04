/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_BindDevice_H_
#define _HSVIEW_CLIENT_API_BindDevice_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
账号下添加（绑定）设备。
deviceId是需要绑定的设备ID。
deviceKey是从设备拿到的一串随机字符串（随机密码），用于后续平台对设备的认证。
deviceGpsInfo 由手机获取到的GPS信息。若任何原因导致无法获取到GPS信息，消息体里不必携带GPS信息

当设备具有Auth能力集时，deviceUsername、devicePassword作为请求必须参数

计算值的公式为，Base64(AES256_CBC(MD5(密码)))。
加密规则如下：
1. 采用CBC分组加密的方式，且固定的初始化向量（iv）；
2. 密匙（key）为：MD5(toUpperCase(deviceCode) + 'DAHUAKEY')   
   说明：(1) 密匙为（设备Id+固定字符串）后的MD5值;
         (2) MD5后的值为小写
3. 加密算法为：Base64(AES256_CBC(password，key[]，iv[]))    
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

typedef struct BindDeviceRequest 
{
	HsviewRequest base;

	struct BindDeviceRequestData
	{
		
		/** [O]设备的随机密码 */
		CSTR deviceKey;
		/** [O]设备用户名（Base64(AES256加密)） */
		CSTR deviceUsername;
		/** [O]设备验证码，在设备使能支持时填入 */
		CSTR code;
		/** [O]设备密码（Base64(AES256加密)） */
		CSTR devicePassword;
		/** struct of BindDeviceRequestData_GpsInfo */
		struct BindDeviceRequestData_GpsInfo {
			/** [double][O]经度，精确到小数点后6位，东经0~180度，西经-180~0度 */
			double longitude;
			/** [double][O]纬度，精确到小数点后6位，北纬0~90度, 南纬-90~0度 */
			double latitude;
		} gpsInfo;
		/** 设备ID */
		CSTR deviceId;

	} data;

} BindDeviceRequest;

C_API BindDeviceRequest *HSAPI_INIT(BindDeviceRequest);

typedef struct BindDeviceResponse 
{
	HsviewResponse base;

	struct BindDeviceResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} BindDeviceResponse;

C_API BindDeviceResponse *HSAPI_INIT(BindDeviceResponse);

#endif
