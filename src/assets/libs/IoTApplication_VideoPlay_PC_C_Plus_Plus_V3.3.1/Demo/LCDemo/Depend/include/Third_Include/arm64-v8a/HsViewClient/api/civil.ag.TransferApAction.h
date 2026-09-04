/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_TransferApAction_H_
#define _HSVIEW_CLIENT_API_TransferApAction_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
报警配件操作接口，当前只支持设置配件的布防使能

【需要使用平台账号签名】
 */

typedef struct TransferApActionRequest 
{
	HsviewRequest base;

	struct TransferApActionRequestData
	{
		
		/** [bool]使能状态：true/false */
		BOOL enable;
		/** 配件ID */
		CSTR apId;
		/** 命令：设置配件的布防使能：set-guard详细见各协议 */
		CSTR action;
		/** 网关的设备ID */
		CSTR deviceId;

	} data;

} TransferApActionRequest;

C_API TransferApActionRequest *HSAPI_INIT(TransferApActionRequest);

typedef struct TransferApActionResponse 
{
	HsviewResponse base;

	struct TransferApActionResponseData
	{
		
		/** [int]返回错误码。成功为0，1- 配件不存在；2-升级地址解析错误；3-当前设备状态不可升级，稍后再试； 4-其他错误 */
		int code;
 
	} data;

} TransferApActionResponse;

C_API TransferApActionResponse *HSAPI_INIT(TransferApActionResponse);

#endif
