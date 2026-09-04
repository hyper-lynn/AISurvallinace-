/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferRecord_LocalRecordParamGet_H_
#define _HSVIEW_CLIENT_API_transferRecord_LocalRecordParamGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取本地录像参数

参考PaaS协议：[获取本地录像参数](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E8%AE%BE%E5%A4%87%E6%9C%AC%E5%9C%B0%E5%BD%95%E5%83%8F%E8%AE%A1%E5%88%92%2F%E8%8E%B7%E5%8F%96%E6%9C%AC%E5%9C%B0%E5%BD%95%E5%83%8F%E5%8F%82%E6%95%B0.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferRecord_LocalRecordParamGetRequest 
{
	HsviewRequest base;

	struct transferRecord_LocalRecordParamGetRequestData
	{
		
		/** [cstr]/device/local/record/media/query */
		#define _STATIC_transferRecord_LocalRecordParamGetRequestData_url "/device/local/record/media/query"
		CSTR url;
		/** struct of transferRecord_LocalRecordParamGetRequestData_Content */
		struct transferRecord_LocalRecordParamGetRequestData_Content {
			/** [int]设备通道号 */
			DECLARE_LIST(int) channels;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferRecord_LocalRecordParamGetRequest;

C_API transferRecord_LocalRecordParamGetRequest *HSAPI_INIT(transferRecord_LocalRecordParamGetRequest);

typedef struct transferRecord_LocalRecordParamGetResponse 
{
	HsviewResponse base;

	struct transferRecord_LocalRecordParamGetResponseData
	{
		
		/** define a list with struct of transferRecord_LocalRecordParamGetResponseData_ChannelsElement */
		DECLARE_LIST(struct transferRecord_LocalRecordParamGetResponseData_ChannelsElement
		{
			/** main */
			CSTR streamType;
			/** [int] 1 */
			int channelId;
		}) channels;
 
	} data;

} transferRecord_LocalRecordParamGetResponse;

C_API transferRecord_LocalRecordParamGetResponse *HSAPI_INIT(transferRecord_LocalRecordParamGetResponse);

#endif
