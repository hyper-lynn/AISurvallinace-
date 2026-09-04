/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_PublicCloudRecord_H_
#define _HSVIEW_CLIENT_API_PublicCloudRecord_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
公开某个云存储录像，得到视频页面URL。
为了兼容老版本，标题可选

类型 - 含义                  - 是否加密    -  备注
1    - 手动录像              -    否       -  X-MINI设备功能
2    - 留言                  -    是       -  TC5S需求
3    - 求救录像              -    是       -  TC5S需求（废弃）
1000 - 告警（移动检测）录像  -    是       -  同file-stream（原报警录像）
1001 - 人头检测录像          -    是       -  TC5S需求
2000 - 云录像                -    是       -  定时录像
注：为空表示原报警录像

secretKey可选，自定义密钥情况下录的录像，在分享时需要携带解密密钥
【需要使用平台账号签名】
 */

typedef struct PublicCloudRecordRequest 
{
	HsviewRequest base;

	struct PublicCloudRecordRequestData
	{
		
		/** [long]云录像ID（查询云存储录像时得到） */
		int64 recordId;
		/** [O]录像类型，如果为空表示原报警录像 */
		CSTR type;
		/** [O]分享的标题 */
		CSTR title;
		/** [O]录像加密密钥，如abc123456 */
		CSTR secretKey;

	} data;

} PublicCloudRecordRequest;

C_API PublicCloudRecordRequest *HSAPI_INIT(PublicCloudRecordRequest);

typedef struct PublicCloudRecordResponse 
{
	HsviewResponse base;

	struct PublicCloudRecordResponseData
	{
		
		/** 公开视频的Token */
		CSTR token;
		/** 公开视频的页面URL */
		CSTR pageUrl;
 
	} data;

} PublicCloudRecordResponse;

C_API PublicCloudRecordResponse *HSAPI_INIT(PublicCloudRecordResponse);

#endif
