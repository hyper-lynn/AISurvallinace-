/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_QueryCloudRecordDomain_H_
#define _LC_OPENAPI_CLIENT_QueryCloudRecordDomain_H_

#include "LCOpenApiDefine.h"
#include "LCOpenApiRequest.h"
#include "LCOpenApiResponse.h"

/** DESCRIPTION: 
获取云录像片段域名

 */

namespace Dahua{
namespace LCOpenApi{
	using namespace std;
	class QueryCloudRecordDomainRequest : public LCOpenApiRequest
	{
	public:
		class QueryCloudRecordDomainRequestData
		{
		public:
			QueryCloudRecordDomainRequestData();
			~QueryCloudRecordDomainRequestData();
			
		public:
			/** [cstr]queryCloudRecordDomain */
			#define _STATIC_QueryCloudRecordDomainRequestData_method "queryCloudRecordDomain"
			string method;
		public:
			/** 授权token(userToken或accessToken) */
			string token;

		};
	public:
		QueryCloudRecordDomainRequest();
		~QueryCloudRecordDomainRequest();
	public:
		virtual int build();
	public:
		QueryCloudRecordDomainRequestData data;
	};

	
	typedef QueryCloudRecordDomainRequest::QueryCloudRecordDomainRequestData QueryCloudRecordDomainRequestData;


	class QueryCloudRecordDomainResponse : public LCOpenApiResponse
	{
	public:
		class QueryCloudRecordDomainResponseData
		{
		public:
			QueryCloudRecordDomainResponseData();
			~QueryCloudRecordDomainResponseData();
			
		public:
			/** 云录像host */
			string host;
		public:
			/** http云录像port */
			string port;
		public:
			/** https云录像port */
			string encryptPort;

		};
	public:
		QueryCloudRecordDomainResponse();
		~QueryCloudRecordDomainResponse();
	public:
		virtual int parse();
	public:
		QueryCloudRecordDomainResponseData data;
	};

	
	typedef QueryCloudRecordDomainResponse::QueryCloudRecordDomainResponseData QueryCloudRecordDomainResponseData;

}
}

#endif
