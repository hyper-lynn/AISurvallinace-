/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferFacelibrary_PersonPictureDownLoadPercent_H_
#define _HSVIEW_CLIENT_API_transferFacelibrary_PersonPictureDownLoadPercent_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取人脸库人员图片下载进度

参考PaaS协议：[获取人脸库人员图片下载进度](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E4%BA%BA%E8%84%B8%E6%99%BA%E8%83%BD%E6%93%8D%E4%BD%9C%2F%E8%8E%B7%E5%8F%96%E4%BA%BA%E8%84%B8%E5%BA%93%E4%BA%BA%E5%91%98%E5%9B%BE%E7%89%87%E4%B8%8B%E8%BD%BD%E8%BF%9B%E5%BA%A6.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferFacelibrary_PersonPictureDownLoadPercentRequest 
{
	HsviewRequest base;

	struct transferFacelibrary_PersonPictureDownLoadPercentRequestData
	{
		
		/** [cstr]/device/facelibrary-person-picture/download-percent */
		#define _STATIC_transferFacelibrary_PersonPictureDownLoadPercentRequestData_url "/device/facelibrary-person-picture/download-percent"
		CSTR url;
		/** struct of transferFacelibrary_PersonPictureDownLoadPercentRequestData_Content */
		struct transferFacelibrary_PersonPictureDownLoadPercentRequestData_Content {
			/** 库Id */
			CSTR groupId;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferFacelibrary_PersonPictureDownLoadPercentRequest;

C_API transferFacelibrary_PersonPictureDownLoadPercentRequest *HSAPI_INIT(transferFacelibrary_PersonPictureDownLoadPercentRequest);

typedef struct transferFacelibrary_PersonPictureDownLoadPercentResponse 
{
	HsviewResponse base;

	struct transferFacelibrary_PersonPictureDownLoadPercentResponseData
	{
		
		/** 未建模 */
		CSTR modelToDo;
		/** 建模失败 */
		CSTR modelFail;
		/** 建模中 */
		CSTR modelDoing;
		/** 建模成功 */
		CSTR modelSuccess;
 
	} data;

} transferFacelibrary_PersonPictureDownLoadPercentResponse;

C_API transferFacelibrary_PersonPictureDownLoadPercentResponse *HSAPI_INIT(transferFacelibrary_PersonPictureDownLoadPercentResponse);

#endif
