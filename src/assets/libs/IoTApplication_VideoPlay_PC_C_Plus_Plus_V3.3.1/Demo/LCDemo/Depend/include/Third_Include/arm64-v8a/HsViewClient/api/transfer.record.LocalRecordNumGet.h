/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferRecord_LocalRecordNumGet_H_
#define _HSVIEW_CLIENT_API_transferRecord_LocalRecordNumGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
查询录像总数


参考PaaS协议：[查询录像总数](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E6%9C%AC%E5%9C%B0%E5%BD%95%E5%83%8F%E5%9B%BE%E7%89%87%E4%BF%A1%E6%81%AF%2F%E6%9F%A5%E8%AF%A2%E5%BD%95%E5%83%8F%E6%80%BB%E6%95%B0.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferRecord_LocalRecordNumGetRequest 
{
	HsviewRequest base;

	struct transferRecord_LocalRecordNumGetRequestData
	{
		
		/** 通道号 */
		CSTR channelId;
		/** [cstr]/device/record/num/ */
		#define _STATIC_transferRecord_LocalRecordNumGetRequestData_url "/device/record/num/"
		CSTR url;
		/** struct of transferRecord_LocalRecordNumGetRequestData_Content */
		struct transferRecord_LocalRecordNumGetRequestData_Content {
			/** all */
			CSTR type;
			/** 查询录像开始时间, 设备时间，20031215T144307 */
			CSTR localBeginTime;
			/** 查询录像开始时间,UTC格式，20031215T144307Z */
			CSTR beginTime;
			/** 查询录像结束时间, 设备时间，20031215T145307 */
			CSTR localEndTime;
			/** 查询录像结束时间,UTC格式，20031215T145307Z */
			CSTR endTime;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferRecord_LocalRecordNumGetRequest;

C_API transferRecord_LocalRecordNumGetRequest *HSAPI_INIT(transferRecord_LocalRecordNumGetRequest);

typedef struct transferRecord_LocalRecordNumGetResponse 
{
	HsviewResponse base;

	struct transferRecord_LocalRecordNumGetResponseData
	{
		
		/** 本地录像数量，如100 */
		CSTR recordNum;
 
	} data;

} transferRecord_LocalRecordNumGetResponse;

C_API transferRecord_LocalRecordNumGetResponse *HSAPI_INIT(transferRecord_LocalRecordNumGetResponse);

#endif
