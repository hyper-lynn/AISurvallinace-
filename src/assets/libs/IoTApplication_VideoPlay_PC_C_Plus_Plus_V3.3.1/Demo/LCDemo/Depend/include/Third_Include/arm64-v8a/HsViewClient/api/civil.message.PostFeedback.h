/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_PostFeedback_H_
#define _HSVIEW_CLIENT_API_PostFeedback_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
用户填写的用户反馈信息上传平台。
【使用平台账号签名】
 */

typedef struct PostFeedbackRequest 
{
	HsviewRequest base;

	struct PostFeedbackRequestData
	{
		
		/** [O]PC或者手机操作系统,Windows,Mac或者手机操作系统 */
		CSTR system;
		/** [O]app或者PC客户端版本 */
		CSTR version;
		/** This is a feedback text, says ... */
		CSTR content;
		/** [O]用户的邮箱地址 */
		CSTR email;

	} data;

} PostFeedbackRequest;

C_API PostFeedbackRequest *HSAPI_INIT(PostFeedbackRequest);

typedef struct PostFeedbackResponse 
{
	HsviewResponse base;

	struct PostFeedbackResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} PostFeedbackResponse;

C_API PostFeedbackResponse *HSAPI_INIT(PostFeedbackResponse);

#endif
