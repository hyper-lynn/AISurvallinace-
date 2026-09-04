/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceAuth_DeleteAuthById_H_
#define _HSVIEW_CLIENT_API_deviceAuth_DeleteAuthById_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
   删除授权设备
【需要使用平台账号签名】

 */

typedef struct deviceAuth_DeleteAuthByIdRequest 
{
	HsviewRequest base;

	struct deviceAuth_DeleteAuthByIdRequestData
	{
		
		/** [long]授权Id */
		int64 id;

	} data;

} deviceAuth_DeleteAuthByIdRequest;

C_API deviceAuth_DeleteAuthByIdRequest *HSAPI_INIT(deviceAuth_DeleteAuthByIdRequest);

typedef struct deviceAuth_DeleteAuthByIdResponse 
{
	HsviewResponse base;

	struct deviceAuth_DeleteAuthByIdResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} deviceAuth_DeleteAuthByIdResponse;

C_API deviceAuth_DeleteAuthByIdResponse *HSAPI_INIT(deviceAuth_DeleteAuthByIdResponse);

#endif
