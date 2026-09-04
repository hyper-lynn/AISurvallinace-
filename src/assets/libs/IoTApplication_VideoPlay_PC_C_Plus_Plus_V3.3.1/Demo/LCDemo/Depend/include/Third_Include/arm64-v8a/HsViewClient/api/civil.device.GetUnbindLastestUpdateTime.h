/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetUnbindLastestUpdateTime_H_
#define _HSVIEW_CLIENT_API_GetUnbindLastestUpdateTime_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
【需要使用平台账号签名】
 */

typedef struct GetUnbindLastestUpdateTimeRequest 
{
	HsviewRequest base;

	struct GetUnbindLastestUpdateTimeRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} GetUnbindLastestUpdateTimeRequest;

C_API GetUnbindLastestUpdateTimeRequest *HSAPI_INIT(GetUnbindLastestUpdateTimeRequest);

typedef struct GetUnbindLastestUpdateTimeResponse 
{
	HsviewResponse base;

	struct GetUnbindLastestUpdateTimeResponseData
	{
		
		/** [long]该用户的流程最近更新时间，UNIX时间戳（秒） */
		int64 lastUpdateTime;
 
	} data;

} GetUnbindLastestUpdateTimeResponse;

C_API GetUnbindLastestUpdateTimeResponse *HSAPI_INIT(GetUnbindLastestUpdateTimeResponse);

#endif
