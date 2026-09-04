/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_cloudMessage_GetSystemMessageDetail_H_
#define _HSVIEW_CLIENT_API_cloudMessage_GetSystemMessageDetail_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
根据消息id查询系统消息详情

【使用平台账号签名】
 */

typedef struct cloudMessage_GetSystemMessageDetailRequest 
{
	HsviewRequest base;

	struct cloudMessage_GetSystemMessageDetailRequestData
	{
		
		/** [long]消息id */
		int64 msgId;

	} data;

} cloudMessage_GetSystemMessageDetailRequest;

C_API cloudMessage_GetSystemMessageDetailRequest *HSAPI_INIT(cloudMessage_GetSystemMessageDetailRequest);

typedef struct cloudMessage_GetSystemMessageDetailResponse 
{
	HsviewResponse base;

	struct cloudMessage_GetSystemMessageDetailResponseData
	{
		
		/** 标题 */
		CSTR title;
		/** 产生的UTC时间，yyyyMMddTHHmmssZ格式 */
		CSTR time;
		/** [long]消息ID */
		int64 msgId;
		/** [O]系统消息对应的网页url */
		CSTR url;
		/** [O]内容 */
		CSTR content;
		/** [O]标题图片的url */
		CSTR imgUrl;
 
	} data;

} cloudMessage_GetSystemMessageDetailResponse;

C_API cloudMessage_GetSystemMessageDetailResponse *HSAPI_INIT(cloudMessage_GetSystemMessageDetailResponse);

#endif
