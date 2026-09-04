/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDoorbell_DoorMusicQuery_H_
#define _HSVIEW_CLIENT_API_transferDoorbell_DoorMusicQuery_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取门铃铃声（门铃自带铃声）

参考PaaS协议：[获取门铃铃声](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E9%97%A8%E9%93%83%E7%9B%B8%E5%85%B3%E6%93%8D%E4%BD%9C%2F%E9%93%83%E5%A3%B0%2F%E8%8E%B7%E5%8F%96%E9%93%83%E5%A3%B0%E9%85%8D%E7%BD%AE%E5%8F%8A%E9%93%83%E5%A3%B0%E5%88%97%E8%A1%A8%28%E9%97%A8%E9%93%83Amcrest%29.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferDoorbell_DoorMusicQueryRequest 
{
	HsviewRequest base;

	struct transferDoorbell_DoorMusicQueryRequestData
	{
		
		/** 设备序列号 */
		CSTR deviceId;
		/** [cstr]/device/doorbell/music/query */
		#define _STATIC_transferDoorbell_DoorMusicQueryRequestData_url "/device/doorbell/music/query"
		CSTR url;

	} data;

} transferDoorbell_DoorMusicQueryRequest;

C_API transferDoorbell_DoorMusicQueryRequest *HSAPI_INIT(transferDoorbell_DoorMusicQueryRequest);

typedef struct transferDoorbell_DoorMusicQueryResponse 
{
	HsviewResponse base;

	struct transferDoorbell_DoorMusicQueryResponseData
	{
		
		/** define a list with struct of transferDoorbell_DoorMusicQueryResponseData_ListElement */
		DECLARE_LIST(struct transferDoorbell_DoorMusicQueryResponseData_ListElement
		{
			/** [int]歌曲索引，从0开始 */
			int index;
			/** 歌曲名称 */
			CSTR name;
		}) list;
		/** [int]用户配置的铃声索引。-1：表示未配置 */
		int ringIndex;
 
	} data;

} transferDoorbell_DoorMusicQueryResponse;

C_API transferDoorbell_DoorMusicQueryResponse *HSAPI_INIT(transferDoorbell_DoorMusicQueryResponse);

#endif
