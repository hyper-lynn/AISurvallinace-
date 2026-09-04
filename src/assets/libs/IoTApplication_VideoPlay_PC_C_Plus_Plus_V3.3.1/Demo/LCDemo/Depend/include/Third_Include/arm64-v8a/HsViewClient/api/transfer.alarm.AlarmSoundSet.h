/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferAlarm_AlarmSoundSet_H_
#define _HSVIEW_CLIENT_API_transferAlarm_AlarmSoundSet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置报警音效
>    请求参数说明
 + sound: 参考[报警音效定义](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2FHome.md&s=pd)

参考PaaS协议：[设置报警音效](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E6%8A%A5%E8%AD%A6%E9%85%8D%E7%BD%AE%2F%E8%AE%BE%E7%BD%AE%E6%8A%A5%E8%AD%A6%E9%9F%B3%E6%95%88.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferAlarm_AlarmSoundSetRequest 
{
	HsviewRequest base;

	struct transferAlarm_AlarmSoundSetRequestData
	{
		
		/** [cstr]/device/alarm/sound/config */
		#define _STATIC_transferAlarm_AlarmSoundSetRequestData_url "/device/alarm/sound/config"
		CSTR url;
		/** struct of transferAlarm_AlarmSoundSetRequestData_Content */
		struct transferAlarm_AlarmSoundSetRequestData_Content {
			/** alert */
			CSTR sound;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferAlarm_AlarmSoundSetRequest;

C_API transferAlarm_AlarmSoundSetRequest *HSAPI_INIT(transferAlarm_AlarmSoundSetRequest);

typedef struct transferAlarm_AlarmSoundSetResponse 
{
	HsviewResponse base;

	struct transferAlarm_AlarmSoundSetResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} transferAlarm_AlarmSoundSetResponse;

C_API transferAlarm_AlarmSoundSetResponse *HSAPI_INIT(transferAlarm_AlarmSoundSetResponse);

#endif
