/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_essInfo_GetPersonalReport_H_
#define _HSVIEW_CLIENT_API_essInfo_GetPersonalReport_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取用户年报详情。

【使用平台账号签名】
 */

typedef struct essInfo_GetPersonalReportRequest 
{
	HsviewRequest base;

	struct essInfo_GetPersonalReportRequestData
	{
		
		/** 报告类型，year：年报  month：月报  week：周报 */
		CSTR type;

	} data;

} essInfo_GetPersonalReportRequest;

C_API essInfo_GetPersonalReportRequest *HSAPI_INIT(essInfo_GetPersonalReportRequest);

typedef struct essInfo_GetPersonalReportResponse 
{
	HsviewResponse base;

	struct essInfo_GetPersonalReportResponseData
	{
		
		/** struct of essInfo_GetPersonalReportResponseData_DeviceInfo */
		struct essInfo_GetPersonalReportResponseData_DeviceInfo {
			/** [int]设备个数 */
			int devNum;
			/** [int]智能锁（把） */
			int lockNum;
		} deviceInfo;
		/** struct of essInfo_GetPersonalReportResponseData_StorageInfo */
		struct essInfo_GetPersonalReportResponseData_StorageInfo {
			/** [double]排名百分比 */
			double payRank;
			/** [int]累计套餐个数 */
			int storageTotal;
			/** [double]消费金额 */
			double pays;
			/** [int]最多云存储套餐个数 */
			int storageMaxNum;
			/** 年度首单时间，格式：yyyy-MM-dd */
			CSTR orderTime;
			/** 最多云存储套餐 */
			CSTR storageMax;
		} storageInfo;
		/** [int] 0:未中奖  1:中奖 */
		int status;
		/** struct of essInfo_GetPersonalReportResponseData_PlayInfo */
		struct essInfo_GetPersonalReportResponseData_PlayInfo {
			/** 实时视频最长的一天 */
			CSTR longestDate;
			/** [int]时长，单位为毫秒 */
			int timespan;
			/** [double]时长排名，百分比制 */
			double playRank;
		} playInfo;
		/** struct of essInfo_GetPersonalReportResponseData_LoginInfo */
		struct essInfo_GetPersonalReportResponseData_LoginInfo {
			/** 城市记录(按城市登录次数排序) */
			DECLARE_LIST(CSTR) citys;
			/** 连续登录开始时间，格式：yyyy-MM-dd */
			CSTR startDate;
			/** [int]累积登录天数 */
			int loginDays;
			/** [int]连续登陆天数，（未登录为0，登陆过但不连续为1） */
			int runningDays;
			/** 连续登录结束时间,格式：yyyy-MM-dd */
			CSTR endDate;
		} loginInfo;
 
	} data;

} essInfo_GetPersonalReportResponse;

C_API essInfo_GetPersonalReportResponse *HSAPI_INIT(essInfo_GetPersonalReportResponse);

#endif
