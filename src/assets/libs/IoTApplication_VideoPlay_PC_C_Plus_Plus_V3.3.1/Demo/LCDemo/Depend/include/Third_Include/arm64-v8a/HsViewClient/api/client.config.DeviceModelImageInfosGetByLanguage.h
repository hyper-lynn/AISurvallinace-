/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_clientConfig_DeviceModelImageInfosGetByLanguage_H_
#define _HSVIEW_CLIENT_API_clientConfig_DeviceModelImageInfosGetByLanguage_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
一键oem协议，拉取设备型号配置信息(除语言外，使用clientUA内的)

language格式定义及说明(http://www.lingoes.net/en/translator/langcode.htm)：
1、格式：
	language_region(或者language-region)
	语言文字种类_国家和地区
2、说明：
	语言文字种类:按ISO 639-1  标准(2字节)
	国家和地区:  按ISO 3166-1 标准(2字节)
3、eg.
	zh_CN或者zh-CN
	en_US或者en-US 

【使用平台账号签名】
 */

typedef struct clientConfig_DeviceModelImageInfosGetByLanguageRequest 
{
	HsviewRequest base;

	struct clientConfig_DeviceModelImageInfosGetByLanguageRequestData
	{
		
		/** 语言类型：'zh_CN'；'en_US' etc.详见下面描述说明 */
		CSTR language;

	} data;

} clientConfig_DeviceModelImageInfosGetByLanguageRequest;

C_API clientConfig_DeviceModelImageInfosGetByLanguageRequest *HSAPI_INIT(clientConfig_DeviceModelImageInfosGetByLanguageRequest);

typedef struct clientConfig_DeviceModelImageInfosGetByLanguageResponse 
{
	HsviewResponse base;

	struct clientConfig_DeviceModelImageInfosGetByLanguageResponseData
	{
		
		/** define a list with struct of clientConfig_DeviceModelImageInfosGetByLanguageResponseData_DeviceTypeConfigsElement */
		DECLARE_LIST(struct clientConfig_DeviceModelImageInfosGetByLanguageResponseData_DeviceTypeConfigsElement
		{
			/** define a list with struct of clientConfig_DeviceModelImageInfosGetByLanguageResponseData_DeviceTypeConfigsElement_DevicesElement */
			DECLARE_LIST(struct clientConfig_DeviceModelImageInfosGetByLanguageResponseData_DeviceTypeConfigsElement_DevicesElement
			{
				/** 设备正视图（图片尺寸参考UI）的URI */
				CSTR deviceImageURI;
				/** APP展示的设备型号名称（产品称之为市场型号） */
				CSTR deviceModelName;
			}) devices;
			/** 分类名称，摄像机Camera, 门锁DoorBell, 报警器AlarmDevice, 网关Gateway, 硬盘录像机DVR */
			CSTR deviceType;
		}) deviceTypeConfigs;
		/** 配置的更新时间，oms更新修改时记录 */
		CSTR updateTime;
 
	} data;

} clientConfig_DeviceModelImageInfosGetByLanguageResponse;

C_API clientConfig_DeviceModelImageInfosGetByLanguageResponse *HSAPI_INIT(clientConfig_DeviceModelImageInfosGetByLanguageResponse);

#endif
