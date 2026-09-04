/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_deviceDoorbell_LinkageByBellIdGet_H_
#define _HSVIEW_CLIENT_API_deviceDoorbell_LinkageByBellIdGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
查询铃铛相关联的的所有门铃

【需要使用平台账号签名】
 */

typedef struct deviceDoorbell_LinkageByBellIdGetRequest 
{
	HsviewRequest base;

	struct deviceDoorbell_LinkageByBellIdGetRequestData
	{
		
		/** 铃铛的ID */
		CSTR bellId;

	} data;

} deviceDoorbell_LinkageByBellIdGetRequest;

C_API deviceDoorbell_LinkageByBellIdGetRequest *HSAPI_INIT(deviceDoorbell_LinkageByBellIdGetRequest);

typedef struct deviceDoorbell_LinkageByBellIdGetResponse 
{
	HsviewResponse base;

	struct deviceDoorbell_LinkageByBellIdGetResponseData
	{
		
		/** define a list with struct of deviceDoorbell_LinkageByBellIdGetResponseData_InfosElement */
		DECLARE_LIST(struct deviceDoorbell_LinkageByBellIdGetResponseData_InfosElement
		{
			/** 相关联的门铃ID */
			CSTR doorId;
			/** 相关联的门铃名称 */
			CSTR doorName;
		}) infos;
 
	} data;

} deviceDoorbell_LinkageByBellIdGetResponse;

C_API deviceDoorbell_LinkageByBellIdGetResponse *HSAPI_INIT(deviceDoorbell_LinkageByBellIdGetResponse);

#endif
