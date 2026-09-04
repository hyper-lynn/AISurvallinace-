/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetAlarmSound_H_
#define _HSVIEW_CLIENT_API_GetAlarmSound_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置配件报警声音
 */

typedef struct GetAlarmSoundRequest 
{
	HsviewRequest base;

	struct GetAlarmSoundRequestData
	{
		
		/** 设备ID */
		CSTR devId;
		/** 无需设置 */
		CSTR optional;
		/** [cstr]POST */
		#define _STATIC_GetAlarmSoundRequestData_METHOD "POST"
		/** [cstr]agcmd */
		#define _STATIC_GetAlarmSoundRequestData_CMD "agcmd"
		/** struct of GetAlarmSoundRequestData_Body */
		struct GetAlarmSoundRequestData_Body {
			/** [cstr]get-alarm-sound */
			#define _STATIC_GetAlarmSoundRequestData_Body_Action "get-alarm-sound"
			/** [int][O]保留 */
			int _nouse;
		} body;

	} data;

} GetAlarmSoundRequest;

C_API GetAlarmSoundRequest *HSAPI_INIT(GetAlarmSoundRequest);

typedef struct GetAlarmSoundResponse 
{
	HsviewResponse base;

	struct GetAlarmSoundResponseData
	{
		
		/** mute-静音  notice-轻柔声音  alert-尖锐的声音 */
		CSTR Sound;
		/** [int]返回错误码。成功为0，1- 配件不存在；2-其他错误 */
		int Code;
 
	} data;

} GetAlarmSoundResponse;

C_API GetAlarmSoundResponse *HSAPI_INIT(GetAlarmSoundResponse);

#endif
