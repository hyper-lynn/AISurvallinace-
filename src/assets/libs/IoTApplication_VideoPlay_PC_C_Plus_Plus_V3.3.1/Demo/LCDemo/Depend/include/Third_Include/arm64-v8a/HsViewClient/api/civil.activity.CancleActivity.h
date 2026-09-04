/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_CancleActivity_H_
#define _HSVIEW_CLIENT_API_CancleActivity_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
用户取消参加活动

【需要乐橙账号鉴权】
 */

typedef struct CancleActivityRequest 
{
	HsviewRequest base;

	struct CancleActivityRequestData
	{
		
		/** [long]活动id */
		int64 activityId;

	} data;

} CancleActivityRequest;

C_API CancleActivityRequest *HSAPI_INIT(CancleActivityRequest);

typedef struct CancleActivityResponse 
{
	HsviewResponse base;

	struct CancleActivityResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} CancleActivityResponse;

C_API CancleActivityResponse *HSAPI_INIT(CancleActivityResponse);

#endif
