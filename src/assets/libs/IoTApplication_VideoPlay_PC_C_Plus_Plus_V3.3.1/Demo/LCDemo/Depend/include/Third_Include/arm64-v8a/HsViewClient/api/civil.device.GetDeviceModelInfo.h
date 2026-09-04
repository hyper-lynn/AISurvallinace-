/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetDeviceModelInfo_H_
#define _HSVIEW_CLIENT_API_GetDeviceModelInfo_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取指定设备型号的相关信息。

字段说明：
	wifiConfigMode可选字段有：
		SmartConfig：SmartConfig方式
		SoundWave：声波方式
		SoftAP：软AP方式
		LAN：有线局域网
		SIMCard:SIM卡方式
	wifiTransferMode可选字段有：
		2.4Ghz
		5Ghz
	faqs:绑定流程提示信息

【无需签名认证】
 */

typedef struct GetDeviceModelInfoRequest 
{
	HsviewRequest base;

	struct GetDeviceModelInfoRequestData
	{
		
		/** 设备内部型号 */
		CSTR deviceModel;

	} data;

} GetDeviceModelInfoRequest;

C_API GetDeviceModelInfoRequest *HSAPI_INIT(GetDeviceModelInfoRequest);

typedef struct GetDeviceModelInfoResponse 
{
	HsviewResponse base;

	struct GetDeviceModelInfoResponseData
	{
		
		/** 设备品牌信息：lechange-乐橙设备，general-通用设备 */
		CSTR brand;
		/** [int]分类： 0-设备,1-配件  */
		int type;
		/** define a list with struct of GetDeviceModelInfoResponseData_FaqsElement */
		DECLARE_LIST(struct GetDeviceModelInfoResponseData_FaqsElement
		{
			/** 文字说明 */
			CSTR caption;
			/** 帮助图片url */
			CSTR picUrl;
			/** [O]更多说明 */
			CSTR furtherHelp;
		}) faqs;
		/** define a list with struct of GetDeviceModelInfoResponseData_MoreDescElement */
		DECLARE_LIST(struct GetDeviceModelInfoResponseData_MoreDescElement
		{
			/** 帮助图片url */
			CSTR picUrl;
			/** 文字说明 */
			CSTR caption;
		}) moreDesc;
		/** 该型号对应的设备logo图片url */
		CSTR logoUrl;
		/** 设备支持的WIFI配置方式数组，可有多种方式，以排在前面的方式为优先 */
		DECLARE_LIST(CSTR) wifiConfigMode;
		/** 设备支持的wifi通信频段，支持多种频段，以逗号隔开，如2.4Ghz,5Ghz */
		CSTR wifiTransferMode;
		/** 设备分类【NVR/DVR/HCVR/IPC/SD/IHG】 */
		CSTR deviceCatalog;
		/** 型号名称（设备外部型号） */
		CSTR modelName;
 
	} data;

} GetDeviceModelInfoResponse;

C_API GetDeviceModelInfoResponse *HSAPI_INIT(GetDeviceModelInfoResponse);

#endif
