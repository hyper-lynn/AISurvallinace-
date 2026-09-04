/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_userFace_ClearUpFamilyFaces_H_
#define _HSVIEW_CLIENT_API_userFace_ClearUpFamilyFaces_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
清空用户家庭成员头像

【用户平台鉴权】
 */

typedef struct userFace_ClearUpFamilyFacesRequest 
{
	HsviewRequest base;

	struct userFace_ClearUpFamilyFacesRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} userFace_ClearUpFamilyFacesRequest;

C_API userFace_ClearUpFamilyFacesRequest *HSAPI_INIT(userFace_ClearUpFamilyFacesRequest);

typedef struct userFace_ClearUpFamilyFacesResponse 
{
	HsviewResponse base;

	struct userFace_ClearUpFamilyFacesResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} userFace_ClearUpFamilyFacesResponse;

C_API userFace_ClearUpFamilyFacesResponse *HSAPI_INIT(userFace_ClearUpFamilyFacesResponse);

#endif
