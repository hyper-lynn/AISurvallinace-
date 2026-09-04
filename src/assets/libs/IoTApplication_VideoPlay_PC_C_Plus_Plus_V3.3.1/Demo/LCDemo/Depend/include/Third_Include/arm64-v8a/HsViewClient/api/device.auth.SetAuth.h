/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceAuth_SetAuth_H_
#define _HSVIEW_CLIENT_API_deviceAuth_SetAuth_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
  暂无此接口！
   修改授权设备和授权对象
【需要使用平台账号签名】

 */

typedef struct deviceAuth_SetAuthRequest 
{
	HsviewRequest base;

	struct deviceAuth_SetAuthRequestData
	{
		
		/** define a list with struct of deviceAuth_SetAuthRequestData_AuthChannelsElement */
		DECLARE_LIST(struct deviceAuth_SetAuthRequestData_AuthChannelsElement
		{
			/** 设备序列号 */
			CSTR deviceCode;
			/** 通道号 */
			CSTR channelId;
		}) authChannels;
		/** [long]好友Id */
		DECLARE_LIST(int64) friends;
		/** [long]好友分组Id */
		DECLARE_LIST(int64) groups;
		/** [long]授权Id */
		int64 id;

	} data;

} deviceAuth_SetAuthRequest;

C_API deviceAuth_SetAuthRequest *HSAPI_INIT(deviceAuth_SetAuthRequest);

typedef struct deviceAuth_SetAuthResponse 
{
	HsviewResponse base;

	struct deviceAuth_SetAuthResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} deviceAuth_SetAuthResponse;

C_API deviceAuth_SetAuthResponse *HSAPI_INIT(deviceAuth_SetAuthResponse);

#endif
