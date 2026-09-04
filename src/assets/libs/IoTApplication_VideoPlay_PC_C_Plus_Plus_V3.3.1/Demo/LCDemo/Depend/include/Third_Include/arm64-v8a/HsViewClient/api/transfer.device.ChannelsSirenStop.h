/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDevice_ChannelsSirenStop_H_
#define _HSVIEW_CLIENT_API_transferDevice_ChannelsSirenStop_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
停止警笛

参考PaaS协议：[停止警笛](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E8%AD%A6%E7%AC%9B%E6%93%8D%E4%BD%9C%2F%E9%80%9A%E9%81%93%E7%BA%A7%E6%93%8D%E4%BD%9C%2F%E5%81%9C%E6%AD%A2%E9%80%9A%E9%81%93%E8%AD%A6%E7%AC%9B.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferDevice_ChannelsSirenStopRequest 
{
	HsviewRequest base;

	struct transferDevice_ChannelsSirenStopRequestData
	{
		
		/** [cstr]/device/channles/siren/stop */
		#define _STATIC_transferDevice_ChannelsSirenStopRequestData_url "/device/channles/siren/stop"
		CSTR url;
		/** struct of transferDevice_ChannelsSirenStopRequestData_Content */
		struct transferDevice_ChannelsSirenStopRequestData_Content {
			/** [int]设备通道号，从0开始 */
			DECLARE_LIST(int) channels;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferDevice_ChannelsSirenStopRequest;

C_API transferDevice_ChannelsSirenStopRequest *HSAPI_INIT(transferDevice_ChannelsSirenStopRequest);

typedef struct transferDevice_ChannelsSirenStopResponse 
{
	HsviewResponse base;

	struct transferDevice_ChannelsSirenStopResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} transferDevice_ChannelsSirenStopResponse;

C_API transferDevice_ChannelsSirenStopResponse *HSAPI_INIT(transferDevice_ChannelsSirenStopResponse);

#endif
