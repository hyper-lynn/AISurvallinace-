/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_thingsControl_SetDevKeys_H_
#define _HSVIEW_CLIENT_API_thingsControl_SetDevKeys_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置设备的秘钥: [设置设备的秘钥](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E7%A7%98%E9%92%A5%E7%AE%A1%E7%90%86%2F&s=pd)
计划周期:  [计划周期](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2FHome.md&s=pdeffectPeriod)
【需要使用平台账号签名】
 */

typedef struct thingsControl_SetDevKeysRequest 
{
	HsviewRequest base;

	struct thingsControl_SetDevKeysRequestData
	{
		
		/** password:密码,card:卡,fingerPrint:指纹,face：人脸 */
		CSTR type;
		/** 密码 卡 指纹的唯一标示符 */
		CSTR keyId;
		/** 设备序列号 */
		CSTR deviceId;
		/** 钥匙名称 */
		CSTR name;
		/** [O] 当bHijackAlarm为true时有效 表示用户设置的手机号码 */
		CSTR phone;
		/** [O] 当bHijackAlarm为true时有效 表示用户设置的地理位置 */
		CSTR location;
		/** [bool]是否为劫持报警 true-是 false-否 */
		BOOL bHijackAlarm;
		/** [int]有效时长 单位为天 -1表示永久有效 */
		int effectTime;
		/** define a list with struct of thingsControl_SetDevKeysRequestData_EffectPeriodElement */
		DECLARE_LIST(struct thingsControl_SetDevKeysRequestData_EffectPeriodElement
		{
			/** T112308 结束时间 时间格式为THHMMSS */
			CSTR endTime;
			/** T112208 开始时间 时间格式为THHMMSS */
			CSTR beginTime;
			/** Monday */
			CSTR period;
		}) effectPeriod;

	} data;

} thingsControl_SetDevKeysRequest;

C_API thingsControl_SetDevKeysRequest *HSAPI_INIT(thingsControl_SetDevKeysRequest);

typedef struct thingsControl_SetDevKeysResponse 
{
	HsviewResponse base;

	struct thingsControl_SetDevKeysResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} thingsControl_SetDevKeysResponse;

C_API thingsControl_SetDevKeysResponse *HSAPI_INIT(thingsControl_SetDevKeysResponse);

#endif
