/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferAlarm_DistanceGet_H_
#define _HSVIEW_CLIENT_API_transferAlarm_DistanceGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取检测距离


参考PaaS协议：[获取检测距离](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E6%A3%80%E6%B5%8B%E8%B7%9D%E7%A6%BB%2F%E8%8E%B7%E5%8F%96%E6%A3%80%E6%B5%8B%E8%B7%9D%E7%A6%BB.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferAlarm_DistanceGetRequest 
{
	HsviewRequest base;

	struct transferAlarm_DistanceGetRequestData
	{
		
		/** 设备序列号 */
		CSTR deviceId;
		/** [cstr]/device/distance/query */
		#define _STATIC_transferAlarm_DistanceGetRequestData_url "/device/distance/query"
		CSTR url;

	} data;

} transferAlarm_DistanceGetRequest;

C_API transferAlarm_DistanceGetRequest *HSAPI_INIT(transferAlarm_DistanceGetRequest);

typedef struct transferAlarm_DistanceGetResponse 
{
	HsviewResponse base;

	struct transferAlarm_DistanceGetResponseData
	{
		
		/** [O]数组，可选，当返回该字段时，APP下拉取该字段的内容展示 */
		DECLARE_LIST(CSTR) distanceList;
		/** remote:远距离 near：近距离 */
		CSTR distance;
 
	} data;

} transferAlarm_DistanceGetResponse;

C_API transferAlarm_DistanceGetResponse *HSAPI_INIT(transferAlarm_DistanceGetResponse);

#endif
