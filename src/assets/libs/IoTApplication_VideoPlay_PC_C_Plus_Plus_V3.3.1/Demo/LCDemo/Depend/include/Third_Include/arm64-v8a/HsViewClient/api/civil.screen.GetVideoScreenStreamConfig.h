/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetVideoScreenStreamConfig_H_
#define _HSVIEW_CLIENT_API_GetVideoScreenStreamConfig_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置视频分屏轮巡拉流时间。
【使用平台账号签名】
 */

typedef struct GetVideoScreenStreamConfigRequest 
{
	HsviewRequest base;

	struct GetVideoScreenStreamConfigRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} GetVideoScreenStreamConfigRequest;

C_API GetVideoScreenStreamConfigRequest *HSAPI_INIT(GetVideoScreenStreamConfigRequest);

typedef struct GetVideoScreenStreamConfigResponse 
{
	HsviewResponse base;

	struct GetVideoScreenStreamConfigResponseData
	{
		
		/** [int]十六分屏拉流时间设置, 单位秒 */
		int sixteenScreen;
		/** [int]九分屏拉流时间设置, 单位秒 */
		int nineScreen;
		/** [int]四分屏拉流时间设置, 单位秒 */
		int fourScreen;
		/** [int]一分屏拉流时间设置, 单位秒 */
		int oneScreen;
 
	} data;

} GetVideoScreenStreamConfigResponse;

C_API GetVideoScreenStreamConfigResponse *HSAPI_INIT(GetVideoScreenStreamConfigResponse);

#endif
