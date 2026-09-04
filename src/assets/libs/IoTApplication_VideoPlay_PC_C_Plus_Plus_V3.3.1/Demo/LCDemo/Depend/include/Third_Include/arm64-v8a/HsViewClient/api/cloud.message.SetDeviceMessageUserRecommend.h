/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_cloudMessage_SetDeviceMessageUserRecommend_H_
#define _HSVIEW_CLIENT_API_cloudMessage_SetDeviceMessageUserRecommend_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
按消息id和用户人形意见更新消息数据

备注：


【使用平台账号签名】
 */

typedef struct cloudMessage_SetDeviceMessageUserRecommendRequest 
{
	HsviewRequest base;

	struct cloudMessage_SetDeviceMessageUserRecommendRequestData
	{
		
		/** define a list with struct of cloudMessage_SetDeviceMessageUserRecommendRequestData_MsgListElement */
		DECLARE_LIST(struct cloudMessage_SetDeviceMessageUserRecommendRequestData_MsgListElement
		{
			/** 消息ID */
			CSTR alarmId;
			/** [O]检测类型，1-AI智能检测(人形，车辆，宠物)；2-物体识别 */
			CSTR type;
			/** [O]用户提交人形检测意见，0-不准确 1-准确 */
			CSTR submit;
			/** define a list with struct of cloudMessage_SetDeviceMessageUserRecommendRequestData_MsgListElement_DetectElement */
			DECLARE_LIST(struct cloudMessage_SetDeviceMessageUserRecommendRequestData_MsgListElement_DetectElement
			{
				/** 用户提交人形检测意见，0-不准确 1-准确 */
				CSTR submit;
				/** 检测类型，1-AI智能检测(人形)；2-物体识别; 3-AI智能检测(车辆)； 4-AI智能检测(宠物) */
				CSTR type;
			}) detect;
			/** 通道号 */
			CSTR channelId;
			/** 设备ID */
			CSTR deviceId;
		}) msgList;

	} data;

} cloudMessage_SetDeviceMessageUserRecommendRequest;

C_API cloudMessage_SetDeviceMessageUserRecommendRequest *HSAPI_INIT(cloudMessage_SetDeviceMessageUserRecommendRequest);

typedef struct cloudMessage_SetDeviceMessageUserRecommendResponse 
{
	HsviewResponse base;

	struct cloudMessage_SetDeviceMessageUserRecommendResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} cloudMessage_SetDeviceMessageUserRecommendResponse;

C_API cloudMessage_SetDeviceMessageUserRecommendResponse *HSAPI_INIT(cloudMessage_SetDeviceMessageUserRecommendResponse);

#endif
