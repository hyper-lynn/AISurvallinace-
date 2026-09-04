/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_TransferRenameCollection_H_
#define _HSVIEW_CLIENT_API_TransferRenameCollection_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
重命名收藏点。

注意：客户端协议都是针对单通道的，PASS层协议都是多通道，两者没有必然的联系

transferContent内容说明参考PaaS协议：[重命名收藏点](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E6%94%B6%E8%97%8F%E7%82%B9%E9%85%8D%E7%BD%AE%2F%E9%87%8D%E5%91%BD%E5%90%8D%E8%AE%BE%E5%A4%87%E6%94%B6%E8%97%8F%E7%82%B9.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct TransferRenameCollectionRequest 
{
	HsviewRequest base;

	struct TransferRenameCollectionRequestData
	{
		
		/** struct of TransferRenameCollectionRequestData_TransferContent */
		struct TransferRenameCollectionRequestData_TransferContent {
			/** [int] 通道ID */
			int channelId;
			/** 收藏点新名称 */
			CSTR newName;
			/** 收藏点旧名称 */
			CSTR oldName;
		} transferContent;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} TransferRenameCollectionRequest;

C_API TransferRenameCollectionRequest *HSAPI_INIT(TransferRenameCollectionRequest);

typedef struct TransferRenameCollectionResponse 
{
	HsviewResponse base;

	struct TransferRenameCollectionResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} TransferRenameCollectionResponse;

C_API TransferRenameCollectionResponse *HSAPI_INIT(TransferRenameCollectionResponse);

#endif
