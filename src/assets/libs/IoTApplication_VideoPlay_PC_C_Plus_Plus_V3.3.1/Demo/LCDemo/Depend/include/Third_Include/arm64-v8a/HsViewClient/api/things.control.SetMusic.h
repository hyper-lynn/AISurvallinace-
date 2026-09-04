/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_thingsControl_SetMusic_H_
#define _HSVIEW_CLIENT_API_thingsControl_SetMusic_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置铃声。

----------请求参数说明---------
deviceId：[string]，设备序列号；
index：[int]，歌曲索引。
----------

参考PaaS协议：[设置铃声](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E9%97%A8%E9%93%83%E7%9B%B8%E5%85%B3%E6%93%8D%E4%BD%9C%2F%E9%93%83%E5%A3%B0%2F%E8%AE%BE%E7%BD%AE%E9%93%83%E5%A3%B0.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct thingsControl_SetMusicRequest 
{
	HsviewRequest base;

	struct thingsControl_SetMusicRequestData
	{
		
		/** [int]歌曲索引，从0开始 */
		int index;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} thingsControl_SetMusicRequest;

C_API thingsControl_SetMusicRequest *HSAPI_INIT(thingsControl_SetMusicRequest);

typedef struct thingsControl_SetMusicResponse 
{
	HsviewResponse base;

	struct thingsControl_SetMusicResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} thingsControl_SetMusicResponse;

C_API thingsControl_SetMusicResponse *HSAPI_INIT(thingsControl_SetMusicResponse);

#endif
