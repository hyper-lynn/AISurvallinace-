/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_SetSpeechRecognition_H_
#define _HSVIEW_CLIENT_API_SetSpeechRecognition_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取设备语音识别状态(TC5S需求)
Enable: 1-开启 0-关闭
 */

typedef struct SetSpeechRecognitionRequest 
{
	HsviewRequest base;

	struct SetSpeechRecognitionRequestData
	{
		
		/** 设备ID */
		CSTR devId;
		/** 无需设置 */
		CSTR optional;
		/** [cstr]POST */
		#define _STATIC_SetSpeechRecognitionRequestData_METHOD "POST"
		/** [cstr]speech-recognition */
		#define _STATIC_SetSpeechRecognitionRequestData_CMD "speech-recognition"
		/** struct of SetSpeechRecognitionRequestData_Body */
		struct SetSpeechRecognitionRequestData_Body {
			/** [int]使能：取值1-开启 0-关闭 */
			int Enable;
		} body;

	} data;

} SetSpeechRecognitionRequest;

C_API SetSpeechRecognitionRequest *HSAPI_INIT(SetSpeechRecognitionRequest);

typedef struct SetSpeechRecognitionResponse 
{
	HsviewResponse base;

	struct SetSpeechRecognitionResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} SetSpeechRecognitionResponse;

C_API SetSpeechRecognitionResponse *HSAPI_INIT(SetSpeechRecognitionResponse);

#endif
