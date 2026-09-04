/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_PaaSGenerateRecordUrlById_H_
#define _LC_OPENAPI_CLIENT_PaaSGenerateRecordUrlById_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
	获取云录像地址
	POST /storage/records/generateRecordUrlById/channels/[channelId]

	channelId : 类型string。通道标识(包括视频通道，图片通道，报警通道等)。最长为32字符。
	对于公有云产品，channelId是使用"设备序列号-通道号"进行标识。
	对于私有云产品，channelId是一个内部生成的唯一描述，只描述设备的通道号，和设备唯一标识解耦，没有任何关系。
 */

typedef struct PaaSGenerateRecordUrlByIdRequest 
{
	LCOpenApiRequest base;

	struct PaaSGenerateRecordUrlByIdRequestData
	{
		
		/** 录像存储路径 */
		CSTR recordPath;
		/** 通道ID */
		CSTR channelId;
		/** 云录像存储域编码 */
		CSTR region;
		/** 设备ID */
		CSTR deviceId;

	} data;

} PaaSGenerateRecordUrlByIdRequest;

C_API PaaSGenerateRecordUrlByIdRequest *LCOPENAPI_INIT(PaaSGenerateRecordUrlByIdRequest);

typedef struct PaaSGenerateRecordUrlByIdResponse 
{
	LCOpenApiResponse base;

	struct PaaSGenerateRecordUrlByIdResponseData
	{
		
		/** 错误码 */
		CSTR errCode;
		/** trace码 */
		CSTR traceId;
		/** struct of PaaSGenerateRecordUrlByIdResponseData_Data */
		struct PaaSGenerateRecordUrlByIdResponseData_Data {
			/** 用于播放此段录像的临时令牌；公有云使用，有效期1小时，用于授权dav切片 */
			CSTR token;
			/** 返回的m3u8或dav下载地址 */
			CSTR url;
		} data;
		/** 请求成功与否信息 */
		CSTR message;
 
	} data;

} PaaSGenerateRecordUrlByIdResponse;

C_API PaaSGenerateRecordUrlByIdResponse *LCOPENAPI_INIT(PaaSGenerateRecordUrlByIdResponse);

#endif
