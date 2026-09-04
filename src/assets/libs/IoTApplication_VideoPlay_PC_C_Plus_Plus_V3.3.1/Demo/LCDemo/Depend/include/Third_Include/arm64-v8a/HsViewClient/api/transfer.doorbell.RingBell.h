/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDoorbell_RingBell_H_
#define _HSVIEW_CLIENT_API_transferDoorbell_RingBell_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
控制响铃

参考PaaS协议：[控制响铃](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E9%97%A8%E9%93%83%E7%9B%B8%E5%85%B3%E6%93%8D%E4%BD%9C%2F%E5%93%8D%E9%93%83%2F%E6%8E%A7%E5%88%B6%E5%93%8D%E9%93%83.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferDoorbell_RingBellRequest 
{
	HsviewRequest base;

	struct transferDoorbell_RingBellRequestData
	{
		
		/** [cstr]/device/ring/bell/nty */
		#define _STATIC_transferDoorbell_RingBellRequestData_url "/device/ring/bell/nty"
		CSTR url;
		/** struct of transferDoorbell_RingBellRequestData_Content */
		struct transferDoorbell_RingBellRequestData_Content {
			/** [int]歌曲索引 */
			int index;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferDoorbell_RingBellRequest;

C_API transferDoorbell_RingBellRequest *HSAPI_INIT(transferDoorbell_RingBellRequest);

typedef struct transferDoorbell_RingBellResponse 
{
	HsviewResponse base;

	struct transferDoorbell_RingBellResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} transferDoorbell_RingBellResponse;

C_API transferDoorbell_RingBellResponse *HSAPI_INIT(transferDoorbell_RingBellResponse);

#endif
