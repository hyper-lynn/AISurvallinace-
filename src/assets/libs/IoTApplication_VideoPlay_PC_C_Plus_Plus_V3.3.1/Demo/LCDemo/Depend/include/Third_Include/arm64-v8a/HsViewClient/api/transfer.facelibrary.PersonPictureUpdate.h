/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferFacelibrary_PersonPictureUpdate_H_
#define _HSVIEW_CLIENT_API_transferFacelibrary_PersonPictureUpdate_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
更新人脸库人员信息

参考PaaS协议：[更新人脸库人员信息](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E4%BA%BA%E8%84%B8%E6%99%BA%E8%83%BD%E6%93%8D%E4%BD%9C%2F%E6%9B%B4%E6%96%B0%E4%BA%BA%E8%84%B8%E5%BA%93%E4%BA%BA%E5%91%98%E4%BF%A1%E6%81%AF.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferFacelibrary_PersonPictureUpdateRequest 
{
	HsviewRequest base;

	struct transferFacelibrary_PersonPictureUpdateRequestData
	{
		
		/** [cstr]/device/facelibrary-person/update */
		#define _STATIC_transferFacelibrary_PersonPictureUpdateRequestData_url "/device/facelibrary-person/update"
		CSTR url;
		/** struct of transferFacelibrary_PersonPictureUpdateRequestData_Content */
		struct transferFacelibrary_PersonPictureUpdateRequestData_Content {
			/** struct of transferFacelibrary_PersonPictureUpdateRequestData_Content_PersonInfo */
			struct transferFacelibrary_PersonPictureUpdateRequestData_Content_PersonInfo {
				/** [O]国籍，符合ISO3166规范 */
				CSTR country;
				/** define a list with struct of transferFacelibrary_PersonPictureUpdateRequestData_Content_PersonInfo_PicturesElement */
				DECLARE_LIST(struct transferFacelibrary_PersonPictureUpdateRequestData_Content_PersonInfo_PicturesElement
				{
					/** [O]图片Id */
					CSTR pictureId;
					/** [O]图片URL。当pictureId有效时，pictureUrl有效。当携带URL时，标明需要更新图片二进制数据 */
					CSTR pictureUrl;
				}) pictures;
				/** 人员Id */
				CSTR personId;
				/** [O]证件编号 */
				CSTR certNo;
				/** [O]证件类型: IC：身份证,Passport：护照,Unknown：未知 */
				CSTR certType;
				/** [O]生日，格式为yyyyMMdd */
				CSTR birthday;
				/** [O]性别。Man：男；Woman：女 */
				CSTR sex;
				/** [O]地址 */
				CSTR address;
				/** [O]城市 */
				CSTR city;
				/** [O]姓名 */
				CSTR name;
				/** [O]省份 */
				CSTR province;
			} personInfo;
			/** 库Id */
			CSTR groupId;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferFacelibrary_PersonPictureUpdateRequest;

C_API transferFacelibrary_PersonPictureUpdateRequest *HSAPI_INIT(transferFacelibrary_PersonPictureUpdateRequest);

typedef struct transferFacelibrary_PersonPictureUpdateResponse 
{
	HsviewResponse base;

	struct transferFacelibrary_PersonPictureUpdateResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} transferFacelibrary_PersonPictureUpdateResponse;

C_API transferFacelibrary_PersonPictureUpdateResponse *HSAPI_INIT(transferFacelibrary_PersonPictureUpdateResponse);

#endif
