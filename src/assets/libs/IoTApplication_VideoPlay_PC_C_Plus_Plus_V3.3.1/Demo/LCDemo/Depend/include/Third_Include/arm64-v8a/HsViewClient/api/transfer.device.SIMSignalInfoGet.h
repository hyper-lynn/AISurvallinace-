/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDevice_SIMSignalInfoGet_H_
#define _HSVIEW_CLIENT_API_transferDevice_SIMSignalInfoGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取2G4G信号信息

能力集SIMCA

参考PaaS协议：[获取2G4G信号信息](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E8%8E%B7%E5%8F%962G4G%E4%BF%A1%E5%8F%B7%E4%BF%A1%E6%81%AF%2F%E8%8E%B7%E5%8F%962G4G%E4%BF%A1%E5%8F%B7%E4%BF%A1%E6%81%AF.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferDevice_SIMSignalInfoGetRequest 
{
	HsviewRequest base;

	struct transferDevice_SIMSignalInfoGetRequestData
	{
		
		/** 设备序列号 */
		CSTR deviceId;
		/** [cstr]/device/2G4G/query */
		#define _STATIC_transferDevice_SIMSignalInfoGetRequestData_url "/device/2G4G/query"
		CSTR url;

	} data;

} transferDevice_SIMSignalInfoGetRequest;

C_API transferDevice_SIMSignalInfoGetRequest *HSAPI_INIT(transferDevice_SIMSignalInfoGetRequest);

typedef struct transferDevice_SIMSignalInfoGetResponse 
{
	HsviewResponse base;

	struct transferDevice_SIMSignalInfoGetResponseData
	{
		
		/** 强度。单位为dbm */
		CSTR sigStrength;
		/** 类型，枚举值为2G、4G、NOSIM */
		CSTR type;
		/** 强度。0最弱，5最强 */
		CSTR intensity;
 
	} data;

} transferDevice_SIMSignalInfoGetResponse;

C_API transferDevice_SIMSignalInfoGetResponse *HSAPI_INIT(transferDevice_SIMSignalInfoGetResponse);

#endif
