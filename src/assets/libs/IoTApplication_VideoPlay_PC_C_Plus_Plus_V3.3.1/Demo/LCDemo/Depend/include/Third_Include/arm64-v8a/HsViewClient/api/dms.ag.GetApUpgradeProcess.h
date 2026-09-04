/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetApUpgradeProcess_H_
#define _HSVIEW_CLIENT_API_GetApUpgradeProcess_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置配件升级进度

> * ID：配件ID
> * Version：配件当前的软件版本号
> * Status：升级状态：
>  - `Idle` 没在升级
>  - `Downloading` 下载升级包中
>  - `Upgrading` 升级中
> * Percent：当前状态的进度百分比
> * Code：返回错误码：
>  - 0 成功
>  - 1 配件不存在
>  - 2 其他错误类型
 */

typedef struct GetApUpgradeProcessRequest 
{
	HsviewRequest base;

	struct GetApUpgradeProcessRequestData
	{
		
		/** 设备ID */
		CSTR devId;
		/** 无需设置 */
		CSTR optional;
		/** [cstr]POST */
		#define _STATIC_GetApUpgradeProcessRequestData_METHOD "POST"
		/** [cstr]agcmd */
		#define _STATIC_GetApUpgradeProcessRequestData_CMD "agcmd"
		/** struct of GetApUpgradeProcessRequestData_Body */
		struct GetApUpgradeProcessRequestData_Body {
			/** [cstr]get-upgrade-progress */
			#define _STATIC_GetApUpgradeProcessRequestData_Body_Action "get-upgrade-progress"
			/** 配件id */
			CSTR ID;
		} body;

	} data;

} GetApUpgradeProcessRequest;

C_API GetApUpgradeProcessRequest *HSAPI_INIT(GetApUpgradeProcessRequest);

typedef struct GetApUpgradeProcessResponse 
{
	HsviewResponse base;

	struct GetApUpgradeProcessResponseData
	{
		
		/** 升级状态 */
		CSTR Status;
		/** [int]前状态的进度百分比 */
		int Percent;
		/** 配件当前的软件版本号 */
		CSTR Version;
		/** [int]返回错误码。成功为0，1- 配件不存在；2-升级地址解析错误；3-当前设备状态不可升级，稍后再试； 4-其他错误 */
		int Code;
 
	} data;

} GetApUpgradeProcessResponse;

C_API GetApUpgradeProcessResponse *HSAPI_INIT(GetApUpgradeProcessResponse);

#endif
