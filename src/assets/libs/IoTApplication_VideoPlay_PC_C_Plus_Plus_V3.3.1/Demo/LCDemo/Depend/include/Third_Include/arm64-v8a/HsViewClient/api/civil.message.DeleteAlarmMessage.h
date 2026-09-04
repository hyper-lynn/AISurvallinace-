/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_DeleteAlarmMessage_H_
#define _HSVIEW_CLIENT_API_DeleteAlarmMessage_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
根据设备序列号和通道号删除报警信息。
deviceId和channelId必须携带，deleteIds有值的话，必须是这个设备这个通道号下面的所有报警信息

若deleteIds有值，则直接删除这些指定的报警消息ID，否则删除这个设备这个通道号下面的所有报警信息。
【使用平台账号签名】
 */

typedef struct DeleteAlarmMessageRequest 
{
	HsviewRequest base;

	struct DeleteAlarmMessageRequestData
	{
		
		/** [long]开始时间。Unix时间（单位秒），0表示最早时间 */
		int64 beginTime;
		/** [int] 0表示删除未读，1表示删除已读，-1表示删除所有 */
		int readFlag;
		/** [long]结束时间。Unix时间（单位秒），0表示最晚时间 */
		int64 endTime;
		/** 删除设备下该通道号（可填通道所接设备ID）的报警消息。 */
		CSTR channelId;
		/** [long]需要删除的消息ID */
		DECLARE_LIST(int64) deleteIds;
		/** 删除该设备ID的报警消息。 */
		CSTR deviceId;

	} data;

} DeleteAlarmMessageRequest;

C_API DeleteAlarmMessageRequest *HSAPI_INIT(DeleteAlarmMessageRequest);

typedef struct DeleteAlarmMessageResponse 
{
	HsviewResponse base;

	struct DeleteAlarmMessageResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} DeleteAlarmMessageResponse;

C_API DeleteAlarmMessageResponse *HSAPI_INIT(DeleteAlarmMessageResponse);

#endif
