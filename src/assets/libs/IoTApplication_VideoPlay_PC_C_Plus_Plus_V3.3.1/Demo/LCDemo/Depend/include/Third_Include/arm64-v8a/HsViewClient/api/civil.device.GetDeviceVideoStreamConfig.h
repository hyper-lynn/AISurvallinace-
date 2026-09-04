/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetDeviceVideoStreamConfig_H_
#define _HSVIEW_CLIENT_API_GetDeviceVideoStreamConfig_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置设备拉流时间。
【使用平台账号签名】
 */

typedef struct GetDeviceVideoStreamConfigRequest 
{
	HsviewRequest base;

	struct GetDeviceVideoStreamConfigRequestData
	{
		
		/** [int]通道号 */
		int channelId;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} GetDeviceVideoStreamConfigRequest;

C_API GetDeviceVideoStreamConfigRequest *HSAPI_INIT(GetDeviceVideoStreamConfigRequest);

typedef struct GetDeviceVideoStreamConfigResponse 
{
	HsviewResponse base;

	struct GetDeviceVideoStreamConfigResponseData
	{
		
		/** [long]设备拉流时间，单位秒（s） */
		int64 streamTime;
 
	} data;

} GetDeviceVideoStreamConfigResponse;

C_API GetDeviceVideoStreamConfigResponse *HSAPI_INIT(GetDeviceVideoStreamConfigResponse);

#endif
