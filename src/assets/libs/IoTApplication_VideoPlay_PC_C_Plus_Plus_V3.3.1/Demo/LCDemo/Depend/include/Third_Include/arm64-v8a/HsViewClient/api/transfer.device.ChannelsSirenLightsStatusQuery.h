/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDevice_ChannelsSirenLightsStatusQuery_H_
#define _HSVIEW_CLIENT_API_transferDevice_ChannelsSirenLightsStatusQuery_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取通道警笛白光灯状态


参考PaaS协议：[通道警笛白光灯状态](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E8%AD%A6%E7%AC%9B%E6%93%8D%E4%BD%9C%2F%E9%80%9A%E9%81%93%E7%BA%A7%E6%93%8D%E4%BD%9C%2F%E8%8E%B7%E5%8F%96%E9%80%9A%E9%81%93%E8%AD%A6%E7%AC%9B%E7%99%BD%E5%85%89%E7%81%AF%E7%8A%B6%E6%80%81.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferDevice_ChannelsSirenLightsStatusQueryRequest 
{
	HsviewRequest base;

	struct transferDevice_ChannelsSirenLightsStatusQueryRequestData
	{
		
		/** [cstr]/device/channels/siren/query */
		#define _STATIC_transferDevice_ChannelsSirenLightsStatusQueryRequestData_url "/device/channels/siren/query"
		CSTR url;
		/** struct of transferDevice_ChannelsSirenLightsStatusQueryRequestData_Content */
		struct transferDevice_ChannelsSirenLightsStatusQueryRequestData_Content {
			/** 客户端本地时间，如20180301T111730 */
			CSTR clientLocalTime;
			/** [int]设备通道号，从0开始 */
			DECLARE_LIST(int) channels;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferDevice_ChannelsSirenLightsStatusQueryRequest;

C_API transferDevice_ChannelsSirenLightsStatusQueryRequest *HSAPI_INIT(transferDevice_ChannelsSirenLightsStatusQueryRequest);

typedef struct transferDevice_ChannelsSirenLightsStatusQueryResponse 
{
	HsviewResponse base;

	struct transferDevice_ChannelsSirenLightsStatusQueryResponseData
	{
		
		/** 将Req的值原样带回，20180301T111730 */
		CSTR clientLocalTime;
		/** define a list with struct of transferDevice_ChannelsSirenLightsStatusQueryResponseData_ChannelsElement */
		DECLARE_LIST(struct transferDevice_ChannelsSirenLightsStatusQueryResponseData_ChannelsElement
		{
			/** [O]探照灯开关状态，on-开启，off-关闭 */
			CSTR searchLight;
			/** 通道号 */
			CSTR channelId;
			/** [int]响铃倒计时剩余时间，单位为秒，若为-1则表示未响铃 */
			int time;
			/** [O]白光灯开关状态，on-开启，off-关闭 */
			CSTR whiteLight;
		}) channels;
 
	} data;

} transferDevice_ChannelsSirenLightsStatusQueryResponse;

C_API transferDevice_ChannelsSirenLightsStatusQueryResponse *HSAPI_INIT(transferDevice_ChannelsSirenLightsStatusQueryResponse);

#endif
