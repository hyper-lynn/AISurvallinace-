/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_QueryPTZ_H_
#define _HSVIEW_CLIENT_API_QueryPTZ_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取设备当前的定位

当通道号为0，或者不存在，表示获取此设备的PTZ。
H 水平位置：归一化到-1~1
V 垂直位置：归一化到-1~1
Z 变倍倍数：归一化到0~1

【需要使用平台账号签名】
 */

typedef struct QueryPTZRequest 
{
	HsviewRequest base;

	struct QueryPTZRequestData
	{
		
		/** 设备ID */
		CSTR devId;
		/** 通道号 */
		CSTR optional;
		/** [cstr]GET */
		#define _STATIC_QueryPTZRequestData_METHOD "GET"
		/** [cstr]ptz */
		#define _STATIC_QueryPTZRequestData_CMD "ptz"
		/** struct of QueryPTZRequestData_Body */
		struct QueryPTZRequestData_Body {
			/** [int][O]保留 */
			int _nouse;
		} body;

	} data;

} QueryPTZRequest;

C_API QueryPTZRequest *HSAPI_INIT(QueryPTZRequest);

typedef struct QueryPTZResponse 
{
	HsviewResponse base;

	struct QueryPTZResponseData
	{
		
		/** [double]水平操作参数 */
		double H;
		/** [double]变倍参数 */
		double Z;
		/** [double]垂直操作参数 */
		double V;
 
	} data;

} QueryPTZResponse;

C_API QueryPTZResponse *HSAPI_INIT(QueryPTZResponse);

#endif
