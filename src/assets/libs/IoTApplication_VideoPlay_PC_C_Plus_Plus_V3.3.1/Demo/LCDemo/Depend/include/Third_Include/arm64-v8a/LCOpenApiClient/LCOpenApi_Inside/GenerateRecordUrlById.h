/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: unknown, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_GenerateRecordUrlById_H_
#define _LC_OPENAPI_CLIENT_GenerateRecordUrlById_H_

#include "LCOpenApiDefine.h"
#include "LCOpenApiRequest.h"
#include "LCOpenApiResponse.h"

/** DESCRIPTION: 
获取云录像地址
错误码:
10004：超过指定路数，拒绝给予RTSP地址
10005：超过指定个流量，拒绝给予RTSP地址

 */

namespace Dahua{
namespace LCOpenApi{
	using namespace std;
	class GenerateRecordUrlByIdRequest : public LCOpenApiRequest
	{
	public:
		class GenerateRecordUrlByIdRequestData
		{
		public:
			GenerateRecordUrlByIdRequestData();
			~GenerateRecordUrlByIdRequestData();
			
		public:
			/** 1000报警云录像,2000定时云录像 */
			string type;
		public:
			/** 授权token(userToken或accessToken) */
			string token;
		public:
			/** 录像ID */
			string recordId;
		public:
			/** 通道ID */
			string channelId;
		public:
			/** 设备ID */
			string deviceId;

		};
	public:
		GenerateRecordUrlByIdRequest();
		~GenerateRecordUrlByIdRequest();
	public:
		virtual int build();
	public:
		GenerateRecordUrlByIdRequestData data;
	};

	
	typedef GenerateRecordUrlByIdRequest::GenerateRecordUrlByIdRequestData GenerateRecordUrlByIdRequestData;


	class GenerateRecordUrlByIdResponse : public LCOpenApiResponse
	{
	public:
		class GenerateRecordUrlByIdResponseData
		{
		public:
			GenerateRecordUrlByIdResponseData();
			~GenerateRecordUrlByIdResponseData();
			
		public:
			/** 返回的rtsp地址 */
			string url;

		};
	public:
		GenerateRecordUrlByIdResponse();
		~GenerateRecordUrlByIdResponse();
	public:
		virtual int parse();
	public:
		GenerateRecordUrlByIdResponseData data;
	};

	
	typedef GenerateRecordUrlByIdResponse::GenerateRecordUrlByIdResponseData GenerateRecordUrlByIdResponseData;

}
}

#endif
