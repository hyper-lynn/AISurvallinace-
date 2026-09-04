/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferAlarm_MotionDetectStallSet_H_
#define _HSVIEW_CLIENT_API_transferAlarm_MotionDetectStallSet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置动检档位

参考PaaS协议：[设置动检参数](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E6%8A%A5%E8%AD%A6%E9%85%8D%E7%BD%AE%2F%E8%AE%BE%E7%BD%AE%E5%8A%A8%E6%A3%80%E5%8C%BA%E5%9F%9F.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferAlarm_MotionDetectStallSetRequest 
{
	HsviewRequest base;

	struct transferAlarm_MotionDetectStallSetRequestData
	{
		
		/** 设备通道号 */
		CSTR channelId;
		/** [cstr]/device/alarm/range/config/ */
		#define _STATIC_transferAlarm_MotionDetectStallSetRequestData_url "/device/alarm/range/config/"
		CSTR url;
		/** struct of transferAlarm_MotionDetectStallSetRequestData_Content */
		struct transferAlarm_MotionDetectStallSetRequestData_Content {
			/** [int]表示档位，取值范围为[1, 6] */
			int stall;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferAlarm_MotionDetectStallSetRequest;

C_API transferAlarm_MotionDetectStallSetRequest *HSAPI_INIT(transferAlarm_MotionDetectStallSetRequest);

typedef struct transferAlarm_MotionDetectStallSetResponse 
{
	HsviewResponse base;

	struct transferAlarm_MotionDetectStallSetResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} transferAlarm_MotionDetectStallSetResponse;

C_API transferAlarm_MotionDetectStallSetResponse *HSAPI_INIT(transferAlarm_MotionDetectStallSetResponse);

#endif
