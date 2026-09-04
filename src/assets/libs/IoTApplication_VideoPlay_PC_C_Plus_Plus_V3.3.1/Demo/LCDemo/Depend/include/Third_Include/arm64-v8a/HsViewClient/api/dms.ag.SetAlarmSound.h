/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_SetAlarmSound_H_
#define _HSVIEW_CLIENT_API_SetAlarmSound_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置配件报警声音
 */

typedef struct SetAlarmSoundRequest 
{
	HsviewRequest base;

	struct SetAlarmSoundRequestData
	{
		
		/** 设备ID */
		CSTR devId;
		/** 无需设置 */
		CSTR optional;
		/** [cstr]POST */
		#define _STATIC_SetAlarmSoundRequestData_METHOD "POST"
		/** [cstr]agcmd */
		#define _STATIC_SetAlarmSoundRequestData_CMD "agcmd"
		/** struct of SetAlarmSoundRequestData_Body */
		struct SetAlarmSoundRequestData_Body {
			/** [cstr]set-alarm-sound */
			#define _STATIC_SetAlarmSoundRequestData_Body_Action "set-alarm-sound"
			/** mute-静音  notice-轻柔声音  alert-尖锐的声音 */
			CSTR Sound;
		} body;

	} data;

} SetAlarmSoundRequest;

C_API SetAlarmSoundRequest *HSAPI_INIT(SetAlarmSoundRequest);

typedef struct SetAlarmSoundResponse 
{
	HsviewResponse base;

	struct SetAlarmSoundResponseData
	{
		
		/** [int]返回错误码。成功为0，1- 配件不存在；2-其他错误 */
		int Code;
 
	} data;

} SetAlarmSoundResponse;

C_API SetAlarmSoundResponse *HSAPI_INIT(SetAlarmSoundResponse);

#endif
