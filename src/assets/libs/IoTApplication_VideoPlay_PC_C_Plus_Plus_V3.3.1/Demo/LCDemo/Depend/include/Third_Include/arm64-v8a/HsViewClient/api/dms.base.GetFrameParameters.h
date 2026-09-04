/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetFrameParameters_H_
#define _HSVIEW_CLIENT_API_GetFrameParameters_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取视频画面参数。
 */

typedef struct GetFrameParametersRequest 
{
	HsviewRequest base;

	struct GetFrameParametersRequestData
	{
		
		/** 设备ID */
		CSTR devId;
		/** 填写通道号 */
		CSTR optional;
		/** [cstr]GET */
		#define _STATIC_GetFrameParametersRequestData_METHOD "GET"
		/** [cstr]frame-params */
		#define _STATIC_GetFrameParametersRequestData_CMD "frame-params"
		/** struct of GetFrameParametersRequestData_Body */
		struct GetFrameParametersRequestData_Body {
			/** [int][O]保留 */
			int _nouse;
		} body;

	} data;

} GetFrameParametersRequest;

C_API GetFrameParametersRequest *HSAPI_INIT(GetFrameParametersRequest);

typedef struct GetFrameParametersResponse 
{
	HsviewResponse base;

	struct GetFrameParametersResponseData
	{
		
		/** normal或reverse */
		CSTR Direction;
 
	} data;

} GetFrameParametersResponse;

C_API GetFrameParametersResponse *HSAPI_INIT(GetFrameParametersResponse);

#endif
