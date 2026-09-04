/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDoorbell_MusicVolumeSizeConfig_H_
#define _HSVIEW_CLIENT_API_transferDoorbell_MusicVolumeSizeConfig_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置音量

参考PaaS协议：[设置音量](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E9%97%A8%E9%93%83%E7%9B%B8%E5%85%B3%E6%93%8D%E4%BD%9C%2F%E9%9F%B3%E9%87%8F%2F%E8%AE%BE%E7%BD%AE%E9%9F%B3%E9%87%8F.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferDoorbell_MusicVolumeSizeConfigRequest 
{
	HsviewRequest base;

	struct transferDoorbell_MusicVolumeSizeConfigRequestData
	{
		
		/** [cstr]/device/ring/music/size/config */
		#define _STATIC_transferDoorbell_MusicVolumeSizeConfigRequestData_url "/device/ring/music/size/config"
		CSTR url;
		/** struct of transferDoorbell_MusicVolumeSizeConfigRequestData_Content */
		struct transferDoorbell_MusicVolumeSizeConfigRequestData_Content {
			/** [int]音量大小的百分比，有效值[0, 100] */
			int percent;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferDoorbell_MusicVolumeSizeConfigRequest;

C_API transferDoorbell_MusicVolumeSizeConfigRequest *HSAPI_INIT(transferDoorbell_MusicVolumeSizeConfigRequest);

typedef struct transferDoorbell_MusicVolumeSizeConfigResponse 
{
	HsviewResponse base;

	struct transferDoorbell_MusicVolumeSizeConfigResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} transferDoorbell_MusicVolumeSizeConfigResponse;

C_API transferDoorbell_MusicVolumeSizeConfigResponse *HSAPI_INIT(transferDoorbell_MusicVolumeSizeConfigResponse);

#endif
