/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetChnAlarmMessage_H_
#define _HSVIEW_CLIENT_API_GetChnAlarmMessage_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
按通道获取报警记录的分布情况。

报警类型定义：
详见[报警类型说明](../推送/报警类型说明.md)

contentEncrypt:设备通道封面码流加密模式，字段详细说明参考[设备加密](../设备加密.md)

【使用平台账号签名】
 */

typedef struct GetChnAlarmMessageRequest 
{
	HsviewRequest base;

	struct GetChnAlarmMessageRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} GetChnAlarmMessageRequest;

C_API GetChnAlarmMessageRequest *HSAPI_INIT(GetChnAlarmMessageRequest);

typedef struct GetChnAlarmMessageResponse 
{
	HsviewResponse base;

	struct GetChnAlarmMessageResponseData
	{
		
		/** define a list with struct of GetChnAlarmMessageResponseData_ChnAlarmsElement */
		DECLARE_LIST(struct GetChnAlarmMessageResponseData_ChnAlarmsElement
		{
			/** struct of GetChnAlarmMessageResponseData_ChnAlarmsElement_ContentEncrypt */
			struct GetChnAlarmMessageResponseData_ChnAlarmsElement_ContentEncrypt {
				/** 密钥生成算法版本号 */
				CSTR ruleVersion;
				/** 内容加密模式 */
				CSTR encryptMode;
				/** 内容加密秘钥种子KeySeed的模式 */
				CSTR keyMode;
			} contentEncrypt;
			/** [int]最新的报警类型 */
			int type;
			/** 通道的缩略图URL */
			CSTR thumbUrl;
			/** [int]该通道的未读消息数量 */
			int unread;
			/** 设备ID */
			CSTR deviceId;
			/** [long]最新报警时间UNIX时间戳秒 */
			int64 time;
			/** 报警时设备本地时间，格式如2014-12-12 12:12:12 */
			CSTR localDate;
			/** [O]通道所接的设备ID */
			CSTR channelDeviceId;
			/** 通道号 */
			CSTR channelId;
			/** 通道的名称 */
			CSTR name;
			/** [O]通道设备的类型 */
			CSTR channelDeviceType;
		}) chnAlarms;
 
	} data;

} GetChnAlarmMessageResponse;

C_API GetChnAlarmMessageResponse *HSAPI_INIT(GetChnAlarmMessageResponse);

#endif
