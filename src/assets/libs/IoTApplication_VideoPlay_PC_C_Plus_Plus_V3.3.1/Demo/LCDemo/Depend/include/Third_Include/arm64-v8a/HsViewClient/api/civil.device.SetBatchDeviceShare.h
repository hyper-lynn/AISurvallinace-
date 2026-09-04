/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_SetBatchDeviceShare_H_
#define _HSVIEW_CLIENT_API_SetBatchDeviceShare_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
批量删除或者增加共享给用户的共享设备
username：要共享的用户名
functions：要共享的功能，可选：videoMonitor，videoRecord
activeTime：生效时间，UTC时间戳
operation：0删除，1增加，2更新
【使用平台账号签名】
 */

typedef struct SetBatchDeviceShareRequest 
{
	HsviewRequest base;

	struct SetBatchDeviceShareRequestData
	{
		
		/** 用户名 */
		CSTR username;
		/** 分享的功能，可选项见说明，用逗号分隔 */
		CSTR functions;
		/** [int]操作类型，0删除，1增加 */
		int operation;
		/** [long](废除)分享激活时间，UNIX时间戳，1970年秒数 */
		int64 activeTime;
		/** define a list with struct of SetBatchDeviceShareRequestData_DevicesElement */
		DECLARE_LIST(struct SetBatchDeviceShareRequestData_DevicesElement
		{
			/** 通道号 */
			CSTR channelId;
			/** 设备序列号 */
			CSTR deviceId;
		}) devices;

	} data;

} SetBatchDeviceShareRequest;

C_API SetBatchDeviceShareRequest *HSAPI_INIT(SetBatchDeviceShareRequest);

typedef struct SetBatchDeviceShareResponse 
{
	HsviewResponse base;

	struct SetBatchDeviceShareResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} SetBatchDeviceShareResponse;

C_API SetBatchDeviceShareResponse *HSAPI_INIT(SetBatchDeviceShareResponse);

#endif
