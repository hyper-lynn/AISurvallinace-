/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferFacelibrary_FacelibraryAdd_H_
#define _HSVIEW_CLIENT_API_transferFacelibrary_FacelibraryAdd_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
新建人脸库

参考PaaS协议：[新建人脸库](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E4%BA%BA%E8%84%B8%E6%99%BA%E8%83%BD%E6%93%8D%E4%BD%9C%2F%E6%96%B0%E5%BB%BA%E4%BA%BA%E8%84%B8%E5%BA%93.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferFacelibrary_FacelibraryAddRequest 
{
	HsviewRequest base;

	struct transferFacelibrary_FacelibraryAddRequestData
	{
		
		/** [cstr]/device/facelibrary/add */
		#define _STATIC_transferFacelibrary_FacelibraryAddRequestData_url "/device/facelibrary/add"
		CSTR url;
		/** struct of transferFacelibrary_FacelibraryAddRequestData_Content */
		struct transferFacelibrary_FacelibraryAddRequestData_Content {
			/** 人脸库名称 */
			CSTR name;
			/** define a list with struct of transferFacelibrary_FacelibraryAddRequestData_Content_ChannelsElement */
			DECLARE_LIST(struct transferFacelibrary_FacelibraryAddRequestData_Content_ChannelsElement
			{
				/** 人脸检测后智能，true, false */
				CSTR rtFaceDetect;
				/** 相似度，归一化到0~100 */
				CSTR similarity;
				/** 是否布控，true, false */
				CSTR enable;
				/** [int]设备通道Id，单通道设备默认为0 */
				int channelId;
				/** 人脸比对后智能，true, false */
				CSTR rtFaceCompa;
			}) channels;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferFacelibrary_FacelibraryAddRequest;

C_API transferFacelibrary_FacelibraryAddRequest *HSAPI_INIT(transferFacelibrary_FacelibraryAddRequest);

typedef struct transferFacelibrary_FacelibraryAddResponse 
{
	HsviewResponse base;

	struct transferFacelibrary_FacelibraryAddResponseData
	{
		
		/** 库Id */
		CSTR groupId;
 
	} data;

} transferFacelibrary_FacelibraryAddResponse;

C_API transferFacelibrary_FacelibraryAddResponse *HSAPI_INIT(transferFacelibrary_FacelibraryAddResponse);

#endif
