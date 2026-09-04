/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_thingsMedia_GetTalkTransferStreamUrl_H_
#define _HSVIEW_CLIENT_API_thingsMedia_GetTalkTransferStreamUrl_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取语音对讲转发地址。

encrypt取值如下：
0：表示普通码流，不加密。
1：表示请求加密的码流，I帧全加密。
2: 表示请求加密的码流，0x95扩展头加密。
3：表示有TCM能力集设备请求加密的码流，aes256加密。

【使用平台账号签名】
 */

typedef struct thingsMedia_GetTalkTransferStreamUrlRequest 
{
	HsviewRequest base;

	struct thingsMedia_GetTalkTransferStreamUrlRequestData
	{
		
		/** [O]所要请求码流的加密类型 */
		CSTR encrypt;
		/** [O]拉流协议类型(当该字段不存在，表示RTSP拉流)，RTSV1：表示私有协议拉流，RTSP：表示RTSP拉流 */
		CSTR type;
		/** [O]是否需要辅助帧，当url为实时流时有效(当该字段不存在或者为空，表示不需要辅助帧)，true：表示需要辅助帧，false：表示不需要辅助帧 */
		CSTR assistStream;
		/** [O] 当前观看者账号 */
		CSTR viewer;
		/** 设备ID */
		CSTR deviceId;
		/** [O]普通对讲与呼叫对讲类型区分(当该字段不存在或者为空，表示普通对讲)，call：表示呼叫对讲，talk：表示普通对讲 */
		CSTR talkType;
		/** [O]方案一或二的类型区分(平台逻辑处理需要，当该字段不存在，表示方案二) first：方案一，实时流和语音对讲，两个不同的链路 second：方案二，实时流和语音对讲，在同一个链路 */
		CSTR design;
		/** [O]主辅流编号 0-主码流,1-辅码流1,2-辅码流2,3-辅码流3 */
		CSTR streamId;
		/** [O]通道号 */
		CSTR channelId;
		/** [O]开放平台侧指定MTS集群名，暂时传opencluster */
		CSTR specialMtsCluster;
		/** [O]设备级对讲与通道级对讲类型区分(当该字段不存在或者为空，表示设备级对讲)，device：表示设备级对讲，channel：表示通道级对讲 */
		CSTR deviceType;

	} data;

} thingsMedia_GetTalkTransferStreamUrlRequest;

C_API thingsMedia_GetTalkTransferStreamUrlRequest *HSAPI_INIT(thingsMedia_GetTalkTransferStreamUrlRequest);

typedef struct thingsMedia_GetTalkTransferStreamUrlResponse 
{
	HsviewResponse base;

	struct thingsMedia_GetTalkTransferStreamUrlResponseData
	{
		
		/** 转发源地址，如：rtsp://202.30.1.8:554/stream/12345678 */
		CSTR resource;
		/** 直播拉流源地址 */
		CSTR tls_resource;
 
	} data;

} thingsMedia_GetTalkTransferStreamUrlResponse;

C_API thingsMedia_GetTalkTransferStreamUrlResponse *HSAPI_INIT(thingsMedia_GetTalkTransferStreamUrlResponse);

#endif
