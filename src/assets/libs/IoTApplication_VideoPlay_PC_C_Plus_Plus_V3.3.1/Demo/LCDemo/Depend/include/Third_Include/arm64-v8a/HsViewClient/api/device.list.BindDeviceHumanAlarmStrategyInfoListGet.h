/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceList_BindDeviceHumanAlarmStrategyInfoListGet_H_
#define _HSVIEW_CLIENT_API_deviceList_BindDeviceHumanAlarmStrategyInfoListGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
分页获取用户绑定的设备通道云存储信息

【需要使用平台账号签名】
 */

typedef struct deviceList_BindDeviceHumanAlarmStrategyInfoListGetRequest 
{
	HsviewRequest base;

	struct deviceList_BindDeviceHumanAlarmStrategyInfoListGetRequestData
	{
		
		/** [int]条数,最大16 */
		int limit;
		/** [long]上次查询最后一个设备id，为-1表示从最开始获取 */
		int64 bindId;

	} data;

} deviceList_BindDeviceHumanAlarmStrategyInfoListGetRequest;

C_API deviceList_BindDeviceHumanAlarmStrategyInfoListGetRequest *HSAPI_INIT(deviceList_BindDeviceHumanAlarmStrategyInfoListGetRequest);

typedef struct deviceList_BindDeviceHumanAlarmStrategyInfoListGetResponse 
{
	HsviewResponse base;

	struct deviceList_BindDeviceHumanAlarmStrategyInfoListGetResponseData
	{
		
		/** [O]支持人形检测套餐设备的型号，逗号分隔,若无该字段或字段为空表示无限制型号 */
		CSTR requiredModel;
		/** define a list with struct of deviceList_BindDeviceHumanAlarmStrategyInfoListGetResponseData_DeviceListElement */
		DECLARE_LIST(struct deviceList_BindDeviceHumanAlarmStrategyInfoListGetResponseData_DeviceListElement
		{
			/** 视频通道的总数量（包含未接入的通道） */
			CSTR channelNum;
			/** 设备名称 */
			CSTR name;
			/** define a list with struct of deviceList_BindDeviceHumanAlarmStrategyInfoListGetResponseData_DeviceListElement_ChannelsElement */
			DECLARE_LIST(struct deviceList_BindDeviceHumanAlarmStrategyInfoListGetResponseData_DeviceListElement_ChannelsElement
			{
				/** 通道号 */
				CSTR channelId;
				/** 当前正在使用的套餐状态 notExist:未开通套餐，using：开通且没有过期， expired：套餐过期 */
				CSTR strategyStatus;
				/** 通道名称 */
				CSTR channelName;
			}) channels;
			/** 设备型号 */
			CSTR deviceModel;
			/** [long]绑定分享表自增id */
			int64 bindId;
			/** 设备能力集 */
			CSTR ability;
			/** 设备序列号 */
			CSTR deviceId;
		}) deviceList;
 
	} data;

} deviceList_BindDeviceHumanAlarmStrategyInfoListGetResponse;

C_API deviceList_BindDeviceHumanAlarmStrategyInfoListGetResponse *HSAPI_INIT(deviceList_BindDeviceHumanAlarmStrategyInfoListGetResponse);

#endif
