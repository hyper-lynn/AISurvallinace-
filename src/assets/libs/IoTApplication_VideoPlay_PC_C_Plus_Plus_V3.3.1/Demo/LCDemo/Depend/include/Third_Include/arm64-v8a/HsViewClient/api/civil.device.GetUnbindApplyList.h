/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetUnbindApplyList_H_
#define _HSVIEW_CLIENT_API_GetUnbindApplyList_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
status表示解绑状态（0：待后台审核；1：后台审核不通过；2：解绑成功）
【需要使用平台账号签名】
 */

typedef struct GetUnbindApplyListRequest 
{
	HsviewRequest base;

	struct GetUnbindApplyListRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} GetUnbindApplyListRequest;

C_API GetUnbindApplyListRequest *HSAPI_INIT(GetUnbindApplyListRequest);

typedef struct GetUnbindApplyListResponse 
{
	HsviewResponse base;

	struct GetUnbindApplyListResponseData
	{
		
		/** define a list with struct of GetUnbindApplyListResponseData_AppliesElement */
		DECLARE_LIST(struct GetUnbindApplyListResponseData_AppliesElement
		{
			/** [long]流程编号 */
			int64 applyId;
			/** [long]流程最近更新时间，UNIX时间戳（秒） */
			int64 updateTime;
			/** [int]流程状态 */
			int status;
			/** [long]流程发起时间，UNIX时间戳（秒） */
			int64 startTime;
			/** 设备编号 */
			CSTR deviceCode;
		}) applies;
 
	} data;

} GetUnbindApplyListResponse;

C_API GetUnbindApplyListResponse *HSAPI_INIT(GetUnbindApplyListResponse);

#endif
