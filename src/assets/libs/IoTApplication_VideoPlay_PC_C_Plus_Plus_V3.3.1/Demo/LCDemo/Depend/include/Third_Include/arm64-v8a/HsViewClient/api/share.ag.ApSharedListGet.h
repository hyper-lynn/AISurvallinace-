/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_shareAg_ApSharedListGet_H_
#define _HSVIEW_CLIENT_API_shareAg_ApSharedListGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
配件共享，查询共享给TA的列表（分享给谁）
functions: apAlarmMsg,apConfigure
friendInfo是可选字段，乐橙基线才会返回，其他的不会返回相关字段。

【需要使用平台账号签名】
 */

typedef struct shareAg_ApSharedListGetRequest 
{
	HsviewRequest base;

	struct shareAg_ApSharedListGetRequestData
	{
		
		/** 配件ID */
		CSTR apId;
		/** 设备ID */
		CSTR deviceId;

	} data;

} shareAg_ApSharedListGetRequest;

C_API shareAg_ApSharedListGetRequest *HSAPI_INIT(shareAg_ApSharedListGetRequest);

typedef struct shareAg_ApSharedListGetResponse 
{
	HsviewResponse base;

	struct shareAg_ApSharedListGetResponseData
	{
		
		/** 分享次数，配件目前分享了多少次 */
		CSTR shareCount;
		/** define a list with struct of shareAg_ApSharedListGetResponseData_ShareListElement */
		DECLARE_LIST(struct shareAg_ApSharedListGetResponseData_ShareListElement
		{
			/** [O]被分享着头像url */
			CSTR userIcon;
			/** [O]好友别名 */
			CSTR friendAlias;
			/** [O]分享功能，英文逗号分隔 */
			CSTR functions;
			/** [O]分享时间 */
			CSTR shareTime;
			/** [O]被分享着昵称 */
			CSTR nickname;
			/** [O] 被分享者用户ID */
			CSTR userId;
			/** [O]被分享者账号，手机或邮箱，账号加密 */
			CSTR account;
		}) shareList;
		/** 拥有者用户Id */
		CSTR ownerId;
		/** 剩余分享数量 */
		CSTR leftShareCount;
		/** 允许分享数量, 999表示不限制,999表示为vip */
		CSTR allowShareCount;
		/** 默认分享数量，默认10 */
		CSTR defaultNum;
 
	} data;

} shareAg_ApSharedListGetResponse;

C_API shareAg_ApSharedListGetResponse *HSAPI_INIT(shareAg_ApSharedListGetResponse);

#endif
