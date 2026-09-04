/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDevice_RemoteDebugSet_H_
#define _HSVIEW_CLIENT_API_transferDevice_RemoteDebugSet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
远程调试使能控制

日志直存时，需要设备有DLS能力

------------请求参数说明------------
log：on-开启日志上传， off-关闭。开启日志直存时（logCloud = on），为可选，否则为必传字段.设备日志埋点开关,当前该功能废弃,App不需要传该字段(能力废除：RDV3	支持RD能力，支持数据埋点控制，支持级别控制)
debug: on-开启调试日志上传,off-关闭, 客户端统一为off, 仅允许公有云后台系统打开, 并且接入库实现时每次重启后重置为off。开启日志直存时，为可选，否则为必传字段
level: [string]，可选，日志等级,设备重启后失效，默认为info
1)debug:调试级别
2)info:重要级别
3)warn:警告级别
4)error:错误级别

logCloud：[string]，可选，日志直存是否开启，当为on时，cloudInfo有效，重启后无效.设备包含能力集:DLS(日志直存 Direct log storage)时使用
cloudInfo：可选，直存信息
type: [string], 数据上传的服务类型
oss: 阿里OSS
url: [string],登入地址
port: [int],登入端口
tls: [bool],是否是https
ak: [string],颁发的AK
sk: [string],颁发的SK
token: [string],颁发的token
bucketName: [string],上传的文件夹路径
fileprefix: [string], 可选，上传的文件唯一前缀
-----------------------------------


------------响应参数说明------------
无
-----------------------------------

参考PaaS协议：[远程调试使能控制](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%BF%9C%E7%A8%8B%E8%B0%83%E8%AF%95%2F%E8%BF%9C%E7%A8%8B%E8%B0%83%E8%AF%95%E4%BD%BF%E8%83%BD.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferDevice_RemoteDebugSetRequest 
{
	HsviewRequest base;

	struct transferDevice_RemoteDebugSetRequestData
	{
		
		/** [cstr]/device/remotedebug/enable */
		#define _STATIC_transferDevice_RemoteDebugSetRequestData_url "/device/remotedebug/enable"
		CSTR url;
		/** struct of transferDevice_RemoteDebugSetRequestData_Content */
		struct transferDevice_RemoteDebugSetRequestData_Content {
			/** [O]设备日志上传开关，on-开启，off-关闭 */
			CSTR log;
			/** [O]设备调试日志开关，on-开启，off-关闭，客户端统一为off */
			CSTR debug;
			/** [O]日志等级debug:调试级别info:重要级别warn:警告级别error:错误级别 */
			CSTR level;
			/** struct of transferDevice_RemoteDebugSetRequestData_Content_CloudInfo */
			struct transferDevice_RemoteDebugSetRequestData_Content_CloudInfo {
				/** [O]上传的文件夹路径 */
				CSTR bucketName;
				/** [O]数据上传的服务类型 */
				CSTR type;
				/** [O]颁发的AK */
				CSTR ak;
				/** [O]颁发的SK */
				CSTR sk;
				/** [O]上传的文件唯一前缀 */
				CSTR fileprefix;
				/** [O][int]登入端口,tls=false,port传80,tls=true,port传443 */
				CSTR port;
				/** [O]颁发的token */
				CSTR token;
				/** [O]登入地址 */
				CSTR url;
				/** [O][bool]是否是https */
				CSTR tls;
			} cloudInfo;
			/** [O]日志直存是否开启，当为on时，cloudInfo有效，重启后无效 */
			CSTR logCloud;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferDevice_RemoteDebugSetRequest;

C_API transferDevice_RemoteDebugSetRequest *HSAPI_INIT(transferDevice_RemoteDebugSetRequest);

typedef struct transferDevice_RemoteDebugSetResponse 
{
	HsviewResponse base;

	struct transferDevice_RemoteDebugSetResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} transferDevice_RemoteDebugSetResponse;

C_API transferDevice_RemoteDebugSetResponse *HSAPI_INIT(transferDevice_RemoteDebugSetResponse);

#endif
