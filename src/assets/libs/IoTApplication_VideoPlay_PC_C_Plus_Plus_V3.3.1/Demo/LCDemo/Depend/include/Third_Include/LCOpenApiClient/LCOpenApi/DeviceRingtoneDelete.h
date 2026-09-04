/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_DeviceRingtoneDelete_H_
#define _LC_OPENAPI_CLIENT_DeviceRingtoneDelete_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
删除铃声协议
 */

typedef struct DeviceRingtoneDeleteRequest 
{
	LCOpenApiRequest base;

	struct DeviceRingtoneDeleteRequestData
	{
		
		/** 授权的token(userToken或accessToken) */
		CSTR token;
		/** device: 关联设备报,accessory: 关联配件报警,reply: 关联自定义回复,local: 设备本地铃声，按下门铃后的响声 */
		CSTR relateType;
		/** 通道,不存在默认为设备 */
		CSTR channelId;
		/** [int]歌曲索引 */
		int index;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} DeviceRingtoneDeleteRequest;

C_API DeviceRingtoneDeleteRequest *LCOPENAPI_INIT(DeviceRingtoneDeleteRequest);

typedef struct DeviceRingtoneDeleteResponse 
{
	LCOpenApiResponse base;

	struct DeviceRingtoneDeleteResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} DeviceRingtoneDeleteResponse;

C_API DeviceRingtoneDeleteResponse *LCOPENAPI_INIT(DeviceRingtoneDeleteResponse);

#endif
