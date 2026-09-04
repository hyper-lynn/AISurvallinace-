/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferFacelibrary_FacelibraryModify_H_
#define _HSVIEW_CLIENT_API_transferFacelibrary_FacelibraryModify_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
修改人脸库

period（计划周期），参考计划周期定义：http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F&s=pd

参考PaaS协议：[修改人脸库](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E4%BA%BA%E8%84%B8%E6%99%BA%E8%83%BD%E6%93%8D%E4%BD%9C%2F%E4%BF%AE%E6%94%B9%E4%BA%BA%E8%84%B8%E5%BA%93.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferFacelibrary_FacelibraryModifyRequest 
{
	HsviewRequest base;

	struct transferFacelibrary_FacelibraryModifyRequestData
	{
		
		/** [cstr]/device/facelibrary/modify */
		#define _STATIC_transferFacelibrary_FacelibraryModifyRequestData_url "/device/facelibrary/modify"
		CSTR url;
		/** struct of transferFacelibrary_FacelibraryModifyRequestData_Content */
		struct transferFacelibrary_FacelibraryModifyRequestData_Content {
			/** define a list with struct of transferFacelibrary_FacelibraryModifyRequestData_Content_ChannelsElement */
			DECLARE_LIST(struct transferFacelibrary_FacelibraryModifyRequestData_Content_ChannelsElement
			{
				/** 人脸检测后智能,true,false */
				CSTR rtFaceDetect;
				/** define a list with struct of transferFacelibrary_FacelibraryModifyRequestData_Content_ChannelsElement_RulesElement */
				DECLARE_LIST(struct transferFacelibrary_FacelibraryModifyRequestData_Content_ChannelsElement_RulesElement
				{
					/** 生效的结束时间，时间格式为THHMMSS */
					CSTR endTime;
					/** 生效的开始时间，时间格式为THHMMSS */
					CSTR beginTime;
					/** 计划周期 */
					CSTR period;
				}) rules;
				/** 相识度，归一化到0~100 */
				CSTR similarity;
				/** 是否布控,true,false */
				CSTR enable;
				/** [int]备通道Id，单通道设备默认为0 */
				int channelId;
				/** 人脸比对后智能,true,false */
				CSTR rtFaceCompa;
			}) channels;
			/** 人脸库名称 */
			CSTR name;
			/** 库Id */
			CSTR groupId;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferFacelibrary_FacelibraryModifyRequest;

C_API transferFacelibrary_FacelibraryModifyRequest *HSAPI_INIT(transferFacelibrary_FacelibraryModifyRequest);

typedef struct transferFacelibrary_FacelibraryModifyResponse 
{
	HsviewResponse base;

	struct transferFacelibrary_FacelibraryModifyResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} transferFacelibrary_FacelibraryModifyResponse;

C_API transferFacelibrary_FacelibraryModifyResponse *HSAPI_INIT(transferFacelibrary_FacelibraryModifyResponse);

#endif
