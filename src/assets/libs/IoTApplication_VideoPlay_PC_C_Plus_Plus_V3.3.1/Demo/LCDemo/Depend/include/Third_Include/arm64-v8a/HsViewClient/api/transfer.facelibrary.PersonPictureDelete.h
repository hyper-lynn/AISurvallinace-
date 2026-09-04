/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferFacelibrary_PersonPictureDelete_H_
#define _HSVIEW_CLIENT_API_transferFacelibrary_PersonPictureDelete_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
删除人脸库人员图片

参考PaaS协议：[删除人脸库人员图片](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E4%BA%BA%E8%84%B8%E6%99%BA%E8%83%BD%E6%93%8D%E4%BD%9C%2F%E5%88%A0%E9%99%A4%E4%BA%BA%E8%84%B8%E5%BA%93%E4%BA%BA%E5%91%98%E5%9B%BE%E7%89%87.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferFacelibrary_PersonPictureDeleteRequest 
{
	HsviewRequest base;

	struct transferFacelibrary_PersonPictureDeleteRequestData
	{
		
		/** [cstr]/device/facelibrary-person-picture/delete */
		#define _STATIC_transferFacelibrary_PersonPictureDeleteRequestData_url "/device/facelibrary-person-picture/delete"
		CSTR url;
		/** struct of transferFacelibrary_PersonPictureDeleteRequestData_Content */
		struct transferFacelibrary_PersonPictureDeleteRequestData_Content {
			/** define a list with struct of transferFacelibrary_PersonPictureDeleteRequestData_Content_PersonIdsElement */
			DECLARE_LIST(struct transferFacelibrary_PersonPictureDeleteRequestData_Content_PersonIdsElement
			{
				/** 可选，图片唯一标识符。当pictureIds为空时，则删除所有人员 */
				DECLARE_LIST(CSTR) pictureIds;
				/** 人员Id */
				CSTR personId;
			}) personIds;
			/** 库Id */
			CSTR groupId;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferFacelibrary_PersonPictureDeleteRequest;

C_API transferFacelibrary_PersonPictureDeleteRequest *HSAPI_INIT(transferFacelibrary_PersonPictureDeleteRequest);

typedef struct transferFacelibrary_PersonPictureDeleteResponse 
{
	HsviewResponse base;

	struct transferFacelibrary_PersonPictureDeleteResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} transferFacelibrary_PersonPictureDeleteResponse;

C_API transferFacelibrary_PersonPictureDeleteResponse *HSAPI_INIT(transferFacelibrary_PersonPictureDeleteResponse);

#endif
