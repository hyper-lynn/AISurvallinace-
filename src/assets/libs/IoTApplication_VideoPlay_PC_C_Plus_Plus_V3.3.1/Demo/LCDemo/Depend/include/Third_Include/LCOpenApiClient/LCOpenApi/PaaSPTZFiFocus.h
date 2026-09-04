/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 226113, Author: 112352, Date: 2024-04-11 09:32:00 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_PaaSPTZFiFocus_H_
#define _LC_OPENAPI_CLIENT_PaaSPTZFiFocus_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
    公有云PaaS 变焦控制。使用指定的变焦速度，以当前焦距为基础进行持续变焦。
	注：此协议由管理节点和子节点同时提供，管理节点按照channelId所在子节点路由。

    PUT /things/operation/ptz/fi/focus/channels/[channelId]
    
    channelId : 类型string。通道标识(包括视频通道，图片通道，报警通道等)。最长为32字符。
    对于公有云产品，channelId是使用”设备序列号-通道号”进行标识。
    对于私有云产品，channelId是一个内部生成的唯一描述，只描述设备的通道号，和设备唯一标识解耦，没有任何关系。
 */

typedef struct PaaSPTZFiFocusRequest 
{
	LCOpenApiRequest base;

	struct PaaSPTZFiFocusRequestData
	{
		
		/** [int]相机类型，0为普通白光相机，1为4k相机，现仅针对上赛协议设备为必选项，其它为选填项 */
		int type;
		/** [double]云台聚焦相对变化值，归一化到(-1, 1)。 */
		double change;

	} data;

} PaaSPTZFiFocusRequest;

C_API PaaSPTZFiFocusRequest *LCOPENAPI_INIT(PaaSPTZFiFocusRequest);

typedef struct PaaSPTZFiFocusResponse 
{
	LCOpenApiResponse base;

	struct PaaSPTZFiFocusResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} PaaSPTZFiFocusResponse;

C_API PaaSPTZFiFocusResponse *LCOPENAPI_INIT(PaaSPTZFiFocusResponse);

#endif
