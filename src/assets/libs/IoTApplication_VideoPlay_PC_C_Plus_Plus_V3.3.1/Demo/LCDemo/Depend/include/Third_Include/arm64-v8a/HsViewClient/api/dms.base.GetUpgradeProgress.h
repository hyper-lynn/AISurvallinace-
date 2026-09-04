/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetUpgradeProgress_H_
#define _HSVIEW_CLIENT_API_GetUpgradeProgress_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取升级设备进度
Version表示当前版本
Status表示升级的状态，有以下几种：
	Idle：没在升级
	Downloading：下载升级包
	Upgrading：升级
Percent表示当前正在进行的百分比
 */

typedef struct GetUpgradeProgressRequest 
{
	HsviewRequest base;

	struct GetUpgradeProgressRequestData
	{
		
		/** 设备ID */
		CSTR devId;
		/** 无需设置 */
		CSTR optional;
		/** [cstr]GET */
		#define _STATIC_GetUpgradeProgressRequestData_METHOD "GET"
		/** [cstr]upgrade-progress */
		#define _STATIC_GetUpgradeProgressRequestData_CMD "upgrade-progress"
		/** struct of GetUpgradeProgressRequestData_Body */
		struct GetUpgradeProgressRequestData_Body {
			/** [int][O]保留 */
			int _nouse;
		} body;

	} data;

} GetUpgradeProgressRequest;

C_API GetUpgradeProgressRequest *HSAPI_INIT(GetUpgradeProgressRequest);

typedef struct GetUpgradeProgressResponse 
{
	HsviewResponse base;

	struct GetUpgradeProgressResponseData
	{
		
		/** 当前状态：Idle、Downloading、Upgrading */
		CSTR Status;
		/** 版本号 */
		CSTR Version;
		/** [int]进度百分比 */
		int Percent;
 
	} data;

} GetUpgradeProgressResponse;

C_API GetUpgradeProgressResponse *HSAPI_INIT(GetUpgradeProgressResponse);

#endif
