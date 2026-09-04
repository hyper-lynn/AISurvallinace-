/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_thingsMedia_GetRealTransferStreamUrl_H_
#define _HSVIEW_CLIENT_API_thingsMedia_GetRealTransferStreamUrl_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取实时流转发地址。

encrypt取值如下：
0：表示普通码流，不加密。
1：表示请求加密的码流，I帧全加密。
2: 表示请求加密的码流，0x95扩展头加密。
3：表示有TCM能力集设备请求加密的码流，aes256加密。

videoLimit   -1:不限制路数    其它:具体限制数

【使用平台账号签名】
 */

typedef struct thingsMedia_GetRealTransferStreamUrlRequest 
{
	HsviewRequest base;

	struct thingsMedia_GetRealTransferStreamUrlRequestData
	{
		
		/** [O]所要请求码流的加密类型 */
		CSTR encrypt;
		/** [O]RTSV1:支持私有协议拉流,RTSP:RTSP拉流 参数空默认为RTSP拉流 */
		CSTR type;
		/** [O] 辅助帧(开放平台5.3需求新增参数) */
		CSTR assistStream;
		/** [O]pc客户端拉流窗口号，pc5.1新增字段，针对pc有效 */
		CSTR windowNum;
		/** [O]设置拉流时长，单位：min */
		CSTR duration;
		/** [O]流量统计时所属用户的唯一标识，当前用userId */
		CSTR owner;
		/** [O]开放平台侧指定MTS集群名，暂时传opencluster */
		CSTR specialMtsCluster;
		/** 设备ID */
		CSTR deviceId;
		/** [O]普通对讲与呼叫对讲类型区分(当该字段不存在或者为空，表示普通对讲)，call：表示呼叫对讲，talk：表示普通对讲 */
		CSTR talkType;
		/** [O]是否跳过回环认证：true-跳过, false-不跳过（针对APP自己走P2P校验过的，跳过校验优化）；无该字段时，国内海外按老逻辑处理 */
		CSTR skipAuth;
		/** [O]方案一或二的类型区分(平台逻辑处理需要，当该字段不存在，表示方案二) first：方案一，实时流和语音对讲，两个不同的链路 second：方案二，实时流和语音对讲，在同一个链路 */
		CSTR design;
		/** [int][O]限制并发路数 -1:不限制路数    其它:具体限制数 */
		int videoLimit;
		/** [O]所属平台open:开放平台 base:乐橙平台 */
		CSTR ownerType;
		/** 通道号 */
		CSTR channelId;
		/** [bool][O]是否限流 */
		BOOL timeLimit;
		/** 主、辅码流编号，0或者1 */
		CSTR streamId;

	} data;

} thingsMedia_GetRealTransferStreamUrlRequest;

C_API thingsMedia_GetRealTransferStreamUrlRequest *HSAPI_INIT(thingsMedia_GetRealTransferStreamUrlRequest);

typedef struct thingsMedia_GetRealTransferStreamUrlResponse 
{
	HsviewResponse base;

	struct thingsMedia_GetRealTransferStreamUrlResponseData
	{
		
		/** [O]mts区域信息,直播功能使用 */
		CSTR region;
		/** [O]MTS建立的转发源地址 */
		CSTR resource;
		/** [O]直播拉流源地址 */
		CSTR internal_resource;
		/** [O]MTS建立的TLS转发源地址 */
		CSTR tls_resource;
 
	} data;

} thingsMedia_GetRealTransferStreamUrlResponse;

C_API thingsMedia_GetRealTransferStreamUrlResponse *HSAPI_INIT(thingsMedia_GetRealTransferStreamUrlResponse);

#endif
