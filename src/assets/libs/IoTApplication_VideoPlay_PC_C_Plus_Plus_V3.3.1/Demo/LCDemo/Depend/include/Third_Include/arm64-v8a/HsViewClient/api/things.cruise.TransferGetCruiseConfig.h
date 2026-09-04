/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_TransferGetCruiseConfig_H_
#define _HSVIEW_CLIENT_API_TransferGetCruiseConfig_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取设备定时巡航配置。

注意：客户端协议都是针对单通道的，PASS层协议都是多通道，两者没有必然的联系

响应内容说明参考PaaS协议：[获取设备收藏点](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E5%AE%9A%E6%97%B6%E5%B7%A1%E8%88%AA%2F%E8%8E%B7%E5%8F%96%E8%AE%BE%E5%A4%87%E5%AE%9A%E6%97%B6%E5%B7%A1%E8%88%AA%E9%85%8D%E7%BD%AE.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct TransferGetCruiseConfigRequest 
{
	HsviewRequest base;

	struct TransferGetCruiseConfigRequestData
	{
		
		/** struct of TransferGetCruiseConfigRequestData_TransferContent */
		struct TransferGetCruiseConfigRequestData_TransferContent {
			/** [int]通道ID */
			int channelId;
		} transferContent;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} TransferGetCruiseConfigRequest;

C_API TransferGetCruiseConfigRequest *HSAPI_INIT(TransferGetCruiseConfigRequest);

typedef struct TransferGetCruiseConfigResponse 
{
	HsviewResponse base;

	struct TransferGetCruiseConfigResponseData
	{
		
		/** define a list with struct of TransferGetCruiseConfigResponseData_CruisePlanElement */
		DECLARE_LIST(struct TransferGetCruiseConfigResponseData_CruisePlanElement
		{
			/** 巡航路径，当mode=collection时有效。default：默认路径，由设备端决定;custom：自定义路径，即collection中收藏点的顺序 */
			CSTR cruisePath;
			/** define a list with struct of TransferGetCruiseConfigResponseData_CruisePlanElement_CollectionElement */
			DECLARE_LIST(struct TransferGetCruiseConfigResponseData_CruisePlanElement_CollectionElement
			{
				/** 收藏点的唯一标示符。当mode=collection时有效 */
				CSTR name;
				/** [int][O]每个收藏点的停留时间，单位为秒。当mode=collection时有效 */
				int stayTime;
			}) collection;
			/** 巡航模式,default：默认模式，即全景巡航；collection：定制模式，即收藏点巡航 */
			CSTR mode;
			/** define a list with struct of TransferGetCruiseConfigResponseData_CruisePlanElement_CruisesElement */
			DECLARE_LIST(struct TransferGetCruiseConfigResponseData_CruisePlanElement_CruisesElement
			{
				/** 结束时间。时间格式为：THHMMSS */
				CSTR endTime;
				/** 开始时间。时间格式为：THHMMSS */
				CSTR beginTime;
				/** 巡航周期，值如下：Monday，Tuesday，Wednesday，Thursday，Friday，Saturday，Sunday */
				CSTR period;
			}) cruises;
			/** [O]巡航计划唯一标示符 */
			CSTR cruiseName;
		}) cruisePlan;
		/** [int]通道ID */
		int channelId;
 
	} data;

} TransferGetCruiseConfigResponse;

C_API TransferGetCruiseConfigResponse *HSAPI_INIT(TransferGetCruiseConfigResponse);

#endif
