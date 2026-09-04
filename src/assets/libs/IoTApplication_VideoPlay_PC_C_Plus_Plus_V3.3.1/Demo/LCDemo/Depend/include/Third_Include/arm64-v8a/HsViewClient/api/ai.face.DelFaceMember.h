/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_aiFace_DelFaceMember_H_
#define _HSVIEW_CLIENT_API_aiFace_DelFaceMember_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
删除家庭成员

【用户平台鉴权】
 */

typedef struct aiFace_DelFaceMemberRequest 
{
	HsviewRequest base;

	struct aiFace_DelFaceMemberRequestData
	{
		
		/** [long]成员id */
		int64 memberId;

	} data;

} aiFace_DelFaceMemberRequest;

C_API aiFace_DelFaceMemberRequest *HSAPI_INIT(aiFace_DelFaceMemberRequest);

typedef struct aiFace_DelFaceMemberResponse 
{
	HsviewResponse base;

	struct aiFace_DelFaceMemberResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} aiFace_DelFaceMemberResponse;

C_API aiFace_DelFaceMemberResponse *HSAPI_INIT(aiFace_DelFaceMemberResponse);

#endif
