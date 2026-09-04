/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_cloudRecord_DeleteCondensedRecordsByRecordIds_H_
#define _HSVIEW_CLIENT_API_cloudRecord_DeleteCondensedRecordsByRecordIds_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
人脸云根据浓缩视频id删除浓缩视频,
recordIds:需要删除的录像id的数组，为空或者长度为0则 不删除录像

【默认AK、SK鉴权】
 */

typedef struct cloudRecord_DeleteCondensedRecordsByRecordIdsRequest 
{
	HsviewRequest base;

	struct cloudRecord_DeleteCondensedRecordsByRecordIdsRequestData
	{
		
		/** [long]浓缩视频id */
		DECLARE_LIST(int64) recordIds;

	} data;

} cloudRecord_DeleteCondensedRecordsByRecordIdsRequest;

C_API cloudRecord_DeleteCondensedRecordsByRecordIdsRequest *HSAPI_INIT(cloudRecord_DeleteCondensedRecordsByRecordIdsRequest);

typedef struct cloudRecord_DeleteCondensedRecordsByRecordIdsResponse 
{
	HsviewResponse base;

	struct cloudRecord_DeleteCondensedRecordsByRecordIdsResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} cloudRecord_DeleteCondensedRecordsByRecordIdsResponse;

C_API cloudRecord_DeleteCondensedRecordsByRecordIdsResponse *HSAPI_INIT(cloudRecord_DeleteCondensedRecordsByRecordIdsResponse);

#endif
