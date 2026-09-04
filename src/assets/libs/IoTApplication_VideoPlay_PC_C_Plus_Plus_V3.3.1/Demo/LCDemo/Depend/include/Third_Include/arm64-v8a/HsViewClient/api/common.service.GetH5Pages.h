/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_commonService_GetH5Pages_H_
#define _HSVIEW_CLIENT_API_commonService_GetH5Pages_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 

获取云存储h5

type 页面类型：
storageStrategyDetail：云存储详情，
storageStrategyBuy：云存储购买，
userStorageStrategy：我的云存储，
windowStrategyBuy：不限流套餐购买
pcStorageStrategyBuy: PC云存储购买
phonealarm：电话报警提醒，
timeAlbum: 时光相册
devShareStrategy:设备分享套餐
timeAlbumUser:“我的”界面使用-时光相册
lcnas:“我的”界面使用-私有云
devShareStrategyUser:“我的”界面使用-设备分享套餐
callCenter:“我的”界面使用-客服中心
squareVideo:视频广场
shop:商城
myShop:我的商城
userCancellation:用户注销
friendList:好友列表
deviceTransferFriendList：设备转移时好友列表
deviceShareFriendList：设备分享时好友列表
humanAlarmStrategy：我的页面-智能人形检测套餐
sightPage:客户端发现页
msgNotifyConfig:安卓消息列表顶部开启告警消息通知开关配置页
strangerAlarmStrategy:陌生人提醒
strangerAlarmStrategyUser：“我的”界面使用-陌生人提醒
timeAlbumDesc：每日影集-服务说明
userRegisterProtocol：用户注册协议
serverProtocol：乐橙云服务协议
privacyPolicy：乐橙隐私政策
unbindApply：解绑申请详情页面
synchGroup：组同步
deviceOfflineTips：设备离线帮助
storageStrategyProtocol：云存储服务协议
freeStorageStrategyDetail 免费云存储详情
encryptStrategyDetail 加密套餐详情

【不需要鉴权】
 */

typedef struct commonService_GetH5PagesRequest 
{
	HsviewRequest base;

	struct commonService_GetH5PagesRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} commonService_GetH5PagesRequest;

C_API commonService_GetH5PagesRequest *HSAPI_INIT(commonService_GetH5PagesRequest);

typedef struct commonService_GetH5PagesResponse 
{
	HsviewResponse base;

	struct commonService_GetH5PagesResponseData
	{
		
		/** define a list with struct of commonService_GetH5PagesResponseData_PagesElement */
		DECLARE_LIST(struct commonService_GetH5PagesResponseData_PagesElement
		{
			/** 页面类型 */
			CSTR type;
			/** 页面的访问地址url */
			CSTR url;
			/** [O]协议更新时间，精确到秒的Unix时间戳(如1585636224)，字符串类型 */
			CSTR updateTime;
		}) pages;
 
	} data;

} commonService_GetH5PagesResponse;

C_API commonService_GetH5PagesResponse *HSAPI_INIT(commonService_GetH5PagesResponse);

#endif
