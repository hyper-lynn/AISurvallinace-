/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_thingsControl_GetGear_H_
#define _HSVIEW_CLIENT_API_thingsControl_GetGear_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
白光灯亮度/补光灯灵敏度，获取档位信息。

----------------响应参数说明-----------
type：[string]，档位类型，bright--亮度--C26E白光灯亮度/fls--补光灯灵敏度--TF1D补光灯灵敏度(Fill light sensitivity)
sn：deviceId代表的设备通道下关联的设备序列号
chan：设备通道号
设备级操作，chan，sn不需要设置
通道级操作，当sn，chan都下发时，优先sn。需要设备有对应II类能力：白光灯亮度调节--ChanWL/补光灯灵敏--LEDS。

参考PaaS协议：[档位类型定义](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E6%A1%A3%E4%BD%8D%E8%AE%BE%E7%BD%AE%2FHome.md&s=pd)
value：[int]，档位值，所有档位值都被抽象成取值范围为0~100之间的百分比。
---------------------------------------

参考PaaS协议：[档位获取](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E6%A1%A3%E4%BD%8D%E8%AE%BE%E7%BD%AE%2F%E6%A1%A3%E4%BD%8D%E8%8E%B7%E5%8F%96.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct thingsControl_GetGearRequest 
{
	HsviewRequest base;

	struct thingsControl_GetGearRequestData
	{
		
		/** [O]设备序列号 */
		CSTR sn;
		/** 档位类型数组 */
		DECLARE_LIST(CSTR) type;
		/** [O]通道,不存在默认为设备 */
		CSTR chan;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} thingsControl_GetGearRequest;

C_API thingsControl_GetGearRequest *HSAPI_INIT(thingsControl_GetGearRequest);

typedef struct thingsControl_GetGearResponse 
{
	HsviewResponse base;

	struct thingsControl_GetGearResponseData
	{
		
		/** define a list with struct of thingsControl_GetGearResponseData_GearElement */
		DECLARE_LIST(struct thingsControl_GetGearResponseData_GearElement
		{
			/** [int]档位值 */
			int value;
			/** 档位类型 */
			CSTR type;
		}) gear;
 
	} data;

} thingsControl_GetGearResponse;

C_API thingsControl_GetGearResponse *HSAPI_INIT(thingsControl_GetGearResponse);

#endif
