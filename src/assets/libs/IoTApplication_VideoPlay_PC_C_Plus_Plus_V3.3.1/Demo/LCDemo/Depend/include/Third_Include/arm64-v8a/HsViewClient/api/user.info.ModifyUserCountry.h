/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_userInfo_ModifyUserCountry_H_
#define _HSVIEW_CLIENT_API_userInfo_ModifyUserCountry_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取这个用户自己的账号信息。


【使用平台账号签名】
 */

typedef struct userInfo_ModifyUserCountryRequest 
{
	HsviewRequest base;

	struct userInfo_ModifyUserCountryRequestData
	{
		
		/** 用户国家信息（使用iso-3166-1二字母，eg. 中国对应'CN'） */
		CSTR country;

	} data;

} userInfo_ModifyUserCountryRequest;

C_API userInfo_ModifyUserCountryRequest *HSAPI_INIT(userInfo_ModifyUserCountryRequest);

typedef struct userInfo_ModifyUserCountryResponse 
{
	HsviewResponse base;

	struct userInfo_ModifyUserCountryResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} userInfo_ModifyUserCountryResponse;

C_API userInfo_ModifyUserCountryResponse *HSAPI_INIT(userInfo_ModifyUserCountryResponse);

#endif
