/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_advertisementInfo_OperateAdvertisement_H_
#define _HSVIEW_CLIENT_API_advertisementInfo_OperateAdvertisement_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
用户查看、关闭广告信息
【需要使用平台账号签名】
 */

typedef struct advertisementInfo_OperateAdvertisementRequest 
{
	HsviewRequest base;

	struct advertisementInfo_OperateAdvertisementRequestData
	{
		
		/** checkedClose:查看广告详情后关闭广告； close：未看详情直接关闭广告;show:客户端展示广告 */
		CSTR operation;
		/** [O]notInterested/poorContent/duplicateContent——不感兴趣/内容质量差/内容重复 */
		CSTR closeType;
		/** [long]广告id */
		int64 advertisementId;

	} data;

} advertisementInfo_OperateAdvertisementRequest;

C_API advertisementInfo_OperateAdvertisementRequest *HSAPI_INIT(advertisementInfo_OperateAdvertisementRequest);

typedef struct advertisementInfo_OperateAdvertisementResponse 
{
	HsviewResponse base;

	struct advertisementInfo_OperateAdvertisementResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} advertisementInfo_OperateAdvertisementResponse;

C_API advertisementInfo_OperateAdvertisementResponse *HSAPI_INIT(advertisementInfo_OperateAdvertisementResponse);

#endif
