/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetSceneDef_H_
#define _HSVIEW_CLIENT_API_GetSceneDef_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取情景模式定义。
【使用平台账号签名】
 */

typedef struct GetSceneDefRequest 
{
	HsviewRequest base;

	struct GetSceneDefRequestData
	{
		
		/** 模式名称，为空表示查询所有模式，不为空则查指定的模式 */
		CSTR mode;
		/** 通道号，查询某个通道的设置 */
		CSTR channelId;
		/** 设备ID，为空则表示获取用户所有设备情景定义 */
		CSTR deviceId;

	} data;

} GetSceneDefRequest;

C_API GetSceneDefRequest *HSAPI_INIT(GetSceneDefRequest);

typedef struct GetSceneDefResponse 
{
	HsviewResponse base;

	struct GetSceneDefResponseData
	{
		
		/** define a list with struct of GetSceneDefResponseData_DefsElement */
		DECLARE_LIST(struct GetSceneDefResponseData_DefsElement
		{
			/** 设备类型 */
			CSTR type;
			/** 状态 */
			CSTR status;
			/** 通道号 */
			CSTR channelId;
			/** 模式名称 */
			CSTR mode;
			/** 设备ID */
			CSTR deviceId;
		}) defs;
 
	} data;

} GetSceneDefResponse;

C_API GetSceneDefResponse *HSAPI_INIT(GetSceneDefResponse);

#endif
