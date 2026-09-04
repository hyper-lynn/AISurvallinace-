/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_SetEncryptMode_H_
#define _HSVIEW_CLIENT_API_SetEncryptMode_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
视频加密模式只能对设备设置，不能对通道设置。

请求参数含义如下：

Mode：视频加密模式，0表示默认加密模式（即使用设备序列号作为密码），1表示用户加密模式（即用户自行设置密码）

Password：仅在Mode为1时有效，表示用户设置的密码的Base64值。

【需要使用平台账号签名】
 */

typedef struct SetEncryptModeRequest 
{
	HsviewRequest base;

	struct SetEncryptModeRequestData
	{
		
		/** 设备ID */
		CSTR devId;
		/** 通道号 */
		CSTR optional;
		/** [cstr]POST */
		#define _STATIC_SetEncryptModeRequestData_METHOD "POST"
		/** [cstr]encrypt-mode */
		#define _STATIC_SetEncryptModeRequestData_CMD "encrypt-mode"
		/** struct of SetEncryptModeRequestData_Body */
		struct SetEncryptModeRequestData_Body {
			/** 用户自定义秘钥的base64编码后的值 */
			CSTR Password;
			/** [int]加密模式：0-默认加密  1-用户自定义加密 */
			int Mode;
		} body;

	} data;

} SetEncryptModeRequest;

C_API SetEncryptModeRequest *HSAPI_INIT(SetEncryptModeRequest);

typedef struct SetEncryptModeResponse 
{
	HsviewResponse base;

	struct SetEncryptModeResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} SetEncryptModeResponse;

C_API SetEncryptModeResponse *HSAPI_INIT(SetEncryptModeResponse);

#endif
