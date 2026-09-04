/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_clientConfig_IntroductionInfosGetByLanguageModel_H_
#define _HSVIEW_CLIENT_API_clientConfig_IntroductionInfosGetByLanguageModel_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
一键oem协议，拉取添加流程引导页配置信息(除语言外，使用clientUA内的)

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
	
App 5.0 update:对于未查询到任何添加流程配置的设备型号，将返回所有默认添加流程

【使用平台账号签名】
 */

typedef struct clientConfig_IntroductionInfosGetByLanguageModelRequest 
{
	HsviewRequest base;

	struct clientConfig_IntroductionInfosGetByLanguageModelRequestData
	{
		
		/** 语言类型：'zh_CN'；'en_US' etc.详见下面描述说明 */
		CSTR language;
		/** APP展示的设备型号名称（产品称之为市场型号） */
		CSTR deviceModelName;

	} data;

} clientConfig_IntroductionInfosGetByLanguageModelRequest;

C_API clientConfig_IntroductionInfosGetByLanguageModelRequest *HSAPI_INIT(clientConfig_IntroductionInfosGetByLanguageModelRequest);

typedef struct clientConfig_IntroductionInfosGetByLanguageModelResponse 
{
	HsviewResponse base;

	struct clientConfig_IntroductionInfosGetByLanguageModelResponseData
	{
		
		/** define a list with struct of clientConfig_IntroductionInfosGetByLanguageModelResponseData_IntroductionsElement */
		DECLARE_LIST(struct clientConfig_IntroductionInfosGetByLanguageModelResponseData_IntroductionsElement
		{
			/** 引导提示内容 */
			CSTR introductionContent;
			/** 引导提示名称，app自定义，用于区分，统计好后发给平台录入 */
			CSTR introductionName;
		}) introductions;
		/** define a list with struct of clientConfig_IntroductionInfosGetByLanguageModelResponseData_ImagesElement */
		DECLARE_LIST(struct clientConfig_IntroductionInfosGetByLanguageModelResponseData_ImagesElement
		{
			/** 图片名称，app自定义，用于区分，统计好后发给平台录入 */
			CSTR imageName;
			/** 图片下载地址uri，oms提供上传图片服务，保存uri */
			CSTR imageURI;
		}) images;
		/** 配置的更新时间，oms更新修改时记录 */
		CSTR updateTime;
 
	} data;

} clientConfig_IntroductionInfosGetByLanguageModelResponse;

C_API clientConfig_IntroductionInfosGetByLanguageModelResponse *HSAPI_INIT(clientConfig_IntroductionInfosGetByLanguageModelResponse);

#endif
