/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_thingsAp_GetApAlarmSound_H_
#define _HSVIEW_CLIENT_API_thingsAp_GetApAlarmSound_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取报警网关配件报警音效。

sound表示报警音效，取值如下：
mute ： 静音
notice : 较为轻柔的报警音，起到提示作用
alert ： 尖锐响亮的报警音，起到警示作用

sound说明参考PaaS协议：[获取配件报警音效](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E6%8A%A5%E8%AD%A6%E7%BD%91%E5%85%B3%2F%E9%9F%B3%E6%95%88%E9%85%8D%E7%BD%AE%2F%E8%8E%B7%E5%8F%96%E9%85%8D%E4%BB%B6%E6%8A%A5%E8%AD%A6%E9%9F%B3%E6%95%88.md&s=pd)
【需要使用平台账号签名】
 */

typedef struct thingsAp_GetApAlarmSoundRequest 
{
	HsviewRequest base;

	struct thingsAp_GetApAlarmSoundRequestData
	{
		
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} thingsAp_GetApAlarmSoundRequest;

C_API thingsAp_GetApAlarmSoundRequest *HSAPI_INIT(thingsAp_GetApAlarmSoundRequest);

typedef struct thingsAp_GetApAlarmSoundResponse 
{
	HsviewResponse base;

	struct thingsAp_GetApAlarmSoundResponseData
	{
		
		/** 报警音效 */
		CSTR sound;
 
	} data;

} thingsAp_GetApAlarmSoundResponse;

C_API thingsAp_GetApAlarmSoundResponse *HSAPI_INIT(thingsAp_GetApAlarmSoundResponse);

#endif
