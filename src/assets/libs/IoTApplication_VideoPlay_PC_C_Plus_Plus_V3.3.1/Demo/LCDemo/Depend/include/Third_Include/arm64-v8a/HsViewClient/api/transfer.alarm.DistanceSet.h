/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferAlarm_DistanceSet_H_
#define _HSVIEW_CLIENT_API_transferAlarm_DistanceSet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置检测距离


参考PaaS协议：[设置检测距离](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E6%A3%80%E6%B5%8B%E8%B7%9D%E7%A6%BB%2F%E8%AE%BE%E7%BD%AE%E6%A3%80%E6%B5%8B%E8%B7%9D%E7%A6%BB.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferAlarm_DistanceSetRequest 
{
	HsviewRequest base;

	struct transferAlarm_DistanceSetRequestData
	{
		
		/** [cstr]/device/distance/config */
		#define _STATIC_transferAlarm_DistanceSetRequestData_url "/device/distance/config"
		CSTR url;
		/** struct of transferAlarm_DistanceSetRequestData_Content */
		struct transferAlarm_DistanceSetRequestData_Content {
			/** 检测距离,枚举remote,near,mid */
			CSTR distance;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferAlarm_DistanceSetRequest;

C_API transferAlarm_DistanceSetRequest *HSAPI_INIT(transferAlarm_DistanceSetRequest);

typedef struct transferAlarm_DistanceSetResponse 
{
	HsviewResponse base;

	struct transferAlarm_DistanceSetResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} transferAlarm_DistanceSetResponse;

C_API transferAlarm_DistanceSetResponse *HSAPI_INIT(transferAlarm_DistanceSetResponse);

#endif
