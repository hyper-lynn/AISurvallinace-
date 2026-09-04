/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_userFace_DeleteFamilyFace_H_
#define _HSVIEW_CLIENT_API_userFace_DeleteFamilyFace_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
删除用户家庭成员脸谱信息

12101：用户没有操作脸谱的权限

【默认AK、SK鉴权】
 */

typedef struct userFace_DeleteFamilyFaceRequest 
{
	HsviewRequest base;

	struct userFace_DeleteFamilyFaceRequestData
	{
		
		/** 图片的id */
		CSTR fid;

	} data;

} userFace_DeleteFamilyFaceRequest;

C_API userFace_DeleteFamilyFaceRequest *HSAPI_INIT(userFace_DeleteFamilyFaceRequest);

typedef struct userFace_DeleteFamilyFaceResponse 
{
	HsviewResponse base;

	struct userFace_DeleteFamilyFaceResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} userFace_DeleteFamilyFaceResponse;

C_API userFace_DeleteFamilyFaceResponse *HSAPI_INIT(userFace_DeleteFamilyFaceResponse);

#endif
