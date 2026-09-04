/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDoorbell_MusicVolumeSizeQuery_H_
#define _HSVIEW_CLIENT_API_transferDoorbell_MusicVolumeSizeQuery_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取音量

参考PaaS协议：[获取音量](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E9%97%A8%E9%93%83%E7%9B%B8%E5%85%B3%E6%93%8D%E4%BD%9C%2F%E9%9F%B3%E9%87%8F%2F%E8%8E%B7%E5%8F%96%E9%9F%B3%E9%87%8F.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferDoorbell_MusicVolumeSizeQueryRequest 
{
	HsviewRequest base;

	struct transferDoorbell_MusicVolumeSizeQueryRequestData
	{
		
		/** 设备序列号 */
		CSTR deviceId;
		/** [cstr]/device/ring/music/size/query */
		#define _STATIC_transferDoorbell_MusicVolumeSizeQueryRequestData_url "/device/ring/music/size/query"
		CSTR url;

	} data;

} transferDoorbell_MusicVolumeSizeQueryRequest;

C_API transferDoorbell_MusicVolumeSizeQueryRequest *HSAPI_INIT(transferDoorbell_MusicVolumeSizeQueryRequest);

typedef struct transferDoorbell_MusicVolumeSizeQueryResponse 
{
	HsviewResponse base;

	struct transferDoorbell_MusicVolumeSizeQueryResponseData
	{
		
		/** [int]音量大小的百分比，有效值[0, 100] */
		int percent;
 
	} data;

} transferDoorbell_MusicVolumeSizeQueryResponse;

C_API transferDoorbell_MusicVolumeSizeQueryResponse *HSAPI_INIT(transferDoorbell_MusicVolumeSizeQueryResponse);

#endif
