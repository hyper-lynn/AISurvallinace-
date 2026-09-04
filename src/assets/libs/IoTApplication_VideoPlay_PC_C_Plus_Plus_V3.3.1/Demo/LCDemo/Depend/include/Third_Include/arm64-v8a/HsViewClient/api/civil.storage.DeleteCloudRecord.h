/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_DeleteCloudRecord_H_
#define _HSVIEW_CLIENT_API_DeleteCloudRecord_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
删除一个或几个录像，需要传入recordId。
如果是共享或者授权的设备录像，需要传入deviceId和channelId进行验权。

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

typedef struct DeleteCloudRecordRequest 
{
	HsviewRequest base;

	struct DeleteCloudRecordRequestData
	{
		
		/** [long]录像ID数组 */
		DECLARE_LIST(int64) recordId;
		/** [O]通道号，如果为空表示不进行验权 */
		CSTR channelId;
		/** [O]录像类型，如果为空表示原报警录像 */
		CSTR type;
		/** [O]设备ID，如果为空表示不进行验权 */
		CSTR deviceId;

	} data;

} DeleteCloudRecordRequest;

C_API DeleteCloudRecordRequest *HSAPI_INIT(DeleteCloudRecordRequest);

typedef struct DeleteCloudRecordResponse 
{
	HsviewResponse base;

	struct DeleteCloudRecordResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} DeleteCloudRecordResponse;

C_API DeleteCloudRecordResponse *HSAPI_INIT(DeleteCloudRecordResponse);

#endif
