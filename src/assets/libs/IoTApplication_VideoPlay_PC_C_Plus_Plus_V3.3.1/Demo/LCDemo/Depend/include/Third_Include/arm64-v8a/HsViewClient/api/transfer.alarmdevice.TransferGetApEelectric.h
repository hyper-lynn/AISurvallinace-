/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferAlarmdevice_TransferGetApEelectric_H_
#define _HSVIEW_CLIENT_API_transferAlarmdevice_TransferGetApEelectric_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
电量查询


参考PaaS协议：[电量查询](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E6%8A%A5%E8%AD%A6%E7%BD%91%E5%85%B3%2F%E6%93%8D%E4%BD%9C%E9%85%8D%E4%BB%B6%2F%E7%94%B5%E9%87%8F%E6%9F%A5%E8%AF%A2.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferAlarmdevice_TransferGetApEelectricRequest 
{
	HsviewRequest base;

	struct transferAlarmdevice_TransferGetApEelectricRequestData
	{
		
		/** [cstr]/device/alarmdevice/electric/ */
		#define _STATIC_transferAlarmdevice_TransferGetApEelectricRequestData_url "/device/alarmdevice/electric/"
		CSTR url;
		/** 配件序列号 */
		CSTR accessoryId;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferAlarmdevice_TransferGetApEelectricRequest;

C_API transferAlarmdevice_TransferGetApEelectricRequest *HSAPI_INIT(transferAlarmdevice_TransferGetApEelectricRequest);

typedef struct transferAlarmdevice_TransferGetApEelectricResponse 
{
	HsviewResponse base;

	struct transferAlarmdevice_TransferGetApEelectricResponseData
	{
		
		/** [O]电池类型 alkElec、litElec */
		CSTR elecType;
		/** [int]80,电量百分比 */
		int electric;
		/** [O]电池型号，按照国标类型 */
		CSTR elecMode;
 
	} data;

} transferAlarmdevice_TransferGetApEelectricResponse;

C_API transferAlarmdevice_TransferGetApEelectricResponse *HSAPI_INIT(transferAlarmdevice_TransferGetApEelectricResponse);

#endif
