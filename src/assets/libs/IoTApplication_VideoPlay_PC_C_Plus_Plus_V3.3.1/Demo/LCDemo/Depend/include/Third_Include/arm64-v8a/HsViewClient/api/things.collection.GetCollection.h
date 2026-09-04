/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_thingsCollection_GetCollection_H_
#define _HSVIEW_CLIENT_API_thingsCollection_GetCollection_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取收藏点。

注意：客户端协议都是针对单通道的，PASS层协议都是多通道，两者没有必然的联系

参考PaaS协议：[获取设备收藏点](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E6%94%B6%E8%97%8F%E7%82%B9%E9%85%8D%E7%BD%AE%2F%E8%8E%B7%E5%8F%96%E8%AE%BE%E5%A4%87%E6%94%B6%E8%97%8F%E7%82%B9.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct thingsCollection_GetCollectionRequest 
{
	HsviewRequest base;

	struct thingsCollection_GetCollectionRequestData
	{
		
		/** 通道号 */
		CSTR channelId;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} thingsCollection_GetCollectionRequest;

C_API thingsCollection_GetCollectionRequest *HSAPI_INIT(thingsCollection_GetCollectionRequest);

typedef struct thingsCollection_GetCollectionResponse 
{
	HsviewResponse base;

	struct thingsCollection_GetCollectionResponseData
	{
		
		/** define a list with struct of thingsCollection_GetCollectionResponseData_CollectionsElement */
		DECLARE_LIST(struct thingsCollection_GetCollectionResponseData_CollectionsElement
		{
			/** [int]停留时间，单位S。可选，为空时，以设备默认值为准 */
			int stayTime;
			/** 收藏点名称 */
			CSTR name;
			/** [O]收藏点图片路径 */
			CSTR picUrl;
		}) collections;
 
	} data;

} thingsCollection_GetCollectionResponse;

C_API thingsCollection_GetCollectionResponse *HSAPI_INIT(thingsCollection_GetCollectionResponse);

#endif
