/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetAlarmEffect_H_
#define _HSVIEW_CLIENT_API_GetAlarmEffect_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取设备的报警效果，如报警音效。

参数说明：
Sound字段可取三种值，定义如下：
  “mute”   静音
  “notice” 较为轻柔的报警音，起到提示作用
  “alert”  尖锐响亮的报警音，起到警示作用

【需要使用平台账号签名】
 */

typedef struct GetAlarmEffectRequest 
{
	HsviewRequest base;

	struct GetAlarmEffectRequestData
	{
		
		/** 设备ID */
		CSTR devId;
		/** 通道号 */
		CSTR optional;
		/** [cstr]GET */
		#define _STATIC_GetAlarmEffectRequestData_METHOD "GET"
		/** [cstr]alarm-effect */
		#define _STATIC_GetAlarmEffectRequestData_CMD "alarm-effect"
		/** struct of GetAlarmEffectRequestData_Body */
		struct GetAlarmEffectRequestData_Body {
			/** [int][O]保留 */
			int _nouse;
		} body;

	} data;

} GetAlarmEffectRequest;

C_API GetAlarmEffectRequest *HSAPI_INIT(GetAlarmEffectRequest);

typedef struct GetAlarmEffectResponse 
{
	HsviewResponse base;

	struct GetAlarmEffectResponseData
	{
		
		/** 报警音效，三种取值：mute、notice、alert */
		CSTR Sound;
 
	} data;

} GetAlarmEffectResponse;

C_API GetAlarmEffectResponse *HSAPI_INIT(GetAlarmEffectResponse);

#endif
