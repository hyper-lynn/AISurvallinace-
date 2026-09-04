/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_cloudRecord_DeleteCondensedRecordsByUserId_H_
#define _HSVIEW_CLIENT_API_cloudRecord_DeleteCondensedRecordsByUserId_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
人脸云删除改用户的所有的视频

【默认AK、SK鉴权】
 */

typedef struct cloudRecord_DeleteCondensedRecordsByUserIdRequest 
{
	HsviewRequest base;

	struct cloudRecord_DeleteCondensedRecordsByUserIdRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} cloudRecord_DeleteCondensedRecordsByUserIdRequest;

C_API cloudRecord_DeleteCondensedRecordsByUserIdRequest *HSAPI_INIT(cloudRecord_DeleteCondensedRecordsByUserIdRequest);

typedef struct cloudRecord_DeleteCondensedRecordsByUserIdResponse 
{
	HsviewResponse base;

	struct cloudRecord_DeleteCondensedRecordsByUserIdResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} cloudRecord_DeleteCondensedRecordsByUserIdResponse;

C_API cloudRecord_DeleteCondensedRecordsByUserIdResponse *HSAPI_INIT(cloudRecord_DeleteCondensedRecordsByUserIdResponse);

#endif
