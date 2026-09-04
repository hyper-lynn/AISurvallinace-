/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_dmssManage_UserDeviceDel_H_
#define _HSVIEW_CLIENT_API_dmssManage_UserDeviceDel_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
DMSS删除设备

注意点：
1、did生成规则：1、ddns添加：ddnsdomain_moduletype; 2、序列号添加：sn_moduletype; 3、IP添加：IP_PORT_moduletype; 

【需要使用平台账号签名】
 */

typedef struct dmssManage_UserDeviceDelRequest 
{
	HsviewRequest base;

	struct dmssManage_UserDeviceDelRequestData
	{
		
		/** 平台判断是否同一台设备的标示符（Base64(AES256加密)） */
		CSTR did;

	} data;

} dmssManage_UserDeviceDelRequest;

C_API dmssManage_UserDeviceDelRequest *HSAPI_INIT(dmssManage_UserDeviceDelRequest);

typedef struct dmssManage_UserDeviceDelResponse 
{
	HsviewResponse base;

	struct dmssManage_UserDeviceDelResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} dmssManage_UserDeviceDelResponse;

C_API dmssManage_UserDeviceDelResponse *HSAPI_INIT(dmssManage_UserDeviceDelResponse);

#endif
