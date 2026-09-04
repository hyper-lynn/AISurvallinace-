/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 226113, Author: 112352, Date: 2024-04-11 09:32:00 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_PaaSStreamUrlVisualTalk_H_
#define _LC_OPENAPI_CLIENT_PaaSStreamUrlVisualTalk_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
	获取一个通道的可视对讲地址
	POST /media/delivery/visualtalk/channels/[channelId]

	channelId : 类型string。通道标识(包括视频通道，图片通道，报警通道等)。最长为32字符。
	对于公有云产品，channelId是使用"设备序列号-通道号"进行标识。
	对于私有云产品，channelId是一个内部生成的唯一描述，只描述设备的通道号，和设备唯一标识解耦，没有任何关系。
 */

typedef struct PaaSStreamUrlVisualTalkRequest 
{
	LCOpenApiRequest base;

	struct PaaSStreamUrlVisualTalkRequestData
	{
		
		/** 对实时视频流进行智能分析的任务id，分析后产生对应算法类型的实时智能视频流, 可选 */
		CSTR taskId;
		/** ivss压缩任务id，需要拉取ivss压缩码流的rtsp业务场景需要带上该字段, 可选 */
		CSTR ivssCode;
		/** 客户端地址 */
		CSTR clientIp;
		/** [long] 类型int64_t。用户期望资源访问有效时间，单位：秒。可选，以响应返回的expire为准 */
		int64 duration;
		/** 码流类型 main, extra1, extra2, extra3 */
		CSTR videoStream;
		/** 传输类型,可选，默认为[“TCP”]。LHTS和CQTS传输协议目前只在RTSV媒体协议上支持 */
		DECLARE_LIST(CSTR) transports;
		/** 视频流类型 normal private... */
		CSTR streamType;
		/** 流媒体RTSV传输协议的信令加密模式，可选项，仅当scheme传输协议为RTSV系列协议（RTSV1\RTSV2\PBSV1\PBSV2\TSV1\TSV2等）时生效(PrivateEncrypt)。否则将忽略。为空或者没有此字段，等同于 NotEncrypt。 */
		CSTR encryptionMode;
		/** [bool] 返回是否是域名, 可选, 默认为false */
		BOOL domainEnable;
		/** 设备加密模式 0:不加密 3:三码合一 */
		CSTR encryptType;
		/** 协议类型 RTSV */
		CSTR scheme;
		/** 用户标识 VSL带来的字段，在url直接返回该内容，不做任何处理，默认invalid */
		CSTR userCode;
		/** [bool] 快速开启 true */
		BOOL fastopen;
		/** 客户端类型 */
		CSTR clientType;

	} data;

} PaaSStreamUrlVisualTalkRequest;

C_API PaaSStreamUrlVisualTalkRequest *LCOPENAPI_INIT(PaaSStreamUrlVisualTalkRequest);

typedef struct PaaSStreamUrlVisualTalkResponse 
{
	LCOpenApiResponse base;

	struct PaaSStreamUrlVisualTalkResponseData
	{
		
		/** define a list with struct of PaaSStreamUrlVisualTalkResponseData_UrlsElement */
		DECLARE_LIST(struct PaaSStreamUrlVisualTalkResponseData_UrlsElement
		{
			/** 资源获取地址 */
			CSTR resource;
			/** 可选。针对流媒体RTSV传输协议的信令加密模式，仅当scheme传输协议为RTSV系列协议（RTSV1\RTSV2\PBSV1\PBSV2\TSV1\TSV2等）时生效。scheme指定RTSP时，或者RTSV系列协议不支持加密能力时，服务将不返回此字段。取值范围:PrivateEncrypt表示私有加密，秘钥由流媒体模块内部推导 */
			CSTR encryptionMode;
			/** 内网资源获取地址。如果是拉流则返回节点的URL,如果是推流则返回的是MTS节点的推流URL */
			CSTR internal_resource;
			/** 传输方式 TCP/LHTS/QCTS */
			CSTR transport;
		}) urls;
		/** 地址过期时间。UTC时间，时间格式为YYYYMMDDThhmmssZ，如：20151119T161900Z 参见ISO 8601格式 */
		CSTR expire;
		/** 区域信息。返回转发服务所在的区域信息 */
		CSTR region;
 
	} data;

} PaaSStreamUrlVisualTalkResponse;

C_API PaaSStreamUrlVisualTalkResponse *LCOPENAPI_INIT(PaaSStreamUrlVisualTalkResponse);

#endif
