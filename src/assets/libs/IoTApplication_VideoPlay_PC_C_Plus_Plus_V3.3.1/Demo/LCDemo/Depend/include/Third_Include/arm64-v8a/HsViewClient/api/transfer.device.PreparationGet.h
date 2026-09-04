/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDevice_PreparationGet_H_
#define _HSVIEW_CLIENT_API_transferDevice_PreparationGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
预案获取

- selected 已选预案
- preparations：可选预案
  -  regionNumberStat：区域客流；
  -  inOutNumberStat：进出客流；
  -  faceDetect：物体识别；
  -  heatmap：热度分析

参考PaaS协议：[预案获取](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E9%A2%84%E6%A1%88%E9%85%8D%E7%BD%AE%2F%E9%A2%84%E6%A1%88%E8%8E%B7%E5%8F%96.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferDevice_PreparationGetRequest 
{
	HsviewRequest base;

	struct transferDevice_PreparationGetRequestData
	{
		
		/** [cstr]/device/preparation/query */
		#define _STATIC_transferDevice_PreparationGetRequestData_url "/device/preparation/query"
		CSTR url;
		/** struct of transferDevice_PreparationGetRequestData_Content */
		struct transferDevice_PreparationGetRequestData_Content {
			/** 0 */
			CSTR channelId;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferDevice_PreparationGetRequest;

C_API transferDevice_PreparationGetRequest *HSAPI_INIT(transferDevice_PreparationGetRequest);

typedef struct transferDevice_PreparationGetResponse 
{
	HsviewResponse base;

	struct transferDevice_PreparationGetResponseData
	{
		
		/** regionNumberStat */
		DECLARE_LIST(CSTR) preparations;
		/** faceDetect */
		DECLARE_LIST(CSTR) selected;
 
	} data;

} transferDevice_PreparationGetResponse;

C_API transferDevice_PreparationGetResponse *HSAPI_INIT(transferDevice_PreparationGetResponse);

#endif
