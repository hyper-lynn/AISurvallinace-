/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDoorbell_ThirdRingTypeQuery_H_
#define _HSVIEW_CLIENT_API_transferDoorbell_ThirdRingTypeQuery_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取第三方铃铛类型

响应参数说明：
ringtime: 可选,响铃的时间，当前需求只有电子铃铛有时间，机械铃铛默认3秒
type：第三方铃铛的类型
0 未接，默认0
1 机械
2 电子

参考PaaS协议：[获取第三方铃铛类型](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E9%97%A8%E9%93%83%E7%9B%B8%E5%85%B3%E6%93%8D%E4%BD%9C%2F%E7%AC%AC%E4%B8%89%E6%96%B9%E9%93%83%E9%93%9B%2F%E8%8E%B7%E5%8F%96%E7%AC%AC%E4%B8%89%E6%96%B9%E9%93%83%E9%93%9B%E7%B1%BB%E5%9E%8B.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferDoorbell_ThirdRingTypeQueryRequest 
{
	HsviewRequest base;

	struct transferDoorbell_ThirdRingTypeQueryRequestData
	{
		
		/** [cstr]/device/third-ring/type/query */
		#define _STATIC_transferDoorbell_ThirdRingTypeQueryRequestData_url "/device/third-ring/type/query"
		CSTR url;
		/** struct of transferDoorbell_ThirdRingTypeQueryRequestData_Content */
		struct transferDoorbell_ThirdRingTypeQueryRequestData_Content {
			/** [O]通道,不存在默认为设备 */
			CSTR chan;
			/** [O]设备序列号 */
			CSTR sn;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferDoorbell_ThirdRingTypeQueryRequest;

C_API transferDoorbell_ThirdRingTypeQueryRequest *HSAPI_INIT(transferDoorbell_ThirdRingTypeQueryRequest);

typedef struct transferDoorbell_ThirdRingTypeQueryResponse 
{
	HsviewResponse base;

	struct transferDoorbell_ThirdRingTypeQueryResponseData
	{
		
		/** 可选,响铃的时间 */
		CSTR ringtime;
		/** [int] 第三方铃铛的类型,0 未接，默认0、1 机械、2 电子 */
		int type;
 
	} data;

} transferDoorbell_ThirdRingTypeQueryResponse;

C_API transferDoorbell_ThirdRingTypeQueryResponse *HSAPI_INIT(transferDoorbell_ThirdRingTypeQueryResponse);

#endif
