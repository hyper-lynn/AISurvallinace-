/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_SetHeaderDetect_H_
#define _HSVIEW_CLIENT_API_SetHeaderDetect_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置人头检测

单通道设备和多通道设备，都[channel-id]都必须填写。
 */

typedef struct SetHeaderDetectRequest 
{
	HsviewRequest base;

	struct SetHeaderDetectRequestData
	{
		
		/** 设备ID */
		CSTR devId;
		/** 必须填写通道号 */
		CSTR optional;
		/** [cstr]POST */
		#define _STATIC_SetHeaderDetectRequestData_METHOD "POST"
		/** [cstr]header-detect */
		#define _STATIC_SetHeaderDetectRequestData_CMD "header-detect"
		/** struct of SetHeaderDetectRequestData_Body */
		struct SetHeaderDetectRequestData_Body {
			/** [int]使能, 1-开启 0-关闭 */
			int Enable;
		} body;

	} data;

} SetHeaderDetectRequest;

C_API SetHeaderDetectRequest *HSAPI_INIT(SetHeaderDetectRequest);

typedef struct SetHeaderDetectResponse 
{
	HsviewResponse base;

	struct SetHeaderDetectResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} SetHeaderDetectResponse;

C_API SetHeaderDetectResponse *HSAPI_INIT(SetHeaderDetectResponse);

#endif
