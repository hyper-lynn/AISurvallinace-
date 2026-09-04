/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_commonService_QueryUpgradeInfo_H_
#define _HSVIEW_CLIENT_API_commonService_QueryUpgradeInfo_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取客户端可升级版本信息，客户端登陆前调用；
如版本太低不兼容需强制升级（国内乐橙目前版本全部兼容，是否强制升级字段全部返回false，海外乐橙需对客户端版本做检查，版本过低不兼容时置为true）。


----------------请求参数说明-------------------
无，但需按SaaS协议标准填写x-pcs-client-ua内容，服务按x-pcs-client-ua内容做版本检测，
参见：[大华公有云客户端协议说明](http://paas.dahuatech.com/wiki/?p=%2FSaaS%2F%E5%AE%A2%E6%88%B7%E7%AB%AFRestful%E5%8D%8F%E8%AE%AE%E8%AF%B4%E6%98%8E.md&s=pj)
-----------------------------------------------


--------------响应参数说明-----------------
baseVersion	String 必须 增量升级所需的前置最低版本，不需要则置空
baseOSVersion	String 必须 对操作系统版本的最低需求，不需要则置空
lastVersion	String 必须 最新版本
updateInfo	String 必须 最新版本的更新信息
apkUrl	String 必须 最新版本的下载地址
forceUpgrade boolen 必须 是否需要强制升级
redirectToStore String 可选 是否跳转到商店,true表示到商店下载，false表示直接下载
-------------------------------------------


【需要使默认AK、SK签名】
 */

typedef struct commonService_QueryUpgradeInfoRequest 
{
	HsviewRequest base;

	struct commonService_QueryUpgradeInfoRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} commonService_QueryUpgradeInfoRequest;

C_API commonService_QueryUpgradeInfoRequest *HSAPI_INIT(commonService_QueryUpgradeInfoRequest);

typedef struct commonService_QueryUpgradeInfoResponse 
{
	HsviewResponse base;

	struct commonService_QueryUpgradeInfoResponseData
	{
		
		/** 最新版本 */
		CSTR lastVersion;
		/** [O]是否跳转到商店 */
		CSTR redirectToStore;
		/** 增量升级所需的前置最低版本 */
		CSTR baseVersion;
		/** 版本发布时间 */
		CSTR publishTime;
		/** 对操作系统版本的最低需求 */
		CSTR baseOSVersion;
		/** [bool]是否需要强制升级 */
		BOOL forceUpgrade;
		/** 最新版本的下载地址 */
		CSTR apkUrl;
		/** 最新版本的更新信息 */
		CSTR updateInfo;
 
	} data;

} commonService_QueryUpgradeInfoResponse;

C_API commonService_QueryUpgradeInfoResponse *HSAPI_INIT(commonService_QueryUpgradeInfoResponse);

#endif
