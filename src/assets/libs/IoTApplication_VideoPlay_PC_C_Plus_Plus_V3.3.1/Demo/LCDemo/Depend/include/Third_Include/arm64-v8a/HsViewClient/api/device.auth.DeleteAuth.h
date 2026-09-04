/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceAuth_DeleteAuth_H_
#define _HSVIEW_CLIENT_API_deviceAuth_DeleteAuth_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
暂无此接口！
   删除授权设备
【需要使用平台账号签名】

 */

typedef struct deviceAuth_DeleteAuthRequest 
{
	HsviewRequest base;

	struct deviceAuth_DeleteAuthRequestData
	{
		
		/** define a list with struct of deviceAuth_DeleteAuthRequestData_AuthChannelsElement */
		DECLARE_LIST(struct deviceAuth_DeleteAuthRequestData_AuthChannelsElement
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

} deviceAuth_DeleteAuthRequest;

C_API deviceAuth_DeleteAuthRequest *HSAPI_INIT(deviceAuth_DeleteAuthRequest);

typedef struct deviceAuth_DeleteAuthResponse 
{
	HsviewResponse base;

	struct deviceAuth_DeleteAuthResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} deviceAuth_DeleteAuthResponse;

C_API deviceAuth_DeleteAuthResponse *HSAPI_INIT(deviceAuth_DeleteAuthResponse);

#endif
