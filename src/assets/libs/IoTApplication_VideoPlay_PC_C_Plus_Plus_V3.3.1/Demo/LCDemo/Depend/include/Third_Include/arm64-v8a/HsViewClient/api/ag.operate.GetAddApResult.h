/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_agOperate_GetAddApResult_H_
#define _HSVIEW_CLIENT_API_agOperate_GetAddApResult_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
报警配件操作接口


获取报警网关配件相关功能的使能

【需要使用平台账号签名】
 */

typedef struct agOperate_GetAddApResultRequest 
{
	HsviewRequest base;

	struct agOperate_GetAddApResultRequestData
	{
		
		/** 配件ID */
		CSTR apId;
		/** 网关的设备ID */
		CSTR deviceId;

	} data;

} agOperate_GetAddApResultRequest;

C_API agOperate_GetAddApResultRequest *HSAPI_INIT(agOperate_GetAddApResultRequest);

typedef struct agOperate_GetAddApResultResponse 
{
	HsviewResponse base;

	struct agOperate_GetAddApResultResponseData
	{
		
		/** [bool]配件是否存在（配件是否上报了硬件信息） */
		BOOL isExist;
		/** [O]海外为配件市场型号，国内为配件上报型号 */
		CSTR apModel;
		/** [O]配件名称 */
		CSTR apName;
		/** [O]配件的使能:on-使能开启 ，off-使能关闭 */
		CSTR apEnable;
		/** [O]配件的能力集，逗号隔开，如ModifyName,LinkageSiren,SASQ,XUpgrade,ElecInfo,SigInfo,NoPlan */
		CSTR apCapacity;
		/** [O]配件的类型 */
		CSTR apType;
		/** [int][O]配件的在线状态：1-在线  0-离线 -1-异常(可升级状态) */
		int apStatus;
		/** [int][O]配件输入输出类型，-1:未知 0-输入 1-输出 */
		int ioType;
		/** [O]配件的市场型号 */
		CSTR apModelName;
		/** [O]配件的版本号 */
		CSTR apVersion;
 
	} data;

} agOperate_GetAddApResultResponse;

C_API agOperate_GetAddApResultResponse *HSAPI_INIT(agOperate_GetAddApResultResponse);

#endif
