/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_shareDevice_ShareDeviceDelete_H_
#define _HSVIEW_CLIENT_API_shareDevice_ShareDeviceDelete_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
shareInfos不为空
注：国内逻辑，若shareInfos没有则表示删除该通道的全部分享信息

根据设备序列号和通道号取消分享设备通道

【使用平台账号签名】
 */

typedef struct shareDevice_ShareDeviceDeleteRequest 
{
	HsviewRequest base;

	struct shareDevice_ShareDeviceDeleteRequestData
	{
		
		/** define a list with struct of shareDevice_ShareDeviceDeleteRequestData_ShareInfosElement */
		DECLARE_LIST(struct shareDevice_ShareDeviceDeleteRequestData_ShareInfosElement
		{
			/** [O]分享的功能，可选项见说明，用逗号分隔 */
			CSTR functions;
			/** 账号类型：当前仅支持userId,海外不支持批量操作 */
			CSTR accountType;
			/** userId，和accountType匹配 */
			CSTR account;
		}) shareInfos;
		/** [O]通道号，海外分享是按照设备级别的，所以通道号不需要,国内需要 */
		CSTR channelId;
		/** 设备ID */
		CSTR deviceId;

	} data;

} shareDevice_ShareDeviceDeleteRequest;

C_API shareDevice_ShareDeviceDeleteRequest *HSAPI_INIT(shareDevice_ShareDeviceDeleteRequest);

typedef struct shareDevice_ShareDeviceDeleteResponse 
{
	HsviewResponse base;

	struct shareDevice_ShareDeviceDeleteResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} shareDevice_ShareDeviceDeleteResponse;

C_API shareDevice_ShareDeviceDeleteResponse *HSAPI_INIT(shareDevice_ShareDeviceDeleteResponse);

#endif
