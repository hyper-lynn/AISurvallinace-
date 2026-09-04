/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetSubGroupListByPage_H_
#define _HSVIEW_CLIENT_API_GetSubGroupListByPage_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 

分页获取该分组下面的子分组。
  
【需要使用平台账号签名】

 */

typedef struct GetSubGroupListByPageRequest 
{
	HsviewRequest base;

	struct GetSubGroupListByPageRequestData
	{
		
		/** 分页获取,从第几条到第几条，如“1-50”,闭区间,最多一次查询50条 */
		CSTR need;
		/** [long]设备分组的id */
		int64 groupId;

	} data;

} GetSubGroupListByPageRequest;

C_API GetSubGroupListByPageRequest *HSAPI_INIT(GetSubGroupListByPageRequest);

typedef struct GetSubGroupListByPageResponse 
{
	HsviewResponse base;

	struct GetSubGroupListByPageResponseData
	{
		
		/** define a list with struct of GetSubGroupListByPageResponseData_GroupsElement */
		DECLARE_LIST(struct GetSubGroupListByPageResponseData_GroupsElement
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

} GetSubGroupListByPageResponse;

C_API GetSubGroupListByPageResponse *HSAPI_INIT(GetSubGroupListByPageResponse);

#endif
