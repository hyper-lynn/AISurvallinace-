/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 221547, Author: 27665, Date: 2021-10-29 15:00:22 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_SirenStart_H_
#define _LC_OPENAPI_CLIENT_SirenStart_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
开启警笛
 */

typedef struct SirenStartRequest 
{
	LCOpenApiRequest base;

	struct SirenStartRequestData
	{
		
		/** 客户端本地时间，如20180301T111730 */
		CSTR clientLocalTime;
		/** [int]设备通道号，从0开始.针对设备级的开启操作，channels这个参数不需要传值 */
		DECLARE_LIST(int) channels;
		/** xxx */
		CSTR token;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} SirenStartRequest;

C_API SirenStartRequest *LCOPENAPI_INIT(SirenStartRequest);

typedef struct SirenStartResponse 
{
	LCOpenApiResponse base;

	struct SirenStartResponseData
	{
		
		/** 20200709T161051 */
		CSTR clientLocalTime;
		/** [int]30 */
		int time;
		/** define a list with struct of SirenStartResponseData_ChannelsElement */
		DECLARE_LIST(struct SirenStartResponseData_ChannelsElement
		{
			/** [int]警笛持续时间 */
			int time;
			/** [String]通道号 */
			CSTR channelId;
		}) channels;
 
	} data;

} SirenStartResponse;

C_API SirenStartResponse *LCOPENAPI_INIT(SirenStartResponse);

#endif
