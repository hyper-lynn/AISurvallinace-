/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_ListDoorbellMusic_H_
#define _LC_OPENAPI_CLIENT_ListDoorbellMusic_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取铃声配置及铃声列表（配置在门铃声，控制响的是铃铛）
 */

typedef struct ListDoorbellMusicRequest 
{
	LCOpenApiRequest base;

	struct ListDoorbellMusicRequestData
	{
		
		/** 生效类型,device:关联设备报警,accessory:关联配件报警,reply:关联自定义回复,local: 设备本地铃声，按下门铃后的响声 */
		CSTR relateType;
		/** 通道号 */
		CSTR channelId;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备ID */
		CSTR deviceId;

	} data;

} ListDoorbellMusicRequest;

C_API ListDoorbellMusicRequest *LCOPENAPI_INIT(ListDoorbellMusicRequest);

typedef struct ListDoorbellMusicResponse 
{
	LCOpenApiResponse base;

	struct ListDoorbellMusicResponseData
	{
		
		/** define a list with struct of ListDoorbellMusicResponseData_ListElement */
		DECLARE_LIST(struct ListDoorbellMusicResponseData_ListElement
		{
			/** [String]可选字段：铃声状态, play：可播放, download：下载中，不可播放， 该字段不存在或为空，默认为play */
			CSTR state;
			/** [String]铃声类型:wav,pcm,aac */
			CSTR type;
			/** [int]歌曲索引，从0开始 */
			int index;
			/** [String]可选字段：关联铃声生效类型，device:关联设备报警，accessory:关联配件报警,reply:关联自定义回复 */
			CSTR relateType;
			/** [String]区分默认铃声/自定义铃声，default:默认铃声，custom:自定义 */
			CSTR ringMode;
			/** [String]歌曲名称 */
			CSTR name;
		}) list;
		/** [int]用户配置的铃声索引。-1：表示未配置 */
		int ringIndex;
 
	} data;

} ListDoorbellMusicResponse;

C_API ListDoorbellMusicResponse *LCOPENAPI_INIT(ListDoorbellMusicResponse);

#endif
