/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferFacelibrary_PersonPictureAdd_H_
#define _HSVIEW_CLIENT_API_transferFacelibrary_PersonPictureAdd_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
新增人脸库人员信息

pictureIds是可选的，pictureIds字段不存在或者pictureIds数组长度为空，都表示没有对应的图片唯一标识符。

参考PaaS协议：[新增人脸库人员信息](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E4%BA%BA%E8%84%B8%E6%99%BA%E8%83%BD%E6%93%8D%E4%BD%9C%2F%E6%96%B0%E5%A2%9E%E4%BA%BA%E8%84%B8%E5%BA%93%E4%BA%BA%E5%91%98%E4%BF%A1%E6%81%AF.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferFacelibrary_PersonPictureAddRequest 
{
	HsviewRequest base;

	struct transferFacelibrary_PersonPictureAddRequestData
	{
		
		/** [cstr]/device/facelibrary-persons/add */
		#define _STATIC_transferFacelibrary_PersonPictureAddRequestData_url "/device/facelibrary-persons/add"
		CSTR url;
		/** struct of transferFacelibrary_PersonPictureAddRequestData_Content */
		struct transferFacelibrary_PersonPictureAddRequestData_Content {
			/** define a list with struct of transferFacelibrary_PersonPictureAddRequestData_Content_PersonInfoElement */
			DECLARE_LIST(struct transferFacelibrary_PersonPictureAddRequestData_Content_PersonInfoElement
			{
				/** 图片URL，此处url是已授权的具有时效性的，具体时长暂定两小时 */
				DECLARE_LIST(CSTR) pictureUrl;
				/** [O]国籍，符合ISO3166规范 */
				CSTR country;
				/** [O]证件类型: IC：身份证,Passport：护照,Unknown：未知 */
				CSTR certType;
				/** [O]证件编号 */
				CSTR certNo;
				/** [O]生日，格式为yyyyMMdd */
				CSTR birthday;
				/** [O]性别。Man：男；Woman：女 */
				CSTR sex;
				/** [O]地址 */
				CSTR address;
				/** 姓名 */
				CSTR name;
				/** [O]城市 */
				CSTR city;
				/** [O]省份 */
				CSTR province;
			}) personInfo;
			/** 库Id */
			CSTR groupId;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferFacelibrary_PersonPictureAddRequest;

C_API transferFacelibrary_PersonPictureAddRequest *HSAPI_INIT(transferFacelibrary_PersonPictureAddRequest);

typedef struct transferFacelibrary_PersonPictureAddResponse 
{
	HsviewResponse base;

	struct transferFacelibrary_PersonPictureAddResponseData
	{
		
		/** define a list with struct of transferFacelibrary_PersonPictureAddResponseData_PersonIdsElement */
		DECLARE_LIST(struct transferFacelibrary_PersonPictureAddResponseData_PersonIdsElement
		{
			/** 图片唯一标识符 */
			DECLARE_LIST(CSTR) pictureIds;
			/** 人员Id */
			CSTR personId;
		}) personIds;
 
	} data;

} transferFacelibrary_PersonPictureAddResponse;

C_API transferFacelibrary_PersonPictureAddResponse *HSAPI_INIT(transferFacelibrary_PersonPictureAddResponse);

#endif
