/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_dmssManage_UserDeviceAdd_H_
#define _HSVIEW_CLIENT_API_dmssManage_UserDeviceAdd_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
DMSS新增设备信息保存到平台

注意点：
1、did生成规则：
	1)、ddns添加：deviceDdnsDomain_moduletype; 
	2)、序列号添加：deviceSN_moduletype; 
	3)、IP添加：deviceIp_devicePort_moduletype;
2、"deviceId"、"ddnsDomain"、"deviceIp"、"devicePort"均为可选,设备序列号添加时必带序列号，ddns添加时必须带ddns的域名，ip添加时必须带设备ip和端口
3、接口须带SaaS协议的clientUA头信息，
4、加密算法：
计算值的公式为，Base64(AES256_CBC(待加密内容，key[]，iv[]))。

加密规则如下：

采用CBC分组加密的方式，且固定的初始化向量（iv）；

密匙（key）为：MD5(did原文 + 'DAHUAKEY')-------------------did本身加密的key使用MD5(用户名 + 'DAHUAKEY')

说明：(1) 密匙为（设备Id+固定字符串）后的MD5值;

(2) MD5后的值为小写

加密算法为：Base64(AES256_CBC(password，key[]，iv[]))

说明：(1) password为新、旧密码，

(2) key[]为密匙的二进制数组，

(3) iv[]为初始化向量的二进制数组

加密算法测试用例：

iv=0a52uuEvqTTTTTTT

deviceCode=123456789

password=123456789abc

结果为 W8UNXMWbHHRz2vOaYCpQhw==

【需要使用平台账号签名】
 */

typedef struct dmssManage_UserDeviceAddRequest 
{
	HsviewRequest base;

	struct dmssManage_UserDeviceAddRequestData
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

	} data;

} dmssManage_UserDeviceAddRequest;

C_API dmssManage_UserDeviceAddRequest *HSAPI_INIT(dmssManage_UserDeviceAddRequest);

typedef struct dmssManage_UserDeviceAddResponse 
{
	HsviewResponse base;

	struct dmssManage_UserDeviceAddResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} dmssManage_UserDeviceAddResponse;

C_API dmssManage_UserDeviceAddResponse *HSAPI_INIT(dmssManage_UserDeviceAddResponse);

#endif
