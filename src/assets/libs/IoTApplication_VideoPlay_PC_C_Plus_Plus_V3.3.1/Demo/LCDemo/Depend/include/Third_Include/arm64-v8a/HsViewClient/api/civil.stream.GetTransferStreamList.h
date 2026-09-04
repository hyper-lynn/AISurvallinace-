/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetTransferStreamList_H_
#define _HSVIEW_CLIENT_API_GetTransferStreamList_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 

获取该用户是否有拉流的VIP协议。
"num"表示[int]个数，没有就是0，有就返回个数

【使用平台账号签名】

 */

typedef struct GetTransferStreamListRequest 
{
	HsviewRequest base;

	struct GetTransferStreamListRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} GetTransferStreamListRequest;

C_API GetTransferStreamListRequest *HSAPI_INIT(GetTransferStreamListRequest);

typedef struct GetTransferStreamListResponse 
{
	HsviewResponse base;

	struct GetTransferStreamListResponseData
	{
		
		/** [int]个数，没有就是0，有就返回个数 */
		int num;
 
	} data;

} GetTransferStreamListResponse;

C_API GetTransferStreamListResponse *HSAPI_INIT(GetTransferStreamListResponse);

#endif
