/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_AddUnbindApply_H_
#define _HSVIEW_CLIENT_API_AddUnbindApply_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
applicant是申请人姓名。
phoneNum是申请人手机号。
deviceId是需要解绑的设备ID。
devicePicUrl是设备机身标签照片URL地址。
idFrontPicUrl是身份证正面照片URL地址。
idBackPicUrl是身份证反面照片URL地址。
signPicUrl是保证书照片URL地址。

如果：
	该申请解绑设备未注册到平台，返回错误码：1301；
	该申请解绑设备未被绑定，返回错误码：1305；
	该申请解绑设备已经在申请人的名下，返回错误码：1303；
	该申请解绑设备被绑定的账号不是乐橙账号，返回错误码：1328
	
错误的返回格式为 {"code":1303,"desc":"DEVICE_ADDBYYOURSELF","data":{}}
【需要使用平台账号签名】
 */

typedef struct AddUnbindApplyRequest 
{
	HsviewRequest base;

	struct AddUnbindApplyRequestData
	{
		
		/** 设备机身标签照片URL地址 */
		CSTR devicePicUrl;
		/** 申请人姓名 */
		CSTR applicant;
		/** 保证书照片URL地址 */
		CSTR signPicUrl;
		/** 设备序列号 */
		CSTR deviceCode;
		/** 身份证正面照片URL地址 */
		CSTR idFrontPicUrl;
		/** 身份证反面照片URL地址 */
		CSTR idBackPicUrl;
		/** 申请人手机号 */
		CSTR phoneNum;

	} data;

} AddUnbindApplyRequest;

C_API AddUnbindApplyRequest *HSAPI_INIT(AddUnbindApplyRequest);

typedef struct AddUnbindApplyResponse 
{
	HsviewResponse base;

	struct AddUnbindApplyResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} AddUnbindApplyResponse;

C_API AddUnbindApplyResponse *HSAPI_INIT(AddUnbindApplyResponse);

#endif
