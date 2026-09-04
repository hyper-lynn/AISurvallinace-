/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_userAccount_GetLoginHistory_H_
#define _HSVIEW_CLIENT_API_userAccount_GetLoginHistory_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取用户前几次登陆的信息（返回数组）：
【使用平台账号签名】
 */

typedef struct userAccount_GetLoginHistoryRequest 
{
	HsviewRequest base;

	struct userAccount_GetLoginHistoryRequestData
	{
		
		/** [int]需要获取的记录条数 */
		int count;

	} data;

} userAccount_GetLoginHistoryRequest;

C_API userAccount_GetLoginHistoryRequest *HSAPI_INIT(userAccount_GetLoginHistoryRequest);

typedef struct userAccount_GetLoginHistoryResponse 
{
	HsviewResponse base;

	struct userAccount_GetLoginHistoryResponseData
	{
		
		/** define a list with struct of userAccount_GetLoginHistoryResponseData_RecordsElement */
		DECLARE_LIST(struct userAccount_GetLoginHistoryResponseData_RecordsElement
		{
			/** 终端型号 */
			CSTR terminalModel;
			/** 登陆时间,yyyyMMddTHHmmssZ格式(UTC时间) */
			CSTR loginTime;
		}) records;
 
	} data;

} userAccount_GetLoginHistoryResponse;

C_API userAccount_GetLoginHistoryResponse *HSAPI_INIT(userAccount_GetLoginHistoryResponse);

#endif
