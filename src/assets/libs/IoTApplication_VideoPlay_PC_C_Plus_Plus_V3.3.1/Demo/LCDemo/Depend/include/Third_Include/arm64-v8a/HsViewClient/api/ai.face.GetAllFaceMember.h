/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_aiFace_GetAllFaceMember_H_
#define _HSVIEW_CLIENT_API_aiFace_GetAllFaceMember_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取家庭成员列表

【用户平台鉴权】
 */

typedef struct aiFace_GetAllFaceMemberRequest 
{
	HsviewRequest base;

	struct aiFace_GetAllFaceMemberRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} aiFace_GetAllFaceMemberRequest;

C_API aiFace_GetAllFaceMemberRequest *HSAPI_INIT(aiFace_GetAllFaceMemberRequest);

typedef struct aiFace_GetAllFaceMemberResponse 
{
	HsviewResponse base;

	struct aiFace_GetAllFaceMemberResponseData
	{
		
		/** define a list with struct of aiFace_GetAllFaceMemberResponseData_MemberListElement */
		DECLARE_LIST(struct aiFace_GetAllFaceMemberResponseData_MemberListElement
		{
			/** [int]成员所属的服务列表，0表示时光相册 */
			DECLARE_LIST(int) repositoryTypeList;
			/** 图片下载地址 */
			CSTR downloadUrl;
			/** 成员名称,最长128字节 */
			CSTR name;
			/** [long]成员id */
			int64 memberId;
		}) memberList;
 
	} data;

} aiFace_GetAllFaceMemberResponse;

C_API aiFace_GetAllFaceMemberResponse *HSAPI_INIT(aiFace_GetAllFaceMemberResponse);

#endif
