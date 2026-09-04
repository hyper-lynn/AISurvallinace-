/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceManager_P2PDeviceInfoUpload_H_
#define _HSVIEW_CLIENT_API_deviceManager_P2PDeviceInfoUpload_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
P2P设备信息上传,仅海外使用。

deviceUsername、devicePassword作为请求必须参数
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

typedef struct deviceManager_P2PDeviceInfoUploadRequest 
{
	HsviewRequest base;

	struct deviceManager_P2PDeviceInfoUploadRequestData
	{
		
		/** 设备密码，Base64(AES256_CBC(MD5(密码))) */
		CSTR devicePassword;
		/** 设备名称 */
		CSTR deviceName;
		/** 设备用户名，Base64(AES256_CBC(MD5(用户名))) */
		CSTR deviceUsername;
		/** define a list with struct of deviceManager_P2PDeviceInfoUploadRequestData_ChannelsElement */
		DECLARE_LIST(struct deviceManager_P2PDeviceInfoUploadRequestData_ChannelsElement
		{
			/** 通道ID */
			CSTR channelId;
			/** 通道封面模式，自定义:,自动抓图: */
			CSTR channelPictureMode;
			/** 通道名称 */
			CSTR channelName;
		}) channels;
		/** 设备ID */
		CSTR deviceId;

	} data;

} deviceManager_P2PDeviceInfoUploadRequest;

C_API deviceManager_P2PDeviceInfoUploadRequest *HSAPI_INIT(deviceManager_P2PDeviceInfoUploadRequest);

typedef struct deviceManager_P2PDeviceInfoUploadResponse 
{
	HsviewResponse base;

	struct deviceManager_P2PDeviceInfoUploadResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} deviceManager_P2PDeviceInfoUploadResponse;

C_API deviceManager_P2PDeviceInfoUploadResponse *HSAPI_INIT(deviceManager_P2PDeviceInfoUploadResponse);

#endif
