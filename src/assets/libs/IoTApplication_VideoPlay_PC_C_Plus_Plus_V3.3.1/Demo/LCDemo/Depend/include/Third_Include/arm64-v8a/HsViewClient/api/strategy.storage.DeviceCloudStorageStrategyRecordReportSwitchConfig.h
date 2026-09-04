/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_strategyStorage_DeviceCloudStorageStrategyRecordReportSwitchConfig_H_
#define _HSVIEW_CLIENT_API_strategyStorage_DeviceCloudStorageStrategyRecordReportSwitchConfig_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
开启暂停套餐对应的云录像上报开关

【使用平台账号签名】
 */

typedef struct strategyStorage_DeviceCloudStorageStrategyRecordReportSwitchConfigRequest 
{
	HsviewRequest base;

	struct strategyStorage_DeviceCloudStorageStrategyRecordReportSwitchConfigRequestData
	{
		
		/** on：云录像开启，off 云录像关闭 */
		CSTR recordSwitchStatus;
		/** 设备通道号 */
		CSTR channelId;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} strategyStorage_DeviceCloudStorageStrategyRecordReportSwitchConfigRequest;

C_API strategyStorage_DeviceCloudStorageStrategyRecordReportSwitchConfigRequest *HSAPI_INIT(strategyStorage_DeviceCloudStorageStrategyRecordReportSwitchConfigRequest);

typedef struct strategyStorage_DeviceCloudStorageStrategyRecordReportSwitchConfigResponse 
{
	HsviewResponse base;

	struct strategyStorage_DeviceCloudStorageStrategyRecordReportSwitchConfigResponseData
	{
		
		/** success: 操作成功， notExist：操作失败，未开通套餐，expired：操作失败，套餐已经过期 */
		CSTR result;
 
	} data;

} strategyStorage_DeviceCloudStorageStrategyRecordReportSwitchConfigResponse;

C_API strategyStorage_DeviceCloudStorageStrategyRecordReportSwitchConfigResponse *HSAPI_INIT(strategyStorage_DeviceCloudStorageStrategyRecordReportSwitchConfigResponse);

#endif
