/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferAlarm_ChannelPirRadiusGet_H_
#define _HSVIEW_CLIENT_API_transferAlarm_ChannelPirRadiusGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取通道级PIR灵敏度

参考PaaS协议：[获取通道级PIR灵敏度](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2FPIR%E9%85%8D%E7%BD%AE%2F%E8%AE%BE%E5%A4%87%E8%A7%86%E9%A2%91%E9%80%9A%E9%81%93%E7%BA%A7PIR%E9%85%8D%E7%BD%AE%2F%E8%8E%B7%E5%8F%96PIR%E7%81%B5%E6%95%8F%E5%BA%A6.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferAlarm_ChannelPirRadiusGetRequest 
{
	HsviewRequest base;

	struct transferAlarm_ChannelPirRadiusGetRequestData
	{
		
		/** [cstr]/device/channels/pir/query */
		#define _STATIC_transferAlarm_ChannelPirRadiusGetRequestData_url "/device/channels/pir/query"
		CSTR url;
		/** struct of transferAlarm_ChannelPirRadiusGetRequestData_Content */
		struct transferAlarm_ChannelPirRadiusGetRequestData_Content {
			/** [int]通道ID */
			DECLARE_LIST(int) channels;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferAlarm_ChannelPirRadiusGetRequest;

C_API transferAlarm_ChannelPirRadiusGetRequest *HSAPI_INIT(transferAlarm_ChannelPirRadiusGetRequest);

typedef struct transferAlarm_ChannelPirRadiusGetResponse 
{
	HsviewResponse base;

	struct transferAlarm_ChannelPirRadiusGetResponseData
	{
		
		/** define a list with struct of transferAlarm_ChannelPirRadiusGetResponseData_ChannelsElement */
		DECLARE_LIST(struct transferAlarm_ChannelPirRadiusGetResponseData_ChannelsElement
		{
			/** [int]通道ID */
			int channelId;
			/** define a list with struct of transferAlarm_ChannelPirRadiusGetResponseData_ChannelsElement_ShapedEnableElement */
			DECLARE_LIST(struct transferAlarm_ChannelPirRadiusGetResponseData_ChannelsElement_ShapedEnableElement
			{
				/** [int]小扇形的索引值，从0开始 */
				int index;
				/** on-开启 off-关闭 */
				CSTR enable;
			}) shapedEnable;
			/** [int]取值范围[0,100]，检测半径的百分比 */
			int radius;
		}) channels;
 
	} data;

} transferAlarm_ChannelPirRadiusGetResponse;

C_API transferAlarm_ChannelPirRadiusGetResponse *HSAPI_INIT(transferAlarm_ChannelPirRadiusGetResponse);

#endif
