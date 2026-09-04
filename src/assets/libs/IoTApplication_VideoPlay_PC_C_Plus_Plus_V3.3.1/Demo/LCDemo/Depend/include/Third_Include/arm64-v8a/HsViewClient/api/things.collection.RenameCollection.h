/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_thingsCollection_RenameCollection_H_
#define _HSVIEW_CLIENT_API_thingsCollection_RenameCollection_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
重命名收藏点。

参考PaaS协议：[重命名收藏点](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E6%94%B6%E8%97%8F%E7%82%B9%E9%85%8D%E7%BD%AE%2F%E9%87%8D%E5%91%BD%E5%90%8D%E8%AE%BE%E5%A4%87%E6%94%B6%E8%97%8F%E7%82%B9.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct thingsCollection_RenameCollectionRequest 
{
	HsviewRequest base;

	struct thingsCollection_RenameCollectionRequestData
	{
		
		/** 收藏点新名称 */
		CSTR newName;
		/** 通道号 */
		CSTR channelId;
		/** 收藏点旧名称 */
		CSTR oldName;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} thingsCollection_RenameCollectionRequest;

C_API thingsCollection_RenameCollectionRequest *HSAPI_INIT(thingsCollection_RenameCollectionRequest);

typedef struct thingsCollection_RenameCollectionResponse 
{
	HsviewResponse base;

	struct thingsCollection_RenameCollectionResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} thingsCollection_RenameCollectionResponse;

C_API thingsCollection_RenameCollectionResponse *HSAPI_INIT(thingsCollection_RenameCollectionResponse);

#endif
