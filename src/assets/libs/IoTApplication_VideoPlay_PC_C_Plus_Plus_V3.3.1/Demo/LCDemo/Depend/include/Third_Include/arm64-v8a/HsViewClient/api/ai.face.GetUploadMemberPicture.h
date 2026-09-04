/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_aiFace_GetUploadMemberPicture_H_
#define _HSVIEW_CLIENT_API_aiFace_GetUploadMemberPicture_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
开始上传库成员图片

【用户平台鉴权】
 */

typedef struct aiFace_GetUploadMemberPictureRequest 
{
	HsviewRequest base;

	struct aiFace_GetUploadMemberPictureRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} aiFace_GetUploadMemberPictureRequest;

C_API aiFace_GetUploadMemberPictureRequest *HSAPI_INIT(aiFace_GetUploadMemberPictureRequest);

typedef struct aiFace_GetUploadMemberPictureResponse 
{
	HsviewResponse base;

	struct aiFace_GetUploadMemberPictureResponseData
	{
		
		/** 本次操作的token信息 */
		CSTR token;
		/** 用户上传图片的地址 */
		CSTR uploadAddr;
 
	} data;

} aiFace_GetUploadMemberPictureResponse;

C_API aiFace_GetUploadMemberPictureResponse *HSAPI_INIT(aiFace_GetUploadMemberPictureResponse);

#endif
