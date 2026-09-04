/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_thingsControl_GetMusic_H_
#define _HSVIEW_CLIENT_API_thingsControl_GetMusic_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取铃声配置及铃声列表。

-------------响应参数说明------------
ringIndex：[int]，用户配置的铃声索引。-1：表示未配置。
index：[int]，歌曲索引，从0开始。
name：[String]，歌曲名称。
--------------

参考PaaS协议：[获取铃声配置及铃声列表](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E9%97%A8%E9%93%83%E7%9B%B8%E5%85%B3%E6%93%8D%E4%BD%9C%2F%E9%93%83%E5%A3%B0%2F%E8%8E%B7%E5%8F%96%E9%93%83%E5%A3%B0%E9%85%8D%E7%BD%AE%E5%8F%8A%E9%93%83%E5%A3%B0%E5%88%97%E8%A1%A8.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct thingsControl_GetMusicRequest 
{
	HsviewRequest base;

	struct thingsControl_GetMusicRequestData
	{
		
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} thingsControl_GetMusicRequest;

C_API thingsControl_GetMusicRequest *HSAPI_INIT(thingsControl_GetMusicRequest);

typedef struct thingsControl_GetMusicResponse 
{
	HsviewResponse base;

	struct thingsControl_GetMusicResponseData
	{
		
		/** define a list with struct of thingsControl_GetMusicResponseData_ListElement */
		DECLARE_LIST(struct thingsControl_GetMusicResponseData_ListElement
		{
			/** [int]歌曲索引，从0开始 */
			int index;
			/** 歌曲名称 */
			CSTR name;
		}) list;
		/** [int]用户配置的铃声索引。-1：表示未配置 */
		int ringIndex;
 
	} data;

} thingsControl_GetMusicResponse;

C_API thingsControl_GetMusicResponse *HSAPI_INIT(thingsControl_GetMusicResponse);

#endif
