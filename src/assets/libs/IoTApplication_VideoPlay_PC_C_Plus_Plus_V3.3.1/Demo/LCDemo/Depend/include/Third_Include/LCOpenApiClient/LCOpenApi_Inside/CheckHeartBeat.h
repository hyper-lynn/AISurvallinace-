/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_CheckHeartBeat_H_
#define _LC_OPENAPI_CLIENT_CheckHeartBeat_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
优化专项--长连接

 */

typedef struct CheckHeartBeatRequest 
{
	LCOpenApiRequest base;

	struct CheckHeartBeatRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} CheckHeartBeatRequest;

C_API CheckHeartBeatRequest *LCOPENAPI_INIT(CheckHeartBeatRequest);

typedef struct CheckHeartBeatResponse 
{
	LCOpenApiResponse base;

	struct CheckHeartBeatResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} CheckHeartBeatResponse;

C_API CheckHeartBeatResponse *LCOPENAPI_INIT(CheckHeartBeatResponse);

#endif
