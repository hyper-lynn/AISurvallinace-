/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 223966, Author: 112352, Date: 2022-12-07 20:46:41 +0800 
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _LC_OPENAPI_CLIENT_DeviceInfo_H_
#define _LC_OPENAPI_CLIENT_DeviceInfo_H_

#include "LCOpenApiClientSdk.h"

/** DESCRIPTION: 
获取单个设备的信息

 */

typedef struct DeviceInfoRequest 
{
	LCOpenApiRequest base;

	struct DeviceInfoRequestData
	{
		
		/** [String]拉流回放地址 */
		CSTR appendUrl;
		/** 授权token(userToken或accessToken) */
		CSTR token;
		/** 设备ID */
		CSTR deviceId;

	} data;

} DeviceInfoRequest;

C_API DeviceInfoRequest *LCOPENAPI_INIT(DeviceInfoRequest);

typedef struct DeviceInfoResponse 
{
	LCOpenApiResponse base;

	struct DeviceInfoResponseData
	{
		
		/** [int]平台类型 */
		int platForm;
		/** define a list with struct of DeviceInfoResponseData_ChannelsElement */
		DECLARE_LIST(struct DeviceInfoResponseData_ChannelsElement
		{
			/** [int]报警布撤防状态，0-撤防，1-布防 */
			int alarmStatus;
			/** 通道名称 */
			CSTR channelName;
			/** [O]通道能力项，逗号隔开，如AlarmMD,AudioTalk,AlarmPIR,WLAN,VVP2P，详见乐橙设备协议 */
			CSTR channelAbility;
			/** 缩略图URL */
			CSTR channelPicUrl;
			/** [int]通道号 */
			int channelId;
			/** [bool]是否在线 */
			BOOL channelOnline;
			/** [int]云存储状态：-1-未开通 0-已失效 1-使用中 2-套餐暂停 */
			int csStatus;
		}) channels;
		/** struct of DeviceInfoResponseData_StreamInfo */
		struct DeviceInfoResponseData_StreamInfo {
			/** [String]辅助帧(开放平台5.3需求新增参数) */
			CSTR assistStream;
			/** [int][O]限制并发路数 -1:不限制路数 其它:具体限制数 */
			int videoLimit;
			/** [String]设备级对讲与通道级对讲类型区分，device：表示设备级对讲，channel：表示通道级对讲 */
			CSTR deviceType;
			/** [String]是否跳过回环认证 */
			CSTR skipAuth;
			/** [String]一次性Token */
			CSTR rtspToken;
			/** [bool][O]是否限流 */
			BOOL timeLimit;
			/** [String]请求拉流分类，real：实时预览；playbackByTime：按时间回放；playbackByRecordId：按文件id回放；talk：对讲 */
			CSTR requestType;
			/** [String]所要请求码流的加密类型 */
			CSTR encrypt;
			/** [String]可选，协议拉流类型 */
			CSTR type;
			/** [String]回放结束时间，requestType为playbackByTime时有值返回，其他为空字符串 */
			CSTR endTime;
			/** [O]流量统计时所属用户的唯一标识，当前用userId */
			CSTR owner;
			/** [String]设置拉流时长，单位：min */
			CSTR duration;
			/** [String]pc客户端拉流窗口号 */
			CSTR windowNum;
			/** [String]回放文件id，requestType为playbackByRecordId时有值返回，其他为空字符串 */
			CSTR recordId;
			/** [String]回放开始时间，requestType为playbackByTime时有值返回，其他为空字符串 */
			CSTR startTime;
			/** [O]所属平台open:开放平台 base:乐橙平台 */
			CSTR ownerType;
			/** [int]通道ID */
			int channelId;
			/** [String]主、辅码流编号 */
			CSTR streamId;
			/** 获取实时流url的入口地址 */
			CSTR streamEntryAddr;
		} streamInfo;
		/** [int]p2p拉流端口 */
		int streamPort;
		/** [bool]是否有新版本可以升级 */
		BOOL canBeUpgrade;
		/** [int]当前状态：0-离线，1-在线，3-升级中 */
		int status;
		/** 设备登陆密码 */
		CSTR devLoginPassword;
		/** 长链接地址（新） */
		CSTR streamAddr;
		/** [O]设备能力项，逗号隔开，如AlarmMD,AudioTalk,AlarmPIR,WLAN,VVP2P，详见乐橙设备协议 */
		CSTR ability;
		/** 设备名称 */
		CSTR name;
		/** [int]netsdk私有协议拉流端口 */
		int port;
		/** 设备ID */
		CSTR deviceId;
		/** [int]总的视频通道数，包含未接入的通道 */
		int channelNum;
		/** [int]http私有协议拉流端口 */
		int httpPort;
		/** 设备软件版本号 */
		CSTR version;
		/** [int]rtsp拉流端口 */
		int rtspPort;
		/** [O]设备型号 */
		CSTR deviceModel;
		/** [int]加密模式 */
		int encryptMode;
		/** 设备登陆用户名 */
		CSTR devLoginName;
		/** 长链接地址 */
		CSTR streamEntryAddr;
 
	} data;

} DeviceInfoResponse;

C_API DeviceInfoResponse *LCOPENAPI_INIT(DeviceInfoResponse);

#endif
