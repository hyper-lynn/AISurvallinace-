/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetSmartTrack_H_
#define _HSVIEW_CLIENT_API_GetSmartTrack_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取智能追踪
===

===

 */

typedef struct GetSmartTrackRequest 
{
	HsviewRequest base;

	struct GetSmartTrackRequestData
	{
		
		/** 设备ID */
		CSTR devId;
		/** 必须填写通道号 */
		CSTR optional;
		/** [cstr]GET */
		#define _STATIC_GetSmartTrackRequestData_METHOD "GET"
		/** [cstr]smart-track */
		#define _STATIC_GetSmartTrackRequestData_CMD "smart-track"
		/** struct of GetSmartTrackRequestData_Body */
		struct GetSmartTrackRequestData_Body {
			/** [int][O]保留 */
			int _nouse;
		} body;

	} data;

} GetSmartTrackRequest;

C_API GetSmartTrackRequest *HSAPI_INIT(GetSmartTrackRequest);

typedef struct GetSmartTrackResponse 
{
	HsviewResponse base;

	struct GetSmartTrackResponseData
	{
		
		/** [int]使能, 1-开启 0-关闭 */
		int Enable;
 
	} data;

} GetSmartTrackResponse;

C_API GetSmartTrackResponse *HSAPI_INIT(GetSmartTrackResponse);

#endif
