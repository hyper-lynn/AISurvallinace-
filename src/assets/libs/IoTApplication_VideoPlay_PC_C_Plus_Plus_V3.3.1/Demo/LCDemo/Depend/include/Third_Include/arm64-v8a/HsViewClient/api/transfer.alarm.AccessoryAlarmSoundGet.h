/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferAlarm_AccessoryAlarmSoundGet_H_
#define _HSVIEW_CLIENT_API_transferAlarm_AccessoryAlarmSoundGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取配件报警音效

>    响应参数说明
 + sound: 参考[报警音效定义](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2FHome.md&s=pd)


参考PaaS协议：[获取配件报警音效](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E6%8A%A5%E8%AD%A6%E7%BD%91%E5%85%B3%2F%E9%9F%B3%E6%95%88%E9%85%8D%E7%BD%AE%2F%E8%8E%B7%E5%8F%96%E9%85%8D%E4%BB%B6%E6%8A%A5%E8%AD%A6%E9%9F%B3%E6%95%88.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferAlarm_AccessoryAlarmSoundGetRequest 
{
	HsviewRequest base;

	struct transferAlarm_AccessoryAlarmSoundGetRequestData
	{
		
		/** 设备序列号 */
		CSTR deviceId;
		/** [cstr]/device/accessory/sound/query */
		#define _STATIC_transferAlarm_AccessoryAlarmSoundGetRequestData_url "/device/accessory/sound/query"
		CSTR url;

	} data;

} transferAlarm_AccessoryAlarmSoundGetRequest;

C_API transferAlarm_AccessoryAlarmSoundGetRequest *HSAPI_INIT(transferAlarm_AccessoryAlarmSoundGetRequest);

typedef struct transferAlarm_AccessoryAlarmSoundGetResponse 
{
	HsviewResponse base;

	struct transferAlarm_AccessoryAlarmSoundGetResponseData
	{
		
		/** 配件报警音效 */
		CSTR sound;
 
	} data;

} transferAlarm_AccessoryAlarmSoundGetResponse;

C_API transferAlarm_AccessoryAlarmSoundGetResponse *HSAPI_INIT(transferAlarm_AccessoryAlarmSoundGetResponse);

#endif
