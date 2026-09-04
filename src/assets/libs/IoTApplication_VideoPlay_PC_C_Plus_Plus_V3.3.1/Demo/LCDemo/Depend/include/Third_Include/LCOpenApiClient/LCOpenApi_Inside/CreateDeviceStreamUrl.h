/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 226180, Author: 426167, Date: 2024-04-16 20:44:14 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_CreateDeviceStreamUrl_H_
#define _LC_OPENAPI_CLIENT_CreateDeviceStreamUrl_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取拉流地址

 */

typedef struct CreateDeviceStreamUrlRequest 
{
	LCOpenApiRequest base;

	struct CreateDeviceStreamUrlRequestData
	{
		
		/** [int]是否开启智能帧 */
		int assistStream;
		/** 协议类型 */
		CSTR protoType;
		/** [int]流ID */
		int recordPlayType;
		/** [int]位深 */
		int bitDepth;
		/** 对讲ID */
		CSTR callId;
		/** 开始时间 */
		CSTR beginTime;
		/** 采样率 */
		CSTR samplingRate;
		/** 出流方式 */
		CSTR type;
		/** 录像文件名 */
		CSTR recordFileName;
		/** 录像id */
		CSTR recordId;
		/** 结束时间 */
		CSTR endTime;
		/** 开始时间时间戳 */
		CSTR beginTimeStamp;
		/** paas需要 */
		CSTR location;
		/** 设备ID */
		CSTR deviceId;
		/** [int]码流类型 0 主码流 1辅码流 默认为主码流 */
		int streamType;
		/** 结束时间时间戳 */
		CSTR endTimeStamp;
		/** 音频编码格式 0 aac 1g711a */
		CSTR audioEncode;
		/** 设备类型 */
		CSTR deviceType;
		/** 流ID */
		CSTR streamId;
		/** [int]加密模式 */
		int encryptMode;
		/** 业务类型 */
		CSTR businessType;
		/** 通道ID */
		CSTR channelId;

	} data;

} CreateDeviceStreamUrlRequest;

C_API CreateDeviceStreamUrlRequest *LCOPENAPI_INIT(CreateDeviceStreamUrlRequest);

typedef struct CreateDeviceStreamUrlResponse 
{
	LCOpenApiResponse base;

	struct CreateDeviceStreamUrlResponseData
	{
		
		/** 拉流地址 */
		CSTR url;
		/** [long] 拉流时间 */
		int64 expireTime;
 
	} data;

} CreateDeviceStreamUrlResponse;

C_API CreateDeviceStreamUrlResponse *LCOPENAPI_INIT(CreateDeviceStreamUrlResponse);

#endif
