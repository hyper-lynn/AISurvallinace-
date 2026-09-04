/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_thingsMedia_GetPlaybackTransferStreamUrlByTime_H_
#define _HSVIEW_CLIENT_API_thingsMedia_GetPlaybackTransferStreamUrlByTime_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
注：乐橙不推荐使用，Easy4ip禁止使用。
获取按时间播放本地录像的转发地址。

startTime和endTime取值可以有两种：
1、1970年来秒数，即Unix时间戳，这是原先的方式。
2、可以填写设备本地时间，格式为：2014_07_25_14_41_00


encrypt取值如下：
0：表示普通码流，不加密。
1：表示请求加密的码流，I帧全加密。
2: 表示请求加密的码流，0x95扩展头加密。
3：表示有TCM能力集设备请求加密的码流，aes256加密。

[码流类型](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E6%9C%AC%E5%9C%B0%E5%BD%95%E5%83%8F%E5%9B%BE%E7%89%87%E4%BF%A1%E6%81%AF%2FHome.md&s=pd)



【使用平台账号签名】
 */

typedef struct thingsMedia_GetPlaybackTransferStreamUrlByTimeRequest 
{
	HsviewRequest base;

	struct thingsMedia_GetPlaybackTransferStreamUrlByTimeRequestData
	{
		
		/** [O]所要请求码流的加密类型 */
		CSTR encrypt;
		/** [O]PBSV1:支持私有协议拉流,RTSP:RTSP拉流 参数空默认为RTSP拉流 */
		CSTR type;
		/** [O]结束时间 */
		CSTR endTime;
		/** [O]流量统计时所属用户的唯一标识，当前用userId */
		CSTR owner;
		/** [O] 当前观看者账号 */
		CSTR viewer;
		/** 设备ID */
		CSTR deviceId;
		/** [O]开放平台侧指定MTS集群名，暂时传opencluster */
		CSTR specialMtsCluster;
		/** [O]所属平台open:开放平台 base:乐橙平台 */
		CSTR ownerType;
		/** 开始时间 */
		CSTR startTime;
		/** [O]码流类型 0:主码流,1:辅码流1,2:辅码流2,3:辅码流3 */
		CSTR streamId;
		/** 通道号 */
		CSTR channelId;

	} data;

} thingsMedia_GetPlaybackTransferStreamUrlByTimeRequest;

C_API thingsMedia_GetPlaybackTransferStreamUrlByTimeRequest *HSAPI_INIT(thingsMedia_GetPlaybackTransferStreamUrlByTimeRequest);

typedef struct thingsMedia_GetPlaybackTransferStreamUrlByTimeResponse 
{
	HsviewResponse base;

	struct thingsMedia_GetPlaybackTransferStreamUrlByTimeResponseData
	{
		
		/** 转发源地址，如：rtsp://202.30.1.8:554/stream/12345678 */
		CSTR resource;
		/** 直播拉流源地址 */
		CSTR tls_resource;
 
	} data;

} thingsMedia_GetPlaybackTransferStreamUrlByTimeResponse;

C_API thingsMedia_GetPlaybackTransferStreamUrlByTimeResponse *HSAPI_INIT(thingsMedia_GetPlaybackTransferStreamUrlByTimeResponse);

#endif
