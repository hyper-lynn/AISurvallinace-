/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceAuth_AddAuth_H_
#define _HSVIEW_CLIENT_API_deviceAuth_AddAuth_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
   新增授权设备和授权对象
【需要使用平台账号签名】

 */

typedef struct deviceAuth_AddAuthRequest 
{
	HsviewRequest base;

	struct deviceAuth_AddAuthRequestData
	{
		
		/** [long]好友Id */
		DECLARE_LIST(int64) friends;
		/** [long]角色Id */
		int64 roleId;
		/** [long]好友分组Id */
		DECLARE_LIST(int64) groups;
		/** define a list with struct of deviceAuth_AddAuthRequestData_AuthChannelsElement */
		DECLARE_LIST(struct deviceAuth_AddAuthRequestData_AuthChannelsElement
		{
			/** 设备序列号 */
			CSTR deviceCode;
			/** 通道号 */
			CSTR channelId;
		}) authChannels;
		/** 授权名称 */
		CSTR authName;

	} data;

} deviceAuth_AddAuthRequest;

C_API deviceAuth_AddAuthRequest *HSAPI_INIT(deviceAuth_AddAuthRequest);

typedef struct deviceAuth_AddAuthResponse 
{
	HsviewResponse base;

	struct deviceAuth_AddAuthResponseData
	{
		
		/** [long]授权Id */
		int64 id;
 
	} data;

} deviceAuth_AddAuthResponse;

C_API deviceAuth_AddAuthResponse *HSAPI_INIT(deviceAuth_AddAuthResponse);

#endif
