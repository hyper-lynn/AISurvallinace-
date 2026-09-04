/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceManager_UserDeviceBind_H_
#define _HSVIEW_CLIENT_API_deviceManager_UserDeviceBind_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
账号下添加（绑定）设备。
deviceId是需要绑定的设备ID。
deviceKey是从设备拿到的一串随机字符串（随机密码），用于后续平台对设备的认证。
当设备具有Auth能力集时，deviceUsername、devicePassword作为请求必须参数
计算值的公式为，Base64(AES256_CBC(MD5(密码)))。
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

typedef struct deviceManager_UserDeviceBindRequest 
{
	HsviewRequest base;

	struct deviceManager_UserDeviceBindRequestData
	{
		
		/** [O]从设备拿到的一串随机字符串（随机密码），用于后续平台对设备的认证,国内使用 */
		CSTR deviceKey;
		/** [O] NB iot设备唯一标识码 */
		CSTR imeiCode;
		/** [O]设备用户名（Base64(AES256加密)）,海外必须，国内设备有Auth能力集的带 */
		CSTR deviceUsername;
		/** [O]设备验证码，在设备能力集支持时填写 */
		CSTR code;
		/** [O]经度，东经0~180度，西经-180~0度,转成double最多保留6位 */
		CSTR longitude;
		/** [O]纬度，北纬0~90度, 南纬-90~0度，转成double最多保留6位 */
		CSTR latitude;
		/** [O]设备密码（Base64(AES256加密)）,海外必须，国内设备有Auth能力集的带 */
		CSTR devicePassword;
		/** 设备ID */
		CSTR deviceId;

	} data;

} deviceManager_UserDeviceBindRequest;

C_API deviceManager_UserDeviceBindRequest *HSAPI_INIT(deviceManager_UserDeviceBindRequest);

typedef struct deviceManager_UserDeviceBindResponse 
{
	HsviewResponse base;

	struct deviceManager_UserDeviceBindResponseData
	{
		
		/** [O]码流类型：main：主码流extra1：辅码流（免费套餐信息,设备有可赠送免费套餐时返回） */
		CSTR streamType;
		/** [O]绑定成功时需要返回，设备绑定初始化的设备名称(绑定成功时返回) */
		CSTR deviceName;
		/** [O]服务时长(秒)（免费套餐信息,设备有可赠送免费套餐时返回）-1 代表永久免费套餐 */
		CSTR seviceTime;
		/** [O]bindByMe, bindByOther；绑定冲突，同时绑定绑定结果为已被绑定时返回 */
		CSTR bindStatus;
		/** [O]所属账号，按产品需求做处理；bindStatus为bindByOther状态时返回 */
		CSTR userAccount;
		/** [O]录像保存天数（免费套餐信息,设备有可赠送免费套餐时返回） */
		CSTR recordSaveDays;
 
	} data;

} deviceManager_UserDeviceBindResponse;

C_API deviceManager_UserDeviceBindResponse *HSAPI_INIT(deviceManager_UserDeviceBindResponse);

#endif
