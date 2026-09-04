/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_thingsP2pdevice_AlarmConfigGet_H_
#define _HSVIEW_CLIENT_API_thingsP2pdevice_AlarmConfigGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
P2P设备告警订阅查询
name格式：push- + 设备序列号，比如 "push-3A00044PAK00393"，
返回的数据为空，或者Indexs为空，表示对应的开关关闭，有值，表示对应的通道号开关开启
【使用平台账号签名】
 */

typedef struct thingsP2pdevice_AlarmConfigGetRequest 
{
	HsviewRequest base;

	struct thingsP2pdevice_AlarmConfigGetRequestData
	{
		
		/** 配置名称 */
		CSTR name;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} thingsP2pdevice_AlarmConfigGetRequest;

C_API thingsP2pdevice_AlarmConfigGetRequest *HSAPI_INIT(thingsP2pdevice_AlarmConfigGetRequest);

typedef struct thingsP2pdevice_AlarmConfigGetResponse 
{
	HsviewResponse base;

	struct thingsP2pdevice_AlarmConfigGetResponseData
	{
		
		/** define a list with struct of thingsP2pdevice_AlarmConfigGetResponseData_ConfigsElement */
		DECLARE_LIST(struct thingsP2pdevice_AlarmConfigGetResponseData_ConfigsElement
		{
			/** [int]索引号 */
			DECLARE_LIST(int) Indexs;
			/** 告警类型，如Motion Detection */
			CSTR Code;
		}) configs;
 
	} data;

} thingsP2pdevice_AlarmConfigGetResponse;

C_API thingsP2pdevice_AlarmConfigGetResponse *HSAPI_INIT(thingsP2pdevice_AlarmConfigGetResponse);

#endif
