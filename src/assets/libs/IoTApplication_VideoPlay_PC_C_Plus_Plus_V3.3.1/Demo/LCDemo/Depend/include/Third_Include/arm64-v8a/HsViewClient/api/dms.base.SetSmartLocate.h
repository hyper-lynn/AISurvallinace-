/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_SetSmartLocate_H_
#define _HSVIEW_CLIENT_API_SetSmartLocate_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置听声辨位
 */

typedef struct SetSmartLocateRequest 
{
	HsviewRequest base;

	struct SetSmartLocateRequestData
	{
		
		/** 设备ID */
		CSTR devId;
		/** 必须填写通道号 */
		CSTR optional;
		/** [cstr]POST */
		#define _STATIC_SetSmartLocateRequestData_METHOD "POST"
		/** [cstr]smart-locate */
		#define _STATIC_SetSmartLocateRequestData_CMD "smart-locate"
		/** struct of SetSmartLocateRequestData_Body */
		struct SetSmartLocateRequestData_Body {
			/** [int]使能, 1-开启 0-关闭 */
			int Enable;
		} body;

	} data;

} SetSmartLocateRequest;

C_API SetSmartLocateRequest *HSAPI_INIT(SetSmartLocateRequest);

typedef struct SetSmartLocateResponse 
{
	HsviewResponse base;

	struct SetSmartLocateResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} SetSmartLocateResponse;

C_API SetSmartLocateResponse *HSAPI_INIT(SetSmartLocateResponse);

#endif
