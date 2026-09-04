/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_DoorbellMusicSet_H_
#define _LC_OPENAPI_CLIENT_DoorbellMusicSet_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
设置门铃的自带铃声
 */

typedef struct DoorbellMusicSetRequest 
{
	LCOpenApiRequest base;

	struct DoorbellMusicSetRequestData
	{
		
		/** [int]门铃自带的铃声索引号 */
		int index;
		/** 门铃设备序列号 */
		CSTR deviceId ;
		/** 授权的token */
		CSTR token;

	} data;

} DoorbellMusicSetRequest;

C_API DoorbellMusicSetRequest *LCOPENAPI_INIT(DoorbellMusicSetRequest);

typedef struct DoorbellMusicSetResponse 
{
	LCOpenApiResponse base;

	struct DoorbellMusicSetResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} DoorbellMusicSetResponse;

C_API DoorbellMusicSetResponse *LCOPENAPI_INIT(DoorbellMusicSetResponse);

#endif
