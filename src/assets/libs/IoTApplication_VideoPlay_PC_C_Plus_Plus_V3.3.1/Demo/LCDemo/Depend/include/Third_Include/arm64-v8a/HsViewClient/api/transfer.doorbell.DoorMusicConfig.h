/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDoorbell_DoorMusicConfig_H_
#define _HSVIEW_CLIENT_API_transferDoorbell_DoorMusicConfig_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置门铃铃声（门铃自带铃声）

设备已经在播放时，返回错误码13803

参考PaaS协议：[设置门铃铃声](https://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E9%97%A8%E9%93%83%E7%9B%B8%E5%85%B3%E6%93%8D%E4%BD%9C%2F%E9%93%83%E5%A3%B0%2F%E8%AE%BE%E7%BD%AE%E9%93%83%E5%A3%B0%28%E9%97%A8%E9%93%83Amcrest%29.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferDoorbell_DoorMusicConfigRequest 
{
	HsviewRequest base;

	struct transferDoorbell_DoorMusicConfigRequestData
	{
		
		/** [cstr]/device/doorbell/music/config */
		#define _STATIC_transferDoorbell_DoorMusicConfigRequestData_url "/device/doorbell/music/config"
		CSTR url;
		/** struct of transferDoorbell_DoorMusicConfigRequestData_Content */
		struct transferDoorbell_DoorMusicConfigRequestData_Content {
			/** [int]歌曲索引 */
			int index;
			/** [O]关联铃声生效类型.quickReply-快捷回复 */
			CSTR relateType;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferDoorbell_DoorMusicConfigRequest;

C_API transferDoorbell_DoorMusicConfigRequest *HSAPI_INIT(transferDoorbell_DoorMusicConfigRequest);

typedef struct transferDoorbell_DoorMusicConfigResponse 
{
	HsviewResponse base;

	struct transferDoorbell_DoorMusicConfigResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} transferDoorbell_DoorMusicConfigResponse;

C_API transferDoorbell_DoorMusicConfigResponse *HSAPI_INIT(transferDoorbell_DoorMusicConfigResponse);

#endif
