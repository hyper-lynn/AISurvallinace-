/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_AddGroup_H_
#define _HSVIEW_CLIENT_API_AddGroup_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
 用户添加分组，添加成功后返回该分组的id

【需要使用平台账号签名】

 */

typedef struct AddGroupRequest 
{
	HsviewRequest base;

	struct AddGroupRequestData
	{
		
		/** 分组名称 */
		CSTR groupName;
		/** [long]父分组Id, 不存在或者为-1表示没有父分组,创建一个顶层的设备分组 */
		int64 parentGroupId;

	} data;

} AddGroupRequest;

C_API AddGroupRequest *HSAPI_INIT(AddGroupRequest);

typedef struct AddGroupResponse 
{
	HsviewResponse base;

	struct AddGroupResponseData
	{
		
		/** [long]分组id */
		int64 groupId;
 
	} data;

} AddGroupResponse;

C_API AddGroupResponse *HSAPI_INIT(AddGroupResponse);

#endif
