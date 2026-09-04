/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_SetMessageCallbackUrl_H_
#define _HSVIEW_CLIENT_API_SetMessageCallbackUrl_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置消息回调URL。

方案说明：
	乐橙平台将消息通过HTTP请求发送到私有云设置的回调URL处。
	私有云消息推送HTTP请求格式定义如下：（假设推送回调URL为http://xxx.com/lcmsg）
	+-----------------------------------------------------+
	| POST /lcmsg HTTP/1.1                                |
	| Host: xxx.com                                       |
	| Content-Type: application/json                      |
	| Content-Length: 123                                 |
	|                                                     |
	| [推送内容]                                          |
	+-----------------------------------------------------+

【使用平台账号签名】
 */

typedef struct SetMessageCallbackUrlRequest 
{
	HsviewRequest base;

	struct SetMessageCallbackUrlRequestData
	{
		
		/** [int]是否订阅消息，1订阅，0不订阅 */
		int status;
		/** [O]回调标识，用逗号隔开；例如alarm,deviceStatus。alarm:报警回调标识，deviceStatus:设备以及通道上下线回调标记 */
		CSTR callbackFlag;
		/** 消息回调URL */
		CSTR callbackUrl;

	} data;

} SetMessageCallbackUrlRequest;

C_API SetMessageCallbackUrlRequest *HSAPI_INIT(SetMessageCallbackUrlRequest);

typedef struct SetMessageCallbackUrlResponse 
{
	HsviewResponse base;

	struct SetMessageCallbackUrlResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} SetMessageCallbackUrlResponse;

C_API SetMessageCallbackUrlResponse *HSAPI_INIT(SetMessageCallbackUrlResponse);

#endif
