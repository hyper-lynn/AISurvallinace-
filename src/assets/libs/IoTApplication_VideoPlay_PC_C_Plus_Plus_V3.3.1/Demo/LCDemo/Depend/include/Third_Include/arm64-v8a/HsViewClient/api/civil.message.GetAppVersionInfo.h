/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetAppVersionInfo_H_
#define _HSVIEW_CLIENT_API_GetAppVersionInfo_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取app版本信息，给手机用。
【无需签名认证】
 */

typedef struct GetAppVersionInfoRequest 
{
	HsviewRequest base;

	struct GetAppVersionInfoRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} GetAppVersionInfoRequest;

C_API GetAppVersionInfoRequest *HSAPI_INIT(GetAppVersionInfoRequest);

typedef struct GetAppVersionInfoResponse 
{
	HsviewResponse base;

	struct GetAppVersionInfoResponseData
	{
		
		/** struct of GetAppVersionInfoResponseData_Android */
		struct GetAppVersionInfoResponseData_Android {
			/** 最新版本 */
			CSTR lastVersion;
			/** 最新版本的下载地址 */
			CSTR apkUrl;
			/** 基础版本（最低要求版本） */
			CSTR baseVersion;
			/** 最新版本的更新信息 */
			CSTR updateInfo;
		} android;
		/** struct of GetAppVersionInfoResponseData_Ios */
		struct GetAppVersionInfoResponseData_Ios {
			/** 最新版本 */
			CSTR lastVersion;
			/** 最新版本的下载地址 */
			CSTR apkUrl;
			/** 基础版本（最低要求版本） */
			CSTR baseVersion;
			/** 最新版本的更新信息 */
			CSTR updateInfo;
		} ios;
 
	} data;

} GetAppVersionInfoResponse;

C_API GetAppVersionInfoResponse *HSAPI_INIT(GetAppVersionInfoResponse);

#endif
