/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_TransferSetEnable_H_
#define _HSVIEW_CLIENT_API_TransferSetEnable_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置设备功能开关。

transferContent内容说明参考PaaS协议：[设置设备功能开关](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E5%8A%9F%E8%83%BD%E5%BC%80%E5%85%B3%2F%E8%AE%BE%E7%BD%AE%E8%AE%BE%E5%A4%87%E5%8A%9F%E8%83%BD%E5%BC%80%E5%85%B3.md&s=pd)

备注：
错误码：1311，表示设备不具备该功能。
【需要使用平台账号签名】
 */

typedef struct TransferSetEnableRequest 
{
	HsviewRequest base;

	struct TransferSetEnableRequestData
	{
		
		/** struct of TransferSetEnableRequestData_TransferContent */
		struct TransferSetEnableRequestData_TransferContent {
			/** define a list with struct of TransferSetEnableRequestData_TransferContent_DeviceElement */
			DECLARE_LIST(struct TransferSetEnableRequestData_TransferContent_DeviceElement
			{
				/** on,使能 */
				CSTR enable;
				/** smartLocate,类型 */
				CSTR type;
			}) device;
			/** define a list with struct of TransferSetEnableRequestData_TransferContent_ChannelsElement */
			DECLARE_LIST(struct TransferSetEnableRequestData_TransferContent_ChannelsElement
			{
				/** define a list with struct of TransferSetEnableRequestData_TransferContent_ChannelsElement_DetailElement */
				DECLARE_LIST(struct TransferSetEnableRequestData_TransferContent_ChannelsElement_DetailElement
				{
					/** on,使能 */
					CSTR enable;
					/** smartTrack,类型 */
					CSTR type;
				}) detail;
				/** [int]通道号,从0开始 */
				int channelId;
			}) channels;
		} transferContent;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} TransferSetEnableRequest;

C_API TransferSetEnableRequest *HSAPI_INIT(TransferSetEnableRequest);

typedef struct TransferSetEnableResponse 
{
	HsviewResponse base;

	struct TransferSetEnableResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} TransferSetEnableResponse;

C_API TransferSetEnableResponse *HSAPI_INIT(TransferSetEnableResponse);

#endif
