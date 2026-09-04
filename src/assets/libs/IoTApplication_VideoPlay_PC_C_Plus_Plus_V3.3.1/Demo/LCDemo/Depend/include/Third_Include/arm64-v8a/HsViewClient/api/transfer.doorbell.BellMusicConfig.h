/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDoorbell_BellMusicConfig_H_
#define _HSVIEW_CLIENT_API_transferDoorbell_BellMusicConfig_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置铃声到铃铛（配置在门铃，控制响的是铃铛）

参考PaaS协议：[设置铃声](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E9%97%A8%E9%93%83%E7%9B%B8%E5%85%B3%E6%93%8D%E4%BD%9C%2F%E9%93%83%E5%A3%B0%2F%E8%AE%BE%E7%BD%AE%E9%93%83%E5%A3%B0.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferDoorbell_BellMusicConfigRequest 
{
	HsviewRequest base;

	struct transferDoorbell_BellMusicConfigRequestData
	{
		
		/** [cstr]/device/bell/music/config */
		#define _STATIC_transferDoorbell_BellMusicConfigRequestData_url "/device/bell/music/config"
		CSTR url;
		/** struct of transferDoorbell_BellMusicConfigRequestData_Content */
		struct transferDoorbell_BellMusicConfigRequestData_Content {
			/** [int]歌曲索引 */
			int index;
			/** [O]生效类型,device:关联设备报警,accessory:关联配件报警,reply:关联自定义回复,local: 设备本地铃声，按下门铃后的响声 */
			CSTR relateType;
			/** [O]通道,不存在默认为设备 */
			CSTR chan;
			/** [O]设备序列号 */
			CSTR sn;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferDoorbell_BellMusicConfigRequest;

C_API transferDoorbell_BellMusicConfigRequest *HSAPI_INIT(transferDoorbell_BellMusicConfigRequest);

typedef struct transferDoorbell_BellMusicConfigResponse 
{
	HsviewResponse base;

	struct transferDoorbell_BellMusicConfigResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} transferDoorbell_BellMusicConfigResponse;

C_API transferDoorbell_BellMusicConfigResponse *HSAPI_INIT(transferDoorbell_BellMusicConfigResponse);

#endif
