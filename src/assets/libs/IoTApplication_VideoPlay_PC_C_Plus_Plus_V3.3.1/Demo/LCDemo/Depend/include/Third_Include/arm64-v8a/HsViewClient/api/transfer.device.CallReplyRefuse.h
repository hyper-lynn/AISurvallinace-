/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDevice_CallReplyRefuse_H_
#define _HSVIEW_CLIENT_API_transferDevice_CallReplyRefuse_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设备拒接
index 拒接铃声索引
 CAV2能力支持
参考PaaS协议：[设备拒接](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E9%97%A8%E5%8F%A3%E6%9C%BA%E7%9B%B8%E5%85%B3%E6%93%8D%E4%BD%9C%2F%E6%8B%92%E6%8E%A5.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferDevice_CallReplyRefuseRequest 
{
	HsviewRequest base;

	struct transferDevice_CallReplyRefuseRequestData
	{
		
		/** [cstr]/device/call/refuse */
		#define _STATIC_transferDevice_CallReplyRefuseRequestData_url "/device/call/refuse"
		CSTR url;
		/** struct of transferDevice_CallReplyRefuseRequestData_Content */
		struct transferDevice_CallReplyRefuseRequestData_Content {
			/** [int]1 */
			int index;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferDevice_CallReplyRefuseRequest;

C_API transferDevice_CallReplyRefuseRequest *HSAPI_INIT(transferDevice_CallReplyRefuseRequest);

typedef struct transferDevice_CallReplyRefuseResponse 
{
	HsviewResponse base;

	struct transferDevice_CallReplyRefuseResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} transferDevice_CallReplyRefuseResponse;

C_API transferDevice_CallReplyRefuseResponse *HSAPI_INIT(transferDevice_CallReplyRefuseResponse);

#endif
