/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_MarkAlarmMessage_H_
#define _HSVIEW_CLIENT_API_MarkAlarmMessage_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
标识报警信息，按照设备序列号和通道号进行标记。

deviceId和channelId必须携带，markIds有值的话，必须是这个设备这个通道号下面的所有报警信息。

若markIds有值，则直接标记这个设备这个通道号下这些指定的报警消息ID，否则标记这个设备这个通道号下面的所有报警信息。


【使用平台账号签名】
 */

typedef struct MarkAlarmMessageRequest 
{
	HsviewRequest base;

	struct MarkAlarmMessageRequestData
	{
		
		/** [long]开始时间。Unix时间（单位秒），0表示最早时间 */
		int64 beginTime;
		/** [long]需要标识的消息ID */
		DECLARE_LIST(int64) markIds;
		/** [long]结束时间。Unix时间（单位秒），0表示最晚时间 */
		int64 endTime;
		/** 标记设备下该通道号（可填通道所接设备ID）的报警消息 */
		CSTR channelId;
		/** [int]动作，0代表设置为未读，1代表设置为已读 */
		int markAction;
		/** 标记该设备ID的报警消息 */
		CSTR deviceId;

	} data;

} MarkAlarmMessageRequest;

C_API MarkAlarmMessageRequest *HSAPI_INIT(MarkAlarmMessageRequest);

typedef struct MarkAlarmMessageResponse 
{
	HsviewResponse base;

	struct MarkAlarmMessageResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} MarkAlarmMessageResponse;

C_API MarkAlarmMessageResponse *HSAPI_INIT(MarkAlarmMessageResponse);

#endif
