/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDevice_OpenControlDevice_H_
#define _HSVIEW_CLIENT_API_transferDevice_OpenControlDevice_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
透传通道，用于开放平台的零售云能够直接控制设备。
该协议用于透传自定义信令，请求内容和回复内容均由用户定义。

type：透传类型，代表透传的目的地，当前有如下类型：DHPri：透传到大华二三代协议组件；
devName：设备用户名，当前DHPri == type时有效。需加密，加密算法详见备注说明；
devPassword：设备密码，当前DHPri == type时有效。需加密，加密算法详见备注说明；
content：透传的请求内容；


请求中的Content-Type必须与实际的请求内容一致；
加密算法详情如下：
格式：Base64(Aes256(AesKey, 待加密内容))；
加密算法：Aes256/CBC/PKCS7，初始化向量IV采用"HLMUQE2342MABCER"；
AesKey：Cut16(UpperCase(MD5-32位(UpperCase(设备序列号))))；
参考PaaS协议：[下行透传接口](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E9%80%8F%E4%BC%A0%E5%8D%8F%E8%AE%AE%2F%E4%B8%8B%E8%A1%8C%E9%80%8F%E4%BC%A0%E6%8E%A5%E5%8F%A3.md&s=pd)

权限校验：
1. 国内乐橙，强制校验用户的绑定关系。

【需要使用平台账号签名】
 */

typedef struct transferDevice_OpenControlDeviceRequest 
{
	HsviewRequest base;

	struct transferDevice_OpenControlDeviceRequestData
	{
		
		/** [O]通道号，如果是被分享者操作，必须带有其被分享的通道号，否则仅允许设备拥有者操作 */
		CSTR channelId;
		/** [cstr]/device/transfer/channel */
		#define _STATIC_transferDevice_OpenControlDeviceRequestData_url "/device/transfer/channel"
		CSTR url;
		/** struct of transferDevice_OpenControlDeviceRequestData_Content */
		struct transferDevice_OpenControlDeviceRequestData_Content {
			/** 设备密码 */
			CSTR devPassword;
			/** 透传类型 */
			CSTR type;
			/** Base64(透传的请求内容) */
			CSTR content;
			/** 设备用户名 */
			CSTR devName;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferDevice_OpenControlDeviceRequest;

C_API transferDevice_OpenControlDeviceRequest *HSAPI_INIT(transferDevice_OpenControlDeviceRequest);

typedef struct transferDevice_OpenControlDeviceResponse 
{
	HsviewResponse base;

	struct transferDevice_OpenControlDeviceResponseData
	{
		
		/** Base64(透传的回复内容) */
		CSTR content;
 
	} data;

} transferDevice_OpenControlDeviceResponse;

C_API transferDevice_OpenControlDeviceResponse *HSAPI_INIT(transferDevice_OpenControlDeviceResponse);

#endif
