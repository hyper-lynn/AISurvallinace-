/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetEmergencyContacts_H_
#define _HSVIEW_CLIENT_API_GetEmergencyContacts_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取用户的紧急联系人列表。
【使用平台账号签名】
 */

typedef struct GetEmergencyContactsRequest 
{
	HsviewRequest base;

	struct GetEmergencyContactsRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} GetEmergencyContactsRequest;

C_API GetEmergencyContactsRequest *HSAPI_INIT(GetEmergencyContactsRequest);

typedef struct GetEmergencyContactsResponse 
{
	HsviewResponse base;

	struct GetEmergencyContactsResponseData
	{
		
		/** define a list with struct of GetEmergencyContactsResponseData_ContactsElement */
		DECLARE_LIST(struct GetEmergencyContactsResponseData_ContactsElement
		{
			/** 紧急联系人手机号，如13912345678 */
			CSTR phoneNumber;
		}) contacts;
 
	} data;

} GetEmergencyContactsResponse;

C_API GetEmergencyContactsResponse *HSAPI_INIT(GetEmergencyContactsResponse);

#endif
