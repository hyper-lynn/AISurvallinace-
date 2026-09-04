/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetHeaderDetect_H_
#define _HSVIEW_CLIENT_API_GetHeaderDetect_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取人头检测
 */

typedef struct GetHeaderDetectRequest 
{
	HsviewRequest base;

	struct GetHeaderDetectRequestData
	{
		
		/** 设备ID */
		CSTR devId;
		/** 必须填写通道号 */
		CSTR optional;
		/** [cstr]GET */
		#define _STATIC_GetHeaderDetectRequestData_METHOD "GET"
		/** [cstr]header-detect */
		#define _STATIC_GetHeaderDetectRequestData_CMD "header-detect"
		/** struct of GetHeaderDetectRequestData_Body */
		struct GetHeaderDetectRequestData_Body {
			/** [int][O]保留 */
			int _nouse;
		} body;

	} data;

} GetHeaderDetectRequest;

C_API GetHeaderDetectRequest *HSAPI_INIT(GetHeaderDetectRequest);

typedef struct GetHeaderDetectResponse 
{
	HsviewResponse base;

	struct GetHeaderDetectResponseData
	{
		
		/** [int]使能, 1-开启 0-关闭 */
		int Enable;
 
	} data;

} GetHeaderDetectResponse;

C_API GetHeaderDetectResponse *HSAPI_INIT(GetHeaderDetectResponse);

#endif
