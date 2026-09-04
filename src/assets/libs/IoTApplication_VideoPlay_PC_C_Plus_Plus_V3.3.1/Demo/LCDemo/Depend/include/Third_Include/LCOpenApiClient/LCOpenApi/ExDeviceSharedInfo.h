/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_ExDeviceSharedInfo_H_
#define _LC_OPENAPI_CLIENT_ExDeviceSharedInfo_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
查询设备分享信息，设备拥有者和设备被分享者信息
 */

typedef struct ExDeviceSharedInfoRequest 
{
	LCOpenApiRequest base;

	struct ExDeviceSharedInfoRequestData
	{
		
		/** 授权token */
		CSTR token;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} ExDeviceSharedInfoRequest;

C_API ExDeviceSharedInfoRequest *LCOPENAPI_INIT(ExDeviceSharedInfoRequest);

typedef struct ExDeviceSharedInfoResponse 
{
	LCOpenApiResponse base;

	struct ExDeviceSharedInfoResponseData
	{
		
		/** [O]分享次数，设备或者通道目前分享出去了多少次 */
		CSTR shareCount;
		/** [O]分享者的账号 */
		CSTR ownerAccount;
		/** [O]剩余分享和授权的数量 */
		CSTR leftShareCount;
		/** [O]允许分享数量, 999表示不限制,999表示为vip */
		CSTR allowShareCount;
		/** define a list with struct of ExDeviceSharedInfoResponseData_ShareInfoListElement */
		DECLARE_LIST(struct ExDeviceSharedInfoResponseData_ShareInfoListElement
		{
			/** [O]分享的功能，可选项见说明，用逗号分隔 */
			CSTR functions;
			/** 被分享者的账号状态，registered-账号已经注册，unregistered-账号未注册 */
			CSTR accountStatus;
			/** [O]分享时间，yyyy-MM-dd HH:mm:ss */
			CSTR shareTime;
			/** 被分享者的用户id */
			CSTR userId;
			/** 被分享者的账号 */
			CSTR account;
		}) shareInfoList;
 
	} data;

} ExDeviceSharedInfoResponse;

C_API ExDeviceSharedInfoResponse *LCOPENAPI_INIT(ExDeviceSharedInfoResponse);

#endif
