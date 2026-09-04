/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferFacelibrary_FacelibraryListGet_H_
#define _HSVIEW_CLIENT_API_transferFacelibrary_FacelibraryListGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取人脸库列表

参考PaaS协议：[获取人脸库列表](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E4%BA%BA%E8%84%B8%E6%99%BA%E8%83%BD%E6%93%8D%E4%BD%9C%2F%E8%8E%B7%E5%8F%96%E4%BA%BA%E8%84%B8%E5%BA%93%E5%88%97%E8%A1%A8.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferFacelibrary_FacelibraryListGetRequest 
{
	HsviewRequest base;

	struct transferFacelibrary_FacelibraryListGetRequestData
	{
		
		/** [cstr]/device/facelibrary/list */
		#define _STATIC_transferFacelibrary_FacelibraryListGetRequestData_url "/device/facelibrary/list"
		CSTR url;
		/** struct of transferFacelibrary_FacelibraryListGetRequestData_Content */
		struct transferFacelibrary_FacelibraryListGetRequestData_Content {
			/** [int]设备通道Id，单通道设备默认为0 */
			int channelId;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferFacelibrary_FacelibraryListGetRequest;

C_API transferFacelibrary_FacelibraryListGetRequest *HSAPI_INIT(transferFacelibrary_FacelibraryListGetRequest);

typedef struct transferFacelibrary_FacelibraryListGetResponse 
{
	HsviewResponse base;

	struct transferFacelibrary_FacelibraryListGetResponseData
	{
		
		/** define a list with struct of transferFacelibrary_FacelibraryListGetResponseData_FacelibrarysElement */
		DECLARE_LIST(struct transferFacelibrary_FacelibraryListGetResponseData_FacelibrarysElement
		{
			/** 是否布控,true, false */
			CSTR enable;
			/** 相识度，归一化到0~100 */
			CSTR similarity;
			/** 人脸库名称 */
			CSTR name;
			/** 库Id */
			CSTR groupId;
		}) facelibrarys;
 
	} data;

} transferFacelibrary_FacelibraryListGetResponse;

C_API transferFacelibrary_FacelibraryListGetResponse *HSAPI_INIT(transferFacelibrary_FacelibraryListGetResponse);

#endif
