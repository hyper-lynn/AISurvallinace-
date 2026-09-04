/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_thingsRecord_GetLocalRecords_H_
#define _HSVIEW_CLIENT_API_thingsRecord_GetLocalRecords_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取设备本地录像信息

录像类型和码流类型说明参考：[设备本地录像信息](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E6%9C%AC%E5%9C%B0%E5%BD%95%E5%83%8F%E5%9B%BE%E7%89%87%E4%BF%A1%E6%81%AF%2FHome.md&s=pd)

示例：
start：1,limit填25，表示从第1条开始，获取25条录像记录，即第1~25条

对于有AIRecordV1的设备, 不需要加入desc字段，如果想查询human类型,那么传递的type值为 all, 在objectType字段里加入["Human"],查询车时，传递的type值为 all, 在objectType字段里加入["Vehicle"],objectType里的取值当前支持"Unknown", "Human", "Vehicle", "NonMotor"
对于不支持AIRecordV1的设备，type值和desc取值约定如下：

当type == crossLine或者type == crossRegion时:
 {
    "ObjectType": ["Human"]
 }
 

注：若设备无存储介质，平台会返回错误码:13700。

增加sessionId参数,配合设备本地录像查询优化方案:https://pc-jira.dahuatech.com/pages/viewpage.action?pageId=416415900

【需要使用平台账号签名】
 */

typedef struct thingsRecord_GetLocalRecordsRequest 
{
	HsviewRequest base;

	struct thingsRecord_GetLocalRecordsRequestData
	{
		
		/** 录像类型 */
		CSTR type;
		/** 设备本地结束时间,yyyyMMddTHHmmss格式 */
		CSTR endTime;
		/** 设备序列号 */
		CSTR deviceId;
		/** struct of thingsRecord_GetLocalRecordsRequestData_Desc */
		struct thingsRecord_GetLocalRecordsRequestData_Desc {
			/** Human */
			DECLARE_LIST(CSTR) ObjectType;
		} desc;
		/** [int]限制查询数量，取值范围是1-100 */
		int limit;
		/** [O]用于本地录像查询优化,有此参数的情况下设备会优先使用此参数查询 */
		CSTR sessionId;
		/** [int]开始条数，从1开始 */
		int start;
		/** 设备本地开始时间,yyyyMMddTHHmmss格式 */
		CSTR beginTime;
		/** Human */
		DECLARE_LIST(CSTR) objectType;
		/** 通道号 */
		CSTR channelId;

	} data;

} thingsRecord_GetLocalRecordsRequest;

C_API thingsRecord_GetLocalRecordsRequest *HSAPI_INIT(thingsRecord_GetLocalRecordsRequest);

typedef struct thingsRecord_GetLocalRecordsResponse 
{
	HsviewResponse base;

	struct thingsRecord_GetLocalRecordsResponseData
	{
		
		/** [O]支持本地录像查询优化的设备会返回此值,在接下来的查询中将此值带入可替代type/beginTime/endTime,并在设备端处理时间有优化 */
		CSTR sessionId;
		/** define a list with struct of thingsRecord_GetLocalRecordsResponseData_RecordsElement */
		DECLARE_LIST(struct thingsRecord_GetLocalRecordsResponseData_RecordsElement
		{
			/** 码流类型 */
			CSTR streamType;
			/** 录像类型 */
			CSTR type;
			/** 可选，type等于muti时携带,如AlarmLocal、videomotion */
			DECLARE_LIST(CSTR) events;
			/** [O]Human */
			DECLARE_LIST(CSTR) objectType;
			/** 本地结束时间,yyyyMMddTHHmmss格式 */
			CSTR endTime;
			/** 本地开始时间,yyyyMMddTHHmmss格式 */
			CSTR beginTime;
			/** 本地录像文件名 */
			CSTR fileName;
			/** [long]录像大小 */
			int64 fileLength;
		}) records;
 
	} data;

} thingsRecord_GetLocalRecordsResponse;

C_API thingsRecord_GetLocalRecordsResponse *HSAPI_INIT(thingsRecord_GetLocalRecordsResponse);

#endif
