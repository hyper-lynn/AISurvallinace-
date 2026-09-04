/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_DeviceRingtoneList_H_
#define _LC_OPENAPI_CLIENT_DeviceRingtoneList_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取铃声配置及铃声列表
 */

typedef struct DeviceRingtoneListRequest 
{
	LCOpenApiRequest base;

	struct DeviceRingtoneListRequestData
	{
		
		/** device: 关联设备报,accessory: 关联配件报警,reply: 关联自定义回复,local: 设备本地铃声，按下门铃后的响声 */
		CSTR relateType;
		/** 通道,不存在默认为设备 */
		CSTR channelId;
		/** 授权的token(userToken或accessToken) */
		CSTR token;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} DeviceRingtoneListRequest;

C_API DeviceRingtoneListRequest *LCOPENAPI_INIT(DeviceRingtoneListRequest);

typedef struct DeviceRingtoneListResponse 
{
	LCOpenApiResponse base;

	struct DeviceRingtoneListResponseData
	{
		
		/** 用户配置的铃声索引。-1：表示未配置 */
		CSTR index;
		/** define a list with struct of DeviceRingtoneListResponseData_ListElement */
		DECLARE_LIST(struct DeviceRingtoneListResponseData_ListElement
		{
			/** 铃声状态, play：可播放, download：下载中，不可播放， 该字段不存在或为空，默认为play */
			CSTR state;
			/** 铃声类型:wav,pcm,aac */
			CSTR type;
			/** 歌曲索引，从0开始 */
			CSTR index;
			/** 关联铃声生效类型，device:关联设备报警，accessory:关联配件报警,reply:关联自定义回复 */
			CSTR relateType;
			/** 区分默认铃声/自定义铃声，default:默认铃声，custom:自定义 */
			CSTR ringMode;
			/** 歌曲名称 */
			CSTR name;
		}) list;
 
	} data;

} DeviceRingtoneListResponse;

C_API DeviceRingtoneListResponse *LCOPENAPI_INIT(DeviceRingtoneListResponse);

#endif
