/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_SetAlarmEffect_H_
#define _HSVIEW_CLIENT_API_SetAlarmEffect_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置设备的报警效果，如报警音效。

参数说明：
Sound字段可取三种值，定义如下：
  “mute”   静音
  “notice” 较为轻柔的报警音，起到提示作用
  “alert”  尖锐响亮的报警音，起到警示作用

【需要使用平台账号签名】
 */

typedef struct SetAlarmEffectRequest 
{
	HsviewRequest base;

	struct SetAlarmEffectRequestData
	{
		
		/** 设备ID */
		CSTR devId;
		/** 通道号 */
		CSTR optional;
		/** [cstr]POST */
		#define _STATIC_SetAlarmEffectRequestData_METHOD "POST"
		/** [cstr]alarm-effect */
		#define _STATIC_SetAlarmEffectRequestData_CMD "alarm-effect"
		/** struct of SetAlarmEffectRequestData_Body */
		struct SetAlarmEffectRequestData_Body {
			/** 报警音效，三种取值：mute、notice、alert */
			CSTR Sound;
		} body;

	} data;

} SetAlarmEffectRequest;

C_API SetAlarmEffectRequest *HSAPI_INIT(SetAlarmEffectRequest);

typedef struct SetAlarmEffectResponse 
{
	HsviewResponse base;

	struct SetAlarmEffectResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} SetAlarmEffectResponse;

C_API SetAlarmEffectResponse *HSAPI_INIT(SetAlarmEffectResponse);

#endif
