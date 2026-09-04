/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_TransferTurnCollection_H_
#define _HSVIEW_CLIENT_API_TransferTurnCollection_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
转动到某个收藏点

注意：客户端协议都是针对单通道的，PASS层协议都是多通道，两者没有必然的联系

transferContent内容说明参考PaaS协议：[转动到某个收藏点](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E6%94%B6%E8%97%8F%E7%82%B9%E9%85%8D%E7%BD%AE%2F%E8%BD%AC%E5%8A%A8%E5%88%B0%E6%9F%90%E4%B8%AA%E6%94%B6%E8%97%8F%E7%82%B9.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct TransferTurnCollectionRequest 
{
	HsviewRequest base;

	struct TransferTurnCollectionRequestData
	{
		
		/** struct of TransferTurnCollectionRequestData_TransferContent */
		struct TransferTurnCollectionRequestData_TransferContent {
			/** 收藏点名称 */
			CSTR name;
			/** [int]通道ID */
			int channelId;
		} transferContent;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} TransferTurnCollectionRequest;

C_API TransferTurnCollectionRequest *HSAPI_INIT(TransferTurnCollectionRequest);

typedef struct TransferTurnCollectionResponse 
{
	HsviewResponse base;

	struct TransferTurnCollectionResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} TransferTurnCollectionResponse;

C_API TransferTurnCollectionResponse *HSAPI_INIT(TransferTurnCollectionResponse);

#endif
