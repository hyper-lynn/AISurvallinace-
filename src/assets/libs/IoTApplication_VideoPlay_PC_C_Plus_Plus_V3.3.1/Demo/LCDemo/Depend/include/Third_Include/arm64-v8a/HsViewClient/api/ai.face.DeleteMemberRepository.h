/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_aiFace_DeleteMemberRepository_H_
#define _HSVIEW_CLIENT_API_aiFace_DeleteMemberRepository_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
解除人脸库与库成员关联关系

【用户平台鉴权】
 */

typedef struct aiFace_DeleteMemberRepositoryRequest 
{
	HsviewRequest base;

	struct aiFace_DeleteMemberRepositoryRequestData
	{
		
		/** 成员id */
		CSTR id;
		/** [int]成员所属的服务列表，0表示我的相册 */
		int repositoryType;

	} data;

} aiFace_DeleteMemberRepositoryRequest;

C_API aiFace_DeleteMemberRepositoryRequest *HSAPI_INIT(aiFace_DeleteMemberRepositoryRequest);

typedef struct aiFace_DeleteMemberRepositoryResponse 
{
	HsviewResponse base;

	struct aiFace_DeleteMemberRepositoryResponseData
	{
		
		/** 结果, success：表示成功，idNotExist：表示id不存在，badArgs：非法参数 */
		CSTR result;
 
	} data;

} aiFace_DeleteMemberRepositoryResponse;

C_API aiFace_DeleteMemberRepositoryResponse *HSAPI_INIT(aiFace_DeleteMemberRepositoryResponse);

#endif
