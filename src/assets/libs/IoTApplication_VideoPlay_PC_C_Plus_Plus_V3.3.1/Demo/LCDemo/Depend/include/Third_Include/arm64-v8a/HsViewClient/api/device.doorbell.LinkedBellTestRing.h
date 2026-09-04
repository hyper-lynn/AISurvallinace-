/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceDoorbell_LinkedBellTestRing_H_
#define _HSVIEW_CLIENT_API_deviceDoorbell_LinkedBellTestRing_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
铃声试听

【需要使用平台账号签名】
 */

typedef struct deviceDoorbell_LinkedBellTestRingRequest 
{
	HsviewRequest base;

	struct deviceDoorbell_LinkedBellTestRingRequestData
	{
		
		/** 试听的铃声索引号 */
		CSTR index;
		/** 试听的铃铛ID */
		DECLARE_LIST(CSTR) bellIds;

	} data;

} deviceDoorbell_LinkedBellTestRingRequest;

C_API deviceDoorbell_LinkedBellTestRingRequest *HSAPI_INIT(deviceDoorbell_LinkedBellTestRingRequest);

typedef struct deviceDoorbell_LinkedBellTestRingResponse 
{
	HsviewResponse base;

	struct deviceDoorbell_LinkedBellTestRingResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} deviceDoorbell_LinkedBellTestRingResponse;

C_API deviceDoorbell_LinkedBellTestRingResponse *HSAPI_INIT(deviceDoorbell_LinkedBellTestRingResponse);

#endif
