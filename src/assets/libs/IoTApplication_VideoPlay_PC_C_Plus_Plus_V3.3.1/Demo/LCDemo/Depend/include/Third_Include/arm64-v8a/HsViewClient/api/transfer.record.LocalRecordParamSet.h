/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferRecord_LocalRecordParamSet_H_
#define _HSVIEW_CLIENT_API_transferRecord_LocalRecordParamSet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置本地录像参数

参考PaaS协议：[设置本地录像参数](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E8%AE%BE%E5%A4%87%E6%9C%AC%E5%9C%B0%E5%BD%95%E5%83%8F%E8%AE%A1%E5%88%92%2F%E8%AE%BE%E7%BD%AE%E6%9C%AC%E5%9C%B0%E5%BD%95%E5%83%8F%E5%8F%82%E6%95%B0.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferRecord_LocalRecordParamSetRequest 
{
	HsviewRequest base;

	struct transferRecord_LocalRecordParamSetRequestData
	{
		
		/** [cstr]/device/local/record/media/config */
		#define _STATIC_transferRecord_LocalRecordParamSetRequestData_url "/device/local/record/media/config"
		CSTR url;
		/** struct of transferRecord_LocalRecordParamSetRequestData_Content */
		struct transferRecord_LocalRecordParamSetRequestData_Content {
			/** define a list with struct of transferRecord_LocalRecordParamSetRequestData_Content_ChannelsElement */
			DECLARE_LIST(struct transferRecord_LocalRecordParamSetRequestData_Content_ChannelsElement
			{
				/** main */
				CSTR streamType;
				/** [int] 1 */
				int channelId;
			}) channels;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferRecord_LocalRecordParamSetRequest;

C_API transferRecord_LocalRecordParamSetRequest *HSAPI_INIT(transferRecord_LocalRecordParamSetRequest);

typedef struct transferRecord_LocalRecordParamSetResponse 
{
	HsviewResponse base;

	struct transferRecord_LocalRecordParamSetResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} transferRecord_LocalRecordParamSetResponse;

C_API transferRecord_LocalRecordParamSetResponse *HSAPI_INIT(transferRecord_LocalRecordParamSetResponse);

#endif
