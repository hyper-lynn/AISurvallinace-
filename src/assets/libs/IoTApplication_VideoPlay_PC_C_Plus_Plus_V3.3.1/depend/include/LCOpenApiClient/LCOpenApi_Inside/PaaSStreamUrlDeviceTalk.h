/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 226202, Author: 112352, Date: 2024-04-22 16:58:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_PaaSStreamUrlDeviceTalk_H_
#define _LC_OPENAPI_CLIENT_PaaSStreamUrlDeviceTalk_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
	请求与设备对讲
	POST /media/delivery/talk/devices/[deviceId]
	deviceId : 类型string。设备标识。添加设备时产生的唯一标识符。
 */

typedef struct PaaSStreamUrlDeviceTalkRequest 
{
	LCOpenApiRequest base;

	struct PaaSStreamUrlDeviceTalkRequestData
	{
		
		/** 流媒体RTSV传输协议的信令加密模式，可选项，仅当scheme传输协议为RTSV系列协议（RTSV1\RTSV2\PBSV1\PBSV2\TSV1\TSV2等）时生效(PrivateEncrypt)。否则将忽略。为空或者没有此字段，等同于 NotEncrypt。 */
		CSTR encryptionMode;
		/** 客户端地址 */
		CSTR clientIp;
		/** [long] 类型int64_t。用户期望资源访问有效时间，单位：秒。可选，以响应返回的expire为准 */
		int64 duration;
		/** [bool] 返回是否是域名, 可选, 默认为false */
		BOOL domainEnable;
		/** 传输类型,可选，默认为TCP。LHTS和CQTS传输协议目前只在RTSV媒体协议上支持 */
		CSTR transport;
		/** 请求的是拉流还是推流url pull push */
		CSTR urlType;
		/** [int] 音频采样位数：8 或者 16位，非0判断 */
		int bits;
		/** 设备加密模式 0:不加密 3:三码合一 */
		CSTR encryptType;
		/** 协议类型 RTSP RTSV */
		CSTR scheme;
		/** 音频编码类型 PCM... */
		CSTR encodeType;
		/** [int] 音频采样率 采样率：8000 或者16000，非0判断 */
		int sampleRate;
		/** [bool] 是否需要重定向 false */
		BOOL locationEnable;
		/** 客户端类型 */
		CSTR clientType;

	} data;

} PaaSStreamUrlDeviceTalkRequest;

C_API PaaSStreamUrlDeviceTalkRequest *LCOPENAPI_INIT(PaaSStreamUrlDeviceTalkRequest);

typedef struct PaaSStreamUrlDeviceTalkResponse 
{
	LCOpenApiResponse base;

	struct PaaSStreamUrlDeviceTalkResponseData
	{
		
		/** 可选。针对流媒体RTSV传输协议的信令加密模式，仅当scheme传输协议为RTSV系列协议（RTSV1\RTSV2\PBSV1\PBSV2\TSV1\TSV2等）时生效。scheme指定RTSP时，或者RTSV系列协议不支持加密能力时，服务将不返回此字段。取值范围:PrivateEncrypt表示私有加密，秘钥由流媒体模块内部推导 */
		CSTR encryptionMode;
		/** 内网资源获取地址。如果是拉流则返回节点的URL,如果是推流则返回的是MTS节点的推流URL */
		CSTR internal_resource;
		/** 区域信息。返回转发服务所在的区域信息 */
		CSTR region;
		/** 地址过期时间。UTC时间，时间格式为YYYYMMDDThhmmssZ，如：20151119T161900Z 参见ISO 8601格式 */
		CSTR expire;
		/** 资源获取地址 */
		CSTR resource;
 
	} data;

} PaaSStreamUrlDeviceTalkResponse;

C_API PaaSStreamUrlDeviceTalkResponse *LCOPENAPI_INIT(PaaSStreamUrlDeviceTalkResponse);

#endif
