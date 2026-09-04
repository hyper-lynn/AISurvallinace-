/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_clientConfig_TabListGet_H_
#define _HSVIEW_CLIENT_API_clientConfig_TabListGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取配置在平台的tab页图标列表。
  
【不需要使用平台账号签名】
 */

typedef struct clientConfig_TabListGetRequest 
{
	HsviewRequest base;

	struct clientConfig_TabListGetRequestData
	{
		
		/** define a list with struct of clientConfig_TabListGetRequestData_TabNameListElement */
		DECLARE_LIST(struct clientConfig_TabListGetRequestData_TabNameListElement
		{
			/** 图标名称位置 */
			CSTR iconNameDefault;
		}) tabNameList;

	} data;

} clientConfig_TabListGetRequest;

C_API clientConfig_TabListGetRequest *HSAPI_INIT(clientConfig_TabListGetRequest);

typedef struct clientConfig_TabListGetResponse 
{
	HsviewResponse base;

	struct clientConfig_TabListGetResponseData
	{
		
		/** define a list with struct of clientConfig_TabListGetResponseData_TabListElement */
		DECLARE_LIST(struct clientConfig_TabListGetResponseData_TabListElement
		{
			/** 图标名称 */
			CSTR iconName;
			/** 图标的图片路径，选中 */
			CSTR iconPicSelected;
			/** 图标的图片路径，未选中 */
			CSTR iconPic;
			/** 图标名称位置 */
			CSTR iconNameDefault;
		}) tabList;
 
	} data;

} clientConfig_TabListGetResponse;

C_API clientConfig_TabListGetResponse *HSAPI_INIT(clientConfig_TabListGetResponse);

#endif
