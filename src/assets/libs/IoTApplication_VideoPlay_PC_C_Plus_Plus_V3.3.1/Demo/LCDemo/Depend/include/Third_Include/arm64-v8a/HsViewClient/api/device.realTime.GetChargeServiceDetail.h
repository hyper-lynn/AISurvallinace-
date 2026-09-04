/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceRealTime_GetChargeServiceDetail_H_
#define _HSVIEW_CLIENT_API_deviceRealTime_GetChargeServiceDetail_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
未开通套餐时或套餐类型为永久免费套餐时invalidTime不存在,
数组顺序为增值服务排序。
deviceModel不为某种类型增值服务支持型号时，不返回该增值类型的chargeDetail
增值服务类型 cloudStorageStrategy :云存储, realtimeWindowStrategy ：拉流不限制, phoneAlarmStrategy：电话报警提醒, deviceShareStrategy : 设备分享, apShareStrategy ：配件分享, timePhotoStrategy：时光相册,timeAlbum：每日影集 humanAlarmStrategy 智能人形检测，strangerAlarmStrategy：陌生人提醒
【使用平台账号签名】
 */

typedef struct deviceRealTime_GetChargeServiceDetailRequest 
{
	HsviewRequest base;

	struct deviceRealTime_GetChargeServiceDetailRequestData
	{
		
		/** define a list with struct of deviceRealTime_GetChargeServiceDetailRequestData_DeviceListElement */
		DECLARE_LIST(struct deviceRealTime_GetChargeServiceDetailRequestData_DeviceListElement
		{
			/** 设备型号 */
			CSTR deviceModel;
			/** 通道号 */
			CSTR channelId;
			/** 增值服务类型 */
			DECLARE_LIST(CSTR) chargeTypes;
			/** 设备ID */
			CSTR deviceId;
		}) deviceList;

	} data;

} deviceRealTime_GetChargeServiceDetailRequest;

C_API deviceRealTime_GetChargeServiceDetailRequest *HSAPI_INIT(deviceRealTime_GetChargeServiceDetailRequest);

typedef struct deviceRealTime_GetChargeServiceDetailResponse 
{
	HsviewResponse base;

	struct deviceRealTime_GetChargeServiceDetailResponseData
	{
		
		/** define a list with struct of deviceRealTime_GetChargeServiceDetailResponseData_DeviceListElement */
		DECLARE_LIST(struct deviceRealTime_GetChargeServiceDetailResponseData_DeviceListElement
		{
			/** 通道号 */
			CSTR channelId;
			/** define a list with struct of deviceRealTime_GetChargeServiceDetailResponseData_DeviceListElement_ChargeDetailElement */
			DECLARE_LIST(struct deviceRealTime_GetChargeServiceDetailResponseData_DeviceListElement_ChargeDetailElement
			{
				/** 服务链接地址 */
				CSTR chargeUrl;
				/** [O]charge：收费套餐，normalFree：普通的存在结束时间的免费套餐，foreverFree:永久免费套餐 */
				CSTR strategyType;
				/** [O]背景图地址 */
				CSTR backgroundPicUrl;
				/** 套餐状态 notExist:未开通套餐，using：开通且没有过期，soonExpire：即将过期 expired：套餐过期 */
				CSTR strategyStatus;
				/** [O]文案描述，app6.0新增 */
				CSTR desc;
				/** 增值服务主键id */
				CSTR chargeId;
				/** [O]过期时间，yyyyMMddTHHmmssZ时间格式 */
				CSTR invalidTime;
				/** 增值服务类型 */
				CSTR chargeType;
				/** [O]状态描述，app6.0新增 */
				CSTR statusDesc;
				/** 增值服务名称 */
				CSTR chargeName;
				/** 简介 */
				CSTR chargeProfile;
				/** 封面图地址 */
				CSTR picUrl;
			}) chargeDetail;
			/** 设备ID */
			CSTR deviceId;
		}) deviceList;
 
	} data;

} deviceRealTime_GetChargeServiceDetailResponse;

C_API deviceRealTime_GetChargeServiceDetailResponse *HSAPI_INIT(deviceRealTime_GetChargeServiceDetailResponse);

#endif
