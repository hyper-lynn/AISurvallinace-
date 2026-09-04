/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_SetSmartTrack_H_
#define _HSVIEW_CLIENT_API_SetSmartTrack_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置智能追踪
 */

typedef struct SetSmartTrackRequest 
{
	HsviewRequest base;

	struct SetSmartTrackRequestData
	{
		
		/** 设备ID */
		CSTR devId;
		/** 必须填写通道号 */
		CSTR optional;
		/** [cstr]POST */
		#define _STATIC_SetSmartTrackRequestData_METHOD "POST"
		/** [cstr]smart-track */
		#define _STATIC_SetSmartTrackRequestData_CMD "smart-track"
		/** struct of SetSmartTrackRequestData_Body */
		struct SetSmartTrackRequestData_Body {
			/** [int]使能, 1-开启 0-关闭 */
			int Enable;
		} body;

	} data;

} SetSmartTrackRequest;

C_API SetSmartTrackRequest *HSAPI_INIT(SetSmartTrackRequest);

typedef struct SetSmartTrackResponse 
{
	HsviewResponse base;

	struct SetSmartTrackResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} SetSmartTrackResponse;

C_API SetSmartTrackResponse *HSAPI_INIT(SetSmartTrackResponse);

#endif
