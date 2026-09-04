/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetPrivateCloudList_H_
#define _HSVIEW_CLIENT_API_GetPrivateCloudList_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取私有云列表。
【使用平台账号签名】
 */

typedef struct GetPrivateCloudListRequest 
{
	HsviewRequest base;

	struct GetPrivateCloudListRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} GetPrivateCloudListRequest;

C_API GetPrivateCloudListRequest *HSAPI_INIT(GetPrivateCloudListRequest);

typedef struct GetPrivateCloudListResponse 
{
	HsviewResponse base;

	struct GetPrivateCloudListResponseData
	{
		
		/** define a list with struct of GetPrivateCloudListResponseData_PrivateCloudListElement */
		DECLARE_LIST(struct GetPrivateCloudListResponseData_PrivateCloudListElement
		{
			/** IPC设备ID */
			CSTR ipcDeviceId;
			/** 智能网关（私有云）设备ID */
			CSTR ihgDeviceId;
		}) privateCloudList;
 
	} data;

} GetPrivateCloudListResponse;

C_API GetPrivateCloudListResponse *HSAPI_INIT(GetPrivateCloudListResponse);

#endif
