/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetCardStorage_H_
#define _HSVIEW_CLIENT_API_GetCardStorage_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
 根据点卡获取对应的套餐信息
 
【使用平台账号签名】
 */

typedef struct GetCardStorageRequest 
{
	HsviewRequest base;

	struct GetCardStorageRequestData
	{
		
		/** 点卡卡号 */
		CSTR cardNo;

	} data;

} GetCardStorageRequest;

C_API GetCardStorageRequest *HSAPI_INIT(GetCardStorageRequest);

typedef struct GetCardStorageResponse 
{
	HsviewResponse base;

	struct GetCardStorageResponseData
	{
		
		/** 上传云存储的码流时段，alarm/always，分别表示报警时上传和全时段上传。 */
		CSTR streamInterval;
		/** [int]录像存储天数 */
		int recordStorageTimeLimit;
		/** [int]报警存储天数 */
		int alarmStorageTimeLimit;
		/** [bool]是否有服务期限，若有，则关注timeLimit字段 */
		BOOL hasTimeLimit;
		/** 费用 */
		CSTR fee;
		/** [long]云存储套餐ID */
		int64 strategyId;
		/** [int]云存储服务期限（天） */
		int timeLimit;
		/** [int]抓图最小间隔，单位秒 */
		int snapInterval;
		/** 套餐名称 */
		CSTR name;
 
	} data;

} GetCardStorageResponse;

C_API GetCardStorageResponse *HSAPI_INIT(GetCardStorageResponse);

#endif
