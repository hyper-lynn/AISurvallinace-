/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_CheckDeviceVerifyCode_H_
#define _HSVIEW_CLIENT_API_CheckDeviceVerifyCode_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 

检查设备验证码是否正确
	
【需要使用平台账号签名】

 */

typedef struct CheckDeviceVerifyCodeRequest 
{
	HsviewRequest base;

	struct CheckDeviceVerifyCodeRequestData
	{
		
		/** 设备的校验码 */
		CSTR code;
		/** 设备ID */
		CSTR deviceId;

	} data;

} CheckDeviceVerifyCodeRequest;

C_API CheckDeviceVerifyCodeRequest *HSAPI_INIT(CheckDeviceVerifyCodeRequest);

typedef struct CheckDeviceVerifyCodeResponse 
{
	HsviewResponse base;

	struct CheckDeviceVerifyCodeResponseData
	{
		
		/** [bool]验证码是否正确 */
		BOOL flag;
 
	} data;

} CheckDeviceVerifyCodeResponse;

C_API CheckDeviceVerifyCodeResponse *HSAPI_INIT(CheckDeviceVerifyCodeResponse);

#endif
