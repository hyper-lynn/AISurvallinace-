/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_QueryCloudRecordDomain_H_
#define _LC_OPENAPI_CLIENT_QueryCloudRecordDomain_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取云录像片段域名

 */

typedef struct QueryCloudRecordDomainRequest 
{
	LCOpenApiRequest base;

	struct QueryCloudRecordDomainRequestData
	{
		
		/** [cstr]queryCloudRecordDomain */
		#define _STATIC_QueryCloudRecordDomainRequestData_method "queryCloudRecordDomain"
		CSTR method;
		/** 授权token(userToken或accessToken) */
		CSTR token;

	} data;

} QueryCloudRecordDomainRequest;

C_API QueryCloudRecordDomainRequest *LCOPENAPI_INIT(QueryCloudRecordDomainRequest);

typedef struct QueryCloudRecordDomainResponse 
{
	LCOpenApiResponse base;

	struct QueryCloudRecordDomainResponseData
	{
		
		/** 云录像host */
		CSTR host;
		/** http云录像port */
		CSTR port;
		/** 国内云录像前缀 */
		CSTR openapiUrl;
		/** https云录像port */
		CSTR encryptPort;
 
	} data;

} QueryCloudRecordDomainResponse;

C_API QueryCloudRecordDomainResponse *LCOPENAPI_INIT(QueryCloudRecordDomainResponse);

#endif
