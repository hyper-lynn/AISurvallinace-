/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 221556, Author: 27665, Date: 2021-10-29 16:28:41 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_SirenStop_H_
#define _LC_OPENAPI_CLIENT_SirenStop_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
停止警笛
 */

typedef struct SirenStopRequest 
{
	LCOpenApiRequest base;

	struct SirenStopRequestData
	{
		
		/** [int]设备通道号，从0开始.针对设备级的开启操作，channels这个参数不需要传值 */
		DECLARE_LIST(int) channels;
		/** xxx */
		CSTR token;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} SirenStopRequest;

C_API SirenStopRequest *LCOPENAPI_INIT(SirenStopRequest);

typedef struct SirenStopResponse 
{
	LCOpenApiResponse base;

	struct SirenStopResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} SirenStopResponse;

C_API SirenStopResponse *LCOPENAPI_INIT(SirenStopResponse);

#endif
