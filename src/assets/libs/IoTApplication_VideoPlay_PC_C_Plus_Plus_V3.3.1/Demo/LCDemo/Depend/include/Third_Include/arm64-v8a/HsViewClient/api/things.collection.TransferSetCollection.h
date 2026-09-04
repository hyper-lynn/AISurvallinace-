/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_TransferSetCollection_H_
#define _HSVIEW_CLIENT_API_TransferSetCollection_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置收藏点。

注意：客户端协议都是针对单通道的，PASS层协议都是多通道，两者没有必然的联系

transferContent内容说明参考PaaS协议：[设置设备收藏点](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E6%94%B6%E8%97%8F%E7%82%B9%E9%85%8D%E7%BD%AE%2F%E8%AE%BE%E7%BD%AE%E8%AE%BE%E5%A4%87%E6%94%B6%E8%97%8F%E7%82%B9.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct TransferSetCollectionRequest 
{
	HsviewRequest base;

	struct TransferSetCollectionRequestData
	{
		
		/** struct of TransferSetCollectionRequestData_TransferContent */
		struct TransferSetCollectionRequestData_TransferContent {
			/** 收藏点名称，作为收藏点的唯一标示符，不允许重复 */
			CSTR name;
			/** [int]通道ID */
			int channelId;
			/** [int][O]停留时间，单位S。为空时，以设备默认值为准 */
			int stayTime;
			/** [bool] 是否加入到巡航计划中 */
			BOOL bCruise;
			/** [O]巡航计划唯一标示符.当bCruise=true时有效 */
			CSTR cruiseName;
		} transferContent;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} TransferSetCollectionRequest;

C_API TransferSetCollectionRequest *HSAPI_INIT(TransferSetCollectionRequest);

typedef struct TransferSetCollectionResponse 
{
	HsviewResponse base;

	struct TransferSetCollectionResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} TransferSetCollectionResponse;

C_API TransferSetCollectionResponse *HSAPI_INIT(TransferSetCollectionResponse);

#endif
