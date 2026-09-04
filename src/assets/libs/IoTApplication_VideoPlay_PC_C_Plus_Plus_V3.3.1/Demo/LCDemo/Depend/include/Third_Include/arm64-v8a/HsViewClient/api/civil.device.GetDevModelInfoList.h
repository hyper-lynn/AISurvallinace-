/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetDevModelInfoList_H_
#define _HSVIEW_CLIENT_API_GetDevModelInfoList_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
绑定流程获取设备外部型号列表
        



【无需签名认证】
 */

typedef struct GetDevModelInfoListRequest 
{
	HsviewRequest base;

	struct GetDevModelInfoListRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} GetDevModelInfoListRequest;

C_API GetDevModelInfoListRequest *HSAPI_INIT(GetDevModelInfoListRequest);

typedef struct GetDevModelInfoListResponse 
{
	HsviewResponse base;

	struct GetDevModelInfoListResponseData
	{
		
		/** define a list with struct of GetDevModelInfoListResponseData_ModelsElement */
		DECLARE_LIST(struct GetDevModelInfoListResponseData_ModelsElement
		{
			/** 设备内部型号（最大出货量） */
			CSTR deviceModel;
			/** 该型号对应的设备logo图片url */
			CSTR logoUrl;
			/** 型号名称（设备外部型号） */
			CSTR modelName;
		}) models;
		/** [long]Unix时间戳 */
		int64 timeStamp;
 
	} data;

} GetDevModelInfoListResponse;

C_API GetDevModelInfoListResponse *HSAPI_INIT(GetDevModelInfoListResponse);

#endif
