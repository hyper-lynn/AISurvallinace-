/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_cloudMessage_GetUserPushMessageList_H_
#define _HSVIEW_CLIENT_API_cloudMessage_GetUserPushMessageList_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
查询个人推送消息列表。
通配符参数详情如下：
			"uname":"[O]账号，手机、邮箱；加密处理：137****6985",
			"cname":"[O]通道名",
			"time":"[O]报警产生的Unix时间戳",
			"did":"[O]设备序列号",
			"cid":"[O]通道名",
			"nickname":"[O]昵称，昵称为空时取手机号/邮箱号，加密处理",
			"storagetype":"[O]云存储套餐类型",
			"remindays":"[O]剩余天数",
			"windows":"[O]不限流窗口个数",
			"windowsnums":"[O]不限流窗口编号",
			"info":"[O]设备共享、授权等详情",
			"handleResult":"[O]好友请求处理结果，通过、已拒绝",
			"userinfos":"[O]用户组信息",
			"insertTime":"消息入库时间",
			"title":"推送消息标题"
【使用平台账号签名】
 */

typedef struct cloudMessage_GetUserPushMessageListRequest 
{
	HsviewRequest base;

	struct cloudMessage_GetUserPushMessageListRequestData
	{
		
		/** [long]从该消息ID开始查询。若要从最新开始查，填-1 */
		int64 msgId;
		/** [int]需要查的最大条数，最大128 */
		int count;

	} data;

} cloudMessage_GetUserPushMessageListRequest;

C_API cloudMessage_GetUserPushMessageListRequest *HSAPI_INIT(cloudMessage_GetUserPushMessageListRequest);

typedef struct cloudMessage_GetUserPushMessageListResponse 
{
	HsviewResponse base;

	struct cloudMessage_GetUserPushMessageListResponseData
	{
		
		/** define a list with struct of cloudMessage_GetUserPushMessageListResponseData_MessagesElement */
		DECLARE_LIST(struct cloudMessage_GetUserPushMessageListResponseData_MessagesElement
		{
			/** [O]个人推送消息类型(混合云项目新增) */
			CSTR type;
			/** 产生时间，yyyyMMddTHHmmssZ格式 */
			CSTR time;
			/** [O]跳转位置 */
			CSTR skipUrl;
			/** [long]消息ID */
			int64 msgId;
			/** [O]个推详情h5地址 */
			CSTR contentH5Url;
			/** [O]通配符参数 */
			CSTR templateParam;
			/** 标题 */
			CSTR title;
		}) messages;
 
	} data;

} cloudMessage_GetUserPushMessageListResponse;

C_API cloudMessage_GetUserPushMessageListResponse *HSAPI_INIT(cloudMessage_GetUserPushMessageListResponse);

#endif
