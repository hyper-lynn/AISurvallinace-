/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_cloudMessage_GetUserPushMessageDetail_H_
#define _HSVIEW_CLIENT_API_cloudMessage_GetUserPushMessageDetail_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
根据消息id查询用户的推送消息
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
type分类待定。

【使用平台账号签名】
 */

typedef struct cloudMessage_GetUserPushMessageDetailRequest 
{
	HsviewRequest base;

	struct cloudMessage_GetUserPushMessageDetailRequestData
	{
		
		/** [long]消息id */
		int64 msgId;

	} data;

} cloudMessage_GetUserPushMessageDetailRequest;

C_API cloudMessage_GetUserPushMessageDetailRequest *HSAPI_INIT(cloudMessage_GetUserPushMessageDetailRequest);

typedef struct cloudMessage_GetUserPushMessageDetailResponse 
{
	HsviewResponse base;

	struct cloudMessage_GetUserPushMessageDetailResponseData
	{
		
		/** 个人推送类型 */
		CSTR type;
		/** [O]跳转位置 */
		CSTR skipUrl;
		/** [O]通配符参数 */
		CSTR templateParam;
		/** [O]设备序列号 */
		CSTR deviceId;
		/** 产生的UTC时间，yyyyMMddTHHmmssZ格式 */
		CSTR time;
		/** [O]个推详情h5地址 */
		CSTR contentH5Url;
		/** [long]消息ID */
		int64 msgId;
		/** [O]通道号 */
		CSTR channelId;
		/** 内容 */
		CSTR content;
		/** 标题 */
		CSTR title;
 
	} data;

} cloudMessage_GetUserPushMessageDetailResponse;

C_API cloudMessage_GetUserPushMessageDetailResponse *HSAPI_INIT(cloudMessage_GetUserPushMessageDetailResponse);

#endif
