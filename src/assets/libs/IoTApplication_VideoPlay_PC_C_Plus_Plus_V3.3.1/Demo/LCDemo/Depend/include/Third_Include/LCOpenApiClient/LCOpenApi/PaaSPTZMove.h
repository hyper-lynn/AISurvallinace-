/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 225694, Author: 112352, Date: 2023-12-27 14:50:15 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_PaaSPTZMove_H_
#define _LC_OPENAPI_CLIENT_PaaSPTZMove_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
    公有云PaaS 云台控制，实现云台的转动和变倍操作。
    注：此协议由管理节点和子节点同时提供，管理节点按照channelId所在子节点路由。

    PUT /things/operation/ptz/move/channels/[channelId]
    
    channelId : 类型string。通道标识(包括视频通道，图片通道，报警通道等)。最长为32字符。
    对于公有云产品，channelId是使用”设备序列号-通道号”进行标识。
    对于私有云产品，channelId是一个内部生成的唯一描述，只描述设备的通道号，和设备唯一标识解耦，没有任何关系。
    
    通过将horizontal、vertical、zoom三个参数设置为0调用该接口，则为停止云台转动。如果在云台转动后不调用停止云台转动，则按照duraiton时间执行转动。
    duration只有部分设备能够支持，如果要确保所有设备都能停止，需要通过手动下发三参数为0的方式实现。
 */

typedef struct PaaSPTZMoveRequest 
{
	LCOpenApiRequest base;

	struct PaaSPTZMoveRequestData
	{
		
		/** [double]垂直控制速度绝对值。归一化到(-1, 1)。-1表示向下转最大速度，1表示向上转最大速度。y>0向上转，反之向下转。 */
		double vertical;
		/** [int]相机类型，0为普通白光相机，1为4k相机，现仅针对上赛协议设备为必选项，其它为选填项 */
		int type;
		/** [double]水平控制速度绝对值。归一化到(-1, 1)。-1表示左转最大速度，1表示右转最大速度。x>0为右转，反之左转。 */
		double horizontal;
		/** [int]持续移动时间，单位：毫秒 */
		int duration;
		/** [double]变倍控制速度绝对值。归一化到(-1, 1)。-1表示缩小最大速度，1表示放大最大速度。zoom>0为放大，反之缩小。 */
		double zoom;

	} data;

} PaaSPTZMoveRequest;

C_API PaaSPTZMoveRequest *LCOPENAPI_INIT(PaaSPTZMoveRequest);

typedef struct PaaSPTZMoveResponse 
{
	LCOpenApiResponse base;

	struct PaaSPTZMoveResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} PaaSPTZMoveResponse;

C_API PaaSPTZMoveResponse *LCOPENAPI_INIT(PaaSPTZMoveResponse);

#endif
