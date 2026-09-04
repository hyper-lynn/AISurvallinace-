/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 226201, Author: 112352, Date: 2024-04-22 16:43:15 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_PaaSPTZFiIris_H_
#define _LC_OPENAPI_CLIENT_PaaSPTZFiIris_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
    公有云PaaS 光圈控制。使光圈相对于当前值进行光圈放大、缩小。
	注：此协议由管理节点和子节点同时提供，管理节点按照channelId所在子节点路由。

    PUT /things/operation/ptz/fi/iris/channels/[channelId]
    
    channelId : 类型string。通道标识(包括视频通道，图片通道，报警通道等)。最长为32字符。
    对于公有云产品，channelId是使用”设备序列号-通道号”进行标识。
    对于私有云产品，channelId是一个内部生成的唯一描述，只描述设备的通道号，和设备唯一标识解耦，没有任何关系。
 */

typedef struct PaaSPTZFiIrisRequest 
{
	LCOpenApiRequest base;

	struct PaaSPTZFiIrisRequestData
	{
		
		/** [double]光圈相对放大、缩小值，归一化到(-1, 1)。 */
		double change;

	} data;

} PaaSPTZFiIrisRequest;

C_API PaaSPTZFiIrisRequest *LCOPENAPI_INIT(PaaSPTZFiIrisRequest);

typedef struct PaaSPTZFiIrisResponse 
{
	LCOpenApiResponse base;

	struct PaaSPTZFiIrisResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} PaaSPTZFiIrisResponse;

C_API PaaSPTZFiIrisResponse *LCOPENAPI_INIT(PaaSPTZFiIrisResponse);

#endif
