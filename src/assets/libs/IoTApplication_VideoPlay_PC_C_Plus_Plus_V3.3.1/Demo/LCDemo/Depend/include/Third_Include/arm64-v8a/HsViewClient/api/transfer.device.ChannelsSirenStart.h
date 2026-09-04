/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDevice_ChannelsSirenStart_H_
#define _HSVIEW_CLIENT_API_transferDevice_ChannelsSirenStart_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
开启警笛

参考PaaS协议：[开启警笛](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E8%AD%A6%E7%AC%9B%E6%93%8D%E4%BD%9C%2F%E9%80%9A%E9%81%93%E7%BA%A7%E6%93%8D%E4%BD%9C%2F%E5%BC%80%E5%90%AF%E9%80%9A%E9%81%93%E8%AD%A6%E7%AC%9B.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferDevice_ChannelsSirenStartRequest 
{
	HsviewRequest base;

	struct transferDevice_ChannelsSirenStartRequestData
	{
		
		/** [cstr]/device/channles/siren/start */
		#define _STATIC_transferDevice_ChannelsSirenStartRequestData_url "/device/channles/siren/start"
		CSTR url;
		/** struct of transferDevice_ChannelsSirenStartRequestData_Content */
		struct transferDevice_ChannelsSirenStartRequestData_Content {
			/** 客户端本地时间，如20180301T111730 */
			CSTR clientLocalTime;
			/** [int]设备通道号，从0开始 */
			DECLARE_LIST(int) channels;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferDevice_ChannelsSirenStartRequest;

C_API transferDevice_ChannelsSirenStartRequest *HSAPI_INIT(transferDevice_ChannelsSirenStartRequest);

typedef struct transferDevice_ChannelsSirenStartResponse 
{
	HsviewResponse base;

	struct transferDevice_ChannelsSirenStartResponseData
	{
		
		/** 客户端本地时间，如20180301T111730 */
		CSTR clientLocalTime;
		/** define a list with struct of transferDevice_ChannelsSirenStartResponseData_ChannelsElement */
		DECLARE_LIST(struct transferDevice_ChannelsSirenStartResponseData_ChannelsElement
		{
			/** [int]警笛持续时间 */
			int time;
			/** 通道号 */
			CSTR channelId;
		}) channels;
 
	} data;

} transferDevice_ChannelsSirenStartResponse;

C_API transferDevice_ChannelsSirenStartResponse *HSAPI_INIT(transferDevice_ChannelsSirenStartResponse);

#endif
