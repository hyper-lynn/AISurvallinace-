/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 222588, Author: 27665, Date: 2022-04-22 15:26:23 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_getSimSignalStrength_H_
#define _LC_OPENAPI_CLIENT_getSimSignalStrength_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
查询设备SIM信号强度
 */

typedef struct getSimSignalStrengthRequest 
{
	LCOpenApiRequest base;

	struct getSimSignalStrengthRequestData
	{
		
		/** xxx */
		CSTR token;
		/**  */
		CSTR deviceId;

	} data;

} getSimSignalStrengthRequest;

C_API getSimSignalStrengthRequest *LCOPENAPI_INIT(getSimSignalStrengthRequest);

typedef struct getSimSignalStrengthResponse 
{
	LCOpenApiResponse base;

	struct getSimSignalStrengthResponseData
	{
		
		/** [int]0-100,0最弱，100最强 */
		int intensity;
 
	} data;

} getSimSignalStrengthResponse;

C_API getSimSignalStrengthResponse *LCOPENAPI_INIT(getSimSignalStrengthResponse);

#endif
