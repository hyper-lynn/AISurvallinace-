/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_aiFace_CreateMemberRepositoryById_H_
#define _HSVIEW_CLIENT_API_aiFace_CreateMemberRepositoryById_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
绑定人脸库与库成员关联关系

【用户平台鉴权】
 */

typedef struct aiFace_CreateMemberRepositoryByIdRequest 
{
	HsviewRequest base;

	struct aiFace_CreateMemberRepositoryByIdRequestData
	{
		
		/** 成员id */
		CSTR id;
		/** [int]成员所属的服务类型，0表示我的相册 */
		int repositoryType;

	} data;

} aiFace_CreateMemberRepositoryByIdRequest;

C_API aiFace_CreateMemberRepositoryByIdRequest *HSAPI_INIT(aiFace_CreateMemberRepositoryByIdRequest);

typedef struct aiFace_CreateMemberRepositoryByIdResponse 
{
	HsviewResponse base;

	struct aiFace_CreateMemberRepositoryByIdResponseData
	{
		
		/** 结果, success：表示成功，idNotExist：表示id不存在，badArgs：非法参数 */
		CSTR result;
 
	} data;

} aiFace_CreateMemberRepositoryByIdResponse;

C_API aiFace_CreateMemberRepositoryByIdResponse *HSAPI_INIT(aiFace_CreateMemberRepositoryByIdResponse);

#endif
