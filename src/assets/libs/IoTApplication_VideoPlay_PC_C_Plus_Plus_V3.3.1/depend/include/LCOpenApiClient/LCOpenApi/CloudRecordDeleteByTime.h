/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_CloudRecordDeleteByTime_H_
#define _LC_OPENAPI_CLIENT_CloudRecordDeleteByTime_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
删除某个设备一段时间内的录像，返回被删除的录像数
 */

typedef struct CloudRecordDeleteByTimeRequest 
{
	LCOpenApiRequest base;

	struct CloudRecordDeleteByTimeRequestData
	{
		
		/** 录像类型，为空表示不区分录像类型 */
		CSTR type;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备本地结束时间,yyyyMMddTHHmmss格式 */
		CSTR localEndTime;
		/** 通道号 */
		CSTR channelId;
		/** 设备本地开始时间,yyyyMMddTHHmmss格式 */
		CSTR localBeginTime;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} CloudRecordDeleteByTimeRequest;

C_API CloudRecordDeleteByTimeRequest *LCOPENAPI_INIT(CloudRecordDeleteByTimeRequest);

typedef struct CloudRecordDeleteByTimeResponse 
{
	LCOpenApiResponse base;

	struct CloudRecordDeleteByTimeResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} CloudRecordDeleteByTimeResponse;

C_API CloudRecordDeleteByTimeResponse *LCOPENAPI_INIT(CloudRecordDeleteByTimeResponse);

#endif
