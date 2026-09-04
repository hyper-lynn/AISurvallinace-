/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_TransferDeleteCollection_H_
#define _HSVIEW_CLIENT_API_TransferDeleteCollection_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
删除收藏点。可以批量

注意：客户端协议都是针对单通道的，PASS层协议都是多通道，两者没有必然的联系

transferContent内容说明参考PaaS协议：[删除设备收藏点](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E6%94%B6%E8%97%8F%E7%82%B9%E9%85%8D%E7%BD%AE%2F%E5%88%A0%E9%99%A4%E8%AE%BE%E5%A4%87%E6%94%B6%E8%97%8F%E7%82%B9.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct TransferDeleteCollectionRequest 
{
	HsviewRequest base;

	struct TransferDeleteCollectionRequestData
	{
		
		/** struct of TransferDeleteCollectionRequestData_TransferContent */
		struct TransferDeleteCollectionRequestData_TransferContent {
			/** cllection-name1 */
			DECLARE_LIST(CSTR) names;
			/** [int]通道ID */
			int channelId;
		} transferContent;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} TransferDeleteCollectionRequest;

C_API TransferDeleteCollectionRequest *HSAPI_INIT(TransferDeleteCollectionRequest);

typedef struct TransferDeleteCollectionResponse 
{
	HsviewResponse base;

	struct TransferDeleteCollectionResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} TransferDeleteCollectionResponse;

C_API TransferDeleteCollectionResponse *HSAPI_INIT(TransferDeleteCollectionResponse);

#endif
