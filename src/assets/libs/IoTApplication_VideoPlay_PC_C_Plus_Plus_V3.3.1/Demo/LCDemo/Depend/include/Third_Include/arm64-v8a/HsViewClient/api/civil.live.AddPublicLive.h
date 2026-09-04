/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_AddPublicLive_H_
#define _HSVIEW_CLIENT_API_AddPublicLive_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
创建摄像头直播分享。
当直播方式是设备device时，返回的结果中streamId才有效。
非设备方式，streamId无效。

错误码：
1、1501 : 视频直播已经存在
2、1322 ：设备已经自定义加密密钥

videoLimit   -1:不限制路数    其它:具体限制数

【使用平台账号签名】
 */

typedef struct AddPublicLiveRequest 
{
	HsviewRequest base;

	struct AddPublicLiveRequestData
	{
		
		/** 直播类型, device表示设备,rtsp表示rtsp码流源,record表示录像 */
		CSTR type;
		/** 项目ID,app为LC,开放平台为LCO，直接活动为LCL,微信助手实时视频为RP */
		CSTR pid;
		/** [long]直播结束时间，UNIX时间戳，单位秒 */
		int64 endTime;
		/** [bool]是否需要直播录像，该字段不存在时，默认是不需要 */
		BOOL needHis;
		/** [int][O]限制并发路数  -1:不限制路数    其它:具体限制数 */
		int videoLimit;
		/** [O]流量统计时所属用户的唯一标识，当前用userId */
		CSTR owner;
		/** [O]所属平台 open:开放平台 base:乐橙平台 */
		CSTR ownerType;
		/** [bool][O]直播的音频使能开关，默认为true */
		BOOL audioFlag;
		/** [O]直播的标题 */
		CSTR title;
		/** [O]设置视频封面,这个设置优先级比coverUpdate高 */
		CSTR coverUrl;
		/** [int]视频封面实时更新间隔,单位秒,为0表示不开启实时封面 */
		int coverUpdate;
		/** [O]直播分发方式,取值为:cdn或者proxy, 默认为proxy方式，app和PC客户端只能用proxy方式 */
		CSTR mode;
		/** struct of AddPublicLiveRequestData_Source */
		struct AddPublicLiveRequestData_Source {
			/** struct of AddPublicLiveRequestData_Source_Device */
			struct AddPublicLiveRequestData_Source_Device {
				/** 0表示主码流，1表示辅码流。逗号分隔 */
				CSTR streamId;
				/** 通道号 */
				CSTR channelId;
				/** 设备ID */
				CSTR deviceId;
			} device;
			/** struct of AddPublicLiveRequestData_Source_Stream */
			struct AddPublicLiveRequestData_Source_Stream {
				/** rtsp://192.168.20.136:5000/xxx666,标准rtsp源 */
				CSTR url;
			} stream;
			/** struct of AddPublicLiveRequestData_Source_Record */
			struct AddPublicLiveRequestData_Source_Record {
				/** 设备本地开始时间,yyyyMMddTHHmmss格式 */
				CSTR begin;
				/** [O]录像类型，为空表示告警录像类型 */
				CSTR type;
				/** 设备本地结束时间,yyyyMMddTHHmmss格式 */
				CSTR end;
				/** 通道号 */
				CSTR channelId;
				/** 设备ID */
				CSTR deviceId;
			} record;
		} source;
		/** [long]直播开始时间，UNIX时间戳，单位秒 */
		int64 beginTime;

	} data;

} AddPublicLiveRequest;

C_API AddPublicLiveRequest *HSAPI_INIT(AddPublicLiveRequest);

typedef struct AddPublicLiveResponse 
{
	HsviewResponse base;

	struct AddPublicLiveResponseData
	{
		
		/** 直播分享的token */
		CSTR token;
		/** 直播网页http地址 */
		CSTR page;
		/** define a list with struct of AddPublicLiveResponseData_StreamsElement */
		DECLARE_LIST(struct AddPublicLiveResponseData_StreamsElement
		{
			/** hls https访问地址 */
			CSTR urlHttps;
			/** 直播流hls访问地址 */
			CSTR url;
			/** [int] 0表示主码流，1表示辅码流,当前只针对device方式才有效 */
			int streamId;
			/** 直播实时视频的封面地址，为空表示没有开启实时封面 */
			CSTR coverUrl;
		}) streams;
 
	} data;

} AddPublicLiveResponse;

C_API AddPublicLiveResponse *HSAPI_INIT(AddPublicLiveResponse);

#endif
