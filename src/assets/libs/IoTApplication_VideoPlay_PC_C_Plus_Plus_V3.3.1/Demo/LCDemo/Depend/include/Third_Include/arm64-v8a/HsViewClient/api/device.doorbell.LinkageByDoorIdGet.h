/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceDoorbell_LinkageByDoorIdGet_H_
#define _HSVIEW_CLIENT_API_deviceDoorbell_LinkageByDoorIdGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
查询门铃关联的所有铃铛

【需要使用平台账号签名】
 */

typedef struct deviceDoorbell_LinkageByDoorIdGetRequest 
{
	HsviewRequest base;

	struct deviceDoorbell_LinkageByDoorIdGetRequestData
	{
		
		/** 门铃的ID */
		CSTR doorId;

	} data;

} deviceDoorbell_LinkageByDoorIdGetRequest;

C_API deviceDoorbell_LinkageByDoorIdGetRequest *HSAPI_INIT(deviceDoorbell_LinkageByDoorIdGetRequest);

typedef struct deviceDoorbell_LinkageByDoorIdGetResponse 
{
	HsviewResponse base;

	struct deviceDoorbell_LinkageByDoorIdGetResponseData
	{
		
		/** define a list with struct of deviceDoorbell_LinkageByDoorIdGetResponseData_InfosElement */
		DECLARE_LIST(struct deviceDoorbell_LinkageByDoorIdGetResponseData_InfosElement
		{
			/** 相关联的铃铛名称 */
			CSTR bellName;
			/** 相关联的铃铛ID */
			CSTR bellId;
		}) infos;
 
	} data;

} deviceDoorbell_LinkageByDoorIdGetResponse;

C_API deviceDoorbell_LinkageByDoorIdGetResponse *HSAPI_INIT(deviceDoorbell_LinkageByDoorIdGetResponse);

#endif
