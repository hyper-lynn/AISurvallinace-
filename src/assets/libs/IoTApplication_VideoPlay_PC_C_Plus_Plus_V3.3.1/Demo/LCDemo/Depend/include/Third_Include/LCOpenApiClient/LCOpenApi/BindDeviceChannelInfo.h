/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_BindDeviceChannelInfo_H_
#define _LC_OPENAPI_CLIENT_BindDeviceChannelInfo_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取单个设备通道的信息

 */

typedef struct BindDeviceChannelInfoRequest 
{
	LCOpenApiRequest base;

	struct BindDeviceChannelInfoRequestData
	{
		
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 通道ID */
		CSTR channelId;
		/** [cstr]bindDeviceChannelInfo */
		#define _STATIC_BindDeviceChannelInfoRequestData_method "bindDeviceChannelInfo"
		CSTR method;
		/** 设备ID */
		CSTR deviceId;

	} data;

} BindDeviceChannelInfoRequest;

C_API BindDeviceChannelInfoRequest *LCOPENAPI_INIT(BindDeviceChannelInfoRequest);

typedef struct BindDeviceChannelInfoResponse 
{
	LCOpenApiResponse base;

	struct BindDeviceChannelInfoResponseData
	{
		
		/** [int]报警布撤防状态，0-撤防，1-布防 */
		int alarmStatus;
		/** [int]云存储状态：-1-未开通 0-已失效 1-使用中 2-套餐暂停 */
		int csStatus;
		/** 设备ID */
		CSTR deviceId;
		/** 通道名称 */
		CSTR channelName;
		/** 可选,被共享和授权的权限功能列表（逗号隔开） */
		CSTR shareFunctions;
		/** 通道能力集，逗号隔开 */
		CSTR channelAbility;
		/** 缩略图URL */
		CSTR channelPicUrl;
		/** [int]通道号 */
		int channelId;
		/** [bool]是否在线 */
		BOOL channelOnline;
		/** [bool]是否分享给别人的,true表示分享给了别人,false表示未分享给别人 */
		BOOL shareStatus;
 
	} data;

} BindDeviceChannelInfoResponse;

C_API BindDeviceChannelInfoResponse *LCOPENAPI_INIT(BindDeviceChannelInfoResponse);

#endif
