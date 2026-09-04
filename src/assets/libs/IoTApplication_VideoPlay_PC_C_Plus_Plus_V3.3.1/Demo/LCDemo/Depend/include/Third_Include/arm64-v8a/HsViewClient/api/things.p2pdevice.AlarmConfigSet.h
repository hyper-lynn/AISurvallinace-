/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_thingsP2pdevice_AlarmConfigSet_H_
#define _HSVIEW_CLIENT_API_thingsP2pdevice_AlarmConfigSet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
P2P设备告警订阅设置
name格式：push- + 设备序列号，比如 "push-3A00044PAK00393"
Code：对应的告警类型
Indexs,对应的通道号

【使用平台账号签名】
 */

typedef struct thingsP2pdevice_AlarmConfigSetRequest 
{
	HsviewRequest base;

	struct thingsP2pdevice_AlarmConfigSetRequestData
	{
		
		/** define a list with struct of thingsP2pdevice_AlarmConfigSetRequestData_ConfigsElement */
		DECLARE_LIST(struct thingsP2pdevice_AlarmConfigSetRequestData_ConfigsElement
		{
			/** [int]索引号 */
			DECLARE_LIST(int) Indexs;
			/** 告警类型，如Motion Detection */
			CSTR Code;
		}) configs;
		/** 配置名称 */
		CSTR name;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} thingsP2pdevice_AlarmConfigSetRequest;

C_API thingsP2pdevice_AlarmConfigSetRequest *HSAPI_INIT(thingsP2pdevice_AlarmConfigSetRequest);

typedef struct thingsP2pdevice_AlarmConfigSetResponse 
{
	HsviewResponse base;

	struct thingsP2pdevice_AlarmConfigSetResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} thingsP2pdevice_AlarmConfigSetResponse;

C_API thingsP2pdevice_AlarmConfigSetResponse *HSAPI_INIT(thingsP2pdevice_AlarmConfigSetResponse);

#endif
