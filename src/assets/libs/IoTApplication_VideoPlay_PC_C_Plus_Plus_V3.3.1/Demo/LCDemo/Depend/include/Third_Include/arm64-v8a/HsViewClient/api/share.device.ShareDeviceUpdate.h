/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_shareDevice_ShareDeviceUpdate_H_
#define _HSVIEW_CLIENT_API_shareDevice_ShareDeviceUpdate_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
PC使用，shareInfos为最终的分享账户列表
更新分享设备通道权限
functions详细描述：
       
	realtime，视频查看权限
	videoMonitor，视频控制权限
	alarmMsg，报警消息查看
	alarmManage，报警消息管理
	localVideoRecord，本地录像查看
	videoRecord，云录像查看
	cloudRecordManage，云录像管理
	configure，基础配置管理
	seniorConfigure，高级配置管理
【使用平台账号签名】
 */

typedef struct shareDevice_ShareDeviceUpdateRequest 
{
	HsviewRequest base;

	struct shareDevice_ShareDeviceUpdateRequestData
	{
		
		/** define a list with struct of shareDevice_ShareDeviceUpdateRequestData_ShareInfosElement */
		DECLARE_LIST(struct shareDevice_ShareDeviceUpdateRequestData_ShareInfosElement
		{
			/** 分享的功能，可选项见说明，用逗号分隔 */
			CSTR functions;
			/** 账号类型：phone,email,userId;国内只支持userId */
			CSTR accountType;
			/** 账号名，手机号、邮箱或userId，和accountType匹配 */
			CSTR account;
		}) shareInfos;
		/** [O]通道号，海外分享是按照设备级别的，所以通道号不需要,国内需要 */
		CSTR channelId;
		/** 设备ID */
		CSTR deviceId;

	} data;

} shareDevice_ShareDeviceUpdateRequest;

C_API shareDevice_ShareDeviceUpdateRequest *HSAPI_INIT(shareDevice_ShareDeviceUpdateRequest);

typedef struct shareDevice_ShareDeviceUpdateResponse 
{
	HsviewResponse base;

	struct shareDevice_ShareDeviceUpdateResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} shareDevice_ShareDeviceUpdateResponse;

C_API shareDevice_ShareDeviceUpdateResponse *HSAPI_INIT(shareDevice_ShareDeviceUpdateResponse);

#endif
