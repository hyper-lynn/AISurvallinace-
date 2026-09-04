/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_TransferSetCruiseConfig_H_
#define _HSVIEW_CLIENT_API_TransferSetCruiseConfig_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置设备定时巡航配置。

注意：客户端协议都是针对单通道的，PASS层协议都是多通道，两者没有必然的联系

transferContent内容说明参考PaaS协议：[设置设备定时巡航配置](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E5%AE%9A%E6%97%B6%E5%B7%A1%E8%88%AA%2F%E8%AE%BE%E7%BD%AE%E8%AE%BE%E5%A4%87%E5%AE%9A%E6%97%B6%E5%B7%A1%E8%88%AA%E9%85%8D%E7%BD%AE.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct TransferSetCruiseConfigRequest 
{
	HsviewRequest base;

	struct TransferSetCruiseConfigRequestData
	{
		
		/** struct of TransferSetCruiseConfigRequestData_TransferContent */
		struct TransferSetCruiseConfigRequestData_TransferContent {
			/** define a list with struct of TransferSetCruiseConfigRequestData_TransferContent_CruisePlanElement */
			DECLARE_LIST(struct TransferSetCruiseConfigRequestData_TransferContent_CruisePlanElement
			{
				/** 巡航路径，当mode=collection时有效,值如下：default：默认路径，由设备端决定；custom：自定义路径，即collection中收藏点的顺序 */
				CSTR cruisePath;
				/** define a list with struct of TransferSetCruiseConfigRequestData_TransferContent_CruisePlanElement_CollectionElement */
				DECLARE_LIST(struct TransferSetCruiseConfigRequestData_TransferContent_CruisePlanElement_CollectionElement
				{
					/** 收藏点的唯一标示符。当mode=collection时有效 */
					CSTR name;
					/** [int]每个收藏点的停留时间，单位为秒。当mode=collection时有效 */
					int stayTime;
				}) collection;
				/** 巡航模式,值如下：default：默认模式，即全景巡航；collection：定制模式，即收藏点巡航 */
				CSTR mode;
				/** define a list with struct of TransferSetCruiseConfigRequestData_TransferContent_CruisePlanElement_CruisesElement */
				DECLARE_LIST(struct TransferSetCruiseConfigRequestData_TransferContent_CruisePlanElement_CruisesElement
				{
					/** 结束时间。时间格式为：THHMMSS */
					CSTR endTime;
					/** 开始时间。时间格式为：THHMMSS */
					CSTR beginTime;
					/** 巡航周期,值如下：Monday，Tuesday，Wednesday，Thursday，Friday，Saturday，Sunday */
					CSTR period;
				}) cruises;
				/** [O]巡航计划唯一标示符 */
				CSTR cruiseName;
			}) cruisePlan;
			/** [int]通道ID */
			int channelId;
		} transferContent;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} TransferSetCruiseConfigRequest;

C_API TransferSetCruiseConfigRequest *HSAPI_INIT(TransferSetCruiseConfigRequest);

typedef struct TransferSetCruiseConfigResponse 
{
	HsviewResponse base;

	struct TransferSetCruiseConfigResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} TransferSetCruiseConfigResponse;

C_API TransferSetCruiseConfigResponse *HSAPI_INIT(TransferSetCruiseConfigResponse);

#endif
