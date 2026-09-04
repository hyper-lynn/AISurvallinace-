/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetDefaultStorage_H_
#define _HSVIEW_CLIENT_API_GetDefaultStorage_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
 获取设备的默认套餐信息
 默认套餐如果是有期限的，如果用户使用过并且已过期，则改套餐不能再重复使用；
 永久免费的套餐没有该限制；
 
【使用平台账号签名】
 */

typedef struct GetDefaultStorageRequest 
{
	HsviewRequest base;

	struct GetDefaultStorageRequestData
	{
		
		/** 通道Id */
		CSTR channelId;
		/** 设备ID */
		CSTR deviceId;

	} data;

} GetDefaultStorageRequest;

C_API GetDefaultStorageRequest *HSAPI_INIT(GetDefaultStorageRequest);

typedef struct GetDefaultStorageResponse 
{
	HsviewResponse base;

	struct GetDefaultStorageResponseData
	{
		
		/** struct of GetDefaultStorageResponseData_StrategyInfo */
		struct GetDefaultStorageResponseData_StrategyInfo {
			/** [bool]是否有服务期限，若有，则关注timeLimit字段 */
			BOOL hasTimeLimit;
			/** [int]录像存储天数 */
			int recordStorageTimeLimit;
			/** 套餐名称 */
			CSTR name;
			/** [int]报警存储天数 */
			int alarmStorageTimeLimit;
			/** [int]云存储服务期限（天） */
			int timeLimit;
			/** [int]抓图最小间隔，单位秒 */
			int snapInterval;
			/** 上传云存储的码流时段，alarm/always，分别表示报警时上传和全时段上传。 */
			CSTR streamInterval;
			/** 费用 */
			CSTR fee;
		} strategyInfo;
		/** [long]云存储套餐ID */
		int64 strategyId;
		/** [long]套餐结束时间，1970年来秒数 */
		int64 endTime;
		/** [long]套餐开始时间，1970年来秒数 */
		int64 beginTime;
		/** [int]套餐剩余秒数 */
		int timeLeft;
		/** [int]套餐状态 -1-未开通  0-过期  1-使用中  2-暂停 */
		int status;
 
	} data;

} GetDefaultStorageResponse;

C_API GetDefaultStorageResponse *HSAPI_INIT(GetDefaultStorageResponse);

#endif
