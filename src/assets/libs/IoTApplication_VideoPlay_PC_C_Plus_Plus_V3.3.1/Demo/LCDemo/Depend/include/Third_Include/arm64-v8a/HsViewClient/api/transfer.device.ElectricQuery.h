/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDevice_ElectricQuery_H_
#define _HSVIEW_CLIENT_API_transferDevice_ElectricQuery_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取电池相机电量通用协议

channels：设备通道号。当channels不存在时，则获取NVR或者HUB上所有外挂的通道的设备电量
参考PaaS协议：[远程设备电量查询](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E7%94%B5%E9%87%8F%E8%8E%B7%E5%8F%96%2F%E8%BF%9C%E7%A8%8B%E8%AE%BE%E5%A4%87%E7%94%B5%E9%87%8F%E6%9F%A5%E8%AF%A2.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferDevice_ElectricQueryRequest 
{
	HsviewRequest base;

	struct transferDevice_ElectricQueryRequestData
	{
		
		/** [cstr]/device/access/device/electric */
		#define _STATIC_transferDevice_ElectricQueryRequestData_url "/device/access/device/electric"
		CSTR url;
		/** struct of transferDevice_ElectricQueryRequestData_Content */
		struct transferDevice_ElectricQueryRequestData_Content {
			/** [int]通道号 */
			DECLARE_LIST(int) channels;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferDevice_ElectricQueryRequest;

C_API transferDevice_ElectricQueryRequest *HSAPI_INIT(transferDevice_ElectricQueryRequest);

typedef struct transferDevice_ElectricQueryResponse 
{
	HsviewResponse base;

	struct transferDevice_ElectricQueryResponseData
	{
		
		/** define a list with struct of transferDevice_ElectricQueryResponseData_ElectricitysElement */
		DECLARE_LIST(struct transferDevice_ElectricQueryResponseData_ElectricitysElement
		{
			/** [O]供电类型。当type为空时，默认为battery类型 */
			CSTR type;
			/** [int][O]可选，碱性电量百分比，取值范围0~100 */
			int alkElec;
			/** [int]设备通道号 */
			int channelId;
			/** [int][O]可选，锂电池电量百分比，取值范围0~100 */
			int litElec;
			/** [int][O]可选，电量百分比，取值范围0~100 */
			int electric;
		}) electricitys;
 
	} data;

} transferDevice_ElectricQueryResponse;

C_API transferDevice_ElectricQueryResponse *HSAPI_INIT(transferDevice_ElectricQueryResponse);

#endif
