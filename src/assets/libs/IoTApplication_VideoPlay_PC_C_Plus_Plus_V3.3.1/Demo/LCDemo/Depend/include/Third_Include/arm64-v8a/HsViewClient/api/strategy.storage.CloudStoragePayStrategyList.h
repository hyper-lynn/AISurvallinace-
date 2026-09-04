/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_strategyStorage_CloudStoragePayStrategyList_H_
#define _HSVIEW_CLIENT_API_strategyStorage_CloudStoragePayStrategyList_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
批量获取设备云存储套餐详情

【使用平台账号签名】
 */

typedef struct strategyStorage_CloudStoragePayStrategyListRequest 
{
	HsviewRequest base;

	struct strategyStorage_CloudStoragePayStrategyListRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} strategyStorage_CloudStoragePayStrategyListRequest;

C_API strategyStorage_CloudStoragePayStrategyListRequest *HSAPI_INIT(strategyStorage_CloudStoragePayStrategyListRequest);

typedef struct strategyStorage_CloudStoragePayStrategyListResponse 
{
	HsviewResponse base;

	struct strategyStorage_CloudStoragePayStrategyListResponseData
	{
		
		/** define a list with struct of strategyStorage_CloudStoragePayStrategyListResponseData_GroupItemsElement */
		DECLARE_LIST(struct strategyStorage_CloudStoragePayStrategyListResponseData_GroupItemsElement
		{
			/** [int]商品数量 */
			int goodNum;
			/** [int]排序值，越大越靠前 */
			int sortVal;
			/** [int]分组id,取值[1,N]（N为正整数，且后者＞前者） */
			int groupId;
			/** [int]0-非活动 1-活动 */
			int isActivity;
			/** define a list with struct of strategyStorage_CloudStoragePayStrategyListResponseData_GroupItemsElement_GoodItemsElement */
			DECLARE_LIST(struct strategyStorage_CloudStoragePayStrategyListResponseData_GroupItemsElement_GoodItemsElement
			{
				/** 商品标签图 */
				CSTR labelImg;
				/** 商品描述 */
				CSTR goodDesc;
				/** [int]存储时长,单位天 */
				int remainDay;
				/** [double][O]自动续费价格,两位小数 */
				double autoRenewalPrice;
				/** [int]服务时长,单位秒 */
				int serviceTime;
				/** 商品主图 */
				CSTR mainImg;
				/** 商品类型 */
				CSTR goodTypeId;
				/** 币种，如USD,AUD */
				CSTR currency;
				/** 币种符号，如￥，$ */
				CSTR currencySymbol;
				/** [O]on/off，该套餐是否为自动续费套餐 */
				CSTR isAutoRenewal;
				/** [double]市场价,两位小数 */
				double mktPrice;
				/** [int]商品id */
				int goodId;
				/** 商品名称 */
				CSTR goodName;
				/** [double]销售价,两位小数 */
				double salePrice;
			}) goodItems;
			/** 分组名称 */
			CSTR groupName;
			/** 创建时间,UTC时间戳,精确到秒 */
			CSTR createTime;
		}) groupItems;
		/** define a list with struct of strategyStorage_CloudStoragePayStrategyListResponseData_AccountsElement */
		DECLARE_LIST(struct strategyStorage_CloudStoragePayStrategyListResponseData_AccountsElement
		{
			/** [O]stripe和adyen支付对应的apikey,paypal不需要 */
			CSTR apiKey;
			/** 支付类型：paypal,stripe信用卡,微信等 */
			CSTR accountType;
			/** 支付账号：paypal账号,stripe支付码等 */
			CSTR accountNumber;
		}) accounts;
 
	} data;

} strategyStorage_CloudStoragePayStrategyListResponse;

C_API strategyStorage_CloudStoragePayStrategyListResponse *HSAPI_INIT(strategyStorage_CloudStoragePayStrategyListResponse);

#endif
