/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDevice_AddSound_H_
#define _HSVIEW_CLIENT_API_transferDevice_AddSound_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
新增铃声协议

参考PaaS协议：[新增铃声](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E9%97%A8%E9%93%83%E7%9B%B8%E5%85%B3%E6%93%8D%E4%BD%9C%2F%E9%93%83%E5%A3%B0%2F%E6%96%B0%E5%A2%9E%E9%93%83%E5%A3%B0.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferDevice_AddSoundRequest 
{
	HsviewRequest base;

	struct transferDevice_AddSoundRequestData
	{
		
		/** [cstr]/device/add/sound */
		#define _STATIC_transferDevice_AddSoundRequestData_url "/device/add/sound"
		CSTR url;
		/** struct of transferDevice_AddSoundRequestData_Content */
		struct transferDevice_AddSoundRequestData_Content {
			/** 铃声类型:wav,pcm,aac */
			CSTR type;
			/** [O]设备序列号 */
			CSTR sn;
			/** [O]device:关联设备报警 accessory:关联配件报警 reply:关联自定义回复 */
			CSTR relateType;
			/** 铃声音频文件对应的已授权URL地址,最大512字节 */
			CSTR url;
			/** [O]通道,不存在默认为设备 */
			CSTR chan;
			/** 铃声名称,最大32字节,不要带上文件后缀名 */
			CSTR name;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferDevice_AddSoundRequest;

C_API transferDevice_AddSoundRequest *HSAPI_INIT(transferDevice_AddSoundRequest);

typedef struct transferDevice_AddSoundResponse 
{
	HsviewResponse base;

	struct transferDevice_AddSoundResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} transferDevice_AddSoundResponse;

C_API transferDevice_AddSoundResponse *HSAPI_INIT(transferDevice_AddSoundResponse);

#endif
