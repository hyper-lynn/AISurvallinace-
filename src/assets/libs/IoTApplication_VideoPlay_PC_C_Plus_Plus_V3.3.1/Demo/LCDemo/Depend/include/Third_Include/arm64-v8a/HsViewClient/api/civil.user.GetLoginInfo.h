/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetLoginInfo_H_
#define _HSVIEW_CLIENT_API_GetLoginInfo_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取自己这个请求的用户（签名认证中携带的账号）前几次登陆的信息（返回数组）：
timestamp：上次登陆的Unix时间戳（UTC时间，1970年来秒数）。
ip：上次登陆的IP。
clientType：上次登陆的客户端类型，“web”或者“phone”。
clientName：上次登陆的客户端名称，web填浏览器类型，phone填手机型号。
refLocation：上次登陆的参考地址（不一定准确）。
【使用平台账号签名】
 */

typedef struct GetLoginInfoRequest 
{
	HsviewRequest base;

	struct GetLoginInfoRequestData
	{
		
		/** [int]需要获取的记录条数 */
		int count;

	} data;

} GetLoginInfoRequest;

C_API GetLoginInfoRequest *HSAPI_INIT(GetLoginInfoRequest);

typedef struct GetLoginInfoResponse 
{
	HsviewResponse base;

	struct GetLoginInfoResponseData
	{
		
		/** define a list with struct of GetLoginInfoResponseData_RecordsElement */
		DECLARE_LIST(struct GetLoginInfoResponseData_RecordsElement
		{
			/** 登陆时参考地址，如“浙江”，不一定准确 */
			CSTR refLocation;
			/** 客户端名称 */
			CSTR clientName;
			/** [long]登陆时的UNIX时间戳秒 */
			int64 timestamp;
			/** 客户端类型，web或phone */
			CSTR clientType;
			/** 登陆时的IP地址，如1.2.3.4 */
			CSTR ip;
		}) records;
 
	} data;

} GetLoginInfoResponse;

C_API GetLoginInfoResponse *HSAPI_INIT(GetLoginInfoResponse);

#endif
