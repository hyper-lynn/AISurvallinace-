/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 223121, Author: 233705, Date: 2022-08-10 09:10:06 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_getTemporaryPasswordList_H_
#define _LC_OPENAPI_CLIENT_getTemporaryPasswordList_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取临时秘钥列表
 */

typedef struct getTemporaryPasswordListRequest 
{
	LCOpenApiRequest base;

	struct getTemporaryPasswordListRequestData
	{
		
		/** 通道号 */
		CSTR channelId;
		/**  */
		CSTR token;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} getTemporaryPasswordListRequest;

C_API getTemporaryPasswordListRequest *LCOPENAPI_INIT(getTemporaryPasswordListRequest);

typedef struct getTemporaryPasswordListResponse 
{
	LCOpenApiResponse base;

	struct getTemporaryPasswordListResponseData
	{
		
		/** define a list with struct of getTemporaryPasswordListResponseData_TemporarypasswordElement */
		DECLARE_LIST(struct getTemporaryPasswordListResponseData_TemporarypasswordElement
		{
			/** [int]可选，有效次数，-1表示不限制次数；无此字段默认无限次 */
			int effectCount;
			/** 开始时间 yyyyMMddTHHmmss */
			CSTR beginTime;
			/** 结束时间 yyyyMMddTHHmmss */
			CSTR endTime;
			/** 临时秘钥 */
			CSTR password;
		}) temporarypassword;
		/** [int]设备支持临时密码最多个数 */
		int maxNumber;
		/** [int]可选，通道编号；不填默认设备 */
		int chan;
 
	} data;

} getTemporaryPasswordListResponse;

C_API getTemporaryPasswordListResponse *LCOPENAPI_INIT(getTemporaryPasswordListResponse);

#endif
