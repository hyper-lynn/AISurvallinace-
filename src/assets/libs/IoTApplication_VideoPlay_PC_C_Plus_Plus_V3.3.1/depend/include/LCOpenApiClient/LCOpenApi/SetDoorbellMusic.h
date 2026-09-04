/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 221279, Author: 27665, Date: 2021-10-14 16:02:14 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_SetDoorbellMusic_H_
#define _LC_OPENAPI_CLIENT_SetDoorbellMusic_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
设置铃声到铃铛（配置在门铃，控制响的是铃铛）
 */

typedef struct SetDoorbellMusicRequest 
{
	LCOpenApiRequest base;

	struct SetDoorbellMusicRequestData
	{
		
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** [String]生效类型:device:关联设备报警,accessory:关联配件报警,reply:关联自定义回复,local: 设备本地铃声，按下门铃后的响声 */
		CSTR relateType;
		/** 通道ID */
		CSTR channelId;
		/** [int]歌曲索引 */
		int index;
		/** 设备ID */
		CSTR deviceId;

	} data;

} SetDoorbellMusicRequest;

C_API SetDoorbellMusicRequest *LCOPENAPI_INIT(SetDoorbellMusicRequest);

typedef struct SetDoorbellMusicResponse 
{
	LCOpenApiResponse base;

	struct SetDoorbellMusicResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} SetDoorbellMusicResponse;

C_API SetDoorbellMusicResponse *LCOPENAPI_INIT(SetDoorbellMusicResponse);

#endif
