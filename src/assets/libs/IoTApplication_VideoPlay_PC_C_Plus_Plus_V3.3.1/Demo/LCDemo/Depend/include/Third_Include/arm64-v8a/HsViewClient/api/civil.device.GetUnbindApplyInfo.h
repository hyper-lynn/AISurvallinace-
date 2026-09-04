/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetUnbindApplyInfo_H_
#define _HSVIEW_CLIENT_API_GetUnbindApplyInfo_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
status表示解绑状态（0：待解绑审核；1：后台审核不通过；2：解绑成功）
statusList表示状态列表，排序为按时间逆序；
time表示流程创建时间；
isExpired的值为字符串型的"true"或者"false"
【需要使用平台账号签名】
 */

typedef struct GetUnbindApplyInfoRequest 
{
	HsviewRequest base;

	struct GetUnbindApplyInfoRequestData
	{
		
		/** [long]解绑流程编号 */
		int64 applyId;

	} data;

} GetUnbindApplyInfoRequest;

C_API GetUnbindApplyInfoRequest *HSAPI_INIT(GetUnbindApplyInfoRequest);

typedef struct GetUnbindApplyInfoResponse 
{
	HsviewResponse base;

	struct GetUnbindApplyInfoResponseData
	{
		
		/** define a list with struct of GetUnbindApplyInfoResponseData_StatusListElement */
		DECLARE_LIST(struct GetUnbindApplyInfoResponseData_StatusListElement
		{
			/** [int]流程状态 */
			int status;
			/** [long]流程创建时间，UNIX时间戳（秒） */
			int64 time;
			/** 状态说明 */
			CSTR explain;
		}) statusList;
		/** 设备编号 */
		CSTR deviceCode;
		/** [O]申请是否过期(超过一年认为过期),true:已过期，false:未过期 */
		CSTR isExpired;
 
	} data;

} GetUnbindApplyInfoResponse;

C_API GetUnbindApplyInfoResponse *HSAPI_INIT(GetUnbindApplyInfoResponse);

#endif
