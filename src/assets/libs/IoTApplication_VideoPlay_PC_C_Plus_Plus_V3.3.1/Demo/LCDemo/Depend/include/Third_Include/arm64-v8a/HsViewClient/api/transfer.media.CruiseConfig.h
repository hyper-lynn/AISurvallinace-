/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferMedia_CruiseConfig_H_
#define _HSVIEW_CLIENT_API_transferMedia_CruiseConfig_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置设备定时巡航配置

参考PaaS协议：[设置设备定时巡航配置](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E5%AE%9A%E6%97%B6%E5%B7%A1%E8%88%AA%2F%E8%AE%BE%E7%BD%AE%E8%AE%BE%E5%A4%87%E5%AE%9A%E6%97%B6%E5%B7%A1%E8%88%AA%E9%85%8D%E7%BD%AE.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferMedia_CruiseConfigRequest 
{
	HsviewRequest base;

	struct transferMedia_CruiseConfigRequestData
	{
		
		/** [cstr]/device/cruise/config */
		#define _STATIC_transferMedia_CruiseConfigRequestData_url "/device/cruise/config"
		CSTR url;
		/** struct of transferMedia_CruiseConfigRequestData_Content */
		struct transferMedia_CruiseConfigRequestData_Content {
			/** define a list with struct of transferMedia_CruiseConfigRequestData_Content_ChannelsElement */
			DECLARE_LIST(struct transferMedia_CruiseConfigRequestData_Content_ChannelsElement
			{
				/** define a list with struct of transferMedia_CruiseConfigRequestData_Content_ChannelsElement_CruisePlanElement */
				DECLARE_LIST(struct transferMedia_CruiseConfigRequestData_Content_ChannelsElement_CruisePlanElement
				{
					/** 巡航路径，当mode=collection时有效。可选值如下：default：默认路径，由设备端决定;custom：自定义路径，即collection中收藏点的顺序 */
					CSTR cruisePath;
					/** define a list with struct of transferMedia_CruiseConfigRequestData_Content_ChannelsElement_CruisePlanElement_CollectionElement */
					DECLARE_LIST(struct transferMedia_CruiseConfigRequestData_Content_ChannelsElement_CruisePlanElement_CollectionElement
					{
						/** 收藏点参数，当mode=collection时有效。收藏点的唯一标示符 */
						CSTR name;
						/** [int]收藏点参数，当mode=collection时有效。每个收藏点的停留时间，单位为秒。 */
						int stayTime;
					}) collection;
					/** default：默认模式，即全景巡航;collection：定制模式，即收藏点巡航 */
					CSTR mode;
					/** define a list with struct of transferMedia_CruiseConfigRequestData_Content_ChannelsElement_CruisePlanElement_CruisesElement */
					DECLARE_LIST(struct transferMedia_CruiseConfigRequestData_Content_ChannelsElement_CruisePlanElement_CruisesElement
					{
						/** 结束时间。时间格式为：THHMMSS。 */
						CSTR endTime;
						/** 开始时间。时间格式为：THHMMSS。 */
						CSTR beginTime;
						/** 巡航周期:Monday每周一;Tuesday每周二;Wednesday每周三;Thursday每周四;Friday每周五;Saturday每周六;Sunday每周日 */
						CSTR period;
					}) cruises;
					/** [O]巡航计划唯一标示符，可选。 */
					CSTR cruiseName;
				}) cruisePlan;
				/** [int]通道ID */
				int channelId;
			}) channels;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferMedia_CruiseConfigRequest;

C_API transferMedia_CruiseConfigRequest *HSAPI_INIT(transferMedia_CruiseConfigRequest);

typedef struct transferMedia_CruiseConfigResponse 
{
	HsviewResponse base;

	struct transferMedia_CruiseConfigResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} transferMedia_CruiseConfigResponse;

C_API transferMedia_CruiseConfigResponse *HSAPI_INIT(transferMedia_CruiseConfigResponse);

#endif
