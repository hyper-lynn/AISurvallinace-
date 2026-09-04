/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetThirdpartyAccountList_H_
#define _HSVIEW_CLIENT_API_GetThirdpartyAccountList_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取当前账号下绑定的第三方账号列表。
【使用平台账号签名】
 */

typedef struct GetThirdpartyAccountListRequest 
{
	HsviewRequest base;

	struct GetThirdpartyAccountListRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} GetThirdpartyAccountListRequest;

C_API GetThirdpartyAccountListRequest *HSAPI_INIT(GetThirdpartyAccountListRequest);

typedef struct GetThirdpartyAccountListResponse 
{
	HsviewResponse base;

	struct GetThirdpartyAccountListResponseData
	{
		
		/** define a list with struct of GetThirdpartyAccountListResponseData_ThirdpartyAccountsElement */
		DECLARE_LIST(struct GetThirdpartyAccountListResponseData_ThirdpartyAccountsElement
		{
			/** [long]第三方账号唯一标识ID */
			int64 id;
			/** 第三方账号类型 */
			CSTR type;
			/** 第三方账号用户名 */
			CSTR accountName;
			/** 第三方账号ID */
			CSTR accountId;
		}) thirdpartyAccounts;
 
	} data;

} GetThirdpartyAccountListResponse;

C_API GetThirdpartyAccountListResponse *HSAPI_INIT(GetThirdpartyAccountListResponse);

#endif
