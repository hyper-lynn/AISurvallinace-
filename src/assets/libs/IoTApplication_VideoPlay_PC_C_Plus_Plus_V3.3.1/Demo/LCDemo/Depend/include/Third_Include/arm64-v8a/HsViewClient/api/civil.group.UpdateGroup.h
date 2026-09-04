/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_UpdateGroup_H_
#define _HSVIEW_CLIENT_API_UpdateGroup_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
 用户修改分组名称

【需要使用平台账号签名】

 */

typedef struct UpdateGroupRequest 
{
	HsviewRequest base;

	struct UpdateGroupRequestData
	{
		
		/** [long]父分组Id, 不存在或者为-1表示没有父分组,创建一个顶层的设备分组 */
		int64 parentGroupId;
		/** 分组名称 */
		CSTR groupName;
		/** [long]分组id */
		int64 groupId;

	} data;

} UpdateGroupRequest;

C_API UpdateGroupRequest *HSAPI_INIT(UpdateGroupRequest);

typedef struct UpdateGroupResponse 
{
	HsviewResponse base;

	struct UpdateGroupResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} UpdateGroupResponse;

C_API UpdateGroupResponse *HSAPI_INIT(UpdateGroupResponse);

#endif
