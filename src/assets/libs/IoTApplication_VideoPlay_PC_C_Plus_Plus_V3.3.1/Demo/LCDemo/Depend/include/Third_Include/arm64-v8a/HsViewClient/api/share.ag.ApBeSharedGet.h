/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_shareAg_ApBeSharedGet_H_
#define _HSVIEW_CLIENT_API_shareAg_ApBeSharedGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
配件共享，查询配件所属用户信息（谁分享给我）

【需要使用平台账号签名】
 */

typedef struct shareAg_ApBeSharedGetRequest 
{
	HsviewRequest base;

	struct shareAg_ApBeSharedGetRequestData
	{
		
		/** 配件ID */
		CSTR apId;
		/** 设备ID */
		CSTR deviceId;

	} data;

} shareAg_ApBeSharedGetRequest;

C_API shareAg_ApBeSharedGetRequest *HSAPI_INIT(shareAg_ApBeSharedGetRequest);

typedef struct shareAg_ApBeSharedGetResponse 
{
	HsviewResponse base;

	struct shareAg_ApBeSharedGetResponseData
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
		/** [O]分享者账号，手机或邮箱 */
		CSTR account;
 
	} data;

} shareAg_ApBeSharedGetResponse;

C_API shareAg_ApBeSharedGetResponse *HSAPI_INIT(shareAg_ApBeSharedGetResponse);

#endif
