/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetShareFile_H_
#define _HSVIEW_CLIENT_API_GetShareFile_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
根据文件ID获取具体的文件信息，包括文件的可用URL。
【需要使用平台账号签名】
 */

typedef struct GetShareFileRequest 
{
	HsviewRequest base;

	struct GetShareFileRequestData
	{
		
		/** [long]需要获取的文件ID */
		int64 fileId;

	} data;

} GetShareFileRequest;

C_API GetShareFileRequest *HSAPI_INIT(GetShareFileRequest);

typedef struct GetShareFileResponse 
{
	HsviewResponse base;

	struct GetShareFileResponseData
	{
		
		/** 发送者用户名 */
		CSTR sender;
		/** 缩略图的可用URL */
		CSTR thumbUrl;
		/** 描述 */
		CSTR desc;
		/** 分享文件的可用URL */
		CSTR fileUrl;
		/** 标题 */
		CSTR title;
		/** 缩略图的加密密钥，为空表示未加密 */
		CSTR thumbKey;
		/** [int]文件类型，1-图片，2-视频 */
		int fileType;
		/** [long]发送时间，UNIX时间戳秒数 */
		int64 time;
		/** 分享文件的加密密钥 */
		CSTR fileKey;
		/** 发送者昵称 */
		CSTR senderNickname;
 
	} data;

} GetShareFileResponse;

C_API GetShareFileResponse *HSAPI_INIT(GetShareFileResponse);

#endif
