/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferWifi_WifiCheckAddrGet_H_
#define _HSVIEW_CLIENT_API_transferWifi_WifiCheckAddrGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取检测wifi网络的地址(由paas路由服务直接返回地址，不用到设备端获取)

参考PaaS协议：[获取检测WIFI的服务地址](http://paas.dahuatech.com/wiki/?p=%2FPaaS%E6%9C%8D%E5%8A%A1%E8%83%BD%E5%8A%9B%E8%BE%93%E5%87%BA%2F%E5%B9%B3%E5%8F%B0%E6%B5%8B%E9%80%9F%2F%E8%8E%B7%E5%8F%96%E6%9C%8D%E5%8A%A1%E5%9C%B0%E5%9D%80.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferWifi_WifiCheckAddrGetRequest 
{
	HsviewRequest base;

	struct transferWifi_WifiCheckAddrGetRequestData
	{
		
		/** [cstr]/speed/server */
		#define _STATIC_transferWifi_WifiCheckAddrGetRequestData_url "/speed/server"
		CSTR url;
		/** [int][O]保留 */
		int _nouse;

	} data;

} transferWifi_WifiCheckAddrGetRequest;

C_API transferWifi_WifiCheckAddrGetRequest *HSAPI_INIT(transferWifi_WifiCheckAddrGetRequest);

typedef struct transferWifi_WifiCheckAddrGetResponse 
{
	HsviewResponse base;

	struct transferWifi_WifiCheckAddrGetResponseData
	{
		
		/** [String]检测wifi服务的地址 */
		CSTR addr;
 
	} data;

} transferWifi_WifiCheckAddrGetResponse;

C_API transferWifi_WifiCheckAddrGetResponse *HSAPI_INIT(transferWifi_WifiCheckAddrGetResponse);

#endif
