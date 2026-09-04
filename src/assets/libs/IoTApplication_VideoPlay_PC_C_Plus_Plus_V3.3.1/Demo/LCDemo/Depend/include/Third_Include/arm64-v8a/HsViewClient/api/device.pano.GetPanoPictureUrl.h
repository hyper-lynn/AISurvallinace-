/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_devicePano_GetPanoPictureUrl_H_
#define _HSVIEW_CLIENT_API_devicePano_GetPanoPictureUrl_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取全景图URL。

若没有生成过全景图，url为空串。
【使用平台账号签名】
 */

typedef struct devicePano_GetPanoPictureUrlRequest 
{
	HsviewRequest base;

	struct devicePano_GetPanoPictureUrlRequestData
	{
		
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} devicePano_GetPanoPictureUrlRequest;

C_API devicePano_GetPanoPictureUrlRequest *HSAPI_INIT(devicePano_GetPanoPictureUrlRequest);

typedef struct devicePano_GetPanoPictureUrlResponse 
{
	HsviewResponse base;

	struct devicePano_GetPanoPictureUrlResponseData
	{
		
		/** struct of devicePano_GetPanoPictureUrlResponseData_ContentEncrypt */
		struct devicePano_GetPanoPictureUrlResponseData_ContentEncrypt {
			/** [O]密钥生成算法版本号 */
			CSTR ruleVersion;
			/** [O]内容加密模式 */
			CSTR encryptMode;
			/** [O]内容加密秘钥种子KeySeed的模式 */
			CSTR keyMode;
		} contentEncrypt;
		/** 全景图URL */
		CSTR url;
 
	} data;

} devicePano_GetPanoPictureUrlResponse;

C_API devicePano_GetPanoPictureUrlResponse *HSAPI_INIT(devicePano_GetPanoPictureUrlResponse);

#endif
