/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_UnbindThirdpartyAccount_H_
#define _HSVIEW_CLIENT_API_UnbindThirdpartyAccount_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
取消第三方账号的绑定。可以同时取消多个，传入数组表示。
【使用平台账号签名】
 */

typedef struct UnbindThirdpartyAccountRequest 
{
	HsviewRequest base;

	struct UnbindThirdpartyAccountRequestData
	{
		
		/** [long]需要删除的第三方账号ID（从获取绑定的第三方账号列表中得到）数组 */
		DECLARE_LIST(int64) thirdpartyAccountIds;

	} data;

} UnbindThirdpartyAccountRequest;

C_API UnbindThirdpartyAccountRequest *HSAPI_INIT(UnbindThirdpartyAccountRequest);

typedef struct UnbindThirdpartyAccountResponse 
{
	HsviewResponse base;

	struct UnbindThirdpartyAccountResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} UnbindThirdpartyAccountResponse;

C_API UnbindThirdpartyAccountResponse *HSAPI_INIT(UnbindThirdpartyAccountResponse);

#endif
