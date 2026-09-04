/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetSpeechRecognition_H_
#define _HSVIEW_CLIENT_API_GetSpeechRecognition_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取设备语音识别状态(TC5S需求)

Enable: 1-开启 0-关闭
 */

typedef struct GetSpeechRecognitionRequest 
{
	HsviewRequest base;

	struct GetSpeechRecognitionRequestData
	{
		
		/** 设备ID */
		CSTR devId;
		/** 无需设置 */
		CSTR optional;
		/** [cstr]GET */
		#define _STATIC_GetSpeechRecognitionRequestData_METHOD "GET"
		/** [cstr]speech-recognition */
		#define _STATIC_GetSpeechRecognitionRequestData_CMD "speech-recognition"
		/** struct of GetSpeechRecognitionRequestData_Body */
		struct GetSpeechRecognitionRequestData_Body {
			/** [int][O]保留 */
			int _nouse;
		} body;

	} data;

} GetSpeechRecognitionRequest;

C_API GetSpeechRecognitionRequest *HSAPI_INIT(GetSpeechRecognitionRequest);

typedef struct GetSpeechRecognitionResponse 
{
	HsviewResponse base;

	struct GetSpeechRecognitionResponseData
	{
		
		/** [int]使能：取值1-开启 0-关闭 */
		int Enable;
 
	} data;

} GetSpeechRecognitionResponse;

C_API GetSpeechRecognitionResponse *HSAPI_INIT(GetSpeechRecognitionResponse);

#endif
