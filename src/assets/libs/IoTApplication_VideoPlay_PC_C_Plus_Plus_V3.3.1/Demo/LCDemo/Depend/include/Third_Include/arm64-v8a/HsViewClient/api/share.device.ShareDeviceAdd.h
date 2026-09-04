/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_shareDevice_ShareDeviceAdd_H_
#define _HSVIEW_CLIENT_API_shareDevice_ShareDeviceAdd_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
shareInfos不为空
分享设备通道
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
	apManage,配件管理
	
functions为空，取默认值："realtime,videoMonitor,alarmMsg,videoRecord,localVideoRecord"

【使用平台账号签名】
 */

typedef struct shareDevice_ShareDeviceAddRequest 
{
	HsviewRequest base;

	struct shareDevice_ShareDeviceAddRequestData
	{
		
		/** define a list with struct of shareDevice_ShareDeviceAddRequestData_ShareInfosElement */
		DECLARE_LIST(struct shareDevice_ShareDeviceAddRequestData_ShareInfosElement
		{
			/** [O]分享的备注，可选项，海外SMB需求 */
			CSTR remark;
			/** [O]分享的功能，可选项见functions详细描述，用逗号分隔,functions为空，取默认值，全部功能传所有字段 */
			CSTR functions;
			/** 账号类型：phone,email,userId,qrToken,friend;国内只支持userId和qrToken,friendId，userId模式支持批量操作。海外支持userId和email,phone,userName类型，不支持批量;当类别为friendId时，会强校验好友关系 */
			CSTR accountType;
			/** 账号名，手机号、邮箱、用户名、userId，friendId或32位二维码令牌，和accountType匹配 */
			CSTR account;
		}) shareInfos;
		/** [O]通道号，海外分享是按照设备级别的，所以通道号不需要,国内需要 */
		CSTR channelId;
		/** 设备ID */
		CSTR deviceId;

	} data;

} shareDevice_ShareDeviceAddRequest;

C_API shareDevice_ShareDeviceAddRequest *HSAPI_INIT(shareDevice_ShareDeviceAddRequest);

typedef struct shareDevice_ShareDeviceAddResponse 
{
	HsviewResponse base;

	struct shareDevice_ShareDeviceAddResponseData
	{
		
		/** [O]用户ID,请求类型为phone，email时返回,优化APP体验,被分享用户为一个人时返回 */
		CSTR userId;
 
	} data;

} shareDevice_ShareDeviceAddResponse;

C_API shareDevice_ShareDeviceAddResponse *HSAPI_INIT(shareDevice_ShareDeviceAddResponse);

#endif
