/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferMedia_PtzLocationSet_H_
#define _HSVIEW_CLIENT_API_transferMedia_PtzLocationSet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
PTZ定位

参考PaaS协议：[PTZ定位](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2FPTZ%E6%93%8D%E4%BD%9C%2FPTZ%E5%AE%9A%E4%BD%8D.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferMedia_PtzLocationSetRequest 
{
	HsviewRequest base;

	struct transferMedia_PtzLocationSetRequestData
	{
		
		/** 通道号，字符串类型 */
		CSTR channelId;
		/** [cstr]/device/ptz/location/config */
		#define _STATIC_transferMedia_PtzLocationSetRequestData_url "/device/ptz/location/config"
		CSTR url;
		/** struct of transferMedia_PtzLocationSetRequestData_Content */
		struct transferMedia_PtzLocationSetRequestData_Content {
			/** [double]水平位置：归一化到-1~1 */
			double horizontal;
			/** [double]变倍倍数：归一化到0~1，其中0表示缩到最小，1表示放到最大 */
			double zoom;
			/** [double]垂直位置：归一化到-1~1 */
			double vertical;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferMedia_PtzLocationSetRequest;

C_API transferMedia_PtzLocationSetRequest *HSAPI_INIT(transferMedia_PtzLocationSetRequest);

typedef struct transferMedia_PtzLocationSetResponse 
{
	HsviewResponse base;

	struct transferMedia_PtzLocationSetResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} transferMedia_PtzLocationSetResponse;

C_API transferMedia_PtzLocationSetResponse *HSAPI_INIT(transferMedia_PtzLocationSetResponse);

#endif
