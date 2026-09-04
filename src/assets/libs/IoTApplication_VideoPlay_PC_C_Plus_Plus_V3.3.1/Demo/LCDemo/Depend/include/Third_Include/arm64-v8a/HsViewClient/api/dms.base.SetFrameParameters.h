/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_SetFrameParameters_H_
#define _HSVIEW_CLIENT_API_SetFrameParameters_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置视频画面参数。
画面参数：
Direction：画面方向，normal/reverse，正常/颠倒

对于单通道设备（如IPC），[channel-id]可以不填。
对于多通道设备，必须填写[channel-id]。
 */

typedef struct SetFrameParametersRequest 
{
	HsviewRequest base;

	struct SetFrameParametersRequestData
	{
		
		/** 设备ID */
		CSTR devId;
		/** 填写通道号 */
		CSTR optional;
		/** [cstr]POST */
		#define _STATIC_SetFrameParametersRequestData_METHOD "POST"
		/** [cstr]frame-params */
		#define _STATIC_SetFrameParametersRequestData_CMD "frame-params"
		/** struct of SetFrameParametersRequestData_Body */
		struct SetFrameParametersRequestData_Body {
			/** normal或reverse */
			CSTR Direction;
		} body;

	} data;

} SetFrameParametersRequest;

C_API SetFrameParametersRequest *HSAPI_INIT(SetFrameParametersRequest);

typedef struct SetFrameParametersResponse 
{
	HsviewResponse base;

	struct SetFrameParametersResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} SetFrameParametersResponse;

C_API SetFrameParametersResponse *HSAPI_INIT(SetFrameParametersResponse);

#endif
