/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetPanoPictureUrl_H_
#define _HSVIEW_CLIENT_API_GetPanoPictureUrl_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取全景图URL。若没有生成过全景图，接口返回错误码。

contentEncrypt:设备通道封面码流加密模式，字段详细说明参考[设备加密](../设备加密.md)
【使用平台账号签名】
 */

typedef struct GetPanoPictureUrlRequest 
{
	HsviewRequest base;

	struct GetPanoPictureUrlRequestData
	{
		
		/** 设备ID */
		CSTR deviceId;

	} data;

} GetPanoPictureUrlRequest;

C_API GetPanoPictureUrlRequest *HSAPI_INIT(GetPanoPictureUrlRequest);

typedef struct GetPanoPictureUrlResponse 
{
	HsviewResponse base;

	struct GetPanoPictureUrlResponseData
	{
		
		/** struct of GetPanoPictureUrlResponseData_ContentEncrypt */
		struct GetPanoPictureUrlResponseData_ContentEncrypt {
			/** 密钥生成算法版本号 */
			CSTR ruleVersion;
			/** 内容加密模式 */
			CSTR encryptMode;
			/** 内容加密秘钥种子KeySeed的模式 */
			CSTR keyMode;
		} contentEncrypt;
		/** 全景图URL */
		CSTR url;
 
	} data;

} GetPanoPictureUrlResponse;

C_API GetPanoPictureUrlResponse *HSAPI_INIT(GetPanoPictureUrlResponse);

#endif
