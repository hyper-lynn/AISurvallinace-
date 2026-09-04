/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_SetEmergencyContacts_H_
#define _HSVIEW_CLIENT_API_SetEmergencyContacts_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置用户的紧急联系人列表。
【使用平台账号签名】
 */

typedef struct SetEmergencyContactsRequest 
{
	HsviewRequest base;

	struct SetEmergencyContactsRequestData
	{
		
		/** define a list with struct of SetEmergencyContactsRequestData_ContactsElement */
		DECLARE_LIST(struct SetEmergencyContactsRequestData_ContactsElement
		{
			/** 手机号，如13912345678 */
			CSTR phoneNumber;
		}) contacts;

	} data;

} SetEmergencyContactsRequest;

C_API SetEmergencyContactsRequest *HSAPI_INIT(SetEmergencyContactsRequest);

typedef struct SetEmergencyContactsResponse 
{
	HsviewResponse base;

	struct SetEmergencyContactsResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} SetEmergencyContactsResponse;

C_API SetEmergencyContactsResponse *HSAPI_INIT(SetEmergencyContactsResponse);

#endif
