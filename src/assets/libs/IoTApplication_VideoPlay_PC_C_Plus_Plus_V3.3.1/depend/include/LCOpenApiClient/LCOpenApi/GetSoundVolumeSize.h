/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 225092, Author: 278719, Date: 2023-09-01 14:48:55 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_GetSoundVolumeSize_H_
#define _LC_OPENAPI_CLIENT_GetSoundVolumeSize_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
type=playsound 获取在线设备提示音量分贝,需要设备拥有PlaySoundModify设备提示音调节能力
type=decible 获取在线设备异常检测音分贝,需要设备拥有AbAlarmSound异常报警音能力和CheckAbDecible异常检测音分贝阈值能力

 */

typedef struct GetSoundVolumeSizeRequest 
{
	LCOpenApiRequest base;

	struct GetSoundVolumeSizeRequestData
	{
		
		/** 设备音量类型,playsound:提示音 decible:异常检测音 */
		CSTR type;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 通道ID */
		CSTR channelId;
		/** 通道下挂载设备的序列号,channelSn与channelId均存在则优先channelSn */
		CSTR channelSn;
		/** 设备ID */
		CSTR deviceId;

	} data;

} GetSoundVolumeSizeRequest;

C_API GetSoundVolumeSizeRequest *LCOPENAPI_INIT(GetSoundVolumeSizeRequest);

typedef struct GetSoundVolumeSizeResponse 
{
	LCOpenApiResponse base;

	struct GetSoundVolumeSizeResponseData
	{
		
		/** 音量大小 */
		CSTR value;
 
	} data;

} GetSoundVolumeSizeResponse;

C_API GetSoundVolumeSizeResponse *LCOPENAPI_INIT(GetSoundVolumeSizeResponse);

#endif
