/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_SendShareFile_H_
#define _HSVIEW_CLIENT_API_SendShareFile_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
发送分享文件给好友。
【需要使用平台账号签名】
 */

typedef struct SendShareFileRequest 
{
	HsviewRequest base;

	struct SendShareFileRequestData
	{
		
		/** 标题 */
		CSTR title;
		/** 接收者用户名 */
		DECLARE_LIST(CSTR) receivers;
		/** 分享文件的加密密钥 */
		CSTR fileKey;
		/** 分享文件的云存储路径 */
		CSTR filePath;
		/** 描述 */
		CSTR desc;

	} data;

} SendShareFileRequest;

C_API SendShareFileRequest *HSAPI_INIT(SendShareFileRequest);

typedef struct SendShareFileResponse 
{
	HsviewResponse base;

	struct SendShareFileResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} SendShareFileResponse;

C_API SendShareFileResponse *HSAPI_INIT(SendShareFileResponse);

#endif
