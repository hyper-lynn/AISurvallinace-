/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_SetDeviceShare_H_
#define _HSVIEW_CLIENT_API_SetDeviceShare_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置设备共享规则。
username：要共享的用户名
functions：要共享的功能，可选：realtime(视频查看),videoMonitor(视频控制)，configure(基础配置管理)，alarmMsg(报警消息查看)，videoRecord(云录像查看),localVideoRecord(本地录像查看),cloudRecordManage(云录像管理),seniorConfigure(高级配置管理)
activeTime：生效时间，UTC时间戳
operation：0删除，1增加，2更新
【使用平台账号签名】
 */

typedef struct SetDeviceShareRequest 
{
	HsviewRequest base;

	struct SetDeviceShareRequestData
	{
		
		/** define a list with struct of SetDeviceShareRequestData_ShareInfosElement */
		DECLARE_LIST(struct SetDeviceShareRequestData_ShareInfosElement
		{
			/** 用户名 */
			CSTR username;
			/** [int]操作类型，0删除，1增加，2更新 */
			int operation;
			/** [long]分享激活时间，UNIX时间戳，1970年秒数 */
			int64 activeTime;
			/** 分享的功能，可选项见说明，用逗号分隔 */
			CSTR functions;
		}) shareInfos;
		/** 通道号 */
		CSTR channelId;
		/** 设备ID */
		CSTR deviceId;

	} data;

} SetDeviceShareRequest;

C_API SetDeviceShareRequest *HSAPI_INIT(SetDeviceShareRequest);

typedef struct SetDeviceShareResponse 
{
	HsviewResponse base;

	struct SetDeviceShareResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} SetDeviceShareResponse;

C_API SetDeviceShareResponse *HSAPI_INIT(SetDeviceShareResponse);

#endif
