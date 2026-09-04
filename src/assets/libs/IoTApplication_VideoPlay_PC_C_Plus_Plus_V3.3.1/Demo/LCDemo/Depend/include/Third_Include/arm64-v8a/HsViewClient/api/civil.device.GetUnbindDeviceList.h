/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetUnbindDeviceList_H_
#define _HSVIEW_CLIENT_API_GetUnbindDeviceList_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 

获取未绑定的设备列表。获取已注册，但未绑定的设备
请求中的filter字段表示对获取设备的过滤，是一个数组，每个元素代表一个设备ID。

例如：
filter为["ABC123"]时，表示获取ID为ABC123这台未绑定设备的信息。（若这台设备已绑定，则返回空。）

回复字段如下：
deviceId：设备ID
baseline：设备基线类型，详见设备Baseline类型
deviceModel:设备型号
name：设备名称
ability：设备能力选项列表，详见设备能力集选项

NVR/DVR/HCVR/IPC/SD/IHG/ARC : ARC-报警网关


【需要使用平台账号签名】

 */

typedef struct GetUnbindDeviceListRequest 
{
	HsviewRequest base;

	struct GetUnbindDeviceListRequestData
	{
		
		/** 过滤器，每个元素表示要获取的设备ID，数组不能为空 */
		DECLARE_LIST(CSTR) filter;

	} data;

} GetUnbindDeviceListRequest;

C_API GetUnbindDeviceListRequest *HSAPI_INIT(GetUnbindDeviceListRequest);

typedef struct GetUnbindDeviceListResponse 
{
	HsviewResponse base;

	struct GetUnbindDeviceListResponseData
	{
		
		/** define a list with struct of GetUnbindDeviceListResponseData_DevicesElement */
		DECLARE_LIST(struct GetUnbindDeviceListResponseData_DevicesElement
		{
			/** [O]设备品牌信息：lechange-乐橙设备，general-通用设备 */
			CSTR brand;
			/** [O]设备基线类型，详见华视微讯设备协议 */
			CSTR baseline;
			/** [O]设备型号 */
			CSTR deviceModel;
			/** 设备logo图片url */
			CSTR logoUrl;
			/** 设备ID */
			CSTR deviceId;
			/** 设备名称 */
			CSTR name;
			/** [int]当前状态：0-离线，1-在线，3-升级中 */
			int status;
			/** [O]设备能力项，逗号隔开，如AlarmMD,AudioTalk,AlarmPIR,WLAN,VVP2P，详见华视微讯设备协议 */
			CSTR ability;
			/** [O]设备分类【NVR/DVR/HCVR/IPC/SD/IHG/ARC】 */
			CSTR deviceCatalog;
			/** 设备软件版本号 */
			CSTR version;
		}) devices;
 
	} data;

} GetUnbindDeviceListResponse;

C_API GetUnbindDeviceListResponse *HSAPI_INIT(GetUnbindDeviceListResponse);

#endif
