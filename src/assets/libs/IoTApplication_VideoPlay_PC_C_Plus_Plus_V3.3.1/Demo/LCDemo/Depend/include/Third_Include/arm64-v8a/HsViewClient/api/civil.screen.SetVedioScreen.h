/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_SetVedioScreen_H_
#define _HSVIEW_CLIENT_API_SetVedioScreen_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置视频分屏轮巡的参数。
【使用平台账号签名】
 */

typedef struct SetVedioScreenRequest 
{
	HsviewRequest base;

	struct SetVedioScreenRequestData
	{
		
		/** [int]视频轮巡停留的时间，单位秒(s) */
		int stayTime;
		/** [int]要设置的视频分屏数 */
		int screenNum;

	} data;

} SetVedioScreenRequest;

C_API SetVedioScreenRequest *HSAPI_INIT(SetVedioScreenRequest);

typedef struct SetVedioScreenResponse 
{
	HsviewResponse base;

	struct SetVedioScreenResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} SetVedioScreenResponse;

C_API SetVedioScreenResponse *HSAPI_INIT(SetVedioScreenResponse);

#endif
