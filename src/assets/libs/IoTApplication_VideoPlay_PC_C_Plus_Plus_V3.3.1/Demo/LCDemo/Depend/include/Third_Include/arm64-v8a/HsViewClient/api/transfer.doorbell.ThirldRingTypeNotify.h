/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDoorbell_ThirldRingTypeNotify_H_
#define _HSVIEW_CLIENT_API_transferDoorbell_ThirldRingTypeNotify_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
通知门铃第三方铃铛类型

sn[可选]，设备序列号
chan[可选]，通道,不存在默认为设备
ringtime:可选,响铃的时间，当前需求只有电子铃铛有时间，机械铃铛默认3秒
type：第三方铃铛的类型
0 未接，默认0
1 机械
2 电子

参考PaaS协议：[通知门铃第三方铃铛类型](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E9%97%A8%E9%93%83%E7%9B%B8%E5%85%B3%E6%93%8D%E4%BD%9C%2F%E7%AC%AC%E4%B8%89%E6%96%B9%E9%93%83%E9%93%9B%2F%E9%80%9A%E7%9F%A5%E9%97%A8%E9%93%83%E7%AC%AC%E4%B8%89%E6%96%B9%E9%93%83%E9%93%9B%E7%B1%BB%E5%9E%8B.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferDoorbell_ThirldRingTypeNotifyRequest 
{
	HsviewRequest base;

	struct transferDoorbell_ThirldRingTypeNotifyRequestData
	{
		
		/** [cstr]/device/third-ring/type/nty */
		#define _STATIC_transferDoorbell_ThirldRingTypeNotifyRequestData_url "/device/third-ring/type/nty"
		CSTR url;
		/** struct of transferDoorbell_ThirldRingTypeNotifyRequestData_Content */
		struct transferDoorbell_ThirldRingTypeNotifyRequestData_Content {
			/** [O]响铃的时间，当前需求只有电子铃铛有时间，机械铃铛默认3秒 */
			CSTR ringtime;
			/** [int] 第三方铃铛的类型,0 未接，默认0、1 机械、2 电子 */
			int type;
			/** [O]通道,不存在默认为设备 */
			CSTR chan;
			/** [O]设备序列号 */
			CSTR sn;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferDoorbell_ThirldRingTypeNotifyRequest;

C_API transferDoorbell_ThirldRingTypeNotifyRequest *HSAPI_INIT(transferDoorbell_ThirldRingTypeNotifyRequest);

typedef struct transferDoorbell_ThirldRingTypeNotifyResponse 
{
	HsviewResponse base;

	struct transferDoorbell_ThirldRingTypeNotifyResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} transferDoorbell_ThirldRingTypeNotifyResponse;

C_API transferDoorbell_ThirldRingTypeNotifyResponse *HSAPI_INIT(transferDoorbell_ThirldRingTypeNotifyResponse);

#endif
