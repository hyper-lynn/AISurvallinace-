/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_userFace_AddFamilyFace_H_
#define _HSVIEW_CLIENT_API_userFace_AddFamilyFace_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
上传用户家庭成员的照片

错误码：13600（人脸的数目超标）

【用户平台鉴权】
 */

typedef struct userFace_AddFamilyFaceRequest 
{
	HsviewRequest base;

	struct userFace_AddFamilyFaceRequestData
	{
		
		/** 家庭成员名字 */
		CSTR name;
		/** 图片二进制数据的base64编码字符串 */
		CSTR pic;

	} data;

} userFace_AddFamilyFaceRequest;

C_API userFace_AddFamilyFaceRequest *HSAPI_INIT(userFace_AddFamilyFaceRequest);

typedef struct userFace_AddFamilyFaceResponse 
{
	HsviewResponse base;

	struct userFace_AddFamilyFaceResponseData
	{
		
		/** 图片id */
		CSTR fid;
 
	} data;

} userFace_AddFamilyFaceResponse;

C_API userFace_AddFamilyFaceResponse *HSAPI_INIT(userFace_AddFamilyFaceResponse);

#endif
