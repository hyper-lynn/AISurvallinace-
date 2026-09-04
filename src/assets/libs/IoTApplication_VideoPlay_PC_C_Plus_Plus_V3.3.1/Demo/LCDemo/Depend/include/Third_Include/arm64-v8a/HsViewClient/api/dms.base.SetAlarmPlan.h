/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_SetAlarmPlan_H_
#define _HSVIEW_CLIENT_API_SetAlarmPlan_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置设备的报警计划
Mode:对于需要布防的时间段，填写nervous。
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

typedef struct SetAlarmPlanRequest 
{
	HsviewRequest base;

	struct SetAlarmPlanRequestData
	{
		
		/** 设备ID */
		CSTR devId;
		/** 通道ID，可以填写通道号或通道对应设备ID */
		CSTR optional;
		/** [cstr]POST */
		#define _STATIC_SetAlarmPlanRequestData_METHOD "POST"
		/** [cstr]scene */
		#define _STATIC_SetAlarmPlanRequestData_CMD "scene"
		/** struct of SetAlarmPlanRequestData_Body */
		struct SetAlarmPlanRequestData_Body {
			/** define a list with struct of SetAlarmPlanRequestData_Body_RuleStructElement */
			DECLARE_LIST(struct SetAlarmPlanRequestData_Body_RuleStructElement
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
		} body;

	} data;

} SetAlarmPlanRequest;

C_API SetAlarmPlanRequest *HSAPI_INIT(SetAlarmPlanRequest);

typedef struct SetAlarmPlanResponse 
{
	HsviewResponse base;

	struct SetAlarmPlanResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} SetAlarmPlanResponse;

C_API SetAlarmPlanResponse *HSAPI_INIT(SetAlarmPlanResponse);

#endif
