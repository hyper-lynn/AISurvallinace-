/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_UpgradeAP_H_
#define _HSVIEW_CLIENT_API_UpgradeAP_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
升级配件
 */

typedef struct UpgradeAPRequest 
{
	HsviewRequest base;

	struct UpgradeAPRequestData
	{
		
		/** 设备ID */
		CSTR devId;
		/** 无需设置 */
		CSTR optional;
		/** [cstr]POST */
		#define _STATIC_UpgradeAPRequestData_METHOD "POST"
		/** [cstr]agcmd */
		#define _STATIC_UpgradeAPRequestData_CMD "agcmd"
		/** struct of UpgradeAPRequestData_Body */
		struct UpgradeAPRequestData_Body {
			/** 配件id */
			CSTR ID;
			/** [cstr]upgrade */
			#define _STATIC_UpgradeAPRequestData_Body_Action "upgrade"
			/** 升级包地址 */
			CSTR Package;
		} body;

	} data;

} UpgradeAPRequest;

C_API UpgradeAPRequest *HSAPI_INIT(UpgradeAPRequest);

typedef struct UpgradeAPResponse 
{
	HsviewResponse base;

	struct UpgradeAPResponseData
	{
		
		/** [int]返回错误码。成功为0，1- 配件不存在；2-升级地址解析错误；3-当前设备状态不可升级，稍后再试； 4-其他错误 */
		int Code;
 
	} data;

} UpgradeAPResponse;

C_API UpgradeAPResponse *HSAPI_INIT(UpgradeAPResponse);

#endif
