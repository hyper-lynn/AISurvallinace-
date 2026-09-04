/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferAlarm_MotionDetectSensitiveSet_H_
#define _HSVIEW_CLIENT_API_transferAlarm_MotionDetectSensitiveSet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置动检档位

参考PaaS协议：[设置动检参数](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E6%8A%A5%E8%AD%A6%E9%85%8D%E7%BD%AE%2F%E8%AE%BE%E7%BD%AE%E5%8A%A8%E6%A3%80%E5%8C%BA%E5%9F%9F.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferAlarm_MotionDetectSensitiveSetRequest 
{
	HsviewRequest base;

	struct transferAlarm_MotionDetectSensitiveSetRequestData
	{
		
		/** 设备通道号 */
		CSTR channelId;
		/** [cstr]/device/alarm/range/config/ */
		#define _STATIC_transferAlarm_MotionDetectSensitiveSetRequestData_url "/device/alarm/range/config/"
		CSTR url;
		/** struct of transferAlarm_MotionDetectSensitiveSetRequestData_Content */
		struct transferAlarm_MotionDetectSensitiveSetRequestData_Content {
			/** [int]面积阀值，取值[0, 100] */
			int threshold;
			/** [int]灵敏度，取值[0, 100] */
			int sensitive;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferAlarm_MotionDetectSensitiveSetRequest;

C_API transferAlarm_MotionDetectSensitiveSetRequest *HSAPI_INIT(transferAlarm_MotionDetectSensitiveSetRequest);

typedef struct transferAlarm_MotionDetectSensitiveSetResponse 
{
	HsviewResponse base;

	struct transferAlarm_MotionDetectSensitiveSetResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} transferAlarm_MotionDetectSensitiveSetResponse;

C_API transferAlarm_MotionDetectSensitiveSetResponse *HSAPI_INIT(transferAlarm_MotionDetectSensitiveSetResponse);

#endif
