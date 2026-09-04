/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_AddAdvertViewTimes_H_
#define _HSVIEW_CLIENT_API_AddAdvertViewTimes_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
增加广告的展示次数
【使用平台账号签名】
 */

typedef struct AddAdvertViewTimesRequest 
{
	HsviewRequest base;

	struct AddAdvertViewTimesRequestData
	{
		
		/** [long]广告id */
		int64 advertId;

	} data;

} AddAdvertViewTimesRequest;

C_API AddAdvertViewTimesRequest *HSAPI_INIT(AddAdvertViewTimesRequest);

typedef struct AddAdvertViewTimesResponse 
{
	HsviewResponse base;

	struct AddAdvertViewTimesResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} AddAdvertViewTimesResponse;

C_API AddAdvertViewTimesResponse *HSAPI_INIT(AddAdvertViewTimesResponse);

#endif
