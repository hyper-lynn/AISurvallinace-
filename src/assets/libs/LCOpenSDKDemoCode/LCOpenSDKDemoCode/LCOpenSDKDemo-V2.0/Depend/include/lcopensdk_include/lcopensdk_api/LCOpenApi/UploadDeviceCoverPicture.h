/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_UploadDeviceCoverPicture_H_
#define _LC_OPENAPI_CLIENT_UploadDeviceCoverPicture_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
上传设备封面图
 */

typedef struct UploadDeviceCoverPictureRequest 
{
	LCOpenApiRequest base;

	struct UploadDeviceCoverPictureRequestData
	{
		
		/** [cstr]uploadDeviceCoverPicture */
		#define _STATIC_UploadDeviceCoverPictureRequestData_method "uploadDeviceCoverPicture"
		CSTR method;
		/** 图片二进制数据的base64编码的字符串 */
		CSTR pictureData;
		/** 通道id */
		CSTR channelId;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备ID */
		CSTR deviceId;

	} data;

} UploadDeviceCoverPictureRequest;

C_API UploadDeviceCoverPictureRequest *LCOPENAPI_INIT(UploadDeviceCoverPictureRequest);

typedef struct UploadDeviceCoverPictureResponse 
{
	LCOpenApiResponse base;

	struct UploadDeviceCoverPictureResponseData
	{
		
		/** id值 */
		CSTR id;
		/** struct of UploadDeviceCoverPictureResponseData_Result */
		struct UploadDeviceCoverPictureResponseData_Result {
			/** 操作结果 */
			CSTR msg;
			/** struct of UploadDeviceCoverPictureResponseData_Result_Data */
			struct UploadDeviceCoverPictureResponseData_Result_Data {
				/** 图片的url */
				CSTR url;
			} data;
			/** 0 */
			CSTR code;
		} result;
 
	} data;

} UploadDeviceCoverPictureResponse;

C_API UploadDeviceCoverPictureResponse *LCOPENAPI_INIT(UploadDeviceCoverPictureResponse);

#endif
