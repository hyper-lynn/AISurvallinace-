/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_RecoverSDCard_H_
#define _HSVIEW_CLIENT_API_RecoverSDCard_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
请求初始化SD卡。
[channel-id]可填，表示初始化某个通道IPC的SD卡。不填表示初始化该设备的SD卡。

Result表示执行结果：
start-recover：开始初始化（正常情况下）
no-sdcard：插槽内无SD卡
in-recover：正在初始化（有可能别的客户端已经请求初始化）
already-recover：已被初始化（有可能别的客户端已经把SD卡初始化掉了）
sdcard-error：其他SD卡错误
 */

typedef struct RecoverSDCardRequest 
{
	HsviewRequest base;

	struct RecoverSDCardRequestData
	{
		
		/** 设备ID */
		CSTR devId;
		/** 填写通道号 */
		CSTR optional;
		/** [cstr]POST */
		#define _STATIC_RecoverSDCardRequestData_METHOD "POST"
		/** [cstr]sdcard-recover */
		#define _STATIC_RecoverSDCardRequestData_CMD "sdcard-recover"
		/** struct of RecoverSDCardRequestData_Body */
		struct RecoverSDCardRequestData_Body {
			/** [int][O]保留 */
			int _nouse;
		} body;

	} data;

} RecoverSDCardRequest;

C_API RecoverSDCardRequest *HSAPI_INIT(RecoverSDCardRequest);

typedef struct RecoverSDCardResponse 
{
	HsviewResponse base;

	struct RecoverSDCardResponseData
	{
		
		/** 结果字串 */
		CSTR Result;
 
	} data;

} RecoverSDCardResponse;

C_API RecoverSDCardResponse *HSAPI_INIT(RecoverSDCardResponse);

#endif
