/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 227286, Author: 251672, Date: 2024-09-02 17:23:07 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_GetRtspUrl_H_
#define _LC_OPENAPI_CLIENT_GetRtspUrl_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取RtspUrl

 */

typedef struct GetRtspUrlRequest 
{
	LCOpenApiRequest base;

	struct GetRtspUrlRequestData
	{
		
		/** [String]pc客户端拉流窗口号，pc5.1新增字段，针对pc有效 */
		CSTR windowNum;
		/** [int][O]限制并发路数 -1:不限制路数    其它:具体限制数 */
		int videoLimit;
		/** [String]设备级对讲与通道级对讲类型区分，device：表示设备级对讲，channel：表示通道级对讲 */
		CSTR deviceType;
		/** [String]是否跳过回环认证：true-跳过, false-不跳过（针对APP自己走P2P校验过的，跳过校验优化）；无该字段时，国内海外按老逻辑处理 */
		CSTR skipAuth;
		/** 一次性token */
		CSTR rtspToken;
		/** 开发者AK */
		CSTR project;
		/** [bool][O]是否限流 */
		BOOL timeLimit;
		/** [String]请求拉流分类，real：实时预览；playbackByTime：按时间回放；playbackByRecordId：按文件id回放；talk：对讲 */
		CSTR requestType;
		/** [String]所要请求码流的加密类型 */
		CSTR encrypt;
		/** [String]RTSV1:支持私有协议拉流,RTSP:RTSP拉流 参数空默认为RTSP拉流 */
		CSTR type;
		/** [String]录像文件id，requestType为playbackByRecordId时必填 */
		CSTR recordId;
		/** [String]流量统计时所属用户的唯一标识，当前用userId */
		CSTR owner;
		/** 共享链路 */
		CSTR design;
		/** [String]设备ID */
		CSTR deviceId;
		/** [String]辅助帧(开放平台5.3需求新增参数) */
		CSTR assistStream;
		/** [String]设置拉流时长，单位：min */
		CSTR duration;
		/** 用户token */
		CSTR token;
		/** [String]回放结束时间，requestType为playbackByTime时必填 */
		CSTR endTime;
		/** [String]主、辅码流编号，0或者1 */
		CSTR streamId;
		/** [String]通道号 */
		CSTR channelId;
		/** [String]所属平台open:开放平台 base:乐橙平台 */
		CSTR ownerType;
		/** [String]回放开始时间，requestType为playbackByTime时必填 */
		CSTR startTime;

	} data;

} GetRtspUrlRequest;

C_API GetRtspUrlRequest *LCOPENAPI_INIT(GetRtspUrlRequest);

typedef struct GetRtspUrlResponse 
{
	LCOpenApiResponse base;

	struct GetRtspUrlResponseData
	{
		
		/** [String]返回Tls链路加密的rtsp优化拉流地址 */
		CSTR tlsUrl;
		/** [String]返回rtsp优化拉流地址 */
		CSTR url;
 
	} data;

} GetRtspUrlResponse;

C_API GetRtspUrlResponse *LCOPENAPI_INIT(GetRtspUrlResponse);

#endif
