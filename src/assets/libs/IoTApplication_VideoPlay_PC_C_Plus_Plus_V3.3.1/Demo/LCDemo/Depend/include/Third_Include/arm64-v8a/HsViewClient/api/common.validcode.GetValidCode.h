/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_commonValidcode_GetValidCode_H_
#define _HSVIEW_CLIENT_API_commonValidcode_GetValidCode_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取验证码接口

usage的枚举值如下
Register：用户注册 
ChangeAccount：账号变更（更换手机号或邮箱 etc.）
BindAccount：账号变更（绑定手机号或邮箱 etc.；）
UnBindAccount：账号变更（解绑手机号或邮箱 etc.；）
ResetPassword：密码重置（含忘记密码）
TransferDevices：设备转移
GenerateSnapkey：k5门锁生成临时秘钥
AccountCancellation：账号注销
ExportAccountInfo：账号信息导出
CloudStorage：云存储密码修改
DeviceCancel: 设备注销
ResetCustomPassword：重置设备自定义秘钥
ResetDevicePassword：重置设备密码
PhoneAlarm：设置电话报警联系人
VerifyEmail: 校验邮箱的有效性（lorex定制使用）
GetUnbindApplyInfo: 查询解绑详情信息
SMSLogin:短信验证码登陆
SetUserPassword:设置用户密码
ObtainApSnapKey：获取配件临时秘钥
SetTwoStepVerifyAccount：二次认证（lorex使用）
language参数从x-pcs-client-ua头域中获取

【默认AK、SK签名认证】
 */

typedef struct commonValidcode_GetValidCodeRequest 
{
	HsviewRequest base;

	struct commonValidcode_GetValidCodeRequestData
	{
		
		/** 类型, phone、email */
		CSTR type;
		/** [O]国际区号,海外需要该字段，当type为phone且usage为Register||ChangeAccount||BindAccount时填写，用于海外接国际手机号码标识相应的国际区号 */
		CSTR areaCode;
		/** 用途，取值详见下面说明 */
		CSTR usage;
		/** [O]验证码token(common.validcode.CheckValidCode接口返回中有携带), 当type为email且usage为ExportAccountInfo时填写, 用于国内APP导出用户信息功能关联手机验证与邮箱验证两步操作 */
		CSTR accessToken;
		/** 帐号, 手机号码、邮箱 */
		CSTR account;

	} data;

} commonValidcode_GetValidCodeRequest;

C_API commonValidcode_GetValidCodeRequest *HSAPI_INIT(commonValidcode_GetValidCodeRequest);

typedef struct commonValidcode_GetValidCodeResponse 
{
	HsviewResponse base;

	struct commonValidcode_GetValidCodeResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} commonValidcode_GetValidCodeResponse;

C_API commonValidcode_GetValidCodeResponse *HSAPI_INIT(commonValidcode_GetValidCodeResponse);

#endif
