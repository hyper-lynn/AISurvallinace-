/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_thingsControl_GetDeviceElectric_H_
#define _HSVIEW_CLIENT_API_thingsControl_GetDeviceElectric_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设备电量查询

--------------------请求参数说明---------------------------------------
type：[String]，供电类型，可选。当type为空时，默认为battery类型；
	battery：电池；
	adapter：适配器；
	batteryAdapter：电池+适配器；
"electric":"[int]电量百分比，取值范围0-100；-1:设备无该电池",
"alkElec":"[int]碱性电池电量百分比，取值范围0-100；-1:设备无该电池",
"litElec":"[int]锂电池电量百分比，取值范围0-100；-1:设备无该电池"
------------------------------------------------------------------------

参考PaaS协议：[设备电量查询](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E7%94%B5%E9%87%8F%E8%8E%B7%E5%8F%96%2FReview-%E8%AE%BE%E5%A4%87%E7%94%B5%E9%87%8F%E6%9F%A5%E8%AF%A2.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct thingsControl_GetDeviceElectricRequest 
{
	HsviewRequest base;

	struct thingsControl_GetDeviceElectricRequestData
	{
		
		/** 门锁序列号 */
		CSTR deviceId;

	} data;

} thingsControl_GetDeviceElectricRequest;

C_API thingsControl_GetDeviceElectricRequest *HSAPI_INIT(thingsControl_GetDeviceElectricRequest);

typedef struct thingsControl_GetDeviceElectricResponse 
{
	HsviewResponse base;

	struct thingsControl_GetDeviceElectricResponseData
	{
		
		/** [int]碱性电池电量百分比，取值范围0-100；-1:设备无该电池 */
		int alkElec;
		/** [O]供电类型，当type为空时，默认为battery类型 */
		CSTR type;
		/** [int]锂电池电量百分比，取值范围0-100；-1:设备无该电池 */
		int litElec;
		/** [int]电量百分比，取值范围0-100；-1:设备无该电池 */
		int electric;
 
	} data;

} thingsControl_GetDeviceElectricResponse;

C_API thingsControl_GetDeviceElectricResponse *HSAPI_INIT(thingsControl_GetDeviceElectricResponse);

#endif
