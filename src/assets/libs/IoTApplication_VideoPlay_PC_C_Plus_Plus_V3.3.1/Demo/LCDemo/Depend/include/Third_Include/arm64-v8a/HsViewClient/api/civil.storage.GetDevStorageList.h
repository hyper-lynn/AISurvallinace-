/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetDevStorageList_H_
#define _HSVIEW_CLIENT_API_GetDevStorageList_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
 获取通道的套餐列表和套餐状态
 
【使用平台账号签名】
 */

typedef struct GetDevStorageListRequest 
{
	HsviewRequest base;

	struct GetDevStorageListRequestData
	{
		
		/** 通道编号 */
		CSTR channelId;
		/** 设备ID */
		CSTR deviceId;

	} data;

} GetDevStorageListRequest;

C_API GetDevStorageListRequest *HSAPI_INIT(GetDevStorageListRequest);

typedef struct GetDevStorageListResponse 
{
	HsviewResponse base;

	struct GetDevStorageListResponseData
	{
		
		/** define a list with struct of GetDevStorageListResponseData_StrategiesElement */
		DECLARE_LIST(struct GetDevStorageListResponseData_StrategiesElement
		{
			/** 上传云存储的码流时段，alarm/always，分别表示报警时上传和全时段上传。 */
			CSTR streamInterval;
			/** [int]录像存储天数 */
			int recordStorageTimeLimit;
			/** [int]报警存储天数 */
			int alarmStorageTimeLimit;
			/** [long]套餐结束时间，1970年来秒数 */
			int64 endTime;
			/** [int]套餐状态 -1-未使用  0-过期  1-使用中 2-暂停 */
			int status;
			/** [bool]是否有服务期限，若有，则关注timeLimit字段 */
			BOOL hasTimeLimit;
			/** [long]套餐开始时间，1970年来秒数 */
			int64 beginTime;
			/** 费用 */
			CSTR fee;
			/** [long]云存储套餐ID */
			int64 strategyId;
			/** [int]云存储服务期限（天） */
			int timeLimit;
			/** [int]抓图最小间隔，单位秒 */
			int snapInterval;
			/** [int]套餐剩余秒数 */
			int timeLeft;
			/** 套餐名称 */
			CSTR name;
		}) strategies;
 
	} data;

} GetDevStorageListResponse;

C_API GetDevStorageListResponse *HSAPI_INIT(GetDevStorageListResponse);

#endif
