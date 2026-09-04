/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_SetGroupDevices_H_
#define _HSVIEW_CLIENT_API_SetGroupDevices_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
 用户修改分组名称

【需要使用平台账号签名】

 */

typedef struct SetGroupDevicesRequest 
{
	HsviewRequest base;

	struct SetGroupDevicesRequestData
	{
		
		/** [int]操作类型，0删除，1增加 */
		int operation;
		/** define a list with struct of SetGroupDevicesRequestData_DevicesElement */
		DECLARE_LIST(struct SetGroupDevicesRequestData_DevicesElement
		{
			/** 设备编号 */
			CSTR deviceCode;
			/** 通道编号 */
			CSTR channelId;
			/** [int]设备所属标志，0表示用户自己的，1表示别人分享的，2表示别人授权的，其他属于非法请求 */
			int ownerFlag;
		}) devices;
		/** [long]分组id */
		int64 groupId;

	} data;

} SetGroupDevicesRequest;

C_API SetGroupDevicesRequest *HSAPI_INIT(SetGroupDevicesRequest);

typedef struct SetGroupDevicesResponse 
{
	HsviewResponse base;

	struct SetGroupDevicesResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} SetGroupDevicesResponse;

C_API SetGroupDevicesResponse *HSAPI_INIT(SetGroupDevicesResponse);

#endif
