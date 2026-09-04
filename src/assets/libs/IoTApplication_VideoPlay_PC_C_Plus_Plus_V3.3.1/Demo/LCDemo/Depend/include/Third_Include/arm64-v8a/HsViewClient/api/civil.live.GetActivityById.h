/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetActivityById_H_
#define _HSVIEW_CLIENT_API_GetActivityById_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
分页获取活动列表

针对streams数组长度为1时，可能streamId不存在（当前只针对device方式才有效,rtsp等方式不存在这个字段）

项目属性为x时，url做必须字段返回；
当type为1（直播活动）时，数组lives下token、title、playTimes、url、coverUrl为必须字段返回；
当type为6（精彩回放）时，数组lives下recBeginTime、recEndTime为必须字段返回；
当type为2（资讯文章）时， beginTime、endTime为可选字段，其余作必须字段返回。


错误码：
1、1504 ：直播活动不存在

【不鉴权】
 */

typedef struct GetActivityByIdRequest 
{
	HsviewRequest base;

	struct GetActivityByIdRequestData
	{
		
		/** [long]活动id */
		int64 activityId;

	} data;

} GetActivityByIdRequest;

C_API GetActivityByIdRequest *HSAPI_INIT(GetActivityByIdRequest);

typedef struct GetActivityByIdResponse 
{
	HsviewResponse base;

	struct GetActivityByIdResponseData
	{
		
		/** [O]用户上传参加信息限制 */
		CSTR joinLimits;
		/** [O]活动规则 */
		CSTR rules;
		/** define a list with struct of GetActivityByIdResponseData_DescriptionElement */
		DECLARE_LIST(struct GetActivityByIdResponseData_DescriptionElement
		{
			/** 标题名称 */
			CSTR name;
			/** 标题相关的内容 */
			CSTR content;
		}) description;
		/** [long]活动id */
		int64 activityId;
		/** [bool]true表示允许评论, false表示禁止评论 */
		BOOL commentFlag;
		/** [int]当前评论数 */
		int commentNumber;
		/** [int][O]育儿活动状态 2-进行中，3-已结束 */
		int status;
		/** [long][O]开始时间。Unix时间（单位秒） */
		int64 beginTime;
		/** [int]类型, 1:直播活动，2：资讯文章，3：投稿活动，4：试用活动，5：线下活动，6：精彩回放 */
		int type;
		/** [long]点赞次数 */
		int64 likeTimes;
		/** [long][O]结束时间。Unix时间（单位秒） */
		int64 endTime;
		/** [O]文章或活动的H5页面链接 */
		CSTR url;
		/** [O]文章或活动的概述 */
		CSTR summary;
		/** 分享的链接 */
		CSTR shareUrl;
		/** [long][O]参加活动的用户数 */
		int64 joinNum;
		/** 活动名称 */
		CSTR name;
		/** 活动封面地址 */
		CSTR coverUrl;
		/** 活动地址 */
		CSTR address;
		/** [long]播放次数 */
		int64 playTimes;
		/** define a list with struct of GetActivityByIdResponseData_LivesElement */
		DECLARE_LIST(struct GetActivityByIdResponseData_LivesElement
		{
			/** [long][O]回放录像结束时间，Unix时间（单位秒） */
			int64 recEndTime;
			/** [O]直播源的token */
			CSTR token;
			/** [O]直播源标题 */
			CSTR title;
			/** [int]视频文件的长度，单位秒 */
			int recLength;
			/** [long][O]回放录像开始时间，Unix时间（单位秒） */
			int64 recBeginTime;
			/** [int][O]当前直播通道的播放次数 */
			int playTimes;
			/** define a list with struct of GetActivityByIdResponseData_LivesElement_StreamsElement */
			DECLARE_LIST(struct GetActivityByIdResponseData_LivesElement_StreamsElement
			{
				/** [int][O] 0表示主码流，1表示辅码流,当前只针对device方式才有效,rtsp等方式不存在这个字段，历史直播无效 */
				int streamId;
				/** [O]直播流hls访问地址 */
				CSTR url;
				/** [O]直播实时视频的封面地址 */
				CSTR coverUrl;
			}) streams;
		}) lives;
		/** [O]文章或活动的标签信息 */
		CSTR tag;
 
	} data;

} GetActivityByIdResponse;

C_API GetActivityByIdResponse *HSAPI_INIT(GetActivityByIdResponse);

#endif
