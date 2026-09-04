/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferAlarmdevice_AccessoryKeyPrepareCreate_H_
#define _HSVIEW_CLIENT_API_transferAlarmdevice_AccessoryKeyPrepareCreate_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
录入秘钥


参考PaaS协议：[录入秘钥](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E6%8A%A5%E8%AD%A6%E7%BD%91%E5%85%B3%2F%E6%93%8D%E4%BD%9C%E9%85%8D%E4%BB%B6%2F%E5%BD%95%E5%85%A5%E7%A7%98%E9%92%A5.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferAlarmdevice_AccessoryKeyPrepareCreateRequest 
{
	HsviewRequest base;

	struct transferAlarmdevice_AccessoryKeyPrepareCreateRequestData
	{
		
		/** struct of transferAlarmdevice_AccessoryKeyPrepareCreateRequestData_Content */
		struct transferAlarmdevice_AccessoryKeyPrepareCreateRequestData_Content {
			/** [O]将要录入的密码、卡、指纹的归属账号，如：18969907618 */
			CSTR accountNumber;
		} content;
		/** [cstr]/device/alarmdevice/entry-key/ */
		#define _STATIC_transferAlarmdevice_AccessoryKeyPrepareCreateRequestData_url "/device/alarmdevice/entry-key/"
		CSTR url;
		/** 配件序列号 */
		CSTR accessoryId;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferAlarmdevice_AccessoryKeyPrepareCreateRequest;

C_API transferAlarmdevice_AccessoryKeyPrepareCreateRequest *HSAPI_INIT(transferAlarmdevice_AccessoryKeyPrepareCreateRequest);

typedef struct transferAlarmdevice_AccessoryKeyPrepareCreateResponse 
{
	HsviewResponse base;

	struct transferAlarmdevice_AccessoryKeyPrepareCreateResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} transferAlarmdevice_AccessoryKeyPrepareCreateResponse;

C_API transferAlarmdevice_AccessoryKeyPrepareCreateResponse *HSAPI_INIT(transferAlarmdevice_AccessoryKeyPrepareCreateResponse);

#endif
