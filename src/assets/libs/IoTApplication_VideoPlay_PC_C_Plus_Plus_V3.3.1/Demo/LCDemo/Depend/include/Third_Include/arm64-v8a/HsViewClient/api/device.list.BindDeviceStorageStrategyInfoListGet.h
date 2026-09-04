/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceList_BindDeviceStorageStrategyInfoListGet_H_
#define _HSVIEW_CLIENT_API_deviceList_BindDeviceStorageStrategyInfoListGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
分页获取用户绑定的设备通道云存储信息

【需要使用平台账号签名】
 */

typedef struct deviceList_BindDeviceStorageStrategyInfoListGetRequest 
{
	HsviewRequest base;

	struct deviceList_BindDeviceStorageStrategyInfoListGetRequestData
	{
		
		/** [int]条数,最大16 */
		int limit;
		/** [long]上次查询最后一个设备id，为-1表示从最开始获取 */
		int64 bindId;

	} data;

} deviceList_BindDeviceStorageStrategyInfoListGetRequest;

C_API deviceList_BindDeviceStorageStrategyInfoListGetRequest *HSAPI_INIT(deviceList_BindDeviceStorageStrategyInfoListGetRequest);

typedef struct deviceList_BindDeviceStorageStrategyInfoListGetResponse 
{
	HsviewResponse base;

	struct deviceList_BindDeviceStorageStrategyInfoListGetResponseData
	{
		
		/** define a list with struct of deviceList_BindDeviceStorageStrategyInfoListGetResponseData_DeviceListElement */
		DECLARE_LIST(struct deviceList_BindDeviceStorageStrategyInfoListGetResponseData_DeviceListElement
		{
			/** define a list with struct of deviceList_BindDeviceStorageStrategyInfoListGetResponseData_DeviceListElement_ChannelListElement */
			DECLARE_LIST(struct deviceList_BindDeviceStorageStrategyInfoListGetResponseData_DeviceListElement_ChannelListElement
			{
				/** 当前正在使用的云存储状态 notExist:未开通套餐，using：开通云存储且没有过期， expired：套餐过期 */
				CSTR storageStrategyStatus;
				/** 通道名称 */
				CSTR channelName;
				/** 列表中最后一个套餐过期时间，当storageStrategyStatus=using时，storageStrategyExpireTime为空字符串：表明永久，不为空表明:套餐总过期时间，套餐过期时间yyyyMMddTHHmmssZ格式 */
				CSTR storageStrategyExpireTime;
				/** 通道号 */
				CSTR channelId;
				/** 通道状态，online-在线 offline-离线 close-未配置接入 */
				CSTR status;
			}) channelList;
			/** [O]设备型号 */
			CSTR deviceModel;
			/** 设备序列号 */
			CSTR deviceId;
			/** [int]视频通道的总数量（包含未接入的通道）,可通过这个数值判断单/多通道设备 */
			int channelNum;
			/** 设备名称 */
			CSTR deviceName;
			/** 设备状态，online-在线 offline-离线 */
			CSTR status;
			/** [long]绑定表自增id */
			int64 bindId;
			/** [O]设备接入类型，PaaS-表示Paas程序接入、Lechange-表示乐橙非PaaS设备、Easy4IP表示Easy4IP程序设备、P2P表示P2P程序设备 */
			CSTR accessType;
			/** 设备能力集 */
			CSTR ability;
		}) deviceList;
 
	} data;

} deviceList_BindDeviceStorageStrategyInfoListGetResponse;

C_API deviceList_BindDeviceStorageStrategyInfoListGetResponse *HSAPI_INIT(deviceList_BindDeviceStorageStrategyInfoListGetResponse);

#endif
