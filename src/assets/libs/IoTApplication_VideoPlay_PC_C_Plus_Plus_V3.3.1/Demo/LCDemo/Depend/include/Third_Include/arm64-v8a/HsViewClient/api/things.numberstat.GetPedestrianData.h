/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_thingsNumberstat_GetPedestrianData_H_
#define _HSVIEW_CLIENT_API_thingsNumberstat_GetPedestrianData_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取客流量数据
* detail的数组限制大小为50个
* 开始时间、结束时间，本地时间、UTC时间出现需要配对
* 若为时间点数据，则开始时间、结束时间相同即可
 */

typedef struct thingsNumberstat_GetPedestrianDataRequest 
{
	HsviewRequest base;

	struct thingsNumberstat_GetPedestrianDataRequestData
	{
		
		/** [int]每次返回的单页最大记录数 */
		int numsPerPage;
		/** [int]进、出、停留的类型标记（0：进，1：出，2：停留） */
		int action;
		/** 记录的结束时间，设备时间 */
		CSTR endTime;
		/** 设备序列号 */
		CSTR deviceId;
		/** [int]正序、倒序查询（0：正序，1：倒序） */
		int order;
		/** [int]当前页码, 从0开始 */
		int pageNum;
		/** 记录的开始时间，UTC时间 */
		CSTR beginUtcTime;
		/** 通道号 */
		CSTR channelId;
		/** 记录的开始时间，设备时间 */
		CSTR beginTime;
		/** 记录的结束时间，UTC时间 */
		CSTR endUtcTime;
		/** [int]查询区域ID数组 */
		DECLARE_LIST(int) areaID;

	} data;

} thingsNumberstat_GetPedestrianDataRequest;

C_API thingsNumberstat_GetPedestrianDataRequest *HSAPI_INIT(thingsNumberstat_GetPedestrianDataRequest);

typedef struct thingsNumberstat_GetPedestrianDataResponse 
{
	HsviewResponse base;

	struct thingsNumberstat_GetPedestrianDataResponseData
	{
		
		/** define a list with struct of thingsNumberstat_GetPedestrianDataResponseData_DetailElement */
		DECLARE_LIST(struct thingsNumberstat_GetPedestrianDataResponseData_DetailElement
		{
			/** [int]该时间段检测到的总人数 */
			int number;
			/** 记录的开始时间，UTC时间 */
			CSTR beginUtcTime;
			/** 记录的结束时间，设备时间 */
			CSTR endTime;
			/** 记录的开始时间，设备时间 */
			CSTR beginTime;
			/** 记录的结束时间，UTC时间 */
			CSTR endUtcTime;
			/** [int]区域ID, 可选, 没有该字段或者为0，为单区域 */
			int areaID;
		}) detail;
 
	} data;

} thingsNumberstat_GetPedestrianDataResponse;

C_API thingsNumberstat_GetPedestrianDataResponse *HSAPI_INIT(thingsNumberstat_GetPedestrianDataResponse);

#endif
