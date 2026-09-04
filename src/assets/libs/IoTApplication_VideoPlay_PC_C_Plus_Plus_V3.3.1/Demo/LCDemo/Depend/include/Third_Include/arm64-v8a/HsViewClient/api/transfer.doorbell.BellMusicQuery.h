/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDoorbell_BellMusicQuery_H_
#define _HSVIEW_CLIENT_API_transferDoorbell_BellMusicQuery_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取铃声配置及铃声列表（配置在门铃声，控制响的是铃铛）

参考PaaS协议：[获取铃声配置及铃声列表](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E9%97%A8%E9%93%83%E7%9B%B8%E5%85%B3%E6%93%8D%E4%BD%9C%2F%E9%93%83%E5%A3%B0%2F%E8%8E%B7%E5%8F%96%E9%93%83%E5%A3%B0%E9%85%8D%E7%BD%AE%E5%8F%8A%E9%93%83%E5%A3%B0%E5%88%97%E8%A1%A8.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferDoorbell_BellMusicQueryRequest 
{
	HsviewRequest base;

	struct transferDoorbell_BellMusicQueryRequestData
	{
		
		/** [cstr]/device/bell/music/query */
		#define _STATIC_transferDoorbell_BellMusicQueryRequestData_url "/device/bell/music/query"
		CSTR url;
		/** struct of transferDoorbell_BellMusicQueryRequestData_Content */
		struct transferDoorbell_BellMusicQueryRequestData_Content {
			/** 生效类型,device:关联设备报警,accessory:关联配件报警,reply:关联自定义回复,local: 设备本地铃声，按下门铃后的响声 */
			CSTR relateType;
			/** [O]通道,不存在默认为设备 */
			CSTR chan;
			/** [O]设备序列号 */
			CSTR sn;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferDoorbell_BellMusicQueryRequest;

C_API transferDoorbell_BellMusicQueryRequest *HSAPI_INIT(transferDoorbell_BellMusicQueryRequest);

typedef struct transferDoorbell_BellMusicQueryResponse 
{
	HsviewResponse base;

	struct transferDoorbell_BellMusicQueryResponseData
	{
		
		/** define a list with struct of transferDoorbell_BellMusicQueryResponseData_ListElement */
		DECLARE_LIST(struct transferDoorbell_BellMusicQueryResponseData_ListElement
		{
			/** [O]铃声状态, play：可播放, download：下载中，不可播放， 该字段不存在或为空，默认为play */
			CSTR state;
			/** 铃声类型:wav,pcm,aac */
			CSTR type;
			/** [int]歌曲索引，从0开始 */
			int index;
			/** [O]关联铃声生效类型，device:关联设备报警，accessory:关联配件报警,reply:关联自定义回复 */
			CSTR relateType;
			/** 区分默认铃声/自定义铃声，default:默认铃声，custom:自定义 */
			CSTR ringMode;
			/** 歌曲名称 */
			CSTR name;
		}) list;
		/** [int]用户配置的铃声索引。-1：表示未配置 */
		int ringIndex;
 
	} data;

} transferDoorbell_BellMusicQueryResponse;

C_API transferDoorbell_BellMusicQueryResponse *HSAPI_INIT(transferDoorbell_BellMusicQueryResponse);

#endif
