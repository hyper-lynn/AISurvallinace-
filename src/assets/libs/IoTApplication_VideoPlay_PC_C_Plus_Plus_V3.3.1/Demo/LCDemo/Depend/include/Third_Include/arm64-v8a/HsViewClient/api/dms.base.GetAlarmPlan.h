/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetAlarmPlan_H_
#define _HSVIEW_CLIENT_API_GetAlarmPlan_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取设备的报警计划
Mode:对于布防的时间段，填写nervous。
Period:重复周期，	
       everyday：每天 等价于周一到周日
       workday：每个工作日 可以认为等价于周一到周五
       Monday：每周一
       Tuesday：每周二
       Wednesday：每周三
       Thursday：每周四
       Friday：每周五
       Saturday：每周六
       Sunday：每周日
       可使用“Monday, Wednesday, Friday”的方式多选。

【需要使用平台账号签名】
 */

typedef struct GetAlarmPlanRequest 
{
	HsviewRequest base;

	struct GetAlarmPlanRequestData
	{
		
		/** 设备ID */
		CSTR devId;
		/** 通道ID。可以填写通道号或通道对应设备ID */
		CSTR optional;
		/** [cstr]GET */
		#define _STATIC_GetAlarmPlanRequestData_METHOD "GET"
		/** [cstr]scene */
		#define _STATIC_GetAlarmPlanRequestData_CMD "scene"
		/** struct of GetAlarmPlanRequestData_Body */
		struct GetAlarmPlanRequestData_Body {
			/** [int][O]保留 */
			int _nouse;
		} body;

	} data;

} GetAlarmPlanRequest;

C_API GetAlarmPlanRequest *HSAPI_INIT(GetAlarmPlanRequest);

typedef struct GetAlarmPlanResponse 
{
	HsviewResponse base;

	struct GetAlarmPlanResponseData
	{
		
		/** define a list with struct of GetAlarmPlanResponseData_RuleStructElement */
		DECLARE_LIST(struct GetAlarmPlanResponseData_RuleStructElement
		{
			/** 结束时间。格式为时:分:秒 */
			CSTR EndTime;
			/** 模式。nervous警惕模式；private隐私模式；normal普通模式 */
			CSTR Mode;
			/** 重复周期 */
			CSTR Period;
			/** 开始时间。格式为时:分:秒 */
			CSTR BeginTime;
		}) Rule;
 
	} data;

} GetAlarmPlanResponse;

C_API GetAlarmPlanResponse *HSAPI_INIT(GetAlarmPlanResponse);

#endif
