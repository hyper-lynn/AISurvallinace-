/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferAlarm_AccessoryAlarmSoundSet_H_
#define _HSVIEW_CLIENT_API_transferAlarm_AccessoryAlarmSoundSet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置配件报警音效


>    请求参数说明
 + sound: 参考[报警音效定义](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2FHome.md&s=pd)

参考PaaS协议：[设置配件报警音效](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E6%8A%A5%E8%AD%A6%E7%BD%91%E5%85%B3%2F%E9%9F%B3%E6%95%88%E9%85%8D%E7%BD%AE%2F%E8%AE%BE%E7%BD%AE%E9%85%8D%E4%BB%B6%E6%8A%A5%E8%AD%A6%E9%9F%B3%E6%95%88.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferAlarm_AccessoryAlarmSoundSetRequest 
{
	HsviewRequest base;

	struct transferAlarm_AccessoryAlarmSoundSetRequestData
	{
		
		/** [cstr]/device/accessory/sound/config */
		#define _STATIC_transferAlarm_AccessoryAlarmSoundSetRequestData_url "/device/accessory/sound/config"
		CSTR url;
		/** struct of transferAlarm_AccessoryAlarmSoundSetRequestData_Content */
		struct transferAlarm_AccessoryAlarmSoundSetRequestData_Content {
			/** alert */
			CSTR sound;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferAlarm_AccessoryAlarmSoundSetRequest;

C_API transferAlarm_AccessoryAlarmSoundSetRequest *HSAPI_INIT(transferAlarm_AccessoryAlarmSoundSetRequest);

typedef struct transferAlarm_AccessoryAlarmSoundSetResponse 
{
	HsviewResponse base;

	struct transferAlarm_AccessoryAlarmSoundSetResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} transferAlarm_AccessoryAlarmSoundSetResponse;

C_API transferAlarm_AccessoryAlarmSoundSetResponse *HSAPI_INIT(transferAlarm_AccessoryAlarmSoundSetResponse);

#endif
