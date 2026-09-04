/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_SetMotionDetectSensitive_H_
#define _HSVIEW_CLIENT_API_SetMotionDetectSensitive_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置动检灵敏度
Sensitive: 灵敏度，取值[0, 100]
Threshold: 面积阀值，取值[0, 100]
乐橙客户端阀值与灵敏度、面积阀值对应表，由产品提供。

单通道设备和多通道设备，都[channel-id]都必须填写。
 */

typedef struct SetMotionDetectSensitiveRequest 
{
	HsviewRequest base;

	struct SetMotionDetectSensitiveRequestData
	{
		
		/** 设备ID */
		CSTR devId;
		/** 必须填写通道号 */
		CSTR optional;
		/** [cstr]POST */
		#define _STATIC_SetMotionDetectSensitiveRequestData_METHOD "POST"
		/** [cstr]motion-detect-sensitive */
		#define _STATIC_SetMotionDetectSensitiveRequestData_CMD "motion-detect-sensitive"
		/** struct of SetMotionDetectSensitiveRequestData_Body */
		struct SetMotionDetectSensitiveRequestData_Body {
			/** [int]面积阀值：取值[0, 100] */
			int Threshold;
			/** [int]灵敏度：取值[0, 100] */
			int Sensitive;
		} body;

	} data;

} SetMotionDetectSensitiveRequest;

C_API SetMotionDetectSensitiveRequest *HSAPI_INIT(SetMotionDetectSensitiveRequest);

typedef struct SetMotionDetectSensitiveResponse 
{
	HsviewResponse base;

	struct SetMotionDetectSensitiveResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} SetMotionDetectSensitiveResponse;

C_API SetMotionDetectSensitiveResponse *HSAPI_INIT(SetMotionDetectSensitiveResponse);

#endif
