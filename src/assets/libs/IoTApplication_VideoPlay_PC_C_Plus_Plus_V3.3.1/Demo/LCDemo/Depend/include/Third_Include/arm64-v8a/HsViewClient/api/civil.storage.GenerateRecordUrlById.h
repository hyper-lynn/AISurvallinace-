/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GenerateRecordUrlById_H_
#define _HSVIEW_CLIENT_API_GenerateRecordUrlById_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
生成云存储录像的URL用于客户端播放。

类型 - 含义                  - 是否加密    -  备注
1    - 手动录像              -    否       -  X-MINI设备功能
2    - 留言                  -    是       -  TC5S需求
3    - 求救录像              -    是       -  TC5S需求（废弃）
1000 - 告警（移动检测）录像  -    是       -  同file-stream（原报警录像）
1001 - 人头检测录像          -    是       -  TC5S需求
2000 - 云录像                -    是       -  定时录像
注：为空表示原报警录像

【使用平台账号签名】
 */

typedef struct GenerateRecordUrlByIdRequest 
{
	HsviewRequest base;

	struct GenerateRecordUrlByIdRequestData
	{
		
		/** [long]录像ID */
		int64 recordId;
		/** [O]录像类型，如果为空表示原报警录像 */
		CSTR type;

	} data;

} GenerateRecordUrlByIdRequest;

C_API GenerateRecordUrlByIdRequest *HSAPI_INIT(GenerateRecordUrlByIdRequest);

typedef struct GenerateRecordUrlByIdResponse 
{
	HsviewResponse base;

	struct GenerateRecordUrlByIdResponseData
	{
		
		/** 用于播放的录像URL地址 */
		CSTR url;
 
	} data;

} GenerateRecordUrlByIdResponse;

C_API GenerateRecordUrlByIdResponse *HSAPI_INIT(GenerateRecordUrlByIdResponse);

#endif
