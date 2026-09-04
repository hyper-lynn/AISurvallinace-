/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_thingsAp_SetApAlarmSound_H_
#define _HSVIEW_CLIENT_API_thingsAp_SetApAlarmSound_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置报警网关配件报警音效。

sound表示报警音效，取值如下：
mute ： 静音
notice : 较为轻柔的报警音，起到提示作用
alert ： 尖锐响亮的报警音，起到警示作用

sound说明参考PaaS协议：[设置配件报警音效](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E6%8A%A5%E8%AD%A6%E7%BD%91%E5%85%B3%2F%E9%9F%B3%E6%95%88%E9%85%8D%E7%BD%AE%2F%E8%AE%BE%E7%BD%AE%E9%85%8D%E4%BB%B6%E6%8A%A5%E8%AD%A6%E9%9F%B3%E6%95%88.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct thingsAp_SetApAlarmSoundRequest 
{
	HsviewRequest base;

	struct thingsAp_SetApAlarmSoundRequestData
	{
		
		/** 报警音效 */
		CSTR sound;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} thingsAp_SetApAlarmSoundRequest;

C_API thingsAp_SetApAlarmSoundRequest *HSAPI_INIT(thingsAp_SetApAlarmSoundRequest);

typedef struct thingsAp_SetApAlarmSoundResponse 
{
	HsviewResponse base;

	struct thingsAp_SetApAlarmSoundResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} thingsAp_SetApAlarmSoundResponse;

C_API thingsAp_SetApAlarmSoundResponse *HSAPI_INIT(thingsAp_SetApAlarmSoundResponse);

#endif
