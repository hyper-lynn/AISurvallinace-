/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_query_H_
#define _HSVIEW_CLIENT_API_query_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
人数统计查询

start：查询起始时间，格式为yyyyMMddHHmm，
end：查询结束时间，格式为yyyyMMddHHmm，单次查询不超过24小时。
granularity：精度，默认按分钟, minute为分钟, hour为小时

results 为查询返回结果,in为进入人数, out为出去人数，查询结果包含查询起始的分钟或小时；


限制：
1、最大的查询时间段为1天；
2、如果经度选择小时，将忽略startTime 和 endTime的分钟；
 */

typedef struct queryRequest 
{
	HsviewRequest base;

	struct queryRequestData
	{
		
		/** 201607062300 */
		CSTR end;
		/** 201607061258 */
		CSTR start;
		/** 粒度, 可选, 默认按分钟, minute为分钟,hour为小时 */
		CSTR granularity;
		/** 设备序列号 */
		CSTR did;
		/** 设备通道号 */
		CSTR cid;

	} data;

} queryRequest;

C_API queryRequest *HSAPI_INIT(queryRequest);

typedef struct queryResponse 
{
	HsviewResponse base;

	struct queryResponseData
	{
		
		/** struct of queryResponseData_Data */
		struct queryResponseData_Data {
			/** [int]进入数 */
			DECLARE_LIST(int) in;
			/** [int]出去数 */
			DECLARE_LIST(int) out;
		} data;
 
	} data;

} queryResponse;

C_API queryResponse *HSAPI_INIT(queryResponse);

#endif
