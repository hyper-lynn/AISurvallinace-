/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetSmartLocate_H_
#define _HSVIEW_CLIENT_API_GetSmartLocate_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取听声辨位
 */

typedef struct GetSmartLocateRequest 
{
	HsviewRequest base;

	struct GetSmartLocateRequestData
	{
		
		/** 设备ID */
		CSTR devId;
		/** 必须填写通道号 */
		CSTR optional;
		/** [cstr]GET */
		#define _STATIC_GetSmartLocateRequestData_METHOD "GET"
		/** [cstr]smart-locate  */
		#define _STATIC_GetSmartLocateRequestData_CMD "smart-locate "
		/** struct of GetSmartLocateRequestData_Body */
		struct GetSmartLocateRequestData_Body {
			/** [int][O]保留 */
			int _nouse;
		} body;

	} data;

} GetSmartLocateRequest;

C_API GetSmartLocateRequest *HSAPI_INIT(GetSmartLocateRequest);

typedef struct GetSmartLocateResponse 
{
	HsviewResponse base;

	struct GetSmartLocateResponseData
	{
		
		/** [int]使能, 1-开启 0-关闭 */
		int Enable;
 
	} data;

} GetSmartLocateResponse;

C_API GetSmartLocateResponse *HSAPI_INIT(GetSmartLocateResponse);

#endif
