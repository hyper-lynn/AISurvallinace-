/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_userAccount_ExportAccountInfo_H_
#define _HSVIEW_CLIENT_API_userAccount_ExportAccountInfo_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
账号信息导出
目前仅支持邮箱
【使用平台账号签名】
 */

typedef struct userAccount_ExportAccountInfoRequest 
{
	HsviewRequest base;

	struct userAccount_ExportAccountInfoRequestData
	{
		
		/** 验证码，如123456 */
		CSTR validCode;
		/** 帐号类型, email */
		CSTR type;
		/** 帐号（目前仅支持邮箱） */
		CSTR account;

	} data;

} userAccount_ExportAccountInfoRequest;

C_API userAccount_ExportAccountInfoRequest *HSAPI_INIT(userAccount_ExportAccountInfoRequest);

typedef struct userAccount_ExportAccountInfoResponse 
{
	HsviewResponse base;

	struct userAccount_ExportAccountInfoResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} userAccount_ExportAccountInfoResponse;

C_API userAccount_ExportAccountInfoResponse *HSAPI_INIT(userAccount_ExportAccountInfoResponse);

#endif
