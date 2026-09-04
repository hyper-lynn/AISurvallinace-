/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferAlarm_ChannelPirRadiusSet_H_
#define _HSVIEW_CLIENT_API_transferAlarm_ChannelPirRadiusSet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置通道级PIR灵敏度

参考PaaS协议：[设置通道级PIR灵敏度](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2FPIR%E9%85%8D%E7%BD%AE%2F%E8%AE%BE%E5%A4%87%E8%A7%86%E9%A2%91%E9%80%9A%E9%81%93%E7%BA%A7PIR%E9%85%8D%E7%BD%AE%2F%E8%AE%BE%E7%BD%AEPIR%E7%81%B5%E6%95%8F%E5%BA%A6.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferAlarm_ChannelPirRadiusSetRequest 
{
	HsviewRequest base;

	struct transferAlarm_ChannelPirRadiusSetRequestData
	{
		
		/** [cstr]/device/channels/pir/config */
		#define _STATIC_transferAlarm_ChannelPirRadiusSetRequestData_url "/device/channels/pir/config"
		CSTR url;
		/** struct of transferAlarm_ChannelPirRadiusSetRequestData_Content */
		struct transferAlarm_ChannelPirRadiusSetRequestData_Content {
			/** define a list with struct of transferAlarm_ChannelPirRadiusSetRequestData_Content_ChannelsElement */
			DECLARE_LIST(struct transferAlarm_ChannelPirRadiusSetRequestData_Content_ChannelsElement
			{
				/** [int]通道ID */
				int channelId;
				/** define a list with struct of transferAlarm_ChannelPirRadiusSetRequestData_Content_ChannelsElement_ShapedEnableElement */
				DECLARE_LIST(struct transferAlarm_ChannelPirRadiusSetRequestData_Content_ChannelsElement_ShapedEnableElement
				{
					/** [int]小扇形的索引值，从0开始 */
					int index;
					/** on-开启 off-关闭 */
					CSTR enable;
				}) shapedEnable;
				/** [int]取值范围[0,100]，检测半径的百分比 */
				int radius;
			}) channels;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferAlarm_ChannelPirRadiusSetRequest;

C_API transferAlarm_ChannelPirRadiusSetRequest *HSAPI_INIT(transferAlarm_ChannelPirRadiusSetRequest);

typedef struct transferAlarm_ChannelPirRadiusSetResponse 
{
	HsviewResponse base;

	struct transferAlarm_ChannelPirRadiusSetResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} transferAlarm_ChannelPirRadiusSetResponse;

C_API transferAlarm_ChannelPirRadiusSetResponse *HSAPI_INIT(transferAlarm_ChannelPirRadiusSetResponse);

#endif
