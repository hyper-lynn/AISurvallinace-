/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_cloudRecord_GetRecordByAlarmId_H_
#define _HSVIEW_CLIENT_API_cloudRecord_GetRecordByAlarmId_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
根据消息id获取对应的云录像。
注意：
入参的channelId适用于权限校验，如果不带，平台默认用0通道去校验权限，对于多通道设备的非0通道的权限校验就会有问题
【使用平台账号签名】
 */

typedef struct cloudRecord_GetRecordByAlarmIdRequest 
{
	HsviewRequest base;

	struct cloudRecord_GetRecordByAlarmIdRequestData
	{
		
		/** 报警消息对应的token，非报警消息记录的id */
		CSTR alarmId;
		/** [O]设备通道号 */
		CSTR channelId;
		/** [O]录像类型，为空表示不区分录像类型 */
		CSTR type;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} cloudRecord_GetRecordByAlarmIdRequest;

C_API cloudRecord_GetRecordByAlarmIdRequest *HSAPI_INIT(cloudRecord_GetRecordByAlarmIdRequest);

typedef struct cloudRecord_GetRecordByAlarmIdResponse 
{
	HsviewResponse base;

	struct cloudRecord_GetRecordByAlarmIdResponseData
	{
		
		/** 区域 */
		CSTR region;
		/** 设备本地开始时间,yyyyMMddTHHmmss格式 */
		CSTR localBeginTime;
		/** 录像文件路径 */
		CSTR recordPath;
		/** [O]通道号（开放平台新增） */
		CSTR channelId;
		/** 缩略图URL */
		CSTR thumbUrl;
		/** 设备本地结束时间,yyyyMMddTHHmmss格式 */
		CSTR localEndTime;
		/** [int]加密模式, 0表示默认加密模式, 1表示用户加密模式 */
		int encryptMode;
		/** [long]录像ID */
		int64 recordId;
		/** [long]云录像的大小，单位byte */
		int64 size;
 
	} data;

} cloudRecord_GetRecordByAlarmIdResponse;

C_API cloudRecord_GetRecordByAlarmIdResponse *HSAPI_INIT(cloudRecord_GetRecordByAlarmIdResponse);

#endif
