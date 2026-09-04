/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_SetSoundVolumeSize_H_
#define _LC_OPENAPI_CLIENT_SetSoundVolumeSize_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
type=playsound 设置在线设备提示音量分贝,需要设备拥有PlaySoundModify设备提示音调节能力 
type=decible 设置在线设备异常检测音分贝,需要设备拥有AbAlarmSound异常报警音能力和CheckAbDecible异常检测音分贝阈值能力

 */

typedef struct SetSoundVolumeSizeRequest 
{
	LCOpenApiRequest base;

	struct SetSoundVolumeSizeRequestData
	{
		
		/** 设备音量类型,playsound:提示音 decible:异常检测音 */
		CSTR type;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 通道下挂载设备的序列号,channelSn与channelId均存在则优先channelSn */
		CSTR channelSn;
		/** 设备分贝大小,单位跟取值范围跟具体设备有关 */
		CSTR value;
		/** 通道ID */
		CSTR channelId;
		/** [cstr]setSoundVolumeSize */
		#define _STATIC_SetSoundVolumeSizeRequestData_method "setSoundVolumeSize"
		CSTR method;
		/** 设备ID */
		CSTR deviceId;

	} data;

} SetSoundVolumeSizeRequest;

C_API SetSoundVolumeSizeRequest *LCOPENAPI_INIT(SetSoundVolumeSizeRequest);

typedef struct SetSoundVolumeSizeResponse 
{
	LCOpenApiResponse base;

	struct SetSoundVolumeSizeResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} SetSoundVolumeSizeResponse;

C_API SetSoundVolumeSizeResponse *LCOPENAPI_INIT(SetSoundVolumeSizeResponse);

#endif
