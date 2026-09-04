/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_thingsRecord_GetLocalRecordBitmap_H_
#define _HSVIEW_CLIENT_API_thingsRecord_GetLocalRecordBitmap_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取设备本地录像信息，参考设备协议：[查询录像月历掩码](https://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E6%9C%AC%E5%9C%B0%E5%BD%95%E5%83%8F%E5%9B%BE%E7%89%87%E4%BF%A1%E6%81%AF%2F%E6%9F%A5%E8%AF%A2%E5%BD%95%E5%83%8F%E6%9C%88%E5%8E%86%E6%8E%A9%E7%A0%81.md&s=pd),type的可选值以[设备录像/图片类型](https://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E6%9C%AC%E5%9C%B0%E5%BD%95%E5%83%8F%E5%9B%BE%E7%89%87%E4%BF%A1%E6%81%AF%2FHome.md&s=pd)为准

bitmap: 不超过31个字节，表示该月中每一天是否存在录像，1表示有录像，0表示没有录像


【需要使用平台账号签名】
 */

typedef struct thingsRecord_GetLocalRecordBitmapRequest 
{
	HsviewRequest base;

	struct thingsRecord_GetLocalRecordBitmapRequestData
	{
		
		/** 录像类型 */
		CSTR type;
		/** [long]年份 */
		int64 year;
		/** [long]月份 */
		int64 month;
		/** 通道号 */
		CSTR channelId;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} thingsRecord_GetLocalRecordBitmapRequest;

C_API thingsRecord_GetLocalRecordBitmapRequest *HSAPI_INIT(thingsRecord_GetLocalRecordBitmapRequest);

typedef struct thingsRecord_GetLocalRecordBitmapResponse 
{
	HsviewResponse base;

	struct thingsRecord_GetLocalRecordBitmapResponseData
	{
		
		/** 月历掩码，如1111100000111110000011111000001 */
		CSTR bitmap;
 
	} data;

} thingsRecord_GetLocalRecordBitmapResponse;

C_API thingsRecord_GetLocalRecordBitmapResponse *HSAPI_INIT(thingsRecord_GetLocalRecordBitmapResponse);

#endif
