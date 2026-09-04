/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferFacelibrary_PersonPictureListGet_H_
#define _HSVIEW_CLIENT_API_transferFacelibrary_PersonPictureListGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取人脸库人员列表


pictureIds是可选的，pictureIds字段不存在或者pictureIds数组长度为空，都表示没有对应的图片唯一标识符。

参考PaaS协议：[获取人脸库人员列表](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E4%BA%BA%E8%84%B8%E6%99%BA%E8%83%BD%E6%93%8D%E4%BD%9C%2F%E8%8E%B7%E5%8F%96%E4%BA%BA%E8%84%B8%E5%BA%93%E4%BA%BA%E5%91%98%E5%88%97%E8%A1%A8.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferFacelibrary_PersonPictureListGetRequest 
{
	HsviewRequest base;

	struct transferFacelibrary_PersonPictureListGetRequestData
	{
		
		/** [cstr]/device/facelibrary-person/list */
		#define _STATIC_transferFacelibrary_PersonPictureListGetRequestData_url "/device/facelibrary-person/list"
		CSTR url;
		/** struct of transferFacelibrary_PersonPictureListGetRequestData_Content */
		struct transferFacelibrary_PersonPictureListGetRequestData_Content {
			/** 当前页码, 从0开始 */
			CSTR pageNum;
			/** 每次返回的单页最大记录数 */
			CSTR numsPerPage;
			/** 库Id */
			CSTR groupId;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferFacelibrary_PersonPictureListGetRequest;

C_API transferFacelibrary_PersonPictureListGetRequest *HSAPI_INIT(transferFacelibrary_PersonPictureListGetRequest);

typedef struct transferFacelibrary_PersonPictureListGetResponse 
{
	HsviewResponse base;

	struct transferFacelibrary_PersonPictureListGetResponseData
	{
		
		/** define a list with struct of transferFacelibrary_PersonPictureListGetResponseData_PersonIdsElement */
		DECLARE_LIST(struct transferFacelibrary_PersonPictureListGetResponseData_PersonIdsElement
		{
			/** 图片唯一标识符 */
			DECLARE_LIST(CSTR) pictureIds;
			/** 人员Id */
			CSTR personId;
		}) personIds;
 
	} data;

} transferFacelibrary_PersonPictureListGetResponse;

C_API transferFacelibrary_PersonPictureListGetResponse *HSAPI_INIT(transferFacelibrary_PersonPictureListGetResponse);

#endif
