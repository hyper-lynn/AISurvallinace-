/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_aiFace_CreateFaceMember_H_
#define _HSVIEW_CLIENT_API_aiFace_CreateFaceMember_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
添加家庭成员

【用户平台鉴权】
 */

typedef struct aiFace_CreateFaceMemberRequest 
{
	HsviewRequest base;

	struct aiFace_CreateFaceMemberRequestData
	{
		
		/** 成员名称,最长128字节 */
		CSTR name;
		/** struct of aiFace_CreateFaceMemberRequestData_FacePicture */
		struct aiFace_CreateFaceMemberRequestData_FacePicture {
			/** 云存储区域 */
			CSTR region;
			/** 库成员源图路径 */
			CSTR url;
		} facePicture;

	} data;

} aiFace_CreateFaceMemberRequest;

C_API aiFace_CreateFaceMemberRequest *HSAPI_INIT(aiFace_CreateFaceMemberRequest);

typedef struct aiFace_CreateFaceMemberResponse 
{
	HsviewResponse base;

	struct aiFace_CreateFaceMemberResponseData
	{
		
		/** 结果, success：表示成功，nameAlreadyExist：表示重名，badArgs：非法参数 */
		CSTR result;
		/** [O]成员id，当result为success时有效 */
		CSTR id;
 
	} data;

} aiFace_CreateFaceMemberResponse;

C_API aiFace_CreateFaceMemberResponse *HSAPI_INIT(aiFace_CreateFaceMemberResponse);

#endif
