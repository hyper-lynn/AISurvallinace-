/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetMotionDetectSensitive_H_
#define _HSVIEW_CLIENT_API_GetMotionDetectSensitive_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置动检灵敏度
Sensitive: 灵敏度，取值[0, 100]
Threshold: 面积阀值，取值[0, 100]
乐橙客户端阀值与灵敏度、面积阀值对应表，由产品提供。

单通道设备和多通道设备，都[channel-id]都必须填写。
 */

typedef struct GetMotionDetectSensitiveRequest 
{
	HsviewRequest base;

	struct GetMotionDetectSensitiveRequestData
	{
		
		/** 设备ID */
		CSTR devId;
		/** 填写通道号 */
		CSTR optional;
		/** [cstr]GET */
		#define _STATIC_GetMotionDetectSensitiveRequestData_METHOD "GET"
		/** [cstr]motion-detect-sensitive */
		#define _STATIC_GetMotionDetectSensitiveRequestData_CMD "motion-detect-sensitive"
		/** struct of GetMotionDetectSensitiveRequestData_Body */
		struct GetMotionDetectSensitiveRequestData_Body {
			/** [int][O]保留 */
			int _nouse;
		} body;

	} data;

} GetMotionDetectSensitiveRequest;

C_API GetMotionDetectSensitiveRequest *HSAPI_INIT(GetMotionDetectSensitiveRequest);

typedef struct GetMotionDetectSensitiveResponse 
{
	HsviewResponse base;

	struct GetMotionDetectSensitiveResponseData
	{
		
		/** [int]面积阀值：取值[0, 100] */
		int Threshold;
		/** [int]灵敏度：取值[0, 100] */
		int Sensitive;
 
	} data;

} GetMotionDetectSensitiveResponse;

C_API GetMotionDetectSensitiveResponse *HSAPI_INIT(GetMotionDetectSensitiveResponse);

#endif
