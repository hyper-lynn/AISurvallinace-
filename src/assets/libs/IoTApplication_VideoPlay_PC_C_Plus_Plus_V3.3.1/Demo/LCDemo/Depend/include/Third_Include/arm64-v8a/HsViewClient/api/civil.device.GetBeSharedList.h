/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetBeSharedList_H_
#define _HSVIEW_CLIENT_API_GetBeSharedList_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取被别人的分享或者授权的设备列表。

回复字段如下：
deviceId：设备ID
baseline：设备基线类型，详见设备Baseline类型
deviceModel:设备型号
name：设备名称
ability：设备能力选项列表，详见设备能力集选项
canBeUpgrade：设备是否能够升级，true/false
设备的视频通道，其中：
  id：通道号
  name：通道名称
  ablility 通道能力项列表
  online：是否在线，true/false
  picurl：通道缩略图URL
  functions: 共享和授权的权限列表合集(并集)

contentEncrypt:设备通道封面码流加密模式，字段详细说明参考[设备加密](../设备加密.md)
  
【需要使用平台账号签名】

 */

typedef struct GetBeSharedListRequest 
{
	HsviewRequest base;

	struct GetBeSharedListRequestData
	{
		
		/** 用户名 */
		CSTR username;
		/** 类型，share或者auth，share表示共享，auth表示授权 */
		CSTR type;
		/** [O]分页获取,从第几条到第几条，如“1-50”,闭区间,最多一次查询50条 */
		CSTR need;
		/** 过滤器，每个元素表示要获取的设备ID，数组为空表示不过滤 */
		DECLARE_LIST(CSTR) filter;

	} data;

} GetBeSharedListRequest;

C_API GetBeSharedListRequest *HSAPI_INIT(GetBeSharedListRequest);

typedef struct GetBeSharedListResponse 
{
	HsviewResponse base;

	struct GetBeSharedListResponseData
	{
		
		/** define a list with struct of GetBeSharedListResponseData_DevicesElement */
		DECLARE_LIST(struct GetBeSharedListResponseData_DevicesElement
		{
			/** struct of GetBeSharedListResponseData_DevicesElement_ContentEncrypt */
			struct GetBeSharedListResponseData_DevicesElement_ContentEncrypt {
				/** 密钥生成算法版本号 */
				CSTR ruleVersion;
				/** 内容加密模式 */
				CSTR encryptMode;
				/** 内容加密秘钥种子KeySeed的模式 */
				CSTR keyMode;
			} contentEncrypt;
			/** [bool]是否有新版本可以升级 */
			BOOL canBeUpgrade;
			/** [int]当前状态：0-离线，1-在线，3-升级中 */
			int status;
			/** [O]设备分类【NVR/DVR/HCVR/IPC/SD/IHG/ARC】 */
			CSTR deviceCatalog;
			/** [O]设备基线类型，详见华视微讯设备协议 */
			CSTR baseline;
			/** 共享或者授权的功能列表（逗号隔开） */
			CSTR functions;
			/** [O]设备能力项，逗号隔开，如AlarmMD,AudioTalk,AlarmPIR,WLAN,VVP2P，详见华视微讯设备协议 */
			CSTR ability;
			/** [O]设备品牌信息：lechange-乐橙设备，general-通用设备 */
			CSTR brand;
			/** 设备ID */
			CSTR deviceId;
			/** [O]设备型号 */
			CSTR deviceModel;
			/** 通道名称 */
			CSTR channelName;
			/** 设备名称 */
			CSTR name;
			/** [int][O] 设备接入是否通过大华paas协议，可选，无该字段或者为0表示通过老的乐橙平台接入，为1表示通过大华paas协议接入 */
			int paasFlag;
			/** 缩略图URL */
			CSTR channelPicUrl;
			/** [int]通道号 */
			int channelId;
			/** [bool]是否在线 */
			BOOL channelOnline;
			/** 设备软件版本号 */
			CSTR version;
		}) devices;
 
	} data;

} GetBeSharedListResponse;

C_API GetBeSharedListResponse *HSAPI_INIT(GetBeSharedListResponse);

#endif
