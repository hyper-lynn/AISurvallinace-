/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_shareAg_ApBeSharedGetPlus_H_
#define _HSVIEW_CLIENT_API_shareAg_ApBeSharedGetPlus_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
配件共享，查询配件所属用户信息（谁分享给我）

【需要使用平台账号签名】
 */

typedef struct shareAg_ApBeSharedGetPlusRequest 
{
	HsviewRequest base;

	struct shareAg_ApBeSharedGetPlusRequestData
	{
		
		/** 配件ID */
		CSTR apId;
		/** 设备ID */
		CSTR deviceId;

	} data;

} shareAg_ApBeSharedGetPlusRequest;

C_API shareAg_ApBeSharedGetPlusRequest *HSAPI_INIT(shareAg_ApBeSharedGetPlusRequest);

typedef struct shareAg_ApBeSharedGetPlusResponse 
{
	HsviewResponse base;

	struct shareAg_ApBeSharedGetPlusResponseData
	{
		
		/** [O]分享着头像url */
		CSTR userIcon;
		/** [O]好友别名 */
		CSTR friendAlias;
		/** [O]分享功能，英文逗号分隔 */
		CSTR functions;
		/** [O]分享时间 */
		CSTR shareTime;
		/** [O]分享着昵称 */
		CSTR nickname;
		/** [O]分享者用户ID */
		CSTR userId;
		/** [O]分享者账号，手机或邮箱，账号加密 */
		CSTR account;
 
	} data;

} shareAg_ApBeSharedGetPlusResponse;

C_API shareAg_ApBeSharedGetPlusResponse *HSAPI_INIT(shareAg_ApBeSharedGetPlusResponse);

#endif
