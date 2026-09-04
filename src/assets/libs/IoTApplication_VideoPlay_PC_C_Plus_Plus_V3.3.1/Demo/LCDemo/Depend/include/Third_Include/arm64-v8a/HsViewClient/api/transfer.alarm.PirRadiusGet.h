/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferAlarm_PirRadiusGet_H_
#define _HSVIEW_CLIENT_API_transferAlarm_PirRadiusGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取PIR灵敏度

参考PaaS协议：[获取PIR灵敏度](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2FPIR%E9%85%8D%E7%BD%AE%2F%E8%AE%BE%E5%A4%87%E7%BA%A7PIR%E9%85%8D%E7%BD%AE%2F%E8%8E%B7%E5%8F%96PIR%E7%81%B5%E6%95%8F%E5%BA%A6.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferAlarm_PirRadiusGetRequest 
{
	HsviewRequest base;

	struct transferAlarm_PirRadiusGetRequestData
	{
		
		/** 设备序列号 */
		CSTR deviceId;
		/** [cstr]/device/pir/query */
		#define _STATIC_transferAlarm_PirRadiusGetRequestData_url "/device/pir/query"
		CSTR url;

	} data;

} transferAlarm_PirRadiusGetRequest;

C_API transferAlarm_PirRadiusGetRequest *HSAPI_INIT(transferAlarm_PirRadiusGetRequest);

typedef struct transferAlarm_PirRadiusGetResponse 
{
	HsviewResponse base;

	struct transferAlarm_PirRadiusGetResponseData
	{
		
		/** define a list with struct of transferAlarm_PirRadiusGetResponseData_ShapedEnableElement */
		DECLARE_LIST(struct transferAlarm_PirRadiusGetResponseData_ShapedEnableElement
		{
			/** [int]小扇形的索引值，从0开始 */
			int index;
			/** on-开启 off-关闭 */
			CSTR enable;
		}) shapedEnable;
		/** [int]取值范围[0,100]，检测半径的百分比 */
		int radius;
 
	} data;

} transferAlarm_PirRadiusGetResponse;

C_API transferAlarm_PirRadiusGetResponse *HSAPI_INIT(transferAlarm_PirRadiusGetResponse);

#endif
