/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferAlarm_AlarmSoundGet_H_
#define _HSVIEW_CLIENT_API_transferAlarm_AlarmSoundGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取报警音效
>    响应参数说明
 + sound: 参考[报警音效定义](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2FHome.md&s=pd)
参考PaaS协议：[获取报警音效](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E6%8A%A5%E8%AD%A6%E9%85%8D%E7%BD%AE%2F%E8%8E%B7%E5%8F%96%E6%8A%A5%E8%AD%A6%E9%9F%B3%E6%95%88.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferAlarm_AlarmSoundGetRequest 
{
	HsviewRequest base;

	struct transferAlarm_AlarmSoundGetRequestData
	{
		
		/** 设备序列号 */
		CSTR deviceId;
		/** [cstr]/device/alarm/sound/query */
		#define _STATIC_transferAlarm_AlarmSoundGetRequestData_url "/device/alarm/sound/query"
		CSTR url;

	} data;

} transferAlarm_AlarmSoundGetRequest;

C_API transferAlarm_AlarmSoundGetRequest *HSAPI_INIT(transferAlarm_AlarmSoundGetRequest);

typedef struct transferAlarm_AlarmSoundGetResponse 
{
	HsviewResponse base;

	struct transferAlarm_AlarmSoundGetResponseData
	{
		
		/** alert */
		CSTR sound;
 
	} data;

} transferAlarm_AlarmSoundGetResponse;

C_API transferAlarm_AlarmSoundGetResponse *HSAPI_INIT(transferAlarm_AlarmSoundGetResponse);

#endif
