/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferMedia_TransEncryptSet_H_
#define _HSVIEW_CLIENT_API_transferMedia_TransEncryptSet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置媒体传输加密参数
>   请求参数说明
 + encryptMode:[string],传输加密
    - "none":不加密
    - "tls":tls加密

参考PaaS协议：[设置媒体传输加密参数](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E4%BA%91%E5%BD%95%E5%83%8F%E9%85%8D%E7%BD%AE%2F%E8%AE%BE%E7%BD%AE%E5%AA%92%E4%BD%93%E4%BC%A0%E8%BE%93%E5%8A%A0%E5%AF%86%E5%8F%82%E6%95%B0.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferMedia_TransEncryptSetRequest 
{
	HsviewRequest base;

	struct transferMedia_TransEncryptSetRequestData
	{
		
		/** [cstr]/device/media/trans/encrypt/config */
		#define _STATIC_transferMedia_TransEncryptSetRequestData_url "/device/media/trans/encrypt/config"
		CSTR url;
		/** struct of transferMedia_TransEncryptSetRequestData_Content */
		struct transferMedia_TransEncryptSetRequestData_Content {
			/** tls */
			CSTR encryptMode;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferMedia_TransEncryptSetRequest;

C_API transferMedia_TransEncryptSetRequest *HSAPI_INIT(transferMedia_TransEncryptSetRequest);

typedef struct transferMedia_TransEncryptSetResponse 
{
	HsviewResponse base;

	struct transferMedia_TransEncryptSetResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} transferMedia_TransEncryptSetResponse;

C_API transferMedia_TransEncryptSetResponse *HSAPI_INIT(transferMedia_TransEncryptSetResponse);

#endif
