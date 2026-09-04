/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferFacelibrary_FacelibraryDelete_H_
#define _HSVIEW_CLIENT_API_transferFacelibrary_FacelibraryDelete_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
删除人脸库

参考PaaS协议：[删除人脸库](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E4%BA%BA%E8%84%B8%E6%99%BA%E8%83%BD%E6%93%8D%E4%BD%9C%2F%E5%88%A0%E9%99%A4%E4%BA%BA%E8%84%B8%E5%BA%93.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferFacelibrary_FacelibraryDeleteRequest 
{
	HsviewRequest base;

	struct transferFacelibrary_FacelibraryDeleteRequestData
	{
		
		/** [cstr]/device/facelibrary/delete */
		#define _STATIC_transferFacelibrary_FacelibraryDeleteRequestData_url "/device/facelibrary/delete"
		CSTR url;
		/** struct of transferFacelibrary_FacelibraryDeleteRequestData_Content */
		struct transferFacelibrary_FacelibraryDeleteRequestData_Content {
			/** 库Id */
			CSTR groupId;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferFacelibrary_FacelibraryDeleteRequest;

C_API transferFacelibrary_FacelibraryDeleteRequest *HSAPI_INIT(transferFacelibrary_FacelibraryDeleteRequest);

typedef struct transferFacelibrary_FacelibraryDeleteResponse 
{
	HsviewResponse base;

	struct transferFacelibrary_FacelibraryDeleteResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} transferFacelibrary_FacelibraryDeleteResponse;

C_API transferFacelibrary_FacelibraryDeleteResponse *HSAPI_INIT(transferFacelibrary_FacelibraryDeleteResponse);

#endif
