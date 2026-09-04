/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_RecordDeviceLog_H_
#define _HSVIEW_CLIENT_API_RecordDeviceLog_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
记录盒子的异常信息日志，可附带日志文件（事先上传到GUS）。
【需要使用平台账号签名】使用一个单独的平台账号鉴权，所有设备都使用该账号签名。
 */

typedef struct RecordDeviceLogRequest 
{
	HsviewRequest base;

	struct RecordDeviceLogRequestData
	{
		
		/** 标题 */
		CSTR title;
		/** 日志文件的云存储路径（为空表示没有文件） */
		CSTR filePath;
		/** 设备软件版本号 */
		CSTR version;
		/** 设备ID */
		CSTR deviceId;
		/** 描述 */
		CSTR desc;

	} data;

} RecordDeviceLogRequest;

C_API RecordDeviceLogRequest *HSAPI_INIT(RecordDeviceLogRequest);

typedef struct RecordDeviceLogResponse 
{
	HsviewResponse base;

	struct RecordDeviceLogResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} RecordDeviceLogResponse;

C_API RecordDeviceLogResponse *HSAPI_INIT(RecordDeviceLogResponse);

#endif
