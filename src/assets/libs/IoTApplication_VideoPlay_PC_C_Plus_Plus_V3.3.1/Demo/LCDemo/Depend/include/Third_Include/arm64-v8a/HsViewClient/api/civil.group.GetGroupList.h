/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetGroupList_H_
#define _HSVIEW_CLIENT_API_GetGroupList_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
 获取用户的分组列表(最顶层的分组)

【需要使用平台账号签名】

 */

typedef struct GetGroupListRequest 
{
	HsviewRequest base;

	struct GetGroupListRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} GetGroupListRequest;

C_API GetGroupListRequest *HSAPI_INIT(GetGroupListRequest);

typedef struct GetGroupListResponse 
{
	HsviewResponse base;

	struct GetGroupListResponseData
	{
		
		/** define a list with struct of GetGroupListResponseData_GroupsElement */
		DECLARE_LIST(struct GetGroupListResponseData_GroupsElement
		{
			/** 分组的封面，为空代表使用默认封面 */
			CSTR cover;
			/** [long]分组的最后修改unix时间戳，精确到秒 */
			int64 ts;
			/** 分组名称 */
			CSTR groupName;
			/** [long]分组id */
			int64 groupId;
		}) groups;
 
	} data;

} GetGroupListResponse;

C_API GetGroupListResponse *HSAPI_INIT(GetGroupListResponse);

#endif
