/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_cloudMessage_PostUserFeedback_H_
#define _HSVIEW_CLIENT_API_cloudMessage_PostUserFeedback_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
用户填写的用户反馈信息上传平台

【需要使用平台账号签名】
 */

typedef struct cloudMessage_PostUserFeedbackRequest 
{
	HsviewRequest base;

	struct cloudMessage_PostUserFeedbackRequestData
	{
		
		/** [O]设备程序版本号（lorex新增） */
		CSTR deviceVersion;
		/** [O]设备型号（lorex新增） */
		CSTR deviceModel;
		/** [O]设备序列号（lorex新增） */
		CSTR deviceId;
		/** 意见反馈 */
		CSTR content;
		/** [O]用户邮箱地址 */
		CSTR email;

	} data;

} cloudMessage_PostUserFeedbackRequest;

C_API cloudMessage_PostUserFeedbackRequest *HSAPI_INIT(cloudMessage_PostUserFeedbackRequest);

typedef struct cloudMessage_PostUserFeedbackResponse 
{
	HsviewResponse base;

	struct cloudMessage_PostUserFeedbackResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} cloudMessage_PostUserFeedbackResponse;

C_API cloudMessage_PostUserFeedbackResponse *HSAPI_INIT(cloudMessage_PostUserFeedbackResponse);

#endif
