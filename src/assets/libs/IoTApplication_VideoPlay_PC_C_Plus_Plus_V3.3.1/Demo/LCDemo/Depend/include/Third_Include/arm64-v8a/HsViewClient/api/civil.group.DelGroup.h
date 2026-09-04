/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_DelGroup_H_
#define _HSVIEW_CLIENT_API_DelGroup_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
 用户删除分组，删除分组时会同步删除该分组下面的所有子分组和设备

【需要使用平台账号签名】

 */

typedef struct DelGroupRequest 
{
	HsviewRequest base;

	struct DelGroupRequestData
	{
		
		/** [long]分组id */
		int64 groupId;

	} data;

} DelGroupRequest;

C_API DelGroupRequest *HSAPI_INIT(DelGroupRequest);

typedef struct DelGroupResponse 
{
	HsviewResponse base;

	struct DelGroupResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} DelGroupResponse;

C_API DelGroupResponse *HSAPI_INIT(DelGroupResponse);

#endif
