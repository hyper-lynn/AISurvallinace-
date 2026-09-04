/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_SetSceneDef_H_
#define _HSVIEW_CLIENT_API_SetSceneDef_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
配置某个设备或某个配件的情景模式定义。
【使用平台账号签名】
 */

typedef struct SetSceneDefRequest 
{
	HsviewRequest base;

	struct SetSceneDefRequestData
	{
		
		/** define a list with struct of SetSceneDefRequestData_DefsElement */
		DECLARE_LIST(struct SetSceneDefRequestData_DefsElement
		{
			/** 设备类型 */
			CSTR type;
			/** 状态，on或off */
			CSTR status;
			/** 通道号 */
			CSTR channelId;
			/** 模式名称 */
			CSTR mode;
			/** 设备ID */
			CSTR deviceId;
		}) defs;

	} data;

} SetSceneDefRequest;

C_API SetSceneDefRequest *HSAPI_INIT(SetSceneDefRequest);

typedef struct SetSceneDefResponse 
{
	HsviewResponse base;

	struct SetSceneDefResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} SetSceneDefResponse;

C_API SetSceneDefResponse *HSAPI_INIT(SetSceneDefResponse);

#endif
