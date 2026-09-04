/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferAlarm_PirRadiusSet_H_
#define _HSVIEW_CLIENT_API_transferAlarm_PirRadiusSet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置PIR灵敏度

参考PaaS协议：[设置PIR灵敏度](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2FPIR%E9%85%8D%E7%BD%AE%2F%E8%AE%BE%E5%A4%87%E7%BA%A7PIR%E9%85%8D%E7%BD%AE%2F%E8%AE%BE%E7%BD%AEPIR%E7%81%B5%E6%95%8F%E5%BA%A6.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferAlarm_PirRadiusSetRequest 
{
	HsviewRequest base;

	struct transferAlarm_PirRadiusSetRequestData
	{
		
		/** [cstr]/device/pir/config */
		#define _STATIC_transferAlarm_PirRadiusSetRequestData_url "/device/pir/config"
		CSTR url;
		/** struct of transferAlarm_PirRadiusSetRequestData_Content */
		struct transferAlarm_PirRadiusSetRequestData_Content {
			/** define a list with struct of transferAlarm_PirRadiusSetRequestData_Content_ShapedEnableElement */
			DECLARE_LIST(struct transferAlarm_PirRadiusSetRequestData_Content_ShapedEnableElement
			{
				/** [int]小扇形的索引值，从0开始 */
				int index;
				/** on-开启 off-关闭 */
				CSTR enable;
			}) shapedEnable;
			/** [int]取值范围[0,100]，检测半径的百分比 */
			int radius;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferAlarm_PirRadiusSetRequest;

C_API transferAlarm_PirRadiusSetRequest *HSAPI_INIT(transferAlarm_PirRadiusSetRequest);

typedef struct transferAlarm_PirRadiusSetResponse 
{
	HsviewResponse base;

	struct transferAlarm_PirRadiusSetResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} transferAlarm_PirRadiusSetResponse;

C_API transferAlarm_PirRadiusSetResponse *HSAPI_INIT(transferAlarm_PirRadiusSetResponse);

#endif
