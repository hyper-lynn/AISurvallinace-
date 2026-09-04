/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDevice_PreparationSet_H_
#define _HSVIEW_CLIENT_API_transferDevice_PreparationSet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
预案设置

- channelId 通道号
- selecting：设置的预案，预案类型如下
  -  regionNumberStat：区域客流；
  -  inOutNumberStat：进出客流；
  -  faceDetect：物体识别；
  -  heatmap：热度分析

参考PaaS协议：[预案设置](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E9%A2%84%E6%A1%88%E9%85%8D%E7%BD%AE%2F%E9%A2%84%E6%A1%88%E8%AE%BE%E7%BD%AE.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferDevice_PreparationSetRequest 
{
	HsviewRequest base;

	struct transferDevice_PreparationSetRequestData
	{
		
		/** [cstr]/device/preparation/config */
		#define _STATIC_transferDevice_PreparationSetRequestData_url "/device/preparation/config"
		CSTR url;
		/** struct of transferDevice_PreparationSetRequestData_Content */
		struct transferDevice_PreparationSetRequestData_Content {
			/** faceDetect */
			DECLARE_LIST(CSTR) selecting;
			/** 0 */
			CSTR channelId;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferDevice_PreparationSetRequest;

C_API transferDevice_PreparationSetRequest *HSAPI_INIT(transferDevice_PreparationSetRequest);

typedef struct transferDevice_PreparationSetResponse 
{
	HsviewResponse base;

	struct transferDevice_PreparationSetResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} transferDevice_PreparationSetResponse;

C_API transferDevice_PreparationSetResponse *HSAPI_INIT(transferDevice_PreparationSetResponse);

#endif
