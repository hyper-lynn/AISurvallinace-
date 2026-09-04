/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_cloudMessage_GetOpenDoorRecord_H_
#define _HSVIEW_CLIENT_API_cloudMessage_GetOpenDoorRecord_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
分页获取开锁记录，倒序
【需要使用平台账号签名】
 */

typedef struct cloudMessage_GetOpenDoorRecordRequest 
{
	HsviewRequest base;

	struct cloudMessage_GetOpenDoorRecordRequestData
	{
		
		/** [long]开锁记录id，初次请求为-1，以后每次请求该id即为上次请求中最后一条记录id */
		int64 recordId;
		/** [int]手机所在时区的时间与零时区时间差值，单位为秒，可正负 */
		int timezoneOffset;
		/** [int]需要查的最大条数 */
		int count;
		/** 门锁序列号 */
		CSTR deviceId;

	} data;

} cloudMessage_GetOpenDoorRecordRequest;

C_API cloudMessage_GetOpenDoorRecordRequest *HSAPI_INIT(cloudMessage_GetOpenDoorRecordRequest);

typedef struct cloudMessage_GetOpenDoorRecordResponse 
{
	HsviewResponse base;

	struct cloudMessage_GetOpenDoorRecordResponseData
	{
		
		/** define a list with struct of cloudMessage_GetOpenDoorRecordResponseData_RecordsElement */
		DECLARE_LIST(struct cloudMessage_GetOpenDoorRecordResponseData_RecordsElement
		{
			/** 钥匙类型，password:密码；card:卡；fingerPrint：指纹；snapkey:临时秘钥; faceAndfinger:人脸+指纹; passwordAndfinger:密码+指纹; */
			CSTR type;
			/** 钥匙名称 */
			CSTR name;
			/** [long]开锁记录id */
			int64 recordId;
			/** 开锁本地时间，格式20170418T162832 */
			CSTR localTime;
			/** 展示文案 */
			CSTR title;
		}) records;
 
	} data;

} cloudMessage_GetOpenDoorRecordResponse;

C_API cloudMessage_GetOpenDoorRecordResponse *HSAPI_INIT(cloudMessage_GetOpenDoorRecordResponse);

#endif
