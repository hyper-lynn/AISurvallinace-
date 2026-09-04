/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferMedia_PtzLocationGet_H_
#define _HSVIEW_CLIENT_API_transferMedia_PtzLocationGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取PTZ位置

参考PaaS协议：[获取PTZ位置](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2FPTZ%E6%93%8D%E4%BD%9C%2F%E8%8E%B7%E5%8F%96PTZ%E4%BD%8D%E7%BD%AE.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferMedia_PtzLocationGetRequest 
{
	HsviewRequest base;

	struct transferMedia_PtzLocationGetRequestData
	{
		
		/** [cstr]/device/ptz/location/query */
		#define _STATIC_transferMedia_PtzLocationGetRequestData_url "/device/ptz/location/query"
		CSTR url;
		/** 通道号，字符串类型 */
		DECLARE_LIST(CSTR) channelId;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferMedia_PtzLocationGetRequest;

C_API transferMedia_PtzLocationGetRequest *HSAPI_INIT(transferMedia_PtzLocationGetRequest);

typedef struct transferMedia_PtzLocationGetResponse 
{
	HsviewResponse base;

	struct transferMedia_PtzLocationGetResponseData
	{
		
		/** [double]变倍倍数：归一化到0~1，其中0表示缩到最小，1表示放到最大 */
		double zoom;
		/** [double]水平视场角近似值 */
		double fov;
		/** [double]水平位置：归一化到-1~1，表示水平经度-180°到180° */
		double horizontal;
		/** [double]焦距，以mm毫米为单位 */
		double focal;
		/** [double]垂直位置：归一化到-1~1，表示垂直维度-90°到90° */
		double vertical;
 
	} data;

} transferMedia_PtzLocationGetResponse;

C_API transferMedia_PtzLocationGetResponse *HSAPI_INIT(transferMedia_PtzLocationGetResponse);

#endif
