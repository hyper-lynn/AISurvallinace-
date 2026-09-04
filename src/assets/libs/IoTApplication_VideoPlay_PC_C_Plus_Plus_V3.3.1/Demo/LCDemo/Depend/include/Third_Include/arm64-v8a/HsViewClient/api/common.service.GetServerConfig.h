/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_commonService_GetServerConfig_H_
#define _HSVIEW_CLIENT_API_commonService_GetServerConfig_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取服务的访问地址，type为空串或者不传，代表查询所有平台配置的服务列表。
建议使用方法：type为空串或者不传。
isRelay 仅代表是否走P2P Relay， 需要注意 非PaaS设备不支持MTS（即非PaaS设备需要走P2P Relay）

举例如下：
[
    {
        "type": "p2p",
        "host": "www-testing-sz.easy4ipcloud.com",
        "port": 8800
    },
    {
        "type": "pss",
        "host": "pss-testing-sz.easy4ipcloud.com",
        "port": 443
    },
    {
        "type": "pns",
        "host": "epns-testing-sz.easy4ipcloud.com",
        "port": 8288
    },
    {
        "type": "p2p-ios-alarm",
        "host": "das-testing-sz.easy4ipcloud.com",
        "port": 15901
    },
    {
        "type": "p2p-android-alarm",
        "host": "das-testing-sz.easy4ipcloud.com",
        "port": 15900
    },
	{
        "type": "device_password_reset",
        "host": "10.1.1.20",
        "port": 9090
    },
	{
        "type": "device_register",
        "host": "funcdevaccess.easy4ipcloud.com",
        "port": 10000
    },
	{
        "type": "device_login",
        "host": "dev-testings-sz.easy4ipcloud.com",
        "port": 15301
    }
]
p2pKey字段为将YXQ3Mahe-5H-R1Z_加密之后的字符串:8dZConmqiQEr7C/7yvOBn41vzV2AzU27F3HLt5y1I64=
p2pSk加密方式与p2pKey相同
加密方式:http://paas.dahuatech.com/wiki/?p=%2FSaaS%2Fprotocol%2Fuser.account.Register&s=pj


【需要使默认AK、SK签名】
 */

typedef struct commonService_GetServerConfigRequest 
{
	HsviewRequest base;

	struct commonService_GetServerConfigRequestData
	{
		
		/** 服务类型：p2p-p2p服务，pss-统计服务，pns-PC客户端推送服务,logreport 客户端埋点统计信息上报,tracelogreport 客户端全链路日志信息上报, device_password_reset 设备密码重置, device_register 设备注册, device_login 设备登录,shop 商城地址 */
		CSTR type;

	} data;

} commonService_GetServerConfigRequest;

C_API commonService_GetServerConfigRequest *HSAPI_INIT(commonService_GetServerConfigRequest);

typedef struct commonService_GetServerConfigResponse 
{
	HsviewResponse base;

	struct commonService_GetServerConfigResponseData
	{
		
		/** [O] 设备密码重置的域名 */
		CSTR resetPwdHost;
		/** [O]一键oem项目的p2p ak,不加密 */
		CSTR p2pAk;
		/** define a list with struct of commonService_GetServerConfigResponseData_ServicesElement */
		DECLARE_LIST(struct commonService_GetServerConfigResponseData_ServicesElement
		{
			/** 服务的访问地址 */
			CSTR host;
			/** 服务类型：p2p-p2p服务，pss-统计服务，pns-PC客户端推送服务,logreport 客户端埋点统计信息上报,tracelogreport 客户端全链路日志信息上报,，device_password_reset 设备密码重置，shop 商城地址 */
			CSTR type;
			/** [int]服务的访问端口 */
			int port;
		}) services;
		/** true/false 是否走P2P relay */
		CSTR isRelay;
		/** [int] 0-FCM推送， 1-非FCM推送。仅海外有该字段 */
		int pushType;
		/** 加密串,无论如何都会返回 */
		CSTR p2pKey;
		/** [O]加密串,[O]一键oem项目的p2p sk */
		CSTR p2pSk;
 
	} data;

} commonService_GetServerConfigResponse;

C_API commonService_GetServerConfigResponse *HSAPI_INIT(commonService_GetServerConfigResponse);

#endif
