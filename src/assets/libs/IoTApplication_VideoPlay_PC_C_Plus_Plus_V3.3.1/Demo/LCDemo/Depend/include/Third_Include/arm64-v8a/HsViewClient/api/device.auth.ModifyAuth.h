/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceAuth_ModifyAuth_H_
#define _HSVIEW_CLIENT_API_deviceAuth_ModifyAuth_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
修改授权，包括角色、设备和授权对象

【需要使用平台账号签名】

 */

typedef struct deviceAuth_ModifyAuthRequest 
{
	HsviewRequest base;

	struct deviceAuth_ModifyAuthRequestData
	{
		
		/** [long]好友Id */
		DECLARE_LIST(int64) friends;
		/** [long]角色Id */
		int64 roleId;
		/** [long]好友分组Id */
		DECLARE_LIST(int64) groups;
		/** define a list with struct of deviceAuth_ModifyAuthRequestData_AuthChannelsElement */
		DECLARE_LIST(struct deviceAuth_ModifyAuthRequestData_AuthChannelsElement
		{
			/** 设备序列号 */
			CSTR deviceCode;
			/** 通道号 */
			CSTR channelId;
		}) authChannels;
		/** [long]授权Id */
		int64 id;

	} data;

} deviceAuth_ModifyAuthRequest;

C_API deviceAuth_ModifyAuthRequest *HSAPI_INIT(deviceAuth_ModifyAuthRequest);

typedef struct deviceAuth_ModifyAuthResponse 
{
	HsviewResponse base;

	struct deviceAuth_ModifyAuthResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} deviceAuth_ModifyAuthResponse;

C_API deviceAuth_ModifyAuthResponse *HSAPI_INIT(deviceAuth_ModifyAuthResponse);

#endif
