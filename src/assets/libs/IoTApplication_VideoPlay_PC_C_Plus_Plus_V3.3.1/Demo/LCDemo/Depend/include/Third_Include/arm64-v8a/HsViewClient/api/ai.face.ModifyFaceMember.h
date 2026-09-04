/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_aiFace_ModifyFaceMember_H_
#define _HSVIEW_CLIENT_API_aiFace_ModifyFaceMember_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
修改家庭成员信息

【用户平台鉴权】
 */

typedef struct aiFace_ModifyFaceMemberRequest 
{
	HsviewRequest base;

	struct aiFace_ModifyFaceMemberRequestData
	{
		
		/** 成员名称,最长20个字符（1个汉字两个字符） */
		CSTR name;
		/** [long]成员id */
		int64 memberId;

	} data;

} aiFace_ModifyFaceMemberRequest;

C_API aiFace_ModifyFaceMemberRequest *HSAPI_INIT(aiFace_ModifyFaceMemberRequest);

typedef struct aiFace_ModifyFaceMemberResponse 
{
	HsviewResponse base;

	struct aiFace_ModifyFaceMemberResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} aiFace_ModifyFaceMemberResponse;

C_API aiFace_ModifyFaceMemberResponse *HSAPI_INIT(aiFace_ModifyFaceMemberResponse);

#endif
