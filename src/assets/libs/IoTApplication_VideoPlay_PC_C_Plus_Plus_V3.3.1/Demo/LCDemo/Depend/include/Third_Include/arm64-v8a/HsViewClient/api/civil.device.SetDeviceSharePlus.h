/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_SetDeviceSharePlus_H_
#define _HSVIEW_CLIENT_API_SetDeviceSharePlus_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置设备共享规则。
functions：要共享的功能，可选：realtime(视频查看),videoMonitor(视频控制)，configure(基础配置管理)，alarmMsg(报警消息查看)，videoRecord(云录像查看),localVideoRecord(本地录像查看),cloudRecordManage(云录像管理),seniorConfigure(高级配置管理)
activeTime：生效时间，UTC时间戳
operation：0删除，1增加，2更新
【使用平台账号签名】
 */

typedef struct SetDeviceSharePlusRequest 
{
	HsviewRequest base;

	struct SetDeviceSharePlusRequestData
	{
		
		/** define a list with struct of SetDeviceSharePlusRequestData_ShareInfosElement */
		DECLARE_LIST(struct SetDeviceSharePlusRequestData_ShareInfosElement
		{
			/** [int]操作类型，0删除，1增加，2更新 */
			int operation;
			/** [long]分享激活时间，UNIX时间戳，1970年秒数 */
			int64 activeTime;
			/** 用户ID */
			CSTR userId;
			/** 分享的功能，可选项见说明，用逗号分隔 */
			CSTR functions;
		}) shareInfos;
		/** 通道号 */
		CSTR channelId;
		/** 设备ID */
		CSTR deviceId;

	} data;

} SetDeviceSharePlusRequest;

C_API SetDeviceSharePlusRequest *HSAPI_INIT(SetDeviceSharePlusRequest);

typedef struct SetDeviceSharePlusResponse 
{
	HsviewResponse base;

	struct SetDeviceSharePlusResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} SetDeviceSharePlusResponse;

C_API SetDeviceSharePlusResponse *HSAPI_INIT(SetDeviceSharePlusResponse);

#endif
