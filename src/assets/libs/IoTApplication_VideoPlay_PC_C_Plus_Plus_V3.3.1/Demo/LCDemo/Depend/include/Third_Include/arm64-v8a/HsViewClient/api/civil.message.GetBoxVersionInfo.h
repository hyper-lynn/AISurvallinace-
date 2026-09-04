/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetBoxVersionInfo_H_
#define _HSVIEW_CLIENT_API_GetBoxVersionInfo_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取盒子版本信息，用于盒子升级。
【无需签名认证】
 */

typedef struct GetBoxVersionInfoRequest 
{
	HsviewRequest base;

	struct GetBoxVersionInfoRequestData
	{
		
		/** 需要获取的盒子设备型号，必填 */
		CSTR deviceModel;
		/** [int]可见标志，0-不可见，1-可见 */
		int readFlag;

	} data;

} GetBoxVersionInfoRequest;

C_API GetBoxVersionInfoRequest *HSAPI_INIT(GetBoxVersionInfoRequest);

typedef struct GetBoxVersionInfoResponse 
{
	HsviewResponse base;

	struct GetBoxVersionInfoResponseData
	{
		
		/** 最低版本号 */
		CSTR minimalVersion;
		/** 关键版本号 */
		CSTR keyVersion;
		/** define a list with struct of GetBoxVersionInfoResponseData_VersionsElement */
		DECLARE_LIST(struct GetBoxVersionInfoResponseData_VersionsElement
		{
			/** 备注描述 */
			CSTR memo;
			/** 基础版本全名。若此字段有值，表示此升级包为增量包。 */
			CSTR baseVersion;
			/** 下载地址 */
			CSTR downloadUrl;
			/** 设备型号 */
			CSTR deviceModel;
			/** [long]更新时间，Unix时间戳，1970年秒数 */
			int64 timestamp;
			/** 版本全名 */
			CSTR version;
			/** [int]升级包大小，单位字节B */
			int size;
		}) versions;
 
	} data;

} GetBoxVersionInfoResponse;

C_API GetBoxVersionInfoResponse *HSAPI_INIT(GetBoxVersionInfoResponse);

#endif
