/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 219104, Author: 32500, Date: 2021-04-12 19:50:48 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_DoorbellMusicList_H_
#define _LC_OPENAPI_CLIENT_DoorbellMusicList_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取门铃的铃声列表
 */

typedef struct DoorbellMusicListRequest 
{
	LCOpenApiRequest base;

	struct DoorbellMusicListRequestData
	{
		
		/** 授权的token */
		CSTR token;
		/** 门铃设备序列号 */
		CSTR deviceId ;

	} data;

} DoorbellMusicListRequest;

C_API DoorbellMusicListRequest *LCOPENAPI_INIT(DoorbellMusicListRequest);

typedef struct DoorbellMusicListResponse 
{
	LCOpenApiResponse base;

	struct DoorbellMusicListResponseData
	{
		
		/** define a list with struct of DoorbellMusicListResponseData_ListElement */
		DECLARE_LIST(struct DoorbellMusicListResponseData_ListElement
		{
			/** [int]门铃自带的铃声索引号，从0开始 */
			int index;
			/** 门铃自带的铃声名称 */
			CSTR name;
		}) list;
		/** [int]用户配置的铃声索引。-1：表示未配置 */
		int ringIndex;
 
	} data;

} DoorbellMusicListResponse;

C_API DoorbellMusicListResponse *LCOPENAPI_INIT(DoorbellMusicListResponse);

#endif
