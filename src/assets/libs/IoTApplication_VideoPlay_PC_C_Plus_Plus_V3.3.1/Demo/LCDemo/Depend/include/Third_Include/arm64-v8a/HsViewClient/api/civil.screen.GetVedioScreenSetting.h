/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetVedioScreenSetting_H_
#define _HSVIEW_CLIENT_API_GetVedioScreenSetting_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取用户设置的视频轮巡参数
【使用平台账号签名】
 */

typedef struct GetVedioScreenSettingRequest 
{
	HsviewRequest base;

	struct GetVedioScreenSettingRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} GetVedioScreenSettingRequest;

C_API GetVedioScreenSettingRequest *HSAPI_INIT(GetVedioScreenSettingRequest);

typedef struct GetVedioScreenSettingResponse 
{
	HsviewResponse base;

	struct GetVedioScreenSettingResponseData
	{
		
		/** [int]视频轮巡停留时间，单位秒(s) */
		int stayTime;
		/** [int]视频轮巡分屏数 */
		int screenNum;
 
	} data;

} GetVedioScreenSettingResponse;

C_API GetVedioScreenSettingResponse *HSAPI_INIT(GetVedioScreenSettingResponse);

#endif
