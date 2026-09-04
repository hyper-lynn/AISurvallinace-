/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 223121, Author: 233705, Date: 2022-08-10 09:10:06 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_setTemporaryPasswordConfig_H_
#define _LC_OPENAPI_CLIENT_setTemporaryPasswordConfig_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
设置临时秘钥
 */

typedef struct setTemporaryPasswordConfigRequest 
{
	LCOpenApiRequest base;

	struct setTemporaryPasswordConfigRequestData
	{
		
		/** define a list with struct of setTemporaryPasswordConfigRequestData_TemporarypasswordElement */
		DECLARE_LIST(struct setTemporaryPasswordConfigRequestData_TemporarypasswordElement
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
		/** 通道号 */
		CSTR channelId;
		/**  */
		CSTR token;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} setTemporaryPasswordConfigRequest;

C_API setTemporaryPasswordConfigRequest *LCOPENAPI_INIT(setTemporaryPasswordConfigRequest);

typedef struct setTemporaryPasswordConfigResponse 
{
	LCOpenApiResponse base;

	struct setTemporaryPasswordConfigResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} setTemporaryPasswordConfigResponse;

C_API setTemporaryPasswordConfigResponse *LCOPENAPI_INIT(setTemporaryPasswordConfigResponse);

#endif
