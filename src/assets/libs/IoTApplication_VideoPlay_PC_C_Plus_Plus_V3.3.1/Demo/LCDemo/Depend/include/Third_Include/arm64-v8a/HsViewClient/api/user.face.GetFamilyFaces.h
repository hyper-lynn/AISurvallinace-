/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_userFace_GetFamilyFaces_H_
#define _HSVIEW_CLIENT_API_userFace_GetFamilyFaces_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取家庭成员脸谱信息。

【用户平台鉴权】
 */

typedef struct userFace_GetFamilyFacesRequest 
{
	HsviewRequest base;

	struct userFace_GetFamilyFacesRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} userFace_GetFamilyFacesRequest;

C_API userFace_GetFamilyFacesRequest *HSAPI_INIT(userFace_GetFamilyFacesRequest);

typedef struct userFace_GetFamilyFacesResponse 
{
	HsviewResponse base;

	struct userFace_GetFamilyFacesResponseData
	{
		
		/** define a list with struct of userFace_GetFamilyFacesResponseData_FacesElement */
		DECLARE_LIST(struct userFace_GetFamilyFacesResponseData_FacesElement
		{
			/** 图片id */
			CSTR fid;
			/** 家庭成员名称 */
			CSTR name;
			/** 人脸图片的url */
			CSTR faceUrl;
		}) faces;
		/** [int]人脸的限制数目 */
		int limitNum;
 
	} data;

} userFace_GetFamilyFacesResponse;

C_API userFace_GetFamilyFacesResponse *HSAPI_INIT(userFace_GetFamilyFacesResponse);

#endif
