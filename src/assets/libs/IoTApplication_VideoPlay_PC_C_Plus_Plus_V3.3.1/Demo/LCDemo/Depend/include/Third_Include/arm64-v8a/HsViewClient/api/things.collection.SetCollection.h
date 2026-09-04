/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_thingsCollection_SetCollection_H_
#define _HSVIEW_CLIENT_API_thingsCollection_SetCollection_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置收藏点。

注意：客户端协议都是针对单通道的，PASS层协议都是多通道，两者没有必然的联系

参考PaaS协议：[设置设备收藏点](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E6%94%B6%E8%97%8F%E7%82%B9%E9%85%8D%E7%BD%AE%2F%E8%AE%BE%E7%BD%AE%E8%AE%BE%E5%A4%87%E6%94%B6%E8%97%8F%E7%82%B9.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct thingsCollection_SetCollectionRequest 
{
	HsviewRequest base;

	struct thingsCollection_SetCollectionRequestData
	{
		
		/** [O]图片二进制数据的base64编码字符串 */
		CSTR pic;
		/** 收藏点名称，作为收藏点的唯一标示符，不允许重复 */
		CSTR name;
		/** [O]巡航计划唯一标示符.当bCruise=true时有效 */
		CSTR cruiseName;
		/** [int][O]停留时间，单位S。为空时，以设备默认值为准 */
		int stayTime;
		/** 通道号 */
		CSTR channelId;
		/** [bool] 是否加入到巡航计划中 */
		BOOL bCruise;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} thingsCollection_SetCollectionRequest;

C_API thingsCollection_SetCollectionRequest *HSAPI_INIT(thingsCollection_SetCollectionRequest);

typedef struct thingsCollection_SetCollectionResponse 
{
	HsviewResponse base;

	struct thingsCollection_SetCollectionResponseData
	{
		
		/** 收藏点图片路径 */
		CSTR picUrl;
 
	} data;

} thingsCollection_SetCollectionResponse;

C_API thingsCollection_SetCollectionResponse *HSAPI_INIT(thingsCollection_SetCollectionResponse);

#endif
