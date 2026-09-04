/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_thingsMedia_GetPlaybackTransferStreamUrlByFile_H_
#define _HSVIEW_CLIENT_API_thingsMedia_GetPlaybackTransferStreamUrlByFile_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取按文件播放本地录像的转发地址。

recordId:设备本地路径，通过查询录像接口返回，如：mnt/sd/2017-08-11/001/dav/04/04.44.53-04.45.52[M][0@0]

encrypt取值如下：
0：表示普通码流，不加密。
1：表示请求加密的码流，I帧全加密。
2: 表示请求加密的码流，0x95扩展头加密。
3：表示有TCM能力集设备请求加密的码流，aes256加密。


【使用平台账号签名】
 */

typedef struct thingsMedia_GetPlaybackTransferStreamUrlByFileRequest 
{
	HsviewRequest base;

	struct thingsMedia_GetPlaybackTransferStreamUrlByFileRequestData
	{
		
		/** [O]所要请求码流的加密类型 */
		CSTR encrypt;
		/** [O]RTSV1:支持私有协议拉流,RTSP:RTSP拉流 参数空默认为RTSP拉流 */
		CSTR type;
		/** 文件名 */
		CSTR recordId;
		/** [O]流量统计时所属用户的唯一标识，当前用userId */
		CSTR owner;
		/** [O] 当前观看者账号 */
		CSTR viewer;
		/** 设备ID */
		CSTR deviceId;
		/** [O]所属平台open:开放平台 base:乐橙平台 */
		CSTR ownerType;
		/** 通道号 */
		CSTR channelId;
		/** [O]开放平台侧指定MTS集群名，暂时传opencluster */
		CSTR specialMtsCluster;

	} data;

} thingsMedia_GetPlaybackTransferStreamUrlByFileRequest;

C_API thingsMedia_GetPlaybackTransferStreamUrlByFileRequest *HSAPI_INIT(thingsMedia_GetPlaybackTransferStreamUrlByFileRequest);

typedef struct thingsMedia_GetPlaybackTransferStreamUrlByFileResponse 
{
	HsviewResponse base;

	struct thingsMedia_GetPlaybackTransferStreamUrlByFileResponseData
	{
		
		/** [O]mts区域信息,直播功能使用 */
		CSTR region;
		/** [O]直播拉流源地址 */
		CSTR internal_resource;
		/** 转发源地址，如：rtsp://202.30.1.8:554/stream/12345678 */
		CSTR resource;
		/** [O]MTS建立的TLS转发源地址 */
		CSTR tls_resource;
 
	} data;

} thingsMedia_GetPlaybackTransferStreamUrlByFileResponse;

C_API thingsMedia_GetPlaybackTransferStreamUrlByFileResponse *HSAPI_INIT(thingsMedia_GetPlaybackTransferStreamUrlByFileResponse);

#endif
