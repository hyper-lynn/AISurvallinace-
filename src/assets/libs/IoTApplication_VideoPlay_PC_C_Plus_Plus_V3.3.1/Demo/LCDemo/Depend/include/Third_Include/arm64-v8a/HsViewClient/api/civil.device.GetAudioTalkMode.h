/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetAudioTalkMode_H_
#define _HSVIEW_CLIENT_API_GetAudioTalkMode_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取对应设备型号的语音对讲模式。
【需要使用平台账号签名】
 */

typedef struct GetAudioTalkModeRequest 
{
	HsviewRequest base;

	struct GetAudioTalkModeRequestData
	{
		
		/** 设备型号 */
		CSTR deviceModel;

	} data;

} GetAudioTalkModeRequest;

C_API GetAudioTalkModeRequest *HSAPI_INIT(GetAudioTalkModeRequest);

typedef struct GetAudioTalkModeResponse 
{
	HsviewResponse base;

	struct GetAudioTalkModeResponseData
	{
		
		/** 语音对讲模式。 UnSupport:不支持；P2P：P2P方式；Transfer:转发方式；FirstP2P:优先尝试P2P； FirstTransfer:优先尝试转发 */
		CSTR mode;
 
	} data;

} GetAudioTalkModeResponse;

C_API GetAudioTalkModeResponse *HSAPI_INIT(GetAudioTalkModeResponse);

#endif
