/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetShareFileList_H_
#define _HSVIEW_CLIENT_API_GetShareFileList_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取分享的文件列表。
【需要使用平台账号签名】
 */

typedef struct GetShareFileListRequest 
{
	HsviewRequest base;

	struct GetShareFileListRequestData
	{
		
		/** [int]需要获取的数量 */
		int count;
		/** [long]起始文件ID */
		int64 fileId;

	} data;

} GetShareFileListRequest;

C_API GetShareFileListRequest *HSAPI_INIT(GetShareFileListRequest);

typedef struct GetShareFileListResponse 
{
	HsviewResponse base;

	struct GetShareFileListResponseData
	{
		
		/** define a list with struct of GetShareFileListResponseData_FilesElement */
		DECLARE_LIST(struct GetShareFileListResponseData_FilesElement
		{
			/** 发送者用户名 */
			CSTR sender;
			/** 缩略图的可用URL */
			CSTR thumbUrl;
			/** 描述 */
			CSTR desc;
			/** 标题 */
			CSTR title;
			/** 缩略图的加密密钥，为空表示未加密 */
			CSTR thumbKey;
			/** [long]文件ID */
			int64 fileId;
			/** [long]发送时间，UNIX时间戳秒数 */
			int64 time;
			/** [int]文件类型，1-图片，2-视频 */
			int fileType;
			/** 发送者昵称 */
			CSTR senderNickname;
		}) files;
 
	} data;

} GetShareFileListResponse;

C_API GetShareFileListResponse *HSAPI_INIT(GetShareFileListResponse);

#endif
