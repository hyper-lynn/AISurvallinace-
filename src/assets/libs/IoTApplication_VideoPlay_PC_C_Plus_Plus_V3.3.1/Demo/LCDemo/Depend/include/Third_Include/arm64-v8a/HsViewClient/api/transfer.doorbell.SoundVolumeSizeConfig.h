/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDoorbell_SoundVolumeSizeConfig_H_
#define _HSVIEW_CLIENT_API_transferDoorbell_SoundVolumeSizeConfig_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置音量通用协议

注：content内容说明
设备级操作，chan，sn不需要设置
通道级操作，当type = decible时，需要设备支持通道异常检测音分贝阈值能力： ChanCheckAbDecible。sn，表示deviceId代表的设备通道下关联的设备序列号，chan是对应的通道号，当sn，chan都下发时，优先sn

参考PaaS协议：[设置音量通用协议](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E9%97%A8%E9%93%83%E7%9B%B8%E5%85%B3%E6%93%8D%E4%BD%9C%2F%E9%9F%B3%E9%87%8F%2F%E8%AE%BE%E7%BD%AE%E9%9F%B3%E9%87%8F%E9%80%9A%E7%94%A8%E5%8D%8F%E8%AE%AE.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferDoorbell_SoundVolumeSizeConfigRequest 
{
	HsviewRequest base;

	struct transferDoorbell_SoundVolumeSizeConfigRequestData
	{
		
		/** [cstr]/device/sound/volume/config */
		#define _STATIC_transferDoorbell_SoundVolumeSizeConfigRequestData_url "/device/sound/volume/config"
		CSTR url;
		/** struct of transferDoorbell_SoundVolumeSizeConfigRequestData_Content */
		struct transferDoorbell_SoundVolumeSizeConfigRequestData_Content {
			/** 音量的大小，单位跟取值范围跟具体类型有关，由客户端跟设备定 */
			CSTR value;
			/** 音量的类型，decible：异常检测音的分贝 */
			CSTR type;
			/** [O]通道,不存在默认为设备 */
			CSTR chan;
			/** [O]设备序列号 */
			CSTR sn;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferDoorbell_SoundVolumeSizeConfigRequest;

C_API transferDoorbell_SoundVolumeSizeConfigRequest *HSAPI_INIT(transferDoorbell_SoundVolumeSizeConfigRequest);

typedef struct transferDoorbell_SoundVolumeSizeConfigResponse 
{
	HsviewResponse base;

	struct transferDoorbell_SoundVolumeSizeConfigResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} transferDoorbell_SoundVolumeSizeConfigResponse;

C_API transferDoorbell_SoundVolumeSizeConfigResponse *HSAPI_INIT(transferDoorbell_SoundVolumeSizeConfigResponse);

#endif
