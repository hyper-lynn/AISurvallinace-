/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDevice_DeleteSound_H_
#define _HSVIEW_CLIENT_API_transferDevice_DeleteSound_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
删除铃声协议

参考PaaS协议：[删除铃声](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E9%97%A8%E9%93%83%E7%9B%B8%E5%85%B3%E6%93%8D%E4%BD%9C%2F%E9%93%83%E5%A3%B0%2F%E5%88%A0%E9%99%A4%E9%93%83%E5%A3%B0.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferDevice_DeleteSoundRequest 
{
	HsviewRequest base;

	struct transferDevice_DeleteSoundRequestData
	{
		
		/** [cstr]/device/delete/sound */
		#define _STATIC_transferDevice_DeleteSoundRequestData_url "/device/delete/sound"
		CSTR url;
		/** struct of transferDevice_DeleteSoundRequestData_Content */
		struct transferDevice_DeleteSoundRequestData_Content {
			/** [int]歌曲索引 */
			int index;
			/** device: 关联设备报,accessory: 关联配件报警,reply: 关联自定义回复,local: 设备本地铃声，按下门铃后的响声 */
			CSTR relateType;
			/** [O]通道,不存在默认为设备 */
			CSTR chan;
			/** [O]设备序列号 */
			CSTR sn;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferDevice_DeleteSoundRequest;

C_API transferDevice_DeleteSoundRequest *HSAPI_INIT(transferDevice_DeleteSoundRequest);

typedef struct transferDevice_DeleteSoundResponse 
{
	HsviewResponse base;

	struct transferDevice_DeleteSoundResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} transferDevice_DeleteSoundResponse;

C_API transferDevice_DeleteSoundResponse *HSAPI_INIT(transferDevice_DeleteSoundResponse);

#endif
