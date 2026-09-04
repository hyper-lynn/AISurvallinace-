/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_SwitchScene_H_
#define _HSVIEW_CLIENT_API_SwitchScene_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
手动切换用户当前的情景模式。
【使用平台账号签名】
 */

typedef struct SwitchSceneRequest 
{
	HsviewRequest base;

	struct SwitchSceneRequestData
	{
		
		/** 要切换成的情景模式 */
		CSTR mode;

	} data;

} SwitchSceneRequest;

C_API SwitchSceneRequest *HSAPI_INIT(SwitchSceneRequest);

typedef struct SwitchSceneResponse 
{
	HsviewResponse base;

	struct SwitchSceneResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} SwitchSceneResponse;

C_API SwitchSceneResponse *HSAPI_INIT(SwitchSceneResponse);

#endif
