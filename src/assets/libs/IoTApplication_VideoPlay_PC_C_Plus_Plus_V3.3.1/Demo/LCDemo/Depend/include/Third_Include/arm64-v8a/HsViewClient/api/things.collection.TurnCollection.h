/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_thingsCollection_TurnCollection_H_
#define _HSVIEW_CLIENT_API_thingsCollection_TurnCollection_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
转动到某个收藏点

参考PaaS协议：[转动到某个收藏点](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E6%94%B6%E8%97%8F%E7%82%B9%E9%85%8D%E7%BD%AE%2F%E8%BD%AC%E5%8A%A8%E5%88%B0%E6%9F%90%E4%B8%AA%E6%94%B6%E8%97%8F%E7%82%B9.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct thingsCollection_TurnCollectionRequest 
{
	HsviewRequest base;

	struct thingsCollection_TurnCollectionRequestData
	{
		
		/** 通道号 */
		CSTR channelId;
		/** collection-1 */
		CSTR name;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} thingsCollection_TurnCollectionRequest;

C_API thingsCollection_TurnCollectionRequest *HSAPI_INIT(thingsCollection_TurnCollectionRequest);

typedef struct thingsCollection_TurnCollectionResponse 
{
	HsviewResponse base;

	struct thingsCollection_TurnCollectionResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} thingsCollection_TurnCollectionResponse;

C_API thingsCollection_TurnCollectionResponse *HSAPI_INIT(thingsCollection_TurnCollectionResponse);

#endif
