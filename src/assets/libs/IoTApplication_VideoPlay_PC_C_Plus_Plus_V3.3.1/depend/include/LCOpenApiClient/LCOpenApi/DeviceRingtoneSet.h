/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_DeviceRingtoneSet_H_
#define _LC_OPENAPI_CLIENT_DeviceRingtoneSet_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
新增铃声协议
 */

typedef struct DeviceRingtoneSetRequest 
{
	LCOpenApiRequest base;

	struct DeviceRingtoneSetRequestData
	{
		
		/** 铃声类型:wav,pcm,aac */
		CSTR type;
		/** 授权的token */
		CSTR token;
		/** [O]device:关联设备报警 accessory:关联配件报警 reply:关联自定义回复 */
		CSTR relateType;
		/** 铃声音频文件对应的已授权URL地址,最大512字节 */
		CSTR url;
		/** [O]通道,不存在默认为设备 */
		CSTR channelId;
		/** 铃声名称,最大32字节,不要带上文件后缀名 */
		CSTR name;
		/** 门铃设备序列号 */
		CSTR deviceId ;

	} data;

} DeviceRingtoneSetRequest;

C_API DeviceRingtoneSetRequest *LCOPENAPI_INIT(DeviceRingtoneSetRequest);

typedef struct DeviceRingtoneSetResponse 
{
	LCOpenApiResponse base;

	struct DeviceRingtoneSetResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} DeviceRingtoneSetResponse;

C_API DeviceRingtoneSetResponse *LCOPENAPI_INIT(DeviceRingtoneSetResponse);

#endif
