/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDoorbell_SoundVolumeSizeQuery_H_
#define _HSVIEW_CLIENT_API_transferDoorbell_SoundVolumeSizeQuery_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取音量通用协议

参考PaaS协议：[获取音量通用协议](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E9%97%A8%E9%93%83%E7%9B%B8%E5%85%B3%E6%93%8D%E4%BD%9C%2F%E9%9F%B3%E9%87%8F%2F%E8%8E%B7%E5%8F%96%E9%9F%B3%E9%87%8F%E9%80%9A%E7%94%A8%E5%8D%8F%E8%AE%AE.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferDoorbell_SoundVolumeSizeQueryRequest 
{
	HsviewRequest base;

	struct transferDoorbell_SoundVolumeSizeQueryRequestData
	{
		
		/** [cstr]/device/sound/volume/query */
		#define _STATIC_transferDoorbell_SoundVolumeSizeQueryRequestData_url "/device/sound/volume/query"
		CSTR url;
		/** struct of transferDoorbell_SoundVolumeSizeQueryRequestData_Content */
		struct transferDoorbell_SoundVolumeSizeQueryRequestData_Content {
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

} transferDoorbell_SoundVolumeSizeQueryRequest;

C_API transferDoorbell_SoundVolumeSizeQueryRequest *HSAPI_INIT(transferDoorbell_SoundVolumeSizeQueryRequest);

typedef struct transferDoorbell_SoundVolumeSizeQueryResponse 
{
	HsviewResponse base;

	struct transferDoorbell_SoundVolumeSizeQueryResponseData
	{
		
		/** 音量的大小，单位跟取值范围跟具体类型有关，由客户端跟设备定 */
		CSTR value;
 
	} data;

} transferDoorbell_SoundVolumeSizeQueryResponse;

C_API transferDoorbell_SoundVolumeSizeQueryResponse *HSAPI_INIT(transferDoorbell_SoundVolumeSizeQueryResponse);

#endif
