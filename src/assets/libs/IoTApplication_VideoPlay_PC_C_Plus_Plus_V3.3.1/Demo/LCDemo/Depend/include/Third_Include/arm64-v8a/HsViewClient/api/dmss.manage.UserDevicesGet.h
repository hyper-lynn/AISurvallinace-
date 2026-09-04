/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_dmssManage_UserDevicesGet_H_
#define _HSVIEW_CLIENT_API_dmssManage_UserDevicesGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取用户下所有设备信息

【需要使用平台账号签名】
 */

typedef struct dmssManage_UserDevicesGetRequest 
{
	HsviewRequest base;

	struct dmssManage_UserDevicesGetRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} dmssManage_UserDevicesGetRequest;

C_API dmssManage_UserDevicesGetRequest *HSAPI_INIT(dmssManage_UserDevicesGetRequest);

typedef struct dmssManage_UserDevicesGetResponse 
{
	HsviewResponse base;

	struct dmssManage_UserDevicesGetResponseData
	{
		
		/** define a list with struct of dmssManage_UserDevicesGetResponseData_DeviceListElement */
		DECLARE_LIST(struct dmssManage_UserDevicesGetResponseData_DeviceListElement
		{
			/** [O]设备ddns域名（Base64(AES256加密)）, ddns添加模式时传 */
			CSTR deviceDdnsDomain;
			/** [O]通道数 */
			CSTR channelCount;
			/** [O]设备IP（Base64(AES256加密)）, IP添加模式时传 */
			CSTR deviceIp;
			/** [O]设备名称,长度限制32字符 */
			CSTR deviceName;
			/** 平台判断是否同一台设备的标示符（Base64(AES256加密)） */
			CSTR did;
			/** 设备密码（Base64(AES256加密)）,原文长度限制32字符 */
			CSTR devicePassword;
			/** [O]模块类型：CCTV,DOOR.... */
			CSTR moduleType;
			/** [O]额外信息,字符串,json格式转字符串存储，供DMSS自行扩展用，字符串长度不得超过1024 */
			CSTR extra;
			/** [O]是否只传声音： true, false */
			CSTR soundOnly;
			/** [O]房间名称,长度限制32字符 */
			CSTR roomName;
			/** [O]预览码流类型 */
			CSTR previewType;
			/** [O]真正显示用的房间名称，长度限制32字符 */
			CSTR showRoomName;
			/** [O]是否包含VTO： true, false */
			CSTR hasVto;
			/** [O]是否支持多画面预览(0通道)：true, false */
			CSTR isSupportPreview;
			/** 设备添加类型 */
			CSTR deviceAddType;
			/** 设备用户名（Base64(AES256加密)）,原文长度限制32字符 */
			CSTR deviceUserName;
			/** [O]设备端口, IP添加模式时传 */
			CSTR devicePort;
			/** [O]设备序列号, 序列号添加模式时传 */
			CSTR deviceSerialNumber;
			/** [O]回放码流类型 */
			CSTR playbackType;
		}) deviceList;
 
	} data;

} dmssManage_UserDevicesGetResponse;

C_API dmssManage_UserDevicesGetResponse *HSAPI_INIT(dmssManage_UserDevicesGetResponse);

#endif
