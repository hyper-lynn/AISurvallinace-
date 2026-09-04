/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_userPush_SetPushOpenInfo_H_
#define _HSVIEW_CLIENT_API_userPush_SetPushOpenInfo_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
用于开放平台添加删除开发者信息。
 */

typedef struct userPush_SetPushOpenInfoRequest 
{
	HsviewRequest base;

	struct userPush_SetPushOpenInfoRequestData
	{
		
		/** 表示操作类型,add:添加信息, delete:删除信息 */
		CSTR type;

	} data;

} userPush_SetPushOpenInfoRequest;

C_API userPush_SetPushOpenInfoRequest *HSAPI_INIT(userPush_SetPushOpenInfoRequest);

typedef struct userPush_SetPushOpenInfoResponse 
{
	HsviewResponse base;

	struct userPush_SetPushOpenInfoResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} userPush_SetPushOpenInfoResponse;

C_API userPush_SetPushOpenInfoResponse *HSAPI_INIT(userPush_SetPushOpenInfoResponse);

#endif
