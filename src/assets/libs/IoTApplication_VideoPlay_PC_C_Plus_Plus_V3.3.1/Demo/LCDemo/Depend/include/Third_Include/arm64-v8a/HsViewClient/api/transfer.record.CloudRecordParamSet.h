/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferRecord_CloudRecordParamSet_H_
#define _HSVIEW_CLIENT_API_transferRecord_CloudRecordParamSet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置云录像参数,平台给设备端下发的云录像参数配置

参考PaaS协议：[设置云录像参数](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E4%BA%91%E5%BD%95%E5%83%8F%E9%85%8D%E7%BD%AE%2F%E8%AE%BE%E7%BD%AE%E4%BA%91%E5%BD%95%E5%83%8F%E5%8F%82%E6%95%B0.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferRecord_CloudRecordParamSetRequest 
{
	HsviewRequest base;

	struct transferRecord_CloudRecordParamSetRequestData
	{
		
		/** [cstr]/device/media/config */
		#define _STATIC_transferRecord_CloudRecordParamSetRequestData_url "/device/media/config"
		CSTR url;
		/** struct of transferRecord_CloudRecordParamSetRequestData_Content */
		struct transferRecord_CloudRecordParamSetRequestData_Content {
			/** [int] 5,预录时长,单位秒 */
			int preRecord;
			/** define a list with struct of transferRecord_CloudRecordParamSetRequestData_Content_ChannelsElement */
			DECLARE_LIST(struct transferRecord_CloudRecordParamSetRequestData_Content_ChannelsElement
			{
				/** main */
				CSTR streamType;
				/** [int] 1 */
				int channelId;
			}) channels;
			/** [int] 15,录像分片最大时长,单位分钟 */
			int maxRecordLength;
			/** [int][O] 45,录像持续时长,单位秒 */
			int durationTime;
			/** [int][O]消息联动的模式。平台端默认录像、图片都进行联动 */
			int linkageMode;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferRecord_CloudRecordParamSetRequest;

C_API transferRecord_CloudRecordParamSetRequest *HSAPI_INIT(transferRecord_CloudRecordParamSetRequest);

typedef struct transferRecord_CloudRecordParamSetResponse 
{
	HsviewResponse base;

	struct transferRecord_CloudRecordParamSetResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} transferRecord_CloudRecordParamSetResponse;

C_API transferRecord_CloudRecordParamSetResponse *HSAPI_INIT(transferRecord_CloudRecordParamSetResponse);

#endif
