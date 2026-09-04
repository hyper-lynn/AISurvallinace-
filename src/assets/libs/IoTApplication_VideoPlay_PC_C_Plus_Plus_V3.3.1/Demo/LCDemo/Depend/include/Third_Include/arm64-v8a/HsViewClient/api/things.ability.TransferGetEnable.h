/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_TransferGetEnable_H_
#define _HSVIEW_CLIENT_API_TransferGetEnable_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取设备功能开关

transferContent内容和响应内容说明参考PaaS协议：[获取设备功能开关](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E5%8A%9F%E8%83%BD%E5%BC%80%E5%85%B3%2F%E8%8E%B7%E5%8F%96%E8%AE%BE%E5%A4%87%E5%8A%9F%E8%83%BD%E5%BC%80%E5%85%B3.md&s=pd)

备注：
错误码：1311，表示设备不具备该功能。
【需要使用平台账号签名】
 */

typedef struct TransferGetEnableRequest 
{
	HsviewRequest base;

	struct TransferGetEnableRequestData
	{
		
		/** struct of TransferGetEnableRequestData_TransferContent */
		struct TransferGetEnableRequestData_TransferContent {
			/** define a list with struct of TransferGetEnableRequestData_TransferContent_DeviceElement */
			DECLARE_LIST(struct TransferGetEnableRequestData_TransferContent_DeviceElement
			{
				/** smartLocate,类型 */
				CSTR type;
			}) device;
			/** define a list with struct of TransferGetEnableRequestData_TransferContent_ChannelsElement */
			DECLARE_LIST(struct TransferGetEnableRequestData_TransferContent_ChannelsElement
			{
				/** localRecord */
				DECLARE_LIST(CSTR) type;
				/** [int]通道号,从0开始 */
				int channelId;
			}) channels;
		} transferContent;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} TransferGetEnableRequest;

C_API TransferGetEnableRequest *HSAPI_INIT(TransferGetEnableRequest);

typedef struct TransferGetEnableResponse 
{
	HsviewResponse base;

	struct TransferGetEnableResponseData
	{
		
		/** define a list with struct of TransferGetEnableResponseData_DeviceElement */
		DECLARE_LIST(struct TransferGetEnableResponseData_DeviceElement
		{
			/** on,使能 */
			CSTR enable;
			/** smartLocate,类型 */
			CSTR type;
		}) device;
		/** define a list with struct of TransferGetEnableResponseData_ChannelsElement */
		DECLARE_LIST(struct TransferGetEnableResponseData_ChannelsElement
		{
			/** define a list with struct of TransferGetEnableResponseData_ChannelsElement_DetailElement */
			DECLARE_LIST(struct TransferGetEnableResponseData_ChannelsElement_DetailElement
			{
				/** on,使能 */
				CSTR enable;
				/** smartTrack,类型 */
				CSTR type;
			}) detail;
			/** [int]通道号,从0开始 */
			int channelId;
		}) channels;
 
	} data;

} TransferGetEnableResponse;

C_API TransferGetEnableResponse *HSAPI_INIT(TransferGetEnableResponse);

#endif
